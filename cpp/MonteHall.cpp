#include <cstdio>

#include "Utilities.h"
#include "RNG31Core/AbstractRNGCore.h"
#include "RNG31Transform/Uniform.h"

typedef enum {
    KEEP = 0,
    SWITCH = 1
} Strategy;

int revealDoor(RNG31::Uniform *urng, int porscheDoor, int selectedDoor);
int followStrategy(Strategy strategy, int selectedDoor, int revealedDoor);
int openDoor(RNG31::Uniform *urng, Strategy strategy);
void openDoors(RNG31::Uniform *urng, Strategy strategy, int roundCount, int *totalRounds, int *totalPorsches);

void openDoorInteractive(RNG31::Uniform *urng);
void openLotsOfDoors(RNG31::Uniform *urng);
void demo(RNG31::Uniform *urng);

int main(int argc, char **argv)
{
    RNG31::AbstractRNGCore *arng = getRNGCore();
    RNG31::Uniform *urng = new RNG31::Uniform(arng);
    int running = 1;
    do {
        int actionCode = getUserInt(
            1, 5,
            "Choose an action:\n"
            "  1. Choose an RNG Core\n"
            "  2. Give me the demo introduction to the Monte Hall Game\n"
            "  3. Play the Monte Hall Game for yourself\n"
            "  4. Simulate a lot of Monte Hall Games\n"
            "  5. Quit");
        switch(actionCode) {
        case 1:
            delete urng;
            delete arng;
            arng = getRNGCore();
            urng = new RNG31::Uniform(arng);
            break;
        case 2:
            demo(urng);
            break;
        case 3:
            openDoorInteractive(urng);
            break;
        case 4:
            openLotsOfDoors(urng);
            break;
        case 5:
            running = 0;
            break;
        }
    } while(running);

    delete urng;
    delete arng;
    return 0;
}

int revealDoor(RNG31::Uniform *urng, int porscheDoor, int selectedDoor)
{
    assert(1 <= porscheDoor && porscheDoor <= 3);
    assert(1 <= selectedDoor && selectedDoor <= 3);

    // Returns zero if there is an error (invalid input, i.e. invalid door number)
    int revealedDoor = 0;
    switch(selectedDoor) {
    case 1:
        switch(porscheDoor) {
        case 1: revealedDoor = urng->coinFlip() ? 2 : 3; break;
        case 2: revealedDoor = 3;                                   break;
        case 3: revealedDoor = 2;                                   break;
        };
        break;
    case 2:
        switch(porscheDoor) {
        case 1: revealedDoor = 3;                                   break;
        case 2: revealedDoor = urng->coinFlip() ? 1 : 3; break;
        case 3: revealedDoor = 1;                                   break;
        };
        break;
    case 3:
        switch(porscheDoor) {
        case 1: revealedDoor = 2;                                   break;
        case 2: revealedDoor = 1;                                   break;
        case 3: revealedDoor = urng->coinFlip() ? 1 : 2; break;
        };
        break;
    };

    assert(1 <= revealedDoor && revealedDoor <= 3);
    return revealedDoor;
}

int followStrategy(Strategy strategy, int selectedDoor, int revealedDoor)
{
    assert(strategy == KEEP || strategy == SWITCH);
    assert(1 <= selectedDoor && selectedDoor <= 3);
    assert(1 <= revealedDoor && revealedDoor <= 3);
    assert(selectedDoor != revealedDoor);

    if(strategy == KEEP)
        return selectedDoor;

    switch(selectedDoor) {
    case 1:
        switch(revealedDoor) {
        case 2: return 3;
        case 3: return 2;
        }
        break;
    case 2:
        switch(revealedDoor) {
        case 1: return 3;
        case 3: return 1;
        }
        break;
    case 3:
        switch(revealedDoor) {
        case 1: return 2;
        case 2: return 1;
        }
        break;
    }

    // Returns zero if there is an error (invalid input, i.e. invalid door number)
    return 0;
}

int openDoor(RNG31::Uniform *urng, Strategy strategy)
{
    int porscheDoor = urng->next(1, 4);
    int selectedDoor_round1 = urng->next(1, 4);
    int revealedDoor = revealDoor(urng, porscheDoor, selectedDoor_round1);
    int selectedDoor_round2 = followStrategy(strategy, selectedDoor_round1, revealedDoor);

    return selectedDoor_round2 == porscheDoor ? 1 : 0;
}

void openDoors(RNG31::Uniform *urng, Strategy strategy, int roundCount, int *totalRounds, int *totalPorsches)
{
    for(int count = 0; count < roundCount; ++count)
        (*totalPorsches) += openDoor(urng, strategy);
    (*totalRounds) += roundCount;
}

void demo(RNG31::Uniform *urng)
{
    message(3.0, "There is a game show where you are presented with three doors.");
    message(3.0, "There are goats hidding behind two of the doors.");
    message(3.0, "Behind the third door is hidden the real prize: a Porsche 911.");
    message(1.0, "");

    message(3.0, "In the first round of the game, you blindly select a door.");
    message(3.0, "The game host will then open one of the doors you did not select");
    message(3.0, "and that door will always reveal a goat.");
    message(1.0, "");

    message(3.0, "In the second round, you now can choose to keep the same door");
    message(3.0, "or you can choose to switch.");
    message(1.0, "");

    message(3.0, "If you played the game forever, how do you win the most Porsches?");
    message(3.0, "Or in other words: what strategy has the highest probability of winning?");
    message(1.0, "");

    message(3.0, "We could do a lot of math to figure it out ...");
    message(3.0, "or we could just simulate a lot of attempts with RNG.");
    message(1.0, "");
    message(3.0, "Let's open some doors ...\n");

    int strategyIndex = getUserInt(
        1, 2,
        "What strategy would you like to use for the second guess every round?\n"
        "  1. Stay with the first guess\n"
        "  2. Switch to the other door");
    --strategyIndex;
    Strategy strategy = static_cast<Strategy>(strategyIndex);

    int roundCount = 0;
    int porscheCount = 0;

    openDoors(urng, strategy, 10, &roundCount, &porscheCount);
    message(3.0, "We played %d rounds. %d times we found the Porsche. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    message(1.0, "Let's drop a few more ...\n");

    openDoors(urng, strategy, 90, &roundCount, &porscheCount);
    message(3.0, "Now we've played %d times. %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    message(1.0, "Let's keep going ...\n");

    openDoors(urng, strategy, 900, &roundCount, &porscheCount);
    message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    message(1.0, "Let's keep going ...\n");

    openDoors(urng, strategy, 9000, &roundCount, &porscheCount);
    message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    openDoors(urng, strategy, 90000, &roundCount, &porscheCount);
    message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    openDoors(urng, strategy, 900000, &roundCount, &porscheCount);
    message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    openDoors(urng, strategy, 9000000, &roundCount, &porscheCount);
    message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.\n", roundCount, porscheCount, 100.0 * porscheCount / roundCount);

    message(1.0, "Wait a minute ...");

    if(strategy == KEEP)
        message(2.0, "If we stay with our first guess, we find more goats than Porsches!\n");
    else
        message(2.0, "If we switch away from out first guess, we find more Porsches than goats!\n");

    message(0.0, "For more information: https://en.wikipedia.org/wiki/Monty_Hall_problem.\n");
}

void openDoorInteractive(RNG31::Uniform *urng)
{
    int porscheDoor = urng->next(1, 4);
    printf("Before you stand three closed doors. Behind one door is a Porsche 911. Behind the other two are goats.\n");
    fflush(stdout);

    int selectedDoor_round1 = getUserInt(1, 3, "Please select one of the doors (1-3):");

    const char *adjectives[] = {
        "firmly",
        "decidedly",
        "boldly",
        "tentatively",
        "hesitantly",
        "confidently",
        "doubtfully"};

    printf("You point %s at door %d.\n", adjectives[urng->next(0, 6)], selectedDoor_round1);
    fflush(stdout);

    int revealedDoor = revealDoor(urng, porscheDoor, selectedDoor_round1);
    printf("The game host steps to door %d and opens it, revealing a goat.\n", revealedDoor);
    fflush(stdout);

    int strategyIndex = getUserInt(
        1, 2,
        "Would you like to stay with door %d or switch to door %d?\n"
        "  1. Stay\n"
        "  2. Switch",
        selectedDoor_round1,
        followStrategy(SWITCH, selectedDoor_round1, revealedDoor));
    --strategyIndex;
    Strategy strategy = static_cast<Strategy>(strategyIndex);
    int selectedDoor_round2 = followStrategy(strategy, selectedDoor_round1, revealedDoor);
    int foundPorsche = selectedDoor_round2 == porscheDoor ? 1 : 0;

    printf("The host steps forward, pausing dramatically before door %d.\n", selectedDoor_round2); fflush(stdout);
    printf("He reaches out his hand to the doorknob, turning it slowly.\n"); fflush(stdout);
    printf("As the door swings open you see a ...\n"); fflush(stdout);
    if(foundPorsche)
        printf("shiny new Porsche 911. You won!!!\n");
    else
        printf("dirty smelly goat. You big loser.\n");
    printf("\n");
    fflush(stdout);
}

void openLotsOfDoors(RNG31::Uniform *urng)
{
    int strategyIndex = getUserInt(
        1, 2,
        "What strategy would you like to use for the second guess?\n"
        "  1. Stay with the first guess\n"
        "  2. Switch to the other door");
    --strategyIndex;
    Strategy strategy = static_cast<Strategy>(strategyIndex);

    int attempts = getUserInt(2, 1000000, "How many tries?");

    int porscheCount = 0;
    int roundCount = 0;
    openDoors(urng, strategy, attempts, &roundCount, &porscheCount);
    printf("Your strategy has won you %d Porsche 911s after %d attempts: %0.2f%% win rate\n\n",
           porscheCount,
           roundCount,
           100.0 * porscheCount / roundCount);
}
