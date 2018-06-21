import os, subprocess

testCount = 4

inputFilename = 'cube/permitted'
solutionFilename = 'cube/solution'
outputFilename = 'cube/output'
exeName = '../hypercube'

def clean_up_lines(lines):
	lines = [x.strip() for x in lines]
	lines = [x for x in lines if x != '']
	return lines

def compare_file(source, compare):
	if not os.path.isfile(source):
		print('\tERROR: Source ' + source + ' does not exist')
		return False
	if not os.path.isfile(compare):
		print('\tERROR: Output ' + compare + ' does not exist')
		return False
	with open(source) as sfile, open(compare) as cfile:
		slines = clean_up_lines(sfile.readlines())
		clines = clean_up_lines(cfile.readlines())
		passed = True
		if len(slines) < len(clines):
			print('\tWARNING: Fewer lines in source file than in cmp file.')
		elif len(slines) > len(clines):
			print('\tWARNING: Fewer lines in comp file than in source file.')

		for i in range(len(slines)):
			if i >= len(clines):
				print('\tMISSING: ' + slines[i])
				passed = False
			else:
				if slines[i] == clines[i]:
					print('\tFOUND: ' + slines[i])
				else:
					print('\tEXPECTED: ' + slines[i])
					print('\tACTUAL: ' + clines[i])
					passed = False

		for i in range(len(slines), len(clines)):
			print('\tEXTRA: ' + clines[i])
			passed = False
	return passed

passedAll = True

with open('cube/start.txt') as startFile:
	startNodes = startFile.readlines()
	startNodes = [x.strip() for x in startNodes]
	for i in range(1, testCount + 1):
		if i > len(startNodes) or startNodes[i-1] == '':
			print('WARNING: no start node found for test ' + str(i))
		else:
			tInput = inputFilename + str(i) + '.txt'
			tOutput = outputFilename + str(i) + '.txt'
			tSolution = solutionFilename + str(i) + '.txt'
			args = [exeName, startNodes[i-1], tInput]
			print(' '.join(args))
			proc = subprocess.Popen(args, stdout=subprocess.PIPE)
			try:
				outs, _ = proc.communicate()
				with open(tOutput, 'w') as outputFile:
					outputFile.write(outs.decode('ascii'))
			except Exception as e:
				print(e)

			passed = compare_file(tSolution, tOutput)
			passedAll &= passed
			print('Test {} {}\n'.format(str(i), 'passed' if passed else 'failed'))

if passedAll:
	print('Passed all tests')
else:
	print('Failed some tests')