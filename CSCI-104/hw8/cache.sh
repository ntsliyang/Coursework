#!/bin/bash
failed() {
	echo "Failed: " $1
	exit
}

runtest() {
	./main $*
	gprof ./main > output.log
	cat output.log | grep -n "leftRotate" -m 1
	cat output.log | grep -n "rightRotate" -m 1
	cat output.log | grep -n "deleteMinLeaf" -m 1
}

g++ -std=c++11 -pg -Wall -Wextra main.cpp -o main || failed "Compile error."
cp ./main ./tests/ || failed "Permission denied"
pushd ./tests/
runtest ./data/large.txt 1000
popd