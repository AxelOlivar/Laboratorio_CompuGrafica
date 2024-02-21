//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
//AXEL DANIEL BECERRIL OLIVAR, PRÁCTICA 2

#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
#include<glm.hpp> //libreria matematica
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include"Mesh.h" //clases para dar orden y limpieza al código
#include"Shader.h"
#include"Window.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderCuboCafe = "shaders/shader_CuboCafe.vert";
static const char* vShaderCuboRojo = "shaders/shader_CuboRojo.vert";
static const char* vShaderCuboVerde = "shaders/shader_CuboVerde.vert";
static const char* vShaderPiramideAzul = "shaders/shader_PiramideAzul.vert";
static const char* vShaderPiramideVerde = "shaders/shader_PiramideVerde.vert";


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
	Mesh* obj1 = new Mesh();
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
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}


void CrearLetrasyFiguras()
{
	GLfloat vertices_letraA[] = {
		//X	    Y	 Z			R	  G	   B
		-0.9, -0.5,	0.0,		0.0, 0.5, 1.0,			
		-0.75,	-0.5, 0.0,		0.0, 0.5, 1.0,
		-0.9, 0.5, 0.0,			0.0, 0.5, 1.0,

		-0.75, 0.5, 0.0,		0.0, 0.5, 1.0,
		-0.9, 0.5, 0.0,			0.0, 0.5, 1.0,
		-0.75, -0.5, 0.0,		0.0, 0.5, 1.0,

		-0.75, -0.15, 0.0,		0.0, 0.5, 1.0,
		-0.6, -0.15, 0.0,		0.0, 0.5, 1.0,
		-0.75, 0.1, 0.0,		0.0, 0.5, 1.0,

		-0.75, 0.1, 0.0,		0.0, 0.5, 1.0,
		-0.6, 0.1, 0.0,			0.0, 0.5, 1.0,
		-0.6, -0.15, 0.0,		0.0, 0.5, 1.0,

		-0.75, 0.35,0.0,		0.0, 0.5, 1.0,
		-0.75, 0.5, 0.0,		0.0, 0.5, 1.0,
		-0.6, 0.35,0.0,			0.0, 0.5, 1.0,

		-0.75, 0.5, 0.0,		0.0, 0.5, 1.0,
		-0.6, 0.35,0.0,			0.0, 0.5, 1.0,
		-0.6, 0.5, 0.0,			0.0, 0.5, 1.0,

		-0.6, 0.5, 0.0,			0.0, 0.5, 1.0,
		-0.45, 0.5, 0.0,		0.0, 0.5, 1.0,
		-0.45, -0.5, 0.0,		0.0, 0.5, 1.0,

		-0.6, 0.5, 0.0,			0.0, 0.5, 1.0,
		-0.45, -0.5, 0.0,		0.0, 0.5, 1.0,
		-0.6, -0.5,0.0,			0.0, 0.5, 1.0,


	};

	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 144);
	meshColorList.push_back(letraA);

	GLfloat vertices_letraD[] = {
		//X		      Y		Z		  R	  G	  B
		-0.24862, 0.49702, 0.0,		1.0, 0.0,0.5,
		-0.24862, -0.50298, 0.0,	1.0, 0.0,0.5,
		-0.09862, 0.19702, 0.0,		1.0, 0.0,0.5,

		-0.24862, -0.50298, 0.0,	1.0, 0.0,0.5,
		-0.09862, 0.19702, 0.0,		1.0, 0.0,0.5,
		-0.09862, -0.20298, 0.0,	1.0, 0.0,0.5,

		-0.24862, -0.50298, 0.0,	1.0, 0.0,0.5,
		-0.09862, -0.20298, 0.0,	1.0, 0.0,0.5,
		0.25138, -0.30298, 0.0,		1.0, 0.0,0.5,

		-0.24862, -0.50298, 0.0,	1.0, 0.0,0.5,
		0.25138, -0.30298, 0.0,		1.0, 0.0,0.5,
		0.05138, -0.50298, 0.0,		1.0, 0.0,0.5,

		-0.09862, -0.20298, 0.0,	1.0, 0.0,0.5,
		0.25138, -0.30298, 0.0,		1.0, 0.0,0.5,
		0.05138, -0.20298, 0.0,		1.0, 0.0,0.5,
			
		0.25138, -0.30298, 0.0,		1.0, 0.0,0.5,
		0.05138, -0.20298, 0.0,		1.0, 0.0,0.5,
		0.10138, -0.15298, 0.0,		1.0, 0.0,0.5,

		0.25138, -0.30298, 0.0,		1.0, 0.0,0.5,
		0.10138, -0.15298, 0.0,		1.0, 0.0,0.5,
		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,

		0.10138, -0.15298, 0.0,		1.0, 0.0,0.5,
		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,
		0.10138, 0.14702, 0.0,		1.0, 0.0,0.5,

		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,
		0.10138, 0.14702, 0.0,		1.0, 0.0,0.5,
		0.05138, 0.19702, 0.0,		1.0, 0.0,0.5,

		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,
		-0.09862, 0.19702, 0.0,		1.0, 0.0,0.5,
		0.05138, 0.19702, 0.0,		1.0, 0.0,0.5,

		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,
		-0.09862, 0.19702, 0.0,		1.0, 0.0,0.5,
		-0.24862, 0.49702, 0.0,		1.0, 0.0,0.5,

		-0.09862, 0.19702, 0.0,		1.0, 0.0,0.5,
		0.05138, 0.19702, 0.0,		1.0, 0.0,0.5,
		0.05138, 0.49702, 0.0,		1.0, 0.0,0.5,

		-0.24862, 0.49702, 0.0,		1.0, 0.0,0.5,
		0.25138, 0.29702, 0.0,		1.0, 0.0,0.5,
		0.05138, 0.49702, 0.0,		1.0, 0.0,0.5,	
	};
	MeshColor* letraD = new MeshColor();
	letraD->CreateMeshColor(vertices_letraD, 234);
	meshColorList.push_back(letraD);

	GLfloat vertices_letraO[] = {
		//X	   Y	Z			 R	  G	  B
		0.4, -0.5, 0.0,			0.0, 1.0,0.5,
		0.55, -0.35, 0.0,		0.0, 1.0,0.5,
		0.4, 0.5, 0.0, 			0.0, 1.0,0.5,

		0.55, -0.35, 0.0, 		0.0, 1.0,0.5,
		0.4, 0.5, 0.0, 			0.0, 1.0,0.5,
		0.55, 0.35, 0.0, 		0.0, 1.0,0.5,

		0.4, 0.5, 0.0, 			0.0, 1.0,0.5,
		0.55, 0.35, 0.0,		0.0, 1.0,0.5,
		0.95, 0.5, 0.0, 		0.0, 1.0,0.5,

		0.55, 0.35, 0.0, 		0.0, 1.0,0.5,
		0.95, 0.5, 0.0,			0.0, 1.0,0.5,
		0.8, 0.35, 0.0,			0.0, 1.0,0.5,

		0.95, 0.5, 0.0,			0.0, 1.0,0.5,
		0.8, 0.35, 0.0,			0.0, 1.0,0.5,
		0.95, -0.5, 0.0,		0.0, 1.0,0.5,

		0.8, 0.35, 0.0,			0.0, 1.0,0.5,
		0.95, -0.5, 0.0,		0.0, 1.0,0.5,
		0.8, -0.35, 0.0,		0.0, 1.0,0.5,

		0.95, -0.5, 0.0, 		0.0, 1.0,0.5,
		0.8, -0.35, 0.0,		0.0, 1.0,0.5,
		0.4, -0.5, 0.0,			0.0, 1.0,0.5,

		0.8, -0.35, 0.0,		0.0, 1.0,0.5,
		0.4, -0.5, 0.0,			0.0, 1.0,0.5,
		0.55, -0.35, 0.0,		0.0, 1.0,0.5,
	};

	MeshColor* letraO = new MeshColor();
	letraO->CreateMeshColor(vertices_letraO, 144);
	meshColorList.push_back(letraO);
}

//FUNCIÓN PARA AGREGAR LOS SHADERS CREADOS 
void CreateShaders()
{
	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide 
	shader3->CreateFromFiles(vShaderCuboCafe, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader4->CreateFromFiles(vShaderCuboRojo, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader5->CreateFromFiles(vShaderCuboVerde, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader6->CreateFromFiles(vShaderPiramideAzul, fShader);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader7->CreateFromFiles(vShaderPiramideVerde, fShader);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(1100, 900);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList

	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList, indice 2
	
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); //2d
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f); //3d
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	//Se almacenan las multiplicaciones
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//									ACTIVIDAD 2

		// CUBO VERDE ABAJO
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0, -0.678f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(0.35, 0.35f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		// CUBO VERDE IZQ
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2, 0.1f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(0.35, 0.35f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		// CUBO VERDE DER
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2, 0.1f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(0.35, 0.35f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		//CUBO ROJO
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(1.0, 1.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		//PIRAMIDE AZUL	
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.1;
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.0f)); //VA A TRASLADAR -2 EN Z
		model = glm::scale(model, glm::vec3(1.2, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //PARA DIBUJAR LA FIGURA

		//PIRAMIDE VERDE IZQ	
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.1;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.34f, -2.0f)); //VA A TRASLADAR -2 EN Z
		model = glm::scale(model, glm::vec3(0.3, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //PARA DIBUJAR LA FIGURA

		//PIRAMIDE VERDE DER	
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.1;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.34f, -2.0f)); //VA A TRASLADAR -2 EN Z
		model = glm::scale(model, glm::vec3(0.3, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //PARA DIBUJAR LA FIGURA

		// CUBO CAFE IZQ
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.74f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(0.2, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		// CUBO CAFE DER
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.2;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.74f, -2.0f)); //profundidad trasladar 
		model = glm::scale(model, glm::vec3(0.2, 0.2f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //EL INDICE ES DE LA FIGURA QUE QUIERO DIBUJAR

		

		////									 ACTIVIDAD 1

		////LETRA A
		////Iniczializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//model = glm::mat4(1.0); 
		//model = glm::translate(model, glm::vec3(-0.1f, 0.0f, -2.0f)); //VA A TRASLADAR -4 EN Z
		//model = glm::scale(model, glm::vec3(0.8, 0.8f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor(); //PARA DIBUJAR LA FIGURA
		//
		////TLETRA D
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f)); //VA A TRASLADAR -4 EN Z
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//meshColorList[1]->RenderMeshColor(); //PARA DIBUJAR LA FIGURA

		////LETRA O
		////Iniczializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.1f, 0.0f, -2.0f)); //VA A TRASLADAR -4 EN Z
		//model = glm::scale(model, glm::vec3(0.8, 0.8f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor(); //PARA DIBUJAR LA FIGURA
		

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
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); //
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //USAR ANGULO
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/