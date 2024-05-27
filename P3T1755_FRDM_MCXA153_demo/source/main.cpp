/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"pin_control.h"
#include	"temp_sensor/P3T1755.h"

I3C		i3c( I3C_SDA, I3C_SCL );	//	SDA, SCL
P3T1755	p3t1755( i3c, P3T1755_ADDR_I2C );

#define	WAIT_SEC	1.00

DigitalOut	r(    RED   );
DigitalOut	g(    GREEN );
DigitalOut	b(    BLUE  );
DigitalOut	trig( D2    );	//	IBI detection trigger output for oscilloscope

void	DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address );

int main( void )
{
	init_pin_control();
	i3c.set_IBI_callback( ibi_trigger_output );

	PRINTF("P3T1755 (Temperature sensor) I3C operation sample: getting temperature data and IBI\r\n");

	DAA_set_dynamic_ddress_from_static_ddress( P3T1755_ADDR_I2C, P3T1755_ADDR_I3C );
	p3t1755.address_overwrite( P3T1755_ADDR_I3C );

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

	float		temp;
	uint8_t		ibi_addr;
	uint32_t	count	= 0;

	while ( true )
	{
		if ( (ibi_addr	= i3c.check_IBI()) )
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\r\n", ibi_addr, ibi_addr << 1 );

		temp	= p3t1755;
		PRINTF( "Read at %4lu sec: Temperature: %8.4f˚C\r\n", count++, temp );

		led_set_color( temp, ref_temp );
		wait( WAIT_SEC );
	}
}

void DAA_set_dynamic_ddress_from_static_ddress( uint8_t static_address, uint8_t dynamic_address )
{
	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	i3c.ccc_set( CCC::DIRECT_SETDASA, static_address, dynamic_address << 1 ); // Set Dynamic Address from Static Address
}
