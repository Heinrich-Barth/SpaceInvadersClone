/*
 * Enemies.cpp
 *
 *  Created on: May 27, 2023
 *      Author: oldforrest
 */

#include "Enemies.h"
#include <iostream>

Enemies::Enemies(SDLApplication *pApplication, int enemyRows)
{
	m_pApplication = pApplication;

	for (int i = 0; i < enemyRows; i++)
		enemyLines.push_back(std::make_unique<EnemyEntity>(8));

	m_unStart = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
	m_bMoveRight = true;
	m_unEnemyTimePerAttackLine = 100;

	m_bIsMoving = false;
	m_nPendingDeltaX = 0;
	m_nPendingDeltaY = 0;
}

Enemies::~Enemies()
{
	m_pApplication = nullptr;
}

bool Enemies::load()
{
	m_nOffsetX = 20;
	m_nOffsetY = 20;

	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
		enemy->enemy->load(m_pApplication);

	m_unStart = SDL_GetTicks();
	return true;
}

void Enemies::display()
{
	int nOffsetY = m_nOffsetY;

	const Uint32 milliNow = SDL_GetTicks();
	bool bMovementCompleted = true;
	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
	{
		int posX = m_nOffsetX;
		int posY = nOffsetY;

		if (milliNow > enemy->velocity->timestamp)
		{
			enemy->velocity->incRel();

			posX += enemy->velocity->relX;
			posY += enemy->velocity->relY;
		}
		else
			bMovementCompleted = false;

		enemy->enemy->display(m_pApplication, posX, posY);
		nOffsetY += enemy->enemy->getHeight() + 20;
	}

	if (bMovementCompleted)
		completeMovement();
}

void Enemies::completeMovement()
{
	if (!m_bIsMoving)
		return;

	m_bIsMoving = false;
	m_nOffsetX += m_nPendingDeltaX;
	m_nOffsetY += m_nPendingDeltaY;

	m_nPendingDeltaX = 0;
	m_nPendingDeltaY = 0;
}

bool Enemies::isEmpty()
{
	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
	{
		if (!enemy->enemy->isEmpty())
			return false;
	}

	return true;
}

void Enemies::destroy()
{
	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
		enemy->enemy->destroy();

	enemyLines.clear();
}

bool Enemies::move(int xLeft, int yTop, int xRight, int yBottom)
{
	if (m_bIsMoving || enemyLines.empty())
		return false;

	if (m_nOffsetX < xLeft)
		m_nOffsetX = xLeft + 1;

	if (m_nOffsetY < yTop)
		m_nOffsetY = yTop + 1;

	int posX;
	int rightX = -1;
	int leftX = -1;

	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
	{
		posX = enemy->enemy->getMostRightX();
		if (rightX < posX)
			rightX = posX;

		posX = enemy->enemy->getMostLeftX();
		if (leftX == -1 || posX < leftX)
			leftX = posX;
	}

	int paceY = 20;
	int paceX = 20;
	int deltaX = 0;
	int deltaY = 0;
	if (m_bMoveRight)
	{
		if (rightX + paceX < xRight)
			deltaX = paceX;
		else
			deltaY = paceY;
	}
	else
	{
		if (leftX - paceX > xLeft)
			deltaX -= paceX;
		else
			deltaY = paceY;
	}

	m_nPendingDeltaX = deltaX;
	m_nPendingDeltaY = deltaY;
	m_bIsMoving = true;

	if (deltaY != 0)
		m_bMoveRight = !m_bMoveRight;

	m_unStart = SDL_GetTicks();

	unsigned int size = static_cast<unsigned int>(enemyLines.size());
	unsigned int timeMoveTotal = size * m_unEnemyTimePerAttackLine;

	Uint32 timeBuffer = m_unStart + timeMoveTotal;
	for (const std::unique_ptr<EnemyEntity> &enemy : enemyLines)
	{
		enemy->velocity->set(deltaX, deltaY, timeBuffer - 1);
		timeBuffer -= m_unEnemyTimePerAttackLine;
	}

	return true;
}
