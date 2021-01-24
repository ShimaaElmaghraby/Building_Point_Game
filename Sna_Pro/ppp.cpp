#include<iostream>
#include <Windows.h>
#include <ctime>
#include <GL\glut.h>
#include <GL\GL.h>
using namespace std;

int Cx=0,Cy=0,Cz=0;
int gridx=40,gridy=40,gridz=40;
int foodX,foodY,foodZ;
float ratio;
extern short sDirection;
bool game=false;
bool food=true;



void init( ){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
}
void reshape(int h,int w){
		glViewport(0,0,w,h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(double)1000/800,0.1f,100);
		glMatrixMode(GL_MODELVIEW);
}

void timer( int v ){
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);

}


void theCube(){
	glPushMatrix();
    glColor3f(1,1,1);
	glTranslatef(Cx,Cy,Cz);
	glutSolidCube(.6);
	glPopMatrix();


}

void theCube2(){
	glPushMatrix();
    glColor3f(1,1,1);
	glTranslatef(1,0,0);
	glutSolidCube(.6);
	glPopMatrix();
}

void drawgrid(){
int i;
for (i=0;i<=100;i++){
	glPushMatrix();
	if (i<50){
		glTranslatef(0,0,i);
	}
	if (i>=50){
		glTranslatef(i-50,0,0);
		glRotatef(-90,0,1,0);
	}
	glBegin(GL_LINES);
	glColor3f(0,225,225);
	glLineWidth(1);
	glVertex3f( 0,-0.1,0);
    glVertex3f(19,-0.1,0);
	glEnd();
	glPopMatrix();
}

}
int index=0;
void display()

{   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13,0,-45);
	glRotatef(40,1,1,0);
		drawgrid();
		glRectd(index,20,index+2,22);
		index++;
		if(index>40){
		index=0;
		
		}
		  theCube();
		   theCube2();
		drawfood();
   glutSwapBuffers();


}

void random(int &x,int &y ){

			int maxX=gridx-2;
			int maxY=gridy-2;
			
			int min=1;
			srand(time(NULL));
			rand();
			x=min-rand() %(maxX-min);
			y=min-rand() %(maxY-min);
			
}
void drawfood(){

if (food)
	random(foodX,foodY);
    food=false;
	glRectf(foodX,foodY,foodX+1,foodY+1);


}
void keyboard ( unsigned char key, int x, int y){
	if( key == 27)
		exit(0);
}

void special(int key, int x, int y){

	switch (key)
	{
	case GLUT_KEY_LEFT:
	Cx-=1;
		break;
	case GLUT_KEY_RIGHT:
		Cx+=1;
		break;
	case GLUT_KEY_DOWN:
	Cz+=1;
		break;
	case GLUT_KEY_UP:
	Cz-=1;
		break;
	
	}
		glutPostRedisplay();	
}
void mainn(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1000,00);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Snake");
	glutFullScreen();
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	init();
    glutMainLoop();

}