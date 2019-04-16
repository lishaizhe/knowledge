//
//  RotateSphere.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/28.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef RotateSphere_h
#define RotateSphere_h

#include <GLUT/GLUT.h>

static int day = 200;

void displayRoateSphere(){
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 400000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
    
    // 绘制红色的“太阳”
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600000, 20, 20);
    // 绘制蓝色的“地球”
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000000, 0.0f, 0.0f);
    glutSolidSphere(15945000, 20, 20);
    // 绘制黄色的“月亮”
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000000, 0.0f, 0.0f);
    glutSolidSphere(4345000, 20, 20);
    
    glFlush();
    glutSwapBuffers();
}

void myIdle(){
    ++day;
    if (day >= 360)
        day = 0;
    displayRoateSphere();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sphere");
    glutDisplayFunc(displayRoateSphere);
    glutIdleFunc(myIdle); //函数会不断被调用,直到有窗口时间发生
    glutMainLoop();
}

#endif /* RotateSphere_h */
