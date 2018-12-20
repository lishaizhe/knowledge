//
//  WindowViewPort.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/6/28.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef WindowViewPort_h
#define WindowViewPort_h

/*
 glViewport是OpenGL中的一个函数。计算机图形学中，在屏幕上打开窗口的任务是由窗口系统，而不是OpenGL负责的。glViewport在默认情况下，视口被设置为占
 据打开窗口的整个像素矩形，窗口大小和设置视口大小相同，所以为了选择一个更小的绘图区域，就可以用glViewport函数来实现这一变换，在窗口中定义一个像素矩形，最终将图像映射到这个矩形中。例如可以对窗口区域进行划分，在同一个窗口中显示分割屏幕的效果，以显示多个视图/
 
 　　glViewport(GLint x,GLint y,GLsizei width,GLsizei height)为其函数原型。
 X，Y————以像素为单位，指定了视口的左下角（在第一象限内，以（0，0）为原点的）位置。
 width，height————表示这个视口矩形的宽度和高度，根据窗口的实时变化重绘窗口
 */

// 目标：测试OpenGL窗口视口坐标
// 结果：glutInitWindowSize(640, 480); 指定的是windows概念中窗口(看得见，可移动，最大化，最小化等操作)大小，以像素为单位
//       OpenGL中的窗口和视口是逻辑上的概念，其中窗口范围是画图时指定顶点坐标使用的坐标，而视口范围是将windows中概念中实际
//       窗口映射成的范围

//#define GLUT_DISABLE_ATEXIT_HACK

#include <GLUT/GLUT.h>

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);     // 设置背景色为白色
    glColor3f(1.0f, 0.0f, 0.0f);          // 绘图颜色为黑色
    glPointSize(4.0);                     // 设置点大小为4x4像素
    
    // 1. 如果不做任何处理，OpenGL默认坐标范围为 x=[-1,1]  y=[-1,1]
    
    // 2. 只指定世界窗口坐标范围，默认视口坐标范围与世界窗口一样，按世界窗口绘图即可
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 500, 0.0, 100);
    
    // 3. 同时指定世界窗口坐标和视口范围，会发生从世界窗口坐标转换为视口坐标，按世界窗口绘图即可
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluOrtho2D(-3, 3, -2, 3);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(-2, -2, 4, 4);
}

// 重绘函数
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // 清屏
    // 1. 测试不做任何处理时，窗口与视口范围相同
    //    OpenGL默认坐标范围为 x=[-1,1]  y=[-1,1]
//    glBegin(GL_QUADS);
//    glVertex2f(-0.5,  0.5);
//    glVertex2f( 0.5,  0.5);
//    glVertex2f( 0.5, -0.5);
//    glVertex2f(-0.5, -0.5);
//    glEnd();
    
    // 2. 测试只指定世界窗口坐标范围，窗口与视口范围
//    glBegin(GL_LINES);
//    glVertex2f(0, 0);
//    glVertex2f(400, 80);
//    glEnd();
    
    // 3. 测试同时指定世界窗口坐标和视口范围
    glBegin(GL_LINES);
    glVertex2f(-2, -1);
    glVertex2f(2, 1);
    glEnd();

    glFlush();
}

void initHook(int argc, char *argv[])
{
    glutInit(&argc, argv);                         // 初始化glut工具箱
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // 设置显示模式
    glutInitWindowSize(640, 480);                  // 设置窗口大小
    glutInitWindowPosition(100, 150);              // 设置窗口在屏幕上的位置
    glutCreateWindow("my first attempt");          // 创建窗口
    glutDisplayFunc(myDisplay);                    // 注册重绘函数
    myInit();
    glutMainLoop();                                // 进入主循环
}












////////////////////////////////////////////////
/*
 网上很多文章都谈过窗口，视口，裁剪区域这些概念，但感觉看了还是不很明白。下面是我个人实践过后的一些看法：
 
 1.窗口：这就不用解释了吧
 
 2.视口：就是窗口中用来显示图形的一块矩形区域，它可以和窗口等大，也可以比窗口大或者小。只有绘制在视口区域中的图形才能被显示，如果图形有一部分超出了视口区域，那么那一部分是看不到的。通过glViewport()函数设置。如下图所示：

 3.裁剪区域：就是视口矩形区域的最小最大x坐标（left,right)和最小最大y坐标(bottom,top)，而不是窗口的最小最大x坐标和y坐标。通过glOrtho()函数设置，这个函数还需指定最近最远z坐标，形成一个立体的裁剪区域。
#include <GL\glut.h>
#include <GL\GL.h>
#include <stdio.h>

void oglDisplay();

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(400,400);
    glutCreateWindow("Viewport");
    glutDisplayFunc(oglDisplay);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glutMainLoop();
    
    return 0;
}

void oglDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Left-Bottom
    glViewport(0,0, 200, 200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-100.0f, 100.0f, 100.0f, -100.0f);
    
    // Right-Bottom
    glViewport(200, 0, 200, 200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glRectf(-100.0f, 100.0f, 100.0f, -100.0f);
    
    // Left-Top
    glViewport(0, 200, 200, 200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glRectf(-100.0f, 100.0f, 100.0f, -100.0f);
    
    // Right-Top
    glViewport(200, 200, 200, 200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    glRectf(-100.0f, 100.0f, 100.0f, -100.0f);
    
    glFlush();
}
*/


void display()
{
    //画分割线 ，分成四个视图区域
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glViewport(0, 0, 400, 400);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0);
    glVertex2f(1.0, 0);
    glVertex2f(0, -1.0);
    glVertex2f(0, 1.0);
    glEnd();
    //定义左下角区域
    glColor3f(0.0, 1.0, 0.0);
    glViewport(0, 0, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义右上角区域
    glColor3f(0.0, 0.0, 1.0);
    glViewport(200, 200,200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义在左上角的区域
    glColor3f(1.0, 0.0, 0.0);
    glViewport(0, 200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义在右下角的区域
    glColor3f(1.0, 1.0, 1.0);
    glViewport(200, 0, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    
    
    glFlush();
}



//int initHook(int argc, char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(400, 400);
//    glutCreateWindow("glViewport");
//    glutDisplayFunc(display);
//    //0100;
//    glutMainLoop();
//    return 0;
//}

#endif /* WindowViewPort_h */
