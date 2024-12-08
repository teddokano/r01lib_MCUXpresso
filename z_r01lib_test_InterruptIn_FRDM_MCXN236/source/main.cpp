/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"
#include "fsl_debug_console.h"
#if defined(FSL_FEATURE_SOC_PORT_COUNT) && (FSL_FEATURE_SOC_PORT_COUNT)
#include "fsl_port.h"
#endif
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_clock.h"
#include "fsl_reset.h"
#include <stdbool.h>

#define		BOARD_LED_GPIO	GPIO0

bool		flag_sw;
bool		flag_pin;

InterruptIn	sw( SW2 );
InterruptIn	pin( D4 );
DigitalOut	out( D0 );

BusIn	bi0( P0_25, P0_26, P0_27, P0_28, P0_29, P0_24, P0_15, P0_14 );
BusIn	bi1( P0_24, P0_15, P0_14, P0_23,  P0_4, P0_19,  P0_5, P0_23 );
BusIn	bi_test( D1, D2, D3, D4, D5, D6, D7 );

void callback_sw( void )
{
	flag_sw	= true;
}

void callback_pin( void )
{
	flag_pin	= true;
}

int main( void )
{
	sw.rise(  callback_sw  );
	pin.fall( callback_pin );

	while ( true )
	{
		if ( flag_sw )
		{
			flag_sw	= false;
			PRINTF( "!!! Switch event detected\r\n" );
		}
		if ( flag_pin )
		{
			flag_pin	= false;
			PRINTF( "!!! Pin event detected\r\n" );
		}

		out	= !out;

		PRINTF( "%d %d\r\n", sw & 1, pin & 1 );

		//printf( "PDIR: 0x%08X\r\n", (uint32_t)(((GPIO_Type *)0x40096000)->PDIR) );
		printf( "bi_test: 0x%02X\r\n", (unsigned char)bi_test );
		wait( 0.1 );
	}
}
