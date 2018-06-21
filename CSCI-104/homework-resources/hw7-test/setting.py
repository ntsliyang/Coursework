import sys
sys.path.insert(0, 'tests')
import cs_grading.logging_tools as log

# Individual test setting
RUN_BST = 1
BST_USE_VALGRIND = 1
BST_TIMEOUT = 20

RUN_ROTATE = 1
ROTATE_USE_VALGRIND = 1
ROTATE_TIMEOUT = 20

RUN_HYPERCUBE = 1
HYPERCUBE_USE_VALGRIND = 1
HYPERCUBE_TIMEOUT = 10

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
OVERWRITE_REPORT = False # Should existing report be overwritten
