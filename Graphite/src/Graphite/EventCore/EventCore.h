//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

#include "Graphite/Core/grpch.h"

#ifndef GRAPHITE_GREVENT_H
#define GRAPHITE_GREVENT_H

#include "Graphite/Core/Core.h"

// All the keycodes used for events are located in 'src/Graphite/Core/Input.h'

namespace Graphite {


    /// <summary>
    /// Enum: different possible types of event, each with its own class implemented, might add more later (mainly for mouse enter and leave events)
    /// </summary>
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowUnfocus,              // Window events
        Tick, Update, Render,                                               // Might deprecate or completely remove later
        MouseButtonDown, MouseButtonUp, MouseMovement, MouseScroll,         // Mouse events
        KeyDown, KeyUp, KeyTyped                                            // Keyboard events
    };

    /// <summary>
    /// Enum: different types of single categories, an event can be of multiple types / a combination of types in the same time
    /// </summary>
    enum class EventCategory {
        None = 0,
        AppEvent_c          = GR_BIT(0),
        InputEvent_c        = GR_BIT(1),
        KeyboardEvent_c     = GR_BIT(2),
        MouseEvent_c        = GR_BIT(3),
        MouseButtonEvent_c  = GR_BIT(4)
    };

	
    /// <summary>
    /// Macros for easier definition of functions that are the same for each type of events
    /// </summary>
#define GR_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                                virtual EventType GetEventType() const override { return GetStaticType(); } \
                                virtual const char * GetName() const override { return #type; }


#define GR_EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    /// <summary>
    /// Base event class, all event types are built on top of Event, a class can't be a valid working event if it doesn't extend Event class
    /// </summary>
    class GRAPHITE_API Event {
        friend class EventDispatch;

    public:
        virtual EventType GetEventType() const = 0;                       // Returns the type of event of an instance
        virtual const char * GetName() const = 0;                           // Returns the name of an event, mainly for debugging & logging
        virtual int GetCategoryFlags() const = 0;                           // Returns the flags representing the combination of categories of an event
        virtual std::string ToString() const { return GetName(); }          // Returns the name in std::string format, mainly for debugging and logging purposes

        /// <summary>
        /// Checks if an event instance if of a given category
        /// </summary>
        /// <param name="category"> The category the function checks for </param>
        /// <returns> Returns weather the event instance is a combination of categories containing the given category </returns>
        inline bool isInCategory(EventCategory category) {
            return GetCategoryFlags() & static_cast<int>(category);
        }

        inline bool isHandled() { return m_Handled; }

    protected:
        /// <summary>
        /// A variable used to track weather the event was handles, if it isn't, its propagated further trough the engine
        /// </summary>
        bool m_Handled = false;
    };

    /// <summary>
    /// Class used to call a callback function on a specific event, that determines weather the event is handled, or dispatched further
    /// </summary>
    class GRAPHITE_API EventDispatch {
        template<typename T> using EventFn = std::function<bool(T&)>;

    public:
        EventDispatch(Event &event): m_Event(event) { }

        /// <summary>
        /// Function used for dispatching the event, if an event the class instance was initialized with is of the type specified when calling the function, the callback will be called
        /// </summary>
        /// <typeparam name="T"> The type of event for which the callback function will be called </typeparam>
        /// <param name="func"> The callback function for handling events </param>
        /// <returns> Returns weather the event was handles or not, important for further event propagation and dispatching </returns>
        template<typename T> bool Dispatch(EventFn<T> func) {
            if(m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            else {
                return false;
            }
        }

    private:
        Event &m_Event;
    };

}

#endif //GRAPHITE_GREVENT_H