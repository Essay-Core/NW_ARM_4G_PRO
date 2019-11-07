#!/bin/bash

echo running in shell test
hciconfig -a

n=1
channel=$2
rfcomm_x=$1

while (( $n<=3 ))
do
	#sudo sdptool add --channel=22 SP	
	sudo sdptool add --channel=$channel SP
	
	#sudo rfcomm listen /dev/rfcomm0 22
	sudo rfcomm listen /dev/rfcomm$rfcomm_x $channel
	
	#sudo rfcomm release /dev/rfcomm$rfcomm_x

	let n+=1;
	#let rfcomm_x+=1;
	
	echo channel:$channel
	echo rfcomm_x:rfcomm$rfcomm_x

done

