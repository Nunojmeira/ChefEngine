#include "Precompiled.h"
#include "ChefEngine.h"


ChefEngine::App& ChefEngine::MainApp()
{
    static App sApp;
    return sApp;
}