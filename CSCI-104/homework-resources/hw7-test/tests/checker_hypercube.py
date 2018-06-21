import os
import cs_grading as cs

def hypercube(problem):
    test = 'permitted'
    start = 'hypercube_test/start.txt'
    input_dir = 'hypercube_test/'
    sol_dir = 'hypercube_sol/'
    output_dir = '../hypercube_output/'
    target = 'hypercube'
    makefile_dir = '../../'

    if not cs.exist_file(start):
        cs.log_error('Failed to open start node file', problem.logging_level)
        return

    cs.mkdir_empty(output_dir, logging_level=problem.logging_level)

    test_names = sorted(os.listdir(input_dir))
    test_names = sorted(test_names, key=lambda fn: len(fn))
    test_names = [x.replace('.txt', '') for x in test_names if x.find(test) != -1]

    with open(start) as start_file:
        start_nodes = [x.strip() for x in start_file.readlines()]

    if len(test_names) != len(start_nodes):
        cs.log_error(
            'Found {} permitted files but {} start nodes'.format(
                str(len(test_names)), str(len(start_nodes))),
            logging_level=problem.logging_level)
        return

    input_files = [input_dir + x + '.txt' for x in test_names]
    output_files = [output_dir + x + '.txt' for x in test_names]
    solution_files = [sol_dir + x + '.txt' for x in test_names]

    test_args = list()
    for i in range(len(test_names)):
        cs.clean_file(output_files[i])
        test_args.append([start_nodes[i], input_files[i], '>', output_files[i]])

    cs.make_code(
        make_command=target,
        makefile_dir=makefile_dir,
        compile_file=problem.compile_file)
    cs.move_file(makefile_dir + target, './')
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

    if problem.remove_output:
        cs.mkdir_empty(output_dir, logging_level=problem.logging_level)
        cs.remove_dir(output_dir)
        cs.remove_file(target)
