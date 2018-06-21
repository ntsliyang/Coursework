import sys

from checker_bst import bst
from checker_rotate import rotate
from checker_hypercube import hypercube
import cs_grading as cs

sys.path.insert(0, '..')
import setting

RESULT_DIR = '../results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = 'rubric/general.config'
RUBRIC_BST = 'rubric/bst.config'
RUBRIC_ROTATE = 'rubric/rotate.config'
RUBRIC_HYPERCUBE = 'rubric/hypercube.config'
RUBRIC_OTHER = '../rubric_other.tsv'
GRADE_REPORT_DIR = '../'

HOMEWORK = cs.Homework(
    7,
    RESULT_DIR,
    setting.REMOVE_OUTPUT,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)
P1 = cs.Problem(HOMEWORK, 1, 'bst', 28)
P2 = cs.Problem(HOMEWORK, 2, 'rotate', 20)
P3 = cs.Problem(HOMEWORK, 3, 'hypercube', 30)

if setting.RUN_BST:
    P1.generate_results(
        bst,
        setting.BST_USE_VALGRIND,
        timeout=setting.BST_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P1.grade_problem(RUBRIC_GENERAL, RUBRIC_BST)
    if setting.OPEN_RESULT:
        P1.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_ROTATE:
    P2.generate_results(
        rotate,
        setting.ROTATE_USE_VALGRIND,
        timeout=setting.ROTATE_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P2.grade_problem(RUBRIC_GENERAL, RUBRIC_ROTATE)
    if setting.OPEN_RESULT:
        P2.open_result(text_editor=setting.TEXT_EDITOR)

if setting.RUN_HYPERCUBE:
    P3.generate_results(
        hypercube,
        setting.HYPERCUBE_USE_VALGRIND,
        timeout=setting.HYPERCUBE_TIMEOUT,)
    if setting.GENERATE_GRADE_REPORT:
        P3.grade_problem(RUBRIC_GENERAL, RUBRIC_HYPERCUBE)
    if setting.OPEN_RESULT:
        P3.open_result(text_editor=setting.TEXT_EDITOR)

if setting.GENERATE_GRADE_REPORT:
    HOMEWORK.grade_other_deduction(RUBRIC_OTHER)
    GRADER = cs.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
    cs.generate_grade_report(
        HOMEWORK,
        GRADER,
        GRADE_REPORT_DIR,
        overwrite=setting.OVERWRITE_REPORT,
        logging_level=setting.LOGGING_LEVEL)
