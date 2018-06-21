import os, collections

	
###################################################################################################################
# Purpose: Defining several strings that can be used for shorthand in many of the methods below.
# Definitions:
#      VALGRIND:    Contains the command needed for running an executable with valgrind.
#      GTEST:       Contains the compilation instruction needed for compiling an executable with Google Tests
#      HEADER:      Contains a string used to print a header to a file.
#      FOOTER:      Contains a string used to print a footer to a file.
#      TEXT_EDITOR: Contains a string representing preferred text editor.
###################################################################################################################
VALGRIND    = 'valgrind --tool=memcheck --leak-check=yes'
GTEST       = '-I /usr/include/gtest/ -l gtest -l gtest_main -pthread'
HEADER      = '\n*++++++++++++++++++++++++++++++++++++++++++++++++*'
FOOTER      = HEADER + '\n\n\n\n\n'
TEXT_EDITOR = 'subl'


###################################################################################################################
# Purpose: Clean up lines before comparison.
# Arguments:
#      source_lines:     The lines to be cleaned.
#      skip_white_space: An optional argument to filter out white space from both the source and comp files.
#      ignore_leading_characters: An optional argument to ignore the first n characters.
#      ignore_lines_with: An optional argument to ignore lines that contain this sequence.
###################################################################################################################
def cleanup_lines(source_lines,
							 skip_white_space = False,
							 ignore_leading_characters = 0,
							 ignore_lines_with = None):
	if skip_white_space:
		source_lines = [x.strip() for x in source_lines]

	source_lines = [x[ignore_leading_characters:] for x in source_lines]
	
	if ignore_lines_with != None:
		source_lines = [item for item in source_lines if ignore_lines_with not in item]

	source_lines = remove_values_from_list(source_lines, '')

	return source_lines


###################################################################################################################
# Purpose: Compares the contents of two files by looking for an extact line-by-line match. Each line will be
#          marked as either FOUND, EXTRA, or will show ACTUAL vs. EXPECTED.
# Arguments:
#      source_file:      The file with the solution contents.
#      comp_file:        The file that is compared against the source_file
#      write_file:       The file where the results are sent; they are appended to the end of the file.
#      starting_line:    An optional argument to start comparison from a particular line. Default is the beginning.
#      skip_white_space: An optional argument to filter out white space from both the source and comp files.
#                        Default is to count the white space between lines.
# Return Value:
#      The return value is a list with two items: the first indicates the number of missing lines from the comp
#      file, and the second indicates the number of extra lines beyond what was expected from the source file.
###################################################################################################################
def compare_files_with_order(source_file,
							 comp_file,
							 write_file,
							 starting_line = 0,
							 skip_white_space = False,
							 ignore_leading_characters = 0,
							 ignore_lines_with = None,
							 detailed_results = 1
							):
	with open(source_file, 'r') as source, open(comp_file, 'r') as comp, open(write_file, 'a') as write:
		source_lines = source.readlines()
		comp_lines   = comp.readlines()
		source_lines = cleanup_lines(source_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);
		comp_lines = cleanup_lines(comp_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);

		# Counts missing lines and writes comparison results to file.
		number_of_missing_lines = 0
		number_of_correct_lines = 0
		for i in range(starting_line, len(source_lines)):
			if len(comp_lines) >= i + starting_line + 1:
				if source_lines[i] == comp_lines[i]:
					if detailed_results:
						write.write('\n\tFOUND: '    + source_lines[i])
					number_of_correct_lines += 1
				else:
					if detailed_results:
						write.write('\n\tEXPECTED: ' + source_lines[i])
						write.write('\n\tACTUAL: ' + comp_lines[i])
					number_of_missing_lines += 1
			else:
				write.write('\nWARNING: Fewer lines in comp file than in source file.')
				for j in range(i, len(source_lines)):
					if detailed_results:
						write.write('\nMISSING: ' + source_lines[j])
					number_of_missing_lines += 1
				break;

		# Counts extra lines and writes the results to file.
		number_of_extra_lines = 0
		for i in range(len(source_lines), len(comp_lines)):
			if detailed_results:
				write.write('\nEXTRA: ' + comp_lines[i])
			number_of_extra_lines += 1

		# Returns list indicating number of missing and extra lines.
		return [number_of_correct_lines, number_of_missing_lines, number_of_extra_lines]

###################################################################################################################
# Purpose: Compares the contents of two files without requiring the lines of content be in the same order for
#          the files. Lines will be marked as either FOUND, MISSING, or EXTRA. Duplicates are allowed.
# Arguments:
#      source_file:      The file with the solution contents.
#      comp_file:        The file that is compared against the source_file
#      write_file:       The file where the results are sent; they are appended to the end of the file.
#      starting_line:    An optional argument to start comparison from a particular line. Default is the beginning.
#      skip_white_space: An optional argument to filter out white space from both the source and comp files.
#                        Default is to count the white space between lines.
# Return Value:
#      The return value is a list with two items: the first indicates the number of missing lines from the comp
#      file, and the second indicates the number of extra lines beyond what was expected from the source file.
###################################################################################################################
def compare_files_without_order(source_file,
								comp_file,
								write_file,
								starting_line = 0,
								skip_white_space = 0,
								ignore_leading_characters = 0,
								ignore_lines_with = None
							   ):
	with open(source_file, 'r') as source, open(comp_file, 'r') as comp, open(write_file, 'a') as write:
		source_lines = source.readlines()
		comp_lines   = comp.readlines()
		source_lines = cleanup_lines(source_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);
		comp_lines = cleanup_lines(comp_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);

		# Counts missing lines and writes comparison results to file. Order does not matter for this
		# operation.
		number_of_missing_lines = 0
		number_of_correct_lines = 0
		for i in range(starting_line, len(source_lines)):
			if source_lines[i] in comp_lines:
				write.write('\nFOUND: ' + source_lines[i])
				comp_lines.remove(source_lines[i])
				number_of_correct_lines += 1
			else:
				write.write('\nMISSING: ' + source_lines[i])
				number_of_missing_lines += 1

		# Returns list indicating number of missing and extra lines.
		number_of_extra_lines = 0
		for i in range(0, len(comp_lines)):
			write.write('\nEXTRA: ' + comp_lines[i])
			number_of_extra_lines += 1

		return [number_of_correct_lines, number_of_missing_lines, number_of_extra_lines]

###################################################################################################################
# Purpose: Compares the contents of two files, looking for sets of things (repeats allowable)
#		   that are within the same file, separated by a delimiter.
# Arguments:
#      source_file:       The file with the solution contents.
#      comp_file:         The file that is compared against the source_file
#      write_file:        The file where the results are sent; they are appended to the end of the file.
#      delimiter:	      The separator between sets, on a line of its own within the file. The separator can be
#						  white space as well as a series of characters.
#	   ignore_lines_with: Any line with this argument as a substring is ignored. This is for when each set contains
#						  a header.
#      starting_line:     An optional argument to start comparison from a particular line from within the source
#						  file. Default is the beginning.
#      skip_white_space:  An optional argument to filter out white space from both the source and comp files.
#                         Default is to count the white space between lines.
# Return Value:
#      The return value is a list with two items: the first indicates the number of missing sets from the comp
#      file, and the second indicates the number of extra sets beyond what was expected from the source file.
###################################################################################################################
def compare_files_with_sets(source_file,
							comp_file,
							write_file,
							delimiter,
							ignore_lines_with = None,
							starting_line = 0,
							skip_white_space = 0,
							ignore_leading_characters = 0
						   ):
	with open(source_file, 'r') as source, open (comp_file, 'r') as comp, open(write_file, 'a') as write:
		source_lines = source.readlines()
		comp_lines   = comp.readlines()
		source_lines = cleanup_lines(source_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);
		comp_lines = cleanup_lines(comp_lines, skip_white_space, ignore_leading_characters, ignore_lines_with);

		# Creates the nested lists needed for source_lines based on the delimiter provided and populates
		# the elements as we iterate over them.
		source_sets = []
		source_sets.append([])
		for i in range(starting_line, len(source_lines)):
			if source_lines[i] == delimiter:
				source_sets.append([])
			else:
				source_sets[len(source_sets) - 1].append(source_lines[i])

		# The student's separate nested lists.
		comp_sets = []
		comp_sets.append([])
		for i in range(0, len(comp_lines)):
			if comp_lines[i] == delimiter:
				comp_sets.append([])
			else:
				comp_sets[len(comp_sets) - 1].append(comp_lines[i])

		# Removes any empty lists from the nested set, which is used to protext against students with
		# differently formatted files that may included extra white space between sets.
		source_sets = [item for item in source_sets if len(item)]
		comp_sets   = [item for item in comp_sets if len(item)]

		# Checks for the number of incorrect sets by iterating through the source_sets and using
		# the compare() function to check if the comp_sets has a matching set. Otherwise, sets
		# are marked as missing.
		number_of_incorrect_sets = 0
		number_of_correct_sets = 0
		while(len(source_sets)):
			found_set_match = 0
			for i in range(0, len(comp_sets)):
				if compare(comp_sets[i], source_sets[0]):
					write.write('\nFOUND SET MATCH:\n')
					number_of_correct_sets += 1
					for j in range(0, len(comp_sets[i])):
						write.write('\n*' + str(comp_sets[i][j]))
					write.write('\n\n')
					comp_sets.pop(i)
					found_set_match = 1
					break
			if found_set_match == 0:
				number_of_incorrect_sets += 1
				write.write('\nMISSING SET:\n')
				for i in range(0, len(source_sets[0])):
					write.write('\n*' + str(source_sets[0][i]))
				write.write('\n\n')
			source_sets.pop(0)

		# Shows any extra sets within the students answers.
		number_of_extra_sets = 0
		while(len(comp_sets)):
			write.write('\nEXTRA SET:\n')
			for i in range(0, len(comp_sets[0])):
				write.write('\n*' + str(comp_sets[0][i]))
			write.write('\n\n')
			number_of_extra_sets += 1
			comp_sets.pop(0)

		# Gives the results back.
		return [number_of_correct_sets, number_of_incorrect_sets, number_of_extra_sets]

###################################################################################################################
# Purpose: Compile students code into an executable either with a makefile or with given arguments.
# Arguments:
#     makefile_provided: Pass 1 if a student has a makefile provided, otherwise pass 0.
#     make_command:      If a student has a makefile provided, and there is a specific make command that needs to
#                        be run, it can be passed here. For example, 'make settest'. Just pass 'settest' as this
#                        argument.
#     source_files:      The source files needed to compile an executable in case a makefile is not provided. The
#                        source files can be in a single string, separated by spaces.
#     compiler:          The compiler that will be used in case a makefile is not provided. Default is 'g++'
#     flags:             Any flags you wish to use when compiling. '-g -Wall' are defaults.
#     target:            The name of the executable that is created in case no makefile is provided.
#     use_gtest:         Pass 1 if no makefile is provided and compilation requires Google Tests.
###################################################################################################################
def compile_student_code(makefile_provided,
						 make_command = '',
						 source_files = '',
						 compiler = 'g++',
						 flags = '-g -Wall',
						 target = 'executable',
						 use_gtest = 0
						):
	if makefile_provided:
		os.system('make ' + make_command)
	else:
		if use_gtest:
			os.system(compiler + ' ' + flags + ' ' + source_files + ' ' + GTEST + ' -o ' + target)
		else:
			os.system(compiler + ' ' + flags + ' ' + source_files + ' -o ' + target)

###################################################################################################################
# Purpose: Runs an executable with additional options.
# Arguments:
#     executable_path: The path to the executable. For example, './'.
#     executable_name: The name of the executable that will be run.
#     extra_arguments: Any extra commands that are needed to run the executable. For example,
#                      run_executable('./', 'ex', 'test.in test.out') will run as follows:
#                      ./ex test.in test.out
#
#                      This can also be used to redirect input and output. For example,
#                      run_executable('./', 'ex', '< test.in > test.out') will run as follows:
#                      ./ex < test.in > test.out
#      use_valgrind:   An optional argument to run an executable with valgrind. By default, it is not used.
###################################################################################################################
def run_executable(executable_path,
					 executable_name,
					 extra_arguments = '',
					 use_valgrind = 0,
					 valgrind_log_filename = ''
					):
	if use_valgrind:
		temp_valgrind_log = 'temp_valgrind_log.txt'
		os.system(VALGRIND + ' --log-file=\"' + temp_valgrind_log + '\" ' + executable_path + executable_name + ' ' + extra_arguments)
		write_file_contents(valgrind_log_filename, temp_valgrind_log)
		write_message(valgrind_log_filename, '\n\n')
		remove_file(temp_valgrind_log)
	else:
		os.system(executable_path + executable_name + ' ' + extra_arguments)

###################################################################################################################
# Purpose: Runs a gtest with filter and additional options.
#          A filer is created with the format: 
#          --gtest_filter=<Suite>.<Prefix><Number><Delimiter>*
# Arguments:
#     executable_path: The path to the executable. For example, './'.
#     executable_name: The name of the executable that will be run.
#     test_suite_name: The name of the gtest suite.
#     test_prefix:     The prefix of a test before test number and delimiter.
#     test_number_min: The test number of the first test (inclusive).
#     test_number_max: The test number of the last test (exclusive).
#     test_delimiter:  The delimier used to denote the end of test number.
#     redirect_output: File name of the rediection output file, if any. 
#                      Default to None and does not use redirecton. 
#     use_valgrind:    An optional argument to run an executable with valgrind. By default, it is not used.
###################################################################################################################
def run_gtest_with_filter(executable_path,
				 executable_name,
				 test_suite_name,
				 test_prefix,
				 test_number_min,
				 test_number_max,
				 test_delimiter = '_',
				 redirect_output = None,
				 use_valgrind = 0,
				 valgrind_log_filename = '',
				):
	gtest_filter = '--gtest_filter=' + test_suite_name + '.' + test_prefix
	temp_gtest_log = 'temp_gtest_log.txt'
	if redirect_output == None:
		extra_arguments = ''
	else:
		extra_arguments = ' > ' + temp_gtest_log

	for i in range(test_number_min, test_number_max):
		gtest_filter_numbered = gtest_filter + str(i) + test_delimiter + '*'
		run_executable(executable_path,
				executable_name,
				gtest_filter_numbered + extra_arguments,
				use_valgrind,
				valgrind_log_filename
			)
		if redirect_output != None:
			write_file_contents(redirect_output, temp_gtest_log)
			write_message(redirect_output, '\n\n')
			remove_file(temp_gtest_log)


###################################################################################################################
# Purpose: Removes all instances of a given value from a list.
# Arguments:
#       list:  The original list that is to be modified.
#       value: The single value that is to be removed from the list.
# Return Value:
#       The return value is a list with the contents of the original list, minus the value. The order of elements
#       in the list is stable.
###################################################################################################################
def remove_values_from_list(list,
							value
						   ):
	return [item for item in list if item != value]

###################################################################################################################
# Purpose: Removes files from the current directory with a given name.
# Arguments:
#       file_name: The name of the file to be removed. Can be used to remove a single fine, or use the wildcard
#                  '*' to remove multiple files. For example, remove_file(*.txt) will remove all .txt files from
#                  the current directory. Multiple file names can be entered in a single string separated by
#                  a space.
###################################################################################################################
def remove_file(file_name):
	files_to_remove = file_name.split()
	for i in range(0, len( files_to_remove)):
		os.system('rm ' + str(files_to_remove[i]))

###################################################################################################################
# Purpose: Checks if a file exists within the current directory or another directory.
# Arguments:
#       file_name: The name of the file to check.
#       directory: The directory to check. By default, the directory is the current directory.
# Return Value:
#       The return value is either 0 or 1 depending on whether or not the file exists. A 1 means the file exists
#       and 0 means the file does not exist.
###################################################################################################################
def check_file_existence(file_name,
						 directory = '/'
						):
	return os.path.exists(file_name)

###################################################################################################################
# Purpose: Opens a file with a text editor for fast viewing.
# Arguments:
#       file_name:   The name of the file to be opened. Can be used to open a single file, or the wildcard '*' can
#                    be used to open multiple files.
#       text_editor: The text editor that the file(s) will be opened with. By default, it is the text editor
#                    defined at the top of the file.
###################################################################################################################
def open_file(file_name,
				text_editor = TEXT_EDITOR
			 ):
	os.system(text_editor + ' ' + file_name)

###################################################################################################################
# Purpose: Write a header to a file, which is used to separate sections of a file.
# Arguments:
#       target_file: The file to which the header is written.
#       write_mode:  The mode in which the header is written. By default, it is appended to a file.
###################################################################################################################
def write_header(target_file,
				 write_mode = 'a'
				):
	with open(target_file, write_mode) as target:
		target.write(HEADER)

###################################################################################################################
# Purpose: Write a footer to a file, which is used to separate sections of a file.
# Arguments:
#       target_file: The file to which the footer is written.
#       write_mode:  The mode in which the footer is written. By default, it is appended to a file.
###################################################################################################################
def write_footer(target_file,
				 write_mode = 'a'
				):
	with open(target_file, write_mode) as target:
		target.write(FOOTER)

###################################################################################################################
# Purpose: Writes a message to a file.
# Arguments:
#       target_file: The file to which the message is written.
#       message:     The message that is written to the file.
#       write_mode:  The mode in which the message is written. By default, it is appended to a file.
###################################################################################################################
def write_message(target_file,
					message,
					write_mode = 'a'
				 ):
	with open(target_file, write_mode) as target:
		target.write(message)

###################################################################################################################
# Purpose: Writes the contents of one file to another file. Line endings are striped away so leading/trailing
#          white space is ignored.
# Arguments:
#       target_file: The name of the file to which the contents of the other file are written.
#       source_file: The name of the file from which the contents are extracted.
#       write_mode:  The mode in which the contents are written. By default, they are appended to the file.
###################################################################################################################
def write_file_contents(target_file,
						source_file,
						write_mode = 'a'
					 ):
	with open(target_file, write_mode) as target, open(source_file, 'r') as source:
		source_contents = source.read().strip()
		target.write(source_contents)

###################################################################################################################
# Purpose: Reads the contents of a file and returns those contents.
# Arguments:
#       target_file: The name of the file that will be read.
###################################################################################################################
def read_file_contents(target_file):
	content = ''
	with open(target_file, 'r') as target:
		content = target.read()
	return content

###################################################################################################################
# Purpose: Used to compare the contents of two unordered list to check if they are the same list.
# Arguments:
#       x and y: The two lists in question.
###################################################################################################################
compare = lambda x, y: collections.Counter(x) == collections.Counter(y)

###################################################################################################################
# Purpose: Used to create a directory.
# Arguments:
#       target: The name of the directory that will be created.
###################################################################################################################
def mkdir(target):
	try:
		os.mkdir(target)
	except Exception as e:
		pass

###################################################################################################################
# Purpose: Used to create the suppresion file for valgrind errors.
# Arguments:
#       target_file: The name of the suppression file that will be created.
###################################################################################################################
def generate_valgrind_suppression(target_file = 'gcc.supp'):
	os.system('echo "{\n<gcc_reachable>\nMemcheck:Leak\nmatch-leak-kinds: reachable\nfun:malloc\nobj:/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21\nfun:call_init.part.0\nfun:call_init\nfun:_dl_init\nobj:/lib/x86_64-linux-gnu/ld-2.23.so\n}" > ~/' + target_file)

###################################################################################################################
# Purpose: Checks for a file's existance and removes it if it exists. 
# Arguments:
#       target_file: The name of the file to be removed.
###################################################################################################################
def clean_file(target_file):
	if check_file_existence(target_file):
		remove_file(target_file)


###################################################################################################################
# Purpose: Takes care of running tests. 
# Arguments:
#       problem_name: The name of the problem to be graded.
#		problem_grading: The name of the function that compiles, grades, and outputs the results. 
#		use_valgrind: Option to enable valgrind for grading.
#		source_files: File location and names that need to be compiled.
#		open_results: Open result files after grading.
#		remove_files: Clean up intermediate files.
#		text_editor: Text editor used to open up results.
###################################################################################################################
def run_test(problem_name, problem_grading, open_results, remove_files, text_editor = 'subl'):
	problem_name_result_file = problem_name + '_result.txt'
	problem_name_valgrind_file = problem_name + '_valgrind.txt'
	problem_name_target = problem_name

	clean_file(problem_name_result_file)
	clean_file(problem_name_valgrind_file)

	###########
	########### COMPILE AND RUN TESTS, PRINT TO RESULTS.
	###########
	problem_grading()


	if open_results:
		open_file(problem_name_result_file, text_editor)
		if check_file_existence(problem_name_valgrind_file):
			open_file(problem_name_valgrind_file, text_editor)

	if remove_files:
		clean_file(problem_name_target)