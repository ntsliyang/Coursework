import os
import subprocess

ERR_NONE = 0
ERR_WARNING = 1
ERR_ERROR = 2

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
		return ERR_ERROR
	elif stderr != '':
		print('You need to remove these warnings:')
		print(stderr)
		return ERR_WARNING
	else:
		print('Compiled OK')
		return ERR_NONE


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
		compiled = ERR_NONE
	else:
		result = 'not found'
		compiled = ERR_ERROR
	print(target_file + ' ' + result + ' after running \'make ' + target + '\'.')
	return compiled


def check_if_passed():
	splay_checker = 'hw8_splay_checker.cpp'
	cache_checker = 'hw8_cache_checker.cpp'
	provided_bst = 'hw8_provided_bst.h'
	provided_rotate = 'hw8_provided_rotateBST.h'
	provided_splay = 'hw8_provided_splayTree.h'
	original_bst = '../bst.h'
	original_rotate = '../rotateBST.h'
	original_splay = '../splayTree.h'
	splay_exe = 'hw8_splay_checker'
	cache_exe = 'hw8_cache_checker'
	temp_bst = 'temp_bst.h'
	temp_rotate = 'temp_rotate.h'
	temp_splay = 'temp_splay.h'

	compiled = ERR_NONE
	result = compile_104([splay_checker], splay_exe)
	compiled |= result
	if result != ERR_NONE:
		print('Failed: splay tree interface check')
	print('----------------------------------------\n')

	result = compile_104([cache_checker], cache_exe)
	compiled |= result
	if result != ERR_NONE:
		print('Failed: cache interface check')
	print('----------------------------------------\n')

	original_found = True
	if not os.path.exists(original_bst):
		original_found = False
		print('Failed: cannot find ' + original_bst)
	if not os.path.exists(original_rotate):
		original_found = False
		print('Failed: cannot find ' + original_rotate)
	if original_found:
		os.system('mv '+ original_bst + ' ' + temp_bst)
		os.system('mv '+ provided_bst + ' ' + original_bst)
		os.system('mv '+ original_rotate + ' ' + temp_rotate)
		os.system('mv '+ provided_rotate + ' ' + original_rotate)
		result = compile_104([splay_checker], splay_exe)
		compiled |= result
		if result == ERR_ERROR:
			print('Failed: found public/protected data/function not in skeleton code')
		os.system('mv '+ original_bst + ' ' + provided_bst)
		os.system('mv '+ temp_bst + ' ' + original_bst)
		os.system('mv '+ original_rotate + ' ' + provided_rotate)
		os.system('mv '+ temp_rotate + ' ' + original_rotate)
	print('----------------------------------------\n')

	if not os.path.exists(original_splay):
		original_found = False
		print('Failed: cannot find ' + original_splay)
	if original_found:
		os.system('mv '+ original_bst + ' ' + temp_bst)
		os.system('mv '+ provided_bst + ' ' + original_bst)
		os.system('mv '+ original_rotate + ' ' + temp_rotate)
		os.system('mv '+ provided_rotate + ' ' + original_rotate)
		os.system('mv '+ original_splay + ' ' + temp_splay)
		os.system('mv '+ provided_splay + ' ' + original_splay)
		result = compile_104([cache_checker], cache_exe)
		compiled |= result
		if result == ERR_ERROR:
			print('Failed: found public/protected data/function not in skeleton code')
		os.system('mv '+ original_bst + ' ' + provided_bst)
		os.system('mv '+ temp_bst + ' ' + original_bst)
		os.system('mv '+ original_rotate + ' ' + provided_rotate)
		os.system('mv '+ temp_rotate + ' ' + original_rotate)
		os.system('mv '+ original_splay + ' ' + provided_splay)
		os.system('mv '+ temp_splay + ' ' + original_splay)
	print('----------------------------------------\n')

	return compiled == ERR_NONE


if check_if_passed():
	print('Passed all compilation checks')
else:
	print('Failed some checks')