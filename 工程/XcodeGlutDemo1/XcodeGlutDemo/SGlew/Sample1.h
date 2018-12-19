//
//  Sample1.h
//  XcodeGlutDemo
//
//  Created by 李帅哲 on 2018/6/27.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef Sample1_h
#define Sample1_h

#include <iostream>
#include <GLShaderManager.h>
#include <GLTools.h>
#include <GLUT/GLUT.h>


//圆周率宏
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH=0;
GLint SCREEN_HEIGHT=0;
//设置程序的窗口大小
GLint windowWidth=400;
GLint windowHeight=300;
//绕x轴旋转角度
GLfloat xRotAngle=0.0f;
//绕y轴旋转角度
GLfloat yRotAngle=0.0f;
//显示回调函数
void renderScreen(void){
    GLfloat x,y,z,angle;
    //把整个窗口清理为当前清理颜色：黑色
    glClear(GL_COLOR_BUFFER_BIT);
    //将当前Matrix状态入栈
    glPushMatrix();
    //坐标系绕x轴旋转xRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //坐标系绕y轴旋转yRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
    
    //进行平滑处理
    /*
     glHint (GLenum target, GLenum mode) 对于抗锯齿进行设置
     针对对象
     GL_POINT_SMOOTH  点
     GL_LINE_SMOOTH  线
     GL_POLYGON_SMOOTH 多边形
     模式为
     GL_DONT_CARE 放弃,系统默认设置
     GL_FASTEST  速度优先
     GL_NICEST   质量优先
     */
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH,GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH,GL_NICEST);
    //使用白色绘制坐标系
    glColor3f(1.0f,1.0f,1.0f);
    //绘制坐标系
    glBegin(GL_LINES);
    glVertex3f(-80.0f,0.0f,0.0f);
    glVertex3f(80.0f,0.0f,0.0f);
    glVertex3f(0.0f,-80.0f,0.0f);
    glVertex3f(0.0f,80.0f,0.0f);
    glVertex3f(0.0f,0.0f,-80.0f);
    glVertex3f(0.0f,0.0f,80.0f);
    glEnd();
    
    //////////////////////////////////绘制三角箭头 开始//////////////////////////////
    /*
     void glutWireSphere(GLdouble radius, GLint slices, GLint stacks); 线框球
     void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks); 实心球
     
     void glutWireCube(GLdouble size); 线框立方体
     void glutSolidCube(GLdouble size); 实心立方体
     
     void glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings); 线框圆环
     void glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings); 实心圆环
     
     void glutWireIcosahedron(void); 线框20面体
     void glutSolidIcosahedron(void); 实心20面体
     
     void glutWireOctahedron(void); 线框8面体
     void glutSolidOctahedron(void); 实心8面体
     
     void glutWireTetrahedron(void); 线框4面体
     void glutSolidTetrahedron(void); 实心4面体
     
     void glutWireDodecahedron(GLdouble radius); 线框12面体
     void glutSolidDodecahedron(GLdouble radius); 实心12面体
     
     void glutWireCone(GLdouble radius, GLdouble height, GLint slices, GLint stacks); 线框圆锥体
     void glutSolidCone(GLdouble radius, GLdouble height, GLint slices, GLint stacks); 实心圆锥体
     radius  指的是底座长度,也就是三角形的底边长度
     height  指的是三角形的高度
     slices  指的是围绕z轴分隔的数目 [简单理解为沿着当前坐标系的z轴方向,垂直于z轴的线的数目]
     stacks  指的是沿着z轴方向分隔线的数目
     
     void glutWireTeapot(GLdouble size); 线框茶壶
     void glutSolidTeapot(GLdouble size); 实心茶壶
     */
    glPushMatrix();
    glTranslatef(80.0f,0.0f,0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutWireCone(10,6,10,10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,80.0f,0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glutWireCone(10,6,10,10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,0.0f,80.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glutWireCone(10,6,10,10);
    glPopMatrix();
    //////////////////////////////////绘制三角箭头 结束//////////////////////////////
    
    
    //坐标系平移到(-50.0f,0.0f,00.0f)
    glPushMatrix();
    glTranslatef(-50.0f,0.0f,00.0f);
    //白色绘制五个顶点
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(25.0f,25.0f,0.0f);
    glVertex3f(0.0f,50.0f,0.0f);
    glVertex3f(-25.0f,25.0f,0.0f);
    glVertex3f(-25.0f,0.0f,0.0f);
    glEnd();
    //GL_FLAT使用单色模式填充三角形
    //GL_SMOOTH使用颜色平滑变换模式填充三角形
    glShadeModel(GL_FLAT);
    //使用GL_TRIANGLE_STRIP绘制三角形
    /*
     关于绘制三角形线的顺序
     GL_TRIANGLES  每3个定点形成一个三角形  [v0,v1,v2] [v3,v4,v5]各点不共用
     GL_TRIANGLE_STRIP 复用点  如果对应于当前点是奇数,则和之前的点结合形成三角形,v0,v1,v2,v3,v4,v5  [v0,v1,v2] 现在为3奇数了,则为[n-1,n-2,n] 如果为偶数则为[n-2,n-1,n] 这个地方只是改变的各个点连接的顺序而已
     GL_TRIANGLE_FAN 各个点也是为复用，不过不同的是，它的各个点的组合为 [n-1,n-2,n]
     */
    
    glBegin(GL_TRIANGLE_STRIP);
    //使用红色绘制第一个三角形
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(25.0f,25.0f,0.0f);
    glVertex3f(0.0f,50.0f,0.0f);
    //使用绿色绘制第二个三角形
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(-25.0f,25.0f,0.0f);
    //使用蓝色绘制第三个三角形
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(-25.0f,0.0f,0.0f);
    //结束GL_TRIANGLE_STRIP绘制三角形
    glEnd();
    glPopMatrix();
    
    //坐标系平移到(50.0f,0.0f,00.0f)
    glPushMatrix();
    glTranslatef(50.0f,0.0f,00.0f);
    //白色绘制五个顶点
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(25.0f,25.0f,0.0f);
    glVertex3f(0.0f,50.0f,0.0f);
    glVertex3f(-25.0f,25.0f,0.0f);
    glVertex3f(-25.0f,0.0f,0.0f);
    glEnd();
    //GL_FLAT使用单色模式填充三角形
    //GL_SMOOTH使用颜色平滑变换模式填充三角形
    glShadeModel(GL_SMOOTH);
    //使用GL_TRIANGLE_STRIP绘制三角形
    glBegin(GL_TRIANGLE_STRIP);
    //使用红色绘制第一个三角形
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(25.0f,25.0f,0.0f);
    glVertex3f(0.0f,50.0f,0.0f);
    //使用绿色绘制第二个三角形
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(-25.0f,25.0f,0.0f);
    //使用蓝色绘制第三个三角形
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(-25.0f,0.0f,0.0f);
    //结束GL_TRIANGLE_STRIP绘制三角形
    glEnd();
    glPopMatrix();
    
    //恢复压入栈的Matrix
    glPopMatrix();
    //交换两个缓冲区的指针
    glutSwapBuffers();
}
//设置Redering State
void setupRederingState(void){
    //设置清理颜色为黑色
    glClearColor(0.0f,0.0,0.0,1.0f);
    //设置绘画颜色为绿色
    glColor3f(0.0f,1.0f,0.0f);
}
//窗口大小变化回调函数
void changSize(GLint w,GLint h){
    //横宽比率
    GLfloat ratio;
    //设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)
    GLfloat coordinatesize=100.0f;
    //窗口宽高为零直接返回
    if((w==0)||(h==0))
        return;
    //设置视口和窗口大小一致
    glViewport(0,0,w,h);
    //对投影矩阵应用随后的矩阵操作
    glMatrixMode(GL_PROJECTION);
    //重置当前指定的矩阵为单位矩阵
    glLoadIdentity();
    ratio=(GLfloat)w/(GLfloat)h;
    //正交投影
    //glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
    //在这个区域内
    if(w == h)
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
    else
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
    //对模型视图矩阵堆栈应用随后的矩阵操作
    glMatrixMode(GL_MODELVIEW);
    //重置当前指定的矩阵为单位矩阵
    glLoadIdentity();
}

//按键输入处理回调函数
void specialKey(int key,int x,int y){
    
    if(key==GLUT_KEY_UP){
        xRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_DOWN){
        xRotAngle+=5.0f;
    }
    else if(key==GLUT_KEY_LEFT){
        yRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_RIGHT){
        yRotAngle+=5.0f;
    }
    //重新绘制
    glutPostRedisplay();
}

int initHook(int argc, char* argv[])
{
    //初始化glut
    glutInit(&argc,argv);
    //使用双缓冲区模式
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    //获取系统的宽像素
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //获取系统的高像素
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
    //创建窗口，窗口名字为OpenGL TriAngleStrip Demo
    glutCreateWindow("OpenGL TriAngleStrip Demo");
    //设置窗口大小
    glutReshapeWindow(windowWidth,windowHeight);
    //窗口居中显示
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
    //窗口大小变化时的处理函数
    glutReshapeFunc(changSize);
    //设置显示回调函数
    glutDisplayFunc(renderScreen);
    //设置按键输入处理回调函数
    glutSpecialFunc(specialKey);
    //设置全局渲染参数
    setupRederingState();
    glutMainLoop();
    return 0;
}


#endif /* Sample1_h */
