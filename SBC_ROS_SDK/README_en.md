# SBC_ROS_SDK Direction Of Use(LD19)

---

> Directory `SBC_ROS_SDK` contains the SDK that is suitable for the platform with native serial peripheral, such as Raspberry Pi, whose GPIOs can  be used to power LD19 and recieve data directly. That's the reason why this version is named "SBC(Single Board Computer)".
>

## General Description

The contents of directory SBC_ROS_SDK` are listed below:

```
/doc/
/rviz/
/src/
/README_cn.md
/README_en.md
```

+ `src` contains the source code of SDK
+ `doc` contains the [Raspbian User manual](./doc/LDRobot_LD19_Raspbian_User_manual_V2.3.pdf) in English (LD19 shares the same documents with LD06, pls be awarded)
+ `rviz` contains the file which is used to configure the visualization of radar data

This SDK has been tested on Raspberry Pi 3B+ with Kinetic in Raspbian 9 and Noetic in Ubuntu 20.04 Server.

## Usage

### Hardware Preparation

> LDRobot LD19 radar, wires

Link LD19 to the upper computer according to the diagram below:

![schematic](../pic/en_conne.png)

LD19 adopt ZH1.5T-4P 1.5mm connector. The PWM signal, namely the second pin, need not to be attached to certain GPIO if you're not going to control the revolving speed.

Attatch `GND` and `P5V` to corresponding Pins on the SBC, `TX` to the UART RX GPIO of the SBC, here takes Raspberry Pi 3B+ for an example:

 ![rp3b+io](../pic/树莓派gpio.png)

> 1(Tx)------------->10(RXD)
>
> 2(PWM)---------floating
>
> 3(GND)--------->6(GND)
>
> 4(P5V)---------->(5V Power)

### Software Preparation

The SDK requires installed ROS, but you may encounter some problems if you manually install ROS on SBC. Advice is that you can try Ubuntu Mate or download system imager with compiled ROS. You can refer to the Manual for detailed direction of installation.

Raspberry Pi's Serial peripheral needs to be enabled, otherwise there won't be corresponding tty device in directory `/dev`, refer to [chapter 4 of Manual](./doc/LDRobot_LD19_Raspbian_User_manual_V2.3.pdf) for details.

The `wiringPi` and `udev` libraries mentioned in the Manual are unnecessary. They could be ignored.

The whole process could be conducted with a normal Linux user's account, however, the **authority of using the Serial device is a necessity**.



So far, all the preparation is done.

### Procedure Of Use

1. Copy folder SBC_ROS_SDK/src` and `SBC_ROS_SDK/rviz` to certain empty directory A.
2. Open a terminal in A, run `catkin_make` to compile the SDK.
3. If the target has been built, run `source ./devel/setup.bash` to add some environmental variables.
4. Call `roslaunch ldlidar ld19.alaunch` at any directory to run the SDK, if there's a `Successfully` in the end of output, the LD19 has been found.
5. Keep the terminal open, the SDK should be kept running when other ROS packets 

**Notice**

Every time you open a terminal, step 3 should be performed before step 4. There's a way to simplify it, add `source ./devel/setup.bash` to `~/.bashrc`, then you can ignore step 3 every time start a new terminal.

If the SDK can't find the radar, it will print `open error`, but it won't exit.

You can make use of `nohup` to let the SDK runs in the background.

## Example

An example of using rviz to visualize real time data from LD19 is in the [chapter 5 of User Manual](./doc/LDRobot_LD19_Raspbian_User_manual_V2.3.pdf).

