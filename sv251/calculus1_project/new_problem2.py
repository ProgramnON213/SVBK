from manim import *
import numpy as np

class SimpsonsRuleViz(Scene):
    def construct(self):
        
        x_vals = np.array([0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24])
        y_vals = np.array([24, 23, 22, 21, 22, 26, 28, 29, 29, 27, 26, 25, 24])
        
        
        problem_text = Tex(
            r"Estimate the average temperature in Ho Chi Minh City on November 28, 2025\\",
            r"using Simpson's Rule with $n=12$."
        ).scale(0.8)
        
        self.play(Write(problem_text))
        self.wait(2)
        self.play(FadeOut(problem_text))

        
        axes = Axes(
            x_range=[0, 25, 2],
            y_range=[0, 35, 5],
            axis_config={"include_numbers": True},
            x_length=10,
            y_length=6
        )
        
        
        labels = axes.get_axis_labels(x_label="Time (h)", y_label="Temp (^\circ C)")
        
        self.play(Create(axes), Write(labels))
        
        dots = VGroup()
        for x, y in zip(x_vals, y_vals):
            dot = Dot(axes.c2p(x, y), color=YELLOW, radius=0.08)
            dots.add(dot)
        
        self.play(LaggedStart(*[FadeIn(dot, scale=0.5) for dot in dots], lag_ratio=0.15))
        
        graph_curve = axes.plot_line_graph(x_vals, y_vals, line_color=BLUE_C, add_vertex_dots=False)
        self.play(Create(graph_curve), run_time=2)
        self.wait(1)

        
        delta_t_text = MathTex(r"\Delta t = \frac{b-a}{n} = \frac{24-0}{12} = 2").to_edge(UP)
        self.play(Write(delta_t_text))
        self.wait(1)
        
        v_lines = VGroup()
        for x in x_vals:
            line = axes.get_vertical_line(axes.c2p(x, 30), color=GRAY)
            line.set_stroke(width=2, opacity=0.5) 
            v_lines.add(line)
        
        self.play(Create(v_lines), run_time=1.5)
        self.play(graph_curve.animate.set_stroke(opacity=0.3))

        
        simpson_curves = VGroup()
        areas = VGroup()
        
        for i in range(0, len(x_vals)-1, 2):
            x_nodes = x_vals[i:i+3]
            y_nodes = y_vals[i:i+3]
            
            current_dots = VGroup(dots[i], dots[i+1], dots[i+2])
            self.play(current_dots.animate.set_color(RED).scale(1.2), run_time=0.2)
            
            coeffs = np.polyfit(x_nodes, y_nodes, 2)
            parabola_func = lambda x: coeffs[0]*x**2 + coeffs[1]*x + coeffs[2]
            
            parabola = axes.plot(parabola_func, x_range=[x_nodes[0], x_nodes[2]], color=ORANGE)
            area = axes.get_area(parabola, x_range=[x_nodes[0], x_nodes[2]], color=ORANGE, opacity=0.3)
            
            simpson_curves.add(parabola)
            areas.add(area)
            
            self.play(Create(parabola), FadeIn(area), run_time=0.8)
            self.play(current_dots.animate.set_color(YELLOW).scale(1/1.2), run_time=0.1)

        self.wait(1)
        self.play(FadeOut(delta_t_text))


        graph_group = VGroup(axes, dots, graph_curve, v_lines, simpson_curves, areas)
        
        
        self.play(
            FadeOut(labels), 
            graph_group.animate.scale(0.6).to_edge(LEFT).shift(UP*0.5)
        )
        
        
        calc_template = MathTex(
            r"S \approx \frac{\Delta t}{3} [ T_0 + 4T_1 + 2T_2 + \dots + T_n ]"
        ).scale(0.7).to_edge(RIGHT).shift(UP*2 + LEFT)
        
        calc_sub = MathTex(
            r"S \approx \frac{2}{3} [ 24 + 4(23) + 2(22) + \dots + 24 ]"
        ).scale(0.7).next_to(calc_template, DOWN, aligned_edge=LEFT)
        
        calc_result = MathTex(
            r"S \approx 604"
        ).scale(0.8).next_to(calc_sub, DOWN, aligned_edge=LEFT)
        
        avg_formula = MathTex(
            r"T_{avg} = \frac{1}{b-a} \int_{0}^{24} T(t) dt \approx \frac{S}{24}"
        ).scale(0.7).next_to(calc_result, DOWN*2, aligned_edge=LEFT)
        
        final_result = MathTex(
            r"T_{avg} \approx \frac{604}{24} \approx \mathbf{25.17^\circ C}"
        ).scale(0.9).next_to(avg_formula, DOWN, aligned_edge=LEFT).set_color(YELLOW)

        self.play(Write(calc_template))
        self.wait(1)
        self.play(Write(calc_sub))
        self.wait(1)
        self.play(Write(calc_result))
        self.wait(1)
        
        self.play(Write(avg_formula))
        self.wait(1)
        self.play(Write(final_result))
        self.play(Indicate(final_result))
        self.wait(3)