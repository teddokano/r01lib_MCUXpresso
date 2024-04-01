/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"

SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
PCA9957		ledd( spi );

int main(void)
{
	PRINTF("***** Hello, PCA9957! *****\r\n");

	ledd.begin( 1.0, PCA9957::ARDUINO_SHIELD );

	while ( true )
	{
		ledd.pwm( 0, 1.0 );
		wait( 0.1 );
		ledd.pwm( 0, 0.0 );
		wait( 0.1 );
	}
}
