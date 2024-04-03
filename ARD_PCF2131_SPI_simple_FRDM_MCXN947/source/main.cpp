/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"rtc/PCF2131_SPI.h"
#include	"rtc/tzcode/strptime.h"
#include	<time.h>

SPI			spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
PCF2131_SPI	rtc( spi );
const char	*intf_str	= "SPI";

void	set_time( void );

int main( void )
{
	printf( "***** Hello, PCF2131! (%s interface) *****\r\n", intf_str );

	if ( rtc.oscillator_stop() )
	{
		printf( "==== oscillator_stop detected :( ====\r\n" );
		set_time();
	}
	else
	{
		printf( "---- RTC has beeing kept running! :) ----\r\n" );
	}

	time_t	current_time;

	while ( true )
	{
		current_time	= rtc.time( NULL );

		printf( "time : %lu, %s", (unsigned long)current_time, ctime( &current_time ) );
		wait( 1 );
	}
}

void set_time( void ) {
	const char* current_time	= "2024-4-1 10:41:30";
	const char* format			= "%Y-%m-%d %H:%M:%S";
	struct tm	now_tm;

	strptime( current_time, format, &now_tm );
	rtc.set( &now_tm );

	printf( "RTC got new time information\r\n" );
}
