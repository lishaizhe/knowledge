//
//  main.cpp
//  TestGL
//
//  Created by admin on 2018/9/1.
//  Copyright © 2018年 admin. All rights reserved.
//

#include <iostream>
#include <GLShaderManager.h>
#include <GLTools.h>
#include <GLUT/GLUT.h>

int main(int argc, const char * argv[]) {
//    gltSetWorkingDirectory(argv[0]);
//    glutInit(&argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    return 0;
}
