//
//  RFirstDot.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/12/18.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef RFirstDot_h
#define RFirstDot_h

#include <GLUT/GLUT.h>

void drawDot(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();
    glutSwapBuffers();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RFirstDot");
    glutDisplayFunc(drawDot);
    glutMainLoop();
    
}

#endif /* RFirstDot_h */
