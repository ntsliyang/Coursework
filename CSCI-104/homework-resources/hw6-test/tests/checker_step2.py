import cs_grading as cs
import os

def step2(problem):
    config_dir = 'config/step2/'
    sol_dir = 'solution/'
    output_dir = '../student_output/'
    target = 'search'
    makefile_dir = '../../'

    test_names = sorted(os.listdir(config_dir))
    test_names = sorted(test_names, key=lambda fn: len(fn))
    test_names = [x.replace('.in', '') for x in test_names]
    
    input_files = [config_dir + x + '.in' for x in test_names]
    output_files = [output_dir + x + '.out' for x in test_names]
    solution_files = [sol_dir + x + '.out' for x in test_names]

    test_args = list()
    for i in range(len(input_files)):
        test_args.append([input_files[i]])

    target = cs.fix_executable_path(target)

    valgrind, norun, timeout, finished = cs.run_tests_in_list(
        target,
        test_names,
        test_args,
        use_valgrind=problem.use_valgrind,
        valgrind_file=problem.valgrind_file,
        timeout=problem.timeout,
        logging_level=problem.logging_level)

    failed, passed = cs.check_test_output(
        test_names,
        solution_files,
        output_files,
        problem.result_file,
        ordered_compare=True,
        skip_white_space=True,
        detailed_results=problem.detailed_results,
        logging_level=problem.logging_level)

    failed, passed = cs.get_test_runtime(finished, failed, passed)
    crashed = set()
    if not problem.use_valgrind:
        valgrind = list()

    cs.write_test_result(
        problem.result_file,
        test_names, norun, timeout, crashed, failed, passed,
        final_log=True, logging_level=problem.logging_level)
    cs.write_formatted_result(
        problem.formatted_file,
        test_names, valgrind, norun, timeout, crashed, failed, passed,
        logging_level=problem.logging_level)
