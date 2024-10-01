#include "header.h"

#include "CrimsonWasteland2TileManager.h"
#include "ImageManager.h"

void CrimsonWasteland2TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	
	switch (getMapValue(iMapX, iMapY))
	{
	case 0: 
		break;
	case 1: 
		exitLeftImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 2: 
		wallImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 3: 
		shelfImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 4: 
		shelfBoxImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1);
		break;
	case 5: 
		shelfSideImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 6: 
		shelfSideBoxImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY, 
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 7: 
		exitRightImage.renderImageWithMask(pSurface,
			0, 0, 
			iStartPositionScreenX, iStartPositionScreenY,
			getTileWidth(), getTileHeight(), 
			-1); 
		break;
	case 8: 
		break;
	}
}
