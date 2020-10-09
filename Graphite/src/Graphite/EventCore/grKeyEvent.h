//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

#include "Graphite/Core/grpch.h"

#ifndef GRAPHITE_GRKEYEVENT_H
#define GRAPHITE_GRKEYEVENT_H

#include "grEventCore.h"

namespace Graphite {


    /// <summary>
    /// An event implementation for key events, all different types of key events are built on top of this class
    /// </summary>
    class GRAPHITE_API grKeyEvent : public grEvent {

    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::KeyboardEvent_c) | static_cast<int>(grEventCategory::InputEvent_c))

    protected:
        grKeyEvent(int keycode) : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    /// <summary>
    /// A key down event implementation, created and dispatched whenever a key is pressed or repeated
    /// </summary>
    class GRAPHITE_API grKeyDownEvent : public grKeyEvent {
    public:
        grKeyDownEvent(int keycode, int count) : grKeyEvent(keycode), m_RepeatCount(count) {}

        inline int Repeated() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Key Down Event: " << m_KeyCode << " (x" << m_RepeatCount << ")";
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(KeyDown);

    protected:
        int m_RepeatCount;
    };
	
    /// <summary>
    /// A key up event implementation, created and dispatched whenever a key is released
    /// </summary>
    class GRAPHITE_API grKeyUpEvent : public grKeyEvent {
    public:
        grKeyUpEvent(int keycode) : grKeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Key Up Event: " << m_KeyCode;
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(KeyUp);
    };

    /// <summary>
    /// A key typed event implementation, created and dispatched whenever a key with a keycode value of a character is pressed, used for typing input
    /// </summary>
    class GRAPHITE_API grKeyTypedEvent : public grKeyEvent {
    public:
        grKeyTypedEvent(int keycode) : grKeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Key Typed Event: " << m_KeyCode;
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(KeyTyped);
    };
	
}

#endif //GRAPHITE_GRKEYEVENT_H
