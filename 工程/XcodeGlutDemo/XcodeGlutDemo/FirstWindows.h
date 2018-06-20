//
//  FirstWindows.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/4/25.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef FirstWindows_h
#define FirstWindows_h

#include <GLUT/GLUT.h>

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);       //清除
    glRectf(-0.5f, -0.5, 0.5, 0.5);     //设置两个点的坐标
    glFlush();                          //立即执行
}

/*
 #define GL_CURRENT_BIT                    0x00000001       当前的Bit
 #define GL_POINT_BIT                      0x00000002       点Bit
 #define GL_LINE_BIT                       0x00000004       线Bit
 #define GL_POLYGON_BIT                    0x00000008       多边形
 #define GL_POLYGON_STIPPLE_BIT            0x00000010       多边形点画 polygon-stipple
 #define GL_PIXEL_MODE_BIT                 0x00000020       像素 pixel
 #define GL_LIGHTING_BIT                   0x00000040       光照 lignting
 #define GL_FOG_BIT                        0x00000080       雾 fog
 #define GL_DEPTH_BUFFER_BIT               0x00000100       深度缓存 depth-buffer
 #define GL_ACCUM_BUFFER_BIT               0x00000200       累积缓存 accum-buffer
 #define GL_STENCIL_BUFFER_BIT             0x00000400       模板缓存 stencil-buffer
 #define GL_VIEWPORT_BIT                   0x00000800       视口 viewport
 #define GL_TRANSFORM_BIT                  0x00001000       变换 transform
 #define GL_ENABLE_BIT                     0x00002000       启用 enable
 #define GL_COLOR_BUFFER_BIT               0x00004000       颜色缓存 color-buffer
 #define GL_HINT_BIT                       0x00008000       建议 hint
 #define GL_EVAL_BIT                       0x00010000       求值 eval
 #define GL_LIST_BIT                       0x00020000       列表 list
 #define GL_TEXTURE_BIT                    0x00040000       纹理 texture
 #define GL_SCISSOR_BIT                    0x00080000       裁剪 scissor
 #define GL_ALL_ATTRIB_BITS                0x000fffff       所有属性组
 */

void initHook(int argc, char * argv[]){
    glutInit(&argc, argv); //初始化,必须
    //GLUT_RGB 使用RGB色值
    //GLUT_INDEX 使用索引色
    //GLUT_SINGLE  使用单缓冲
    //GLUT_DOUBLE  使用双缓冲
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(100, 100); //设置窗口在屏幕中的位置
    glutInitWindowSize(400, 400); //设置窗口的大小
    glutCreateWindow("第一个OpenGL程序");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
}

#endif /* FirstWindows_h */
