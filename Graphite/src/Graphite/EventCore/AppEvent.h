//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"

#ifndef GRAPHITE_GRAPPEVENT_H
#define GRAPHITE_GRAPPEVENT_H

#include "EventCore.h"

namespace Graphite {

    /// <summary>
    /// Implementation of a window resize event, created and dispatched whenever a window with resizing enabled is resized,
    /// holds the height and width of the window after resizing, measured in pixels
    /// </summary>
    class GRAPHITE_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() { return m_Width; }
        inline unsigned int GetHeight() { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Window Resize Event: " << "(" << m_Width << ", " << m_Height << ")";
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(WindowResize)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    /// <summary>
    /// Implementation of a window close event, triggered when the close button or a close 'signal' is sent to the application, and is dispatched and propagated before the application closes
    /// </summary>
    class GRAPHITE_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        GR_EVENT_CLASS_TYPE(WindowClose)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

    /// <summary>
    /// Implementation of a window focus event, triggered when the app window is clicked, while not in focus
    /// </summary>
    class GRAPHITE_API WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() {}

        GR_EVENT_CLASS_TYPE(WindowFocus)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

    /// <summary>
    /// Implementation of a window unfocus event, triggered when left mouse button is clicked outside of the app window, while being in focus
    /// </summary>
    class GRAPHITE_API WindowUnfocusEvent : public Event {
    public:
        WindowUnfocusEvent() {}

        GR_EVENT_CLASS_TYPE(WindowUnfocus)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

    /// <summary>
    /// App tick event, triggered every time the app goes trough the main loop ('ticks')
    /// </summary>
    class GRAPHITE_API AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        GR_EVENT_CLASS_TYPE(Tick)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

    /// <summary>
    /// App update event, triggered after every app info update
    /// </summary>
    class GRAPHITE_API AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        GR_EVENT_CLASS_TYPE(Update)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

    /// <summary>
    /// App render event, triggered whenever the window is rendered to (after the used renderer goes trough a render loop)
    /// </summary>
    class GRAPHITE_API AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        GR_EVENT_CLASS_TYPE(WindowClose)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::AppEvent_c))
    };

}

#endif //GRAPHITE_GRAPPEVENT_H

#if defined (_MSC_VER)
#pragma warning(pop)
#endif