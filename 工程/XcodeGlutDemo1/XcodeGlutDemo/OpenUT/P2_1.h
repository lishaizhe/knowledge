//
//  P2_1.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/14.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef P2_1_h
#define P2_1_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;

void changeSize(int w, int h){
    glViewport(0, 0, w/2., h/2.);
}

void SetupRC(){
    glClearColor(0.0, 0.0, 1.0, 1.0); //设置背景的颜色
    shaderManager.InitializeStockShaders();
    GLfloat vVerts[] = {-0.5, 0.0f, 0.0f,
                         0.5, 0.0f, 0.0f,
                         0.0, 0.5f, 0.0
    };
    triangleBatch.Begin(GL_TRIANGLES, 3); //设置绘制的模式
    triangleBatch.CopyVertexData3f(vVerts);//拷贝数据
    triangleBatch.End();//设置完成
}

void RenderScene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);//清空屏幕
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed); //表示使用什么颜色对图形进行填充
    triangleBatch.Draw();
    glutSwapBuffers();
}

void initHook(int argc, char * argv[]){
    gltSetWorkingDirectory(argv[0]); //设置shader的当前工作目录
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);  //GLUT_STENCIL  模板测试
    glutCreateWindow("P2_1");
    
    GLenum error = glewInit();
    if (error != GLEW_OK){
        printf("error");
        return;
    }
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(changeSize);
    glutMainLoop();
}

#endif /* P2_1_h */
