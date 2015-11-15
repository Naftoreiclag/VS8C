#ifndef VSE_SERIALIZATIONUTIL_HPP
#define VSE_SERIALIZATIONUTIL_HPP

#include "json/json.h"

#include "NRES.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

namespace vse {

namespace SerializationUtil {
    void serializeEntities(const nres::World& world, Json::Value& json);
    void deserializeEntities(nres::World& world, const Json::Value& json);
    
    void serializeComponent(const nres::Component& component, Json::Value& json);
    nres::Component* deserializeComponent(const Json::Value& json);
    
    void serialize(const Vec3f& vector, Json::Value& json);
    void serialize(const Quate& quater, Json::Value& json);
}

}

#endif // VSE_SERIALIZATIONUTIL_HPP
