#pragma once

#include "header.h"
#include "DisplayableObject.h"
#include "ImageManager.h"
#include "BaseEngine.h"
#include "CrimsonWasteland2.h"

class CrimsonWasteland2MenuObjects :
    public DisplayableObject
{
};

class ImageObject : public DisplayableObject {
public:
    // Constructor
    ImageObject(BaseEngine* pEngine, std::string imageURL, int x, int y, bool useTopLeftFor00 = true)
        : DisplayableObject(pEngine, 100, 100, useTopLeftFor00),
        image(ImageManager::get()->getImagebyURL(imageURL, true, false)) {
        // Set the draw width and height to the image's dimensions
        this->m_iDrawWidth = image.getWidth();
        this->m_iDrawHeight = image.getHeight();
        // Set the object's initial screen position
        this->m_iCurrentScreenX = x;
        this->m_iCurrentScreenY = y;
        // Set drawing position offset based on whether we're using the top left corner for (0,0)
        m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
        m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
        setVisible(true); // Make the image visible
    }

    // Draw the object with white background made transparent
    virtual void virtDraw() override {
        if (isVisible()) {
            // Assuming renderImageWithMask supports a color key for transparency,
            // where 0xFFFFFF is the color code for white
            image.renderImageWithMask(getEngine()->getForegroundSurface(),
                0, 0, // Source position
                m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, // Destination position
                m_iDrawWidth, m_iDrawHeight,
                0xFFFFFF); // Color key for transparency
        }
    }

private:
    SimpleImage image;
};

class ClickableImageObject : public DisplayableObject {
public:
    // Constructor
    ClickableImageObject(BaseEngine* pEngine, std::string imageUrl, int x, int y, bool useTopLeftFor00 = true)
        : DisplayableObject(x, y, pEngine, 100, 100, useTopLeftFor00),
        image(ImageManager::get()->getImagebyURL(imageUrl, true, false)),
        startPressed(false) {  // Initialize startPressed to false
        // Set the draw width and height to the image's dimensions
        m_iDrawWidth = image.getWidth();
        m_iDrawHeight = image.getHeight();
        // Offset within the drawing area to draw at - need to reset since width and height changed
        m_iStartDrawPosX = useTopLeftFor00 ? 0 : -m_iDrawWidth / 2;
        m_iStartDrawPosY = useTopLeftFor00 ? 0 : -m_iDrawHeight / 2;
        setVisible(true); // Make the image visible
    }

    virtual void virtDraw() override {
        if (isVisible()) {
            // Use the correct color key for white (0xFFFFFF)
            image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
                m_iCurrentScreenX + m_iStartDrawPosX,
                m_iCurrentScreenY + m_iStartDrawPosY,
                m_iDrawWidth, m_iDrawHeight, 0xFFFFFF); // Color key for white
        }
    }

    virtual void virtMouseDown(int iButton, int iX, int iY) override {
        std::cout << "Mouse Down Detected at: " << iX << ", " << iY << std::endl;
        if (iButton == SDL_BUTTON_LEFT && virtIsPositionWithinObject(iX, iY)) {
            std::cout << "Start button was clicked." << std::endl;
            startPressed = true;
        }
    }

    // Function to check if the start button was pressed
    bool isStartPressed() const {
        return startPressed;
    }

private:
    SimpleImage image;
    bool startPressed;
};

class TextBoxObject : public DisplayableObject {
public:
    TextBoxObject(BaseEngine* pEngine, int x, int y)
        : DisplayableObject(pEngine, x, y),
        textBoxPressed(false), userWantsToType(false),
        textContent(""), MAX_CHARS(4) {

        m_iStartDrawPosX = x;
        m_iStartDrawPosY = y;
        setVisible(true);
    }

    virtual void virtDraw() override {
        if (isVisible()) {
            getEngine()->drawForegroundRectangle(m_iStartDrawPosX - 7, m_iStartDrawPosY - 7, m_iStartDrawPosX + 207, m_iStartDrawPosY + 57, 0x000000);
            getEngine()->drawForegroundRectangle(m_iStartDrawPosX - 5, m_iStartDrawPosY - 5, m_iStartDrawPosX + 205, m_iStartDrawPosY + 55, 0x6EA2A2);

            getEngine()->drawForegroundRectangle(m_iStartDrawPosX - 2, m_iStartDrawPosY - 2, m_iStartDrawPosX + 202, m_iStartDrawPosY + 52, 0x000000);
            getEngine()->drawForegroundRectangle(m_iStartDrawPosX, m_iStartDrawPosY, m_iStartDrawPosX + 200, m_iStartDrawPosY + 50, 0xFEFDD7);
        }
    }


private:
    bool textBoxPressed;
    bool userWantsToType;
    std::string textContent;
    const size_t MAX_CHARS;
};

