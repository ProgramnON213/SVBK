from manim import *

class SimpsonsRule(Scene):
    def construct(self):
        # Axes setup
        axes = Axes(
            x_range=[0, 6, 1],
            y_range=[0, 8, 1],
            axis_config={"include_numbers": True}
        )
        labels = axes.get_axis_labels(x_label="x", y_label="f(x)")
        self.play(Create(axes), Write(labels))

        # Define the function f(x)
        def f(x):
            return 0.2*(x-1)*(x-5)*(x-6) + 6

        curve = axes.plot(f, color=BLUE)
        self.play(Create(curve), run_time=2)

        # Simpson’s Rule partition: 3 points (a, mid, b)
        a, b = 1, 5
        mid = (a + b) / 2

        # Dots on curve
        dots = VGroup(
            Dot(axes.c2p(a, f(a)), color=YELLOW),
            Dot(axes.c2p(mid, f(mid)), color=YELLOW),
            Dot(axes.c2p(b, f(b)), color=YELLOW)
        )
        self.play(FadeIn(dots))

        # Labels a, m, b
        labels = VGroup(
            MathTex("a").next_to(axes.c2p(a, 0), DOWN),
            MathTex(r"\frac{a+b}{2}").next_to(axes.c2p(mid, 0), DOWN),
            MathTex("b").next_to(axes.c2p(b, 0), DOWN)
        )
        self.play(Write(labels))

        # Parabola through (a, f(a)), (mid, f(mid)), (b, f(b))
        parabola_points = [axes.c2p(x, f(x)) for x in [a, mid, b]]
        parabola = CubicBezier(
            parabola_points[0],
            parabola_points[0] + UP * 1.5,
            parabola_points[2] + UP * 1.5,
            parabola_points[2],
            color=ORANGE
        )
        # Alternatively, use quadratic approximation
        simpson_curve = axes.plot(lambda x: f(a)
                                  + ((f(b)-f(a))/(b-a))*(x-a)
                                  - 0.25*(x-mid)**2,
                                  color=ORANGE)

        # Fill area under parabola (approximation)
        fill = axes.get_area(simpson_curve, x_range=[a, b], color=ORANGE, opacity=0.3)

        self.play(Create(simpson_curve), FadeIn(fill))
        self.wait(2)

        # Final text label
        text = MathTex(r"\text{Simpson's Rule: } \int_a^b f(x)dx \approx \frac{b-a}{6}\big[f(a)+4f\left(\tfrac{a+b}{2}\right)+f(b)\big]")
        text.to_edge(DOWN)
        self.play(Write(text))
        self.wait(3)