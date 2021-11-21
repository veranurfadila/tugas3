#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void cylinder(float rbase, float rtop, float height);
void pipe(float rbase, float rtop, float height, int resolusi);
void blok(float tebal, int ratiol, int ratiop);

double rotation_y = 0, rotation_y_plis = -15, direction;
double Move = 30, Movep = 0;
double rotate_All = 0;

GLfloat ambient_light[] = { 0.0,0.0,0.0,0.0 };
GLfloat source_light[] = { 1.0,0.0,1.0,1.0 };
GLfloat light_pos[] = { 100,100.0,0.0,4.0 };

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

void draw3D(void)
{
	glClearColor(0.0, 1.0, 0.0, 0.1); //white
	glShadeModel(GL_SMOOTH);
	glViewport(10, 100, 480, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(58.0, (GLfloat)640 / (GLfloat)480, 1.0, 200.0);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, source_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_pos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

GLUquadricObj* quadObj;

void display(void)
{
	quadObj = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0., -90);
	glPushMatrix();
	glRotatef(1.0, 1.0, 1.0, 1.0);
	glRotatef(rotate_All, 1.0, 1.0, 1.0);

	Move++;
	Move = Move - Movep;
	glRotatef(Move, 0.0, 1.0, 0.1);
	Movep = 10;
	glTranslatef(1.0, 0.0, 0.);

	
	glColor3f(0, 0, 0);
	glTranslatef(0.0, 0, 0);
	//glRotatef(180, 1, 0, 0);
	pipe(1.1, 0, 2.1, 10);

	glColor3f(10, 3, 0);
	glTranslatef(0.0, 0, -4.6);
	//glRotatef(180, 1, 0, 0);
	pipe(2.7, 0, 6.10, 10);

	glColor3f(0, 0, 1);
	glTranslatef(0, 0, -42);
	//glRotatef(-39, 1, 0, 0);
	cylinder(1, 0.6, 40.10);

	glColor3f(1, 5, 0);
	glTranslatef(0, 0, -7);
	//glRotatef(-39, 1, 0, 0);
	cylinder(1, 0.0, 20.90);

	glColor3f(1, 0, 0);
	glTranslatef(0, 0, 28);
	gluCylinder(quadObj, 5.412, 4.25, 8, 50, 50);

	glColor3f(0, 1, 0);
	glTranslatef(0, 0, -17.5);
	gluCylinder(quadObj, 1.9, 8, 8, 50, 50);

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void cylinder(float rbase, float rtop, float height)
{
	float i;
	glPushMatrix();
	glTranslatef(0, 0.0, -rbase / 4);
	for (i = 0;i <= height;i += rbase / 8)
	{
		glTranslatef(0, 0.0, rbase / 8);
		glutSolidTorus(3, rbase - ((i * (rbase - rtop)) / height), 20, 16);
	}
	glTranslatef(0, 0.0, rbase / 4);
	glPopMatrix();
}

void pipe(float rbase, float rtop, float height, int resolusi)
{
	float i;
	glPushMatrix();
	glTranslatef(0.0, 0.0, -rbase / 4);
	for (i = 0;i <= height;i += rbase / 8)
	{
		glTranslatef(0.0, 0.0, rbase / 8);
		glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
	}
	glTranslatef(0.0, 0.0, rbase / 4);
	glPopMatrix();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pencil");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	draw3D();
	glutMainLoop();
	return 0;

	vec3 ambient = pipe * lightColor * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = cylinder	* lightColor * (diff * material.diffuse);
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = blok * lightColor * (spec * material.specular);
	vec3 result = ambient + diffuse + specular;
	FragColor = vec3(result, 1.0);

}