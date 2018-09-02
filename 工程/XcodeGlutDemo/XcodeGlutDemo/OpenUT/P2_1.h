//
//  P2_1.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/9/2.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef P2_1_h
#define P2_1_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>



GLBatch triangleBatch;
GLShaderManager shaderManager;

void ChangeSize(int width, int height){
    glViewport(0, 0, width, height);
}

void RenderScene(){
    //清除屏幕的颜色
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    //根据上方填充的buffer进行绘制
    glutSwapBuffers();
}

void SetupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    //加载多边形
    GLfloat vVerts[] = {-0.5f, 0.0f, 0.0f,
                        0.5f,  0.0f, 0.0f,
                        0.0f,  0.5f, 0.0f };
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void initHook(int argc, char * argv[]){
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("P_2_1");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "GLERROR: %s \n", glewGetErrorString(err));
        return;
    }
    SetupRC();
    glutMainLoop();
}

#endif /* P2_1_h */
