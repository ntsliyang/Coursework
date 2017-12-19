CSCI 103 Programming Assignment 4, A Mazeing BFS

Name: Yang Li	

Email Address: yli546@usc.edu

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

:
=============================== Prelab ==================================

1. What data structure will you use to remember which cells have
already been added to the queue or not?

: 2D array of booleans, which has the data type of bool**.

2. At what step of the BFS algorithm do you have to mark a cell as visited?

: When I discover an unvisited, valid position that does not go over the 
bounds of rows and columns, I would firstly add this cell into the queue 
and mark it as visited by changing this cell from false to true.

=============================== Review ==================================

1. Describe your "mymaze.txt" test file. It should have multiple paths
of different distances. When you ran your program on it, did your program 
behave as expected?

: Yes. My mymaze.txt has multiple possible paths, and one marked with *
is the shortest amongst those. 

============================== Remarks ==================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: 5 hours.

Were there any specific problems you encountered? This is especially 
useful to know if you turned it in incomplete.

: I had difficulty in implementing BFS search and understanding which 
locations should be added in the queue at first. However, as I read the
instructions more times, I gradually understood different roles of variables
and successfully completed the program.

Do you have any other remarks?

: N/A.
