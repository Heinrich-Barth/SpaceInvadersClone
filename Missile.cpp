/*
 * Missiles.cpp
 *
 *  Created on: May 30, 2023
 */

#include "Missile.h"

Missile::Missile(int x, int y, int maxY, bool isShipMissle)
{
	m_Position.x = x;
	m_Position.w = 5;
	m_Position.h = 10;
	m_nBorderY = maxY;

	if (isShipMissle)
	{
		m_Position.y = y;
		m_nDeltaY = -5;
		timeOffset = 30;
	}
	else
	{
		m_Position.y = y + m_Position.h;
		m_nDeltaY = 5;
		timeOffset = 50;
	}

	timeNextMove = SDL_GetTicks() + timeOffset;
}

Missile::~Missile()
{
}

bool Missile::move(Uint32 currentTime)
{
	if (currentTime < timeNextMove)
		return true;

	if (isVisible())
	{
		m_Position.y += m_nDeltaY;
		timeNextMove = currentTime + timeOffset;
		return true;
	}
	else
		return false;
}

SDL_Rect *Missile::getPosition()
{
	return &m_Position;
}

void Missile::display(SDLApplication *application)
{
	SDL_SetRenderDrawColor(application->getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(application->getRenderer(), &m_Position);
}

bool Missile::isVisible()
{
	if (m_nDeltaY > 0)
		return m_Position.y < m_nBorderY;
	else
		return m_Position.y + m_Position.h > m_nBorderY;
}
