from manim import *
import numpy as np

# ------------------------------------------------------------
# ACCELERATION DATA FROM THE TABLE
# ------------------------------------------------------------
accel_data = [
    (0, 0.0),
    (1, 0.3),
    (2, 2.1),
    (3, 5.0),
    (4, 6.5),
    (5, 4.7),
    (6, 0.0),
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

class SimpsonAcceleration(Scene):
    def construct(self):
        # -----------------------------
        # AXES AND TITLE
        # -----------------------------
        title = Tex("Simpson's Rule: Increase in Velocity").to_edge(UP)

        ax = Axes(
            x_range=[0, 7, 1],
            y_range=[0, 7, 1],
            x_length=10,
            y_length=5,
            axis_config={"color": BLUE},
        ).add_coordinates()

        axis_labels = ax.get_axis_labels("t (s)", Tex("a(t)"))

        graph_group = VGroup(ax, axis_labels).shift(DOWN * 0.5)

        # -----------------------------
        # GRAPH OF a(t)
        # -----------------------------
        acceleration_graph = VMobject().set_points_smoothly(
            [ax.c2p(t, a) for t, a in accel_data]
        ).set_color(RED)

        data_dots = VGroup(*[
            Dot(ax.c2p(t, a), color=YELLOW)
            for t, a in accel_data
        ])

        self.play(Write(title))
        self.play(Create(ax), Write(axis_labels))
        self.play(Create(acceleration_graph), run_time=2)
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
        self.wait(0.5)

        # -----------------------------
        # DRAW SIMPSON SUBINTERVAL PARABOLAS
        # -----------------------------
        parabola_shapes = VGroup()

        for i in range(0, len(accel_data) - 2, 2):
            p1, p2, p3 = accel_data[i], accel_data[i + 1], accel_data[i + 2]
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

        self.play(FadeOut(VGroup(parabola_shapes, dt_text, acceleration_graph, data_dots)))
        self.play(FadeOut(VGroup(ax, axis_labels, title)))
        self.wait(0.5)

        # -----------------------------
        # SHOW CALCULATION STEPS
        # -----------------------------
        calc_title = Tex("Calculation")
        calc_text = MathTex(
            r"\int_0^{6} a(t)\,dt \approx \frac{1}{3}\left[ a_0 + 4a_1 + 2a_2 + 4a_3 + 2a_4 + 4a_5 + a_6 \right] \\[4pt]",
            r"\approx \frac{1}{3} \left[ 0 + 4(0.3) + 2(2.1) + 4(5.0) + 2(6.5) + 4(4.7) + 0 \right] \\[4pt]",
            r"= \frac{1}{3}(57.0) \\[4pt]",
            r"\approx 19.1\ \text{m/s}",
            font_size=36
        ).arrange(DOWN, aligned_edge=LEFT)
        
        calc_group = VGroup(calc_title, calc_text).arrange(DOWN, buff=0.5)
        calc_group.to_corner(UL, buff=0.7)

        self.play(Write(calc_group, run_time=8))
        self.wait(5)