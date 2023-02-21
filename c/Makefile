COMPILER = gcc
FLAGS = -Wall -g --std=c99
OBJS = AbstractRNG31Core.o				\
       RNG31Core_GBFlip.o				\
       RNG31Core_LinearCongruential.o	\
       RNG31Core_Isaac.o				\
       RNG31Core_MersenneTwister.o		\
       RNG31Core_R250.o					\
       RNG31Core_R250_R521.o			\
       RNG31_Uniform.o					\
       RNG31_Normal.o					\
       RNG31_Vose.o						\
       RNG31_Perlin.o					\
       Ease.o                           \
       Utilities.o

all : test BuffonsNeedle MonteHall
	./test.exe

# Tests/Examples
test : test.c $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

BuffonsNeedle : BuffonsNeedle.c $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

MonteHall : MonteHall.c $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

# Misc
Ease.o : Ease.h Ease.c
	$(COMPILER) $(FLAGS) $^ -c

Utilities.o : Utilities.h Utilities.c
	$(COMPILER) $(FLAGS) $^ -c

# 31-bit Random Number Transforms
RNG31_Uniform.o : RNG31Transform/RNG31_Uniform.h RNG31Transform/RNG31_Uniform.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31_Normal.o : RNG31Transform/RNG31_Normal.h RNG31Transform/RNG31_Normal.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31_Vose.o : RNG31Transform/RNG31_Vose.h RNG31Transform/RNG31_Vose.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31_Perlin.o : RNG31Transform/RNG31_Perlin.h RNG31Transform/RNG31_Perlin.c
	$(COMPILER) $(FLAGS) $^ -c

# 31-bit Random Number Generator Cores
RNG31Core_R250_R521.o : RNG31Core/RNG31Core_R250_R521.h RNG31Core/RNG31Core_R250_R521.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31Core_R250.o : RNG31Core/RNG31Core_R250.h RNG31Core/RNG31Core_R250.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31Core_MersenneTwister.o : RNG31Core/RNG31Core_MersenneTwister.h RNG31Core/RNG31Core_MersenneTwister.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31Core_Isaac.o : RNG31Core/RNG31Core_Isaac.h RNG31Core/RNG31Core_Isaac.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31Core_LinearCongruential.o : RNG31Core/RNG31Core_LinearCongruential.h RNG31Core/RNG31Core_LinearCongruential.c
	$(COMPILER) $(FLAGS) $^ -c

RNG31Core_GBFlip.o : RNG31Core/RNG31Core_GBFlip.h RNG31Core/RNG31Core_GBFlip.c
	$(COMPILER) $(FLAGS) $^ -c

AbstractRNG31Core.o : RNG31Core/AbstractRNG31Core.h RNG31Core/AbstractRNG31Core.c
	$(COMPILER) $(FLAGS) $^ -c

# Utilities
clean :
	rm -rf *.o *.gch *.exe *.stackdump RNG31Core/*.gch RNG31Transform/*.gch
