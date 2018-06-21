import cs_grading as CS 
import os

text_editor = 'subl'


#Options for p5
run_p5_test     = 1            # Change to 0 to turn off these tests .
p5_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
p5_source_files = '../barry.cpp' # The name and location of the student's solution file relative to this script.
p5_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
p5_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 

#Options for p6
run_p6_test     = 1            # Change to 0 to turn off these tests .
p6_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
p6_source_files = '../hw1q6.cpp' # The name and location of the student's solution file relative to this script.
p6_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
p6_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 


#Options for p7
run_p7_test     = 1            # Change to 0 to turn off these tests .
p7_use_valgrind = 1            # Change to 0 if you don't want valgrind to be run.
p7_source_files = '../game_of_pointers.cpp' # The name and location of the student's solution file relative to this script.
p7_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
p7_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 


### p5 run tests
if run_p5_test:
	p5_result_file = 'p5_result.txt'
	p5_valgrind_file = 'p5_valgrind.txt'
	p5_target = 'barry'

	if CS.check_file_existence(p5_result_file):
		CS.remove_file(p5_result_file)
	if CS.check_file_existence(p5_valgrind_file):
		CS.remove_file(p5_valgrind_file)

	CS.compile_student_code(0, 
							source_files=p5_source_files, 
							target=p5_target, 
							flags='-g -Wall -std=c++11')

	CS.mkdir('q5_student_output')

	f = open('q5_input/input.txt', 'r')

	correct_test = 0
	for i in xrange(1,11):
		string = f.readline().strip()
		output_file = 'q5_student_output/output'  + str(i) + '.out'
		expected_output_file = 'q5_output/output'  + str(i) + '.txt'
		CS.run_executable('./', 
						p5_target, 
						string + ' > ' + output_file, 
						use_valgrind=p5_use_valgrind, 
						valgrind_log_filename=p5_valgrind_file)
		if CS.check_file_existence(output_file):
			results = CS.compare_files_with_order(	output_file, 
													expected_output_file, 
													p5_result_file, 
													skip_white_space=1, 
													detailed_results=0)
			CS.write_message(p5_result_file, '\n')

		if results[1] == 0 and results[2] == 0:
			correct_test += 1
			CS.write_message(p5_result_file, 'Test ' + str(i) + ' passed!\n\n')
		else:
			CS.write_message(p5_result_file, 'Test ' + str(i) + ' failed.\n\n')

	if correct_test == 10:
		CS.write_message(p5_result_file, '\nAll Test Cases Passed!')
	else: 
		CS.write_message(p5_result_file, 'Failed ' + str(10 - correct_test) + ' tests!')

	if p5_open_results:
		CS.open_file(p5_result_file, text_editor)
		if p5_use_valgrind:
			CS.open_file(p5_valgrind_file, text_editor)

	# Clean up
	if p5_remove_files:
		CS.remove_file(p5_target)
		os.system('rm -r q5_student_output')



### p6 run tests
if run_p6_test:
	p6_result_file = 'p6_result.txt'
	p6_valgrind_file = 'p6_valgrind.txt'
	p6_target = 'hw1q6'

	if CS.check_file_existence(p6_result_file):
		CS.remove_file(p6_result_file)
	if CS.check_file_existence(p6_valgrind_file):
		CS.remove_file(p6_valgrind_file)

	CS.compile_student_code(0, 
							source_files=p6_source_files, 
							target=p6_target, 
							flags='-g -Wall -std=c++11')

	CS.mkdir('q6_student_output')

	correct_test = 0
	for i in xrange(1,11):
		string = 'q6_input/input' + str(i) + '.txt'
		output_file = 'q6_student_output/output'  + str(i) + '.out'
		expected_output_file = 'q6_output/output'  + str(i) + '.txt'
		CS.run_executable('./', 
						p6_target, 
						string + ' > ' + output_file, 
						use_valgrind=p6_use_valgrind, 
						valgrind_log_filename=p6_valgrind_file)
		if CS.check_file_existence(output_file):
			results = CS.compare_files_with_order(	output_file, 
													expected_output_file, 
													p6_result_file, 
													skip_white_space=1, 
													detailed_results=0)
			CS.write_message(p6_result_file, '\n')

		if results[1] == 0 and results[2] == 0:
			correct_test += 1
			CS.write_message(p6_result_file, 'Test ' + str(i) + ' passed!\n\n')
		else:
			CS.write_message(p6_result_file, 'Test ' + str(i) + ' failed.\n\n')

	if correct_test == 10:
		CS.write_message(p6_result_file, '\nAll Test Cases Passed!')
	else: 
		CS.write_message(p6_result_file, 'Failed ' + str(10 - correct_test) + ' tests!')

	if p6_open_results:
		CS.open_file(p6_result_file, text_editor)
		if p6_use_valgrind:
			CS.open_file(p6_valgrind_file, text_editor)

	# Clean up
	if p6_remove_files:
		CS.remove_file(p6_target)
		os.system('rm -r q6_student_output')

if run_p7_test:
	p7_result_file = 'got_result.txt'
	p7_valgrind_file = 'got_valgrind.txt'
	p7_target = 'game_of_pointers'
	p7_test_count = 16

	if CS.check_file_existence(p7_result_file):
		CS.remove_file(p7_result_file)
	if CS.check_file_existence(p7_valgrind_file):
		CS.remove_file(p7_valgrind_file)

	CS.compile_student_code(0, 
							source_files=p7_source_files, 
							target=p7_target, 
							flags='-g -Wall -std=c++11')

	CS.mkdir('q7_student_output')

	correct_test = 0
	for i in xrange(1,p7_test_count + 1):
		parameters = 'q7_input/input' + str(i) + '.txt'
		parameters += ' q7_student_output/output' + str(i) +'.txt'
		output_file = 'q7_student_output/output' + str(i) +'.txt'
		expected_output_file = 'q7_input/solution'  + str(i) + '.txt'
		CS.run_executable('./', 
						p7_target, 
						parameters, 
						use_valgrind=p7_use_valgrind, 
						valgrind_log_filename=p7_valgrind_file)
		if CS.check_file_existence(output_file):
			results = CS.compare_files_with_order(	output_file, 
													expected_output_file, 
													p7_result_file, 
													skip_white_space=1, 
													detailed_results=0)
			CS.write_message(p7_result_file, '\n')

		if results[1] == 0 and results[2] == 0:
			correct_test += 1
			CS.write_message(p7_result_file, 'Test ' + str(i) + ' passed!\n\n')
		else:
			CS.write_message(p7_result_file, 'Test ' + str(i) + ' failed.\n\n')

	if correct_test == p7_test_count:
		CS.write_message(p7_result_file, '\nAll Test Cases Passed!')
	else: 
		CS.write_message(p7_result_file, 'Failed ' + str(p7_test_count - correct_test) + ' tests!')

	if p6_open_results:
		CS.open_file(p7_result_file, text_editor)
		if p6_use_valgrind:
			CS.open_file(p7_valgrind_file, text_editor)

	# Clean up
	if p7_remove_files:
		CS.remove_file(p7_target)
		os.system('rm -r q7_student_output')
