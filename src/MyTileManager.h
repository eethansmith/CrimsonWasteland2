#pragma once

#include "TileManager.h" // Ensure this path is correct based on your project structure

class MyTileManager : public TileManager {
public:
    // Constructor
    MyTileManager() : TileManager(20, 20, 15, 15) {}

    // Override virtDrawTileAt
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;
};
