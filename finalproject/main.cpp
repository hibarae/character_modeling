
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "MeshFactory.h"
#include "ObjMesh.h"
#include <math.h>

using namespace std;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Idle();
void MakeViewPort(int x, int y, int width, int height, int eye);
void Grid();
void Keyboard(unsigned char key, int x, int y);

ObjMesh objMesh;
ObjMesh objMesh1,objMesh2,objMesh3,objMesh4;
int width = 800;
int height = 640;

float camPos[3] = { 0, 15, 25 };
float cntPos[3] = { 0, 6, 0 };

//위치 지정 카메라
float eyeOne[3] = { 20,10,10 };
float eyeTwo[3] = { 0,30,4 };
float eyeThree[3] = { 0,10,20 };
float eyeFour[3] = { 20,30,20 };

void Random(int radom) {
	int random = 0;
	for (int i = 9; i < 10; i++) {
		random = rand() % 9;
	}
}

void init_light() {// 라이트 적용 //enter를 누르면 적용!!
	GLfloat light_0_pos[] = { 1 ,1, 1, 1 };
	GLfloat light_0_ambient[] = { 0.5, 0.5 ,0.5, 1.0 };
	GLfloat light_0_diffuse[] = { 2.0, 2.0 ,2.0 , 1.0 };
	GLfloat light_0_specular[] = { 2.0, 2.0 , 2.0 , 1.0 };

	glShadeModel(GL_SMOOTH); // 구로 세이딩 모델
	glEnable(GL_DEPTH_TEST); // depth test

	glLightfv(GL_LIGHT1, GL_POSITION, light_0_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING); // 조명
}

void Init()
{
	CMeshFacotry::LoadObjModel("uuu.obj", &objMesh);

	glDepthFunc(GL_LESS); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing

	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black

	glEnable(GL_SMOOTH);
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Grid();

	/*glPushMatrix();
	static float a = 0;
	glTranslatef(0, 6, 0);
	glRotatef(a += 0.05, 0, 1, 0);
	objMesh.Render();
	glPopMatrix();*/

	//MakeViewPort(width / 2, height / 2, width / 2, height / 2, 1);	//1사분면
	//MakeViewPort(0, height / 2, width / 2, height / 2, 2);		//2사분면
	//MakeViewPort(0, 0, width / 2, height / 2, 3);				//3사분면
	//MakeViewPort(width / 2, 0, width / 2, height / 2, 4);			//4사분면

	//위
	glViewport(0, height / 2, width / 2, height / 2);

	glLoadIdentity();

	gluLookAt(camPos[0], 300, 100, cntPos[0], cntPos[1], cntPos[2], 1.0, 0.0, 0.0);

	glColor3f(0.0f, 0.0f, 1.0f);

	objMesh.Render();



	//오른쪽

	glViewport(width / 2, height / 2, width / 2, height / 2);

	glLoadIdentity();

	gluLookAt(camPos[0], 300, 300, cntPos[0], cntPos[1], cntPos[2], 0.0, 1.0, 0.0);

	glColor3f(0.0f, 1.0f, 1.0f);

	objMesh.Render();



	//왼쪽

	glViewport(0, 0, width / 2, height / 2);

	glLoadIdentity();

	gluLookAt(camPos[0], 300, 300, cntPos[0], cntPos[1], cntPos[2], 0.0, 1.0, 0.0);

	glColor3f(1.0f, 0.0f, 0.0f);

	objMesh.Render();



	//랜덤
	
	glViewport(width / 2, 0, width / 2, height / 2);

	glLoadIdentity();

	gluLookAt(camPos[0], 300, 300, cntPos[0], cntPos[1], cntPos[2], 0.0, 1.0, 0.0);

	glColor3f(0.0f, 1.0f, 0.0f);

	objMesh.Render();
	
	glutSwapBuffers(); //swap the buffers




	init_light(); //조명 출력
	//glutPostRedisplay();
	//glutSwapBuffers();
	
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100000.0);
	glMatrixMode(GL_MODELVIEW);
}



void Idle()
{
	Display();
}

void Grid()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	for (int i = -50; i < 50; i++)
	{
		glBegin(GL_LINES);
		glNormal3f(0, 1, 0);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++)
	{
		glBegin(GL_LINES);
		glNormal3f(0, 1, 0);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

	glPopMatrix();
}

void MakeViewPort(int x, int y, int width, int height, int eye) {
	//화면 출력 문자열
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glViewport(x, y, 800, 640);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (eye == 1) { gluLookAt(eyeOne[0], eyeOne[1], eyeOne[2], 0, 10, eyeOne[2], 0.0, 0.1, 0.0); }
	else if (eye == 2) { gluLookAt(eyeTwo[0], eyeTwo[1], eyeTwo[2], eyeTwo[0], 10, -5, 0.0, 0.1, 0.0); }
	else if (eye == 3) { gluLookAt(eyeThree[0], eyeThree[1], eyeThree[2], eyeThree[0], 10, 0, 0.0, 0.1, 0.0); }
	else if (eye == 4) { gluLookAt(eyeFour[0], eyeFour[1], eyeFour[2], eyeFour[0] - 20, 10, 0, 0.0, 0.1, 0.0); }
	//오브젝트 렌더링
	objMesh1.Render();
	objMesh2.Render();
	objMesh3.Render();
	objMesh4.Render();

	glDisable(GL_TEXTURE_2D);	//다른 객체들에게 영향x	
	glPopMatrix();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		eyeOne[0] -= 0.6;
		eyeTwo[1] -= 0.6;
		eyeThree[2] -= 0.6;

		eyeFour[0] -= 0.62;
		eyeFour[1] -= 0.62;
		eyeFour[2] -= 0.62;
		break;
	case GLUT_KEY_DOWN:
		eyeOne[0] += 0.6;
		eyeTwo[1] += 0.6;
		eyeThree[2] += 0.6;

		eyeFour[0] += 0.62;
		eyeFour[1] += 0.62;
		eyeFour[2] += 0.62;
		break;
	case GLUT_KEY_LEFT:
		eyeOne[2] -= 0.6;
		eyeTwo[0] += 0.6;
		eyeThree[0] += 0.6;
		eyeFour[0] += 0.6;
		break;
	case GLUT_KEY_RIGHT:
		eyeOne[2] += 0.6;
		eyeTwo[0] -= 0.6;
		eyeThree[0] -= 0.6;
		eyeFour[0] -= 0.6;
		break;
	}
	glutPostRedisplay();

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 640);
	glutCreateWindow("20174014 서재원");
	Init();	
	glutIgnoreKeyRepeat(0);

	glutDisplayFunc(Display);
	
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutIdleFunc(Idle);

	glutMainLoop();

	return 0;
}

