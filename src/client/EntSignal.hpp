#ifndef VSE_ENTSIGNAL_HPP
#define VSE_ENTSIGNAL_HPP

namespace vse
{

class EntSignal {
public:
    enum Type {
        LOCAL_PLAYER_MOVE
    };
public:
    EntSignal();
    virtual ~EntSignal();
    
    virtual Type getType() const = 0;

};

}

#endif // VSE_ENTSIGNAL_HPP
