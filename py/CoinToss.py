from RNG31Core.GBFlip import GBFlip
from RNG31Transform.Uniform import Uniform

gbFlip = GBFlip()
urng = Uniform(gbFlip)

if urng.coinFlip():
    print("Heads")
else:
    print("Tails")
