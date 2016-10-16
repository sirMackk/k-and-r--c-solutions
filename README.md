## K&R C 2nd ed. Solutions

<img src="https://upload.wikimedia.org/wikipedia/en/5/5e/The_C_Programming_Language_cover.svg" width="300px" alt="Cover of K&R C" />

This repository contains the solutions to exercises from the 1988 classic "The C Programming Language" by [Brian Kernighan][1] and [Dennis Ritchie][2]. I had a lot of fun doing these and I hope they'll help someone who's stuck or who wants to compare their solution against mine.

There are two issues with this collections:

1. The exercises from chapter 1 are not numbered. Some contain the exercise number inside the file.
2. There are a few exercises missing: 5.18, 5.20 and potentially 1 or 3 more.

Aside from those issues, everything should compile and run. I used gcc *5.4.0 20160609* to compile everything with the *ansi* flag:

    gcc -Wall -ansi -o exercise exercise.c

If the compiler complains about missing the maths library, remember to use the `-lm` option!


[1]: https://en.wikipedia.org/wiki/Brian_Kernighan
[2]: https://en.wikipedia.org/wiki/Dennis_Ritchie
