#include	"AFE_NXP.h"
#include	"r01lib.h"

/* NAFE13388 class ******************************************/

NAFE13388::NAFE13388( SPI& spi ) : SPI_for_AFE( spi ), enabled_channels( 0 )
{
}

NAFE13388::~NAFE13388()
{
}

void NAFE13388::begin( void )
{
	DigitalOut	ADC_nRESET( D6, 1 );
	DigitalOut	ADC_SYN(    D5, 1 );

	DigitalIn	ADC_nDRDY( D3 );
	DigitalIn	ADC_nINT(  D2 );

	reset();
	boot();	
}

void NAFE13388::boot( void )
{
	write_r16( 0x0010 ); 
	write_r16( 0x002A, 0x0000 );
	write_r16( 0x002B, 0x0000 );
	write_r16( 0x002C, 0x0000 );
	write_r16( 0x002F, 0x0000 );
	write_r16( 0x0029, 0x0000 );
	wait( 0.001 );
	write_r16( 0x0030, 0x0010 );
	wait( 0.001 );
}

void NAFE13388::reset( void )
{
	write_r16( 0x0014 ); 
	wait( 0.001 );
}

void NAFE13388::logical_ch_config( int ch, uint16_t cc0, uint16_t cc1, uint16_t cc2, uint16_t cc3 )
{	
	constexpr double	pga_gain[]	= { 0.2, 0.4, 0.8, 1, 2, 4, 8, 16 };
	
	write_r16( ch );
	
	write_r16( 0x0020, cc0 );
	write_r16( 0x0021, cc1 );
	write_r16( 0x0022, cc2 );
	write_r16( 0x0023, cc3 );
	
	uint16_t	mask	= 1;
	uint16_t	bits	= read_r16( 0x0024 ) | (mask << ch);
	enabled_channels	= 0;
	
	for ( int i = 0; i < 16; i++ ) {
		if ( bits & (mask << i) )
			enabled_channels++;
	}
	
	write_r16( 0x0024, bits );
	
	if ( cc0 & 0x0010 )
		coeff_uV[ ch ]	= ((10.0 / (double)(1L << 24)) / pga_gain[ (cc0 >> 5) & 0x7 ]) * 1e6;
	else
		coeff_uV[ ch ]	= (4.0 / (double)(1L << 24)) * 1e6;
}

double NAFE13388::read( int ch, float delay, bool raw )
{
	write_r16( ch );
	write_r16( 0x2000 );
	wait( delay );
	
	return read( ch, raw );
};

void NAFE13388::start( int ch )
{
	write_r16( ch );
	write_r16( 0x2000 );
}

double NAFE13388::read( int ch, bool raw )
{
	if ( raw )
		return read_r24( 0x2040 + ch );
	else
		return read_r24( 0x2040 + ch ) * coeff_uV[ ch ];
}

//double	NAFE13388::coeff_uV[ 16 ];
