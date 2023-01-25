#include <ChefEngine/Inc/ChefEngine.h>
#include "GameState.h"

using namespace ChefEngine;
using namespace ChefEngine::Graphics;

enum class States : size_t
{
    GameState = 0
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Simple Draw";
    config.winWidth = 1280;
    config.winHeight = 720;

    App& mainApp = ChefEngine::MainApp();    
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run(config);

    return(0);
}