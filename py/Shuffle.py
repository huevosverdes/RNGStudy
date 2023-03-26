from RNG31Core.GBFlip import GBFlip
from RNG31Transform.Uniform import Uniform


def printArray(array, prefix):
    print("%s Array:" % (prefix,))
    formatString = " - {%s}\n" % (", ".join(["%d"] * len(array)),)
    print(formatString % tuple(array))


gbFlip = GBFlip()
urng = Uniform(gbFlip)

count = 20
array = []
for index in range(count):
    array.append(index)

printArray(array, "Sorted")
urng.shuffle(array)
printArray(array, "Shuffled")
