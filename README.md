# r01lib_MCUXpresso

## What is this?

The `r01lib_MCUXpresso` is a sample/test projects for [`r01lib`](https://github.com/teddokano/r01lib).  
`r01lib` is a source code package for class libraries to abstract MCUs and peripheral devices.
From application code, GPIO, I²C, I3C, SPI, Pin-interrupt and timer (ticker) can be accessed with simple APIs.
For the detailed information, refer to document in [docs/r01lib_introduction.pdf](https://github.com/teddokano/r01lib_MCUXpresso/blob/main/docs/r01lib_introduction.pdf).

The `r01lib` is a submodule of this repository.  
In this `r01lib_MCUXpresso` repository there are several projects in same workspace and some of those project named as `_r01lib_*`. 
Those are library projects which cannot run standalone but those are linked from application projects.  

All projects can be imported/build/execute on MCUXpresso IDE. 

### Supported MCUs

Currently, 4 types of MCU boards are supported. 
- FRDM-MCXN947
- FRDM-MCXN236
- FRDM-MCXA156
- FRDM-MCXA153

![FRDM boards](docs/img/frdm_boards.jpg)
*NXP FRDM boards: N947, N236, A156 and A153 (from left to right)*

### Samples
The code can be written like next sample.  
The API are in Arm-Mbed style.  
`#include	"r01lib.h"` includes `"stdio.h"` to enable calling `printf()` function. 

```cpp
// Sample code in app_template_FRDM_MCX* project

#include	"r01lib.h"

DigitalOut	led( BLUE );

int main( void )
{
    printf( "Hello, world!\r\n" );

    led	= true;

    while ( true )
    {
        led	= !led;
        wait( 0.5 );
    }
}
```

Since the projects are written in C++, `std::cout` can be used also.  
However, this cannot be used on FRDM-MCXA153 because it flash memory size limication.  

```cpp
// Sample code in z_r01lib_demo_Hello_world_FRDM_MCX* project

#include	"r01lib.h"

int main( void )
{
    printf( "Hello, world! (in C style)\r\n" );
    std::cout << "Hello, world! (in C++ style)" << std::endl;

    return 0;
}
```

## References

### API document
API documents of the `r01lib` can be found in `docs/r01lib_docs/` folder. 

