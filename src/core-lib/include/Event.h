//
// Created by tomek on 26.04.2022.
//

#ifndef PROI_PROJEKT_EVENT_H
#define PROI_PROJEKT_EVENT_H

#include <exception>
#include <string>

/**
 * Indicates an error encountered while constructing an Event instance.
 */
struct EventConstructionException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override;
};

/**
 * \brief Represents a single event of type Event::EventType
 *
 * Event types are represented with EventType enum. EventType always needs to be passes to constructor, followed
 * by appropriate args. If incorrect args are provided, an EvenConstructionException is thrown.
 *
 * Event class has multiple constructor that can be used for initializing different events.
 *
 * Events can be generated by any classed and should be passed to an event queue (./EventQueue.h)
 */
class Event {
public:

    /**
     * Represents event types
     */
    enum EventType {
        KeyPressed = 0,
        KeyReleased,

        NullEvent
    };

    EventType type;

    /**
     * Carries additional event info for KeyPressed event
     */
    struct KeyEventInfo {
        enum KeyAction{
            Pressed =0,
            Released
        };
        unsigned int keyCode;
        KeyAction action;
    };

    // ####################################################3
    /**
     * Contains additional event info.
     * Unions member is initialized according to EventType enum passed to the constructor
     * Trying to access any member other than initialized will result in undefined behavior
     */
    union info_u {
        KeyEventInfo key;
        ~info_u(){};  // DO NOT change this to =default, or else it will stop working
    } info = {};

    // FIXME not so elegant
    Event(EventType, unsigned int ui1, KeyEventInfo::KeyAction);

    explicit Event(EventType);

    Event()=delete;
};


#endif //PROI_PROJEKT_EVENT_H
