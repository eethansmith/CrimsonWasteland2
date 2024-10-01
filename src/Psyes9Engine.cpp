#include "header.h"

#include "Psyes9Engine.h"

#include "BaseEngine.h"

#include "ImageManager.h"

#include "DisplayableObject.h"

#include "BouncingFishObject.h"

#include "SwimmingFishObject.h"

#include "Psyes9TileManager.h"

int Psyes9Engine::virtInitialise()
{
    // These only need to be called once, so I didn't want to put them in functions which are called multiple times, even though I now need to override this method too
    getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
    getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

    // Call base class version
    return BaseEngine::virtInitialise();
}

void Psyes9Engine::virtSetupBackgroundBuffer()
{
    
    SimpleImage shark1 = ImageManager::loadImage("shark.png", true);
    SimpleImage shark2 = ImageManager::loadImage("shark.png", true);

    // Calculate random positions for sharks, ensuring they fit within screen boundaries
    // For shark1 - positioned randomly within the left half of the screen
    int shark1X = rand() % (getWindowWidth() / 2);
    int shark1Y = rand() % (getWindowHeight());

    // For shark2 - positioned randomly within the right half of the screen
    int shark2X = rand() % (getWindowWidth() / 2 ) + getWindowWidth() / 2;
    int shark2Y = rand() % (getWindowHeight() );

    shark1.renderImage(getBackgroundSurface(), 0, 0, shark1X, shark1Y,
        shark1.getWidth(), shark1.getHeight());
    
    shark2.renderImage(getBackgroundSurface(), 0, 0, shark2X, shark2Y,
        shark2.getWidth(), shark2.getHeight());

    myTileManager.drawAllTiles(this, getBackgroundSurface());

    // Base length of the outer triangle
	int baseLengthOrange = 200;
	// Base length of the inner triangle
	int baseLengthWhite = 100;
	// Height of an equilateral outer triangle
	double heightOrange = (sqrt(3) / 2) * baseLengthOrange;
	// Height of an equilateral inner triangle
	double heightWhite = (sqrt(3) / 2) * baseLengthWhite;

	// Starting point (left bottom vertex) should now use the current position
	int startX = 280;
	int startY = 280;

	int x2O = startX + baseLengthOrange; // 200 units to the right
	int x2W = startX + baseLengthWhite; // 200 units to the right

	int y2O = startY; // Same Y coordinate because it's the base of the triangle
	int y2W = startY; // Same Y coordinate because it's the base of the triangle

	int x3O = startX + (baseLengthOrange / 2); // Middle of the base
	int x3W = startX + (baseLengthWhite / 2); // Middle of the base

	int y3O = static_cast<int>(startY + heightOrange); // Adding height to the Y coordinate
	int y3W = static_cast<int>(startY + heightWhite); // Adding height to the Y coordinate

	drawBackgroundTriangle(
		startX, startY,
		startX + baseLengthOrange, startY,
		startX + (baseLengthOrange / 2), static_cast<int>(startY + heightOrange),
		0xFFA500); // Color: Orange

	drawBackgroundTriangle(
		startX, startY,
		startX + baseLengthWhite, startY,
		startX + (baseLengthWhite / 2), static_cast<int>(startY + heightWhite),
		0xFFFFFF); // Color: White

    char buf[128];
    int orangeColour = 0xFFA500; // Hex code for orange color
    sprintf(buf, "Where's Nemo?");
    drawBackgroundString(550, 350, buf, orangeColour);
}

/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int Psyes9Engine::virtInitialiseObjects()
{
    // Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
    drawableObjectsChanged();

    // Destroy any existing objects
    destroyOldObjects(true);

    // Initially, create array with default size for objects. Assuming you need 3 objects.
    createObjectArray(3);

    // Store the first BouncingObject in the first element of the array
    storeObjectInArray(0, new BouncingFishObject(this));

    // Now, store the SwimmingFishObject in the third element of the array
    storeObjectInArray(1, new SwimmingFishObject(this));

    return 0;
}

/* Draw the string that moving objects should be drawn on top of */
void Psyes9Engine::virtDrawStringsUnderneath()
{
    if (hasCollisionOccurred()) {
        drawForegroundString(550, 375, "NEMO WAS FOUND!!", 0xff0000, NULL);
    }
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void Psyes9Engine::virtDrawStringsOnTop()
{
    // Build the string to print
    char buf[128];
    sprintf(buf, "Since Nemo was last seen: %6d Seconds", rand());
    drawForegroundString(200, 20, buf, 0x00ffff, NULL);

    if (isPaused())
        drawForegroundString(550, 550, "--- MOVIE PAUSED ---", 0xff0000, NULL);
}

void Psyes9Engine::virtMouseDown(int iButton, int iX, int iY)
{
    // Toggle pause state on mouse click
    if (isPaused())
        unpause();
    else
        pause();

}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is currently pressed
*/
void Psyes9Engine::virtKeyDown(int iKeyCode)
{
    switch (iKeyCode)
    {
    case SDLK_ESCAPE: // End program when escape is pressed
        setExitWithCode(0);
        break;
    case SDLK_LEFT:
        m_filterTranslation.changeOffset(10, 0);
        redrawDisplay();
        break;
    case SDLK_RIGHT:
        m_filterTranslation.changeOffset(-10, 0);
        redrawDisplay();
        break;
    case SDLK_UP:
        m_filterTranslation.changeOffset(0, 10);
        redrawDisplay();
        break;
    case SDLK_DOWN:
        m_filterTranslation.changeOffset(0, -10);
        redrawDisplay();
        break;
    case SDLK_SPACE: // Space moves the top left back to the zero coordinates - to be on initial location
        m_filterTranslation.setOffset(0, 0);
        redrawDisplay();
        break;
    }
}