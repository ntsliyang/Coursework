import cs_grading as cs
import os

text_editor = 'subl'
compile_flags = '-g -Wall -std=c++11'

run_stack_test = 1
stack_source_file = "stack_gtest.cpp ../lliststr.cpp ../stackstr.cpp"
stack_use_valgrind = 1
stack_output = 'stack_results.txt'
stack_valgrind = 'stack_valgrind.txt'

run_parser_test = 1
parser_source_file = "../stringparser.cpp ../lliststr.cpp ../stackstr.cpp"
parser_use_valgrind = 1
parser_output = 'stringparser_results.txt'
parser_valgrind = 'stringparser_valgrind.txt'


def run_stack():
	cs.compile_student_code(0, 
							source_files=stack_source_file, 
							flags=compile_flags, 
							use_gtest=1, 
							target='stack')
	cs.run_gtest_with_filter(executable_path='./',
							executable_name='stack',
							test_suite_name='StackStrTest',
							test_prefix='Test',
							test_number_min = 1,
							test_number_max = 14,
							test_delimiter='',
							redirect_output=stack_output,
							use_valgrind=stack_use_valgrind,
							valgrind_log_filename=stack_valgrind)
def run_parser():
	cs.compile_student_code(0, 
							source_files=parser_source_file, 
							flags=compile_flags, 
							use_gtest=0, 
							target='stringparser')
	cs.mkdir("parser_student_output")
	correct_test = 0
	for i in xrange(1,41):
		executable = "stringparser p5/input" + str(i) + ".txt parser_student_output/output" + str(i) + ".txt"
		output_file = "parser_student_output/output" + str(i) + ".txt"
		expected_output_file = "p5/output" + str(i) + ".txt"
		cs.run_executable('./', 
						executable, 
						'', 
						use_valgrind=parser_use_valgrind, 
						valgrind_log_filename=parser_valgrind)
		if cs.check_file_existence(output_file):
			results = cs.compare_files_with_order(	output_file, 
													expected_output_file, 
													parser_output, 
													skip_white_space=1, 
													detailed_results=0)
			cs.write_message(parser_output, '\n')

		if results[1] == 0 and results[2] == 0:
			correct_test += 1
			cs.write_message(parser_output, 'Test ' + str(i) + ' passed!\n\n')
		else:
			cs.write_message(parser_output, 'Test ' + str(i) + ' failed.\n\n')

	if correct_test == 40:
		cs.write_message(parser_output, '\nAll Test Cases Passed!')
	else: 
		cs.write_message(parser_output, 'Failed ' + str(40 - correct_test) + ' tests!')

	os.system("rm -rf parser_student_output")

if run_stack_test:
	cs.run_test(problem_name="stack", problem_grading=run_stack, open_results=1, remove_files=1)

if run_parser_test:
	cs.run_test(problem_name="stringparser", problem_grading=run_parser, open_results=1, remove_files=1)
