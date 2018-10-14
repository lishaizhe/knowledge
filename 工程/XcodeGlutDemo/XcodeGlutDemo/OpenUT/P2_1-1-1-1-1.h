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
GLBatch dotBatch;
GLShaderManager shaderManager;

void ChangeSize(int width, int height){
    glViewport(2, 0, width, height);
}

void RenderScene(){
    //清除屏幕的颜色
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f}; //采用红色填充
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    GLfloat vRed1[] = {0.0f, 1.0f, 0.0f, 1.0f}; //采用红色填充
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed1);
    dotBatch.Draw();
    //根据上方填充的buffer进行绘制
    glutSwapBuffers();
}

void SetupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  //为RGBA, 所以当前背景图变成了蓝色
    shaderManager.InitializeStockShaders();
    //加载多边形
    GLfloat vVerts[] = {-0.5f, 0.0f, 0.0f,
                        0.5f,  0.0f, 0.0f,
                        0.0f,  0.5f, 0.0f };
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
    GLfloat vDot[] = {-0.8f, -0.8f, 0.0f};
    dotBatch.Begin(GL_POINTS, 1);
    dotBatch.CopyVertexData3f(vDot);
    dotBatch.End();
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

/*
 解析：
 gltSetWorkingDirectory [GLTools的函数--设置当前的工作目录]
    实际上在windows中是不必要的,因为工作目录默认就是和可执行程序相同的目录,但是MAC OS中,这个程序将当前的工作文件夹改成应用捆绑包(Application Bundle)中的 /Resource 文件夹
 
 glutDisplayFunc()   //显示回调
 glutReshapeFunc()   //窗口发生变化的回调
 
 
 
 */



#endif /* P2_1_h */
