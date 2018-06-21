num_primes = 1000

arr = [2, 3, 5, 7]
count = 7

while len(arr) <> num_primes:
	prime = 1
	for i in arr:
		if count % i == 0:
			prime = 0
	if prime:
		arr.append(count)
	else:
		count = count + 1

for i in arr:
	print i,