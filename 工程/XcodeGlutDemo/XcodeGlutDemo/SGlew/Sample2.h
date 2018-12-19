//
//  Sample2.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/6/27.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef Sample2_h
#define Sample2_h

#include <iostream>
#include <GLShaderManager.h>
#include <GLTools.h>
#include <GLUT/GLUT.h>

GLBatch squareBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;
GLfloat vVertes[] = {
    -blockSize-0.5f, -blockSize, 0.0f,
    blockSize-0.5f, -blockSize, 0.0f,
    blockSize-0.5f, blockSize, 0.0f,
    -blockSize-0.5f, blockSize, 0.0f
};

//设置中间移动的四方体 这个地方是通过两个三角形形成的一个举行
void setupRC(){
    glClearColor(1, 0, 1, 1);
    shaderManager.InitializeStockShaders();
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVertes);
    squareBatch.End();
}

void BounceFunction(){
    static GLfloat xDir = 1.0f;
    static GLfloat yDir = 1.0f;

    GLfloat stepSize = 0.005f;
    GLfloat blockX = vVertes[0];
    GLfloat blockY = vVertes[7];
    blockY += stepSize * yDir;
    blockX += stepSize * xDir;

    if (blockX < -1.0f){
        blockX = -1.0f;
        xDir *= -1.0f;
    }
    if(blockX < -1.0f) { blockX = -1.0f; xDir *= -1.0f; }
    if(blockX > (1.0f - blockSize * 2)) { blockX = 1.0f - blockSize * 2; xDir *= -1.0f; }
    if(blockY < -1.0f + blockSize * 2)  { blockY = -1.0f + blockSize * 2; yDir *= -1.0f; }
    if(blockY > 1.0f) { blockY = 1.0f; yDir *= -1.0f; }

    // Recalculate vertex positions
    vVertes[0] = blockX;
    vVertes[1] = blockY - blockSize*2;

    vVertes[3] = blockX + blockSize*2;
    vVertes[4] = blockY - blockSize*2;

    vVertes[6] = blockX + blockSize*2;
    vVertes[7] = blockY;

    vVertes[9] = blockX;
    vVertes[10] = blockY;

    squareBatch.CopyVertexData3f(vVertes);
}

/**
 渲染情景
 */
void renderScence(void){

    // 这部才是真正的清理缓存区，包括以下几种清理方式，防止上次缓冲区数据和这次重叠了
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    GLfloat vBlue[] = {0.0f,0.0f,1.0f,1.0f};
    //设置坐标和颜色
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vBlue);
    squareBatch.Draw();

    glutSwapBuffers();
    //加入碰撞检查
    BounceFunction();
    //标记需要重新绘制
    glutPostRedisplay();


}

void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}


int initHook(int argc,char * argv[]) {

    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv);
    //函数功能为设置初始显示模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Block");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    //glutReshapeFunc是窗口改变的时候调用的函数，在这个里面可以根据缩放后的窗口重新设置
    glutReshapeFunc(ChangeSize);
    //glutDisplayFunc函数用于注册一个绘图函数， 这样操作系统在必要时刻就会对窗体进行重新绘制操作
    glutDisplayFunc(renderScence);
    setupRC();
    glutMainLoop();
    return 0;
}


#endif /* Sample2_h */
