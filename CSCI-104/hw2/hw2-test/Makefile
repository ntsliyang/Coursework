all: fullsort lliststr assassin

fullsort: ../fullsort.cpp fullsort_gtest.cpp
	python compile.py 5

lliststr: ../lliststr.h ../lliststr.cpp lliststr_gtest.cpp
	python compile.py 6

assassin: ../assassin.cpp
	python hw2-checker.py