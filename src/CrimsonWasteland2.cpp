#include "header.h"

#include "BaseEngine.h"

#include "CrimsonWasteland2.h"

#include "ImageManager.h"

#include "CrimsonWasteland2MenuObjects.h"

#include "CrimsonWasteland2GameObjects.h"

#include "CrimsonWasteland2TileManager.h"


CrimsonWasteland2TileManager m_oTiles;

CrimsonWasteland2::CrimsonWasteland2(void)
	: m_state(stateMenuStartUp),
	m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling),
	rotator(0.0),
	shifter1(0, 0),
	shifter2(0, 0),
	currentOffsetX(0),
	scrolledOut(0),
	userWantsToType(false),
	m_warehouse(0),
	rat(false),
	level2Complete(false),
	zombie1X(rand() % 800), zombie1Y(rand() % 200), 
	zombie2X(rand() % 800 + 200), zombie2Y(rand() % 200 + 400), 
	zombie3X(1200), zombie3Y(300),
	playerLives(3),
	difficulty( "NORMAL" )
{
}

CrimsonWasteland2::~CrimsonWasteland2(void)
{
}

int CrimsonWasteland2::virtInitialise()
{
		getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);

		return BaseEngine::virtInitialise();

}

int getTextWidth(const std::string& text) {
	return static_cast<int>(text.length() * 10);  
}

void CrimsonWasteland2::virtSetupBackgroundBuffer()
{
	SimpleImage background; 

	switch (m_state) {
	case stateMenuStartUp:
		m_iOffset = 0;
		fillBackground(0);
		background = ImageManager::loadImage("images/startupscreen.png", true);
		background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
		name[0] = '\0';
		break;

	case stateMenuRunning:
		m_iOffset = 0;
		level2Complete = false;
		fillBackground(0);
		background = ImageManager::loadImage("images/background2.png", true);
		background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
		break;

	case stateGamePause:
		fillBackground(0);
		break;

	case stateGameIntro:
		m_iOffset = 0;
		fillBackground(0xffffff);
		background = ImageManager::loadImage("images/ComicEntry.png", true);
		background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
		redrawDisplay();
		break;

	case stateGameStartUp:
		m_iOffset = 0;
		fillBackground(0);
		{
			{

				m_oTiles.setMapSize(26, 16);
				m_oTiles.setTopLeftPositionOnScreen(0, 0);
				const char* data[] = {
					"cccccccccccccccccccccccccc",
					"cffggceaafgfaaaaaaaaaaaaec",
					"caaaacdaaaaaaaaaaaaaaaaaec",
					"caaaaceaaaaaaacaaccccccccc",
					"cffaacdaaaaaaacaaaaaaaaaab",
					"cccaaccaaaagfgcaaaaaaaaaah",
					"caaaadcaaacccccccccccccccc",
					"caaaaecaaaaaaaaaaaaaaaaaec",
					"caaaadcaaaaaaaaaaaaaaaaaec",
					"caaccccccccccccccdaaaaaadc",
					"caaceaaaaaaaaaaeceaaaaaaec",
					"caaceaaaaaaaaaaecccaaacccc",
					"caaceaaaaaadcaaaaaaaaaaadc",
					"caaaaaaaaaadcaaaaaaaaaaaec",
					"caaaaaaaaaadcfggffgfaaaadc",
					"cccccccccccccccccccccccccc"
				};

				for (int y = 0; y < 16; y++) {
					for (int x = 0; x < 26; x++) {
						m_oTiles.setMapValue(x, y, data[y][x] - 'a');
					}
				}
			}
			bool ratAppears = false;
		}
		return;

	case stateGameRunning:
	{
		SimpleImage background;

		switch (m_warehouse) {
		case 0: background = ImageManager::loadImage("images/ratAnimation/rat1.png", true); break;
		case 1:  background = ImageManager::loadImage("images/ratAnimation/rat2.png", true); break;
		case 2:  background = ImageManager::loadImage("images/ratAnimation/rat3.png", true); break;
		case 3:  background = ImageManager::loadImage("images/ratAnimation/rat4.png", true); break;
		case 4:  background = ImageManager::loadImage("images/ratAnimation/rat5.png", true); break;
		case 5:  background = ImageManager::loadImage("images/ratAnimation/rat6.png", true); break;
		case 6:  background = ImageManager::loadImage("images/ratAnimation/rat7.png", true); break;
		case 7:  background = ImageManager::loadImage("images/ratAnimation/rat8.png", true); break;
		case 8:  background = ImageManager::loadImage("images/ratAnimation/rat9.png", true); break;
		case 9:  background = ImageManager::loadImage("images/ratAnimation/rat10.png", true); break;
		case 10:  background = ImageManager::loadImage("images/ratAnimation/rat11.png", true); break;
		case 11:  background = ImageManager::loadImage("images/ratAnimation/rat12.png", true); break;
		case 12:  background = ImageManager::loadImage("images/ratAnimation/rat13.png", true); break;
		case 13:  background = ImageManager::loadImage("images/ratAnimation/rat14.png", true); break;
		case 14:  background = ImageManager::loadImage("images/ratAnimation/rat15.png", true); break;
		case 15:  background = ImageManager::loadImage("images/ratAnimation/rat16.png", true); break;
		case 16:  background = ImageManager::loadImage("images/ratAnimation/rat17.png", true); break;
		case 17:  background = ImageManager::loadImage("images/ratAnimation/rat18.png", true); break;
		case 18:  background = ImageManager::loadImage("images/ratAnimation/rat19.png", true); break;
		case 19:  background = ImageManager::loadImage("images/ratAnimation/rat20.png", true); break;
		case 20:  background = ImageManager::loadImage("images/ratAnimation/rat21.png", true); break;
		case 21:  background = ImageManager::loadImage("images/ratAnimation/rat22.png", true); break;
		case 22:  background = ImageManager::loadImage("images/ratAnimation/rat23.png", true); break;
		}

		background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
		redrawDisplay();

		m_iOffset = 0;
		m_oTiles.drawAllTiles(this, this->getBackgroundSurface());

		setAllObjectsVisible(true);
	}
		break;


	case stateGameWon:
		m_iOffset = 0;
		fillBackground(0xFFFFF);
		{
			background = ImageManager::loadImage("images/WonGame.png", true);
			background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());

		}
		break;
	case stateLevelWon:
		m_iOffset = 0;
		fillBackground(0xFFFFF);
		{
			background = ImageManager::loadImage("images/WonGame.png", true);
			background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());

		}
		break;
	case stateGameLevel2StartUp:
		m_iOffset = 0;
		fillBackground(0);
		{
			{

				m_oTiles.setMapSize(26, 16);
				m_oTiles.setTopLeftPositionOnScreen(0, 0);
				const char* data[] = {
					"cccccccccccccccccccccccccc",
					"caaaaacaaaaaaaaaaaaaaaaaac",
					"caaaaaaaaaaaaaaaaaaaaaaaac",
					"caaaaacaaaaaaaaaaaccccaaac",
					"caaaaacaaaaaacccccaaaaaaac",
					"caaacccaaaaaacaaaaaaaaaaac",
					"caaaaaaaaaaaacaaaaaaaaaaac",
					"caaaaaaaacccccaaaaaacaaaac",
					"caaaaaaaacaaaaaaaaaacaaaac",
					"caaaaaaaacccaaaaaaaacccacc",
					"ccaccccacaacccaaaaaaaaaaab",
					"aaaaaaaaaaaaacaaaaaaaaaaah",
					"aaaaaaaaaaaaaacccacccccccc",
					"aaaaaaaaaaaaaaaaaaaaaaaaaa",
					"aaacccccaaaaaaaaaaaaaaaaaa",
					"aaaaaaaaaaaaaaaaaaaaaaaaaa"
				};

				for (int y = 0; y < 16; y++) {
					for (int x = 0; x < 26; x++) {
						m_oTiles.setMapValue(x, y, data[y][x] - 'a');
					}
				}
			}
			bool ratAppears = false;
		}
		return;

	case stateGameLevel2:
	{

		background = ImageManager::loadImage("images/desert.png", true);
		background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
		redrawDisplay();

		m_iOffset = 0;
		m_oTiles.drawAllTiles(this, this->getBackgroundSurface());

		setAllObjectsVisible(true);
	}
	break;


	case stateGameLost:
		m_iOffset = 0;
		fillBackground(0xFFF);
		{
			background = ImageManager::loadImage("images/LostGame.png", true);
			background.renderImage(getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());

		}
		break;
	} 
}

void CrimsonWasteland2::virtMainLoopDoBeforeUpdate()
{
	long currentTime = getRawTime();

	if (m_state == stateMenuRunning)
	{
		m_iOffset = (m_iOffset + 3) % getWindowHeight();
		int iOffset = getModifiedTime() / 10;

		shifter2.setYShift((double)iOffset / 1.0);

		this->redrawDisplay();
	}
	if (m_state == stateGameRunning && rat)
	{
		if (currentTime - ratTime < 805)
		{
			int frameDuration = 35; 
			int elapsedTimeSinceLastShot = currentTime - ratTime;
			int frame = (elapsedTimeSinceLastShot / frameDuration) % 23;
			m_warehouse = frame;

			if (frame % 1 == 0) 
			{
				lockAndSetupBackground();
			}
			if (frame == 16) {
				ratTime - 35;
			}
		}
		else
		{
			m_warehouse = 0;
			rat = false;
			lockAndSetupBackground();
		}
	}
}


void CrimsonWasteland2::copyAllBackgroundBuffer()
{
	m_pForegroundSurface->copyRectangleFrom(
		m_pBackgroundSurface, 0, 0, getWindowWidth(),
		getWindowHeight(), 0, m_iOffset);

	m_pForegroundSurface->copyRectangleFrom(
		m_pBackgroundSurface, 0,
		getWindowHeight() - m_iOffset, getWindowWidth(),
		getWindowHeight(), 0, m_iOffset - getWindowHeight());
}

int CrimsonWasteland2::virtInitialiseObjects()
{
	switch (m_state)
	{
	case stateMenuStartUp:
		clip = 4;
		playerLives = 2;
		drawableObjectsChanged();

		destroyOldObjects(true);

		createObjectArray(1);
		storeObjectInArray(0, new ImageObject(this, "images/CW2Logo.png", 0, 130, true));
	}
	return 0;
}

void CrimsonWasteland2::virtDrawStringsOnTop()
{
	switch (m_state)
	{
		destroyOldObjects(true);
	case stateMenuRunning:
	{
		SimpleImage zombie1 = ImageManager::loadImage("images/zombie.png", true);
		zombie1.renderImageWithMask(getBackgroundSurface(), 0, 0, zombie1X, zombie1Y,
			zombie1.getWidth(), zombie1.getHeight());

		SimpleImage zombie2 = ImageManager::loadImage("images/zombie.png", true);
		zombie2.renderImageWithMask(getBackgroundSurface(), 0, 0, zombie2X, zombie2Y,
			zombie2.getWidth(), zombie2.getHeight());

		SimpleImage zombie3 = ImageManager::loadImage("images/zombie.png", true);
		zombie3.renderImageWithMask(getBackgroundSurface(), 0, 0, zombie3X, zombie3Y,
			zombie3.getWidth(), zombie3.getHeight());

		drawableObjectsChanged();

		destroyOldObjects(true);

		createObjectArray(3);
		storeObjectInArray(0, new ImageObject(this, "images/CW2Logo.png", 240, 75, true));
		storeObjectInArray(1, new ClickableImageObject(this, "images/SpaceStart.png", 480, 610, true));
		storeObjectInArray(2, new TextBoxObject(this, 580, 505));

		if (!userWantsToType && nameLength == 0) {
			drawForegroundString(580 + 7, 505 + 12, "ENTER NAME", 0xD0D0D0, NULL);
		}
		else if (userWantsToType && nameLength == 0) {

		}
		else {
			drawForegroundString(650, 517, name, 0x000000, NULL);
		}
	}
	break;
	case stateGameIntro:

		destroyOldObjects(true);
		lockAndSetupBackground();
		redrawDisplay();

		break;

	case stateGameStartUp:
	{

		drawableObjectsChanged();

		destroyOldObjects(true);

		createObjectArray(100);
		Player* player = new Player(this, 75, 110, true);
		storeObjectInArray(1, player);

		storeObjectInArray(2, new Zombie(this, player, 500, 510, true));

		storeObjectInArray(3, new Zombie(this, player, 780, 120, true));

		storeObjectInArray(4, new Zombie(this, player, 500, 175, true));

		storeObjectInArray(5, new Lives(this, this, playerLives));

		setAllObjectsVisible(false);

		break;
	}


	case stateGameWon:
		setAllObjectsVisible(false);
		lockAndSetupBackground();
		redrawDisplay();
		break;

	case stateLevelWon:
		setAllObjectsVisible(false);
		lockAndSetupBackground();
		redrawDisplay();
		break;

	case stateGameLevel2StartUp:
	{

		drawableObjectsChanged();

		destroyOldObjects(true);

		createObjectArray(100);
		Player* player = new Player(this, 75, 110, true);
		storeObjectInArray(1, player);

		storeObjectInArray(2, new Zombie(this, player, 800, 510, true));

		storeObjectInArray(3, new Zombie(this, player, 1100, 100, true));

		storeObjectInArray(4, new Zombie(this, player, 500, 600, true));

		storeObjectInArray(5, new Lives(this, this, playerLives));

		setAllObjectsVisible(false);

		break;
	}

	case stateGameLost:
		setAllObjectsVisible(false);
		lockAndSetupBackground();
		redrawDisplay();
		break;
	}
}


void CrimsonWasteland2::virtDrawStringsUnderneath()
{
	switch (m_state)
	{
	case stateMenuStartUp:
		drawForegroundString(230, 500, "PRESS 'SPACE' KEY", 0xF7D100, NULL);
		break;
	case stateMenuRunning:
		drawForegroundString(250, 10, "Running", 0xffffff, NULL);
		drawForegroundString(585, 440, "<           >", 0xffffff, NULL);
		{
			std::string text = " " + difficulty + " ";
			int textWidth = getTextWidth(text);
			int textX = 650 - textWidth / 2;
			drawForegroundString(textX, 440, text.c_str(), 0xffffff, NULL);
		}
		break;
	case stateGamePause:
		drawForegroundString(200, 300, "Paused. Press SPACE to continue", 0xffffff, NULL);
		break;
	case stateGameIntro:
		drawForegroundString(1017, 47, "'SPACE' TO SKIP", 0x000000, NULL);
		drawForegroundString(1023, 53, "'SPACE' TO SKIP", 0x000000, NULL);
		drawForegroundString(1020, 50, "'SPACE' TO SKIP", 0xF7D100, NULL);
		{
			int score = 0;
		}
		break;
	case stateGameStartUp:
		drawForegroundString(450, 500, "PRESS 'SPACE' KEY TO START", 0xF7D100, NULL);
		break;

	case stateGameRunning:
	{	
		int score = (BaseEngine::getModifiedTime() / 50);
		char buf[1024];
		sprintf(buf, "Score: %d", score);
		drawForegroundString(998, 24, buf, 0x000000, NULL);
		drawForegroundString(1002, 27, buf, 0x000000, NULL);
		drawForegroundString(1000, 25, buf, 0xF7D100, NULL);
		level2Complete = true;
	}

		break;
		
	case stateGameWon:
		break;
	case stateGameLevel2StartUp:
		drawForegroundString(450, 500, "PRESS 'SPACE' KEY TO START", 0xF7D100, NULL);
		break;

	case stateGameLevel2:
	{
		int score = (BaseEngine::getModifiedTime() / 50);
		char buf[1024];
		sprintf(buf, "Score: %d", score);
		drawForegroundString(998, 24, buf, 0x000000, NULL);
		drawForegroundString(1002, 27, buf, 0x000000, NULL);
		drawForegroundString(1000, 25, buf, 0xF7D100, NULL);
		level2Complete = false;
	}

	break;

	case stateGameLost:
		break;
	}
}


void CrimsonWasteland2::virtMouseDown(int iButton, int iX, int iY) {
	if (m_state == stateMenuRunning) {
		std::string text = "<  " + difficulty + "  >";
		int textWidth = getTextWidth(text);
		int textX = 650 - textWidth / 2;
		int textY = 440; 
		int textHeight = 30; 

		int startWidthHeight = 175;
		int startX = 585;
		int startY = 570;
		if (iButton == SDL_BUTTON_LEFT) {
			if (iX >= textX - 20 && iX <= (textX + textWidth + 75) && iY >= textY && iY <= (textY + textHeight)) {
				std::vector<std::string> difficulties = { "EASY", "NORMAL", "HARD" };
				auto it = std::find(difficulties.begin(), difficulties.end(), difficulty);
				if (it != difficulties.end() && ++it != difficulties.end()) {
					difficulty = *it;
				}
				else {
					difficulty = difficulties.front();
				}

				redrawDisplay();
			}
			if (iX >= 573 && iX <= 787 && iY >= 498 && iY <= 562) {
				userWantsToType = true;
			}
			else {
				userWantsToType = false;
			}
		}
	}
}

void CrimsonWasteland2::virtMouseWheel(int x, int y, int which, int timestamp)
{
	if (m_state == stateGameIntro) {
		int iOldCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iOldCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		if (y < 0) {
			if (scrolledOut < 0) {
				m_filterScaling.compress();
				++scrolledOut;
			}
		}else if (y > 0) {
			if (scrolledOut <= 0) {
				m_filterScaling.stretch();
				--scrolledOut;
			}
		}

		int iNewCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iNewCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		redrawDisplay(); 
	}
}

void CrimsonWasteland2::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE:
		if (m_state == stateGameRunning) {
		m_state = stateGamePause;
		this->pause();
		setAllObjectsVisible(false);
		lockAndSetupBackground();
		redrawDisplay();
		break;
		}
		else {
			setExitWithCode(0);
		}
		break;

	case SDLK_SPACE:
		switch (m_state)
		{
		case stateMenuStartUp:
			m_state = stateMenuRunning;
			lockAndSetupBackground();
			setAllObjectsVisible(true);
			destroyOldObjects(true);
			redrawDisplay();
			break;

		case stateMenuRunning:
			m_state = stateGameIntro;
			setAllObjectsVisible(false);
			lockAndSetupBackground();
			redrawDisplay();

			if (difficulty == "EASY") {
				playerLives = 3;
			}
			else if (difficulty == "NORMAL") {
				playerLives = 2;
			}
			else if (difficulty == "HARD") {
				playerLives = 1;
			}
			break;

		case stateGameIntro:
			m_state = stateGameStartUp;
			virtInitialise();
			m_filterTranslation.setOffset(0, 0);
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateGameStartUp:
			m_state = stateGameRunning;
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateGamePause:
			m_state = stateGameRunning;
			this->unpause();
			setAllObjectsVisible(true);
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateLevelWon:
			zombieCollide(false);
			reachedExit(false);
			m_state = stateMenuRunning;
			setAllObjectsVisible(true);
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateGameWon:
			zombieCollide(false);
			reachedExit(false);
			if (level2Complete) {
				m_state = stateGameLevel2StartUp;
			}
			else {
				stateMenuRunning;
			}
			setAllObjectsVisible(true);
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateGameLevel2StartUp:
			m_state = stateGameLevel2;
			lockAndSetupBackground();
			redrawDisplay();
			break;

		case stateGameLost:
			destroyOldObjects(true);
			zombieCollide(false);
			reachedExit(false);
			m_state = stateMenuRunning;
			setAllObjectsVisible(true);
			lockAndSetupBackground();
			redrawDisplay();
			break;
		}

	case SDLK_LEFT:
		if (m_state == stateGameIntro) {
			virtInitialise();
			if (currentOffsetX < 5000 - 1300) {
				int newOffset = currentOffsetX + 100;
				if (newOffset > 5000 - 1300) newOffset = 5000 - 13000;
				m_filterTranslation.changeOffset(-100, 0);
				currentOffsetX = newOffset;
			}
			redrawDisplay();
		}
		break;

	case SDLK_RIGHT:
		if (m_state == stateGameIntro) {
			virtInitialise();
			if (currentOffsetX > 0) {
				int newOffset = currentOffsetX - 100;
				if (newOffset < 0) newOffset = 0;
				m_filterTranslation.changeOffset(100, 0);
				currentOffsetX = newOffset;
			}
			redrawDisplay();
		}
		break;
	case SDLK_p:
	{
		rat = true;
		ratTime = getRawTime();
	}
		break;
	}

	if (userWantsToType) {
		if (iKeyCode == SDLK_BACKSPACE) {
			if (nameLength > 0) {
				nameLength--;
				name[nameLength] = '\0';
			}
		}
		else if (iKeyCode >= SDLK_a && iKeyCode <= SDLK_z) {
			if (nameLength < 4) {
				char key = static_cast<char>(iKeyCode);
				name[nameLength] = key;
				nameLength++;
				name[nameLength] = '\0';
			}
		}
	}

}