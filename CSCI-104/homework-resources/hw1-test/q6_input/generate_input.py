import random 

print 10000
random.seed(a=None)


for i in xrange(0,10000):
	length = random.randint(5,20)
	string = ""
	for j in xrange(0, length):
		x = random.randint(ord('a'), ord('z'))
		string += chr(x)
	print string
	