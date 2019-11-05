#!/bin/bash

echo running in shell test
hciconfig -a

n=1
channel=22
rfcomm_x=1
pid=0
while (( $n<=2 ))
do
	#sudo sdptool add --channel=22 SP	
	sudo sdptool add --channel=$channel SP
	
	#sudo rfcomm listen /dev/rfcomm0 22
	sudo rfcomm listen /dev/rfcomm$rfcomm_x $channel
	
	
	sudo rfcomm release /dev/rfcomm$rfcomm_x

	let n+=1;
#	let channel+=1;
#	let rfcomm_x+=1;

	echo channel:$channel
	echo rfcomm_x:rfcomm$rfcomm_x
#	sudo ./kill_pid_test.sh

done

