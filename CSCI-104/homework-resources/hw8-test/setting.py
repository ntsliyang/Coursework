import sys
sys.path.insert(0, 'tests')
import cs_grading.logging_tools as log

# Individual test setting
RUN_SPLAY = 1
SPLAY_USE_VALGRIND = 1
SPLAY_TIMEOUT = 60

RUN_CACHE = 1
CACHE_USE_VALGRIND = 1
CACHE_TIMEOUT = 60

# Global test settings

# whether test output is removed
REMOVE_OUTPUT = 0

# whether to open result file and valgrind file
OPEN_RESULT = 0

# use detailed results in file comparison
DETAILED_RESULT = 1

# DO NOT MODIFY AFTER THIS
TEXT_EDITOR = 'subl'
COMPILE_FLAGS = ['-g', '-Wall', '-std=c++11']
LOGGING_LEVEL = log.LOGLEVEL_INFO # none, error, warning, or all
GENERATE_GRADE_REPORT = False # Do now turn on when student runs test
OVERWRITE_REPORT = False # Should existing report be overwritten
