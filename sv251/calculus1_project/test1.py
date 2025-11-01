from manim import *

class SquareToCircle(Scene):
    def construct(self):
        square = Square()          # create a square
        self.play(Create(square))  # animate drawing
        self.wait(1)
        self.play(Transform(square, Circle()))  # morph square → circle
        self.wait(1)
