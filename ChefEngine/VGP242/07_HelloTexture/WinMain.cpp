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
    mainApp.Run();

    return(0);
}