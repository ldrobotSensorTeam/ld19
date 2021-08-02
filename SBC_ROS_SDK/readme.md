## LOGIN 
```sh
sudo chmod 777 /dev/ttyS0

```
## COMPILE

```sh
cd sdk_toflidar_raspberry_ros
catkin_make

```

## RUN

```sh
source devel/setup.bash
roslaunch ldlidar ld06.launch
rosrun rviz rviz

```
## or RUN
```sh
bash run.sh

```

## TEST

Code in ubuntun16.04 It is tested under the version of kinetic and visualized with rviz.
