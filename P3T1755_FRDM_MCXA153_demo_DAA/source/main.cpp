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
P3T1755	p3t1755( i3c, P3T1755_ADDR_I2C );

#define	WAIT_SEC	0.97

DigitalOut	r(    RED   );
DigitalOut	g(    GREEN );
DigitalOut	b(    BLUE  );
DigitalOut	trig( D2    );	//	IBI detection trigger output for oscilloscope

void	DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address );
void	DAA( const uint8_t *address_list, uint8_t list_length );

int main(void)
{
	init_pin_control();
	i3c.set_IBI_callback( ibi_trigger_output );

	PRINTF("\r\nP3T1755 (Temperature sensor) I3C operation sample: getting temperature data and IBI\r\n");

#if 0
	DAA_set_dynamic_ddress_from_static_ddress( P3T1755_ADDR_I2C, P3T1755_ADDR_I3C );
	p3t1755.address_overwrite( P3T1755_ADDR_I3C );
#else
	const uint8_t	address_list[]	= { 0x08, 0x09, 0x0A };
	DAA( address_list, sizeof( address_list ) );
	p3t1755.address_overwrite( P3T1755_ADDR_I3C );
#endif

	float ref_temp	= p3t1755;
	float low		= ref_temp + 1.0;
	float high		= ref_temp + 2.0;

	p3t1755.high( high );
	p3t1755.low(  low  );

	PRINTF( "  T_LOW / T_HIGH registers updated: %8.4f˚C / %8.4f˚C\r\n", low, high );
	PRINTF( "      based on current temperature: %8.4f˚C\r\n", ref_temp );

	p3t1755.conf( p3t1755.conf() | 0x02 );		//	ALART pin configured to INT mode
	p3t1755.ccc_set( CCC::DIRECT_ENEC, 0x01 );	// Enable IBI

	p3t1755.info();

	float	temp;
	uint8_t	ibi_addr;

	while ( true )
	{
		if ( (ibi_addr	= i3c.check_IBI()) )
			PRINTF("Read at %7.2f sec: *** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\r\n", (float)clock() / CLOCKS_PER_SEC, ibi_addr, ibi_addr << 1 );

		temp	= p3t1755;
		PRINTF( "Read at %7.2f sec: Temperature: %8.4f˚C\r\n", (float)clock() / CLOCKS_PER_SEC, temp );

		led_set_color( temp, ref_temp );
		wait( WAIT_SEC );
	}
}

void DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address )
{
	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	i3c.ccc_set( CCC::DIRECT_SETDASA, static_address, dynamic_address << 1 ); // Set Dynamic Address from Static Address
}

void DAA( const uint8_t *address_list, uint8_t list_length )
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
}
