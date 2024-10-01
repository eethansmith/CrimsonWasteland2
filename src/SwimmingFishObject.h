#pragma once
#include "DisplayableObject.h"
class SwimmingFishObject :
    public DisplayableObject
{
public:
	SwimmingFishObject(BaseEngine* pEngine)
		: DisplayableObject(pEngine)
	{
		m_iCurrentScreenX = 500; // Starting position on the screen
		m_iCurrentScreenY = 500;
		m_iDrawWidth = 100; // Width of drawing area
		m_iDrawHeight = 100; // Height of drawing area
	}
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
};