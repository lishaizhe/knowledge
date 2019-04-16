//
//  FirstDot.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/25.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef FirstDot_h
#define FirstDot_h

#include <GLUT/GLUT.h>
#include <math.h>

//绘制一个点
void displayOnePoint(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2f(0.5f, 0.0f);
    glEnd();
    glFlush();
}
//绘制线
void displayLine(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();
    glFlush();
}
//画圆
const int n = 20;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926f;
void displayCircle(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int i = 0;i < n; ++i){
        glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
    }
    glEnd();
    glFlush();
}
//正弦函数
const GLfloat factor = 0.1f;
void displaySin(){
    GLfloat x;
    glClear(GL_COLOR_BUFFER_BIT);
//    glLineWidth(5.0f); 设置线的宽度
//    glPointSize(5.0f); 设置点的大小
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
    glEnd();
    glBegin(GL_LINE_STRIP);         //GL_LINE_STRIP 表示一系列的连续直线,这个时候如果是两个点的情况,和GL_LINES是没有区别的,当多个点的时候，我们就可以看出来，而GL_LINES是两两匹配的
    for(x=-1.0f/factor; x<1.0f/factor; x+=0.01f)
    {
        glVertex2f(x*factor, sin(x)*factor);
    }
    glEnd();
    glFlush();
}
//虚线
/*
 glEnable(GL_LINE_STIPPLE) 开启虚线模式
 glDisable(GL_LINE_STIPPLE) 关闭虚线模式
 void glLineStipple(GLint factor, GLushort pattern);  设置虚线的样式
 pattern是由1和0组成的长度为16的序列，从最低位开始看，如果为1，则直线上接下来应该画的factor个点将被画为实的；如果为0，则直线上接下来应该画的factor个点将被画为虚的。
 换个人语言:
    这个虚线的实现方式是每16个像素来循环绘制。根据pattern中给出的16位二进制，如果该位为1则进行绘制，为0则不绘制。来形成的虚线
 */
void displayStipple(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x0F01);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    glFlush();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);//初始化,必须
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);//初始化渲染模式
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("绘制一个点");
    glutDisplayFunc(displaySin);
    glutMainLoop();
}

#endif /* FirstDot_h */
