#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

#include "init.h"

void Draw() {
	// Устанавливаем шейдерную программу текущей
	glUseProgram(shaderProgram);

	//material
	glUniform4fv(Unif_material_emission, 1, material.emission);
	glUniform4fv(Unif_material_ambient, 1, material.ambient);
	glUniform4fv(Unif_material_diffuse, 1, material.diffuse);
	glUniform4fv(Unif_material_specular, 1, material.specular);
	glUniform1f(Unif_material_shininess, material.shininess);

	//light
	glUniform4fv(Unif_light_ambient, 1, light.ambient);
	glUniform4fv(Unif_light_diffuse, 1, light.diffuse);
	glUniform4fv(Unif_light_specular, 1, light.specular);
	glUniform3fv(Unif_light_direction, 1, light.direction);

	glUniform3fv(Unif_transform_viewPosition, 1, viewPosition);


	//olen
	glUniform3fv(unifRotate, 1, olenRotate);
	glUniform3fv(unifMove, 1, olenMove);
	glUniform3fv(unifScale, 1, olenScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&olenTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(olenVAO);
	glDrawArrays(GL_TRIANGLES, 0, olen_count);
	glBindVertexArray(0);

	//cone
	glUniform3fv(unifRotate, 1, coneRotate);
	glUniform3fv(unifMove, 1, coneMove);
	glUniform3fv(unifScale, 1, coneScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&coneTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(coneVAO);
	glDrawArrays(GL_TRIANGLES, 0, cone_count);
	glBindVertexArray(0);

	//bus
	glUniform3fv(unifRotate, 1, busRotate);
	glUniform3fv(unifMove, 1, busMove);
	glUniform3fv(unifScale, 1, busScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&busTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(busVAO);
	glDrawArrays(GL_TRIANGLES, 0, bus_count);
	glBindVertexArray(0);

	//road1
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road1Move);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//road2
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road2Move);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//road3
	glUniform3fv(unifRotate, 1, roadRotate);
	glUniform3fv(unifMove, 1, road3Move);
	glUniform3fv(unifScale, 1, roadScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//grassleft1
	glUniform3fv(unifRotate, 1, grassLeftRotate);
	glUniform3fv(unifMove, 1, grassLeft1Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassleft2
	glUniform3fv(unifRotate, 1, grassLeftRotate);
	glUniform3fv(unifMove, 1, grassLeft2Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassleft3
	glUniform3fv(unifRotate, 1, grassLeftRotate);
	glUniform3fv(unifMove, 1, grassLeft3Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassleft4
	glUniform3fv(unifRotate, 1, grassLeftRotate);
	glUniform3fv(unifMove, 1, grassLeft4Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	//grassright1
	glUniform3fv(unifRotate, 1, grassRightRotate);
	glUniform3fv(unifMove, 1, grassRight1Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassright2
	glUniform3fv(unifRotate, 1, grassRightRotate);
	glUniform3fv(unifMove, 1, grassRight2Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassright3
	glUniform3fv(unifRotate, 1, grassRightRotate);
	glUniform3fv(unifMove, 1, grassRight3Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassright3
	glUniform3fv(unifRotate, 1, grassRightRotate);
	glUniform3fv(unifMove, 1, grassRight4Move);
	glUniform3fv(unifScale, 1, grassScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	//sky
	glUniform3fv(unifRotate, 1, skyRotate);
	glUniform3fv(unifMove, 1, skyMove);
	glUniform3fv(unifScale, 1, skyScale);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&skyTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(skyVAO);
	glDrawArrays(GL_TRIANGLES, 0, sky_count);
	glBindVertexArray(0);

	glUseProgram(0);
	checkOpenGLerror();
}


void ReleaseShader() {
	glUseProgram(0);
	glDeleteProgram(shaderProgram);
}
void ReleaseVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &roadVAO);
	glDeleteBuffers(1, &roadVBO);

	glDeleteVertexArrays(1, &busVAO);
	glDeleteBuffers(1, &busVBO);
}
void Release() {
	ReleaseShader();
	ReleaseVBO();
}

void HandleTerrain(double speed)
{
	road1Move[2] -= speed;
	road2Move[2] -= speed;
	road3Move[2] -= speed;
	if (road1Move[2] < -10)
		road1Move[2] = 10;
	if (road2Move[2] < 10)
		road2Move[2] = 30;
	if (road3Move[2] < 30)
		road3Move[2] = 50;

	grassLeft1Move[2] -= speed;
	grassLeft2Move[2] -= speed;
	grassLeft3Move[2] -= speed;
	grassLeft4Move[2] -= speed;
	grassRight1Move[2] -= speed;
	grassRight2Move[2] -= speed;
	grassRight3Move[2] -= speed;
	grassRight4Move[2] -= speed;

	if (grassLeft1Move[2] < -10)
		grassLeft1Move[2] = 10;
	if (grassLeft2Move[2] < 10)
		grassLeft2Move[2] = 30;
	if (grassLeft3Move[2] < 30)
		grassLeft3Move[2] = 50;
	if (grassLeft4Move[2] < 50)
		grassLeft4Move[2] = 70;

	if (grassRight1Move[2] < -10)
		grassRight1Move[2] = 10;
	if (grassRight2Move[2] < 10)
		grassRight2Move[2] = 30;
	if (grassRight3Move[2] < 30)
		grassRight3Move[2] = 50;
	if (grassRight4Move[2] < 50)
		grassRight4Move[2] = 70;
}
void HandleBariers(int& level_counter, double& speed)
{
	olenMove[2] -= speed;
	coneMove[2] -= speed;

	if (olenMove[2] < -0.1)
	{
		level_counter++;
		if (level_counter % 2 == 0)
			speed += 0.03;
		olenMove[2] = 41.0f;
		coneMove[2] = 41.0f;
		int current_barrier = rand() % 2;
		int current_strip = rand() % 3;
		if (current_strip == 0)
		{
			olenMove[0] = -1;
			coneMove[0] = -1;
		}
		else if (current_strip == 1)
		{
			olenMove[0] = 0;
			coneMove[0] = 0;
		}
		else
		{
			olenMove[0] = 1;
			coneMove[0] = 1;
		}
		if (current_barrier == 1)
			coneMove[0] = -100.0f;
		else
			olenMove[0] = -100.0f;
	}
}
bool HasIntersection()
{
	return sqrt((busMove[2] - olenMove[2]) * (busMove[2] - olenMove[2]) + (busMove[0] - olenMove[0]) * (busMove[0] - olenMove[0])) < 0.5f;
}


int main() {
	sf::Window window(sf::VideoMode(800, 800), "Subway Surf Clone", sf::Style::Default, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	srand(clock());
	// Инициализация glew
	glewInit();
	glEnable(GL_DEPTH_TEST);

	Init();

	bool moveLeft = false;
	bool moveRight = false;

	double angle = 0.524;
	double radius = 150.0;
	double speed = 0.07;
	int level_counter = 0;

	int current_barrier = rand() % 2;
	int current_strip = rand() % 3;
	if (current_strip == 0)
	{
		olenMove[0] = -1;
		coneMove[0] = -1;
	}
	else if (current_strip == 1)
	{
		olenMove[0] = 0.0f;
		coneMove[0] = 0.0f;
	}
	else 
	{
		olenMove[0] = 1;
		coneMove[0] = 1;
	}
	if (current_barrier == 0)
		olenMove[0] = -100.f;
	else
		coneMove[0] = -100.f;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = true;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = true;
					break;
				}
				case (sf::Keyboard::Left):
				{
					light.direction[0] -= 5.0;
					break;
				}
				case (sf::Keyboard::Right):
				{
					angle += 0.1;
					light.direction[0] = radius * std::sin(angle) - 50;
					light.direction[1] = radius * std::cos(angle);
					break;
				}
				case (sf::Keyboard::Up):
				{
					angle -= 0.1;
					light.direction[0] = radius * std::sin(angle) - 50;
					light.direction[1] = radius * std::cos(angle);
					break;
				}
				case (sf::Keyboard::Down):
				{
					light.direction[2] -= 1.0;
					break;
				}
				default: break;
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = false;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = false;
					break;
				}
				default: break;
				}
			}
		}

		

		if (moveLeft && busMove[0] > -1)
		{
			busMove[0] -= 0.05;
			busRotate[1] -= 0.05;
		}
		if (moveRight && busMove[0] < 1)
		{
			busMove[0] += 0.05;
			busRotate[1] += 0.05;
		}

		if (busRotate[1] < -3.14f )
		{
			busRotate[1] += 0.03f;
			if (std::abs(busRotate[1] - 3.14f) < 0.03f)
				busRotate[1] = -3.14f;
		}
		if (busRotate[1] > -3.14f )
		{
			busRotate[1] -= 0.03f;
			if (std::abs(busRotate[1] - 3.14f) < 0.03f)
				busRotate[1] = -3.14f;
		}
		
		if (std::abs(busMove[1] + 0.25) < 0.01f)
		{
			busMove[1] += 1.0f;
		}

		    
		HandleTerrain(speed);
		HandleBariers(level_counter, speed);

		if (HasIntersection())
		{
			level_counter = 0;
			speed = 0.07;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw();

		window.display();
	}

	Release();
	return 0;
}


