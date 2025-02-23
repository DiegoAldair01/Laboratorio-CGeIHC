//Ejercicio 2: índices, mesh, proyecciones, transformaciones geométricas
// Realizado por Diego Aldair Garcia Hernandez

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

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067


void CrearLetrasyFiguras()
{
	// Techo
	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	// Casa (cuadrado grande)
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

	// Puerta y ventanas
	GLfloat vertices_puerta[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* puerta = new MeshColor();
	puerta->CreateMeshColor(vertices_puerta, 36);
	meshColorList.push_back(puerta);

	// Troncos
	GLfloat vertices_tronco[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.0f,

	};
	MeshColor* tronco = new MeshColor();
	tronco->CreateMeshColor(vertices_tronco, 36);
	meshColorList.push_back(tronco);

	// Pino
	GLfloat vertices_pino[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* pino = new MeshColor();
	pino->CreateMeshColor(vertices_pino, 18);
	meshColorList.push_back(pino);


}


void CreateShaders()
{
	Shader *shader = new Shader();//shader para usar color como parte del VAO: letras 
	shader->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
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
		
													
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

		// Dibujar pino1 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.24f, 0.45f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(-3.0f, -0.6f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		// Dibujar pino2 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.24f, 0.45f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(3.0f, -0.6f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		// Dibujar tronco1 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(-4.75f, -3.26f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();

		// Dibujar tronco2 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(4.75f, -3.26f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();

		// Dibujar puerta 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.25f, 0.45f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(0.0f, -1.58f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		// Dibujar ventana1
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.35f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(-0.7f, 0.1f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		// Dibujar ventana2
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.35f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(0.7f, 0.1f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		// Dibujar techo (triángulo azul)
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.5f, 0.35f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		
		// Dibujar casa (cuadrado rojo)
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.8f, 1.25f, 1.0f)); // Escalamiento
		model = glm::translate(model, glm::vec3(0.0f, -0.25f, -1.0f)); // Traslacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();




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