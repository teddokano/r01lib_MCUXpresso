# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## P3T1755: I3C temperature sensor demo

- This example code demonstrates MIPI I3C bus operation with P3T1755 temperature sensor and MCX microcontroller.  
<br />
- MIPI I3C bus is a serial bus that performs high datarate data transfer with two wire signals. 
The prptocol is similar to I²C but there are several extended features like Dynamic Address Assignment (DAA), In-band interrupt (IBI) etc.  
  - This code shows those features and signal characterristics.  
  - The MIPI I3C bus is introduced in a NXP document: [SYSTEM MANAGEMENT I²C, I3C AND SPI SELECTOR GUIDE](https://www.nxp.com/docs/en/product-selector-guide/I2CSELECTORBROC.pdf). 
<br />
- As a target device of I3C, The P3T1755 is used. 
<br />
- The P3T1755 is a temperature-to-digital converter from -40 °C to +125 °C range. It uses an on-chip band gap temperature sensor and A-to-D conversion technique with
an overtemperature detection. The device contains a number of configuration and data registers to store the device settings, such as device operation mode, and a temperature register (Temp) to store the digital temp reading that can be communicated by a controller via the 2-wire serial I3C (up to 12.5 MHz) and I2C (up to 3.4 MHz) interface. 
For the details of the P3T1755, please refer to its [datasheet](https://www.nxp.com/docs/en/data-sheet/P3T1755.pdf)
<br />
- An MCU abstraction library: "r01lib" is used. It's a library to write demo code easy with presenting operations of serial buses and GPIO pins with simple APIs. Those APIs are inspired by Arm Mbed SDK. This library is distributed as a part of this example code. 
<br />

![block](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/block.png)

**DEMO VIDEO LINK WILL BE HERE**
**DEMO VIDEO LINK WILL BE HERE**
**DEMO VIDEO LINK WILL BE HERE**

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
- Oscilloscope
- (option but not used on this demo) [P3T1755DP Arduino® Shield Evaluation Board](https://www.nxp.com/design/design-center/development-boards/analog-toolbox/arduino-shields-solutions/p3t1755dp-arduino-shield-evaluation-board:P3T1755DP-ARD)

## 3. Setup<a name="step3"></a>

### 3.1 Step 0: Conect hardware
- Connect an FRDM-MCXN947 or an FRDM-MCXA153 board to PC via USB cable
- (option) connect I3C signals to an oscilloscope
  - FRDM-MCXN947:SDA=J5-3, SCL=J5-4
  - FRDM-MCXA153:SDA=J20, SCL=J21)

### 3.2 Step 1: Download and Install required Software(s)
- Download and Install [MCUXpresso IDE 11.9.0](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE)
- Download and Install one of following
  - MCXUpresso SDK 2.14.0 for FRDM-MCXN947
  - MCXUpresso SDK 2.14.2 for FRDM-MCXA153

### 3.3 Step 2: Download or clone the APP-CODE-HUB/P3T1755_demo_on_FRDM_MCX_boards_vx.x.x
- There are 2 options to get the example code : import or clone

#### 3.3.1 Step 2 - Option 1 : Download the zip file and import it from file system
- Launch MCUXpresso IDE and make new workspace
- Download the zip file and store it on user's PC
- Go to "Quickstart Panel" and click on "Import Project(s) from file system"
![ide0](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide0.png)  
![ide1](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide1.png)  
![ide2](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide2.png)  
![ide3](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide3.png)  
![ide4](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide4.png)  
![ide5](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/ide5.png)  

#### 3.3.2 Step 2 - Option2 : Import into IDE by clone
**!!!!!!!! This step is shown with temtative Github URL. It should be replaced before launch !!!!!!!!!**  
**!!!!!!!! This step is shown with temtative Github URL. It should be replaced before launch !!!!!!!!!**  
**!!!!!!!! This step is shown with temtative Github URL. It should be replaced before launch !!!!!!!!!**  

- Launch MCUXpresso IDE and make new workspace
- Close welcome message and find "Project Explorer" panel in left-top pane. Click on "Import projects..."
- Choose "Git" > "Projects from Git"
- Choose "Clone URL" and put "https://github.com/nxpnxpnxpnxpnxpnxpnxp/nnnnnnnnnnn.git"
- Clone "main" branch
- Choose clone target directory. This will be a new workspace
- Goto cloned workspace
![clone0](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone0.png)  
![clone1](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone1.png)  
![clone2](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone2.png)  
![clone3](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone3.png)  
![clone4](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone4.png)  
![clone5](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone5.png)  
![clone6](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone6.png)  
![clone7](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone7.png)  
![clone8](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/clone8.png)  

### 3.4 Step 3: Build and run
- Select a project in "Project Explorer" panel in left top pane (The `_r01lib_*`" projects are libraries. Those code cannot be executed alone)
- Click "Debug" icon in "Quickstart Panel" or "Start debugging project" icon (blue bug icon) in icon-toolbar
- The IDE will find the MCU board and resume the program at "main()" function started
- Press "Resume" button in to continue from there
![run0](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/run0.png) 
![run1](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/run1.png) 
![run2](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/run2.png) 
![run3](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/run3.png) 
![run4](https://github.com/teddokano/additional_files/blob/main/r01projects-p3t1755/run4.png) 

## 4. Results<a name="step4"></a>
- Message and measured temperature value on terminal panel (middle-bottom pane) in MCUXpresso IDE
- Touch on P3T1755 to heat up by funger temperature or use hair-dryer, cooling-splay to find the value changes
- In IBI enabled example, the IBI event will be shown in the terminal panel. The default setting to trigger the IBI is 2 degree-C higher temperature than program started (T_HIGH register set to T_program_start + 2 degC). IBI will be triggered again when the temperature down to T_start + 1degC. 
- Probe on I3C signals and confirm the waveform. In IBI enabled example, D2 pin outputs trigger signal (falling edge) at IBI event for oscilloscope. 

## 5. FAQ<a name="step5"></a>
- None

## 6. Support<a name="step5"></a>
- Reach out to NXP Sensors Community page for more support - [NXP Community](https://community.nxp.com)
- Learn more about P3T1755: I3C, I2C-bus interface, 0.5 °C accuracy, digital temperature sensor, refer to - [P3T1755 Product summary page](https://www.nxp.com/products/sensors/i3c-ic-digital-temp-sensors/i3c-ic-bus-0-5-c-accurate-digital-temperature-sensor:P3T1755DP)
- "SYSTEM MANAGEMENT I²C, I3C AND SPI SELECTOR GUIDE" including introduction of I3C bus, refer to - [Sensors Development Ecosystem](https://www.nxp.com/docs/en/product-selector-guide/I2CSELECTORBROC.pdf)



#### Project Metadata
<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN947-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN947+in%3Areadme&type=Repositories) [![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXA153-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXA153+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-SENSOR-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+sensor+in%3Areadme&type=Repositories) [![Category badge](https://img.shields.io/badge/Category-LOW%20POWER-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+low_power+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-I3C-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+i3c+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-SENSOR-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+sensor+in%3Areadme&type=Repositories) [!

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
| 1.0     | Initial release on Application Code Hub        | Apr 17<sup>th</sup> 2024 |



[def]: pics/block.png
