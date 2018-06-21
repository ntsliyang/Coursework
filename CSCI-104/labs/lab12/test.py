import os

input_count = 4
input_name = 'map'
output_name = 'output'
solution_name = 'path'
file_suffix = '.txt'
exe_name = 'gas'

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

for i in range(input_count):
	input_i = input_name + str(i + 1) + file_suffix
	output_i = output_name + str(i + 1) + file_suffix
	solution_i = solution_name + str(i + 1) + file_suffix
	os.system('./gas ' + input_i + ' ' + output_i)
	print('compare ' + solution_i + ' ' + output_i)
	passed = compare_file(solution_i, output_i)
	print('test ' + str(i + 1) + (' passed' if passed else ' failed'))