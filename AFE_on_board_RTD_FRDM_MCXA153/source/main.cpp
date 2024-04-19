/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"NAFE13388.h"

#define		LOGICAL_CHANNEL	0

SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
NAFE13388	afe( spi );
InterruptIn	ADC_nDRDY( D3 );			//	ADC_nDRDY is re-routed to D3 by pin-adapter

volatile bool	flag_RDY	= false;

double	calc_temp( double micro_volt );
void	logical_ch_config_view( int channel );
void	system_level_config_view( void );
double	single_read( int channel, bool raw = false );
void	callback_RDY( void );

int main( void )
{
	printf( "***** Hello, NAFE13388! *****\r\n" );

	spi.frequency( 1000 * 1000 );
	spi.mode( 1 );

	afe.begin();

	afe.write_r16( 0x002B, 0x00C0 );
	system_level_config_view();

	afe.logical_ch_config( LOGICAL_CHANNEL, 0xAA02, 0x0058, 0x2C80, 0x0000 );
	logical_ch_config_view( LOGICAL_CHANNEL );

	printf( "values in ratio\r\n" );

	ADC_nDRDY.rise( callback_RDY );
	
	double	micro_volt;
	double	temp;

	while ( true )
	{
		micro_volt	= single_read( LOGICAL_CHANNEL );
		temp		= calc_temp( micro_volt );

		printf( "temp = %f˚C\r\n", temp );
		wait( 1.0 );
	}
}

double calc_temp( double micro_volt )
{
	static constexpr double	r_series	= 2940 * 2;
	static constexpr double	v_cc		= 2.5;
	static constexpr double	k			= 0.385;

	double	v_rtd						= micro_volt * 1e-6;
	double	r_rtd;

	r_rtd	= (r_series * v_rtd) / (v_cc - v_rtd);

	printf( "V_RTD = %9.2fuV,  R_RTD = %6.2fohms,  ", micro_volt, r_rtd );

	return (r_rtd  - 100.0) / k;
}

double single_read( int ch, bool raw )
{
	flag_RDY	= false;

	afe.start( ch );
	
	while ( !flag_RDY )
		;

	return afe.read( ch, raw );
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

void system_level_config_view( void )
{
	printf( "  SYS_CONFIG0 : 0x%04X\r\n", afe.read_r16( 0x0030 ) );
	printf( "  GPIO_CONFIG0: 0x%04X\r\n", afe.read_r16( 0x002A ) );
	printf( "  GPIO_CONFIG1: 0x%04X\r\n", afe.read_r16( 0x002B ) );
	printf( "  GPIO_CONFIG2: 0x%04X\r\n", afe.read_r16( 0x002C ) );
	printf( "\r\n" );
}
