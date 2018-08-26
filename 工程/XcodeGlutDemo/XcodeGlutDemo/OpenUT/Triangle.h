//
//  Tiangle.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/7/2.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef Tiangle_h
#define Tiangle_h

#include "GLTools.h"
#include "GLShaderManager.h"
#include <GLUT/GLUT.h>

GLBatch triangleBatch;
GLBatch squareBatch;
GLShaderManager shaderManager;
GLfloat vVerts[] = {
    -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f
};

void changeSize(int w, int h){
    glViewport(0, 0, w, h);
}

void setupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    
    
    triangleBatch.Begin(GL_TRIANGLES, 3);  //定义几个顶点
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    squareBatch.CopyVertexData3f(vVerts);
}

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y){
    GLfloat stepSize = 0.025f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    if (key == GLUT_KEY_DOWN){
        blockY -= stepSize;
    }else if (key == GLUT_KEY_UP){
        blockY += stepSize;
    }else if (key == GLUT_KEY_RIGHT){
        blockX += stepSize;
    }else if (key == GLUT_KEY_LEFT){
        blockX -= stepSize;
    }
    blockX = blockX < -1.0f ? -1.0f : blockX;
    blockX = blockX > 1.0f ? 1.0f : blockX;
    blockY = blockY < -1.0f ? -1.0f : blockY;
    blockY = blockY > 1.0f ? 1.0f : blockY;
    vVerts[0] = blockX;
    vVerts[1] = blockY;
    vVerts[3] = blockX;
    vVerts[4] = blockY;
    vVerts[6] = blockX;
    vVerts[7] = blockY;
    vVerts[9] = blockX;
    vVerts[10] = blockY;
}

int initHook(int argc, char* argv[]){
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene);
    glutSpecialFunc(specialKeys);
    GLenum error = glewInit();
    if (error != GLEW_OK){
        fprintf(stderr, "error: %s\n", glewGetErrorString(error));
        return 1;
    }
    setupRC();
    glutMainLoop();
    return 0;
}



#endif /* Tiangle_h */
