#pragma once

#include <SDL3/SDL_events.h>
#include <array>
#include "debug.h"

namespace Core
{

class EventManager
{
public:
    EventManager() = default;
    ~EventManager() = default;

    void PollEvents()
    {
        SDL_Event evt;
        m_prevKeysPressed = m_keysPressed;
        while(SDL_CALL(SDL_PollEvent(&evt))) {
            switch(evt.type) {
                case SDL_EVENT_QUIT:
                    m_shouldQuit = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    m_keysPressed[evt.key.scancode] = true;
                    break;
                case SDL_EVENT_KEY_UP:
                    m_keysPressed[evt.key.scancode] = false;
                    break;
            }
        }
    }

    inline bool ShouldQuit() const                    { return m_shouldQuit; }
    inline bool IsKeyPressed (SDL_Scancode key) const { return m_keysPressed[key] && !m_prevKeysPressed[key]; }
    inline bool IsKeyHeld    (SDL_Scancode key) const { return m_keysPressed[key]; }
    inline bool isKeyReleased(SDL_Scancode key) const { return !m_keysPressed[key] && m_prevKeysPressed[key]; }

private:
    bool m_shouldQuit = false;
    std::array<bool, SDL_SCANCODE_COUNT> m_keysPressed      = {};
    std::array<bool, SDL_SCANCODE_COUNT> m_prevKeysPressed  = {};
};

}