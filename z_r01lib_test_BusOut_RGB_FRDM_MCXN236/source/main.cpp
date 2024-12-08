/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"

//BusOut	leds( RED, GREEN, BLUE );
//BusOut	leds( D0, D1, D2, D3, D4, D5, D6, D7 );

BusIn	leds( D0, D1, D2, D3, D4, D5, D6, D7 );


int main( void )
{

	while ( true )
	{
		printf( "0x%02X\r\n", (uint8_t)leds );
		wait( 0.5 );
	}
}
