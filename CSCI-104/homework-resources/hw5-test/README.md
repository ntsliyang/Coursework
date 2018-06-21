# HW05 Test

## Setting Up

copy the entire folder of `hw5-test` into your `hw5` directory, move to your `hw5-test` directory

## Running Test 

run `python hw5-checker.py` under `hw5-test` folder to run the automated testing script. You can toggle `run_[problem]` variable in the script to run each test individually. The result would be saved at `[problem]_results.txt` and `[problem]_valgrind.txt`


## Runtime Tests

The runtime for quicksort should be `nlogn`, By this, Test 11-13 should show a linear-log increase, we expect the last test (Test13) to be finished in one minute. For example: 

```
[       OK ] QSortTest.Test11 (145 ms)
[ RUN      ] QSortTest.Test12
[       OK ] QSortTest.Test12 (1440 ms)
[ RUN      ] QSortTest.Test13
[       OK ] QSortTest.Test13 (16212 ms)
```  

The runtime for `assignPlates` should be `nlogn`, By this, Test 9-11 should show a linear-log increase, we expect the last test (Test13) to be finished in one minute. For example: 
```
[ RUN      ] ThanksgivingTest.Test9
[       OK ] ThanksgivingTest.Test9 (156 ms)
[ RUN      ] ThanksgivingTest.Test10
[       OK ] ThanksgivingTest.Test10 (1103 ms)
[ RUN      ] ThanksgivingTest.Test11
[       OK ] ThanksgivingTest.Test11 (14130 ms)
```

## Additional Notes
We realized our runtime test for graders might be too large. If you encountered an unexpected deduction for quicksort runtime, please let us know and paste your excution result under the issue. 