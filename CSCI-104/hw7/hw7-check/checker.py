import os
import subprocess

def compile_gnu(args):
	# compile
	prefix = ['g++', '-g', '-std=c++11', '-Wall']
	prefix += ['-Wvla', '-Wshadow', '-Wunreachable-code',
						 '-Wconversion']
	args = prefix + args
	print('$ ' + ' '.join(args))

	proc = subprocess.Popen(args, stderr=subprocess.PIPE)
	_, stderr = proc.communicate()
	stderr = stderr.decode('utf8')
	if proc.returncode != 0:
		print('Did not compile')
		print(stderr)
		return False
	elif stderr != '':
		print('You need to remove these warnings:')
		print(stderr)
		return False
	else:
		print('Compiled OK')
		return True


def compile_104(file_list, exe_name):
	compile_command = file_list + ['-o', exe_name]
	compiled = compile_gnu(compile_command)
	if os.path.exists(exe_name):
		os.system('rm ' + exe_name)
	return compiled


def run_make(target, target_file = ''):
	if target_file == '':
		target_file = target
	print('Attempting to run your Makefile using \'make ' + target + '\'')
	os.system('make ' + target)
	if os.path.exists(target_file):
		os.system('rm ' + target_file)
		result = 'found'
		compiled = True
	else:
		result = 'not found'
		compiled = False
	print(target_file + ' ' + result + ' after running \'make ' + target + '\'.')
	return compiled


def check_if_passed():
	compiled = True
	result = compile_104(['hw7_node_checker.cpp'], 'hw7_node_checker')
	compiled &= result
	if not result:
		print('Failed: node interface check')
	print('----------------------------------------\n')

	result = compile_104(['hw7_bst_checker.cpp'], 'hw7_bst_checker')
	compiled &= result
	if not result:
		print('Failed: bst interface check')
	print('----------------------------------------\n')

	result = compile_104(['hw7_iterator_checker.cpp'], 'hw7_iterator_checker')
	compiled &= result
	if not result:
		print('Failed: bst iterator interface check')
	print('----------------------------------------\n')

	result = compile_104(['hw7_rotate_checker.cpp'], 'hw7_rotate_checker')
	compiled &= result
	if not result:
		print('Failed: rotateBST interface check')
	print('----------------------------------------\n')

	original = '../bst.h'
	if os.path.exists(original):
		temp = 'temp_bst.h'
		provided = 'hw7_provided_bst.h'
		os.system('mv '+ original + ' ' + temp)
		os.system('mv '+ provided + ' ' + original)
		result = compile_104(['hw7_rotate_checker.cpp'], 'hw7_rotate_checker')
		compiled &= result
		if not result:
			print('Failed: found public/protected data/function not in skeleton code')
		os.system('mv '+ original + ' ' + provided)
		os.system('mv '+ temp + ' ' + original)
	else:
		print('Failed: cannot find ../bst.h')
	print('----------------------------------------\n')

	cwd = os.getcwd()
	os.chdir('..')
	compiled &= run_make('hypercube')
	os.chdir(cwd)
	print('----------------------------------------\n')

	return compiled

if check_if_passed():
	print('Passed all compilation checks')
else:
	print('Failed some checks')