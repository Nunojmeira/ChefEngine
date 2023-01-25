#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
    ChefEngine::Graphics::GraphicsSystem::Get()->SetClearColor(ChefEngine::Colors::Black);
}

void GameState::Update(float deltaTime)
{    
    auto inputSystem = Input::InputSystem::Get();
    if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
    {
        ChefEngine::Graphics::GraphicsSystem::Get()->SetClearColor(ChefEngine::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
    {
        ChefEngine::Graphics::GraphicsSystem::Get()->SetClearColor(ChefEngine::Colors::Green);
    }
}