//
//  P4_5.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/15.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

/*
 //绘制球体
 fRadius 半径
 iSlices  围绕着球体排列的三角形对数
 iStacks  从球体底部堆叠到顶部的三角形带的数量
 典型情况下，一个对称性较好的球体的片段数量是堆叠数量的2倍，why？围绕球体一周是360度，而从底部到顶部只有180度
    另外 +z是球体的定点  -z是球体的底部
 void gltMakeSphere(GLTriangleBatch& batch, GLFloat fRadius, GLint iSlices, GLint iStacks)
 
 //花托 -》面包圈
    majorRadius 从中心到外边缘的半径
    minorRadius 从中心到内边缘的半径
    numMajor/numMinor 从中心到两个边缘的细分单元的数量
  void gltMakeTorus(GLTriangleBatch& batch, GLFloat majorRadius, GLFloat minorRadius, GLint numMajor, GLint numMinor)
 
 */





#ifndef P4_5_h
#define P4_5_h

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#include <stdio.h>

#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GLUT/GLUT.h>

/*
 * 当libjpeg-turbo为vs2010编译时，vs2015下静态链接libjpeg-turbo会链接出错:找不到__iob_func,
 * 增加__iob_func到__acrt_iob_func的转换函数解决此问题,
 * 当libjpeg-turbo用vs2015编译时，不需要此补丁文件
 */
#if _MSC_VER>=1900
#include "stdio.h"
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus
extern "C"
#endif
FILE* __cdecl __iob_func(unsigned i) {
    return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */

#define NUM_SPHERES 50
GLFrame disk[NUM_SPHERES/2];
GLFrame cylinder[NUM_SPHERES/2];


GLShaderManager     shaderManager;          // Shader Manager
GLMatrixStack       modelViewMatrix;        // Modelview Matrix
GLMatrixStack       projectionMatrix;       // Projection Matrix
GLFrustum           viewFrustum;            // View Frustum
GLGeometryTransform transformPipeline;      // Geometry Transform Pipeline

GLTriangleBatch     torusBatch;
GLBatch             floorBatch;
GLTriangleBatch     sphereBatch;
GLTriangleBatch     triangleBatch;
GLTriangleBatch     cylinderBatch;
GLTriangleBatch     diskBatch;

GLFrame             cameraFrame;

//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
    // Initialze Shader Manager
    shaderManager.InitializeStockShaders();
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // 制造花圈
    gltMakeTorus(torusBatch, 0.4f, 0.15f, 30, 30);
    
    // 制造小球
    gltMakeSphere(sphereBatch, 0.3f, 26, 13);
    
    //制造圆柱
    gltMakeCylinder(cylinderBatch, 0.2f, 0.2f, 0.5f, 13, 2);
    
    //制造圆盘
    gltMakeDisk(diskBatch, 0.2f, 0.4f, 13, 3);
    
    floorBatch.Begin(GL_LINES, 324);
    for (GLfloat x = -20.0; x <= 20.0f; x += 0.5) {
        floorBatch.Vertex3f(x, -0.55f, 20.0f);
        floorBatch.Vertex3f(x, -0.55f, -20.0f);
        
        floorBatch.Vertex3f(20.0f, -0.55f, x);
        floorBatch.Vertex3f(-20.0f, -0.55f, x);
    }
    floorBatch.End();
    
    // Randomly place the spheres
    for (int i = 0; i < NUM_SPHERES; i++) {
        GLfloat x = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        GLfloat z = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        if(i%2==0)
            disk[i/2].SetOrigin(x, 0.0f, z);
        else
            cylinder[(i-1)/2].SetOrigin(x, 0.0f, z);
    }
    
    GLfloat vetts[3][3];
    GLfloat vNorms[3][3];
    GLfloat vTexCoords[3][2];
    GLfloat angle = 0;
    for (int i = 0; i < 3; i++) {
        angle += M3D_2PI / 6.0f;
        vetts[i][0] = float(-5 + i*0.2);
        vetts[i][1] = float(sin(float(angle)));
        vetts[i][2] = float(cos(float(angle)));
        
        vNorms[i][0] = float(-5 + i*0.2);
        vNorms[i][1] = float(cos(float(angle)));
        vNorms[i][2] = float(sin(float(angle)));
        
        vTexCoords[i][0] = float(-5 + i*0.2);
        vTexCoords[i][1] = float(sin(float(angle)));
    }
    triangleBatch.BeginMesh(3);
    triangleBatch.AddTriangle(vetts, vNorms, vTexCoords);
    triangleBatch.End();
    
}

///////////////////////////////////////////////////
// Screen changes size or is initialized
void ChangeSize(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    
    // 创建投影矩阵，并将它载入到投影矩阵堆栈中
    viewFrustum.SetPerspective(35.0f, float(nWidth) / float(nHeight), 1.0f, 100.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // 设置变换管线以使用两个矩阵堆栈
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

// Called to draw scene
void RenderScene(void)
{
    // 颜色值
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    static GLfloat vTorusColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    static GLfloat vSphereColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    static GLfloat vdiskColor[] = { 0.0f, 0.5f, 0.5f, 1.0f };
    static GLfloat vcylinderColor[] = { 0.5f, 0.0f, 0.5f, 1.0f };
    
    // 基于时间的动画
    static CStopWatch   rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    
    // 清除颜色缓冲区和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // 保存当前模型视图矩阵 (单位矩阵)
    modelViewMatrix.PushMatrix();
    
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);
    
    // 将光源位置变换到视觉坐标系
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    m3dTransformVector4(vLightEyePos, vLightPos, mCamera);
    
    // 绘制背景
    shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                 transformPipeline.GetModelViewProjectionMatrix(),
                                 vFloorColor);
    floorBatch.Draw();
    
    
    //绘制圆柱和圆盘
    for (int i = 0; i < NUM_SPHERES; i++) {
        modelViewMatrix.PushMatrix();
        if (i % 2 == 0) {
            modelViewMatrix.MultMatrix(disk[i / 2]);
            shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                         transformPipeline.GetProjectionMatrix(), vLightEyePos, vdiskColor);
            diskBatch.Draw();
        }
        else
        {
            modelViewMatrix.MultMatrix(cylinder[(i - 1) / 2]);
            shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                         transformPipeline.GetProjectionMatrix(), vLightEyePos, vcylinderColor);
            cylinderBatch.Draw();
            
        }
        modelViewMatrix.PopMatrix();
    }
    
    
    // 绘制旋转花托
    modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
    
    // 保存平移矩阵
    modelViewMatrix.PushMatrix();
    
    // 应用旋转并绘制花托
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vTorusColor);
    torusBatch.Draw();
    modelViewMatrix.PopMatrix(); // "清除" 以前的旋转
    
    //绘制三角形
    //modelViewMatrix.PushMatrix();
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vTorusColor);
    triangleBatch.Draw();
    //modelViewMatrix.PopMatrix();
    
    
    // 应用另一个旋转，然后进行平移，然后再绘制球体
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),
                                 transformPipeline.GetProjectionMatrix(), vLightEyePos, vSphereColor);
    sphereBatch.Draw();
    
    // 还原到以前的模型视图矩阵 (单位矩阵)
    modelViewMatrix.PopMatrix();
    modelViewMatrix.PopMatrix();
    // 进行缓冲区交换
    glutSwapBuffers();
    
    // 通知GLUT在进行一次同样操作
    glutPostRedisplay();
}


// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
    float linear = 0.1f;
    float angular = float(m3dDegToRad(5.0f));
    
    if (key == GLUT_KEY_UP)
        cameraFrame.MoveForward(linear);
    
    if (key == GLUT_KEY_DOWN)
        cameraFrame.MoveForward(-linear);
    
    if (key == GLUT_KEY_LEFT)
        cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    
    if (key == GLUT_KEY_RIGHT)
        cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

void initHook(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    
    glutCreateWindow("OpenGL SphereWorld");
    
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return;
    }
    
    SetupRC();
    glutMainLoop();
}

#endif /* P4_5_h */
