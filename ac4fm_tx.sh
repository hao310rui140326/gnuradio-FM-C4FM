#!/bin/bash


#make open

echo "0" > cmd
echo "0" >> cmd

cnt=1;
lcnt=1;
working=0;

python2  ./s.py  &

while(($cnt !=0))
##for i in {1..2}
do
	sleep 1s

	while read line
	do
		##sleep 1s
		if [ $lcnt -eq 1 ]
	       	then
			start_flag=$line
			##echo "start_flag is $start_flag"
		elif [ $lcnt -eq 2 ]
	       	then
			freq=$line
		elif [ $lcnt -eq 3 ]
	       	then
			tdb=$line
			##echo "freq is $freq"			
			##if  [ $start_flag -eq 1 ] && [ $working -eq 0 ]; then	
			if  [ $start_flag -eq 1 ] 
		       	then
				if [ $working -eq 0 ]
				then
					working=1
					cp  -rf ./rx_data  ./data
					./c4fm_tx_db.py  $freq  $tdb  &
					echo "c4fm_tx start !! start_flag is $start_flag ; freq is $freq !!! tdb is $tdb !!! "
				fi
			elif   [ $start_flag -eq 0 ]  
		       	then
				if [ $working -eq 1 ]
				then
					working=0
					killall python3
					echo "c4fm_tx stop  !! start_flag is $start_flag ; freq is $freq !!! tdb is $tdb !!! "		
				fi
			fi
		fi
		let "lcnt++"
	done < ./cmd
	lcnt=1
        ##echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! working is $working  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	let "cnt++"
done


