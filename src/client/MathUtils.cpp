#include "MathUtils.hpp"

namespace vse {
namespace MathUtils {
    
    Vec3f onAxis(const Vec3f& input, const Vec3f& normalizedConstraint) {
        return normalizedConstraint * input.dot(normalizedConstraint);
    }
    Vec3f onPlane(const Vec3f& input, const Vec3f& planeNormal) {
        return input - (planeNormal * input.dot(planeNormal));
    }
    
}
}

