// Triangles.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <GL/gl.h>

GLfloat x11 = -0.1f;
GLfloat y11 = -0.1f;
GLfloat x22 = 0.5f;
GLfloat y22 = 0.5f;


void Show()
{
	glClear(GL_COLOR_BUFFER_BIT);

	x11 += 0.001;
	y11 += 0.001;
	x22 -= 0.001;
	y22 -= 0.001;

	glRectf(x11, y11, x22, y22);
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(Show);
	glutMainLoop();

	return 0;

    //glfwInit
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
