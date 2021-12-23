#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "init_params.h"

int road_count = 0;
int bus_count = 0;
int grass_count = 0;
int sky_count = 0;
int olen_count = 0;
int cone_count = 0;


//id программы
GLuint shaderProgram;
//id атрибута вершин
GLint attribVertex;
//id атрибута текстур
GLint attribTex;
//id атрибута нормалей
GLint attribNormal;
//id глоб. переменной текстуры
GLint unifTexture;
//id глоб. переменной поворота
GLint unifRotate;
//id глоб. переменной передвижения
GLint unifMove;
//id глоб. переменной масштабирования
GLint unifScale;

//вершинный буфер дороги
GLuint roadVBO;
//вершинный буфер грузовика
GLuint busVBO;
//вершинный буфер травы
GLuint grassVBO;
//вершинный буфер небаФ
GLuint skyVBO;
GLuint olenVBO;
GLuint coneVBO;

//для загрузки текстур в opengl
GLint roadTextureHandle;
GLint busTextureHandle;
GLint grassTextureHandle;
GLint skyTextureHandle;
GLint coneTextureHandle;
GLint olenTextureHandle;

sf::Texture roadTextureData;
sf::Texture busTextureData;
sf::Texture grassTextureData;
sf::Texture skyTextureData;
sf::Texture coneTextureData;
sf::Texture olenTextureData;

//вершинные массивы для объектов
GLuint roadVAO;
GLuint busVAO;
GLuint grassVAO;
GLuint skyVAO;
GLuint olenVAO;
GLuint coneVAO;

//id глоб. переменной точки обзора
GLint Unif_transform_viewPosition;

//id глоб. переменных для материалов
GLint Unif_material_emission;
GLint Unif_material_ambient;
GLint Unif_material_diffuse;
GLint Unif_material_specular;
GLint Unif_material_shininess;

//id глоб. переменных для освещения
GLint Unif_light_ambient;
GLint Unif_light_diffuse;
GLint Unif_light_specular;
GLint Unif_light_attenuation;
GLint Unif_light_direction;

//логгирование ошибок
void checkOpenGLerror() {
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error!: " << errCode << std::endl;
}
void ShaderLog(unsigned int shader)
{
	int infologLen = 0;
	int charsWritten = 0;
	char* infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << "ERROR: Could not allocate InfoLog buffer" << std::endl;
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}


Index StringToIndex(std::string s)
{
	std::vector<std::string> split;
	std::stringstream ss(s);
	std::string str;
	while (std::getline(ss, str, '/'))
	{
		split.push_back(str);
	}
	Index i = { std::stoi(split[0]), std::stoi(split[1]), std::stoi(split[2]) };
	return i;
}
Index SurfaceToIndex(Surface s)
{
	std::vector<Index> v;
	Index i = { s.vert[0].x, s.vert[1].x, s.vert[2].x };
	return i;
}

/// <summary>
/// Загрузка молдели из файла
/// </summary>
/// <param name="filename"></param>
/// <param name="count"></param>
/// <returns></returns>
std::vector<float> ReadModel(std::string filename, int& count)
{
	std::vector<Vertex> v;
	std::vector<Tex> t;
	std::vector<Normal> n;
	std::vector<Surface> s;

	std::ifstream infile(filename);
	std::string line;

	while (std::getline(infile, line))
	{
		if (line[0] == 'v' || line[0] == 'f')
		{
			//разбиваем каждую строку по пробелам в вектор split
			std::vector<std::string> split;
			std::stringstream ss(line);
			std::string str;
			while (std::getline(ss, str, ' '))
			{
				split.push_back(str);
			}

			//заполняем вектор вершин
			if (split[0] == "v")
			{
				Vertex vert = { std::stof(split[1]), std::stof(split[2]), std::stof(split[3]) };
				v.push_back(vert);
			}

			//заполняем вектор текстурных координат
			else if (split[0] == "vt")
			{
				Tex tex = { std::stof(split[1]), std::stof(split[2]) };
				t.push_back(tex);
			}

			//заполняем вектор нормалей
			else if (split[0] == "vn")
			{
				Normal norm = { std::stof(split[1]), std::stof(split[2]), std::stof(split[3]) };
				n.push_back(norm);
			}

			//заполняем массив индексов и соответствий
			else if (split[0] == "f")
			{
				Surface surf =
				{
					StringToIndex(split[1]),
					StringToIndex(split[2]),
					StringToIndex(split[3]),
				};
				s.push_back(surf);
			}
		}
	}

	std::vector<float> pos_tex;
	for (int i = 0; i < s.size(); ++i)
	{
		pos_tex.push_back(v[s[i].vert[0].x - 1].x);
		pos_tex.push_back(v[s[i].vert[0].x - 1].y);
		pos_tex.push_back(v[s[i].vert[0].x - 1].z);
		pos_tex.push_back(t[s[i].vert[0].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[0].y - 1].y);
		pos_tex.push_back(n[s[i].vert[0].z - 1].x);
		pos_tex.push_back(n[s[i].vert[0].z - 1].y);
		pos_tex.push_back(n[s[i].vert[0].z - 1].z);

		pos_tex.push_back(v[s[i].vert[1].x - 1].x);
		pos_tex.push_back(v[s[i].vert[1].x - 1].y);
		pos_tex.push_back(v[s[i].vert[1].x - 1].z);
		pos_tex.push_back(t[s[i].vert[1].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[1].y - 1].y);
		pos_tex.push_back(n[s[i].vert[1].z - 1].x);
		pos_tex.push_back(n[s[i].vert[1].z - 1].y);
		pos_tex.push_back(n[s[i].vert[1].z - 1].z);

		pos_tex.push_back(v[s[i].vert[2].x - 1].x);
		pos_tex.push_back(v[s[i].vert[2].x - 1].y);
		pos_tex.push_back(v[s[i].vert[2].x - 1].z);
		pos_tex.push_back(t[s[i].vert[2].y - 1].x);
		pos_tex.push_back(1 - t[s[i].vert[2].y - 1].y);
		pos_tex.push_back(n[s[i].vert[2].z - 1].x);
		pos_tex.push_back(n[s[i].vert[2].z - 1].y);
		pos_tex.push_back(n[s[i].vert[2].z - 1].z);
	}
	count = s.size() * 3;
	return pos_tex;
}


/// <summary>
/// инициализация вршинного буфера
/// </summary>
void InitVBO()
{
	//Загружаем дорогу
	std::vector<float> pos_tex = ReadModel("resources/road.obj", road_count);

	
	glGenBuffers(1, &roadVBO);	//создаём буфер
	glGenVertexArrays(1, &roadVAO);	//создаём VAO

	glBindVertexArray(roadVAO);	//привязываем VAO

	//Копируем массив вершин в буфер
	glEnableVertexAttribArray(attribVertex);	
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, roadVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//bus
	pos_tex = ReadModel("resources/bus2.obj", bus_count);

	glGenBuffers(1, &busVBO);
	glGenVertexArrays(1, &busVAO);

	glBindVertexArray(busVAO);

	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, busVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//grass
	pos_tex = ReadModel("resources/grass.obj", grass_count);

	glGenBuffers(1, &grassVBO);
	glGenVertexArrays(1, &grassVAO);

	glBindVertexArray(grassVAO);

	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	//sky
	pos_tex = ReadModel("resources/sky.obj", sky_count);
	glGenBuffers(1, &skyVBO);
	glGenVertexArrays(1, &skyVAO);

	glBindVertexArray(skyVAO);

	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	//los(olen)
	pos_tex = ReadModel("resources/olen.obj", olen_count);
	glGenBuffers(1, &olenVBO);
	glGenVertexArrays(1, &olenVAO);

	glBindVertexArray(olenVAO);

	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, olenVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	//cone
	pos_tex = ReadModel("resources/cone.obj", cone_count);
	glGenBuffers(1, &coneVBO);
	glGenVertexArrays(1, &coneVAO);

	glBindVertexArray(coneVAO);

	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTex);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, coneVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	checkOpenGLerror();
}

/// <summary>
/// Инициализация юниформы имени
/// </summary>
GLint InitUniform(const char* name)
{
	GLint id = glGetUniformLocation(shaderProgram, name);
	if (id == -1)
		std::cout << "could not bind uniform " << name << std::endl;
	return id;
}

/// <summary>
/// Инициализация шейдеров
/// </summary>
void InitShader() {
	//создаём и компилируем вершинный шейдер
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &VertexShader, NULL);
	glCompileShader(vShader);
	std::cout << "vertex shader \n";
	ShaderLog(vShader);

	//создаём и компилируем фрагментный шейдер
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &FragmentShader, NULL);
	glCompileShader(fShader);
	std::cout << "fragment shader \n";
	ShaderLog(fShader);

	//создаём программу и привзяывем к ней шейдеры
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	// Линкуем шейдерную программу
	glLinkProgram(shaderProgram);
	// Проверяем статус сборки
	int link_status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_status);
	if (!link_status)
	{
		std::cout << "error attach shaders \n";
		return;
	}

	// Вытягиваем ID атрибутов из собранной программы
	attribVertex = glGetAttribLocation(shaderProgram, "coord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib coord" << std::endl;
		return;
	}
	attribTex = glGetAttribLocation(shaderProgram, "texcoord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib texcoord" << std::endl;
		return;
	}
	attribNormal = glGetAttribLocation(shaderProgram, "normal");
	if (attribNormal == -1)
	{
		std::cout << "could not bind attrib normal" << std::endl;
		return;
	}

	//инициализируем юниформы
	unifTexture = InitUniform("textureData");
	unifRotate = InitUniform("rotate");
	unifMove = InitUniform("move");
	unifScale = InitUniform("scale");
	Unif_transform_viewPosition = InitUniform("viewPosition");
	Unif_material_emission = InitUniform("material.emission");
	Unif_material_ambient = InitUniform("material.ambient");
	Unif_material_diffuse = InitUniform("material.diffuse");
	Unif_material_specular = InitUniform( "material.specular");
	Unif_material_shininess = InitUniform("material.shininess");
	Unif_light_ambient = InitUniform("light.ambient");
	Unif_light_diffuse = InitUniform("light.diffuse");
	Unif_light_specular = InitUniform("light.specular");
	Unif_light_direction = InitUniform("light.direction");

	checkOpenGLerror();
}

/// <summary>
/// Загрузка текстур моделей
/// </summary>
void InitTexture()
{
	const char* road = "resources/road.png";
	const char* bus = "resources/bus2.png";
	const char* grass = "resources/grass.png";
	const char* sky = "resources/sky.jpg";
	const char* olen = "resources/olen.png";
	const char* cone = "resources/cone.png";
	if (!busTextureData.loadFromFile(bus))
	{
		std::cout << "could not load texture bus";
		return;
	}
	if (!roadTextureData.loadFromFile(road))
	{
		std::cout << "could not load texture road";
		return;
	}
	if (!grassTextureData.loadFromFile(grass))
	{
		std::cout << "could not load texture grass";
		return;
	}
	if (!skyTextureData.loadFromFile(sky))
	{
		std::cout << "could not load texture sky";
		return;
	}
	if (!olenTextureData.loadFromFile(olen))
	{
		std::cout << "could not load texture olen";
		return;
	}
	if (!coneTextureData.loadFromFile(cone))
	{
		std::cout << "could not load texture cone";
		return;
	}
	roadTextureHandle = roadTextureData.getNativeHandle();
	busTextureHandle = busTextureData.getNativeHandle();
	grassTextureHandle = grassTextureData.getNativeHandle();
	skyTextureHandle = skyTextureData.getNativeHandle();
	olenTextureHandle = olenTextureData.getNativeHandle();
	coneTextureHandle = coneTextureData.getNativeHandle();
}

/// <summary>
/// Инициализация буферов, шейдеров и текстур
/// </summary>
void Init() {
	InitShader();
	InitVBO();
	InitTexture();
}