#pragma once

#include "BaseEngine.h"
#include "ImageManager.h"

#include "ImagePixelMapping.h"
#include "CrimsonWasteland2MenuObjects.h"
#include "CrimsonWasteland2TileManager.h"

#include "ExampleFilterPointClasses.h" 

#define MAX_PLAYERS 100
#define NAME_LEN 50

class CrimsonWasteland2 :
    public BaseEngine
{
public:
    CrimsonWasteland2(void) ;
    ~CrimsonWasteland2(void);

    int virtInitialise() override;
    virtual void virtSetupBackgroundBuffer() override;
    virtual void virtMainLoopDoBeforeUpdate() override;
    virtual void copyAllBackgroundBuffer();
    virtual int virtInitialiseObjects();
    virtual void virtDrawStringsOnTop() override;
    virtual void virtDrawStringsUnderneath() override;
    
    virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtMouseWheel(int x, int y, int which, int timestamp) override;
    virtual void virtKeyDown(int iKeyCode) override;

    enum State { 
        stateMenuStartUp,  
        stateMenuRunning, 
        stateGameIntro,
        stateGameStartUp, 
        stateGameRunning, 
        stateGamePause,
        stateGameWon,
        stateGameLevel2StartUp,
        stateGameLevel2,
        stateGameLost,
        stateLevelWon
    };

    struct PlayerScore {
        char name[50]; 
        int score;
    };

    CrimsonWasteland2TileManager& GetTileManager() { return m_oTiles; }
    
    void reachedExit(bool atExit) {
        if (atExit == true) {
            if (!level2Complete) {
                m_state = stateLevelWon;
            }
            else if (level2Complete){
                m_state = stateGameWon;
            }
            
  
        }
    }

    void CrimsonWasteland2::loadScores(PlayerScore scores[], int& count) { // Correct the signature
        FILE* file = fopen("scoreboard.txt", "r");
        if (file == NULL) {
            count = 0;
            return;
        }

        while (fscanf(file, "%49s %d", scores[count].name, &scores[count].score) != EOF && count < MAX_PLAYERS) {
            count++;
        }

        fclose(file);
    }

    void CrimsonWasteland2::saveScores(const PlayerScore scores[], int count) {
        FILE* file = fopen("scoreboard.txt", "w");
        if (file == NULL) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }

        fclose(file);
    }

    void CrimsonWasteland2::virtScoreboard(const std::string& name, int score) {
        PlayerScore scores[MAX_PLAYERS];
        int count = 0;

        loadScores(scores, count);

        if (count < MAX_PLAYERS) {
            strncpy(scores[count].name, name.c_str(), NAME_LEN - 1);
            scores[count].name[NAME_LEN - 1] = '\0';
            scores[count].score = score;
            count++;
        }

        saveScores(scores, count);
    }

    int getPlayerLives() const { return playerLives; }
    void setPlayerLives(int lives) { playerLives = lives; }

    void zombieCollide(bool touchZombie) {
        if (touchZombie == true) {
            if (--playerLives <= 0) {
                m_state = stateGameLost;
            }
        }
    }

private:
    State m_state;

    int m_warehouse;

    bool ratAppears;
    int ratAppearTime;

    double zombie1X, zombie1Y;
    double zombie2X, zombie2Y;
    double zombie3X, zombie3Y;

    int clip;
    int playerX;
    int playerY;
    int currentOffsetX;
    int scrolledOut;

    bool userWantsToType;
    char name[5];
    int nameLength = 0;
    int score;
    int startScore;

    int now;
    bool rat;
    int ratTime;

    std::string difficulty = "NORMAL";
    int textWidth = 500, textHeight = 30; 
    std::vector<std::string> difficulties = { "EASY", "NORMAL", "HARD" };
    size_t currentDifficultyIndex = 1; 

    ClickableImageObject* startButton;

    CrimsonWasteland2TileManager m_oTiles;

    bool level2Complete;

protected:
    int m_iOffset;
    int playerLives;

    ImagePixelMappingRotate rotator;
    ImagePixelMappingShiftXY shifter1;
    ImagePixelMappingShiftXY shifter2;

    FilterPointsScaling m_filterScaling;
    FilterPointsTranslation m_filterTranslation;
};

