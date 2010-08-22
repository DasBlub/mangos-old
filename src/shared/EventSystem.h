/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "Utilities/UnorderedMapSet.h"
#include "Utilities/MemberFunction.h"
#include "Policies/Singleton.h"

enum EVENT_TYPE
{
    EVENT_DUMMY = 0, // FIXME: dummy event because there needs to be an event! replace with _real_ events!
    EVENT_COUNT
};

/**
 * Base class for events. All events are derived from this class.
 */
class Event {
private:
    /**
     * Defines the type of this event
     */
    EVENT_TYPE eventType;
public:
    Event(EVENT_TYPE eventType);
    /**
     * Returns the type of this event
     */
    const EVENT_TYPE GetEventType() { return eventType; };

    virtual operator std::string() const = 0;
};

/**
 * Base class for event listenerers. All event listeners are derived from this class.
 *
 * Every event listener has to implement the RegisterSelf() function in order to register his own listener functions.
 */
class EventListener {
protected:
    virtual void RegisterSelf() = 0;
public:
    EventListener();
};

/**
 * This is the EventDispatcher which takes all Events and calls the listener functions.
 *
 * All listeners have to register with this class in order to be called for an event.
 */
class EventDispatcher {
    friend class MaNGOS::Singleton<EventDispatcher>;
    friend class MaNGOS::OperatorNew<EventDispatcher>;

private:
    /**
     * All listeners are stored in an unordered_set
     *
     * Because a listener can register himself for several events and an event can trigger several listeners, this is an array with an unordered_set for each kind of events.
     */
    UNORDERED_SET<MemberFunction<Event*>> listeners[EVENT_COUNT];

    EventDispatcher() {};
public:
    /**
     * All listeners have to call this function to register themself.
     *
     * @param eventType The event for which the listeners hould be registered
     * @param fct The MemberFunction which should be called when an event registers himself
     */
    void RegisterEventListener(EVENT_TYPE eventType, MemberFunction<Event*> fct);

    /**
     * Trigger an event
     */
    void TriggerEvent(Event* evt);
};

#define sEventDispatcher MaNGOS::Singleton<EventDispatcher>::Instance()

#endif