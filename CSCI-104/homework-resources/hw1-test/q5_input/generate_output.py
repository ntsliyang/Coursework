import os

f = open("input.txt", "r")
for i in xrange(1,11):
	os.system("touch ../q5_output/output" + str(i) + ".txt")
	output = "../q5_output/output" + str(i) + ".txt"
	string = f.readline().strip()
	print string

	os.system("../../hw1-solution/barry " + string + " > " + output)
	