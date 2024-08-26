//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShaderBlue = "shaders/shaderBlue.vert";
static const char* fShaderBlue = "shaders/shaderBlue.frag";

static const char* vShaderGreenSoft = "shaders/shaderGreenSoft.vert";
static const char* fShaderGreenSoft = "shaders/shaderGreenSoft.frag";

static const char* vShaderGreenStrong = "shaders/shaderGreenStrong.vert";
static const char* fShaderGreenStrong = "shaders/shaderGreenStrong.frag";

static const char* vShaderBrown = "shaders/shaderBrown.vert";
static const char* fShaderBrown = "shaders/shaderBrown.frag";

static const char* vShaderRed = "shaders/shaderRed.vert";
static const char* fShaderRed = "shaders/shaderRed.frag";

static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}


//Vértices de un cubo
void CrearVentana1()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.1f, 0.1f,  0.1f,
		-0.05f, 0.1f,  0.1f,
		-0.05f,  0.15f,  0.1f,
		-0.1f,  0.15f,  0.1f,
		// back
		-0.1f, 0.1f, -0.1f,
		-0.05f, 0.1f, -0.1f,
		-0.05f,  0.15f, -0.1f,
		-0.1f,  0.15f, -0.1f
	};
	Mesh* ventana1 = new Mesh();
	ventana1->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(ventana1);
}

//Vértices de un cubo
void CrearPuerta()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.05f, -0.1f,  0.1f,
		0.05f, -0.1f,  0.1f,
		-0.05f,  -0.2f,  0.1f,
		0.05f,  -0.2f,  0.1f,
		// back
		-0.05f, -0.1f, -0.1f,
		0.05f, -0.1f, -0.1f,
		-0.05f,  -0.2f, -0.1f,
		0.05f,  -0.2f, -0.1f
	};
	Mesh* puerta = new Mesh();
	puerta->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(puerta);
}

//Vértices de un cubo
void CrearArbolTronco()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.1f,  0.1f,
		-0.4f, -0.1f,  0.1f,
		-0.5f,  -0.2f,  0.1f,
		-0.4f,  -0.2f,  0.1f,
		// back
		-0.5f, -0.1f, -0.1f,
		-0.4f, -0.1f, -0.1f,
		-0.5f,  -0.2f, -0.1f,
		-0.4f,  -0.2f, -0.1f
	};
	Mesh* tronco = new Mesh();
	tronco->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(tronco);
}

void CrearArbolHojas()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.55f, -0.1f,0.0f,	//0
		-0.35f, -0.1f,0.0f,	//1
		-0.45f,0.1f, 0.0f,	//2
		-0.45f,0.0f,-0.5f,	//3

	};
	Mesh* hojas = new Mesh();
	hojas->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(hojas);

}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letraV[] = {	
			//X    Y	Z		R		G		B
			//----------- V (\)
			-0.7f, 0.6f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.6f, 0.7f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.5f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,

			-0.6f, 0.7f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.4f, 0.5f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.5f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,
			//triangulo V
			-0.5f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.4f, 0.5f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.3f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,

			//V (/)
			-0.4f, 0.5f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.2f, 0.7f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.3f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,

			-0.3f, 0.4f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.1f, 0.6f,0.0f, 0.0f,	0.0f,	1.0f,
			-0.2f, 0.7f,0.0f, 0.0f,	0.0f,	1.0f,

			
	};
	MeshColor* letraV = new MeshColor();
	letraV->CreateMeshColor(vertices_letraV, 90);
	meshColorList.push_back(letraV);
	
	GLfloat vertices_letraA[] = {

		//---------------- A (/)
		0.0f, 0.5f,0.0f, 1.0f,	0.0f,	0.0f,
		0.1f, 0.4f,0.0f, 1.0f,	0.0f,	0.0f,
		0.3f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,

		0.1f, 0.4f,0.0f, 1.0f,	0.0f,	0.0f,
		0.4f, 0.7f,0.0f, 1.0f,	0.0f,	0.0f,
		0.3f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,
		// Triangulo A
		0.3f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,
		0.4f, 0.7f,0.0f, 1.0f,	0.0f,	0.0f,
		0.5f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,
		//A (\)
		0.4f, 0.7f,0.0f, 1.0f,	0.0f,	0.0f,
		0.5f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,
		0.7f, 0.4f,0.0f, 1.0f,	0.0f,	0.0f,

		0.7f, 0.4f,0.0f, 1.0f,	0.0f,	0.0f,
		0.8f, 0.5f,0.0f, 1.0f,	0.0f,	0.0f,
		0.5f, 0.8f,0.0f, 1.0f,	0.0f,	0.0f,
		//A (-)
		0.15f, 0.6f,0.0f, 1.0f,	0.0f,	0.0f,
		0.15f, 0.55f,0.0f, 1.0f,	0.0f,	0.0f,
		0.65f, 0.55f,0.0f, 1.0f,	0.0f,	0.0f,

		0.65f, 0.55f,0.0f, 1.0f,	0.0f,	0.0f,
		0.15f, 0.6f,0.0f, 1.0f,	0.0f,	0.0f,
		0.65f, 0.6f,0.0f, 1.0f,	0.0f,	0.0f,
	};
	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 126);
	meshColorList.push_back(letraA);

	GLfloat vertices_letraM[] = {
		//---------------- M (| izq)
			-0.6f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.5f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.6f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,

			-0.6f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.5f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.5f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,

			// M (| der)
			-0.2f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.2f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.1f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,

			-0.1f, -0.5f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.1f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.2f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,

			//Triangulo M
			-0.4f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.3f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.35f, -0.35f,0.0f, 0.0f,	1.0f,	0.0f,

			// M (\)
			-0.55f, -0.25f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.5f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.4f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,

			-0.4f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.35f, -0.35f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.5f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,

			// M(/)

			-0.35f, -0.35f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.2f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.3f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,

			-0.3f, -0.4f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.15f, -0.25f,0.0f, 0.0f,	1.0f,	0.0f,
			-0.2f, -0.2f,0.0f, 0.0f,	1.0f,	0.0f,
	};
	MeshColor* letraM = new MeshColor();
	letraM->CreateMeshColor(vertices_letraM, 162);
	meshColorList.push_back(letraM);


	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


}


void CreateShaders()
{

	Shader *shader10 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader10->CreateFromFiles(vShaderBlue, fShaderBlue);
	shaderList.push_back(*shader10);

	Shader* shader11 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader11->CreateFromFiles(vShaderGreenSoft, fShaderGreenSoft);
	shaderList.push_back(*shader11);

	Shader* shader12 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader12->CreateFromFiles(vShaderGreenStrong, fShaderGreenStrong);
	shaderList.push_back(*shader12);

	Shader* shader13 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader13->CreateFromFiles(vShaderBrown, fShaderBrown);
	shaderList.push_back(*shader13);

	Shader* shader14 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader14->CreateFromFiles(vShaderRed, fShaderRed);
	shaderList.push_back(*shader14);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 700);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	
	//CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//EHERCICIO 1 DE REPORTE 
		//Primer letra con color indice 2 en la lista de colores
		/*
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();//Primera figura


		//Primer letra con color indice 3 en la lista de colores
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();//Segunda gifura

		//Primer letra con color indice 4 en la lista de colores
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));

		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();//Tercer figura
		*/
		//EJERCICIO 2 DE REPORTE 
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.55f, -3.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//Cuadrado rojo 
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Ventana izq
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, 0.1f, -2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//ventana der
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.1f, 0.1f, -2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puerta
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		//tronco izq
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.4f, -0.15f, -2.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//hojas izq
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.4f, -0.04f, -2.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//tronco der
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.4f, -0.15f, -2.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//hojas der
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.5;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.4f, -0.04f, -2.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.2f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//EJERCICIO DE CLASE
		/*
		//------------TRIANGULO----------------

		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//------------CUADRADO----------------

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//------------VENTANA IZQUIERSA----------------

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//------------VENTANA DERECHA----------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.15f, 0.0f, -1.0f)); //Como es la misma ventana solo se traslada en X
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//------------PUERTA----------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)); //Como es la misma ventana solo se traslada en X
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		//------------Arbol IZQUIERDO----------------

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();
		//Hojas
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[5]->RenderMesh();


		//------------Arbol DERECHO----------------

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.9f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		//Hojas
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.9f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[5]->RenderMesh();
		*/

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/