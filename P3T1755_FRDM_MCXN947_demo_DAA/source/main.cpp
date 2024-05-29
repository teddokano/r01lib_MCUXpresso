/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"pin_control.h"
#include	"temp_sensor/P3T1755.h"
#include	<time.h>

I3C		i3c( I3C_SDA, I3C_SCL );	//	SDA, SCL

const uint8_t	static_address_list[]	= { 0x48, 0x4A, 0x4C };
const uint8_t	dynamic_address_list[]	= { 0x1A, 0x2B, 0x3C };

P3T1755	sensor[]	= {
						P3T1755( i3c, static_address_list[ 0 ] ),
						P3T1755( i3c, static_address_list[ 1 ] ),
						P3T1755( i3c, static_address_list[ 2 ] )
				  };

P3T1755	lm75b( i3c, 0x4F );

#define	WAIT_SEC	0.96

DigitalOut	r(    RED   );
DigitalOut	g(    GREEN );
DigitalOut	b(    BLUE  );
DigitalOut	trig( MB_INT);	//	IBI detection trigger output for oscilloscope
InterruptIn	mode_delect_button( SW3 );

bool	i3c_mode	= true;

void	DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address );
int		DAA( const uint8_t *address_list, uint8_t list_length );
void	mode_select_callback( void );

int main( void )
{
	init_pin_control();
	i3c.set_IBI_callback( ibi_trigger_output );

	PRINTF("\r\nP3T1755 (Temperature sensor) I3C operation sample: getting temperature data and IBI\r\n");

	int	ndev	= DAA( dynamic_address_list, sizeof( dynamic_address_list ) );

	float	ref_temp	= 0;

	for ( int i = 0; i < ndev; i++)
	{
		sensor[ i ].address_overwrite( dynamic_address_list[ i ] );

		ref_temp	= sensor[ i ];
		sensor[ i ].high( ref_temp + 2.0 );
		sensor[ i ].low(  ref_temp + 1.0 );

		sensor[ i ].conf( sensor[ i ].conf() | 0x02 );	//	ALART pin configured to INT mode
		sensor[ i ].ccc_set( CCC::DIRECT_ENEC, 0x01 );	// Enable IBI

		sensor[ i ].info();
	}

	float	temp	= 0;
	uint8_t	ibi_addr;

	mode_delect_button.rise( mode_select_callback );

	while ( true )
	{
		if ( (ibi_addr	= i3c.check_IBI()) )
			PRINTF( "\r\n*** IBI : Got IBI from target_address: 0x%02X", ibi_addr );

		PRINTF( "\r\n" );

		for ( int i = 0; i < ndev; i++)
			PRINTF( "  %8.4f˚C @%02X", (float)sensor[ i ], dynamic_address_list[ i ] );

		i3c.mode( I3C::I2C_MODE );
		PRINTF( "  %7.3f˚C @4F(I2C)", (float)lm75b );
		i3c.mode( I3C::I3C_MODE );

		led_set_color( temp, ref_temp );
		wait( WAIT_SEC );
	}
}

void DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address )
{
	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	i3c.ccc_set( CCC::DIRECT_SETDASA, static_address, dynamic_address << 1 ); // Set Dynamic Address from Static Address
}

int DAA( const uint8_t *address_list, uint8_t list_length )
{
	i3c_device_info_t	*list_p;
	int					n_devices;

	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	n_devices	= i3c.DAA( address_list, list_length, &list_p );

	printf( "\r\n=== DAA result: total %d target(s) found\r\n", n_devices );
	for ( int i = 0; i < n_devices; i++ )
	{
		printf( "Target %d\r\n", i );
		printf( "  dynamicAddr    = 0x%02X\r\n",  list_p[ i ].dynamicAddr    );
		printf( "  staticAddr     = 0x%02X\r\n",  list_p[ i ].staticAddr     );
		printf( "  dcr            = 0x%02X\r\n",  list_p[ i ].dcr            );
		printf( "  bcr            = 0x%02X\r\n",  list_p[ i ].bcr            );
		printf( "  vendorID       = 0x%04X\r\n",  list_p[ i ].vendorID       );
		printf( "  partNumber     = 0x%08lX\r\n", list_p[ i ].partNumber     );
		printf( "  maxReadLength  = 0x%04X\r\n",  list_p[ i ].maxReadLength  );
		printf( "  maxWriteLength = 0x%04X\r\n",  list_p[ i ].maxWriteLength );
		printf( "  hdrMode        = 0x%02X\r\n",  list_p[ i ].hdrMode        );
		printf( "\r\n" );
	}

	return n_devices;
}

void mode_select_callback( void )
{
	i3c_mode	= !i3c_mode;
}
