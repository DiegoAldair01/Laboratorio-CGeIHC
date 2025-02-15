//Archivo inicial semestre 2025-2
// Archivo editado por Diego Aldair Garcia Hernandez

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;

// Variables de color
float rojo, verde, azul = 0.0f; // Variables que almacenan los valores de los componentes RGB en el rango de [0.0, 1.0] 
float duracion = 2.0f; // Define el intervalo en segundos para actualizar el color de fondo

// Funcion para generar un color de fondo aleatorio
// Al dividir el valor generado por RAND_MAX, se normaliza el resultado dentro del rango [0.0, 1.0],
// asegurando que los colores estén dentro del espectro válido de RGB.
void generarColorAleatorio() {
	rojo = (float)rand() / RAND_MAX;
	verde = (float)rand() / RAND_MAX;
	azul = (float)rand() / RAND_MAX;
}

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,1.0f,1.0f);	 			\n\
}";

// Función para crear los triángulos que forman las letras
// Se definen los vértices de las letras "D", "A", "G" y "H" usando triángulos.
// Cada conjunto de tres coordenadas (x, y, z) define un triángulo en el espacio 2D con z = 0.0f.
void CrearTriangulo()
{
	GLfloat vertices[] = {
		// Letra D
		-0.8f, 0.9f, 0.0f, // Triangulo 1 de la letra D
		-0.6f, 0.9f, 0.0f,
		-0.8f, 0.1f, 0.0f,

		-0.6f, 0.9f, 0.0f, //2
		-0.8f,0.1f, 0.0f,
		-0.6f, 0.1f, 0.0f,

		-0.6f, 0.1f, 0.0f, //3
		-0.6f, 0.3f, 0.0f,
		-0.1f, 0.3f, 0.0f,

		-0.6f, 0.1f, 0.0f, //4
		-0.3f, 0.1f, 0.0f,
		-0.1f, 0.3f, 0.0f,

		-0.4f, 0.3f, 0.0f, //5
		-0.3f, 0.3f, 0.0f,
		-0.3f, 0.4f, 0.0f,

		-0.3f, 0.3f, 0.0f, //6
		-0.1f, 0.3f, 0.0f,
		-0.1f, 0.7f, 0.0f,

		-0.3f, 0.3f, 0.0f, //7
		-0.3f, 0.7f, 0.0f,
		-0.1f, 0.7f, 0.0f,

		-0.4f, 0.7f, 0.0f, //8
		-0.3f, 0.6f, 0.0f,
		-0.3f, 0.7f, 0.0f,

		-0.6f, 0.7f, 0.0f, //9
		-0.6f, 0.9f, 0.0f,
		-0.1f, 0.7f, 0.0f,

		-0.6f, 0.9f, 0.0f, //10
		-0.3f, 0.9f, 0.0f,
		-0.1f, 0.7f, 0.0f,


		// Letra A
		0.1f, 0.1f, 0.0f, // Triangulo 1 de letra A
		0.4f, 0.9f, 0.0f,
		0.6f, 0.9f, 0.0f,

		0.1f, 0.1f, 0.0f, //2
		0.3f, 0.1f, 0.0f,
		0.6f, 0.9f, 0.0f,

		0.35f, 0.25f, 0.0f, //3
		0.4f, 0.4f, 0.0f,
		0.6f, 0.4f, 0.0f,

		0.65f, 0.25f, 0.0f, //4
		0.6f, 0.4f, 0.0f,
		0.35f, 0.25f, 0.0f,

		0.5f, 0.65f, 0.0f, //5
		0.7f, 0.1f, 0.0f,
		0.9f, 0.1f, 0.0f,

		0.9f, 0.1f, 0.0f, //6
		0.5f, 0.65f, 0.0f,
		0.6f, 0.9f, 0.0f,


		// Letra G
		-0.5f, -0.5f, 0.0f, // Triangulo 1 de letra G
		-0.5f, -0.6f, 0.0f,
		-0.4f, -0.5f, 0.0f,

		-0.4f, -0.5f, 0.0f, //2
		-0.5f, -0.6f, 0.0f,
		-0.4f, -0.6f, 0.0f,

		-0.4f, -0.5f, 0.0f, //3
		-0.2f, -0.5f, 0.0f,
		-0.4f, -0.7f, 0.0f,

		-0.2f, -0.5f, 0.0f, //4
		-0.4f, -0.7f, 0.0f,
		-0.2f, -0.7f, 0.0f, 

		-0.2f, -0.7f, 0.0f, //5
		-0.2f, -0.8f, 0.0f,
		-0.3f, -0.9f, 0.0f,

		-0.2f, -0.7f, 0.0f, //6
		-0.3f, -0.9f, 0.0f,
		-0.8f, -0.7f, 0.0f,

		-0.8f,-0.7f, 0.0f, //7
		-0.3f, -0.9f, 0.0f,
		-0.7f, -0.9f, 0.0f,

		-0.8f, -0.7f, 0.0f, //8
		-0.8f, -0.8f, 0.0f,
		-0.7f, -0.9f, 0.0f,

		-0.8f, -0.7f, 0.0f, //9
		-0.6f, -0.7f, 0.0f,
		-0.6f, -0.3f, 0.0f,

		-0.8f, -0.7f, 0.0f, //10
		-0.6f, -0.3f, 0.0f,
		-0.8f, -0.3f, 0.0f,

		-0.8f, -0.3f, 0.0f, //11
		-0.8f, -0.2f, 0.0f,
		-0.7f, -0.1f, 0.0f,

		-0.7f, -0.1f, 0.0f, //12
		-0.8f, -0.3f, 0.0f,
		-0.3f, -0.1f, 0.0f,

		-0.3f, -0.1f, 0.0f, //13
		-0.8f, -0.3f, 0.0f,
		-0.2f, -0.3f, 0.0f,

		-0.3f, -0.1f, 0.0f, //14
		-0.2f, -0.3f, 0.0f,
		-0.2f, -0.2f, 0.0f,

		-0.2f, -0.3f, 0.0f, //15
		-0.4f, -0.3f, 0.0f,
		-0.4f, -0.4f, 0.0f,

		-0.2f, -0.3f, 0.0f, //16
		-0.2f, -0.4f, 0.0f,
		-0.4f, -0.4f, 0.0f,

		
		// Letra H
		0.2f, -0.1f, 0.0f, // Triangulo 1 de letra H
		0.4f, -0.1f, 0.0f,
		0.2f, -0.9f, 0.0f,

		0.4f, -0.1f, 0.0f, //2
		0.2f, -0.9f, 0.0f,
		0.4f, -0.9f, 0.0f,

		0.4f, -0.4f, 0.0f, //3
		0.4f, -0.6f, 0.0f,
		0.6f, -0.4f, 0.0f,

		0.6f, -0.4f, 0.0f, //4
		0.6f, -0.6f, 0.0f,
		0.4f, -0.6f, 0.0f,

		0.6f, -0.1f, 0.0f, //5
		0.8f, -0.1f, 0.0f,
		0.6f, -0.9f, 0.0f,

		0.8f, -0.1f, 0.0f, //6 
		0.8f, -0.9f, 0.0f,
		0.6f, -0.9f, 0.0f


	};

	// Generacion de buffers para almacenar y manejar vertices en la GPU
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO); // Se crea un VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Se enlaza el VBO para asignar datos
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader = glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	//verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}

int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1: Introduccion a OpenGL", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("\n Reemplazar con Número de cuenta del alumno \n");
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//Crear tríangulo
	CrearTriangulo();
	CompileShaders();

	// Iniciar aleatoridad
	srand(time(NULL)); // Se establece la semilla para la generacion de numeros aleatorios
	generarColorAleatorio(); // Se genera un color aleatorio inicial antes de que la ventana comience a renderizar
	glfwSetTime(0); // Para reiniciar el temporizador de GLFW
	
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();


		// Cambio de estado que verifica que ha pasado al menos dos segundos desde el ultimo cambio
		if (glfwGetTime() >= duracion) {
			generarColorAleatorio(); // Genera un nuevo color aleatorio
			glfwSetTime(0); // Reiniciar el temporizador a 0

		}

		//Limpiar la ventana
		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activa el shader program que controla el renderizado
		glUseProgram(shader);

		// Dibuja las letras en pantalla
		glBindVertexArray(VAO); // Se vincula el VAO que tiene la info de los vertices
		glDrawArrays(GL_TRIANGLES, 0, 114); // Se dibujan los triangulos definidos
		glBindVertexArray(0); // Se desvincula el VAO para evitar modificaciones accidentales

		// Se desactiva el uso de shaders para evitar afectar otros procesos
		glUseProgram(0);

		// Intercambia los buffers de renderizado,
		// permitiendo actualizar la imagen en pantalla sin parpadeos
		glfwSwapBuffers(mainWindow);

	}


	return 0;
}