//
//  P4_6.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/10/16.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef P4_6_h
#define P4_6_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

//关于glclear  glclearcolor 等 https://blog.csdn.net/hebbely/article/details/69951068

GLShaderManager shaderManager;

void SetupRc(){
    shaderManager.InitializeStockShaders();
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void RenderScene(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void initHook(int argc, char * argv[]){
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);  //GLUT_DOUBLE  GL_DOUBLE
    glutCreateWindow("P4_6");
    GLenum error = glewInit();
    if (GLEW_OK != error){
        return;
    }
    SetupRc();
    glutDisplayFunc(RenderScene);
    glutMainLoop();
}

#endif /* P4_6_h */
