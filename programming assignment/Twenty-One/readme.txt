1. CSCI 103 Twenty One Programming Assignment 

Name: **Yang Li**

Email Address: **yli546@usc.edu**

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

: **Discussion with roommates**

================================ Questions ==================================

1. Did you use the 'suit', 'type' and 'value' arrays? What functions are easier to implement when using these arrays? How do you use them?

: **I used all of these three arrays and I primarily used them in 'printCard' function and 'cardValue' function. In 'printCard' function, I called 'type' array and 'suit' array and used 'id' mod 13 to showcase the each desired element and 'id' divided by 13 to display four types of suits. In 'cardValue' function, I called 'value' array and used 'id' divided by 13 to indicate 13 different values.**

2. Did you add any additional functions to your implementation? If so briefly
describe how the functions improved your solution.

: **No.** 

3. There are many ways to shuffle the deck of cards. The method used in our
implementation generates a permutaion of the cards to shuffle. For an array of
size N, how many swap (exchange) operations does this algorithm do? Does the
algorithm require any extra memory to generate a permutation?

: **This algorithm would do (N-1) swap operations. It requires extra memory to store a 'temp' value for all the swap operations.**


================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: **5 hours.**

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: **I had difficulty understanding the use of 'hand[]' and 'numCards' initially, but I solved this problem by skipping this part and writing the 'main' function. Therefore, as I was writing the 'main' function, by thinking what I need, I gradually understood the use of these two variables.**

Do you have any other remarks?

: **No.**

