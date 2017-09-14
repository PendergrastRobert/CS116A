//Robert Pendergrast
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800
int clicks = 0;
GLsizei X_START = 0;
GLsizei Y_START = 0;
GLsizei X_END = 0;
GLsizei Y_END = 0;
GLsizei POS_X_0 = 0;
GLsizei POS_Y_0 = 0;
GLsizei POS_X_1 = 0;
GLsizei POS_Y_1 = 0;
GLsizei POS_X_2 = 0;
GLsizei POS_Y_2 = 0;
GLsizei POS_X_3 = 0;
GLsizei POS_Y_3 = 0;

void rectangleOutline(){
    if(clicks==2){
        clicks=0;
        glBegin(GL_LINE_LOOP);
        glVertex3f(X_START, Y_START, 0);
        glVertex3f(X_END, Y_START, 0);
        glVertex3f(X_END, Y_END, 0);
        glVertex3f(X_START, Y_END, 0);
        glEnd();
        glFlush();
    } 
}
void rectangleFill(){
    if(clicks==2){
        clicks=0;
        glBegin(GL_POLYGON);
        glVertex3f(X_START, Y_START, 0);
        glVertex3f(X_END, Y_START, 0);
        glVertex3f(X_END, Y_END, 0);
        glVertex3f(X_START, Y_END, 0);
        glEnd();
        glFlush();
    }
}
void ellipseOutline(){
    if(clicks==2){
        clicks=0;
        glBegin(GL_LINE_LOOP);
        float x;
		float y;
		float i;
        float max=fabs(X_START-X_END);
        float min=fabs(Y_START-Y_END);
        for (i=0;i<2*M_PI;i=i+M_PI/12){
            x=cos(i)*max/2;
            y=sin(i)*min/2;
            glVertex2f((X_START+X_END)/2+x,(Y_START+Y_END)/2+y);
        }
        glEnd();
        glFlush();
    }
}

void ellipseFill(){
    if (clicks==2){
        clicks=0;
        glBegin(GL_POLYGON);
        float x;
		float y;
		float i;
        float max=fabs(X_START-X_END);
        float min=fabs(Y_START-Y_END);
        for(i=0;i<2*M_PI;i=i+M_PI/12){
            x=cos(i)*max/2;
            y=sin(i)*min/2;
            glVertex2f((X_START+X_END)/2+x,(Y_START+Y_END)/2+y);
        }
        glEnd();
        glFlush();
    }
}
void line(){
    if (clicks==2){
        clicks=0;
        glBegin(GL_LINES);
        glVertex3f(X_START,Y_START,0);
        glVertex3f(X_END,Y_END,0);
        glEnd();
        glFlush();
    }
}
void bezierCurve(){
    GLfloat i;
	GLfloat temp;
	GLfloat xStart;
	GLfloat yStart;
	GLfloat xEnd;
	GLfloat yEnd;
    if(clicks>=1){
        if((POS_X_0>10)&&(POS_X_0<(WIDTH-10))&&(POS_Y_0>10)&&(POS_Y_0<(HEIGHT-10))){
            glBegin(GL_LINES);
            glVertex3f(POS_X_0-10,POS_Y_0,0);
            glVertex3f(POS_X_0+10,POS_Y_0,0);
            glVertex3f(POS_X_0,POS_Y_0-10,0);
            glVertex3f(POS_X_0,POS_Y_0+10,0);
            glEnd();
            glFlush();
        }
    }
    if(clicks>=2){
        if((POS_X_1>10)&&(POS_X_1<(WIDTH-10))&&(POS_Y_1>10)&&(POS_Y_1<(HEIGHT-10))){
            glBegin(GL_LINES);
            glVertex3f(POS_X_1-10,POS_Y_1,0);
            glVertex3f(POS_X_1+10,POS_Y_1,0);
            glVertex3f(POS_X_1,POS_Y_1-10,0);
            glVertex3f(POS_X_1,POS_Y_1+10,0);
            glEnd();
            glFlush();
        }
    }
    if(clicks>=3){
        if((POS_X_2>10)&&(POS_X_2<(WIDTH-10))&&(POS_Y_2>10)&&(POS_Y_2<(HEIGHT-10))){
            glBegin(GL_LINES);
            glVertex3f(POS_X_2-10,POS_Y_2,0);
            glVertex3f(POS_X_2+10,POS_Y_2,0);
            glVertex3f(POS_X_2,POS_Y_2-10,0);
            glVertex3f(POS_X_2,POS_Y_2+10,0);
            glEnd();
            glFlush();
        }
    }
    if(clicks>=4){
        if((POS_X_3>10)&&(POS_X_3<(WIDTH-10))&&(POS_Y_3>10)&&(POS_Y_3<(HEIGHT-10))){
            glBegin(GL_LINES);
            glVertex3f(POS_X_3-10,POS_Y_3,0);
            glVertex3f(POS_X_3+10,POS_Y_3,0);
            glVertex3f(POS_X_3,POS_Y_3-10,0);
            glVertex3f(POS_X_3,POS_Y_3+10,0);
            glEnd();
            glFlush();
        }
    }
    if(clicks==4){
        clicks=0;
        xStart=0;
        yStart=0;
        xEnd=0;
        yEnd=0;
        glBegin(GL_LINES);
        for(i=0;i<=1;i=i+0.01){
            temp=1-i;
            xEnd=temp*temp*temp*POS_X_0+3*temp*temp*i*POS_X_1
				+3*temp*i*i*POS_X_2+i*i*i*POS_X_3;
            yEnd=temp*temp*temp*POS_Y_0+3*temp*temp*i*POS_Y_1
				+3*temp*i*i*POS_Y_2+i*i*i*POS_Y_3;
            if(i>0){
                glVertex3f(xStart,yStart,0);
                glVertex3f(xEnd,yEnd,0);
            }
            xStart=xEnd;
            yStart=yEnd;
        }
        glEnd();
        glFlush();
    }
}
void coloring(char color){
    switch(color){
        case '1':
            glColor3ub(255,0,0);
            break;
        case '2':
            glColor3ub(0,255,0);
            break;
        case '3': 
            glColor3ub(0,0,255);
            break;            
        case '4': 
            glColor3ub(255,255,0);
            break;            
        case '5': 
            glColor3ub(255,0,255);
            break;            
        case '6': 
            glColor3ub(255,128,0);
            break;            
        case '7': 
            glColor3ub(255,255,255);
            break;            
        case '8': 
            glColor3ub(0,0,0);
            break;            
        default: 
			break;
    }
}
void fillingRectangle(int button,int pos,int x,int y){
    if ((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        if(clicks==1){
			X_START=x;
            Y_START=y;
        }
        else{
            if(clicks==2){
                X_END=x;
                Y_END=y;
            }
            else{
                clicks=0;
            }
        }
        rectangleFill();
    }
}
void fillingRectangleOutline(int button,int pos,int x,int y){
    if((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        if(clicks==1){
            X_START=x;
            Y_START=y;
        }
        else{
            if(clicks==2){
                X_END=x;
                Y_END=y;
            }
            else{
                clicks=0;
            }
        }
        rectangleOutline();
    }
}
void fillingEllipse(int button,int pos,int x,int y){
    if((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        if(clicks==1){
            X_START=x;
            Y_START=y;
        }
        else{
            if(clicks==2){
                X_END=x;
                Y_END=y;
            }
            else{
                clicks=0;
            }
        }
        ellipseFill();
    }
}
void fillingEllipseOutline(int button,int pos,int x,int y){
    if ((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        if(clicks==1){
            X_START=x;
            Y_START=y;
        }
        else{
            if(clicks==2){
                X_END=x;
                Y_END=y;
            }
            else{
                clicks=0;
            }
        }
        ellipseOutline();
    }
}
void fillingLine(int button,int pos,int x,int y){
    if ((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        if (clicks==1){
            X_START=x;
            Y_START=y;
        }
        else{
            if(clicks==2){
                X_END=x;
                Y_END=y;
            }
            else
                clicks=0;
		}
        line();
    }
}
void fillingBezierCurve(int button,int pos,int x,int y){
    if((button==GLUT_RIGHT_BUTTON)&&(pos==GLUT_DOWN)){
        clicks++;
        switch(clicks){
            case 1:
                POS_X_0=x;
                POS_Y_0=y;
                break;
            case 2:
                POS_X_1=x;
                POS_Y_1=y;
                break;
            case 3:
                POS_X_2=x;
                POS_Y_2=y;
                break;
            case 4:
                POS_X_3=x;
                POS_Y_3=y;
                break;
            default:
                clicks=0;
                break;
        }
        bezierCurve();
    }
}
void filledRectMenu(int caseIndex){
    switch(caseIndex){
        case 1:
            coloring('1');
            glutMouseFunc(fillingRectangle);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingRectangle);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingRectangle);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingRectangle);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingRectangle);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingRectangle);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingRectangle);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingRectangle);
            break;
    }
}
void outlineRectMenu(int caseIndex){
    switch(caseIndex){
        case 1:
            coloring('1');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingRectangleOutline);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingRectangleOutline);
            break;
    }
}
void filledEllipseMenu(int caseIndex){
    switch(caseIndex){
        case 1:
            coloring('1');
            glutMouseFunc(fillingEllipse);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingEllipse);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingEllipse);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingEllipse);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingEllipse);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingEllipse);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingEllipse);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingEllipse);
            break;
    }
}
void outlineEllipseMenu(int caseIndex){
    switch(caseIndex){
        case 1:
            coloring('1');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingEllipseOutline);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingEllipseOutline);
            break;
    }
}
void lineMenu(int caseIndex){
    switch(caseIndex) {
        case 1:
            coloring('1');
            glutMouseFunc(fillingLine);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingLine);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingLine);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingLine);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingLine);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingLine);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingLine);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingLine);
            break;
    }
}
void bezierCurveMenu(int caseIndex){
    switch(caseIndex) {
        case 1:
            coloring('1');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 2:
            coloring('2');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 3:
            coloring('3');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 4:
            coloring('4');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 5:
            coloring('5');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 6:
            coloring('6');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 7:
            coloring('7');
            glutMouseFunc(fillingBezierCurve);
            break;
        case 8:
            coloring('8');
            glutMouseFunc(fillingBezierCurve);
            break;
    }
}
void display(void){
    glClearColor(255.0, 255.0, 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    rectangleFill();
    rectangleOutline();
    ellipseFill();
    ellipseOutline();
    line();
    bezierCurve();
    glFlush();
}
void reshape(int w,int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,800,800,0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main (int argc, char *argv[]){
    int rectangleMenuChildren;
	int ellipseMenuChildren;
	int rectOutlineMenuChild;
	int rectFilledMenuChild;
	int ellipseOutlineMenuChild;
	int ellipseFilledMenuChild;
	int lineMenuChild;
	int bezierCurveMenuChild;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Final Drawing Project");
    
	rectFilledMenuChild=glutCreateMenu(filledRectMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    rectOutlineMenuChild=glutCreateMenu(outlineRectMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    ellipseFilledMenuChild=glutCreateMenu(filledEllipseMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    ellipseOutlineMenuChild=glutCreateMenu(outlineEllipseMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    lineMenuChild=glutCreateMenu(lineMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    bezierCurveMenuChild=glutCreateMenu(bezierCurveMenu);
    glutAddMenuEntry("red",1);
    glutAddMenuEntry("green",2);
    glutAddMenuEntry("blue",3);
    glutAddMenuEntry("yellow",4);
    glutAddMenuEntry("purple",5);
    glutAddMenuEntry("orange",6);
    glutAddMenuEntry("white",7);
    glutAddMenuEntry("black",8);
    rectangleMenuChildren=glutCreateMenu(lineMenu);
    glutAddSubMenu("filled",rectFilledMenuChild);
    glutAddSubMenu("outline",rectOutlineMenuChild);
    ellipseMenuChildren=glutCreateMenu(lineMenu);
    glutAddSubMenu("filled",ellipseFilledMenuChild);
    glutAddSubMenu("outline",ellipseOutlineMenuChild);

    glutCreateMenu(lineMenu);
    glutAddSubMenu("add rectangle",rectangleMenuChildren);
    glutAddSubMenu("add ellipse",ellipseMenuChildren);
    glutAddSubMenu("add line",lineMenuChild);
    glutAddSubMenu("add bezier curve",bezierCurveMenuChild);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(fillingRectangle);
    glutMouseFunc(fillingRectangleOutline);
    glutMouseFunc(fillingEllipse);
    glutMouseFunc(fillingEllipseOutline);
    glutMouseFunc(fillingLine);
    glutMouseFunc(fillingBezierCurve);
    glutMainLoop();
}
