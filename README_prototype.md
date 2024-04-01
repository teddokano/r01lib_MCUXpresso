# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## MIPI I3C bus demonstration using P3T1755 temperature sensor on FRDM-MCXN947/MCXA153

- This example code demonstrates MIPI I3C bus operation with P3T1755 temperature sensor and MCX microcontroller.  
<br />
- MIPI I3C bus is a serial bus that performs high datarate data transfer with two wire signals. 
The prptocol is similar to I²C but there are several extended features like Dynamic Address Assignment (DAA), In-band interrupt (IBI) etc. 
This code shows those signal characterristics. 
The MIPI I3C bus is introduced in a NXP document: [SYSTEM MANAGEMENT I²C, I3C AND SPI SELECTOR GUIDE](https://www.nxp.com/docs/en/product-selector-guide/I2CSELECTORBROC.pdf). 
<br />
- The P3T1755 is a temperature-to-digital converter from -40 °C to +125 °C range. It uses an on-chip band gap temperature sensor and A-to-D conversion technique with
an overtemperature detection. The device contains a number of configuration and data registers to store the device settings, such as device operation mode, and a temperature register (Temp) to store the digital temp reading that can be communicated by a controller via the 2-wire serial I3C (up to 12.5 MHz) and I2C (up to 3.4 MHz) interface. 
For the details of the P3T1755, please refer to its [datasheet](https://www.nxp.com/docs/en/data-sheet/P3T1755.pdf)
<br />
- "r01lib" is a MCU abstraction library to write code easy and presenting operation of serial buses and GPIO pins. The APIs are inspired by Arm Mbed SDK. This library is distributed as a part of this example code. 
<br />
- The image below shows  block diagram.

*Description should provide a clear explanation of what the code is for, and provide links to any related documentation. If documentation is included in the Github repo then its location should be mentioned here, along with the name of documentation file(s). If the code is a snippet/general software, then a sufficient description must be provided for a developer to fully understand the example, either in this readme or in another document in the repo.*

*If the code is an App SW pack then a link to the software summary page (SSP) on nxp.com must be provided.*

*If the code is a demo, then a link to any related videos on nxp.com.Youtube, and/or other related pages must be provided.*

*For training content you must reference the class training number (e.g. AMP-ENT-T4545), if available. You should also refer the reader to the training workbook and other materials from the class here.*

*Ask yourself - if you were finding this code for the first time, is there enough information to make it useful? Think **QUALITY**.*


#### Boards: FRDM-MCXN947, FRDM-MCXA153
#### Categories: Sensor
#### Peripherals: I3C
#### Toolchains: MCUXpresso IDE

## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)



## 1. Software<a name="step1"></a>
- One of two from below, depends on your hardware
  - MCUXpresso SDK v2.14.0 for FRDM-MCXN947 (https://mcuxpresso.nxp.com/en/select)
  - MCUXpresso SDK v2.14.2 for FRDM-MCXA153 (https://mcuxpresso.nxp.com/en/select)
- MCUXpresso IDE v11.9.0

## 2. Hardware<a name="step2"></a>
- One of two from below
  - [FRDM-MCXN947 MCU board](https://www.nxp.com/design/design-center/development-boards/general-purpose-mcus/frdm-development-board-for-mcx-n94-n54-mcus:FRDM-MCXN947)
  - [FRDM-MCXA153 MCU board](https://www.nxp.com/design/design-center/development-boards/general-purpose-mcus/frdm-development-board-for-mcx-a14x-a15x-mcus:FRDM-MCXA153)
- Personal Computer
- Type-C USB cable
- (option) [P3T1755DP Arduino® Shield Evaluation Board](https://www.nxp.com/design/design-center/development-boards/analog-toolbox/arduino-shields-solutions/p3t1755dp-arduino-shield-evaluation-board:P3T1755DP-ARD)

## 3. Setup<a name="step3"></a>

### 3.1 Step 1: Download and Install required Software(s)
- Install MCUXpresso IDE 11.9.0
- Download and Install one of following
  - MCXUpresso SDK 2.14.0 for FRDM-MCXN947
  - Download and Install MCXUpresso SDK 2.14.2 for FRDM-MCXA153

### 3.2 Step 2: Download or clone the APP-CODE-HUB/dm-nmh1000-magnetic-switch-example
- There are 2 options to get the example code : import or clone

#### 3.2.1 Option 1 : Download the zip file and import it from file system
- Launch MCUXpresso IDE and make new workspace
- Download the zip file and store it on user's PC
- Go to "Quickstart Panel" and click on "Import Project(s) from file system",

#### 3.2.2 Option2 : Import into IDE by clone
- Launch MCUXpresso IDE and make new workspace
- Close welcome message and find "Project Explorer" panel in left-top pane. Click on "Import projects..."
- Choose "Git" > "Projects from Git"
- Choose "Clone URL" and put "https://github.com/nxpnxpnxpnxpnxpnxpnxp/nnnnnnnnnnn.git"
- Clone "main" branch
- Choose clone target directory. This will be a new workspace
- Goto cloned workspace

### 3.3 Conect hardware
- Connect an FRDM-MCXN947 or an FRDM-MCXA153 board to PC via USB cable

### 3.4 Step 3: Build and run
- Select a project in "Project Explorer" panel in left top pane (The "r01lib" project is just a library this code canot be executed alone)
- Click "Debug" icon in "Quickstart Panel" or "Start debugging project" icon (blue bug icon) in icon-toolbar
- The IDE will find the MCU board and resume the program at "main()" function started
- Press "Resume" button in to continue from there

## 4. Results<a name="step4"></a>
- Message and measured temperature value on terminal panel (middle-bottom pane) in MCUXpresso IDE
- Touch on P3T1755 to heat up by funger temperature or use hair-dryer, cooling-splay to find the value changes
- In IBI enabled example, the IBI event will be shown in the terminal panel. The default setting to trigger the IBI is 2 degree-C higher temperature than program started (T_HIGH register set to T_program_start + 2 degC). IBI will be triggered again when the temperature down to T_start + 1degC. 
- Probe on I3C signals and confirm the waveform. In IBI enabled example, D2 pin outputs trigger signal (falling edge) at IBI event for oscilloscope. 

## 5. Support<a name="step5"></a>
- Reach out to NXP Sensors Community page for more support - [NXP Community](https://)
- Learn more about P3T1755: I3C, I2C-bus interface, 0.5 °C accuracy, digital temperature sensor, refer to - [P3T1755 Product summary page](https://www.nxp.com/products/sensors/i3c-ic-digital-temp-sensors/i3c-ic-bus-0-5-c-accurate-digital-temperature-sensor:P3T1755DP)
- "SYSTEM MANAGEMENT I²C, I3C AND SPI SELECTOR GUIDE" including introduction of I3C bus, refer to - [Sensors Development Ecosystem](https://www.nxp.com/design/design-center/software/sensor-toolbox:SENSOR-TOOLBOXX)



#### Project Metadata
<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN947-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN947+in%3Areadme&type=Repositories) [![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXA153-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXA153+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-SENSOR-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+sensor+in%3Areadme&type=Repositories) [![Category badge](https://img.shields.io/badge/Category-LOW%20POWER-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+low_power+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-I2C-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+i2c+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-SENSOR-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+sensor+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-UART-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+uart+in%3Areadme&type=Repositories)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://github.com/search?q=org%3Anxp-appcodehub+mcux+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code Hub        | January 17<sup>th</sup> 2024 |

