#pragma once

#include "util.h"

class Collide
{
public:
	virtual Rect getCollisionHull() const = 0;
};

class GameObj 
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
