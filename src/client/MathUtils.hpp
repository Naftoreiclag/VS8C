/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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
