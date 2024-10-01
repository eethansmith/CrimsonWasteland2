#pragma once

#include "TileManager.h"

class Psyes9TileManager : public TileManager {
public:
    Psyes9TileManager(int tileWidth = 50, int tileHeight = 50, int mapWidth = 10, int mapHeight = 10)
        : TileManager(tileWidth, tileHeight, mapWidth, mapHeight) {
    }

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override {
        
        int iMapValue = getMapValue(iMapX, iMapY);
        unsigned int iColour = 0x90EE90 * ((iMapX + iMapY + iMapValue) % 2);
        pSurface->drawRectangle(
            iStartPositionScreenX,
            iStartPositionScreenY,
            iStartPositionScreenX + getTileWidth() - 1,
            iStartPositionScreenY + getTileHeight() - 1,
            iColour);
    }
};