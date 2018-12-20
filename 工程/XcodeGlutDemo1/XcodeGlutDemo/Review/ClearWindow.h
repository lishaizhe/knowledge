//
//  ClearWindow.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/12/18.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef ClearWindow_h
#define ClearWindow_h
#include <GLUT/GLUT.h>

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5, -0.5, 0.5, 0.5);
    glutSwapBuffers();
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ClearWindow");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
}

#endif /* ClearWindow_h */
