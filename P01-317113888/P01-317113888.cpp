#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <windows.h>
#include <random>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Variables de color y tiempo
float rojo = 0.8f;
float verde = 0.6f;
float azul = 1.0f;
double segundos;

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



void CrearTriangulo()
{
	GLfloat vertices[] = {
		//Letra A
		-0.9, -0.5, 0.0, //A
		-0.75, -0.5, 0.0, //D
		-0.9, 0.5, 0.0, //B

		-0.75, 0.5, 0.0, //I1
		-0.9, 0.5, 0.0, //B
		-0.75, -0.5, 0.0, //D

		-0.75, -0.15, 0.0, //E
		-0.6, -0.15, 0.0, //F
		-0.75, 0.1, 0.0, //I

		-0.75, 0.1, 0.0, //I
		-0.6, 0.1, 0.0, //L
		-0.6, -0.15, 0.0, //F

		-0.75, 0.35,0.0, //J
		-0.75, 0.5, 0.0, //I1
		-0.6, 0.35,0.0, //K

		-0.75, 0.5, 0.0, //I1
		-0.6, 0.35,0.0, //K
		-0.6, 0.5, 0.0, //J1

		-0.6, 0.5, 0.0, //J1
		-0.45, 0.5, 0.0, //C
		-0.45, -0.5, 0.0, //H

		-0.6, 0.5, 0.0, //J1
		-0.45, -0.5, 0.0, //H
		-0.6, -0.5,0.0, //G


		//LETRA D
		-0.24862, 0.49702, 0.0,//M
		- 0.24862, -0.50298, 0.0,//N
		-0.09862, 0.19702, 0.0, //S

		-0.24862, -0.50298, 0.0,//N
		-0.09862, 0.19702, 0.0, //S
		-0.09862, -0.20298, 0.0, //V

		-0.24862, -0.50298, 0.0,//N
		-0.09862, -0.20298, 0.0, //V
		0.25138, -0.30298, 0.0, //P

		-0.24862, -0.50298, 0.0,//N
		0.25138, -0.30298, 0.0, //P
		0.05138, -0.50298, 0.0, //R

		-0.09862, -0.20298, 0.0, //V
		0.25138, -0.30298, 0.0, //P
		0.05138, -0.20298, 0.0, //W

		0.25138, -0.30298, 0.0, //P
		0.05138, -0.20298, 0.0, //W
		0.10138, -0.15298, 0.0, //Z

		0.25138, -0.30298, 0.0, //P
		0.10138, -0.15298, 0.0, //Z
		0.25138, 0.29702, 0.0, //O

		0.10138, -0.15298, 0.0, //Z
		0.25138, 0.29702, 0.0, //O
		0.10138, 0.14702, 0.0, //U

		0.25138, 0.29702, 0.0, //O
		0.10138, 0.14702, 0.0, //U
		0.05138, 0.19702, 0.0, //T

		0.25138, 0.29702, 0.0, //O
		-0.09862, 0.19702, 0.0, //S
		0.05138, 0.19702, 0.0, //T

		0.25138, 0.29702, 0.0, //O
		-0.09862, 0.19702, 0.0, //S
		-0.24862, 0.49702, 0.0, //M

		-0.09862, 0.19702, 0.0, //S
		0.05138, 0.19702, 0.0, //T
		0.05138, 0.49702, 0.0, //Q

		-0.24862, 0.49702, 0.0, //M
		0.25138, 0.29702, 0.0, //O
		0.05138, 0.49702, 0.0, //Q

		//LETRA O
		0.4, -0.5, 0.0, //C1
		0.55, -0.35, 0.0, //G1
		0.4, 0.5, 0.0, //A1

		0.55, -0.35, 0.0, //G1
		0.4, 0.5, 0.0, //A1
		0.55, 0.35, 0.0, //E1

		0.4, 0.5, 0.0, //A1
		0.55, 0.35, 0.0, //E1
		0.95, 0.5, 0.0, //B1

		0.55, 0.35, 0.0, //E1
		0.95, 0.5, 0.0, //B1
		0.8, 0.35, 0.0, //F1

		0.95, 0.5, 0.0, //B1
		0.8, 0.35, 0.0, //F1
		0.95, -0.5, 0.0, //D1

		0.8, 0.35, 0.0, //F1
		0.95, -0.5, 0.0, //D1
		0.8, -0.35, 0.0, //H1

		0.95, -0.5, 0.0, //D1
		0.8, -0.35, 0.0, //H1
		0.4, -0.5, 0.0, //C1

		0.8, -0.35, 0.0, //H1
		0.4, -0.5, 0.0, //C1
		0.55, -0.35, 0.0 //G1


	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "P01-317113888", NULL, NULL);

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

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Obtener tiempo transcurrido desde el primer color
		segundos = glfwGetTime();
		//Función de cambio de color
		if (2.0 < segundos){
			//Obtener colores random
			rojo = (float)(rand()) / (float)(rand());
			verde = (float)(rand()) / (float)(rand());
			azul = (float)(rand()) / (float)(rand());
			glfwSetTime(0.0);	//Reinicia el tiempo 
		}
		//Limpiar la ventana
		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		// LETRA A
		glDrawArrays(GL_TRIANGLES,0,3); //inicio, cantidad de vertices
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);
		glDrawArrays(GL_TRIANGLES, 9, 3);
		glDrawArrays(GL_TRIANGLES, 12, 3);
		glDrawArrays(GL_TRIANGLES, 15, 3);
		glDrawArrays(GL_TRIANGLES, 18, 3);
		glDrawArrays(GL_TRIANGLES, 21, 3);

		//LETRA D
		glDrawArrays(GL_TRIANGLES, 24, 3);
		glDrawArrays(GL_TRIANGLES, 27, 3);
		glDrawArrays(GL_TRIANGLES, 30, 3);
		glDrawArrays(GL_TRIANGLES, 33, 3);
		glDrawArrays(GL_TRIANGLES, 36, 3);
		glDrawArrays(GL_TRIANGLES, 39, 3);
		glDrawArrays(GL_TRIANGLES, 42, 3);
		glDrawArrays(GL_TRIANGLES, 45, 3);
		glDrawArrays(GL_TRIANGLES, 48, 3);
		glDrawArrays(GL_TRIANGLES, 51, 3);
		glDrawArrays(GL_TRIANGLES, 54, 3);
		glDrawArrays(GL_TRIANGLES, 57, 3);
		glDrawArrays(GL_TRIANGLES, 60, 3);

		//LETRA 0
		glDrawArrays(GL_TRIANGLES, 63, 3);
		glDrawArrays(GL_TRIANGLES, 66, 3);
		glDrawArrays(GL_TRIANGLES, 69, 3);
		glDrawArrays(GL_TRIANGLES, 72, 3);
		glDrawArrays(GL_TRIANGLES, 75, 3);
		glDrawArrays(GL_TRIANGLES, 78, 3);
		glDrawArrays(GL_TRIANGLES, 81, 3);
		glDrawArrays(GL_TRIANGLES, 84, 3);


		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}