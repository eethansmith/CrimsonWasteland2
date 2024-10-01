#pragma once

#include "BaseEngine.h"
#include "MyTileManager.h" // Include the header file for your Tile Manager.

class MyDemoA :
    public BaseEngine
{
public:
    MyDemoA(); // Constructor declaration.
    void virtSetupBackgroundBuffer() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;

protected:
    MyTileManager tm; // Tile Manager instance.
public:
    int virtInitialiseObjects();
};
