#include<iostream>
#include<Windows.h>
#include<GL/glut.h>
#include <GL/gl.h>
#include<GLFW/glfw3.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "primitivas.h"

float angulo = 0.0;
float n1 = 0, n2 = 0, n3 = 0;
float intensidade = 1.0;
float intensidadeSol = 1.0;
float intensidadeCeu = 1.0;
float moverx = -1.0;
float moverCamerax = 0.0;
float moverCameraFrent = 1.0;
int i = 0;
glm::vec3 posicao_camera = glm::vec3(0.0, 0.0, 0.1);

void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);

}

void desenha()
{

	if (n1 == 1) {
		moverx += 0.019;
		intensidade += 0.001;
		if (moverx >= -2.0) {
			moverx = -1.0;
		}
		if (intensidade >= 1) {
			intensidade = 1.0;
		}
		if (moverx <= -10.00) {
			
			intensidadeSol += 0.01;
			intensidadeCeu += 0.001;
			if (intensidadeSol <= 1.0) {
				intensidadeSol = 1.0;

			}if (intensidadeCeu >= 1.0) {
				intensidadeCeu = 1.0;

			}
		}
		
		if (intensidade >= 1) {
			intensidade = 1.0;
		}
	}
	if (n2 == 2) {
		intensidade -= 0.001;
		moverx -= 0.019;
		if (moverx <= -25.00) {
			moverx = -25.00;
		}
		if (moverx <= -10.00) {
			intensidadeSol -= 0.001;
			intensidadeCeu -= 0.001;
			if (intensidadeCeu <= 0.01) {
				intensidadeCeu = 0.001;
			}
			if (intensidadeSol <= 0.1) {
				intensidadeSol = 0.1;
			}
		}
		if (intensidade < 0.2) {
			intensidade = 0.2;
		}



	}


	desenhaCeu(intensidadeCeu);
	glm::vec3 nova_posicao_camera = glm::vec3(moverCamerax, 0.0, 0.1);
	posicao_camera = nova_posicao_camera;
	// Matriz de visão
	glm::mat4 view = glm::lookAt(
		posicao_camera,  // Posição da câmera
		glm::vec3(0.0, 0.0, 0.0),  // Ponto para onde a câmera está olhando
		glm::vec3(0.0, 1.0, 0.0)   // Vetor que indica a direção "para cima" da câmera
	);

	// Passa a matriz de visão para o OpenGL
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(view));

	glEnable(GL_DEPTH_TEST);
	desenhaTerreno(intensidade);

	desenhaSol(intensidadeSol, moverx); // Desenha o sol
	glClear(GL_DEPTH_BUFFER_BIT);
	angulo += 0.5;

	desenhaPoste(4, angulo);
	desenhaCasa(20.0, -20.0, -150.0);
	desenhaCasa(20.0, -20.0, -80.0);
	desenhaCasa(20.0, -20.0, -100.0);
	desenhaCasa(20.0, -20.0, -200.0);
	desenhaCasa(20.0, -20.0, -150.0);
	desenhaCasa(20.0, -20.0, -50.0);
	desenhaCasa(20.0, -20.0, -180.0);
	desenhaCasa(20.0, -20.0, -250.0);
	desenhaCasa(20.0, -20.0, -350.0);
	desenhaCasa(20.0, -20.0, -480.0);
	desenhaCasa(20.0, -20.0, -550.0);

	desenhaCasa(-10.0, -20.0, -150.0);
	desenhaCasa(-10.0, -20.0, -80.0);
	desenhaCasa(-10.0, -20.0, -100.0);
	desenhaCasa(-10.0, -20.0, -200.0);
	desenhaCasa(-10.0, -20.0, -150.0);
	desenhaCasa(-10.0, -20.0, -50.0);
	desenhaCasa(-10.0, -20.0, -180.0);
	desenhaCasa(-10.0, -20.0, -250.0);
	desenhaCasa(-10.0, -20.0, -350.0);
	desenhaCasa(-10.0, -20.0, -480.0);
	desenhaCasa(-10.0, -20.0, -550.0);

	desenhaCasa(-30.0, -20.0, -150.0);
	desenhaCasa(-30.0, -20.0, -80.0);
	desenhaCasa(-30.0, -20.0, -100.0);
	desenhaCasa(-30.0, -20.0, -200.0);
	desenhaCasa(-30.0, -20.0, -150.0);
	desenhaCasa(-30.0, -20.0, -50.0);
	desenhaCasa(-30.0, -20.0, -180.0);
	desenhaCasa(-30.0, -20.0, -250.0);
	desenhaCasa(-30.0, -20.0, -350.0);
	desenhaCasa(-30.0, -20.0, -480.0);
	desenhaCasa(-30.0, -20.0, -550.0);



	desenhaCasa(-100.0, -20.0, -100.0);
	desenhaCasa(-100.0, -20.0, -200.0);
	desenhaCasa(-100.0, -20.0, -180.0);
	desenhaCasa(-50.0, -20.0, -250.0);
	desenhaCasa(-50.0, -20.0, -350.0);
	desenhaCasa(-300.0, -20.0, -480.0);
	desenhaCasa(-200.0, -20.0, -550.0);


}
void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		i = 7;

	}
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		n1 = 1;
		n2 = 0;

	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		n2 = 2;
		n1 = 0;

	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		moverCamerax -= 0.1;

	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		moverCamerax += 0.1;
	}
}

void mouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		moverCamerax = 0.00;
	}
}
int main(void)
{

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(600, 400, "Animacao", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	int largura, altura;
	time_t inicio = time(NULL);

	// Aguarda 5 segundos
	while (difftime(time(NULL), inicio) < 5) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imagens("primeira.jpeg");
	}
	inicio = time(NULL);
	while (difftime(time(NULL), inicio) < 5) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imagens("inicio.jpg");
	}
	while (i != 7)
	{
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwSetKeyCallback(window, teclado);
		glfwSetMouseButtonCallback(window, mouse);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glfwGetFramebufferSize(window, &largura, &altura);
		redimensiona(largura, altura);
		desenha();
	}

	inicio = time(NULL);

	// Aguarda 5 segundos
	while (difftime(time(NULL), inicio) < 5) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imagens("ultima.jpg");
	}
	return 0;

}
