#include <ChefEngine/Inc/ChefEngine.h>

enum class States : size_t
{
    GameState = 0
};
class GameState : public ChefEngine::AppState
{
public:
    virtual ~GameState() = default;

};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    ChefEngine::App& mainApp = ChefEngine::MainApp();
    
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run();

    return(0);
}