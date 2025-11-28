from manim import *
class Ex_37(Scene):
    def construct(self):
        text=Tex(r"""\large
37. The table gives the power consumption in megawatts in Ontario from midnight to 6:00 AM on December 10, 2004. Use Simpson's Rule to estimate the energy used during that time period. (Use the fact that power is the derivative of energy.)
""",font_size=25)
        text.to_edge(UP)
        table=Tex(r"""\begin{tabular}{|c|c|}
\hline
   t  & P (MW)  \\
\hline
  0:00 & 17,888\\
\hline
    0:30 & 17,398\\
\hline
1:00 & 17,110\\
\hline
1:30 & 16,881\\
\hline
 2:00&16,832\\\hline
 2:30&16,950\\\hline
 3:00&16,833\\\hline
 3:30&16,835\\\hline
 4:00&17,065\\\hline
 4:30&17,264\\\hline
 5:00&17,577\\\hline
 5:30&17,992\\\hline
 6:00&18,216\\\hline

    
\end{tabular}""", font_size=25)
        table.next_to(text,DOWN)
        self.play(Create(text),run_time=3)
        self.play(Create(table),run_time=2)
        self.wait()
        self.play(FadeOut(text),table.animate.to_corner(UL),run_time=2)
        plane=NumberPlane(x_range=[-1.01,7.01],y_range=[-1.01,4.01],axis_config={"include_tip":True,"tip_shape":StealthTip,"tip_width":0.1,"tip_height":0.1}).add_coordinates()
        plane.to_edge(RIGHT,buff=1)
        plane.scale(1.1)
        labelx=plane.get_x_axis_label(label=MathTex(r"t(h)",font_size=25))
        labelx.next_to(plane,RIGHT,buff=0.1)
        labelx.shift([0,-1.5,0])
        labely=plane.get_y_axis_label(label=MathTex(r"P(5\times10^3 MW)",font_size=25))
        labely.next_to(plane,UL,buff=0.1)
        labely.shift([1.5,0,0])
        dotg=VGroup()
        dotl=[[0,17888],[0.5,17398],[1,17110],[1.5,16881],[2,16832],[2.5,16950],[3,16833],[3.5,16835],[4,17065],[4.5,17264],[5,17577],[5.5,17992],[6,18216]]
        for i in dotl:
            dotg.add(Dot(plane.coords_to_point(i[0],i[1]/5000),radius=0.06))
        self.play(Create(plane),Create(labelx),Create(labely))
        self.wait()
        self.play(Transform(table,dotg))
        text2=Tex(r"""
\begin{flalign*}
&\text{Using Simpson's rule:}\\
&E=\int_0^6{P(t)dt}\\
\end{flalign*}""",font_size=25)
        textsum=MathTex(r"\approx\frac{1}{6}\times0",font_size=24)
        text2.to_corner(UL,buff=0.1)
        textsum.next_to(text2,DOWN)
        textsum.align_to(text2,LEFT)
        self.play(Create(text2))
        self.play(Create(textsum))
        pl=[]
        ptl=[]
        asum=0
        texg=VGroup()
        texg.add(textsum)
        for i in range(0,12,2):
            mat=np.array([
                [dotl[i][0]**2,dotl[i][0],1],
                [dotl[i+1][0]**2,dotl[i+1][0],1],
                [dotl[i+2][0]**2,dotl[i+2][0],1]])
            vect=np.array([dotl[i][1]/5000,dotl[i+1][1]/5000,dotl[i+2][1]/5000])
            pcof=np.linalg.solve(mat,vect)
            if pcof[0]>0:
                delta=pcof[1]**2-4*pcof[0]*(pcof[2]-4)
                xran=(max((-pcof[1]-np.sqrt(delta))/(2*pcof[0]),-1),min((-pcof[1]+np.sqrt(delta))/(2*pcof[0]),7))
            else:
                delta=pcof[1]**2-4*pcof[0]*(pcof[2]+1)
                xran=(max((-pcof[1]+np.sqrt(delta))/(2*pcof[0]),-1),min((-pcof[1]-np.sqrt(delta))/(2*pcof[0]),7))
            func=lambda x:pcof[0]*x**2+pcof[1]*x+pcof[2]
            pl+=[plane.plot(func,color=BLUE,x_range=xran)]
            ptl+=[plane.plot(func,color=GREEN,x_range=[dotl[i][0],dotl[i+2][0]])]
        planeg=VGroup(plane,labelx,labely,table,dotg,ptl)
        for i in range(0,len(pl)):
            self.play(Create(pl[i]),dotg[2*i].animate.set_fill(color=ORANGE),dotg[2*i+1].animate.set_fill(color=ORANGE),dotg[2*i+2].animate.set_fill(color=ORANGE))
            area=plane.get_area(pl[i],x_range=[dotl[2*i][0],dotl[2*i+2][0]],color=BLUE)
            planeg.add(area)
            areac=area.copy()
            texta=MathTex(r"+&\\&\frac{1}{6}\times[P("+str(dotl[2*i][0])+r")+4P("+str(dotl[2*i+1][0])+r")+P("+str(dotl[2*i+2][0])+r")]",font_size=24)
            texta.next_to(textsum,DOWN,buff=0.1)
            texta.align_to(text2,LEFT)
            textb=MathTex(r"+&\\&\frac{1}{6}\times("+str(dotl[2*i][1])+r"+4\times"+str(dotl[2*i+1][1])+r"+"+str(dotl[2*i+2][1])+r")",font_size=24)
            textb.next_to(textsum,DOWN,buff=0.1)
            textb.align_to(text2,LEFT)
            textc=MathTex(r"+&\\&\frac{1}{6}\times"+str(dotl[2*i][1]+4*dotl[2*i+1][1]+dotl[2*i+2][1]),font_size=24)
            textc.next_to(textsum,DOWN,buff=0.1)
            textc.align_to(text2,LEFT)
            asum+=dotl[2*i][1]+4*dotl[2*i+1][1]+dotl[2*i+2][1]
            textsumn=MathTex(r"\approx\frac{1}{6}\times"+str(asum),font_size=24)
            textsumn.next_to(text2,DOWN)
            textsumn.align_to(text2,LEFT)
            self.wait(0.5)
            self.play(Create(area))
            self.wait(0.5)
            self.play(Transform(areac,texta))
            self.wait(0.5)
            self.play(Transform(areac,textb))
            self.wait(0.5)
            self.play(Transform(areac,textc))
            self.wait(0.5)
            texg.add(areac)
            self.play(Transform(texg,textsumn))
            texg.remove(areac)
            self.wait(0.5)
            self.play(FadeOut(pl[i]),FadeIn(ptl[i]),dotg[2*i].animate.set_fill(color=WHITE),dotg[2*i+1].animate.set_fill(color=WHITE),dotg[2*i+2].animate.set_fill(color=WHITE),area.animate.set_fill(color=GREEN))
            self.wait(0.5)
        textsumn=MathTex(r"\approx103369.\bar{6}",font_size=24)
        textsumn.next_to(text2,DOWN)
        textsumn.align_to(text2,LEFT)
        textsumn2=MathTex(r"\approx1.0337\times10^{5} (MWh)",font_size=24)
        textsumn2.next_to(text2,DOWN)
        textsumn2.align_to(text2,LEFT)
        self.play(Transform(texg,textsumn))
        self.wait(0.5)
        self.play(Transform(texg,textsumn2))
        self.wait(0.5)
        texg.add(text2)
        self.play(FadeOut(planeg),texg.animate.center())
        self.play(texg.animate.scale(1.75))
        self.wait(2)
