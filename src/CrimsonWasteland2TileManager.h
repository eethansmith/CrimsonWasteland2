#pragma once

#include "TileManager.h"

class CrimsonWasteland2TileManager :
    public TileManager
{
private: 
    SimpleImage wallImage;
    SimpleImage shelfImage;
    SimpleImage shelfBoxImage;
    SimpleImage shelfSideImage;
    SimpleImage shelfSideBoxImage;
    SimpleImage exitLeftImage;
    SimpleImage exitRightImage;

public:
    CrimsonWasteland2TileManager(void) : TileManager(50, 50)
    {
        wallImage = ImageManager::loadImage("images/Wall.png", true);  
        shelfImage = ImageManager::loadImage("images/Shelves.png", true);
        shelfBoxImage = ImageManager::loadImage("images/ShelvesBox.png", true);
        shelfSideImage = ImageManager::loadImage("images/ShelvesSide.png", true);
        shelfSideBoxImage = ImageManager::loadImage("images/ShelvesSideBox.png", true);
        exitLeftImage = ImageManager::loadImage("images/ExitLeft.png", true);
        exitRightImage = ImageManager::loadImage("images/ExitRight.png", true);
    }

    ~CrimsonWasteland2TileManager(void)
    {
    }

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

    bool isWalkable(int iMapX, int iMapY) const {
        int tileValue = getMapValue(iMapX, iMapY);
        switch (tileValue) {
        case 0:
        case 7:
        case 8:
        case 1:  
            return true; 
        default:
            return false;  
        }
    }
    bool isExitTile(int iMapX, int iMapY) const {
        return getMapValue(iMapX, iMapY) == 1; 
    }

};
