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
    // std::this_thread::sleep_for(std::chrono::milliseconds(int(timeout * 1000)));
}
