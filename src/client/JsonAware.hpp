#ifndef VSE_JSONAWARE
#define VSE_JSONAWARE

#include "json/json.h"

namespace vse {

class JsonAware {
public:
    JsonAware();
    virtual ~JsonAware();
    
    virtual void serialize(Json::Value& json) const = 0;
};

}

#endif // VSE_JSONAWARE
