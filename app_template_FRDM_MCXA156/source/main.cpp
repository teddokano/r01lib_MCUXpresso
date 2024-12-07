/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"

int main( void )
{
	printf( "Hello, world!\r\n" );

	DigitalOut	led( GREEN );

	led	= true;

	while ( true )
	{
		led	= !led;
		wait( 0.1 );
	}
}
