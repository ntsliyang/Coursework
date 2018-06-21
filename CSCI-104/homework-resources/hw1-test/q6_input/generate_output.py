import os

for i in xrange(1,11):
	infile  = "input" + str(i) +".txt"
	os.system("touch ../q6_output/output" + str(i) + ".txt")
	output = "../q6_output/output" + str(i) + ".txt"

	
	os.system("../hw1q6 " + infile + " > " + output)
	