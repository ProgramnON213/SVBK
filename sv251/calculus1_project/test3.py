from manim import *
import numpy as np

class SimpsonsRule(Scene):
    def construct(self):
        # Title
        title = Text("Simpson's Rule", font_size=48)
        title.to_edge(UP)
        self.play(Write(title))
        self.wait()
        
        # Set up axes with labels
        axes = Axes(
            x_range=[0, 6, 1],
            y_range=[0, 6, 1],
            x_length=6,
            y_length=6,
            axis_config={"include_tip": True}
        )
        axes.shift(LEFT * 2 + DOWN * 0.5)
        
        # Add axis labels
        x_label = MathTex("x").next_to(axes.x_axis.get_end(), RIGHT)
        y_label = MathTex("y").next_to(axes.y_axis.get_end(), UP)
        
        # Define a simple function to integrate
        def func(x):
            return np.log(x)
        
        # Plot the function
        graph = axes.plot(func, color=BLUE, x_range=[0, 4])
        graph_label = MathTex("f(x)", color=BLUE).next_to(graph, UP)
        
        self.play(Create(axes), Write(x_label), Write(y_label), Create(graph), Write(graph_label))
        self.wait(1)
        
        # Define interval [a, b]
        a, b = 1, 5
        n = 2  # Number of subintervals (must be even for Simpson's)
        h = (b - a) / n
        
        # Mark points
        points = [a + i * h for i in range(n + 1)]
        dots = VGroup(*[
            Dot(axes.c2p(x, func(x)), color=RED)
            for x in points
        ])
        
        # Labels for points
        labels = VGroup(*[
            MathTex(f"x_{i}", font_size=30).next_to(
                axes.c2p(points[i], 0), DOWN
            )
            for i in range(len(points))
        ])
        
        self.play(Create(dots), Write(labels))
        self.wait()
        
        # Create parabolic segments
        parabolas = VGroup()
        for i in range(0, n, 2):
            # Three points for parabola
            x0, x1, x2 = points[i], points[i+1], points[i+2]
            y0, y1, y2 = func(x0), func(x1), func(x2)
            
            # Fit parabola through three points
            # Using Lagrange interpolation
            def parabola(x):
                L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2))
                L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2))
                L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1))
                return y0 * L0 + y1 * L1 + y2 * L2
            
            parab = axes.plot(
                parabola,
                x_range=[x0, x2],
                color=YELLOW,
                stroke_width=6
            )
            parabolas.add(parab)
        
        self.play(Create(parabolas))
        self.wait()
        
        # Show area under parabolas
        areas = VGroup()
        for i in range(0, n, 2):
            x0, x2 = points[i], points[i+2]
            x1 = points[i+1]
            
            def parabola(x):
                y0, y1, y2 = func(points[i]), func(points[i+1]), func(points[i+2])
                L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2))
                L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2))
                L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1))
                return y0 * L0 + y1 * L1 + y2 * L2
            
            area = axes.get_area(
                axes.plot(parabola, x_range=[x0, x2]),
                x_range=[x0, x2],
                color=GREEN,
                opacity=0.3
            )
            areas.add(area)
        
        self.play(FadeIn(areas))
        self.wait()
        
        # Simpson's Rule formula - positioned on the right
        formula = MathTex(
            r"\int_a^b f(x)\,dx \approx \frac{h}{3}[f(x_0) + 4f(x_1) + 2f(x_2) + ... + f(x_n)]",
            font_size=28
        )
        formula.shift(RIGHT * 3.5)
        formula_box = SurroundingRectangle(formula, color=WHITE, buff=0.2)
        
        self.play(Write(formula), Create(formula_box))
        self.wait(2)