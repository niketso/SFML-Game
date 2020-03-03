#ifndef BRICK_H
#define BRICK_H
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

constexpr float brickWidth(60.0f), brickHeight(20.0f);
constexpr int bricksOnX(12.0f), bricksOnY(5.0f);

struct Brick
{
	RectangleShape shape;
	bool isDestroyed = false;
	Brick(float startPosX, float startPosY)
	{
		shape.setPosition(startPosX, startPosY);
		shape.setSize({ brickWidth,brickHeight });
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

void BrickCollision(Brick& brick, Ball& ball)
{

	if (!(brick.right() >= ball.left() && brick.left() <= ball.right() &&
		brick.bottom() >= ball.top() && brick.top() <= ball.bottom()))
	{
		return;
	}

	brick.isDestroyed = true;

	float overlapLeft{ ball.right() - brick.left() };
	float overlapRight{ brick.right() - ball.left() };
	float overlapTop{ ball.bottom() - brick.top() };
	float overlapBottom{ brick.bottom() - ball.top() };

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
#endif