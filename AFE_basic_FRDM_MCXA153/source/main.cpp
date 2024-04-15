/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"NAFE13388.h"

SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
NAFE13388	afe( spi );
InterruptIn	ADC_nDRDY( D3 );			//	ADC_nDRDY is re-routed to D3 by pin-adapter

bool	flag_RDY	= false;

void	logical_ch_config_view( int channel );
double	single_read( int channel );
void	callback_RDY( void );

int main( void )
{
	printf( "***** Hello, NAFE13388! *****\r\n" );

	spi.frequency( 1000 * 1000 );
	spi.mode( 1 );

	afe.begin();

	afe.logical_ch_config( 0, 0x1070, 0x0084, 0x0200, 0x0000 );
	afe.logical_ch_config( 1, 0x1070, 0x0084, 0x0200, 0x0000 );

	logical_ch_config_view( 0 );
	logical_ch_config_view( 1 );

	printf( "values in micro-volts\r\n" );

	ADC_nDRDY.rise( callback_RDY );
	
	while ( true )
	{		
		printf( "%11.2f, %11.2f\r\n", single_read( 0 ), single_read( 0 ) );
	}
}

double single_read( int ch )
{
	afe.start( 0 );
	
	while ( !flag_RDY )
		;

	return afe.read( ch );
}

void callback_RDY( void )
{
	flag_RDY	= true;
}

void logical_ch_config_view( int channel )
{
	printf( "logical channel: %02d\r\n", channel );

	afe.write_r16( channel );

	printf( "  0x%04X\r\n", afe.read_r16( 0x0020 ) );
	printf( "  0x%04X\r\n", afe.read_r16( 0x0021 ) );
	printf( "  0x%04X\r\n", afe.read_r16( 0x0022 ) );
	printf( "  0x%04X\r\n", afe.read_r16( 0x0023 ) );
	printf( "\r\n" );
}
