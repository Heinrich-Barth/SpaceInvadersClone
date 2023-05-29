/*
 * Enemies.h
 *
 *  Created on: May 27, 2023
 *      Author: oldforrest
 */

#include "Enemy.h"
#include <vector>
#include <memory>
#include <iostream>

#ifndef ENEMIES_H_
#define ENEMIES_H_

struct Velocity
{
	int x;
	int y;
	int relX;
	int relY;
	Uint32 timestamp;

	Velocity() {
		x = 0;
		y = 0;
		relX = 0;
		relY = 0;
		timestamp = 0;
	}

	void set(int x, int y, Uint32 time)
	{
		this->x = x;
		this->y = y;
		this->relX = 0;
		this->relY = 0;
		this->timestamp = time;
	}

	void incRel()
	{
		if (y != relY)
		{
			if (relY < y)
				relY++;
			else if (relY > y)
				relY--;
		}

		if (relX != x)
		{
			if (relX < x)
				relX++;
			else if (relX > x)
				relX--;
		}
	}
};

struct EnemyEntity
{
	std::unique_ptr<Enemy> enemy;
	std::unique_ptr<Velocity> velocity;

	EnemyEntity(int enemyCount = 8)
	{
		enemy = std::make_unique<Enemy>(enemyCount);
		velocity = std::make_unique<Velocity>();
	}
};


class Enemies {

private:
	std::vector<std::unique_ptr<EnemyEntity>> enemyLines;

	SDLApplication *m_pApplication;

	int m_nOffsetX;
	int m_nOffsetY;
	bool m_bMoveRight;

	Uint32 m_unStart;
	Uint32 m_unEnemyTimePerAttackLine;

	void completeMovement();

	int m_nPendingDeltaX;
	int m_nPendingDeltaY;

	bool m_bIsMoving;

public:
	Enemies(SDLApplication *pApplication, int enemyRows = 5);
	virtual ~Enemies();

	bool load();
	void display();
	void destroy();

	bool isEmpty();
	bool move(int xLeft, int yTop, int xRight, int yBottom);
};

#endif /* ENEMIES_H_ */
