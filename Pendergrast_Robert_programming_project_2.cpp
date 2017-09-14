#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//Robert Pendergrast

float X_AXIS=0.0f;
float Z_AXIS=-1.0f;
float Y_AXIS=0.0f;

float x=-1.0f;
float z=1.0f;

float VIEW_ANGLE=0.0f;
float HEIGHT=1.0f;

int ROWS=100;
int COLUMNS=100;
//function to draw the triangle grid
void drawTriangleGrid(int ROWS,int COLUMNS){
	/*double arr[500] = { };
	for (int i = 0; i < 500; i++){
		arr[i] = (rand()%3);	
	}*/
  	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  	glColor3f(1.0,0.0,0.0);
	float LENGTH=100.0f/(float)ROWS;
  	float WIDTH=-100.0f/(float)COLUMNS;
	//loop draws the triangle strip into a grid, allowing for even spacing
  	for (int i=0;i<COLUMNS;i++){
  	  	float x_vert=-1.0+i*WIDTH;
  	  	glBegin(GL_TRIANGLE_STRIP);

  		for (int j=0;j<=ROWS;j++){
			//float r=(rand()%3);
  			float z_vert=-100.0+j*LENGTH;
      		glVertex3f(x_vert,0.0,z_vert);
      		glVertex3f(x_vert+LENGTH,0.0,z_vert);
    	}
    	glEnd();
  	} 
//This was my poor late-night attempt at solving the algorithm
/*	int index = 0;
	for (x = 0; x < 50; x++){
		glBegin(GL_TRIANGLES);
		for (z = 0; z < 10; z++){
			y = arr[index];
			glVertex3f(x,y,z);
			glVertex3f(x+10,y,z);
			glVertex3f(x+10,y,z+10);
			glVertex3f(x,y,z);
			glVertex3f(x,y,z+10);
			glVertex3f(x,y+10,z+10);
    //		y = randomized value between 0 and 5 (or whatever height you want max);
    //		Draw Triangle: (x,y,z) to (x+10,y,z) to (x+10,y,z+10)
    //		Draw Triangle: (x,y,z) to (x,y,z+10) to (x+10,y,z+10)
			index++;
   		}
		glEnd();
	}*/
}
//arrow keys require SpecialKeys function to be called 
void processSpecialKeys(int key,int xx,int yy)
{
	float INCREASE_AXIS=0.1f;
	switch(key){
	case GLUT_KEY_UP:
		x+=X_AXIS*INCREASE_AXIS;
		z+=Z_AXIS*INCREASE_AXIS;
			glutPostRedisplay();
	break;
	case GLUT_KEY_DOWN:
		x-=X_AXIS*INCREASE_AXIS;
		z-=Z_AXIS*INCREASE_AXIS;
			glutPostRedisplay();
	break;	
	case GLUT_KEY_LEFT:
		//VIEW_ANGLE as a negative float allows the angle to move to the left
		VIEW_ANGLE-=0.05f;
		//pressing left causes a viewing shift to the left. 
		//the sin and -cos of VIEW_ANGLE are calculated to determine this
		X_AXIS=sin(VIEW_ANGLE);
		Z_AXIS=-cos(VIEW_ANGLE);
			glutPostRedisplay();
	break;
	case GLUT_KEY_RIGHT:
		//VIEW_ANGLE as a positive float allows the angle to move to the right
		VIEW_ANGLE+=0.05f;
		//pressing left causes a viewing shift to the left. 
		//the sin and -cos of VIEW_ANGLE are calculated to determine this
		X_AXIS=sin(VIEW_ANGLE);
		Z_AXIS=-cos(VIEW_ANGLE);
			glutPostRedisplay();	
	}
}
//NormalKeys required for 'a' and 'z' keys
void processNormalKeys(unsigned char key,int x,int y){
	switch(key){
		case 'a':
			HEIGHT+=0.05;
				glutPostRedisplay();
			break;
		case 'z':
			HEIGHT-=0.05;
				glutPostRedisplay();
			break;
	}
}
//renders the scene and adds the camera to the image and calls the drawing function
void render(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
  	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	gluLookAt(x,HEIGHT+=Y_AXIS,z,x+X_AXIS,HEIGHT,z+Z_AXIS,0.0f,1.0f,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
	//calls triangle drawing function
	drawTriangleGrid(ROWS,COLUMNS);
	glutSwapBuffers();
}

void resize(int width_local,int height_local){
	float PERSPECTIVE_HEIGHT=width_local*1/height_local;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//adds the camera perspective and viewing angle
	gluPerspective(20.0f,PERSPECTIVE_HEIGHT,0.2f,0.0f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv){
	//boiler code for openGL
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Programming Project 2");
	//basic required glut functions to render the scene
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	//calling to allow for keyboard functionality
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
	return 1;
}


