import sys
sys.path.insert(0, 'tests')
import cs_grading.logging_tools as log

# Individual test setting
RUN_STEP2 = 1
STEP2_USE_VALGRIND = 1
STEP2_TIMEOUT = 10

RUN_STEP3 = 1
STEP3_USE_VALGRIND = 1
STEP3_TIMEOUT = 10

RUN_STEP4 = 1
STEP4_USE_VALGRIND = 1
STEP4_TIMEOUT = 10

RUN_STEP5 = 1
STEP5_USE_VALGRIND = 1
STEP5_TIMEOUT = 10

# Global test settings

# whether test output is removed
REMOVE_OUTPUT = 0

# whether to open result file and valgrind file
OPEN_RESULT = 1

# use detailed results in file comparison
DETAILED_RESULT = 1

# DO NOT MODIFY AFTER THIS
TEXT_EDITOR = 'subl'
COMPILE_FLAGS = ['-g', '-Wall', '-std=c++11']
LOGGING_LEVEL = log.LOGLEVEL_INFO # none, error, warning, or all
GENERATE_GRADE_REPORT = False # Do now turn on when student runs test
OVERWRITE_REPORT = True # Should existing report be overwritten
