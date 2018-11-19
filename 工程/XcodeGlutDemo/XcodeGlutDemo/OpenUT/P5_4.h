//
//  P5_4.h
//  XcodeGlutDemo
//
//  Created by admin on 2018/10/29.
//  Copyright © 2018年 李帅哲. All rights reserved.
//

#ifndef P5_4_h
#define P5_4_h

//#include <GLTools.h>
#include "GLTools.h"
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>
#include "GLToolEx.h"

static GLfloat zPos = -60.0f;

#define TEXTURE_BRICK 0
#define TEXTURE_FLOOR 1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT 3
GLuint textures[TEXTURE_COUNT];
const char *szTextureFiles[TEXTURE_COUNT] = { "/Users/lishuaizhe/Documents/knowledge/工程/XcodeGlutDemo/brick.tga", "/Users/lishuaizhe/Documents/knowledge/工程/XcodeGlutDemo/floor.tga", "/Users/lishuaizhe/Documents/knowledge/工程/XcodeGlutDemo/ceiling.tga" };

//为每个纹理对象个性纹理过滤器
/*
 GL_LINEAR 采用插值的原理，填充内部的颜色，这样可以让两者之前平衡过度
 GL_NEAREST 采用就近色值，所以这种颜色区分较明显，会有锯齿
 GL_REPEAT: 看名称就能猜出，在纹理没有覆盖的部分重复之前的纹理。
 GL_CLAMP_TO_EDGE：延续结束时的纹理
 GL_MIRRORED_REPEAT：将原来的纹理先颠倒再重复。
 */
void ProcessMenu( int value )
{
    GLint iLoop;
    
    for ( iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++ )
    {
        glBindTexture( GL_TEXTURE_2D, textures[iLoop] );
        
        switch( value )
        {
            case 0:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
                break;
            case 1:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                break;
            case 2:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
                break;
            case 3:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
                break;
            case 4:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
                break;
            case 5:
            default:
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
                break;
        }
    }
    
    glutPostRedisplay();
}

void SetupRC()
{
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    GLint iLoop;
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    
    glEnable( GL_TEXTURE_2D );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
    /*glTexEnvi(GLenum target, GLenum pname, GLint param)
     纹理环境指定在对片段进行纹理处理时如何解释纹理值。
     target 纹理环境 - 必须是 GL_TEXTURE_ENV
     pname  单值纹理环境参数的符号名称。必须是 GL_TEXTURE_ENV_MODE
     param  单个符号常量 GL_MODULATE  GL_DECAL, GL_BLEND, GL_REPLACE 之一
     */
    
    //载入纹理
    /*
     glGenTextures (GLsizei n, GLuint *textures)
     1.n 个数  2.textures 可用纹理索引数组
     返回纹理名数组.
     在调用glGenTextures函数之前，没有任何返回的名称可以立即使用
     glGenTextures返回的纹理名称不会被后续的glGenTextures调用返回，除非它们首先通过调用glDeleteTextures删除
     */
    
    /*
     glBindTexture (GLenum target, GLuint texture) 绑定纹理
     将纹理名称绑定到相应的纹理目标。当纹理绑定到目标时，该目标的先前绑定不再有效。
     target 的参数为 GL_TEXTURE_1D  GL_TEXUTURE_2D
     texture 为无符号整数
     ！！！一定不能放在glBegin()   glEnd()中否则绑定无效
     glBindTexture实际上是改变了OpenGL的状态，告诉Opengl下面对纹理的任何操作都是基于当前所绑定纹理对象的
     有个重复绑定的坑 https://www.cnblogs.com/vernon/articles/1885223.html
     */
    /*
     GLint gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data)
     创建2D的minimap
     target目标纹理,必须是GL_TEXTURE_2D
     internalFormat 为什么样的组合形式GL_RGBA8  GL_RGB8
     format 像素数据的格式。必须是以下之一：GL_COLOR_INDEX，GL_RED，GL_GREEN，GL_BLUE，GL_ALPHA，GL_RGB，GL_RGBA，GL_BGR_EXT，GL_BGRA_EXT，GL_LUMINANCE或GL_LUMINANCE_ALPHA
     type 为数据类型数据。必须是以下之一：GL_UNSIGNED_BYTE，GL_BYTE，GL_BITMAP，GL_UNSIGNED_SHORT，GL_SHORT，GL_UNSIGNED_INT，GL_INT或GL_FLOAT
     data 指向内存中图像数据的指针
     */
    
    /*
     glTexParameteri (GLenum target, GLenum pname, GLint param)
     设置纹理参数
     target 目标纹理，必须是GL_TEXTURE_1D  GL_TEXTURE_2D
     pname 单值纹理参数的符号名称
        GL_TEXUTRE_WRAP_S  s方向上拉伸
        GL_TEXTURE_WRAP_T  t方向上拉伸
        GL_TEXTURE_MAG_FILTER  当纹理小于要映射的对象时使用 是一张放大处理  magnification
        GL_TEXTURE_MIN_FILTER  当纹理大于要映射的对象时使用 是一种缩小处理  minify
     param 拉伸方式
        
     */
    glGenTextures( TEXTURE_COUNT, textures );
    for ( iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++ )
    {
        glBindTexture( GL_TEXTURE_2D, textures[iLoop] );
        
        pBytes = gltLoadTGA( szTextureFiles[iLoop], &iWidth, &iHeight, &iComponents, &eFormat );
        gluBuild2DMipmaps( GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes );
        
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        
        free( pBytes );
    }
    
    //开启各向异性过滤
//    if ( gltIsExtSupported( "GL_EXT_texture_filter_anisotropic" ) )
//    {
//        GLfloat fLargest;
//        glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest );
//
//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest );
//    }
}

void ShutdownRC()
{
    glDeleteTextures( TEXTURE_COUNT, textures );
}

void SpecialKeys( int key, int x, int y )
{
    if ( key == GLUT_KEY_UP )
    {
        zPos += 1.0f;
    }
    
    if ( key == GLUT_KEY_DOWN )
    {
        zPos -= 1.0f;
    }
    
    glutPostRedisplay(); //重新绘制
}

void ChangeSize( int w, int h )
{
    GLfloat fAspect;
    
    if ( h == 0 )
    {
        h = 1;
    }
    
    glViewport( 0, 0, w, h );
    
    fAspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective( 90.0f, fAspect, 1, 120 ); //设置透视摄像机
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void RenderScene()
{
    GLfloat z;
    
    glClear( GL_COLOR_BUFFER_BIT );
    
    glPushMatrix();
    glTranslatef( 0.0f, 0.0f, zPos );
    
    /*
     glTexCoord2f (GLfloat s, GLfloat t) 设置纹理坐标系
     s: 0代表纹理左侧  1代表纹理右侧
     t: 0代表纹理底部  1代表纹理上部
     这个函数一般和glVertex3f组合使用,需要把对应的纹理贴合到指定的地方
     必须左上、左下、右上、右下 对应的贴合
     glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, 1.0 );
     glTexCoord2f( 1.0, 0.0 ); glVertex3f( 1.0, -1.0, 1.0 );
     glTexCoord2f( 1.0, 1.0 ); glVertex3f( 1.0, 1.0, 1.0 );
     glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0, 1.0, 1.0 );
     */
    for ( z = 60.0f; z >= 0.0f; z -= 10 )
    {
        //地面
        glBindTexture( GL_TEXTURE_2D, textures[TEXTURE_FLOOR] );
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); //设置纹理坐标
        glVertex3f( -10.0f, -10.0f, z );
        
        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 10.0f, -10.0f, z );

        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 10.0f, -10.0f, (z - 10.0f) );
        
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -10.0f, -10.0f, (z - 10.0f) );
        glEnd();
        
        //天花板
        glBindTexture( GL_TEXTURE_2D, textures[TEXTURE_CEILING] );
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -10.0f, 10.0f, z - 10.0f );

        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 10.0f, 10.0f, z - 10.0f );

        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 10.0f, 10.0f, z );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -10.0f, 10.0f, z );
        glEnd();

        //左墙
        glBindTexture( GL_TEXTURE_2D, textures[TEXTURE_BRICK] );
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -10.0f, -10.0f, z );

        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( -10.0f, -10.0f, z - 10.0f );

        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( -10.0f, 10.0f, z - 10.0f );

        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -10.0f, 10.0f, z );
        glEnd();

        //右墙
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( 10.0f, 10.0f, z );

        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 10.0f, 10.0f, z - 10.0f );

        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 10.0f, -10.0f, z - 10.0f );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( 10.0f, -10.0f, z );
        glEnd();
    }
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void initHook( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "Tunnel" );
    glutReshapeFunc( ChangeSize );
    glutSpecialFunc( SpecialKeys );
    glutDisplayFunc( RenderScene );
    
    //创建菜单
    glutCreateMenu( ProcessMenu ); //设置回调
    glutAddMenuEntry( "GL_NEAREST", 0 ); //设置选项
    glutAddMenuEntry( "GL_LINEAR", 1 );
    glutAddMenuEntry( "GL_NEAREST_MIPMAP_NEAREST", 2 );
    glutAddMenuEntry( "GL_NEAREST_MIPMAP_LINEAR", 3 );
    glutAddMenuEntry( "GL_LINEAR_MIPMAP_NEAREST", 4 );
    glutAddMenuEntry( "GL_LINEAR_MIPMAP_LINEAR", 5 );
    glutAttachMenu( GLUT_RIGHT_BUTTON ); //设置怎么样可以响应菜单//这个是鼠标右键
    
    SetupRC();
    glutMainLoop();
    ShutdownRC();
    
}

#endif /* P5_4_h */
