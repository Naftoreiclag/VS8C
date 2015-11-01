#include "MathUtils.hpp"

namespace vse {
namespace MathUtils {
    
    Vec3f onAxis(const Vec3f& input, const Vec3f& axisToRemove) {
        return axisToRemove * input.dot(axisToRemove);
    }
    Vec3f onPlane(const Vec3f& input, const Vec3f& axisPerpToPlane) {
        return input - (axisPerpToPlane * input.dot(axisPerpToPlane));
    }
    
}
}

