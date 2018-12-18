//
//  Pologon.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/25.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef Pologon_h
#define Pologon_h

#include <GLUT/GLUT.h>

/*
 正反向 -- 反转
 讲解:
 在这里有三个知识点  1.正反向    2.填充/空心线   3.反转
 1.正反向   任何物体都会分为正向和反向。但此时是涉及到两个物体的时候
 2.填充/空心线   GL_FILL填充   GL_LINE 空心线
 3.反转    GL_CCW 以逆时针旋转从Y轴开始第一个为正向，第二个为反向      GL_CW是以顺时针
 */
void displayPologon(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);   //设置正面为填充模式
    glPolygonMode(GL_BACK, GL_LINE);    //设置反面为线性模式
    glFrontFace(GL_CCW);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.3);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.5f, 0.0f);
    glEnd();
    glFlush();
}

/*
 剔除 -- 隐藏不需要及时渲染的东西
 */
void displayCull(){
    glEnable(GL_CULL_FACE);//启动剔除
    glDisable(GL_CULL_FACE);//关闭剔除
    glCullFace(GL_FRONT);//剔除前面
    glCullFace(GL_BACK);//后面
    glCullFace(GL_FRONT_AND_BACK);//前后面
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("多边形");
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(displayPologon);
    glutMainLoop();
}

#endif /* Pologon_h */
