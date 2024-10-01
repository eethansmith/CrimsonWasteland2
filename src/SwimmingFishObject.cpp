#include "header.h"

#include "BaseEngine.h"

#include "SwimmingFishObject.h"

#include "Psyes9TileManager.h"

void SwimmingFishObject::virtDraw()
{
	// Base length of the outer triangle
	int baseLengthOrange = 100;
	// Base length of the inner triangle
	int baseLengthWhite = 50;
	// Height of an equilateral outer triangle
	double heightOrange = (sqrt(3) / 2) * baseLengthOrange;
	// Height of an equilateral inner triangle
	double heightWhite = (sqrt(3) / 2) * baseLengthWhite;

	// Starting point (left bottom vertex) should now use the current position
	int startX = m_iCurrentScreenX;
	int startY = m_iCurrentScreenY;

	// Calculating the vertices based on the current position
	int x1 = startX;
	int y1 = startY;

	int x2O = startX + baseLengthOrange; // 200 units to the right
	int x2W = startX + baseLengthWhite; // 200 units to the right

	int y2O = startY; // Same Y coordinate because it's the base of the triangle
	int y2W = startY; // Same Y coordinate because it's the base of the triangle

	int x3O = startX + (baseLengthOrange / 2); // Middle of the base
	int x3W = startX + (baseLengthWhite / 2); // Middle of the base

	int y3O = static_cast<int>(startY + heightOrange); // Adding height to the Y coordinate
	int y3W = static_cast<int>(startY + heightWhite); // Adding height to the Y coordinate

	getEngine()->drawForegroundTriangle(
		x1, y1,
		x2O, y2O,
		x3O, y3O,
		0xFFA500); // Color: Orange

	getEngine()->drawForegroundTriangle(
		x1, y1,
		x2W, y2W,
		x3W, y3W,
		0xFFFFFF); // Color: White
}

void SwimmingFishObject::virtDoUpdate(int iCurrentTime)
{
	if (getEngine()->isKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 7.5;
	if (getEngine()->isKeyPressed(SDLK_s))
		m_iCurrentScreenY += 7.5;
	if (getEngine()->isKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 7.5;
	if (getEngine()->isKeyPressed(SDLK_d))
		m_iCurrentScreenX += 7.5;
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;

	this->redrawDisplay();
}

int SwimmingFishObject::getX() const {
	return m_iCurrentScreenX;
}

int SwimmingFishObject::getY() const {
	return m_iCurrentScreenY;
}

int SwimmingFishObject::getWidth() const {
	return 100;
}

int SwimmingFishObject::getHeight() const {
	double heightOrange = (sqrt(3) / 2) * 100;
	return static_cast<int>(heightOrange);
}