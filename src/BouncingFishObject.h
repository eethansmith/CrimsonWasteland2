#pragma once

#include "BaseEngine.h"

#include "Psyes9Engine.h"

#include "ImageManager.h"

#include "DisplayableObject.h"
#include "SwimmingFishObject.h"


class BouncingFish : public DisplayableObject
{
private:
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;

public:
	BouncingFish(BaseEngine* pEngine, int iWidth = 100, int iHeight = 50, double dXPos = 100, double dYPos = 200, double dXSpeed = 1.5, double dYSpeed = 2.5)
		: DisplayableObject(pEngine, 100, 50, false), m_dX(dXPos), m_dY(dYPos), m_dSX(dXSpeed), m_dSY(dYSpeed)
	{


		setVisible(true);
	}

	void virtDraw() override
	{
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX - m_iDrawWidth / 2 + 1,
			m_iCurrentScreenY - m_iDrawHeight / 2 + 1,
			m_iCurrentScreenX + m_iDrawWidth / 2 - 1,
			m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
			0x000000);
	}

void BouncingFish::virtDoUpdate(int iCurrentTime) {
    if (getEngine()->isPaused())
        return;

    // Assume no collision initially
    bool collisionOccurred = false;

    // Randomly adjust speed and direction
    m_dSX += (rand() % 5 - 2) * 0.4; // Adjust speed by a random value between -0.2 and 0.2
    m_dSY += (rand() % 5 - 2) * 0.2; // Same for Y direction

    m_dX += m_dSX;
    m_dY += m_dSY;

    // Start collision detection after updating the fish's position
    DisplayableObject* pObject;
    for (int iObjectId = 0; (pObject = getEngine()->getDisplayableObject(iObjectId)) != NULL; iObjectId++) {
        if (pObject == this) // Skip checking against itself
            continue;

        SwimmingFishObject* pOtherObject = dynamic_cast<SwimmingFishObject*>(pObject);
        if (pOtherObject != nullptr) {
            if ((m_iCurrentScreenX < pOtherObject->getX() + pOtherObject->getWidth()) &&
                (m_iCurrentScreenX + m_iDrawWidth > pOtherObject->getX()) &&
                (m_iCurrentScreenY < pOtherObject->getY() + pOtherObject->getHeight()) &&
                (m_iCurrentScreenY + m_iDrawHeight > pOtherObject->getY())) {

                // Collision detected
                collisionOccurred = true;

                m_dSX = -m_dSX; // Simple response: reverse X speed
                m_dSY = -m_dSY; // Reverse Y speed
            }
        }
    }

    // Notify the engine about the collision state
    Psyes9Engine* engine = dynamic_cast<Psyes9Engine*>(getEngine());
    if (engine != nullptr) {
        engine->setCollisionOccurred(collisionOccurred);
    }

		m_dX += m_dSX;
		m_dY += m_dSY;

		if ((m_dX + m_iStartDrawPosX) < 0)
		{
			m_dX = -m_iStartDrawPosX;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
			m_dSX += (rand() % 5 - 2) - 1;
		}
		if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (getEngine()->getWindowWidth() - 1))
		{
			m_dX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
			m_dSX += (rand() % 5 - 2) - 1;
		}
		if ((m_dY + m_iStartDrawPosY) < 0)
		{
			m_dY = -m_iStartDrawPosY;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
			m_dSY += (rand() % 5 - 2) - 1;
		}
		if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (getEngine()->getWindowHeight() - 1))
		{
			m_dY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
			m_dSY += (rand() % 5 - 2) - 1;
		}

		m_iCurrentScreenX = (int)(m_dX);
		m_iCurrentScreenY = (int)(m_dY);


		redrawDisplay();
	}
};


class FishPicture : public DisplayableObject
{
public:
	FishPicture(BaseEngine* pEngine, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(pEngine, 100, 100, useTopLeftFor00),
		image(pEngine->loadImage("fish.png", false))
	{
		this->m_iDrawWidth = image.getWidth();
		this->m_iDrawHeight = image.getHeight();
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(true);
	}

	FishPicture(int xStart, int yStart, BaseEngine* pEngine, bool useTopLeftFor00 = true, bool bVisible = true)
		: DisplayableObject(xStart, yStart, pEngine, 100, 100, useTopLeftFor00),
		image(ImageManager::get()->getImagebyURL("fish.png", true, false))
	{
		m_iDrawWidth = image.getWidth();
		m_iDrawHeight = image.getHeight();
		m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
		m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
		setVisible(bVisible);
	}

	virtual void virtDraw() override
	{
		if (isVisible())
		{
			image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}
	}

private:
	SimpleImage image;
};


class BouncingFishObject : public BouncingFish
{
public:

	BouncingFishObject(BaseEngine* pEngine)
		: BouncingFish(pEngine)
		, image(pEngine->loadImage("fish.png", false))
	{
	}

	virtual void virtDraw() override
	{
		if (isVisible())
		{
			image.renderImageWithMask(getEngine()->getForegroundSurface(), 35, 50, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}

private:
	SimpleImage image;
};