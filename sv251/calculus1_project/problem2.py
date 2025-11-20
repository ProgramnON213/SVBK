from manim import *
import numpy as np

# --- LỆNH KHAI BÁO DỮ LIỆU ---
# Một danh sách chứa các điểm (thời gian, nhiệt độ) từ bài toán.
temp_data = [
    (0, 66.0), (2, 65.5), (4, 64.0), (6, 62.0), (8, 66.5),
    (10, 71.0), (12, 75.0), (14, 78.0), (16, 79.5), (18, 75.0),
    (20, 75.5), (22, 71.5), (24, 67.0)
]

# --- LỆNH ĐỊNH NGHĨA CÔNG CỤ TÍNH TOÁN ---
# Một hàm để tìm công thức parabol đi qua 3 điểm cho trước.
def get_parabola_through_points(p1, p2, p3):
    x_coords = np.array([p1[0], p2[0], p3[0]])
    y_coords = np.array([p1[1], p2[1], p3[1]])
    A = np.array([
        [x_coords[0]**2, x_coords[0], 1],
        [x_coords[1]**2, x_coords[1], 1],
        [x_coords[2]**2, x_coords[2], 1]
    ])
    try:
        coeffs = np.linalg.solve(A, y_coords)
        a, b, c = coeffs
        return lambda x: a * x**2 + b * x + c
    except np.linalg.LinAlgError:
        return lambda x: 0

# --- LỆNH TẠO KỊCH BẢN CHÍNH ---
class SimpsonRuleTemperature(Scene):
    def construct(self):
        # -----------------------------------------------------------------
        # PHẦN 1: MINH HỌA ĐỒ THỊ
        # -----------------------------------------------------------------

        # 1. Thiết lập các đối tượng ban đầu
        title = Tex("Visualizing Simpson's Rule for Average Temperature").to_edge(UP)
        
        ax = Axes(
            x_range=[0, 24, 4], y_range=[50, 90, 10],
            x_length=10, y_length=5,
            axis_config={"color": BLUE},
        ).add_coordinates()
        
        axis_labels = ax.get_axis_labels(x_label="t (hours)", y_label=Tex(r"T (F)"))
        
        graph_group = VGroup(ax, axis_labels).shift(DOWN * 0.5)

        temperature_graph = VMobject().set_points_smoothly(
            [ax.c2p(t, temp) for t, temp in temp_data]
        ).set_color(RED)
        
        data_dots = VGroup(*[Dot(ax.c2p(t, temp), color=YELLOW) for t, temp in temp_data])

        part_one_mobjects = VGroup(title, graph_group, temperature_graph, data_dots)

        # 2. Dàn dựng hoạt ảnh theo thứ tự mới
        self.play(Write(title))
        self.play(Create(ax), Write(axis_labels))
        self.play(Create(temperature_graph), run_time=2)
        self.wait(1)

        delta_t_text = MathTex(
            r"\Delta t = \frac{24 - 0}{12} = 2 \, \text{(hours)}",
            font_size=40
        ).move_to(ax.c2p(7, 85))
        delta_t_text.add_background_rectangle(opacity=0.7) 

        self.play(Write(delta_t_text))
        self.wait(1)

        self.play(LaggedStart(*[FadeIn(dot, scale=0.6) for dot in data_dots], lag_ratio=0.1))
        self.wait(1)
        
        # === THAY ĐỔI Ở ĐÂY ===
        # Tạo đối tượng văn bản mới và biến đổi từ cái cũ
        approximation_text = Tex(
            "Approximate with parabolas", 
            font_size=42 # Cỡ chữ bự hơn
        ).move_to(delta_t_text.get_center()) # Đặt ở vị trí của delta_t
        approximation_text.add_background_rectangle(opacity=0.7)

        # Hoạt ảnh biến đổi từ delta_t thành approximation
        self.play(Transform(delta_t_text, approximation_text))
        self.wait(1) # Dừng một chút sau khi biến đổi
        
        # (Đối tượng delta_t_text bây giờ đã biến thành approximation_text)
        
        parabolic_areas = VGroup()
        for i in range(0, len(temp_data) - 2, 2):
            p1, p2, p3 = temp_data[i], temp_data[i+1], temp_data[i+2]
            parabola_func = get_parabola_through_points(p1, p2, p3)
            parabola_graph = ax.plot(parabola_func, x_range=[p1[0], p3[0]], color=YELLOW)
            area = ax.get_area(parabola_graph, x_range=[p1[0], p3[0]], color=YELLOW, opacity=0.5)
            self.play(Create(parabola_graph), FadeIn(area), run_time=0.5)
            parabolic_areas.add(parabola_graph, area)
        
        self.wait(2)
        # Thêm các đối tượng cần dọn dẹp vào nhóm chính
        part_one_mobjects.add(delta_t_text, parabolic_areas)

        # -----------------------------------------------------------------
        # PHẦN 2: TRÌNH BÀY PHÉP TÍNH
        # -----------------------------------------------------------------
        # (Phần này không thay đổi)

        self.play(FadeOut(part_one_mobjects))
        self.wait(1)

        graph_points = temperature_graph.get_points()
        bottom_left = ax.c2p(0, 50)
        bottom_right = ax.c2p(24, 50)
        area_points = np.concatenate([[bottom_left], graph_points, [bottom_right]])
        total_area = Polygon(*area_points, stroke_width=0, fill_color=GREEN, fill_opacity=0.7)
        small_graph = VGroup(ax, temperature_graph, total_area)
        small_graph.scale(0.6).to_edge(RIGHT, buff=0.5)

        calc_title = Tex("Calculation")
        calculation_tex = Tex(
            r"\begin{align*}"
            r"\overline{T} &= \frac{1}{24} \int_{0}^{24} T(t) \,dt \\"
            r"&\approx \frac{1}{24} \frac{2}{3} \left( T_0 + 4T_1 + \dots + T_{12} \right) \\"
            r"&\approx \frac{1}{36} \Big[ 66.0 + 4(65.5) + \dots \\"
            r"&\phantom{\approx \frac{1}{36} \Big[} + 4(71.5) + 67.0 \Big] \\"
            r"&\approx \frac{1}{36} (2546.0) \\"
            r"&\approx 70.72 \, \text{(F)}"
            r"\end{align*}",
            font_size=40
        )
        
        calc_group = VGroup(calc_title, calculation_tex).arrange(DOWN, buff=0.5)
        calc_group.to_corner(UL, buff=0.7)

        self.play(FadeIn(small_graph), Write(calc_group, run_time=8))
        self.wait(5)