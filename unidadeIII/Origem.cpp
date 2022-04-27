#include<Windows.h>
#include<GLFW/glfw3.h>
#include<gl/GLU.h>
#include<iostream>
#include "cores.h"
#include "primitivas.h"


static float angulo = 0.0;
static int n1 = 0, n2 = 0, n3 = 0, n4 = 0 , n5;
static float esferaL1 = 0.0, esferaL2 = 0.0;

//display list
unsigned int esferaID[3];
unsigned int terrenoID;

void redimensiona(int w, int h) 
{
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);

}

void desenha(float dt)
{
	float veloc_ang = 240.0* dt;
	glLoadIdentity();
	glCallList(terrenoID);
	
	glPushMatrix();
		glTranslatef(-20.0, 20.0, -100.0);
		glRotatef(angulo, 1.0, 1.0, 0.0);
		desenhaCubo(8.0);
	glPopMatrix();


	glPushMatrix();
		glTranslatef(20.0, 20.0, -100.0);
		glRotatef(angulo, 1.0, 1.0, 0.0);
		desenhaCubo(8.0);
	glPopMatrix();
	// cubo meio 
	glPushMatrix();
		glTranslatef(0.0, 20.0, -100.0);
		glRotatef(-angulo, 1.0, 1.0, 0.0);
		desenhaCubo(8.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(esferaL2, 5.0, -100.0);
	glRotatef(angulo, 1.0, 1.0, 0.0);
	glCallList(esferaID[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(esferaL1, 5.0, -100.0);
	glRotatef(angulo, 1.0, 1.0, 0.0);
	glCallList(esferaID[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 5.0, -100.0);
	glRotatef(angulo, 1.0, 1.0, 0.0);
	 glCallList(esferaID[2]);
	glPopMatrix();

	// gira 
	if (n1 == 1) 
		angulo += veloc_ang;

	// separa as esferas 
	if ((n2 == 2)){
		esferaL1 -= 0.005;
		esferaL2 += 0.005;

		if (esferaL1 <= -30)
			esferaL1 = -30;
		if (esferaL2 >= 30)
			esferaL2 = 30;
	}

	// para
	if ((n3 == 3)) {
		    angulo = angulo;
	}

	// junta as esferas
	if ((n4 == 4)) {
		esferaL2 -= 0.005;
		esferaL1 += 0.005;
		if (esferaL1 >= 0.0)
			esferaL1 = 0.0;
		if (esferaL2 <= 0.0)
			esferaL2 = 0.0;
	}

	//gira pro outro lado 
	if (n5 == 5) {
		angulo -= veloc_ang;
	}
}

void init() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //COR DO FUNDO
	glEnable(GL_DEPTH_TEST);

	esferaID[0]= glGenLists(3);
	esferaID[1] = esferaID[0] + 1;
	esferaID[2] = esferaID[0] + 2;

	terrenoID = esferaID[0] + 3;

	desenhaTerreno(terrenoID);

	desenhaEsfera(esferaID[0], verde, 5.0, 20.0, 20.0);
	desenhaEsfera(esferaID[1], laranja, 5.0, 20.0, 20.0);
	desenhaEsfera(esferaID[2], violeta, 5.0, 20.0, 20.0);

}

int main(void)
{

	/* Initialize the library */
	glfwInit();


	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "Desenha cubo", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	
	/* Loop until the user closes the window */

	// INICIO
	init();
	float valor = 0.0;
	float lastTime = 0.0;
	
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		float dt = currentTime - lastTime;
		lastTime = currentTime;
	
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			 n1 = 1;
			 n3 = 0;
			 n5 = 0;
		 

		}
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			n2 = 2;
			n3 = 0;
			n4 = 0;
		}
		else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			n3 = 3;
			n2 = 0;
			n1 = 0;
			n4 = 0;
			n5 = 0;
		}
		else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			n4 = 4;
			n2 = 0;

		}
		else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		{
			n5 = 5;
			n1 = 0;

		}
		

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);
		desenha(dt);
	}
	glDeleteLists(esferaID[0],4);
	glfwTerminate();
	return 0;
}
