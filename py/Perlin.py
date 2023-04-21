from BMPWriter import BMPWriter
from Image import Image
from Color import Color

import Utilities
from Ease import Ease
from NoiseBuffer2D import NoiseBuffer2D
from RNG31Core.GBFlip import GBFlip
from RNG31Transform.Uniform import Uniform
from RNG31Transform.Perlin import Perlin

# Image Properties
WIDTH  = 256
HEIGHT = 256

def describe():
    Utilities.message(5.0, "Perlin noise has many uses in computer graphics: alpha blending, terrain height generation, color variation, and so much more.")
    Utilities.message(2.0, "Perlin noise lends itself to using randomness to create interesting variation.")
    Utilities.message(2.0, "This example doesn't actually use randomness.")
    Utilities.message(3.0, "Rather, this is a tool for exploring how the parameters change the resulting texture.")
    Utilities.message(3.0, "As you learn what the parameters do, you can randomize the ones you want to get a specific range of effects.\n")

    Utilities.message(5.0, "A brief description of what is happening is this: Perlin noise is sampling a pseudorandom 3D volume (generalizable to more dimensions).")
    Utilities.message(5.0, "  The x and y scale parameters are how tightly to sample the cube as we walk through a 2D slice of the volume. Bigger numbers mean higher-freqency noise.")
    Utilities.message(5.0, "  The z value describes where we walk through a 2D slice of the volume. Moving this up and down slightly can create wave-like progressions of textures.")
    Utilities.message(5.0, "  If the layer count is greater than one, we will add more noise on top of the previous layers. This can create more fractal-like affects.")
    Utilities.message(5.0, "    - Layer attentuation makes each succeeding layer have less strength, so the later layers are \"fainter\".")
    Utilities.message(5.0, "    - Layer scale makes each succeeding layer smaller to create that fractal feeling.")
    Utilities.message(3.0, "  Not usually part of a Perlin Noise discussion, I allow you to choose from different easing curves.")
    Utilities.message(2.0, "    - Normal Perlin Noise uses Smooth Step or Smoother Step. Some are more interesting than others.")
    Utilities.message(0.0, "")

    Utilities.message(0.0, "For more information: https://en.wikipedia.org/wiki/Perlin_noise\n")


def generatePerlinTexture(perlin, noise, img):
    fileName = makePerlinNoise(perlin, noise)
    encodeNoiseAsGrayscaleImage(noise, img)
    Utilities.writeBMPImage(img, fileName)


def makePerlinNoise(perlin, noise):
    fileName = ""

    xScale = Utilities.getUserFlt(0.125, 16.0, "X Scale (0.125 - 16.0)")
    yScale = Utilities.getUserFlt(0.125, 16.0, "Y Scale (0.125 - 16.0)")
    zValue = Utilities.getUserFlt(-1.0, 1.0, "Z Value (-1.0 - 1.0)")
    easingNumber = Utilities.getUserInt(
        1, 6,
        "Interpolation Method:\n"
        "  1. Smoother Step\n"
        "  2. Smooth Step\n"
        "  3. Linear\n"
        "  4. Quad In Out\n"
        "  5. Elastic In Out\n"
        "  6. Bounce In Out")

    easingMethod, easingMethodName = [
        (Ease.SMOOTHERSTEP, "SmootherStep"),
        (Ease.SMOOTHSTEP, "SmoothStep"),
        (Ease.LINEAR, "Linear"),
        (Ease.QUAD_IN_OUT, "QuadInOut"),
        (Ease.ELASTIC_IN_OUT, "ElasticInOut"),
        (Ease.BOUNCE_IN_OUT, "BounceInOut")][easingNumber - 1]
    perlin.setEasingMethod(easingMethod)

    layerCount = Utilities.getUserInt(1, 4, "Layer Count (1 - 4)")
    layerAttenuation = 0.5
    layerScale = 0.5

    if layerCount > 1:
        layerScale       = Utilities.getUserFlt(1.125, 8.0, "Layer Size Scale (1.125 - 8.0)")
        layerAttenuation = Utilities.getUserFlt(0.125, 0.875, "Layer Signal Attenuation (0.125 - 0.875)")

        perlin.layeredFill(noise, layerCount, layerScale, layerAttenuation, xScale, yScale, zValue)
        fileName = "Perlin_%s_%0.3f-%0.3f-%0.3f_%d-%0.3f%0.3f.bmp" % (
            easingMethodName,
            xScale,
            yScale,
            zValue,
            layerCount,
            layerScale,
            layerAttenuation)
    else:
        perlin.fill(noise, xScale, yScale, zValue)
        fileName = "Perlin_%s_%0.3f-%0.3f-%0.3f.bmp" % (
            easingMethodName,
            xScale,
            yScale,
            zValue)

    return fileName


def encodeNoiseAsGrayscaleImage(noise, img):
    assert(noise.width() == img.width())
    assert(noise.height() == img.height())

    c = Color()
    for row in range(noise.height()):
        for col in range(noise.width()):
            value = noise.at(row, col)
            c.setF(value, value, value, 1.0)
            img.set(row, col, c)


if __name__ == "__main__":
    img = Image(WIDTH, HEIGHT)
    img.fill(Color.BLK)

    gbFlip = GBFlip()
    urng = Uniform(gbFlip)
    perlin = Perlin(urng)
    noise = NoiseBuffer2D(WIDTH, HEIGHT)

    running = True
    while running:
        actionCode = Utilities.getUserInt(
            1, 3,
            "Would you like to continue?\n"
            "  1. Describe what this is\n"
            "  2. Generate a Perlin noise texture\n"
            "  3. Quit");

        if actionCode == 1:
            describe()
        elif actionCode == 2:
            generatePerlinTexture(perlin, noise, img)
        elif actionCode == 3:
            running = False

    exit(0)
