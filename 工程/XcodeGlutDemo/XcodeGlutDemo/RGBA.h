//
//  RGBA.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/27.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef RGBA_h
#define RGBA_h

#include <GLUT/GLUT.h>
#include <math.h>

const GLfloat Pi = 3.1415926536;

void display(){
    //glShadeModel(GL_SMOOTH);  GL_FLAT -- 单色模式[这种模式下不同颜色之间没有过渡]   GL_SMOOTH -- 平滑模式(默认方式)
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 8; ++i){
        glColor3f(i&0x04, i&0x02, i&0x01);
        glVertex2f(cos(i*Pi/4), sin(i*Pi/4));
    }
    glEnd();
    glFlush();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("pologon");
    glutDisplayFunc(display);
    glutMainLoop();
}

#endif /* RGBA_h */
