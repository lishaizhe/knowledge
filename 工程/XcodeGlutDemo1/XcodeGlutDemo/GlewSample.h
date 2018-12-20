//
//  GlewSample.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/6/22.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef GlewSample_h
#define GlewSample_h

#include <GLUT/GLUT.h>

GLuint VBO;

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

static void CreateVertexBuffer(){
    /*
     // 创建含有一个顶点的顶点数组
     Vector3f Vertices[1];
     // 将点置于屏幕中央
     Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
     
     // 创建缓冲器
     glGenBuffers(1, &VBO);
     // 绑定GL_ARRAY_BUFFER缓冲器
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     // 绑定顶点数据
     glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
     */
    
    static GLint i_list[][3] = {
        0, 0, 0,
    };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(i_list), i_list, GL_STATIC_DRAW);
}

void initHook(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLEW");
    glutDisplayFunc(RenderSceneCB);
    
//    GLenum res = glewInit();
//    if (res != GLEW_OK)
//        return 1;
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    CreateVertexBuffer();
    
    glutMainLoop();
}

void myDisplay()
{
    
}

#endif /* GlewSample_h */
