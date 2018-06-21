#!/bin/bash

YELLOW='\e[38;5;226m'
NORMAL='\e[0m'
RED='\e[38;5;196m'
BLUE='\e[38;5;033m'
GREEN='\e[38;5;046m'

failed() {
	echo ${RED}"Failed: " $1${NORMAL}
	exit
}

output() {
	cnt=0
	for i in $*
	do
		if ((cnt==0))
		then
			echo -n -e $i
		fi
		if ((cnt==4))
		then
			echo -n -e ${RED} $i
		fi
		cnt=$((cnt+1))
	done
	echo -e ${NORMAL}
}

runtest() {
	echo -e ${YELLOW}"========== Running Test: "$* "==========" ${NORMAL}
	./cache-test $*
	gprof ./cache-test > output.log
	LEFT="$(cat output.log | grep -n "leftRotate" -m 1)"
	RIGHT="$(cat output.log | grep -n "rightRotate" -m 1)"
	DELETE="$(cat output.log | grep -n "deleteMinLeaf" -m 1)"
	echo -n -e ${BLUE}"leftRotate count detected at Line "
	output ${LEFT}
	echo -n -e ${BLUE}"rightRotate count detected at Line "
	output ${RIGHT}
	echo -n -e ${BLUE}"deleteMinLeaf count detected at Line "
	output ${DELETE}
}

g++ -std=c++11 -pg -Wall -Wextra cache-main.cpp -o cache-test || failed "Compile error."
runtest ./data/hamlet.txt 1000
runtest ./data/hamlet.txt 500
runtest ./data/hamlet.txt 100
runtest ./data/viptest.txt 1000
runtest ./data/viptest.txt 500
runtest ./data/viptest.txt 100