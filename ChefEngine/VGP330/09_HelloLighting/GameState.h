#pragma once
#include <ChefEngine/Inc/ChefEngine.h>

using namespace ChefEngine;
using namespace ChefEngine::Graphics;

class GameState : public ChefEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;
    
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
protected:
    void ShowNormals();

    Camera mCamera;
    DirectionalLight mDirectionalLight;

    Mesh mSphere;
    RenderObject mEarthObject;
    StandardEffect mStandardEffect;

    bool mShowNormals = false;
};