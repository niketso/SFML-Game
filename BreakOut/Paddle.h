#ifndef PADDLE_H
#define PADDLE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

constexpr float paddleWidth(80.0f), paddleHeight(15.0f), paddleVelocity(6.0f);

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
	void Update(float windowWidth, float windowHeight)
	{
		shape.move(velocity);
		CheckInputs(windowWidth,windowHeight);

	}
	void CheckInputs(float windowWidth,float windowHeight)
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

void PaddleCollision(Paddle& paddle, Ball& ball)
{
	if (!(paddle.right() >= ball.left() && paddle.left() <= ball.right() &&
		paddle.bottom() >= ball.top() && paddle.top() <= ball.bottom()))
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

#endif 

