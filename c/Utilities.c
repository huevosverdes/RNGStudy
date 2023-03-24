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
        printf("That was either not an integer or not between 1-3. Try again.\n"); fflush(stdout);
    } while(1);
    free(userInput);

    assert(low <= result && result <= high);
    printf("\n");
    return result;
}

AbstractRNG31Core *getRNGCore()
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
        RNG31Core_GBFlip *gbFlipRNG = (RNG31Core_GBFlip*)malloc(sizeof(RNG31Core_GBFlip));
        return gbFlip_initDefault(gbFlipRNG);
    case 2:
        RNG31Core_LinearCongruential *linCongRNG = (RNG31Core_LinearCongruential*)malloc(sizeof(RNG31Core_LinearCongruential));
        return linearCongruential_initDefault(linCongRNG);
    case 3:
        RNG31Core_Isaac *isaacRNG = (RNG31Core_Isaac*)malloc(sizeof(RNG31Core_Isaac));
        return isaac_initDefault(isaacRNG);
    case 4:
        RNG31Core_MersenneTwister *mtRNG = (RNG31Core_MersenneTwister*)malloc(sizeof(RNG31Core_MersenneTwister));
        return mersenneTwister_initDefault(mtRNG);
    case 5:
        RNG31Core_R250 *r250RNG = (RNG31Core_R250*)malloc(sizeof(RNG31Core_R250));
        return r250_initDefault(r250RNG);
    case 6:
        RNG31Core_R250_R521 *r250r521RNG = (RNG31Core_R250_R521*)malloc(sizeof(RNG31Core_R250_R521));
        return r250_r521_initDefault(r250r521RNG);
    };

    return NULL;
}

void message(double timeout, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\n");
    fflush(stdout);
    sleep(timeout);
}

void addSamplePoint(Image *img, int x, int y)
{
#define STEP 50
#define MAX (255 - STEP)

    Color c = image_colorAt(img, y, x);

    if(c.bytes[BLU_BYTE] <= MAX)
        c.bytes[BLU_BYTE] += STEP;
    else if(c.bytes[GRN_BYTE] <= MAX)
        c.bytes[GRN_BYTE] += STEP;
    else if(c.bytes[RED_BYTE] <= MAX)
        c.bytes[RED_BYTE] += STEP;
    else
        c.value = 0xFFFFFFFF;

    image_setPixel(img, y, x, c);
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

    bmp_write(fileName, img);
    printf("Wrote File: %s\n", fileName);
    free(fileName);
}
