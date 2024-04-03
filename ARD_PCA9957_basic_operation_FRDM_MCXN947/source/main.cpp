/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"

SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
DigitalOut	rst( D8, 1 );
DigitalOut	oe(  D9, 0 );

constexpr uint8_t	MODE2		= 0x01;
constexpr uint8_t	LEDOUT0		= 0x08;
constexpr uint8_t	IREFALL		= 0x6B;
constexpr uint8_t	PWM0_reg	= 0x10;

int main( void )
{
	uint8_t	w_data[]	= {
			(LEDOUT0 + 0) << 1, 0xAA,
			(LEDOUT0 + 1) << 1, 0xAA,
			(LEDOUT0 + 2) << 1, 0xAA,
			(LEDOUT0 + 3) << 1, 0xAA,
			(LEDOUT0 + 4) << 1, 0xAA,
			(LEDOUT0 + 5) << 1, 0xAA
	};
	uint8_t	m2_data[]	= { MODE2   << 1, 0x18 };	//	clear error and no auto switch-off
	uint8_t	iref_data[]	= { IREFALL << 1, 0xFF };	//	output current maximum
	uint8_t	pwm_data[ 2 ];
	uint8_t	dummy[ sizeof( w_data ) ];

	spi.write( m2_data,   dummy, sizeof( iref_data ) );
	spi.write( w_data,    dummy, sizeof(    w_data ) );
	spi.write( iref_data, dummy, sizeof( iref_data ) );

	while ( true )
	{
		for ( int channel = 0; channel < 24; channel++ )
		{
			pwm_data[ 0 ]	= (PWM0_reg + channel) << 1;

			for ( int pwm = 0; pwm < 256; pwm++ )
			{
				pwm_data[ 1 ]	= pwm;
				spi.write( pwm_data, dummy, sizeof( pwm_data ) );
				wait( 0.01 );
			}

			pwm_data[ 1 ]	= 0x00;
			spi.write( pwm_data, dummy, sizeof( pwm_data ) );
		}
	}
}
