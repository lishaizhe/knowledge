//
//  P4.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/15.
//  Copyright © 2018年 李帅哲. All rights reserved.
//


/*
 关于目前基于最简单的OpenGL绘制的理解
 1.首先，我们需要经过一些列的OpenGl Init的方式，设置OpenGl的状态
 
 */


/*
 点乘
 在math3d库中
 float m3dDotProduct3(const M3DVector3f u, const M3DVector3f v) //得到点乘
 
 //返回两个向量之间的弧度值
 float m3dGetAngleBetweenVectors3(const M3DVector3f u, const M3DVector3f v)
 
 //叉乘
 void m3dCrossProduct3(M3DVector3f result, const M3DVector3f u, const M3DVector3f v)
 
 //创建单位矩阵
 void m3dLoadIdentity44(M3DMatrix44f m)
 
 //沿xyz轴平移
 void m3dTranslationMatrix44(M3DMatrix44f m, float x, float y, float z);
 
 //围绕xyz旋转 沿逆时针旋转->需要弧度
 void m3dRotationMatrix44(M3DMatrix44f m , float angle, float x, float y, float z)
 =》 M3DMatrix44f m;
    m3dRotationMatrix(m, m3dDegToRad(45.0), 1.0f, 1.0f, 1.0f)
 
 //缩放
 void m3dScaleMatrix44(M3DMatrix44f m, float xScale, float yScale, float zScale)
 
 //矩阵相乘和顺序是有关系的
 //矩阵相乘
 void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b)
 
 
 
 
 */

/*
 关于单缓冲/双缓冲的区别
 GLUT_SINGLE  0x0000 单缓冲窗口
 GLUT_DOUBLE  0x0002 双缓冲窗口
 GLUT_SINGLE  单缓冲,屏幕调用显示使用glFlush,将图像在当前显示缓存中直接渲染，会有图形跳动(闪烁)问题
 GLUT_DOUBLE  双缓冲,屏幕显示调用glutSwapBuffers()将图像先绘制在另外的缓存中，渲染完毕之后，将其整个缓存贴到当前的窗口，能消除闪烁,一般动画要用双缓冲.
 !!!以上两者的调用方式必须匹配,如果GLUT_DOUBLE模式下调用glFlush，会造成问题，可
 在Review/ClearWindow下试验
 */

