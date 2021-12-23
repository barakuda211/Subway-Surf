#pragma once

struct Vertex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct Tex
{
	GLfloat x;
	GLfloat y;
};

struct Normal
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct Index
{
	GLushort x;
	GLushort y;
	GLushort z;
};

struct Surface
{
	Index vert[3];
};

float busRotate[3] = { 0.0f, -3.14f, 0.0f };
float busMove[3] = { 0.0f, -1.0f, 0.7f };
float busScale[3] = { 0.07f, 0.07f, 0.07f };

float olenRotate[3] = { 0.0f, -0.01f, 0.0f };
float olenMove[3] = { 0.0f, -1.0f, 41.0f };
float olenScale[3] = { 0.1f, 0.1f, 0.1f };

float coneRotate[3] = { 0.0f, 0.0f, 0.0f };
float coneMove[3] = { 0.0f, -1.0f, 41.0f };
float coneScale[3] = { 0.2f,  0.2f,  0.2f };

float road1Move[3] = { 0.0f, -1.0f, 10.0f };
float road2Move[3] = { 0.0f, -1.0f, 30.0f };
float road3Move[3] = { 0.0f, -1.0f, 50.0f };
float roadRotate[3] = { 0.0f, 0.0f, 0.0f };
float roadScale[3] = { 0.1f, 0.1f, 0.1f };

float grassLeftRotate[3] = { 0.0f, -3.1415f, 0.1f };
float grassRightRotate[3] = { 0.0f, 0.0f, -0.1f };
float grassLeft1Move[3] = { -11.6f, -2.1f, 10.0f };
float grassLeft2Move[3] = { -11.6f, -2.1f, 30.0f };
float grassLeft3Move[3] = { -11.6f, -2.1f, 50.0f };
float grassLeft4Move[3] = { -11.6f, -2.1f, 70.0f };
float grassRight1Move[3] = { 11.6f, -2.1f, 10.0f };
float grassRight2Move[3] = { 11.6f, -2.1f, 30.0f };
float grassRight3Move[3] = { 11.6f, -2.1f, 50.0f };
float grassRight4Move[3] = { 11.6f, -2.1f, 70.0f };
float grassScale[3] = { 0.1f, 0.1f, 0.1f };

float skyRotate[3] = { -1.7f, 0.0f, 3.1415f };
float skyMove[3] = { 0.0f, 23.0f, 40.0f };
float skyScale[3] = { 100.0f, 20.0f, 50.0f };

float viewPosition[3] = { 0.0, 0.0, -100.0 };

struct Material
{
	float emission[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float shininess = 128.0f;
};
Material material;

struct Light
{
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 0.9f, 0.9f, 0.9f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float direction[3] = { 0.0f, 80.0f, -150.0f };
};
Light light;

// Вершинный шейдер
const char* VertexShader = R"(
    #version 330 core

	uniform vec3 rotate;
	uniform vec3 move;
	uniform vec3 scale;

	uniform vec3 viewPosition;

	uniform struct PointLight {
		vec3 direction;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	} light;

    in vec3 coord;
	in vec2 texcoord;
	in vec3 normal;

	out Vertex {
		vec2 texcoord;
		vec3 normal;
		vec3 lightDir;
		vec3 viewDir;
	} Vert;

    void main() {

		vec3 vertex = coord * mat3(
									scale[0], 0, 0,
									0, scale[1], 0,
									0, 0, scale[2]);	

        // Поворачиваем вершину
        mat3 rotate = mat3(
            1, 0, 0,
            0, cos(rotate[0]), -sin(rotate[0]),
            0, sin(rotate[0]), cos(rotate[0])
        ) * mat3(
            cos(rotate[1]), 0, sin(rotate[1]),
            0, 1, 0,
            -sin(rotate[1]), 0, cos(rotate[1])
        ) * mat3(
			cos(rotate[2]), -sin(rotate[2]), 0,
			sin(rotate[2]), cos(rotate[2]), 0,
			0, 0, 1
		);	

		vertex *= rotate;

        vec4 vert = vec4(vertex, 1.0);

		vert *= mat4(
					1, 0, 0, move[0],
					0, 1, 0, move[1],
					0, 0, 1, move[2],
					0, 0, 0, 1);

		float c = -1;
		float last_z = vert.z;
		vert *= mat4(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, -1/c, 1);

		gl_Position = vec4(vert.xy, last_z * vert[3] / 100, vert[3]);

		Vert.texcoord = texcoord;
		Vert.normal = normal * rotate;
		Vert.lightDir = light.direction;
		Vert.viewDir = viewPosition - vec3(vert);
    }
)";

// Фрагментный шейдер
const char* FragmentShader = R"(
    #version 330 core

	in Vertex {
		vec2 texcoord;
		vec3 normal;
		vec3 lightDir;
		vec3 viewDir;
	} Vert;

	uniform struct PointLight {
		vec3 direction;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	} light;

	uniform struct Material {
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 emission;
		float shininess;
	} material;

	uniform sampler2D textureData;

	out vec4 color;

    void main() {
		
		vec3 normal = normalize(Vert.normal);
		vec3 lightDir = normalize(Vert.lightDir);
		vec3 viewDir = normalize(Vert.viewDir);

		color = material.emission;
		color += material.ambient * light.ambient;

		float Ndot = max(dot(normal, lightDir), 0.0);
		color += material.diffuse * light.diffuse * Ndot;

		float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
		color +=material.specular * light.specular * RdotVpow;

		color *= texture(textureData, Vert.texcoord);
    }
)";