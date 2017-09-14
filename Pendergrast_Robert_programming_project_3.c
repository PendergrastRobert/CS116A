#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include <math.h>
GLuint image;
float rotatingImage;
char ch = '1';
float X_AXIS=0.0f;
float Z_AXIS=-1.0f;
float Y_AXIS=0.0f;

float x=-1.0f;
float z=1.0f;

float VIEW_ANGLE=0.0f;
float HEIGHT=1.0f;
void loadObj(char *fname){
    FILE *fp;
    int read;
    char ch;
    GLfloat x, y, z;

    image = glGenLists(1);
    fp = fopen(fname,"r");
    if (!fp){
        printf("ERROR: UNABLE TO READ FILE %s\n", fname);
        exit(1);
    }
    glPointSize(1.0);
    glNewList(image, GL_COMPILE);{
        glPushMatrix();
        glBegin(GL_POINTS);
        while(!(feof(fp))){
            read=fscanf(fp,"%c %f %f %f", &ch, &x, &y, &z);
            if(read == 4 && ch =='v'){ 
                glVertex3f(5000 * x, 5000 * y, 5000 * z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (60,(GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawImage(){
    glPushMatrix();

    glTranslatef(0,-40.00,-105);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(rotatingImage,0,1,0);
	gluLookAt(x,HEIGHT+=Y_AXIS,z,x+X_AXIS,HEIGHT,z+Z_AXIS,0.0f,1.0f,0.0f);
    glCallList(image);
    glPopMatrix();

}

void display(void){
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    drawImage();
    glutSwapBuffers(); 
}

void processSpecialKeys(int key,int xx,int yy)
{
	float INCREASE_AXIS=1.0f;
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
		VIEW_ANGLE-=0.05f;
		X_AXIS=sin(VIEW_ANGLE);
		Z_AXIS=-cos(VIEW_ANGLE);
			glutPostRedisplay();
	break;
	case GLUT_KEY_RIGHT:
		VIEW_ANGLE+=0.05f;
		X_AXIS=sin(VIEW_ANGLE);
		Z_AXIS=-cos(VIEW_ANGLE);
			glutPostRedisplay();	
	}
}

void processNormalKeys(unsigned char key,int x,int y){
	switch(key){
		case 'w':
			exit(1);
			break;
		case 's':
			exit(1);
			break;
	}
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Project 3");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
    loadObj("bunny.obj");
    glutMainLoop();
    return 0;
}
