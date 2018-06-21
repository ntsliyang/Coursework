import os
import cs_grading as cs

def splay(problem):
    output_dir = '../splay_output'
    source_dir = 'splay_test'
    target_dir = '../splay_target'

    cs.mkdir_empty(output_dir, logging_level=problem.logging_level)
    cs.mkdir_empty(target_dir, logging_level=problem.logging_level)

    test_sorted = sorted(os.listdir(source_dir))
    test_sorted = sorted(test_sorted, key=lambda fn: len(fn))
    test_sorted = [x.replace('.cpp', '') for x in test_sorted if x.find('.cpp') != -1]

    valgrind, norun, timeout, crashed, failed, passed = cs.run_gtest_in_dir(
        test_sorted,
        source_dir,
        output_dir,
        target_dir,
        compile_flags=problem.compile_flags,
        compile_file=problem.compile_file,
        use_valgrind=problem.use_valgrind,
        valgrind_file=problem.valgrind_file,
        timeout=problem.timeout,
        logging_level=problem.logging_level
    )

    if not problem.use_valgrind:
        valgrind = list()

    cs.write_test_result(
        problem.result_file,
        test_sorted, norun, timeout, crashed, failed, passed,
        logging_level=problem.logging_level)
    cs.write_formatted_result(
        problem.formatted_file,
        test_sorted, valgrind, norun, timeout, crashed, failed, passed,
        logging_level=problem.logging_level)

    if problem.remove_output:
        cs.mkdir_empty(output_dir, logging_level=problem.logging_level)
        cs.mkdir_empty(target_dir, logging_level=problem.logging_level)
        cs.remove_dir(output_dir)
        cs.remove_dir(target_dir)
