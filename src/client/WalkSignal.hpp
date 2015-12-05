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

#ifndef VSE_LOCALPLAYERMOVESIGNAL_HPP
#define VSE_LOCALPLAYERMOVESIGNAL_HPP

#include "EntSignal.hpp"
#include "Vec3f.hpp"

namespace vse {

class WalkSignal : public EntSignal {
public:
    WalkSignal(Vec3f requestedMovement);
    ~WalkSignal();

    EntSignal::Type getType() const;
    
    Vec3f requestedMovement;
};

}

#endif // VSE_LOCALPLAYERMOVESIGNAL_HPP
