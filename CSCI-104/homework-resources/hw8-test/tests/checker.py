import sys

from checker_splay import splay
from checker_cache import cache
from cs_grading import Grader, Homework, Problem
from cs_grading import generate_grade_report

sys.path.insert(0, '..')
import setting

RESULT_DIR = '../results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = 'rubric/general.config'
RUBRIC_SPLAY = 'rubric/splay.config'
RUBRIC_CACHE = 'rubric/cache.config'
RUBRIC_OTHER = '../rubric_other.tsv'
GRADE_REPORT_DIR = '../'

HOMEWORK = Homework(
    8,
    RESULT_DIR,
    setting.REMOVE_OUTPUT,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)
P1 = Problem(HOMEWORK, 1, 'splay', 30)
P2 = Problem(HOMEWORK, 2, 'cache', 14)

if setting.RUN_SPLAY:
    P1.generate_results(
        splay,
        setting.SPLAY_USE_VALGRIND,
        timeout=setting.SPLAY_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P1.grade_problem(RUBRIC_GENERAL, RUBRIC_SPLAY)
    if setting.OPEN_RESULT:
        P1.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_CACHE:
    P2.generate_results(
        cache,
        setting.CACHE_USE_VALGRIND,
        timeout=setting.CACHE_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P2.grade_problem(RUBRIC_GENERAL, RUBRIC_CACHE)
    if setting.OPEN_RESULT:
        P2.open_result(text_editor=setting.TEXT_EDITOR)

if setting.GENERATE_GRADE_REPORT:
    HOMEWORK.grade_other_deduction(RUBRIC_OTHER)
    GRADER = Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
    generate_grade_report(
        HOMEWORK,
        GRADER,
        GRADE_REPORT_DIR,
        overwrite=setting.OVERWRITE_REPORT,
        logging_level=setting.LOGGING_LEVEL)
