# HW07 Tests

To run tests:

1. Copy `hw7-test` to `hw7` solution directory (i.e. `hw-username/hw7-test`).
1. Change directory to `hw-username/hw7-test`.
1. Run `make test`.
1. Test results are found at `hw7-test/results`. 
	1. `*_compile.txt` is the compilation result.
	1. `*_valgrind` is the valgrind result.
	1. `*_result.txt` is the test result.
	1. `*_formatted.txt` is also test result, but it's formatted and contains runtime information.
1. Individual test output are fount at `*_output` directories.

## BST and RotateBST

1. Executables for `bst` and `rotate` are found at `*_target` directories.

## Hypercube

1. Hypercube executable is found at `hw7-test/tests/hypercube`.
1. The start nodes is found at `hw7-test/tests/hypercube_test/start.txt`.
1. The permitted node files are found at `hw7-test/tests/hypercube_test`.