/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"

DigitalOut	led( BLUE );

int main( void )
{
	led	= true;

	while ( true )
	{
		led	= !led;
		wait( 0.5 );
	}
}
