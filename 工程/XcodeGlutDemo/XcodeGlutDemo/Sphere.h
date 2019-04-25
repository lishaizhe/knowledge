//
//  Sphere.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/27.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include <GLUT/GLUT.h>

/*
 glMatrixMode 指定哪一个矩阵是当前矩阵
    创建一个投影矩阵并且与当前矩阵相乘,得到的矩阵设定为当前变换,但要先通过glMatrixMode设定为投影矩阵才会得到想要的投影矩阵变换
 mode 指定哪一个矩阵堆栈是下一个矩阵操作的目标
    GL_MODELVIEW 对模型视景矩阵堆栈应用随后的矩阵操作
    GL_PROJECTION 对投影矩阵应用随后的矩阵操作
    GL_TEXTURE  对纹理矩阵应用随后的矩阵操作
 
 
 GL_DEPTH_TEST  如果启用了之后，OpenGL在绘制的时候就会检查，当前像素前面是否有别的像素
 如果有别的像素遮挡，则只绘制最前面的一层
 
 如果要绘制透明图片的时候，则需要关闭他
 glDisable(GL_DEPTH_TEST)并且打开混合模式
 glEnable(GL_BLEND)而且还需要设置使用的透明度
 glColor4f(1.0f, 1.0f, 1.0f, 0.5f)这种
 
 glBlendFunc(GL_SRC_ALPHA, GL_ONE)
 
 void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    fovy 眼睛上下睁开的幅度，角度值，值越小，视野越小，值越大，视野范围也越宽阔
    zNear 近裁剪面到眼睛的距离
    zFar 表示远裁剪面到眼睛的距离   注意zNear和zFar不能设置为负值(不能看到眼睛后面的东西)
    aspect 表示裁剪面的宽w高h比，这个影响到视野的截面有多大
 */

/*
 glFrustum() 和 glperspective()两者的关系
 https://blog.csdn.net/zhouxuguang236/article/details/44999529
 gluPerspective(75, 1, 1, 300);
 =》glFrustum(-1.0, 1, -1, 1, 1, 300); 几乎相同,不完全相同哈。只是两者的计算可以这么得出
 所以就看的出
 */

static int day = 2;
void displaySphere(){
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-1.0, 1, -1, 1, 1, 300);
    glOrtho(-50, 50, -50, 50, 1, 300); //正交摄像机
//    gluPerspective(75, 1, 1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -40, 0, 0, 0, 0, 1, 0);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireCube(70);
    // 绘制红色的“太阳”
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glutSolidSphere(69, 20, 20);
//
//    glBegin(GL_POLYGON);
//    glVertex2f(-100.0, 100.0);
//    glVertex2f(-100.0, -100.0);
//    glVertex2f(100.0, -100.0);
//    glVertex2f(100.0, 100.0);
//    glEnd();
//    // 绘制蓝色的“地球”
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(150000000, 0.0f, 0.0f);
//    glutSolidSphere(15945000, 20, 20);
//    // 绘制黄色的“月亮”
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(38000000, 0.0f, 0.0f);
//    glutSolidSphere(4345000, 20, 20);
    
    glFlush();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sphere");
    glutDisplayFunc(displaySphere);
    glutMainLoop();
}

#endif /* Sphere_h */
