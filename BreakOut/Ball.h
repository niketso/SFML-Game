#ifndef BALL_H
#define BALL_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

constexpr float ballRadius(10.0f), ballVelocity(8.0f);

struct Ball
{

	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };

	//ball bounderies
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }


	Ball(float startPosX, float startPosY)
	{
		shape.setPosition(startPosX, startPosY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Green);
		shape.setOrigin(ballRadius, ballRadius);
	}

	void Update(float windowWidth, float windowHeight)
	{
		shape.move(velocity);
		CheckBounderies( windowWidth, windowHeight);
	}
	void CheckBounderies(float windowWidth,float windowHeight)
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
#endif