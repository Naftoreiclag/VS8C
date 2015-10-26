#ifndef VSE_ENTSIGNAL_HPP
#define VSE_ENTSIGNAL_HPP

namespace vse
{

class EntSignal {
public:
    enum Type {
        LOCAL_PLAYER_MOVE, // Player input requests movement
        LOCATION, // Entity changed spacial location
        ORIENTATION // Entity changed spacial orientation (i.e. rotation)
    };
public:
    EntSignal();
    virtual ~EntSignal();
    
    virtual Type getType() const = 0;

};

}

#endif // VSE_ENTSIGNAL_HPP
