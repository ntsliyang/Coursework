import sys

from checker_step2 import step2
from checker_step3 import step3
from checker_step4 import step4
from checker_step5 import step5
import cs_grading as cs

sys.path.insert(0, '..')
import setting

RESULT_DIR = '../results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = 'rubric/general.config'
RUBRIC_CONFIG = 'rubric/search.config'
RUBRIC_OTHER = '../rubric_other.tsv'
GRADE_REPORT_DIR = '../'
OUTPUT_DIR = '../student_output/'
MAKEFILE_DIR = '../../'
TARGET_SEARCH = 'search'
TARGET_CRAWLER = 'crawler'

HOMEWORK = cs.Homework(
    6,
    RESULT_DIR,
    setting.REMOVE_OUTPUT,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)
P2 = cs.Problem(HOMEWORK, 2, 'step2', 5)
P3 = cs.Problem(HOMEWORK, 3, 'step3', 25)
P4 = cs.Problem(HOMEWORK, 4, 'step4', 10)
P5 = cs.Problem(HOMEWORK, 5, 'step5', 36)

cs.mkdir_empty(OUTPUT_DIR, logging_level=setting.LOGGING_LEVEL)

cs.make_code(
    make_command=TARGET_SEARCH,
    makefile_dir=MAKEFILE_DIR,
    compile_file=P5.compile_file)
cs.move_file(MAKEFILE_DIR + TARGET_SEARCH, './')
cs.make_code(
    make_command=TARGET_CRAWLER,
    makefile_dir=MAKEFILE_DIR,
    compile_file=P3.compile_file)
cs.move_file(MAKEFILE_DIR + TARGET_CRAWLER, './')

if setting.RUN_STEP2:
    P2.generate_results(
        step2,
        setting.STEP2_USE_VALGRIND,
        timeout=setting.STEP2_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P2.grade_problem(RUBRIC_GENERAL, RUBRIC_CONFIG)
    if setting.OPEN_RESULT:
        P2.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_STEP3:
    P3.generate_results(
        step3,
        setting.STEP3_USE_VALGRIND,
        timeout=setting.STEP3_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P3.grade_problem(RUBRIC_GENERAL, RUBRIC_CONFIG)
    if setting.OPEN_RESULT:
        P3.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_STEP4:
    P4.generate_results(
        step4,
        setting.STEP4_USE_VALGRIND,
        timeout=setting.STEP4_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P4.grade_problem(RUBRIC_GENERAL, RUBRIC_CONFIG)
    if setting.OPEN_RESULT:
        P4.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_STEP5:
    P5.generate_results(
        step5,
        setting.STEP5_USE_VALGRIND,
        timeout=setting.STEP5_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P5.grade_problem(RUBRIC_GENERAL, RUBRIC_CONFIG)
    if setting.OPEN_RESULT:
        P5.open_result(text_editor=setting.TEXT_EDITOR)

if setting.GENERATE_GRADE_REPORT:
    HOMEWORK.grade_other_deduction(RUBRIC_OTHER)
    GRADER = cs.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
    cs.generate_grade_report(
        HOMEWORK,
        GRADER,
        GRADE_REPORT_DIR,
        overwrite=setting.OVERWRITE_REPORT,
        logging_level=setting.LOGGING_LEVEL)

if setting.REMOVE_OUTPUT:
    cs.mkdir_empty(OUTPUT_DIR, logging_level=setting.LOGGING_LEVEL)
    cs.remove_dir(OUTPUT_DIR)
    cs.remove_file(TARGET_SEARCH)
    cs.remove_file(TARGET_CRAWLER)
