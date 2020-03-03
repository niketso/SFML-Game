#include <SFML/Graphics.hpp>
#include"Ball.h"
#include"Brick.h"
#include"Paddle.h"
#include <iostream>
using namespace sf;
using namespace std;

constexpr int windowWidth(800), windowHeight(600);

int main()
{
	Ball ball(windowWidth / 2.f, windowHeight / 2.f);
	Paddle paddle(windowWidth / 2.f, windowHeight - 30.f);
	vector<Brick> brickVec;

	for (int i = 0; i < bricksOnX; i++)
	{
		for (int j = 0; j < bricksOnY; j++)
		{
			brickVec.emplace_back(((i+1) * (brickWidth + 2)), ((j+2) * (brickHeight+2)));
		}
	}

	RenderWindow appWindow(VideoMode(windowWidth, windowHeight), "BreakOut");
	appWindow.setFramerateLimit(60);
	
	while (appWindow.isOpen())
	{
		Event event;
		while (appWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				appWindow.close();
		}
		ball.Update( windowWidth,windowHeight);
		paddle.Update( windowWidth,windowHeight);

		PaddleCollision(paddle, ball);
		for (int i = 0; i < brickVec.size(); i++)
		{
			BrickCollision(brickVec[i], ball);
		}
			
			brickVec.erase(remove_if(begin(brickVec), end(brickVec),
			[](const Brick& brick) {return brick.isDestroyed; }),
			end(brickVec));

			if (brickVec.size() == 0)
			{
				cout << "Ganaste" << endl;
				appWindow.close();
			}
		
		appWindow.clear();
		appWindow.draw(ball.shape);
		appWindow.draw(paddle.shape);

		for (int i = 0; i < brickVec.size(); i++)
		{
			appWindow.draw(brickVec[i].shape);
		}
		appWindow.display();
	}

	return 0;
}

