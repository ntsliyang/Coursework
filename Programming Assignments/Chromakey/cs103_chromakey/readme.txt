CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name: Yang Li

Email Address: yli546@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | (69, 140, 20)    |  n/a
Arm                  | (235, 151, 105)  |  186.82
Vest                 | (23, 22, 20)     |  126.65
Shirt                | (255, 216, 243)  |  300.17

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: I choose the first 4 columns of pixels and first 4 rows of 
pixels, add up their RGB values, and calculate the average value to set 
as chromakey. As one of the test bmp files is astro.bmp, the top of 
astronaut's head is very close to the right of the frame. Therefore, 
choosing rightmost columns of pixels would result in inappropriate 
chromakey value. 

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2:

  Image                  Min Threshold           Max Threshold
  Colbert range:  from       75          to           85
  Bird range:     from       10          to           75


3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3: I would first determine which colors appears the most in 
one particular image so that I could individually process this image 
with 'if' statement later. Therefore, I firstly iterate over the whole 
image and calculate the number of times each color appears in the image. 
Then, by comparing the number of times a particular color that appears 
in an image with the number of times other colors appear in the image, 
I could specifically determine the processing of that particular color. 

Before applying this method, I also considered only using the green color 
to compare with other colors. However, by implementing this methodology, 
I found images with dominant red color, such as faded.bmp, did not change 
at all. Thus, I reconsidered the solutions and use more colors as subject 
of comparisons, thus resulting in my current method.

The pros of my method are that it could single out the most dominant 
color in an image and use that as the subject of comparison. So my 
method could both apply in all images with red, green, blue dominant 
colors.

However, the cons of my method are that it could only process images 
with uniform background. So for example, with regard to images such 
as astro.bmp or images with more complicated background, it might not 
work so well because it categorically considers the most dominant color.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: 3 hours.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: I really had no clue when I started the method 2, and I move the 
mouse on geeqie but I soon found the connection between three separate 
R, G, and B values. Therefore,I based my method on the relationship 
between R, G, and B values.

Do you have any other remarks?

: N/A
