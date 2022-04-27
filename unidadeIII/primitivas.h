#pragma once
#include<vector>
#include<cmath>

struct vec3 {
	float x, y, z;
	vec3() :x(0.0), y(0.0), z(0.0) {}
	vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
};

void react(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color cor)
{
	glColor3fv(cor);
	glBegin(GL_QUADS);
	glVertex3fv(&p1.x);
	glVertex3fv(&p2.x);
	glVertex3fv(&p3.x);
	glVertex3fv(&p4.x);
	glEnd();
}

void desenhaCubo(float s)
{
	float d = s / 2.0;

	vec3 v1(-d, d, d);
	vec3 v2(-d, -d, d);
	vec3 v3(d, -d, d);
	vec3 v4(d, d, d);

	vec3 v5(d, d, -d);
	vec3 v6(d, -d, -d);
	vec3 v7(-d, -d, -d);
	vec3 v8(-d, d, -d);

	// frente
	react(v1, v2, v3, v4, vermelho);

	//direita
	react(v4, v3, v6, v5, azul);

	//back
	react(v5, v8, v7, v6, amarelo);

	//esquerda
	react(v1, v8, v7, v2, verde);

	//topo
	react(v1, v4, v5, v8, laranja);

	//bottonm
	react(v2, v7, v6, v3, violeta);

}
void desenhaEsfera(unsigned int& id,color cor,GLfloat raio, GLuint nStacks, GLuint  nSectors) 
{
	std::vector< std::vector<GLuint> >indices;

	std::vector<vec3> pontos;
	const GLfloat PI = 3.14159265359;

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = 2 * PI / nSectors;

	for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -PI / 2.0 + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);

		std::vector<GLuint> pt;

		for (GLuint j = 0; j < nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
			GLuint index = pontos.size() - 1;
			pt.push_back(index);
		}

		indices.push_back(pt);

	}
  

	glNewList(id , GL_COMPILE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	for (GLuint i = 0; i < nStacks; i++)
	{
		// cores na esfera
		if (i % 3 == 0)
			glColor3fv(cor);
		else if (i % 3 == 1)
			glColor3fv(branco_gelo);
		else
			glColor3fv(cinza);

		glBegin(GL_TRIANGLE_STRIP);
		for (GLuint j = 0; j < nSectors; j++)
		{
			GLuint index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);

			if (j == nSectors - 1) 
			{
				index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				index = indices[i + 1][0];
				glVertex3fv(&pontos[index].x);
			}
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glEndList();
	
}
void desenhaTerreno(unsigned int id) 
{
	float L = 500.0;
	float incr = 1.0;
	float y = -0.5;

	glNewList(id, GL_COMPILE);

	glColor3fv(branco_gelo);
	glBegin(GL_LINES);

	for (float i = -L; i <= L; i += incr)
	{
		//verticais
		glVertex3f(i, y, -L);
		glVertex3f(i, y, L);

		//HORIZONTAIS
		glVertex3f(-L, y, i);
		glVertex3f(L, y, i);
	}
	glEnd();
	glEndList();
}