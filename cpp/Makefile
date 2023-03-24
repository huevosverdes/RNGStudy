COMPILER = g++
FLAGS = -Wall -g --std=c++20
OBJS = AbstractRNGCore.o	\
       GBFlip.o				\
       LinearCongruential.o	\
       Isaac.o				\
       MersenneTwister.o	\
       R250.o				\
       R250_R521.o			\
       Uniform.o			\
       Normal.o				\
       Vose.o				\
       Perlin.o				\
       Ease.o				\
       Color.o				\
       Image.o				\
       NoiseBuffer2D.o      \
       BMPWriter.o          \
       Utilities.o

all : test BuffonsNeedle MonteHall ChaosGame CoinToss UniformVsNormal PointsInACircle
	./test.exe

# Tests/Examples
test : test.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

BuffonsNeedle : BuffonsNeedle.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

MonteHall : MonteHall.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

ChaosGame : ChaosGame.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

CoinToss : CoinToss.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

UniformVsNormal : UniformVsNormal.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

PointsInACircle : PointsInACircle.cpp $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@.exe

# Misc
Ease.o : Ease.h Ease.cpp
	$(COMPILER) $(FLAGS) $^ -c

Utilities.o : Utilities.h Utilities.cpp
	$(COMPILER) $(FLAGS) $^ -c

Color.o : Color.h Color.cpp
	$(COMPILER) $(FLAGS) $^ -c

Image.o : Image.h Image.cpp
	$(COMPILER) $(FLAGS) $^ -c

NoiseBuffer2D.o : NoiseBuffer2D.h NoiseBuffer2D.cpp
	$(COMPILER) $(FLAGS) $^ -c

BMPWriter.o : BMPWriter.h BMPWriter.cpp
	$(COMPILER) $(FLAGS) $^ -c

# 31-bit Random Number Transforms
Uniform.o : RNG31Transform/Uniform.h RNG31Transform/Uniform.cpp
	$(COMPILER) $(FLAGS) $^ -c

Normal.o : RNG31Transform/Normal.h RNG31Transform/Normal.cpp
	$(COMPILER) $(FLAGS) $^ -c

Vose.o : RNG31Transform/Vose.h RNG31Transform/Vose.cpp
	$(COMPILER) $(FLAGS) $^ -c

Perlin.o : RNG31Transform/Perlin.h RNG31Transform/Perlin.cpp
	$(COMPILER) $(FLAGS) $^ -c

# 31-bit Random Number Generator Cores
R250_R521.o : RNG31Core/R250_R521.h RNG31Core/R250_R521.cpp
	$(COMPILER) $(FLAGS) $^ -c

R250.o : RNG31Core/R250.h RNG31Core/R250.cpp
	$(COMPILER) $(FLAGS) $^ -c

MersenneTwister.o : RNG31Core/MersenneTwister.h RNG31Core/MersenneTwister.cpp
	$(COMPILER) $(FLAGS) $^ -c

Isaac.o : RNG31Core/Isaac.h RNG31Core/Isaac.cpp
	$(COMPILER) $(FLAGS) $^ -c

LinearCongruential.o : RNG31Core/LinearCongruential.h RNG31Core/LinearCongruential.cpp
	$(COMPILER) $(FLAGS) $^ -c

GBFlip.o : RNG31Core/GBFlip.h RNG31Core/GBFlip.cpp
	$(COMPILER) $(FLAGS) $^ -c

AbstractRNGCore.o : RNG31Core/AbstractRNGCore.h RNG31Core/AbstractRNGCore.cpp
	$(COMPILER) $(FLAGS) $^ -c

clean :
	rm -rf *.o *.gch *.bmp *.exe *.stackdump RNG31Core/*.gch RNG31Transform/*.gch
