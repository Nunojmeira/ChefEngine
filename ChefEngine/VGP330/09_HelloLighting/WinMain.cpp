#include <ChefEngine/Inc/ChefEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle,
    Square,
    Diamond
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    ChefEngine::App& mainApp = ChefEngine::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);

    ChefEngine::AppConfig config;
    config.appName = L"Hello Lighting";
    config.winWidth = 1280;
    config.winHeight = 720;
    
    mainApp.Run(config);

    return(0);
}