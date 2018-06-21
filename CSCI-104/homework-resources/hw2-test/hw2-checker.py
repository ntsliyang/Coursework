import cs_grading as cs
import os

text_editor = 'subl'
compile_flags = '-g -Wall -std=c++11'

run_fullsort_test     = 0            # Change to 0 to turn off these tests .
fullsort_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
fullsort_source_files = 'fullsort_gtest.cpp' # The name and location of the student's solution file relative to this script.
fullsort_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
fullsort_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 

run_lliststr_test     = 0            # Change to 0 to turn off these tests .
lliststr_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
lliststr_source_files = 'lliststr_gtest.cpp ../lliststr.cpp' # The name and location of the student's solution file relative to this script.
lliststr_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
lliststr_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 

run_assassin_test     = 1            # Change to 0 to turn off these tests .
assassin_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
assassin_source_files = '../assassin.cpp ../lliststr.cpp' # The name and location of the student's solution file relative to this script.
assassin_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
assassin_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 

def file_comp(lhs, rhs):
	if lhs == rhs:
		return 0
	elif len(lhs) < len(rhs):
		return -1 
	elif len(lhs) == len(rhs):
		if lhs < rhs:
			return -1
		else:
			return 1
	else:
		return 1

def run_fullsort():
	cs.compile_student_code(0, source_files = fullsort_source_files, 
	flags = compile_flags, use_gtest = 1, target = 'fullsort')
	cs.run_gtest_with_filter(executable_path = './',
				 executable_name = 'fullsort',
				 test_suite_name = 'FullsortTest',
				 test_prefix = 'Test',
				 test_number_min = 1,
				 test_number_max = 16,
				 test_delimiter = '_',
				 redirect_output = 'fullsort_result.txt',
				 use_valgrind = fullsort_use_valgrind,
				 valgrind_log_filename = 'fullsort_valgrind.txt',
				)


def run_lliststr():
	cs.compile_student_code(0, source_files = lliststr_source_files, 
		flags = compile_flags, use_gtest = 1, target = 'lliststr')
	cs.run_gtest_with_filter(executable_path = './',
				 executable_name = 'lliststr',
				 test_suite_name = 'LListStrTest',
				 test_prefix = 'Test',
				 test_number_min = 1,
				 test_number_max = 26,
				 test_delimiter = '_',
				 redirect_output = 'lliststr_result.txt',
				 use_valgrind = lliststr_use_valgrind,
				 valgrind_log_filename = 'lliststr_valgrind.txt',
				)

def run_assassin():
	cs.compile_student_code(0, source_files = assassin_source_files,
		flags = compile_flags, target = 'assassin')

	executable = './assassin'
	input_dir = executable + '_input/'
	output_dir = executable + '_output/'
	assassin_result_file = 'assassin_result.txt'

	if(not os.path.isdir('assassin_student')):
		os.mkdir('assassin_student')
	else:
		os.system('rm -rf assassin_student')
		os.mkdir('assassin_student')

	for fn in os.listdir(input_dir):
		cs.run_executable(executable_path = './',
					 executable_name = 'assassin',
					 extra_arguments = input_dir + fn + ' > assassin_student/' + fn.split('.')[0] + '.out',
					 use_valgrind = assassin_use_valgrind,
					 valgrind_log_filename = 'assassin_valgrind.txt'
					)

	failed_test = [];
	for fn in sorted(os.listdir(input_dir), file_comp):
		results = [-1, -1, -1]
		results = cs.compare_files_with_order(source_file = 'assassin_student/' + fn.split('.')[0] + '.out',
								 comp_file = output_dir + fn.split('.')[0] + '.out',
								 write_file = 'assassin_result.txt',
								 skip_white_space = 1,
								 detailed_results = 0
								)
		if results[1] == 0 and results[2] == 0:
			cs.write_message(assassin_result_file, 'Test ' + fn + ' passed!\n\n')
		else:
			failed_test.append(fn)
			cs.write_message(assassin_result_file, 'Test ' + fn + ' failed.\n\n')

	if len(failed_test) == 0:
		cs.write_message(assassin_result_file, '\nAll Test Cases Passed!')
	else: 
		cs.write_message(assassin_result_file, 'Failed ' + str(len(failed_test)) + ' tests:\n')
		for ft in failed_test:
			cs.write_message(assassin_result_file, ft + '\n')

	if assassin_remove_files:
		os.system('rm -rf assassin_student')


if run_fullsort_test:
	cs.run_test(problem_name = 'fullsort', problem_grading = run_fullsort, 
		open_results = fullsort_open_results, remove_files = fullsort_remove_files)

if run_lliststr_test:
	cs.run_test(problem_name = 'lliststr', problem_grading = run_lliststr,
		open_results = lliststr_open_results, remove_files = fullsort_remove_files)

if run_assassin_test:
	cs.run_test(problem_name = 'assassin', problem_grading = run_assassin,
		open_results = assassin_open_results, remove_files = assassin_remove_files)