//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

#include "Graphite/Core/grpch.h"

#ifndef GRAPHITE_GRAPPEVENT_H
#define GRAPHITE_GRAPPEVENT_H

#include "grEventCore.h"

namespace Graphite {

    /// <summary>
    /// Implementation of a window resize event, created and dispatched whenever a window with resizing enabled is resized,
    /// holds the height and width of the window after resizing, measured in pixels
    /// </summary>
    class GRAPHITE_API grWindowResizeEvent : public grEvent {
    public:
        grWindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() { return m_Width; }
        inline unsigned int GetHeight() { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Window Resize Event: " << "(" << m_Width << ", " << m_Height << ")";
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(WindowResize)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    /// <summary>
    /// Implementation of a window close event, triggered when the close button or a close 'signal' is sent to the application, and is dispatched and propagated before the application closes
    /// </summary>
    class GRAPHITE_API grWindowCloseEvent : public grEvent {
    public:
        grWindowCloseEvent() {}

        GR_EVENT_CLASS_TYPE(WindowClose)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

    /// <summary>
    /// Implementation of a window focus event, triggered when the app window is clicked, while not in focus
    /// </summary>
    class GRAPHITE_API grWindowFocusEvent : public grEvent {
    public:
        grWindowFocusEvent() {}

        GR_EVENT_CLASS_TYPE(WindowFocus)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

    /// <summary>
    /// Implementation of a window unfocus event, triggered when left mouse button is clicked outside of the app window, while being in focus
    /// </summary>
    class GRAPHITE_API grWindowUnfocusEvent : public grEvent {
    public:
        grWindowUnfocusEvent() {}

        GR_EVENT_CLASS_TYPE(WindowUnfocus)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

    /// <summary>
    /// App tick event, triggered every time the app goes trough the main loop ('ticks')
    /// </summary>
    class GRAPHITE_API grAppTickEvent : public grEvent {
    public:
        grAppTickEvent() {}

        GR_EVENT_CLASS_TYPE(Tick)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

    /// <summary>
    /// App update event, triggered after every app info update
    /// </summary>
    class GRAPHITE_API grAppUpdateEvent : public grEvent {
    public:
        grAppUpdateEvent() {}

        GR_EVENT_CLASS_TYPE(Update)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

    /// <summary>
    /// App render event, triggered whenever the window is rendered to (after the used renderer goes trough a render loop)
    /// </summary>
    class GRAPHITE_API grAppRenderEvent : public grEvent {
    public:
        grAppRenderEvent() {}

        GR_EVENT_CLASS_TYPE(WindowClose)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(grEventCategory::AppEvent_c))
    };

}

#endif //GRAPHITE_GRAPPEVENT_H
