from manim import *

class AccelerationData(Scene):
    def construct(self):
        # Axes
        axes = Axes(
            x_range=[0, 7, 1],
            y_range=[0, 8, 1],
            x_length=6,
            y_length=6,
            axis_config={"include_numbers": True},
        )
        labels = axes.get_axis_labels(x_label="\\text{Time (s)}", y_label="a\\,(m/s^2)")
        self.play(Create(axes), Write(labels))
        self.wait(0.5)

        # Data points (time, acceleration)
        data = [
            (0, 0),
            (1, 0.3),
            (2, 2.1),
            (3, 5.0),
            (4, 6.5),
            (5, 4.7),
            (6, 0)
        ]

        # Plot points
        dots = VGroup(*[
            Dot(axes.c2p(x, y), color=YELLOW)
            for x, y in data
        ])
        self.play(LaggedStartMap(FadeIn, dots, lag_ratio=0.1))
        self.wait(0.5)

        # Label each point with coordinates
        labels = VGroup(*[
            MathTex(f"({x}, {y})").scale(0.5).next_to(axes.c2p(x, y), UP)
            for x, y in data
        ])
        self.play(LaggedStartMap(Write, labels, lag_ratio=0.1))
        self.wait(1)
        self.play(FadeOut(labels))

        # --- Parabola through first 3 points ---
        pts = data[:3]
        x_vals, y_vals = zip(*pts)

        # Solve for a, b, c in y = a*x^2 + b*x + c
        A = np.array([[x**2, x, 1] for x in x_vals])
        B = np.array(y_vals)
        a, b, c = np.linalg.solve(A, B)

        # Define the fitted quadratic
        def parabola(x):
            return a*x**2 + b*x + c

        # Plot only between x=0 and x=2
        curve = axes.plot(parabola, x_range=[0, 2], color=WHITE, stroke_width=1)
        self.play(Create(curve), run_time=2)
        area = axes.get_area(curve, x_range=[0, 2], color=BLUE, opacity=0.4)
        self.play(FadeIn(area), run_time=2)
        self.wait(1)
        
        # --- Parabola through points 2 to 4 ---
        pts2 = data[2:5]
        x_vals2, y_vals2 = zip(*pts2)

        A2 = np.array([[x**2, x, 1] for x in x_vals2])
        B2 = np.array(y_vals2)
        a2, b2, c2 = np.linalg.solve(A2, B2)

        def parabola2(x):
            return a2*x**2 + b2*x + c2

        # --- Parabola through points 2 to 4 ---
        curve2 = axes.plot(parabola2, x_range=[2, 4], color=WHITE, stroke_width=1)
        self.play(Create(curve2), run_time=2)
        area2 = axes.get_area(curve2, x_range=[2, 4], color=BLUE, opacity=0.4)
        self.play(FadeIn(area2), run_time=2)
        self.wait(1)

        # --- Parabola through points 4 to 6 ---
        pts3 = data[4:]
        x_vals3, y_vals3 = zip(*pts3)

        A3 = np.array([[x**2, x, 1] for x in x_vals3])
        B3 = np.array(y_vals3)
        a3, b3, c3 = np.linalg.solve(A3, B3)

        def parabola3(x):
            return a3*x**2 + b3*x + c3

        # --- Parabola through points 4 to 6 ---
        curve3 = axes.plot(parabola3, x_range=[4, 6], color=WHITE, stroke_width=1)
        self.play(Create(curve3), run_time=2)
        area3 = axes.get_area(curve3, x_range=[4, 6], color=BLUE, opacity=0.4)
        self.play(FadeIn(area3), run_time=2)
        self.wait(1)

        self.wait(3)