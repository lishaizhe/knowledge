//
//  R_2_1.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2019/4/16.
//  Copyright © 2019 李帅哲. All rights reserved.
//

#ifndef R_2_1_h
#define R_2_1_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

GLShaderManager shaderManager;
GLBatch triangleBatch;

//改变屏幕尺寸
void ChangeSize(int width, int height){
    glViewport(0, 0, width, height);
}

//设置渲染初始化
void setupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
                          0.5f, 0.0f, 0.0f,
                          0.0f, 0.5f, 0.0f };
    triangleBatch.Begin(GL_TRIANGLES, 3); //这个地方有个知识点.关于三角形点连接顺序的问题
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    glutSwapBuffers();
}

void initHook(int argc, char * argv[]){
    //设置工作目录
    gltSetWorkingDirectory(argv[0]);
    //初始化OPENGL引擎
    glutInit(&argc, argv);
    //设置缓冲模式
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("R_2_1");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(renderScene);
    GLenum eCode = glewInit();
    if (eCode != GLEW_OK){
        return;
    }
    setupRC();
    glutMainLoop();
}

#endif /* R_2_1_h */
