#include<vector>
#define PI 3.14159265358979323846
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;

void desenhaCubo(float s)
{
	float d = s / 2.0;

	// frente
	glBegin(GL_QUADS);
	glColor3f(0.85, 0.12, 0.0);
	glVertex3f(-d, d, d);
	glVertex3f(-d, -d, d);
	glVertex3f(d, -d, d);
	glVertex3f(d, d, d);
	glEnd();

	// direita
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.15, 0.35);
	glVertex3f(d, d, d);
	glVertex3f(d, -d, d);
	glVertex3f(d, -d, -d);
	glVertex3f(d, d, -d);
	glEnd();

	// trás
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(d, d, -d);
	glVertex3f(d, -d, -d);
	glVertex3f(-d, -d, -d);
	glVertex3f(-d, d, -d);
	glEnd();

	// esquerda
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-d, d, -d);
	glVertex3f(-d, -d, -d);
	glVertex3f(-d, -d, d);
	glVertex3f(-d, d, d);
	glEnd();

	// cima
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.6, 0.2);
	glVertex3f(-d, d, -d);
	glVertex3f(-d, d, d);
	glVertex3f(d, d, d);
	glVertex3f(d, d, -d);
	glEnd();

	// baixo
	glBegin(GL_QUADS);
	glColor3f(0.54, 0.17, 0.88);
	glVertex3f(-d, -d, d);
	glVertex3f(-d, -d, -d);
	glVertex3f(d, -d, -d);
	glVertex3f(d, -d, d);
	glEnd();
}

void desenhaTerreno(float intensidadeTerreno)
{
	float intensidadeLinha = intensidadeTerreno;
	float L = 500.0;
	float incr = 1.0;
	float y = -0.5;

	// Define a cor do terreno
	float cor[3] = { 1.0, 1.0, 0.0 };

	// Ajusta a intensidade da cor
	for (int i = 0; i < 3; i++) {
		cor[i] *= intensidadeTerreno;
	}

	// Define a textura do terreno
	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);

	// Carrega a imagem da textura
	int largura, altura, nrCanais;
	unsigned char* dados = stbi_load("terreno.jpg", &largura, &altura, &nrCanais, 0);
	if (dados)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);

		// Define a filtragem da textura
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(dados);
	}
	else
	{
		std::cout << "Erro ao carregar a imagem da textura" << std::endl;
		stbi_image_free(dados);
		return;
	}

	// Ativa a textura
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);

	// Desenha o terreno com a textura
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-L, y, -L);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(L, y, -L);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(L, y, L);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-L, y, L);
	glEnd();

	// Desativa a textura
	glDisable(GL_TEXTURE_2D);

	// Define a cor das linhas
	float corLinha[3] = { 1.0, 0.0, 0.0 };
	if (intensidadeLinha < 0.1) {
		intensidadeLinha = 0.1;
	}
	else {
		intensidadeLinha = intensidadeLinha;
	}
	// Ajusta a intensidade da cor das linhas
	for (int i = 0; i < 3; i++) {
		corLinha[i] *= intensidadeLinha;
	}


	glColor3fv(cor);
	glLineWidth(10.0f); // Altere o valor para o tamanho desejado
	glBegin(GL_LINES);

	for (float i = -L; i <= L; i += incr)
	{
		//verticais
		glVertex3f(i, y, -L);
		glVertex3f(i, y, L);
	}

	glEnd();

	glLineWidth(1.0f); // Volte para o tamanho padrão
	glBegin(GL_LINES);

	for (float i = -L; i <= L; i += incr)
	{
		//HORIZONTAIS
		glVertex3f(-L, y, i);
		glVertex3f(L, y, i);
	}
	glEnd();


}

void desenhaSol(float intensidadeSol, float moverx)
{
	// Define o raio do sol
	float raio = 20.0;

	// Define a posição do sol na tela
	float x = 0.0;
	float y = 0.0;

	// Define a cor 
	float cor_sol[3] = { 1.0, 1.0, 0.0 }; //
	float cor_laranja[3] = { 1.0, 0.6, 0.2 };
	if (moverx <= -10) {
		// Ajusta a intensidade da cor
		for (int i = 0; i < 3; i++) {
			cor_sol[i] *= intensidadeSol;
		}
	}
	// cor do sol
	glColor3fv(cor_sol);

	// Define o número de raios do sol
	int numRaios = 50;

	// Define o ângulo entre cada raio do sol
	float anguloRaios = 2.0 * PI / numRaios;

	// Define a largura dos raios do sol
	float larguraRaios = 5.0;

	// Desenha o círculo do sol
	glPushMatrix();
	glTranslatef(0.0, moverx, -150); // Move o sol
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= numRaios; i++) {
		float angulo = i * anguloRaios;
		float dx = raio * cos(angulo);
		float dy = raio * sin(angulo);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();

	// Desenha os raios do sol
	glColor3fv(cor_laranja);
	glBegin(GL_LINES);
	for (int i = 0; i < numRaios; i++) {
		float angulo = i * anguloRaios;
		float dx1 = raio * cos(angulo);
		float dy1 = raio * sin(angulo);
		float dx2 = (raio + larguraRaios) * cos(angulo);
		float dy2 = (raio + larguraRaios) * sin(angulo);
		glVertex2f(x + dx1, y + dy1);
		glVertex2f(x + dx2, y + dy2);
	}
	glEnd();
	glPopMatrix();
}

void desenhaCasa(float x, float y, float z) // adicionando parâmetros x, y e z para especificar a posição
{
	float cor_vermelha[3] = { 0.85, 0.12, 0.0 };
	float cor_branco[3] =  { 1.0, 1.0, 1.0 };
	float s = 5.0;
	float h = s / 4.0;
	float l = s * 1.2;
	float d = s * 1.2;
	float telhadoPI = 3 * h;

	// desenha o corpo da casa
	glPushMatrix();
	glTranslatef(x, y + s / 2.0, z); // move o cubo para a posição especificada
	desenhaCubo(s);
	glPopMatrix();

	// desenha o telhado
	glPushMatrix();
	glTranslatef(x, y + s + h / 2.0, z); // move o telhado para a posição especificada
	glColor3fv(cor_vermelha);
	glBegin(GL_TRIANGLES);
	glVertex3f(-l / 2.0, 0.0, -d / 2.0);
	glVertex3f(l / 2.0, 0.0, -d / 2.0);
	glVertex3f(0.0, telhadoPI, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(l / 2.0, 0.0, -d / 2.0);
	glVertex3f(l / 2.0, 0.0, d / 2.0);
	glVertex3f(0.0, telhadoPI, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(l / 2.0, 0.0, d / 2.0);
	glVertex3f(-l / 2.0, 0.0, d / 2.0);
	glVertex3f(0.0, telhadoPI, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-l / 2.0, 0.0, d / 2.0);
	glVertex3f(-l / 2.0, 0.0, -d / 2.0);
	glVertex3f(0.0, telhadoPI, 0.0);
	glEnd();
	glPopMatrix();

	// desenha a porta
	glPushMatrix();
	glTranslatef(x, y, z + 3.1); // move a porta para a posição especificada
	glColor3fv(cor_branco);
	glBegin(GL_QUADS);
	glVertex3f(-s / 4.0, 0.0, 0.0);
	glVertex3f(s / 4.0, 0.0, 0.0);
	glVertex3f(s / 6.0, s / 2.0, 0.0);
	glVertex3f(-s / 6.0, s / 2.0, 0.0);
	glEnd();
	glPopMatrix();

}
void desenhaPoste(int numPoste, float angulo)
{
	// Defina aqui a posição e tamanhos
	std::vector<vec3> posicoes = { {-50.0, -20.0, -200.0}, {50.0, -20.0, -100.0}, {-30.0, -20.0, -400.0}, {80.0, -20.0, -400.0}};
	std::vector<float> tamanhos = { 40.0, 40.0, 40.0, 40.0 };
	float cor_verde[3] = { 0.0, 1.0, 0.0 };


	for (int i = 0; i < numPoste; i++)
	{
		glPushMatrix();
		glTranslatef(posicoes[i].x, posicoes[i].y, posicoes[i].z);

		// POSTE
		glPushMatrix();
		glScalef(1.0, tamanhos[i]* 2, 1.0);
		desenhaCubo(1.0);
		glPopMatrix();

		// LUZ
		glPushMatrix();
		glTranslatef(0.0, tamanhos[i],0.0);
		glRotatef(angulo, 0.0f, 1.0f, 0.0f); // rotação em torno do eixo y
		glScalef(10.0, 10.0, 10.0);
		glColor3fv(cor_verde);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 2.0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -2.0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(2.0, 0.0, 0.0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(-2.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
}
void imagens(const char* nomeArquivo) {

		int larguraImgInicio, alturaImgInicio, nrCanaisImgInicio;
		unsigned char* dataImgInicio = stbi_load(nomeArquivo, &larguraImgInicio, &alturaImgInicio, &nrCanaisImgInicio, 0);

		stbi_set_flip_vertically_on_load(true); // inverte a imagem verticalmente
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glViewport(0, 0, larguraImgInicio, alturaImgInicio);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		gluOrtho2D(0, larguraImgInicio, 0, alturaImgInicio);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(0, 0);
		glDrawPixels(larguraImgInicio, alturaImgInicio, GL_RGB, GL_UNSIGNED_BYTE, dataImgInicio);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		stbi_image_free(dataImgInicio); // libera a memória alocada pela imagem
	
}
void desenhaCeu(float intensidadeCeu) {
	float cor_ceu[4] = { 0.529, 0.808, 0.922, 1.0 };
	float tamanhoEstrelas = 2.0;
	for (int i = 0; i < 4; i++) {
		cor_ceu[i] *= intensidadeCeu;
	}
	glClearColor(cor_ceu[0], cor_ceu[1], cor_ceu[2], cor_ceu[3]); // Azul claro	// Define a cor do céu
	// Limpa o buffer de cor e profundidade
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Desenha as estrelas
	if (intensidadeCeu < 0.2) {
		glPointSize(tamanhoEstrelas);
		glBegin(GL_POINTS);
		// Estrelas em pontos específicos
		glVertex3f(10.0, 20.0, -100.0); // Estrela 1
		glVertex3f(-10.0, 20.0, -100.0); // Estrela 2
		glVertex3f(25.0, 20.0, -100.0); // Estrela 3
		glVertex3f(-20.0, 20.0, -100.0); // Estrela 4
		glVertex3f(15.0, 20.0, -100.0); // Estrela 5
		glVertex3f(-5.0, 20.0, -100.0); // Estrela 6
		glVertex3f(0.0, 10.0, -100.0); // Estrela 7
		glVertex3f(-50.0, 40.0, -100.0); // Estrela 8
		glVertex3f(50.0, 40.0, -100.0); // Estrela 9
		glVertex3f(-50.0, 35.0, -100.0); // Estrela 10
		glVertex3f(-50.0, 20.0, -100.0); // Estrela 11
		glVertex3f(50.0, 20.0, -100.0); // Estrela 12
		glVertex3f(-50.0, 10.0, -100.0); // Estrela 13
		glEnd();
	}
}