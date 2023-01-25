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
    virtual void OnCreateShape();
    struct Vertex
    {
        ChefEngine::DEMath::Vector3 position;
        ChefEngine::Color color;
    };
    std::vector<Vertex> mVerticies;

    Camera mCamera;
    ConstantBuffer mConstantBuffer;
    MeshBuffer mMeshBuffer;
    VertexShader mVertexShader;
    PixelShader mPixelShader;
};

class Triangle : public GameState
{
public:
    virtual ~Triangle() = default;

protected:
    void OnCreateShape() override;
};