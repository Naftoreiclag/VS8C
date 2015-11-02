#ifndef VSE_MATHUTILS_HPP
#define VSE_MATHUTILS_HPP

#include "Vec3f.hpp"

namespace vse {
namespace MathUtils {

    Vec3f onAxis(const Vec3f& input, const Vec3f& normalizedConstraint);
    Vec3f onPlane(const Vec3f& input, const Vec3f& planeNormal);
    
}
}

#endif // VSE_MATHUTILS_HPP
