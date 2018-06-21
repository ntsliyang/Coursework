import cs_grading as cs
import os

text_editor = 'subl'

run_websearch_test     = 1            # Change to 0 to turn off these tests .
run_websearch_stress   = 1			  # Change to 0 to turn off stress tests.
websearch_use_valgrind = 0            # Change to 0 if you don't want valgrind to be run.
websearch_open_results = 1            # Change to 0 if you don't want the results files opened automatically.
websearch_remove_files = 1            # Change to 0 if you don't want intermediary files to be removed. 

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

def gen_stress_files():
	for i in range(1, 100000):
		os.system('echo "a b c d e f" > stress-data/data' + str(i) + '.txt')

def run_websearch():
	# Compile student's executable and move it into our test directory
	cwd = os.getcwd();
	os.chdir('..')
	os.system('make search')
	os.chdir(cwd);

	index_dir = 'index/'
	query_dir = 'query/'
	student_output = 'student_output/'
	websearch_result_file = 'websearch_result.txt'

	# Generate student output folder
	if os.path.isdir(student_output):
		os.system('rm -rf ' + student_output)
	os.mkdir(student_output) 


	for di in os.listdir(query_dir):
		for fn in os.listdir(query_dir + di + '/'):
			print(query_dir + di + '/' + fn + ' -> ' + student_output + fn.split('.')[0] + '.out')
			cs.run_executable(executable_path = '../',
						 executable_name = 'search',
						 extra_arguments = 'index/' + di + '.in' + ' ' + query_dir + di + '/' + fn + ' ' + student_output + fn.split('.')[0] + '.out',
						 use_valgrind = websearch_use_valgrind,
						 valgrind_log_filename = 'websearch_valgrind.txt')

	failed_test = []
	for fn in sorted(os.listdir('websearch_output'), file_comp):
		results = [-1, -1, -1]
		student_ofile = student_output + fn.split('.')[0] + '.out'
		if (os.path.exists(student_ofile)):
			results = cs.compare_files_without_order(source_file = student_ofile,
									 comp_file = 'websearch_output/' + fn,
									 write_file = 'websearch_result.txt',
									 skip_white_space = True,
									)

		cs.write_message(websearch_result_file, '\n\n')

		if results[1] == 0 and results[2] == 0:
			cs.write_message(websearch_result_file, 'Test ' + fn + ' passed!\n\n')
		else:
			failed_test.append(fn)
			cs.write_message(websearch_result_file, 'Test ' + fn + ' failed.\n\n')

	if len(failed_test) == 0:
		cs.write_message(websearch_result_file, '\nAll Test Cases Passed!')
	else: 
		cs.write_message(websearch_result_file, 'Failed ' + str(len(failed_test)) + ' tests:\n')
		for ft in failed_test:
			cs.write_message(websearch_result_file, ft + '\n')

	if run_websearch_stress:
		cs.clean_file('stress-websearch_result.txt')

		if os.path.exists('stress-student'):
			os.system('rm -rf stress-student')

		os.mkdir('stress-student')

		cs.mkdir('stress-data')
		print 'Checking for stress-data files..'
		if len(os.listdir('stress-data')) == 0:
			print 'Generating stress-data files...'
			gen_stress_files()

		print "Running stress tests:"
		for di in sorted(os.listdir('stress-query/'), file_comp):
			for fn in sorted(os.listdir('stress-query/' + di + '/'), file_comp):
				print 'index: ' + di + ' query: ' + fn
				os.system('time --format=%E ' + '../search' + ' ' + 'stress-index/' + di + '.in' + ' ' + 'stress-query/' + di + '/' + fn + ' ' + 'stress-student/' + fn.split('.')[0] + '.out')
				print '\n'

		failed_test = []
		for fn in sorted(os.listdir('stress-websearch_output'), file_comp):
			results = [-1, -1, -1]
			student_ofile = 'stress-student/' + fn.split('.')[0] + '.out'
			if (os.path.exists(student_ofile)):
				results = cs.compare_files_without_order(source_file = student_ofile,
										 comp_file = 'stress-websearch_output/' + fn,
										 write_file = 'stress-websearch_result.txt',
										 skip_white_space = True,
										)

			cs.write_message('stress-websearch_result.txt', '\n\n')

			if results[1] == 0 and results[2] == 0:
				cs.write_message('stress-websearch_result.txt', 'Test ' + fn + ' passed!\n\n')
			else:
				failed_test.append(fn)
				cs.write_message('stress-websearch_result.txt', 'Test ' + fn + ' failed.\n\n')

		if len(failed_test) == 0:
			cs.write_message('stress-websearch_result.txt', '\nAll Test Cases Passed!')
			print "Stress test correctness passed."
		else: 
			cs.write_message('stress-websearch_result.txt', 'Failed ' + str(len(failed_test)) + ' tests:\n')
			print "Stress test correctness failed:"
			for ft in failed_test:
				cs.write_message('stress-websearch_result.txt', ft + '\n')
				print ft + '\n'

		if websearch_remove_files:
			print "Cleaning stress data files... Set websearch_remove_files to 0 to skip this step"
			os.system('rm stress-data/data1*')
			os.system('rm stress-data/data2*')
			os.system('rm stress-data/data3*')
			os.system('rm stress-data/data4*')
			os.system('rm stress-data/data5*')
			os.system('rm stress-data/*')


	if websearch_remove_files:
		os.system('rm -rf ' + student_output)
		os.system('rm -rf stress-student')
		

if run_websearch_test:
	cs.run_test(problem_name = 'websearch', problem_grading = run_websearch,
		open_results = websearch_open_results, remove_files = websearch_remove_files)
