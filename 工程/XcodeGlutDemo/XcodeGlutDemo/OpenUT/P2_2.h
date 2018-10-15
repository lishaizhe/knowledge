//
//  P2_2.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/14.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef P2_2_h
#define P2_2_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;

GLfloat vVerts[] = {-0.3, 0.3f, 0.0f,
    0.3, 0.3f, 0.0f,
    0.3, -0.3f, 0.0,
    -0.3, -0.3, 0.0
};

void changeSize(int w, int h){
    glViewport(0, 0, w, h);
}

void SetupRC(){
    glClearColor(0.0, 0.0, 1.0, 1.0); //设置背景的颜色
    shaderManager.InitializeStockShaders();
    
//    triangleBatch.Begin(GL_POLYGON, 4); //设置绘制的模式
//    triangleBatch.CopyVertexData3f(vVerts);//拷贝数据
//    triangleBatch.End();//设置完成
}

void RenderScene(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);//清空屏幕
//    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed); //表示使用什么颜色对图形进行填充
//    triangleBatch.Draw();
//    glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y){
    GLfloat stepSize = 0.025f;
    int _bUD = 0; //0 none, 1U  2D
    int _bLR = 0; //0 none  1L  2R
    if (key == GLUT_KEY_UP){
        _bUD = 1;
    }
    if (key == GLUT_KEY_DOWN){
        _bUD = 2;
    }
    if (key == GLUT_KEY_LEFT){
        _bLR = 1;
    }
    if (key == GLUT_KEY_RIGHT){
        _bLR = 2;
    }
    GLfloat disX = 0.0f;
    GLfloat disY = 0.0f;
    if (_bUD == 1){
        disY = stepSize;
    }else if (_bUD == 2){
        disY = -stepSize;
    }
    if (_bLR == 1){
        disX = -stepSize;
    }else if (_bLR == 2){
        disX = stepSize;
    }
    vVerts[0] += disX;
    vVerts[1] += disY;
    
    vVerts[3] += disX;
    vVerts[4] += disY;
    
    vVerts[6] += disX;
    vVerts[7] += disY;
    
    vVerts[9] += disX;
    vVerts[10] += disY;
    triangleBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
    
}

void initHook(int argc, char * argv[]){
    gltSetWorkingDirectory(argv[0]); //设置shader的当前工作目录
    glutInit(&argc, argv);
    glutInitWindowSize(200, 150);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);  //GLUT_STENCIL  模板测试
    glutCreateWindow("P2_1");
    
    GLenum error = glewInit();
    if (error != GLEW_OK){
        printf("error");
        return;
    }
    SetupRC();
    glutDisplayFunc(RenderScene);
//    glutReshapeFunc(changeSize);
//    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
}

#endif /* P2_2_h */
