from manim import *
import numpy as np

# ------------------------------------------------------------
# SPEED DATA FROM THE TABLE
# ------------------------------------------------------------
speed_data = [
    (0, 6.94),
    (1, 8.33),
    (2, 10.00),
    (3, 11.67),
    (4, 12.50),
    (5, 12.22),
    (6, 11.11),
]

# Fit a parabola through 3 points (used for Simpson subintervals)
def parabola_through(p1, p2, p3):
    xs = np.array([p1[0], p2[0], p3[0]])
    ys = np.array([p1[1], p2[1], p3[1]])

    A = np.array([
        [xs[0] ** 2, xs[0], 1],
        [xs[1] ** 2, xs[1], 1],
        [xs[2] ** 2, xs[2], 1],
    ])
    try:
        a, b, c = np.linalg.solve(A, ys)
        return lambda x: a * x ** 2 + b * x + c
    except np.linalg.LinAlgError:
        return lambda x: 0

class SimpsonSpeed(Scene):
    def construct(self):
        # -----------------------------
        # AXES AND TITLE
        # -----------------------------
        title = Tex("Simpson's Rule: Distance Covered").to_edge(UP)

        ax = Axes(
            x_range=[0, 7, 1],
            y_range=[0, 14, 2],
            x_length=5,
            y_length=5,
            axis_config={"color": BLUE},
        ).add_coordinates()

        axis_labels = ax.get_axis_labels("t (s)", Tex("v(t)"))

        graph_group = VGroup(ax, axis_labels).shift(DOWN * 0.5)

        # -----------------------------
        # GRAPH OF a(t)
        # -----------------------------

        data_dots = VGroup(*[
            Dot(ax.c2p(t, a), color=YELLOW)
            for t, a in speed_data
        ])

        self.play(Write(title))
        self.play(Create(ax), Write(axis_labels))
        self.play(LaggedStart(*[
            FadeIn(dot, scale=0.6) for dot in data_dots
        ], lag_ratio=0.1))
        self.wait(0.5)

        # -----------------------------
        # SHOW Δt
        # -----------------------------
        dt_text = MathTex(
            r"\Delta t = 1\ \text{second}",
            font_size=40
        ).move_to(ax.c2p(4, 7.5))
        dt_text.add_background_rectangle(opacity=0.7)

        self.play(Write(dt_text))
        self.wait(0.5)

        # -----------------------------
        # TRANSFORM TO "Approximate with parabolas"
        # -----------------------------
        approx_text = Tex(
            "Approximate with parabolas",
            font_size=40
        ).move_to(dt_text.get_center())
        approx_text.add_background_rectangle(opacity=0.7)

        self.play(Transform(dt_text, approx_text))
        self.wait(1)
        self.play(FadeOut(dt_text))

        # -----------------------------
        # DRAW SIMPSON SUBINTERVAL PARABOLAS
        # -----------------------------
        parabola_shapes = VGroup()

        for i in range(0, len(speed_data) - 2, 2):
            p1, p2, p3 = speed_data[i], speed_data[i + 1], speed_data[i + 2]
            f = parabola_through(p1, p2, p3)

            parabola_graph = ax.plot(
                f,
                x_range=[p1[0], p3[0]],
                color=YELLOW
            )
            area = ax.get_area(
                parabola_graph,
                x_range=[p1[0], p3[0]],
                color=YELLOW,
                opacity=0.5
            )

            self.play(Create(parabola_graph), FadeIn(area), run_time=0.5)
            parabola_shapes.add(parabola_graph, area)

        self.wait(1)

        self.play(FadeOut(VGroup(parabola_shapes, data_dots)))
        self.play(FadeOut(VGroup(ax, axis_labels, title)))
        self.wait(0.5)

        # -----------------------------
        # SHOW CALCULATION STEPS
        # -----------------------------
        calc_title = Tex("Calculation")
        calc_text = MathTex(
            r"& x(6) - x(0) = \int_0^6{v(t)\,dt} \\", 
            r"& \approx \frac{\Delta x}{3}(v(0)+4v(1)+2v(2)+4v(3)+2v(4)+4v(5)+v(6)) \\", 
            r"& = \frac{1}{3}(6.94+4*8.33+2*10+4*11.67+2*12.5+4*12.22+11.11) \approx 63.98 \,(m)",
            font_size=36
        ).arrange(DOWN, aligned_edge=LEFT)
        
        calc_group = VGroup(calc_title, calc_text).arrange(DOWN, buff=0.5)
        calc_group.to_corner(UL, buff=0.7)

        self.play(Write(calc_group, run_time=8))
        self.wait(3)