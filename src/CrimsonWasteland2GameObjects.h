#pragma once

#include "header.h"
#include "DisplayableObject.h"
#include "ImageManager.h"
#include "BaseEngine.h"
#include "CrimsonWasteland2.h"
#include "UtilMovementPosition.h" 


#include "SimpleImage.h"
#include "ImagePixelMapping.h"
#include "ImageManager.h"


class CrimsonWasteland2GameObjects :
    public DisplayableObject
{
};

class Lives : public DisplayableObject {
public:
    enum Difficulty {
        DifficultyEasy,
        DifficultyMedium,
        DifficultyHard
    };


    Lives(BaseEngine* pEngine, CrimsonWasteland2* gameInstance, int totalLives)
        : DisplayableObject(pEngine, 75, 75),
        m_gameInstance(gameInstance),
        m_totalLives(totalLives),
        m_livesRemaining(totalLives) {
        m_iCurrentScreenX = 25;
        m_iCurrentScreenY = 25;
        setVisible(true);
        LifeFull = ImageManager::get()->getImagebyURL("images/+Life.png", true, true);
        LifeLost = ImageManager::get()->getImagebyURL("images/-Life.png", true, true);
    }

    virtual void virtDraw() override {
        if (!isVisible() || getEngine()->isPaused()) return;

        int currentLives = m_gameInstance->getPlayerLives();

        int lifeX = m_iCurrentScreenX; 
        for (int i = 0; i < m_totalLives; ++i) {
            SimpleImage img = (i < currentLives) ? LifeFull : LifeLost;
            img.renderImageWithMask(getEngine()->getForegroundSurface(),
                0, 0,
                lifeX, m_iCurrentScreenY, 
                m_iDrawWidth, m_iDrawHeight, 
                0xFFFFFF); 
            lifeX += 90; 
        }
    }


    virtual void virtDoUpdate(int iCurrentTime) override {
    };

private:
    int m_totalLives;
    int m_livesRemaining;
    CrimsonWasteland2* m_gameInstance;
    SimpleImage LifeFull;
    SimpleImage LifeLost;
};

class Bullet : public DisplayableObject {
public:
    int speed; 
    int lastUpdateTime;
    std::string direction;

    Bullet(BaseEngine* pEngine, int x, int y, std::string direction)
        : DisplayableObject(pEngine, x, y),
        speed(5),
        lastUpdateTime(0),
        direction(direction)
    {
        this->m_iCurrentScreenX = x + 16;
        this->m_iCurrentScreenY = y + 78;
        direction;
        setVisible(true);
    }

    virtual void virtDraw() override {

        int ovalWidth = 7;  
        int ovalHeight = 7; 

        int left = m_iCurrentScreenX - ovalWidth / 2;
        int top = m_iCurrentScreenY - ovalHeight / 2;
        int right = m_iCurrentScreenX + ovalWidth / 2;
        int bottom = m_iCurrentScreenY + ovalHeight / 2;

        getEngine()->drawForegroundOval(
            left, top,
            right, bottom,
            0x000000);

    }

    virtual void virtDoUpdate(int iCurrentTime) override {

        int elapsedTime = iCurrentTime - lastUpdateTime;
        if (elapsedTime < 1) { 
            return;
        }
        lastUpdateTime = iCurrentTime;

        int newX = m_iCurrentScreenX;
        int newY = m_iCurrentScreenY;

        if (direction == "down") {newY += speed;}
        else if (direction == "left") {newX -= speed;}
        else if (direction == "up") {newY -= speed;}
        else if (direction == "right") {newX += speed;}

        if (canMoveTo(newX, newY)) {
            m_iCurrentScreenX = newX;
            m_iCurrentScreenY = newY;
        }
        else {
            setVisible(false);
            getEngine()->removeDisplayableObject(this);
        }
    }
private:
    CrimsonWasteland2* m_pMainEngine;

    bool canMoveTo(int newX, int newY) {
        int tileX = newX / 50;
        int tileY = newY / 50;
        CrimsonWasteland2TileManager& tileManager = static_cast<CrimsonWasteland2*>(getEngine())->GetTileManager();
        return tileManager.isWalkable(tileX, tileY);
    }
};

class Player : public DisplayableObject {
public:
    double rotationAngle;
    int bulletOffsetX = 0;
    int bulletOffsetY = 0;
    int speed; 
    int clip;
    int lastFireTime; 
    const int fireDelay = 100;
    bool shotFired = false;
    int lives = 1;
    int difficulty = 0;
    MovementPosition m_oMover; 
    int getCurrentScreenX() const { return m_iCurrentScreenX; }
    int getCurrentScreenY() const { return m_iCurrentScreenY; }
    bool isShotFired() const { return shotFired; }
    void resetLocation() { 
        m_iCurrentScreenX = 75;
        m_iCurrentScreenY = 110;
    }
    std::string direction;
    int bulletCount;

    enum ShootingState {
        notShoot,
        shoot1,
        shoot2,
        shoot3,
        shoot4,
        shoot5
    };

    ShootingState shooting = notShoot;

    Player(BaseEngine* pEngine, int x, int y, bool useTopLeftFor00 = true)
        : DisplayableObject(pEngine, x, y, useTopLeftFor00),
        rotationAngle(0.0), speed(3), direction("right"),
        clip(10),
        m_oMover() { 
        this->m_iCurrentScreenX = x;
        this->m_iCurrentScreenY = y;
        setVisible(true);
    }

    virtual void virtDraw() override {
        if (!isVisible() || getEngine()->isPaused()) return;

        SimpleImage player;
        switch (shooting) {
        case notShoot: player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player.png", true, true); break;
        case shoot1:   player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player1.png", true, true); break;
        case shoot2:   player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player2.png", true, true); break;
        case shoot3:   player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player3.png", true, true); break;
        case shoot4:   player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player4.png", true, true); break;
        case shoot5:   player = ImageManager::get()->getImagebyURL("images/playerAnimation/Player5.png", true, true); break;
        }

        double rotationAngle = 0.0; 

        if (direction == "down") {
            rotationAngle = 0.0;
            bulletOffsetX = 0;
            bulletOffsetY = 2;
        }
        else if (direction == "left") {
            rotationAngle = 3 * M_PI / 2;
            bulletOffsetX = -17;
            bulletOffsetY = -54;
        }
        else if (direction == "up") {
            rotationAngle = M_PI;
            bulletOffsetX =  37;
            bulletOffsetY = -71;
        }
        else if (direction == "right") {
            rotationAngle = M_PI / 2;
            bulletOffsetX = 55;
            bulletOffsetY = -16; 
        }

        ImagePixelMappingRotate mapping1(rotationAngle);

        player.renderImageApplyingMapping(
            getEngine(),
            getEngine()->getForegroundSurface(),
            m_iCurrentScreenX, m_iCurrentScreenY,
            player.getWidth(), player.getHeight(),
            &mapping1);
    }


    virtual void virtDoUpdate(int iCurrentTime) override {
        int newX = m_iCurrentScreenX, newY = m_iCurrentScreenY;
        handleShooting(iCurrentTime);

        if (iCurrentTime - lastFireTime < 500) {
            int frameDuration = 100; 
            int elapsedTimeSinceLastShot = iCurrentTime - lastFireTime;
            int frame = (elapsedTimeSinceLastShot / frameDuration) % 5;
            switch (frame) {
            case 0: shooting = shoot1; break;
            case 1: shooting = shoot2; break;
            case 2: shooting = shoot3; break;
            case 3: shooting = shoot4; break;
            case 4: shooting = shoot5; break;
            case 5: shooting = notShoot; break;
            }
        }
        else {
            shooting = notShoot;
        }

        int deltaX = (getEngine()->isKeyPressed(SDLK_RIGHT) - getEngine()->isKeyPressed(SDLK_LEFT)) * speed;
        if (deltaX > 0) {
            direction = "right";
        }
        else if (deltaX < 0) {
            direction = "left";
        }

        int proposedNewX = m_iCurrentScreenX + deltaX;
        if (deltaX != 0 && canMoveTo(proposedNewX, m_iCurrentScreenY)) {
            m_iCurrentScreenX = proposedNewX;
        }

        int deltaY = (getEngine()->isKeyPressed(SDLK_DOWN) - getEngine()->isKeyPressed(SDLK_UP)) * speed;
        if (deltaY > 0) {
            direction = "down";
        }
        else if (deltaY < 0) {
            direction = "up";
        }

        int proposedNewY = m_iCurrentScreenY + deltaY;
        if (deltaY != 0 && canMoveTo(m_iCurrentScreenX, proposedNewY)) {
            m_iCurrentScreenY = proposedNewY;
        }

        m_iCurrentScreenX = std::max(0, std::min(m_iCurrentScreenX, getEngine()->getWindowWidth() - m_iDrawWidth));
        m_iCurrentScreenY = std::max(0, std::min(m_iCurrentScreenY, getEngine()->getWindowHeight() - m_iDrawHeight));

        m_oMover.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX, m_iCurrentScreenY, iCurrentTime, iCurrentTime);
        m_oMover.calculate(iCurrentTime);

        getEngine()->redrawDisplay();
    }

    void handleShooting(int iCurrentTime) {
    if (iCurrentTime - lastFireTime > 5000) {
        shotFired = false;
    } 

    if (getEngine()->isKeyPressed(SDLK_SPACE)) {
        if (iCurrentTime - lastFireTime >= 500) {
            shooting = shoot1;

            int bulletStartX = m_iCurrentScreenX + bulletOffsetX;
            int bulletStartY = m_iCurrentScreenY + bulletOffsetY;

            Bullet* newBullet = new Bullet(getEngine(), bulletStartX, bulletStartY, direction);
            getEngine()->storeObjectInArray(clip, newBullet);
            clip = (clip >= 20) ? 10 : clip + 1;

            lastFireTime = iCurrentTime;  
            shotFired = true;        
        }
    }
}


    bool canMoveTo(int x, int y) {
        int playerSide = 78;
  
        int topLeftX = x / 50;
        int topLeftY = y / 50;
        int topRightX = (x + playerSide) / 50;
        int topRightY = y / 50;
        int bottomLeftX = x / 50;
        int bottomLeftY = (y + playerSide) / 50;
        int bottomRightX = (x + playerSide) / 50;
        int bottomRightY = (y + playerSide) / 50;

        if (getTileManager().isExitTile(bottomRightX, bottomRightY) || getTileManager().isExitTile(topRightX, topRightY)) {
            dynamic_cast<CrimsonWasteland2*>(getEngine())->reachedExit(true);
        }

        return getTileManager().isWalkable(topLeftX, topLeftY) &&
            getTileManager().isWalkable(topRightX, topRightY) &&
            getTileManager().isWalkable(bottomLeftX, bottomLeftY) &&
            getTileManager().isWalkable(bottomRightX, bottomRightY);
    }

    CrimsonWasteland2TileManager& getTileManager() {
        return static_cast<CrimsonWasteland2*>(getEngine())->GetTileManager();
    }


private:
    CrimsonWasteland2* m_pMainEngine;
};


class Zombie : public DisplayableObject {
public:
    int speed; 
    MovementPosition m_oMover; 
    Player* m_pPlayer;
    int lastUpdateTime;
    int currentDirection; 
    int stepsTaken; 

    Zombie(BaseEngine* pEngine, Player* player, int x, int y, bool useTopLeftFor00 = true)
        : DisplayableObject(pEngine, x, y, useTopLeftFor00),
        speed(5),
        m_oMover(),
        m_pPlayer(player),
        lastUpdateTime(0),
        currentDirection(-1),
        stepsTaken(0)
        { 
        this->m_iCurrentScreenX = x;
        this->m_iCurrentScreenY = y;
        setVisible(true);
    }

    virtual void virtDraw() override {
        if (!isVisible() || getEngine()->isPaused()) return;

        SimpleImage zombie = ImageManager::get()->getImagebyURL("images/ZombiePlay.png", true, true);

        double rotationAngle = 0.0; 

        switch (currentDirection) {
        case 0: 
            rotationAngle = 0.0;
            break;
        case 1: 
            rotationAngle = 3 * M_PI / 2; 
            break;
        case 2: 
            rotationAngle = M_PI; 
            break;
        case 3: 
            rotationAngle = M_PI / 2; 
            break;
        }

        ImagePixelMappingRotate mapping1(rotationAngle);

        zombie.renderImageApplyingMapping(
            getEngine(),
            getEngine()->getForegroundSurface(),
            m_iCurrentScreenX, m_iCurrentScreenY,
            zombie.getWidth(), zombie.getHeight(),
            &mapping1);
}


    virtual void virtDoUpdate(int iCurrentTime) override {
        if (getEngine()->isPaused()) return;

        if (iCurrentTime - lastUpdateTime > 100) { 
            if (m_pPlayer->isShotFired()) {
                int shotHeardAtX = m_pPlayer->getCurrentScreenX();
                int shotHeardAtY = m_pPlayer->getCurrentScreenY();

                int dx = (shotHeardAtX - m_iCurrentScreenX);
                int dy = (shotHeardAtY - m_iCurrentScreenY);
                int stepX = (dx == 0 ? 0 : (dx > 0 ? speed : -speed));
                int stepY = (dy == 0 ? 0 : (dy > 0 ? speed : -speed));

                if (canMoveTo(m_iCurrentScreenX + stepX, m_iCurrentScreenY + stepY)) {
                    m_iCurrentScreenX += stepX;
                    m_iCurrentScreenY += stepY;
                }
                else if (canMoveTo(m_iCurrentScreenX + stepX, m_iCurrentScreenY)) {
                    m_iCurrentScreenX += stepX;
                }
                else if (canMoveTo(m_iCurrentScreenX, m_iCurrentScreenY + stepY)) {
                    m_iCurrentScreenY += stepY;
                }
                else {
                    currentDirection = rand() % 4;
                }
            }
            else if (currentDirection == -1 || stepsTaken >= 3) {
                currentDirection = rand() % 4; 
                stepsTaken = 0;
            }

            int newX = m_iCurrentScreenX, newY = m_iCurrentScreenY;
            switch (currentDirection) {
            case 0: newY -= speed; break; 
            case 1: newX += speed; break; 
            case 2: newY += speed; break; 
            case 3: newX -= speed; break; 
            }

            if (canMoveTo(newX, newY)) {
                m_iCurrentScreenX = newX;
                m_iCurrentScreenY = newY;
                stepsTaken++;
            }
            else {
                currentDirection = -1;
            }
            lastUpdateTime = iCurrentTime;
        }       

        if (collidePlayer(m_pPlayer->getCurrentScreenX(), m_pPlayer->getCurrentScreenY(), m_iCurrentScreenX, m_iCurrentScreenY)) {
            dynamic_cast<CrimsonWasteland2*>(getEngine())->zombieCollide(true);
            m_pPlayer->resetLocation();
        }

        m_oMover.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX, m_iCurrentScreenY, iCurrentTime, iCurrentTime);
        m_oMover.calculate(iCurrentTime);
        getEngine()->redrawDisplay();
    }

    void updateFacingDirection(int targetX, int targetY) {
        if (targetX > m_iCurrentScreenX) {
            currentDirection = 1; 
        }
        else if (targetX < m_iCurrentScreenX) {
            currentDirection = 3; 
        }
        else if (targetY > m_iCurrentScreenY) {
            currentDirection = 2; 
        }
        else if (targetY < m_iCurrentScreenY) {
            currentDirection = 0; 
        }
    }

    bool canMoveTo(int x, int y) {
        int tileSide = 50; 
        int zombieSide = 70; 

        int topLeftX = x / tileSide;
        int topLeftY = y / tileSide;
        int topRightX = (x + zombieSide) / tileSide;
        int topRightY = y / tileSide;
        int bottomLeftX = x / tileSide;
        int bottomLeftY = (y + zombieSide) / tileSide;
        int bottomRightX = (x + zombieSide) / tileSide;
        int bottomRightY = (y + zombieSide) / tileSide;


        CrimsonWasteland2TileManager& tm = static_cast<CrimsonWasteland2*>(getEngine())->GetTileManager();
        return tm.isWalkable(topLeftX, topLeftY) &&
            tm.isWalkable(topRightX, topRightY) &&
            tm.isWalkable(bottomLeftX, bottomLeftY) &&
            tm.isWalkable(bottomRightX, bottomRightY);
    }

    bool collidePlayer(int playerX, int playerY, int x, int y) {
        int playerSide = 70;

        int zombieSide = 70;

        return (x < playerX + playerSide && x + zombieSide > playerX &&
            y < playerY + playerSide && y + zombieSide > playerY);

    }

private:
    CrimsonWasteland2* m_pMainEngine;
};