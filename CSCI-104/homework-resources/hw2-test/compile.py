import sys
import cs_grading as cs
import os

compile_flags = '-g -Wall -std=c++11'

if not len(sys.argv) == 2:
	print 'usage: compile.py <problem#>'
	sys.exit()

arg = sys.argv[1]

if arg == '5':
	cs.compile_student_code(0, source_files = 'fullsort_gtest.cpp', 
	flags = compile_flags, use_gtest = 1, target = 'fullsort')
	os.system('valgrind --leak-check=yes ./fullsort')

if arg == '6':
	cs.compile_student_code(0, source_files = 'lliststr_gtest.cpp ../lliststr.cpp', 
	flags = compile_flags, use_gtest = 1, target = 'lliststr')
	os.system('valgrind --leak-check=yes ./lliststr')