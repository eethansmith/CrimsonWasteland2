#ifndef PSYESENGINE_H
#define PSYESENGINE_H

#include "BaseEngine.h"

#include "Psyes9TileManager.h"

#include "ExampleFilterPointClasses.h" 

class Psyes9Engine : public BaseEngine
{
public:
    /**
    Constructor 
    */
    Psyes9Engine()
        : m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling)
    {}
    int virtInitialise() override;

    virtual void virtSetupBackgroundBuffer() override;

    int virtInitialiseObjects() override;

    void virtDrawStringsOnTop() override;

    void virtDrawStringsUnderneath() override;

    virtual void virtMouseDown(int iButton, int iX, int iY) override;

    void virtKeyDown(int iKeyCode) override;

    void setCollisionOccurred(bool occurred) {
        m_bCollisionOccurred = occurred;
    }

    bool hasCollisionOccurred() const {
        return m_bCollisionOccurred;
    }

private:
    bool m_bCollisionOccurred = false;
    Psyes9TileManager myTileManager;

protected:
    FilterPointsScaling m_filterScaling;
    FilterPointsTranslation m_filterTranslation;
};

#endif