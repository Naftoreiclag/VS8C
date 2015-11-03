#ifndef VSE_SERIALIZATIONUTIL_HPP
#define VSE_SERIALIZATIONUTIL_HPP

#include "json/json.h"

#include "NRES.hpp"

namespace vse {

namespace SerializationUtil {
    void serializeEntities(const nres::World& world, Json::Value& json);
    void deserializeEntities(nres::World& world, const Json::Value& json);
}

}

#endif // VSE_SERIALIZATIONUTIL_HPP
