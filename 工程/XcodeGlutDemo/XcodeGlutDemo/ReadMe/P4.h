//
//  P4.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/15.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

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
