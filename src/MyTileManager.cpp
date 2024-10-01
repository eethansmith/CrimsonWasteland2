#include "header.h"

#include "MyTileManager.h"

void MyTileManager::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX, int iMapY,
    int iStartPositionScreenX, int iStartPositionScreenY) const
{
    // Example to draw ovals with colors based on tile map value
    int iMapValue = getMapValue(iMapX, iMapY);
    unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
        + (unsigned int)((iMapValue & 0xf0) << 8) // green
        + (unsigned int)((iMapValue & 0xf) << 4); // blue
    pSurface->drawOval(
        iStartPositionScreenX,
        iStartPositionScreenY,
        iStartPositionScreenX + getTileWidth() - 1,
        iStartPositionScreenY + getTileHeight() - 1,
        iColour);
}

