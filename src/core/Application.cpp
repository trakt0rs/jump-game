#include "Application.h"

#include <SDL3/SDL.h>
#include "debug.h"

namespace Core
{

Application::Application(const char* title, uint32_t width, uint32_t height)
{
    if(!SDL_CALL(SDL_Init(SDL_INIT_VIDEO))) {
        LOG_FATAL("Failed to init SDL: {}", SDL_GetError());
    }

    m_window = SDL_CALL(SDL_CreateWindow(title, width, height, SDL_WINDOW_HIDDEN));

    SDL_CALL(SDL_ShowWindow(m_window));
}

Application::~Application()
{
    SDL_CALL_VOID(SDL_DestroyWindow(m_window));
}

void Application::Run()
{
    constexpr double targetFPS = 60.0;
    constexpr double targetFrameTime = static_cast<uint64_t>(1e9 / targetFPS); // in ns

    uint64_t lastTicks = SDL_GetPerformanceCounter();
    const uint64_t freq = SDL_GetPerformanceFrequency();

    while(!m_shouldQuit) {
        // delta time
        uint64_t currentTicks = SDL_GetPerformanceCounter();
        double deltaTime = static_cast<double>(currentTicks - lastTicks) / freq;
        lastTicks = currentTicks;

        // update/poll events
        m_eventManager.PollEvents();
        m_shouldQuit = m_eventManager.ShouldQuit();

        this->Update(deltaTime);

        // frame limiting
        uint64_t frameEnd = SDL_GetPerformanceCounter();
        uint64_t elapsedTicks = frameEnd - currentTicks;
        uint64_t elapsedNs = (elapsedTicks * 1000000000ull) / freq;

        if (elapsedNs < targetFrameTime) {
            SDL_DelayPrecise(targetFrameTime - elapsedNs);
        }
    }
}

}