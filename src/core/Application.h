#pragma once

#include "inttypes.h"
#include "EventManager.h"

class SDL_Window;

namespace Core
{

class Application
{
public:
    Application(const char* title, uint32_t width, uint32_t height);
    virtual ~Application();

    void Run();

    virtual void Update(double dtime) {}

private:
    SDL_Window* m_window    = nullptr;
    bool m_shouldQuit       = false;

    EventManager m_eventManager;
};

}