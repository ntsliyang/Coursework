# HW01 Tests

+ General rules: the tests for each homework assignments are used to verify your correctness of solution, identify erros in your code and potentially raised regrade request. The tests in this folder are identical to those for your graders, you can use this as a cross reference with your grade report. 

#### Instruction

+ The answers for problem 1-3 are included in this `README.md`
+ For programming question, follow the following steps:
+ Copy the entire test folder under your `hw1` folder, use `cd` command to change to the test folder
+ Do `python hw1-checker.py` to run our automated grading script
+ The results are usually named `q#_results.txt` and `q#_valgrind.txt`
+ (Optional) You can toggle certain variables in `hw1-checker.py` to control the grading script, specified later


#### Important Files

+ [Grading Script](hw1-checker.py)

## Problem 1 Course Policy (10%)

#### Solution (2% each)
+ a) 1, 4
+ b) 2, 3, 4
+ c) 2, 3, 4, 5
+ d) 2
+ e) 2, 3, 4, 5


## Problem 2 Git (10%)

#### Solution (2% each)
+ a) 3
+ b) 1, 2
+ c) 1: `git add hw1q2b.cpp`
+ c) 2: `git log -3`
+ d) `git` will ask for a commit message since none was provided. This will open a file where a `commit` message can be entered. Once this is done, the commit command will record the changes to the repo. (Mentioning the change will be committed but not the missing commit message results in 1% deduction)
+ e) `git clone repo-url` (It is acceptable if students provide an actual url)

## Problem 4 Recursion (10%)

1. (3% total)
	+ Draw out the recursive call tree or any other explanation for why the array will be printed in order, one number per line.  No credit for merely stating what the output will be without an accompanying explanation.
2. (4% total)
	+ (2%) funcB fails to terminate when max < min.
	+ (2%) Explains why funcB always terminate for other input.  
3. (3% total)
	+ (1%) The array `a` at indices min to max (both inclusive) is printed, one number per line.
	+ (2%) Gave sufficient explanation for why that's the output.


## Problem 5 Recursion (Barry) (10%)

#### Important Files

+ Grading Script: [hw1-checker.py](hw1-checker.py)
+ Input Files: [input](q5_input/input.txt)

#### Run Instruction

`python hw1-checker.py`

+ You can toggle this test in `hw1-checker.py` by changing `run_p5_test`
+ The output would be located at `p5_result.txt` and `p5_valgrind.txt`

#### Test Cases

This problem split into 10 test cases, each consist of __1%__.

| Index | Test | Description |
|:--|:-:|:-:|
| 1 | 1 |  single digit   |
| 2 | 123 |  small increase   |
| 3 | 12345678 |  long increase |
| 4 | 11111111 |  same digit  |
| 5 | 1024 |  short non increase  |
| 6 | 98765431 |  long non increase  |
| 7 | 11223345 |  increase + same digit  |
| 8 | 55443321 |  long non increase  |
| 9 | 321 |  short non increase  |
| 10 | 0 |  zero  |

#### Additional Deductions

+ (-10%) Solution is not recursive or uses a loop in addition to recursive solution.


## Problem 6 Stream (10%)

#### Important Files

+ Grading Script: [hw1-checker.py](hw1-checker.py)

#### Run Instruction

`python hw1-checker.py`

+ You can toggle this test in `hw1-checker.py` by changing `run_p6_test`
+ The output would be located at `p6_result.txt` and `p6_valgrind.txt`

#### Test Cases

This problem is split into 10 test cases, each consist of __1%__.

| Index | Description |
|:--|:-:|
| 1 | empty |
| 2 | one word |
| 3 | 3 words |
| 4 | 9 words change lines |
| 5 | single characters |
| 6 | special characters |
| 7 | random test 100 |
| 8 | random test 1000 |
| 9 | random test 10000 |
| 10 | random test 10000 |

#### Additional Deductions

+ (-10%) Solution is not recursive or uses a loop for purposes other than to read the input.
+ (-10%) Uses stl container or dynamically allocated array.


## Problem 7 Game of Pointers (50%)

#### Important Files

+ Grading Script: [hw1-checker.py](hw1-checker.py)

#### Run Instruction

`python hw1-checker.py`

+ You can toggle this test in `hw1-checker.py` by changing `run_p7_test`
+ The output would be located at `got_result.txt` and `got_valgrind.txt`

### Point Distribution

This problem is split into 16 test cases, each of __2.5%__ (40% total) and __10%__ code review.

#### Test Cases

| Index | Description |
|:--|:-:|
|1 | Sample input  |
|2 | Simple duel test |
|3 | Out of bound test |
|4 | Simple duel test 2  |
|5 | Wrap in the reserve warrior  |
|6 | Exhaust the reserve warrior (invader finally win) |
|7 | Exhaust the invader  |
|8 | Test the power of defect warrior  |
|9 | No assult |
|10 | More defect |
|11 | No open space, protector dies |
|12 | A rather comprehensive case, invader win |
|13 | Protector die, wrap in reserve |
|14 | Check reserve warrior's power |
|15 | Invader immediately win and terminate |
|16 | Large input |

#### Additional Deductions

+ (-50%) Solution uses `vector` or any stl container.
+ (Up to -20%) Take half of the tests points off of test cases for which they have valgrind errors (memory leak, invalid read, jump based on unitialized value, etc).


### If you found any bug or problems with the grading files, please don't hesitate to contact the head CPs immediately at ziyanma@usc.edu (and cc' shermand@usc.edu, bcen@usc.edu, cynthiaz@usc.edu)

### If you have trouble running our grading script, feel free to post on piazza, tag your grader in github issue or find us in office hour. 
