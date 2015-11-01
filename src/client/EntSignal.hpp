#ifndef VSE_ENTSIGNAL_HPP
#define VSE_ENTSIGNAL_HPP

namespace vse
{

class EntSignal {
public:
    enum Type {
        REQ_WALK, // Player input requests movement
        LOCATION, // Physics changed location
        ORIENTATION // Physics changed orientation (i.e. rotation)
    };
public:
    EntSignal();
    virtual ~EntSignal();
    
    virtual Type getType() const = 0;

};

}

#endif // VSE_ENTSIGNAL_HPP
