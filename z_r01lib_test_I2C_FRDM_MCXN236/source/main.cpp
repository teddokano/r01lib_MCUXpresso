/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"

DigitalOut	r( RED,   1 );
DigitalOut	g( GREEN, 1 );
DigitalOut	b( BLUE,  1 );

int main( void )
{
	printf( "Hello, world!\r\n" );

	while ( true )
	{
		printf( "*\r\n" );
		r	= 0;
		g	= 1;
		b	= 1;
		wait( 0.5 );
		r	= 1;
		g	= 0;
		b	= 1;
		wait( 0.5 );
		r	= 1;
		g	= 1;
		b	= 0;
		wait( 0.5 );
	}
}
