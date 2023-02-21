# RNGStudy
A study of various topics in RNG. Code in C, C++ and Python. No libraries or dependencies needed.

I conceptualize two parts to random number generation:
1. The core RNG which generates some number of random bits
2. The RNG transformations that give us useful numbers

## Core RNG
The main goal was to have random number generation cores that would always generate the same sequence of numbers no matter what language it was built in. I was inspired by the GBFlip paper which gives some testing values for a given seed at the first and 135th values generated. If you get the expected values, you coded it right. To the best of my ability I verified each core and provide the same testing for each core.

For this study I stuck with 31 bit signed integers, so they will always be positive. The transformations need to know what bits are being generated or they will not work correctly and I want all the cores to be interchangeable in the transformations as we explore various ideas. Some RNG cores demonstrated here normally generate 32 bits, so the most significant bit was stripped in these cases.

Some of the cores are things I found in the far, dusty corners of the internet, while others are used today in popular languages and libraries:
- [GBFlip](https://tex.loria.fr/sgb/gb_flip.pdf)
- [Isaac](http://burtleburtle.net/bob/rand/isaac.html)
- [Linear Congruential](https://en.wikipedia.org/wiki/Linear_congruential_generator)
- [Mersenne Twister](https://en.wikipedia.org/wiki/Mersenne_Twister)
  - [ACM Paper](http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf)
  - [Value Testing](https://create.stephan-brumme.com/mersenne-twister/)
- [R250](http://faculty.uml.edu/jpropp/r250.c)
- [R250/R521](http://pythonlabtools.sourceforge.net/analysisdocs/html/a00152.html)

Any core that needs another RNG core to intialize itself uses the Linear Congruential core.

Also, for the interested student, the C versions of the cores show how polymorphism and vtables work without an object oriented language.

## RNG Transformations
Usually 31 random bits aren't useful. Instead we want to get a random value in some range or do other things. Here we explore a few ideas:
- **Uniform Distribution**: Every value in the specified range is equally likely. Some other useful tidbits included here.
- **Normal Distribution**: This is your bell curve, with a mean and standard deviation. Also called a Gauss distrubution.
- **Vose Weighted Distribution**: This is useful for creating weighted dice or loot tables.
- **Perlin Noise**: Fancy noise creation used in an awful lot of graphics applications.

## Demonstrations
- [Buffon's Needle](https://en.wikipedia.org/wiki/Buffon%%27s_needle_problem): A probability problem with some interesting properties related to PI. We don't do the math, just an RNG simulation.
- [Monte Hall Problem](https://en.wikipedia.org/wiki/Monty_Hall_problem): A counterintuitive probability problem. We don't do the math, just an RNG simulation.
