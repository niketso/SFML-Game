#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

constexpr int windowWidth(800), windowHeight(600);
constexpr float ballRadius(10.0f), ballVelocity(8.0f);
constexpr float paddleWidth(80.0f), paddleHeight(15.0f), paddleVelocity(6.0f);
constexpr float brickWidth(60.0f), brickHeight(20.0f);
constexpr int bricksOnX(12.0f), bricksOnY(5.0f);

struct Ball
{

	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };

	//ball bounderies
	float x()		{	return shape.getPosition().x;	}
	float y()		{	return shape.getPosition().y;	}
	float left()	{	return x() - shape.getRadius();	}
	float right()	{	return x() + shape.getRadius();	}
	float top()		{	return y() - shape.getRadius();	}
	float bottom()	{	return y() + shape.getRadius();	}
	

	Ball(float startPosX, float startPosY)
	{
		shape.setPosition(startPosX, startPosY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Green);
		shape.setOrigin(ballRadius, ballRadius);
	}

	void Update() 
	{
		shape.move(velocity);
		CheckBounderies();
	}
	void CheckBounderies()
	{
		if (left() < 0) 
		{
			velocity.x = ballVelocity;
		}
		else if (right() > windowWidth)
		{
			velocity.x = -ballVelocity;
		}

		if (top() < 0) 
		{
			velocity.y = ballVelocity;
		}
		else if (bottom() > windowHeight)
		{
			velocity.y = -ballVelocity;
			//velocity.x = velocity.y = 0.0f;
		}
	}
};
struct Paddle 
{
	RectangleShape shape;
	Vector2f velocity;

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.0f; }
	float right() { return x() + shape.getSize().x / 2.0f; }
	float top() { return y() - shape.getSize().y / 2.0f; }
	float bottom() { return y() + shape.getSize().y / 2.0f; }

	Paddle(float startPosX, float startPosY)
	{
		shape.setPosition(startPosX, startPosY);
		shape.setSize({ paddleWidth,paddleHeight });
		shape.setFillColor(Color::Blue);
		shape.setOrigin(paddleWidth / 2.0f, paddleHeight / 2.0f);
	}
	void Update() 
	{
		shape.move(velocity);
		CheckInputs();
		

	}
	void CheckInputs()
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
		{
			 velocity.x = -paddleVelocity;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
		{
			velocity.x = paddleVelocity;
		}
		else 
		{
			velocity.x = 0.0f;
		}
		
	}
	
};

struct Brick 
{
	RectangleShape shape;
	bool isDestroyed = false;
	Brick(float startPosX, float startPosY) 
	{
		shape.setPosition(startPosX, startPosY);
		shape.setSize({brickWidth,brickHeight});
		shape.setFillColor(Color::Yellow);
		shape.setOrigin(brickWidth / 2.0f, brickHeight / 2.0f);

	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.0f; }
	float right() { return x() + shape.getSize().x / 2.0f; }
	float top() { return y() - shape.getSize().y / 2.0f; }
	float bottom() { return y() + shape.getSize().y / 2.0f; }


};
void PaddleCollision(Paddle& paddle, Ball& ball)
	{
		if (!( paddle.right() >= ball.left() && paddle.left() <= ball.right() &&
			paddle.bottom() >= ball.top() && paddle.top() <= ball.bottom() ))
		{
			return;
		}

		ball.velocity.y = -ballVelocity;

		if (ball.x() < paddle.x())
		{
			ball.velocity.x = -ballVelocity;
		}
		else
		{
			ball.velocity.x = ballVelocity;
		}
	}

void BrickCollision(Brick& brick ,Ball& ball )
{
	
	if	(!(brick.right() >= ball.left() && brick.left() <= ball.right() &&
		brick.bottom() >= ball.top() && brick.top() <= ball.bottom()))
		{
			return;
		}

		brick.isDestroyed = true;

		float overlapLeft {ball.right() - brick.left()};
		float overlapRight {brick.right() - ball.left()};
		float overlapTop {ball.bottom() - brick.top()};
		float overlapBottom {brick.bottom() - ball.top()};
			
		bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));		
		bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

		//? uno o el otro
		float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (abs(minOverlapX) < abs(minOverlapY))
			ball.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
		else
			ball.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
		
}


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
		ball.Update();
		paddle.Update();

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

