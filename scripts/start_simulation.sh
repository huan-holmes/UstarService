#! /bin/bash
source /opt/ros/kinetic/setup.sh
source ~/UstarService/devel/setup.bash
move=0

gnome-terminal -x bash -c "roslaunch simulator stage.launch"
if [ $? -eq 0 ]; then
	sleep 2
	gnome-terminal --tab -e 'bash -c "roslaunch simulator move.launch"' 
	move=1
else
	echo "stage start falied"
fi
if [ $move -eq 1 ]; then
	sleep 2
	gnome-terminal --tab -e 'bash -c "rosrun rqt_reconfigure rqt_reconfigure"'
else
	echo "move start failed"
fi
