#define STB_IMAGE_IMPLEMENTATION
#define fbs 10
#include<Windows.h>
#include<iostream>
#include <gl/stb_image.h>
#include<gl/glut.h>
#include<ctime>
using namespace std;
int Cx=0,Cy=0,Cz=0;
bool food=true;
bool gameover=false;
unsigned int texture;
int width, height, nrChannels;
unsigned char *data = NULL;
bool fullScreen;
float ratio , angle ,eyey, eyez , eyex , upx , upz = -20 ;
int x,z;
struct quad{ int x1,x2,z1,z2;
}q[100];
int lensnake=0;
void background();
void mydraw();
void reshape( int , int );
void timer( int );
void keyboard ( unsigned char , int , int );
void specialKeyboard (int , int , int);
void load ( int imgnum );
void check (unsigned char *data);



void main ( int argc , char** argv){
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
	glutInit( &argc , argv);
	glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE);
	glutInitWindowSize(width,height);
	glutCreateWindow(" 3D shapes and animation");
	//glutFullScreen();
	background();
	glutDisplayFunc(mydraw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMainLoop();
}

void background(){
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST); //give permission to use 3d 
	glEnable(GL_TEXTURE_2D); //to use pictures in border of the game 
}
//bta3t al mok3b el byt7rak 
void theCube(){
	
	glPushMatrix();
 //   glColor3f(1,1,1);
	glTranslatef(Cx,0,Cz);
	 q[0].x1=0;
	 q[0].z1=1;
	//bootom
	   glBegin(GL_QUADS);
	   glColor3f(0,1,1);
	   glVertex3i(0, 0, 0);
	   glVertex3i(1, 0, 0);
	   glVertex3i(1, 0, 1);
	   glVertex3i(0, 0, 1);
	   glEnd();
	   //face
	   glBegin(GL_QUADS);
	   glColor3f(0,1,1);
	   glVertex3i(1, 0, 1);
	   glVertex3i(1, 1, 1);
	   glVertex3i(0, 1, 1);
	   glVertex3i(0, 0, 1);
	   glEnd();
	   //left
	   glBegin(GL_QUADS);
	   glColor3f(0,1,1);
	   glVertex3i(0, 0, 1);
	   glVertex3i(0, 1, 1);
	   glVertex3i(0, 1, 0);
	   glVertex3i(0, 0, 0);
	   glEnd();
	   //top
	   glBegin(GL_QUADS);
	   glColor3f(0,1,1);
	   glVertex3i(1, 0, 1);
	   glVertex3i(1, 0, 0);
	   glVertex3i(1, 1, 0);
	   glVertex3i(1, 1, 1);
	   glEnd();
	   //
	   glBegin(GL_QUADS);
	   glColor3f(0,1,1);
	   glVertex3i(0, 0, 0);
	   glVertex3i(1, 0, 0);
	   glVertex3i(1, 1, 0);
	   glVertex3i(0, 1, 0);
	   glEnd();
	
	   for (int i =0;i<lensnake;i++){
		   q[i].x1=q[0].x1+i;
	    glBegin(GL_QUADS);
	   glColor3f(0,0,1);
	   glVertex3i(0, q[i].x1, 0);
	   glVertex3i(1, q[i].x1, 0);
	   glVertex3i(1, q[i].x1, 1);
	   glVertex3i(0, q[i].x1, 1);
	   glEnd();
	   
	   //rigth
	   glBegin(GL_QUADS);
	   glColor3f(1,1,1);
	   glVertex3i(1, q[i].x1, 0);
	   glVertex3i(1, q[i].x1, 1);
	   glVertex3i(1, q[i].x1+1, 1);
	   glVertex3i(1,q[i].x1+1, 0);
	   glEnd();
	   //front
	     glBegin(GL_QUADS);
	   glColor3f(1,1,1);
	   glVertex3i(1, q[i].x1, 1);
	   glVertex3i(1, q[i].x1+1, 1);
	   glVertex3i(0, q[i].x1+1, 1);
	   glVertex3i(0, q[i].x1, 1);
	   glEnd();
	   //back
	     glBegin(GL_QUADS);
	   glColor3f(1,1,1);
	   glVertex3i(1, q[i].x1, 0);
	   glVertex3i(1, q[i].x1+1, 0);
	   glVertex3i(0, q[i].x1+1, 0);
	   glVertex3i(0, q[i].x1, 0);
	   glEnd();
	   //left
	  glBegin(GL_QUADS);

	   glColor3f(1,1,1);
	    glVertex3i(1, q[i].x1, 1);
	    glVertex3i(1, q[i].x1+1, 1);
	   glVertex3i(1, q[i].x1+1, 0);
	   glVertex3i(1, q[i].x1, 0);
	   glEnd();
	   //top
	    glBegin(GL_QUADS);

	   glColor3f(1,0,1);
	   glVertex3i(0, q[i].x1+1, 0);
	   glVertex3i(1, q[i].x1+1, 0);
	   glVertex3i(1, q[i].x1+1, 1);
	   glVertex3i(0, q[i].x1+1, 1);
	   glEnd();	    
	   

	  }glPopMatrix();
	 /*  if(lensnake==5&&(Cx==9 && Cz==9)){
		   MessageBox(NULL,"WIN","SCore",MB_ICONEXCLAMATION | MB_OK);
		exit(0);
		   
	   }*/
	  
	   if(lensnake==6){
		   MessageBox(NULL,"Win!!your score :5","score",MB_ICONEXCLAMATION | MB_OK);
		exit(0);
		}

}
// da al code al feh al loop al rasmet 18*18 orba3 lel background 
void drawgrid(){
int i;
for (i=0;i<40;i++){
	glPushMatrix();
	if (i<20){
		glTranslatef(0,0,i);
	}
	if (i>=20){
		glTranslatef(i-20,0,0);
		glRotatef(-90,0,1,0);
	}
	// load(2);
	glBegin(GL_LINES);
	glColor3f(1,.6,.5);
	glLineWidth(1);
	glVertex3f( 0,-0.1,0);
    glVertex3f(19,-0.1,0);

	glEnd();
	glPopMatrix();
}

}
// al 7agez al f al borders al abyad da  
void drawboxes(){
	glPushMatrix();
	//back
	load(2); //to get picture from function 
		glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glColor3f(1,.6,.5);
		glTexCoord2d(0.0f,0.0f);
		glVertex3i(19, 0, 0);
	    glTexCoord2d(1.0f,0.0f);
		glVertex3i(19, 5, 0);
		glTexCoord2d(1.0f,1.0f);
		glVertex3i(0,5, 0);
		glTexCoord2d(0.0f,1.0f);
		glVertex3i(0, 0, 0);
		glEnd();
		glPopMatrix();
		//right
		glPushMatrix();
		// load(2);
		glBegin(GL_QUADS);
		glColor3f(1,.6,.5);
      //   glTexCoord2d(0.0f,0.0f);
		glVertex3i(19, 5, 20);
	//	glTexCoord2d(1.0f,0.0f);
		glVertex3i(19, 5, 0);
		//glTexCoord2d(1.0f,1.0f);
		glVertex3i(19, 0,0 );	
		//glTexCoord2d(0.0f,1.0f);
		glVertex3i(19, 0, 20);	
		glEnd();
		glPopMatrix();
		//front
		glPushMatrix();
		//load(2);
		glBegin(GL_QUADS);
		glColor3f(1,.6,.5);
     //    glTexCoord2d(0.0f,0.0f);
		glVertex3i(19, 0, 20);
	//	glTexCoord2d(1.0f,0.0f);
		glVertex3i(19, 1, 20);
	//	glTexCoord2d(1.0f,1.0f);
		glVertex3i(0, 1,20 );	
	//	glTexCoord2d(0.0f,1.0f);
		glVertex3i(0, 0, 20);	
		glEnd();
		glPopMatrix();
		//left
		glPushMatrix();
		// load(2);
		glBegin(GL_QUADS);
		glColor3f(1,.6,.5);
        
		glVertex3i(0, 5, 20);

		glVertex3i(0, 5, 0);
			
		glVertex3i(0, 0,0 );	
		glVertex3i(0, 0, 20);	
		glEnd();
	
		glPopMatrix();

}
void drawfood(){

	glPushMatrix();
	 srand((unsigned)time(NULL));  
	if (Cx==x && Cz==z){
	   lensnake++;
	   food=true;
	   cout<<lensnake<<endl;
	      }
	else
		food=false;
		 if(food){
	     x=rand()%18;
		 z=rand()%18;}
		 //bottom
	     load(1);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f,0.0f);
		glVertex3i(x, 0,z+1);
		glTexCoord2d(1.0f,0.0f);
		glVertex3i(x+1, 0,z+1);	
		glTexCoord2d(1.0f,1.0f);
		glVertex3i(x+1, 0,z);
		glTexCoord2d(0.0f,1.0f);
		glVertex3i(x, 0,z);	
		glEnd();
		glPopMatrix();
	
		 
}

void mydraw(){
	glClear( GL_COLOR_BUFFER_BIT |	GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt( eyex , eyey , eyez ,
				upx , eyey , upz ,
				0, 1 , 0);
	glTranslatef(-10,2,-60);
	glRotatef(35,1,0,0);
	drawgrid();
	theCube();
    drawboxes();
	drawfood();
	glutSwapBuffers();
	if(gameover){
		MessageBox(NULL,"oooooh","gameover",MB_ICONEXCLAMATION | MB_OK);
		exit(0);
	
	}
}

void reshape( int w , int h ){
	if( h == 0 ) h = 1 ;
	ratio = w / (float)h ; 
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(42,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard ( unsigned char key, int x, int y){
		angle += 4;
	if( key == 27)
		exit(0);
	if( key == 'a')
	{
		upx -= .9*cos(.1);
		upz -= .9 * sin(.1);
	}
	if( key == 'd'){
		upx += .9*cos(.1);
		upz += .9 * sin(.1);
	}
	if( key == 'w')
	{
		eyez -= 5;
		eyey = .3*abs(cos(angle));
	}
	if( key == 's'){
		eyez += 5;
		eyey = .3*abs(cos(angle));
	}

}

void specialKeyboard (int key, int x, int y){
	if( key == GLUT_KEY_F1){
		fullScreen = !fullScreen;
		if(fullScreen)
			glutFullScreen();
		else{
			glutPositionWindow(10,10);
			glutReshapeWindow(600,600);
		}
	}
	
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if(Cx-1>=0)
	      Cx-=1;
		else gameover=true;
		break;
	case GLUT_KEY_RIGHT:
		if(Cx+1<19)
			Cx+=1;
		else gameover=true;
		break;
	case GLUT_KEY_DOWN:
		if(Cz+1<19)
	      Cz+=1;
		else gameover=true;
		break;
	case GLUT_KEY_UP:
		if(Cz-1>=0)
	      Cz-=1;
		else gameover=true;

		break;
		
	}
	
		glutPostRedisplay();	
}
void timer( int v ){
	glutPostRedisplay();
     glutTimerFunc(30,timer,0);
	
}
void load ( int imgnum ){
	if( imgnum == 1){
		
		data= stbi_load("th.jpg", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if( imgnum == 2){
		
		data= stbi_load("wood-floor.jpg", &width, &height, &nrChannels, 0);
		check(data);
	}
}

void check (unsigned char *data){
	if (data)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
}
