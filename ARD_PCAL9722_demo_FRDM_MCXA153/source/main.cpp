/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"gpio/PCAL9722.h"
#include	<ctype.h>

SPI			spi( D11, D12, D13, D10 );
PCAL9722	gpio( spi );

bool			int_flag		= false;

void message( const char *s );
void disp7seg( char c );
void callback( void );

int main( void )
{
	InterruptIn		int_pin( D10 );

	printf( "***** Hello, PCAL9722! *****\r\n" );
	gpio.begin( PCAL9722::ARDUINO_SHIELD );

	uint8_t io_config_and_pull_up[] = {
		0x00,	// Configure port0 as OUTPUT
		0x00,	// Configure port1 as OUTPUT
		0xF0,	// Configure port2 bit 7~4 as INTPUT
	};

	gpio.config( io_config_and_pull_up );					//  Port0, 1 and port2 bit 3~0 are configured as output
	gpio.write_port( PULL_UD_EN,  io_config_and_pull_up );	//  Pull-up/down enabled for port2 bit 7~4
	gpio.write_port( PULL_UD_SEL, io_config_and_pull_up );	//  Pull-up selected for port2 bit 7~4

	gpio.write_port(INT_MASK, (uint8_t)(~0xF0), 2);			//  Interrupt mask cleared pn port2 bit 3~0

	int_pin.fall( callback );

	message( "Hello PCAL9722" );
	message( "0123456789" );

	while ( true )
	{
		static uint8_t	pat[] = {  //  LED blinking pattern
			0xFE, 0xFB, 0xFD, 0xEF, 0xF7, 0xBF, 0xDF,
			0x7F, 0xDF, 0xBF, 0xF7, 0xEF, 0xFD, 0xFB,
		};
		static int	count = 0;
		uint8_t input2;

		if ( int_flag )
		{
			int_flag = false;

			uint8_t	status[ gpio.n_ports ];

			gpio.read_port( INT_STATUS, status );

			printf( "[INT] status 0~2:" );

			for ( int i = 0; i < gpio.n_ports; i++ )
				GPIO_base::print_bin( status[ i ] );

			input2	= gpio.input( 2 );

			printf( ",  input 2: " );
			GPIO_base::print_bin( input2 );
			printf( "\r\n" );
		}
		else
		{
			input2	= gpio.input( 2 );
		}

		gpio.output( 0, (input2 >> 4) & pat[ count++ % sizeof( pat ) ] );
		wait( 0.08 );
	}
}

void message( const char *s )
{
	char c;

	while ( (c	= *s++) )
	{
		disp7seg( c );
		wait( 0.2 );
		disp7seg( 0xFF );
		wait( 0.1 );
	}
}

void disp7seg( char c )
{
	static uint8_t	patterns[]	= {
			0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,	//	0~7
			0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, //	8~F
			0xC2, 0x89, 0xCF, 0xF1, 0x8D, 0xC7, 0xAA, 0xAB,	//	G~N
			0xA3, 0x8C, 0x98, 0xAF, 0x92, 0x87, 0xE3, 0xC1,	//	O~V
			0xE2, 0x9B, 0x91, 0xB6							//	W~Z
	};

	if ( isdigit( c ) )
		gpio.output( 1, patterns[ c - '0' ] );
	else if ( isalpha( c ) )
		gpio.output( 1, patterns[ tolower( c ) - 'a' ] );
	else if ( '.' == c )
		gpio.output( 1, 0x7F );
	else
		gpio.output( 1, 0xFF );
}

void callback( void )
{
	int_flag = true;
}
