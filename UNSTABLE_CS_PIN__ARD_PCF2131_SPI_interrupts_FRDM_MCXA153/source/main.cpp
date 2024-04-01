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

InterruptIn	intA( D8 );
InterruptIn	intB( D9 );

bool int_flagA	= false;
bool int_flagB	= false;

void pin_int_callbackA() {
  int_flagA	= true;
}

void pin_int_callbackB() {
  int_flagB	= true;
}

void	int_cause_monitor( uint8_t* status );
void	set_time( void );

int main(void)
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

	rtc.int_clear();
	intA.fall( pin_int_callbackA );
	intB.fall( pin_int_callbackB );

	rtc.timestamp( 1, PCF2131_base::LAST, 1 );
	rtc.timestamp( 2, PCF2131_base::LAST, 1 );
	rtc.timestamp( 3, PCF2131_base::LAST, 1 );
	rtc.timestamp( 4, PCF2131_base::LAST, 1 );

	rtc.periodic_interrupt_enable( PCF2131_base::EVERY_SECOND );
	rtc.alarm(PCF2131_base::SECOND, 37, 1);

	while ( true )
	{
		if ( int_flagA || int_flagB )
		{
			if ( int_flagA )
			{
				int_flagA	= false;
				printf( "[INT-A] " );
			}
			if ( int_flagB )
			{
				int_flagB	= false;
				printf( "[INT-B] " );
			}

			uint8_t status[3];
			rtc.int_clear(status);
			int_cause_monitor(status);
		}
	}
}

void int_cause_monitor( uint8_t* status )
{
	printf( "status:" );

	for (int i = 0; i < 3; i++)
		printf( " %02X", status[i] );

	printf( ", " );

	if ( status[0] & 0x80 )
	{
		time_t current_time = rtc.time(NULL);
		printf( "INT:every min/sec, time:%lu %s", (unsigned long)current_time, ctime( &current_time ) );
	}
	if ( status[0] & 0x40 )
	{
		printf( "INT:watchdog" );
	}
	if ( status[0] & 0x10 )
	{
		printf( "INT:alarm " );
		printf( "########## ALARM ########## \r\n" );
	}
	if ( status[1] & 0x08 )
	{
		printf( "INT:battery switch over" );
	}
	if ( status[1] & 0x04 )
	{
		printf( "INT:battery low" );
	}
	if ( status[2] & 0xF0 )
	{
		for ( int i = 0; i < 4; i++ )
			if ( status[2] & (0x80 >> i) )
				printf( "INT:timestamp%d\r\n", i + 1 );

		for ( int i = 0; i < 4; i++ )
		{
			time_t ts = rtc.timestamp(i + 1);
			printf( "  TIMESTAMP%d: %s", i + 1, ctime( &ts ) );
		}
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
