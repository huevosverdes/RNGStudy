#include "Utilities.h"

int getUserInt(int low, int high, const char *prompt, ...)
{
    int result;
    char *userInput = NULL;
    size_t bufferLen = 0;

    do {
        va_list args;
        va_start(args, prompt);
        vprintf(prompt, args);
        va_end(args);
        printf("\n> "); fflush(stdout);

        (void)getline(&userInput, &bufferLen, stdin);
        if((sscanf(userInput, "%d", &result) > 0) &&
           (low <= result && result <= high))
            break;

        free(userInput);
        userInput = NULL;
        bufferLen = 0;
        printf("That was either not an integer or not between %d and %d. Try again.\n", low, high); fflush(stdout);
    } while(1);
    free(userInput);

    assert(low <= result && result <= high);
    printf("\n");
    return result;
}

double getUserFlt(double low, double high, const char *prompt, ...)
{
    double result;
    char *userInput = NULL;
    size_t bufferLen = 0;

    do {
        va_list args;
        va_start(args, prompt);
        vprintf(prompt, args);
        va_end(args);
        printf("\n> "); fflush(stdout);

        (void)getline(&userInput, &bufferLen, stdin);
        if((sscanf(userInput, "%lf", &result) > 0) &&
           (low <= result && result <= high))
            break;

        free(userInput);
        userInput = NULL;
        bufferLen = 0;
        printf("That was either not a float or not between %f and %f. Try again.\n", low, high); fflush(stdout);
    } while(1);
    free(userInput);

    assert(low <= result && result <= high);
    printf("\n");
    return result;
}

RNG31::AbstractRNGCore *getRNGCore()
{
    int rngCoreIndex = getUserInt(
        1, 6,
        "Choose an RNG engine:\n"
        "  1. GBFlip\n"
        "  2. Linear Congruential\n"
        "  3. Isaac\n"
        "  4. Mersenne Twister\n"
        "  5. R250\n"
        "  6. R250/R521");

    switch(rngCoreIndex) {
    case 1:
        return new RNG31::GBFlip;
    case 2:
        return new RNG31::LinearCongruential;
    case 3:
        return new RNG31::Isaac;
    case 4:
        return new RNG31::MersenneTwister;
    case 5:
        return new RNG31::R250;
    case 6:
        return new RNG31::R250_R521;
    };

    return nullptr;
}

void message(double timeout, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\n");
    fflush(stdout);
    std::this_thread::sleep_for(std::chrono::milliseconds(int(timeout * 1000)));
}

void addSamplePoint(Image *img, int x, int y)
{
#define STEP 50
#define MAX (255 - STEP)

    Color c = img->at(y, x);

    if(c.blu() <= MAX)
        c.setBlu(c.blu() + STEP);
    else if(c.grn() <= MAX)
        c.setGrn(c.grn() + STEP);
    else if(c.red() <= MAX)
        c.setRed(c.red() + STEP);
    else
        c.set(0xFF, 0xFF, 0xFF);

    img->set(y, x, c);
}

void writeBMPImage(Image *img, char *fileNameFormat, ...)
{
    va_list args1, args2;
    va_start(args1, fileNameFormat);
    va_copy(args2, args1);
    int len = vsnprintf(NULL, 0, fileNameFormat, args1);
    va_end(args1);

    char *fileName = (char*)malloc(sizeof(char) * (len+2));
    vsnprintf(fileName, len+1, fileNameFormat, args2);
    va_end(args2);

    BMPWriter::write(fileName, img);
    printf("Wrote File: %s\n", fileName);
    free(fileName);
}
