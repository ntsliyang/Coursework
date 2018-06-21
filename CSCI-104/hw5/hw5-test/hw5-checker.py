import cs_grading as cs
import os

text_editor = 'subl'
compile_flags = '-g -Wall -std=c++11'

run_functor = 1
functor_source_file = "functor_gtest.cpp"
functor_use_valgrind = 1
functor_output = 'functor_result.txt'
functor_valgrind = 'functor_valgrind.txt'

run_qsort = 1
qsort_source_file = "qsort_gtest.cpp"
qsort_use_valgrind = 1
qsort_output = 'qsort_result.txt'
qsort_valgrind = 'qsort_valgrind.txt'

run_exception = 1
exception_source_file = "exception_gtest.cpp"
exception_use_valgrind = 1
exception_output = 'exception_result.txt'
exception_valgrind = 'exception_valgrind.txt'

run_thanksgiving = 1
thanksgiving_source_file = "thanksgiving_gtest.cpp ../LengthMismatch.cpp"
thanksgiving_use_valgrind = 1
thanksgiving_output = 'thanksgiving_result.txt'
thanksgiving_valgrind = 'thanksgiving_valgrind.txt'

def functor():
	cs.compile_student_code(0, 
							source_files=functor_source_file, 
							flags=compile_flags, 
							use_gtest=1, 
							target='functor')
	cs.run_gtest_with_filter(executable_path='./',
							executable_name='functor',
							test_suite_name='FunctorTest',
							test_prefix='Test',
							test_number_min = 1,
							test_number_max = 6,
							test_delimiter='',
							redirect_output=functor_output,
							use_valgrind=functor_use_valgrind,
							valgrind_log_filename=functor_valgrind)


def qsort():
	cs.compile_student_code(0, 
							source_files=qsort_source_file, 
							flags=compile_flags, 
							use_gtest=1, 
							target='qsort')
	cs.run_gtest_with_filter(executable_path='./',
							executable_name='qsort',
							test_suite_name='QSortTest',
							test_prefix='Test',
							test_number_min = 1,
							test_number_max = 14,
							test_delimiter='',
							redirect_output=qsort_output,
							use_valgrind=qsort_use_valgrind,
							valgrind_log_filename=qsort_valgrind)

def exception():
	cs.compile_student_code(0, 
							source_files=exception_source_file, 
							flags=compile_flags, 
							use_gtest=1, 
							target='exception')
	cs.run_executable('./',
					 'exception',
					 extra_arguments = (' > ' + exception_output),
					 use_valgrind = 1,
					 valgrind_log_filename = exception_valgrind
					)

def thanksgiving():
	cs.compile_student_code(0, 
							source_files=thanksgiving_source_file, 
							flags=compile_flags, 
							use_gtest=1, 
							target='thanksgiving')
	cs.run_executable('./',
					 'thanksgiving',
					 extra_arguments = (' > ' + thanksgiving_output),
					 use_valgrind = 1,
					 valgrind_log_filename = thanksgiving_valgrind
					)

if run_functor:
	cs.run_test(problem_name="functor", problem_grading=functor, open_results=1, remove_files=1)

if run_qsort:
	cs.run_test(problem_name="qsort", problem_grading=qsort, open_results=1, remove_files=1)

if run_exception:
	cs.run_test(problem_name="exception", problem_grading=exception, open_results=1, remove_files=1)

if run_thanksgiving:
	cs.run_test(problem_name="thanksgiving", problem_grading=thanksgiving, open_results=1, remove_files=1)
