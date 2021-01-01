//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"

#ifndef GRAPHITE_GRMOUSEEVENT_H
#define GRAPHITE_GRMOUSEEVENT_H

#include "EventCore.h"

namespace Graphite {

    /// <summary>
    /// Implementation of a mouse move event, whenever a mouse is moved, the event is created and dispatched, and holds the position of the mouse cursor, which is retrievable
    /// </summary>
    class GRAPHITE_API MouseMovEvent : public Event {
    public:
        MouseMovEvent(double x, double y) : m_MouseX(x), m_MouseY(y) {}

        inline double GetX() { return m_MouseX; }

        inline double getY() { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Movement Event: " << "(" << m_MouseX << ", " << m_MouseY << ")";
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(MouseMovement)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::MouseEvent_c) | static_cast<int>(EventCategory::InputEvent_c))
    private:
        double m_MouseX;
        double m_MouseY;
    };

    /// <summary>
    /// Implementation of a mouse scroll event, supports both horizontal and vertical scrolling
    /// </summary>
    class GRAPHITE_API MouseScrollEvent : public Event {
    public:
        MouseScrollEvent(double offsetX, double offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}

        inline double GetOffsetX() { return m_OffsetX; }
        inline double GetOffsetY() { return m_OffsetY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Scroll Event: " << "(" << m_OffsetX << ", " << m_OffsetY << ")";
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(MouseScroll)

        GR_EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::MouseEvent_c) | static_cast<int>(EventCategory::InputEvent_c))
    private:
        double m_OffsetX;
        double m_OffsetY;
    };

    /// <summary>
    /// Implementation of a mouse button event, on which the button up and down events are based upon, supports left, right, scroll click plus 5 additional buttons for use
    /// </summary>
    class GRAPHITE_API MouseButtonEvent : public Event {
    public:
        inline int GetMouseButton() { return m_Button; }

        GR_EVENT_CLASS_CATEGORY( static_cast<int>(EventCategory::MouseButtonEvent_c) | static_cast<int>(EventCategory::MouseEvent_c)
                                            | static_cast<int>(EventCategory::InputEvent_c))
    protected:
        MouseButtonEvent(int button) : m_Button(button) {}

        int m_Button;
    };

    /// <summary>
    /// Implementation of mouse button down event, dispatched when a mouse button is clicked
    /// </summary>
    class GRAPHITE_API MouseButtonDownEvent : public MouseButtonEvent {
    public:
        MouseButtonDownEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Button Down Event: " << m_Button;
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(MouseButtonDown)
    };

    /// <summary>
    /// Implementation of mouse button up event, dispatched when a mouse button is released
    /// </summary>
    class GRAPHITE_API MouseButtonUpEvent : public MouseButtonEvent {
    public:
        MouseButtonUpEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Button Up Event: " << m_Button;
            return ss.str();
        }

        GR_EVENT_CLASS_TYPE(MouseButtonUp)
    };

}

#endif //GRAPHITE_GRMOUSEEVENT_H
