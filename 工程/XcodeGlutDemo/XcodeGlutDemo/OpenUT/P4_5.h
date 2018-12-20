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


/**
 矩阵行主序/列主序
 解释
 __inline void m3dTransformVector4(M3DVector4f vOut, const M3DVector4f v, const M3DMatrix44f m)
 {
 vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];
 vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];
 vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
 vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
 }
 为什么是 m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];
 而不是   m[0] * v[0] + m[1] * v[1] + m[2] *  v[2] + m[3] * v[3];
 对于正常矩阵相乘来讲应该是 m[0] * v[0] + m[1] * v[1] + m[2] *  v[2] + m[3] * v[3];
 但是请注意,opengl关于矩阵的存储并不是二维数组,而是一维数组,所以在这个时候，出现了行优先,列优先的规则，比如
 | 1  2 |
 | 3  4 |
 这个时候在Opengl中存储的是 {1，3， 2， 4} 所以就会出现上面的疑问,在DX中是和正常相同的，这和计算效率有关
 在这个时候我们可以发现 矩阵的行主序等于其转置矩阵的列主序
 具体可参考 https://www.jianshu.com/p/bfc8327eaad3
 
 
 float m3dDotProduce3(u,v) 返回两个单位向量的余弦值
 float m3dCrossProduce3(result, u, v) 返回垂直于两个向量的向量
 
 视觉坐标：一个虚拟的固定坐标系，作为参考坐标系使用
 视图变换：其实就是照相机在场景中的位置变换，忧郁视图变换会移动当前的工作坐标系，所以视图变换必须在其他模型变换之前
 模型变换：场景中的对象的变换，变换的结果与变换的顺序相关
 模型视图：就是视图矩阵和 模型矩阵的结合
 投影变换：定义了视景体并创建了裁剪平面。
 视口变换：剪裁平面和物理窗口的映射过程

 4、模型视图矩阵变换的函数：
 快速或获取一个单位矩阵：void m3dLoadIdentity44(m)
 平移矩阵：void m3dTranslationMatrix44(m,x,y,z)
 旋转矩阵：void m3dRotationMatrix44(m,angle,x,y,z):逆时针，弧度，xyz指定各轴上的分量
 如果需要按角度选择，可以这样调用m3dRotationMatrix44(m,m3dDegToRad(angle),x,y,z)
 缩放矩阵：void m3dScaleMatrix44(m,xScale,yScale,zScale)
 矩阵相乘：void m3dMatrixMultiply44(product,a,b)->product = a*b

 6、矩阵堆栈的使用：GLMatrixStack,初始化时已经在堆栈中包含了单位矩阵
 载入单位矩阵：GLMatrixStack::LoadIdentity()
 载入任何矩阵：GLMatrixStack::LoadMatrix(m)
 任何矩阵乘以栈顶元素并压栈：GLMatrixStack::MultMatrix(m)
 获取栈顶矩阵：1.const M3DMatrix44f& GLMatrixStack::GetMatrix()
  2.void GLMatrixStack::GetMatrix(m)
 压栈：复制当前矩阵（或指定矩阵），压入栈顶
 1、GLMatrixStack::PushMatrix()
 2、GLMatrixStack::PushMatrix(m)
 3、GLMatrixStack::PushMatrix(frame)
 出栈：GLMatrixStack::PopMatrix()
 栈顶变换：对当前栈顶矩阵进行变换
 Rotate(angle,x,y,z)
 Translate(x,y,z)
 Scale(x,y,z)
 3D渲染的流程
https://blog.csdn.net/zh13544539220/article/details/45505655
 
 
 */

/*
 需要注意
 1.OpenGL的模型视图变换矩阵(顶点对象)都是右乘当前变化矩阵
 2.摄像机矩阵和模型矩阵用的是同一个矩阵就是GL_MODELVIEW model是模型的矩阵,view是摄像机的矩阵,modelview其实就是两者的矩阵积 [讲的有点蹩脚]
 */


/**
 需要解决
 GLFrustum SetPerspective(float fFov, float fAspect, float fNear, float fFar) 参数的定义
 这个地方是设置平截头体的方法
         |
    |    |
    |    |
         |
 fFov 是设置初识的高度
 fAspect 是设置张开度  为float(nWidth) / float(nHeight)
 fNear 是离摄像机最近的距离
 fFar 是离摄像机最远的距离
 
 
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
#include <GLUT/GLUT.h>


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
    modelViewMatrix.PushMatrix(); //将上一个Matrix进行再次压栈,压栈最多压64层，初始层0为单位矩阵
    
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
