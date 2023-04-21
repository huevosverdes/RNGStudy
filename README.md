# Random Number Generation Study
A study of various topics in Random Number Generation (RNG). Code is provided in C, C++ and Python with no dependencies.

I conceptualize RNG in two parts:
1. The core which generates some number of random bits
2. The transformations that give us useful values from the random bits provided by the core

I could have made a fancy User Interface with Qt or OpenGL, but instead opted to keep things as simple as possible so anyone can build and run the examples in almost any environment. In this case, I used gcc and make. On Windows you can get this to run fairly simply by installing [MinGW](https://www.mingw-w64.org/downloads/) or [MSYS2](https://www.msys2.org/wiki/MSYS2-installation/).

Also, I know that the C++ input/output looks a lot like C-style input/output. This demo is not intended to be a full ideomatic translation. The input/output is not what I want to focus on, so there is quite a bit of copy/paste because it is easier.

## Core RNG
The main goal was to have random number generation cores that would always generate the same sequence of numbers no matter what language it was built in. I was inspired by the GBFlip paper which gives some testing values for a given seed at the first and 135th values generated. If you get the expected values, you coded it right. To the best of my ability I verified each core and provide value tests for each.

For this study I stuck with 31 bit signed integer cores. The transformations need to know what bits are being generated or they will not work correctly. For example, if we provide a 32 bit random number and put it into the 31 bit transformations, the results would be wrong. Also, I want all the cores to be interchangeable in the transformations as we explore various ideas. Some RNG cores here would normally generate 32 bits, so the most significant bit was stripped in these cases.

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

Also, for the interested student, the C versions of the cores show how inheritance, polymorphism and vtables work without an object oriented language.

## RNG Transformations
Usually 31 random bits aren't useful. Instead we want to get a random value in some range or do other things. Here we explore a few ideas:
- **Uniform Distribution**: Every value in the specified range is equally likely. Some other useful tidbits included here.
- **Normal Distribution**: This is a bell curve, with a mean and standard deviation. Also called a Gauss distrubution.
- **Vose Weighted Distribution**: Used for creating weighted dice or loot tables.
- **Perlin Noise**: Fancy noise creation used in many graphics applications.

## Demonstrations
- Coin Toss: Simple demonstration of a coin toss. This method is fairly efficient with 31 coin tosses per randomly generated number.
- [Shuffle](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle): Simple demonstration of shuffling. If you aren't careful you can accidentally bias your shuffle.
- [Uniform](https://en.wikipedia.org/wiki/Discrete_uniform_distribution) vs. [Normal](https://en.wikipedia.org/wiki/Normal_distribution): A side-by-side comparison of different random distributions.
- [Buffon's Needle](https://en.wikipedia.org/wiki/Buffon%27s_needle_problem): A probability problem with some interesting properties related to PI. We don't do the math, just an RNG simulation.
- [Monte Hall Problem](https://en.wikipedia.org/wiki/Monty_Hall_problem): A counterintuitive probability problem. We don't do the math, just an RNG simulation.
- [Chaos Game](https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle#Chaos_game): We use randomness to generate pretty pictures.
- [Points-In-Circle](https://programming.guide/random-point-within-circle.html): Uniform sampling of a radius can lead to non-uniform point distributions if we don't correct it.
- [Perlin Noise](https://en.wikipedia.org/wiki/Perlin_noise): This demo doesn't use RNG, but rather enables exploring some of the Perlin Noise parameters that you might vary with RNG.
