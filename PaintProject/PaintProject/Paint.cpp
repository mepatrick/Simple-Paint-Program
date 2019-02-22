#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
using namespace std;

float red = 1.0, green = 0.0, blue = 0.0;
int shape = 1; //1 = brush, 2 = line, 3 = box, 4 = circle
int brushSize = 2;
bool second = false;
static int width = 640, height = 480;
int firstx = 0.0;
int firsty = 0.0;
int secondx = 0.0;
int secondy = 0.0;
int numVertices = 1000;

void setup() {
	glClearColor(1.0, 1.0, 1.0, 1.0);//red,green,blue,alpha
	//cord system for "Real World"
	glMatrixMode(GL_PROJECTION); //uses marties to transform cords from one to the other
	//projection putting something from 3d image and putting it into 2d plane
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0); //left,right,bottom,top

}

void drawSquare() {
//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(red, blue, green);
	/*
	glBegin(GL_POLYGON); //used to draw a square
	//vetices of polygon
	glVertex2f(20.0, 20.0);
	glVertex2f(80.0, 20.0);
	glVertex2f(80.0, 80.0);
	glVertex2f(20.0, 80.0);

	glEnd();*/
	glFlush();
}

void circle(int x1, int y1, int x2, int y2) {
	y1 = height - y1;
	y2 = height - y2;
	float rx = (x1 + x2)/2;
	float ry = (y1 + y2)/2;
	int dx = x2 - x1; //delt x
	int dy = y2 - y1; //delta y
	float D = sqrt((pow(dx,2)) + (pow(dy,2))); //use distance formula 
	float R = D / 2; //radius 
	float t = 0.0;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numVertices; i++) {
		glVertex2f(rx + R * cos(t), ry + R * sin(t));
		t += 2 * 3.1415 / numVertices;
	}
	glEnd();
	glFlush();
	//int r = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void box(int x, int y, int x2, int y2) {
	//a^2 + b^2 = c^2
	y = height - y;
	y2 = height - y2;
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y); //top left
	glVertex2f(x, y2); //bottom left
	glVertex2f(x2, y2); //bottom right
	glVertex2f(x2, y); //top right
	glEnd();

}

void line(int x, int y, int x2, int y2) {
	y = height - y;
	y2 = height - y2;
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}


void brush(int x, int y) {
	
	glColor3f(red, blue, green);
	glBegin(GL_POLYGON);
	glVertex2f(x-brushSize, y-brushSize);
	glVertex2f(x+brushSize, y-brushSize);
	glVertex2f(x+brushSize, y+brushSize);
	glVertex2f(x-brushSize, y+brushSize);
	glEnd();
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		y = height - y;
		//glViewport(x, y, 200, 200);
		if (shape == 1) { //brush
			brush(x, y);
		}
		if (shape == 2 && second == false) {
			firstx = x;
			firsty = height - y;
			second = true;
			cout << second <<endl; //0 false, 1 true
			cout << firstx << endl;
			cout << firsty << endl;
		}
		else if (shape == 2 && second == true) {
			secondx = x;
			secondy = height - y;
			line(firstx, firsty,secondx,secondy);
			second = false;
			cout << second << endl;
			cout << secondx << endl;
			cout << secondy << endl;
		}
		else if (shape == 3 && second == false) {
			firstx = x;
			firsty = height - y;
			second = true;
			cout << second << endl; //0 false, 1 true
			cout << firstx << endl;
			cout << firsty << endl;
		}
		else if (shape == 3 && second == true) {
			secondx = x;
			secondy = height - y;
			box(firstx, firsty, secondx, secondy);
			second = false;
			cout << second << endl;
			cout << secondx << endl;
			cout << secondy << endl;
		}
		else if (shape == 4 && second == false) {
			firstx = x;
			firsty = height - y;
			second = true;
			cout << second << endl; //0 false, 1 true
			cout << firstx << endl;
			cout << firsty << endl;
		}
		else if (shape == 4 && second == true) {
			secondx = x;
			secondy = height - y;
			circle(firstx, firsty, secondx, secondy);
			second = false;
			cout << second << endl;
			cout << secondx << endl;
			cout << secondy << endl;
		}
		
	}
	else{
		
	}
	//glutPostRedisplay(); //recalls any display function you already have
}

void mouseMove(int x, int y) {
	//stuff
	//glViewport(x, (480 - y), 200, 200);
	if (shape == 1) { //brush
		y = height - y;
		brush(x, y);
	}
}


void mainMenu(int value) {

}
/*Will clear everything on screen, and will change background color to chosen color*/
void backMenu(int value) {
	if (value == 1) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else if (value == 2) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else {
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void colorMenu(int value) {
	if (value == 1) {
		red = 1.0;
		blue = 0.0;
		green = 0.0;
	}
	else if (value == 2) {
		red = 0.0;
		blue = 1.0;
		green = 0.0;
	}
	else if(value == 3) {
		red = 0.0;
		blue = 0.0;
		green = 1.0;
	}
	else {
		red = 0.0;
		blue = 0.0;
		green = 0.0;
	}
	glutPostRedisplay();
}

void shapeMenu(int value) {
	if (value == 1) {
		shape = 1;
	}
	else if (value == 2) {
		shape = 2;
	}
	else if(value == 3) {
		shape = 3;
	}
	else {
		shape = 4;
	}
}

void clearMenu(int value) {
	if (value == 1) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void widthMenu(int value) {
	if (value == 1) {
		brushSize = 2;
	}
	else if (value == 2) {
		brushSize = 4;
	}
	else if (value == 3) {
		brushSize = 6;
	}
	else {
		brushSize = 8;
	}
}

void menu() {
	int backmenu = glutCreateMenu(backMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Blue", 2);

	int colormenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);

	int shapemenu = glutCreateMenu(shapeMenu);
	glutAddMenuEntry("Brush", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Sqaure", 3);
	glutAddMenuEntry("Circle", 4);

	int width = glutCreateMenu(widthMenu);
	glutAddMenuEntry("2px", 1);
	glutAddMenuEntry("4px", 2);
	glutAddMenuEntry("6px", 3);
	glutAddMenuEntry("8px", 4);

	int clearmenu = glutCreateMenu(clearMenu);
	glutAddMenuEntry("Clear",1);

	int main = glutCreateMenu(mainMenu);
	glutAddSubMenu("Backg", backmenu);
	glutAddSubMenu("Color", colormenu);
	glutAddSubMenu("Shapes", shapemenu);
	glutAddSubMenu("Width", width);
	glutAddSubMenu("Clear", clearmenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) { //** means pointer to another pointer
	glutInit(&argc, argv); //initialize Glut (library that will do windowing part) 
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(640, 480); //sets window size

	glutInitWindowPosition(100, 100);//where windows shows up on my screen

	glutCreateWindow("Paint Project");//title of window
	setup();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(drawSquare); //when you want to display, use this function
	glutMouseFunc(myMouse);
	/*
	glutKeyboardFunc(keyFunc); //used for keyboard events
	glutMouseFunc(mouse2);*/
	glutMotionFunc(mouseMove); //good for paint program
	
	menu();
	glutMainLoop();
}