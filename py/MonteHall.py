import sys
import math

import Utilities
from RNG31Transform.Uniform import Uniform

KEEP = 0
SWITCH = 1


def revealDoor(urng, porscheDoor, selectedDoor):
    assert(1 <= porscheDoor and porscheDoor <= 3);
    assert(1 <= selectedDoor and selectedDoor <= 3);

    revealedDoor = 0
    revealedDoor = [[2 if urng.coinFlip() else 3,
                     3,
                     2],
                    [3,
                     1 if urng.coinFlip() else 3,
                     1],
                    [2,
                     1,
                     1 if urng.coinFlip() else 2]][selectedDoor - 1][porscheDoor - 1]

    assert(1 <= revealedDoor and revealedDoor <= 3)
    return revealedDoor

def followStrategy(strategy, selectedDoor, revealedDoor):
    assert(strategy == KEEP or strategy == SWITCH)
    assert(1 <= selectedDoor and selectedDoor <= 3)
    assert(1 <= revealedDoor and revealedDoor <= 3)
    assert(selectedDoor != revealedDoor)

    if strategy == KEEP:
        return selectedDoor

    # Returns zero if there is an error (invalid input, i.e. invalid door number)
    return [[0, 3, 2],
            [3, 0, 1],
            [2, 1, 0]][selectedDoor - 1][revealedDoor - 1]


def openDoor(urng, strategy):
    porscheDoor = urng.next(1, 4)
    selectedDoor_round1 = urng.next(1, 4)
    revealedDoor = revealDoor(urng, porscheDoor, selectedDoor_round1)
    selectedDoor_round2 = followStrategy(strategy, selectedDoor_round1, revealedDoor)

    return selectedDoor_round2 == porscheDoor


def openDoors(urng, strategy, roundCount, totalRounds, totalPorsches):
    for count in range(roundCount):
        totalPorsches += 1 if openDoor(urng, strategy) else 0
    totalRounds += roundCount
    return totalRounds, totalPorsches


def demo(urng):
    Utilities.message(3.0, "There is a game show where you are presented with three doors.");
    Utilities.message(3.0, "There are goats hidding behind two of the doors.");
    Utilities.message(3.0, "Behind the third door is hidden the real prize: a Porsche 911.");
    Utilities.message(1.0, "");

    Utilities.message(3.0, "In the first round of the game, you blindly select a door.");
    Utilities.message(3.0, "The game host will then open one of the doors you did not select");
    Utilities.message(3.0, "and that door will always reveal a goat.");
    Utilities.message(1.0, "");

    Utilities.message(3.0, "In the second round, you now can choose to keep the same door");
    Utilities.message(3.0, "or you can choose to switch.");
    Utilities.message(1.0, "");

    Utilities.message(3.0, "If you played the game forever, how do you win the most Porsches?");
    Utilities.message(3.0, "Or in other words: what strategy has the highest probability of winning?");
    Utilities.message(1.0, "");

    Utilities.message(3.0, "We could do a lot of math to figure it out ...");
    Utilities.message(3.0, "or we could just simulate a lot of attempts with RNG.");
    Utilities.message(1.0, "");
    Utilities.message(3.0, "Let's open some doors ...\n");

    strategy = Utilities.getUserInt(
        1, 2,
        "What strategy would you like to use for the second guess every round?\n"
        "  1. Stay with the first guess\n"
        "  2. Switch to the other door");
    strategy -= 1

    roundCount = 0;
    porscheCount = 0;

    roundCount, porscheCount = openDoors(urng, strategy, 10, roundCount, porscheCount);
    Utilities.message(3.0, "We played %d rounds. %d times we found the Porsche. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    Utilities.message(1.0, "Let's drop a few more ...\n");

    roundCount, porscheCount = openDoors(urng, strategy, 90, roundCount, porscheCount);
    Utilities.message(3.0, "Now we've played %d times. %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    Utilities.message(1.0, "Let's keep going ...\n");

    roundCount, porscheCount = openDoors(urng, strategy, 900, roundCount, porscheCount);
    Utilities.message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    Utilities.message(1.0, "Let's keep going ...\n");

    roundCount, porscheCount = openDoors(urng, strategy, 9000, roundCount, porscheCount);
    Utilities.message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    roundCount, porscheCount = openDoors(urng, strategy, 90000, roundCount, porscheCount);
    Utilities.message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    roundCount, porscheCount = openDoors(urng, strategy, 900000, roundCount, porscheCount);
    Utilities.message(3.0, "%d rounds played with %d Porsches found. The probability is %0.4f%%.", roundCount, porscheCount, 100.0 * porscheCount / roundCount);
    print("")

    Utilities.message(1.0, "Wait a minute ...");

    if strategy == KEEP:
        Utilities.message(2.0, "If we stay with our first guess, we find more goats than Porsches!\n");
    else:
        Utilities.message(2.0, "If we switch away from out first guess, we find more Porsches than goats!\n");

    Utilities.message(0.0, "For more information: https://en.wikipedia.org/wiki/Monty_Hall_problem.");

    print("")
    sys.stdout.flush()


def openDoorInteractive(urng):
    porscheDoor = urng.next(1, 4)
    print("Before you stand three closed doors. Behind one door is a Porsche 911. Behind the other two are goats.")

    selectedDoor_round1 = Utilities.getUserInt(1, 3, "Please select one of the doors (1-3):")

    adjectives = [
        "firmly",
        "decidedly",
        "boldly",
        "tentatively",
        "hesitantly",
        "confidently",
        "doubtfully"]

    print("You point %s at door %d." % (adjectives[urng.next(0, 6)], selectedDoor_round1))

    revealedDoor = revealDoor(urng, porscheDoor, selectedDoor_round1)
    print("The game host steps to door %d and opens it, revealing a goat.\n" % (revealedDoor,))

    strategy = Utilities.getUserInt(
        1, 2,
        ("Would you like to stay with door %d or switch to door %d?\n" % (
            selectedDoor_round1,
            followStrategy(SWITCH, selectedDoor_round1, revealedDoor))) +
        "  1. Stay\n" +
        "  2. Switch")
    strategy -= 1
    selectedDoor_round2 = followStrategy(strategy, selectedDoor_round1, revealedDoor)
    foundPorsche = selectedDoor_round2 == porscheDoor

    print("The host steps forward, pausing dramatically before door %d." % (selectedDoor_round2,));
    print("He reaches out his hand to the doorknob, turning it slowly.");
    print("As the door swings open you see a ...");
    if foundPorsche:
        print("shiny new Porsche 911. You won!!!");
    else:
        print("dirty smelly goat. You big loser.");

    print("")
    sys.stdout.flush()


def openLotsOfDoors(urng):
    strategy = Utilities.getUserInt(
        1, 2,
        "What strategy would you like to use for the second guess?\n" +
        "  1. Stay with the first guess\n" +
        "  2. Switch to the other door")
    strategy -= 1

    attempts = Utilities.getUserInt(2, 100000, "How many tries?");

    roundCount = 0;
    porscheCount = 0;
    roundCount, porscheCount = openDoors(urng, strategy, attempts, roundCount, porscheCount);
    print("Your strategy has won you %d Porsche 911s after %d attempts: %0.2f%% win rate" % (
        porscheCount,
        roundCount,
        100.0 * porscheCount / roundCount))

    print("")
    sys.stdout.flush()


if __name__ == "__main__":
    arng = Utilities.getRNGCore()
    urng = Uniform(arng)

    running = True;
    while running:
        actionCode = Utilities.getUserInt(
            1, 5,
            "Choose an action:\n" +
            "  1. Choose an RNG Core\n" +
            "  2. Give me the demo introduction to the Monte Hall Game\n" +
            "  3. Play the Monte Hall Game for yourself\n" +
            "  4. Simulate a lot of Monte Hall Games\n" +
            "  5. Quit");
        if actionCode == 1:
            arng = Utilities.getRNGCore()
            urng = Uniform(arng)
        elif actionCode == 2:
            demo(urng);
        elif actionCode == 3:
            openDoorInteractive(urng)
        elif actionCode == 4:
            openLotsOfDoors(urng)
        elif actionCode == 5:
            running = False

    exit(0)
