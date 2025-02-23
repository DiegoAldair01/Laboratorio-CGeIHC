//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
// Realizado por Diego Aldair García Hernández
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
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vRojoShader = "shaders/shaderrojo.vert";
static const char* vVerdeShader = "shaders/shaderverde.vert";
static const char* vAzulShader = "shaders/shaderazul.vert";
static const char* vVerdeFShader = "shaders/shaderverdefuerte.vert";
static const char* vCafeShader = "shaders/shadercafe.vert";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

void CrearLetrasyFiguras()
{

	//////////////// LETRA D //////////////////
	// figura 1_D
	GLfloat vertices_figuraUnoD[] = {
		//X			Y			Z			R		G		B
		-0.8f,	0.9f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.9f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.8f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.9f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.8f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,

	};
	MeshColor* figuraUnoD = new MeshColor();
	figuraUnoD->CreateMeshColor(vertices_figuraUnoD, 36);
	meshColorList.push_back(figuraUnoD);

	// figura 2_D
	GLfloat vertices_figuraDosD[] = {
		//X			Y			Z			R		G		B
		-0.6f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.1f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.3f,	0.1f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.1f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.4f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.3f,	0.3f,		0.5f,			0.0f,	0.0f,	1.0f,
		-0.3f,	0.4f,		0.5f,			0.0f,	0.0f,	1.0f,

	};
	MeshColor* figuraDosD = new MeshColor();
	figuraDosD->CreateMeshColor(vertices_figuraDosD, 54);
	meshColorList.push_back(figuraDosD);

	//////////////// LETRA A //////////////////
	GLfloat vertices_figuraUnoA[] = {
		//X			Y			Z			R		G		B
		0.1f,	0.1f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.4f,	0.9f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.6f,	0.9f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.1f,	0.1f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.3f,	0.1f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.6f,	0.9f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* figuraUnoA = new MeshColor();
	figuraUnoA->CreateMeshColor(vertices_figuraUnoA, 36);
	meshColorList.push_back(figuraUnoA);

	GLfloat vertices_figuraDosA[] = {
		//X			Y			Z			R		G		B
		0.35f,	0.25f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.4f,	0.4f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.6f,	0.4f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.65f,	0.25f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.6f,	0.4f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.35f,	0.25f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* figuraDosA = new MeshColor();
	figuraDosA->CreateMeshColor(vertices_figuraDosA, 36);
	meshColorList.push_back(figuraDosA);

	//////////////// LETRA G //////////////////
	GLfloat vertices_figuraUnoG[] = {
		//X			Y			Z			R		G		B
		-0.2f,	-0.7f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.2f,	-0.8f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.3f,	-0.9f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.2f,	-0.7f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.3f,	-0.9f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.8f,	-0.7f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.8f,	-0.7f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.3f,	-0.9f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.7f,	-0.9f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.8f,	-0.7f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.8f,	-0.8f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.7f,	-0.9f,		0.5f,			0.0f,	1.0f,	1.0f,

	};
	MeshColor* figuraUnoG = new MeshColor();
	figuraUnoG->CreateMeshColor(vertices_figuraUnoG, 72);
	meshColorList.push_back(figuraUnoG);

	GLfloat vertices_figuraDosG[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.5f,	-0.6f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.4f,	-0.5f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.4f,	-0.5f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.5f,	-0.6f,		0.5f,			0.0f,	1.0f,	1.0f,
		-0.4f,	-0.6f,		0.5f,			0.0f,	1.0f,	1.0f,
	};
	MeshColor* figuraDosG = new MeshColor();
	figuraDosG->CreateMeshColor(vertices_figuraDosG, 36);
	meshColorList.push_back(figuraDosG);


	//////////////// LETRA H //////////////////
	GLfloat vertices_figuraUnoH[] = {
		//X			Y			Z			R		G		B
		0.2f,	-0.1f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.1f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.9f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.1f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.9f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.9f,		0.5f,			0.0f,	1.0f,	0.0f,
	};
	MeshColor* figuraUnoH = new MeshColor();
	figuraUnoH->CreateMeshColor(vertices_figuraUnoH, 36);
	meshColorList.push_back(figuraUnoH);


}


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




void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader = new Shader();//shader para usar color como parte del VAO: letras 
	shader->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader);

	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vRojoShader, fShader);
	shaderList.push_back(*shaderRojo);

	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vVerdeShader, fShader);
	shaderList.push_back(*shaderVerde);

	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vAzulShader, fShader);
	shaderList.push_back(*shaderAzul);

	Shader* shaderVerdeF = new Shader();
	shaderVerdeF->CreateFromFiles(vVerdeFShader, fShader);
	shaderList.push_back(*shaderVerdeF);

	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vCafeShader, fShader);
	shaderList.push_back(*shaderCafe);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearLetrasyFiguras();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//////////////// DIBUJO EJERCICIO 2 ////////////////// 
		
		////Tronco 1
		shaderList[6].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(3.75f, -1.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		////Tronco 2
		shaderList[6].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(-3.75f, -1.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		////Pino 1
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-1.5f, 0.125f, 0.0f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		////Ventana 1 
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 1.0f));
		model = glm::translate(model, glm::vec3(0.8f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//
		////Ventana 2
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.8f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		////Puerta
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();



		////Techo
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 0.6f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 1.12f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Casa (Cubo rojo)
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.25f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		////Pino 2
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(1.5f, 0.125f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		////////////////// DIBUJO EJERCICIO 1 //////////////////
		// 
		////Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		//shaderList[1].useShader();
		//uniformModel = shaderList[0].getModelLocation();
		//uniformProjection = shaderList[0].getProjectLocation();

		////////////////// LETRA D //////////////////
		//// Figura1 D
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		//// Figura1_1 D
		//model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		//model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		//// Figura2 D
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();

		//// Figura2_1 D
		//model = glm::mat4(1.0);
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();

		////////////////// LETRA A //////////////////
		//// Figura1 A
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		//// Figura1_1 A
		//model = glm::mat4(1.0);
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		//// Figura2 A
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[3]->RenderMeshColor();

		////////////////// LETRA G //////////////////
		//// Figura1 G
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		//// Figura1_1 G
		//model = glm::mat4(1.0);
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		//// Figura2 G
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		//// Figura2_1 G
		//model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.3f, 0.25f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		//// Figura2_2 G
		//model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(0.3f, 0.2f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		//// Figura2_3 G
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.2f, 1.7f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 4.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();


		////////////////// LETRA H //////////////////
		//// Figura1 H
		//model = glm::mat4(1.0);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		//// Figura1_1 H
		//model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(1.0f, 0.25f, 1.0f));
		//model = glm::translate(model, glm::vec3(0.2f, -1.5f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		//// Figura1_2 H
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

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