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

#ifndef VSE_ORIENATIONSIGNAL_HPP
#define VSE_ORIENATIONSIGNAL_HPP

#include "EntSignal.hpp"
#include "Quate.hpp"

namespace vse {

class OrientationSignal : public EntSignal {
public:
    OrientationSignal(Quate orienationUpdate);
    ~OrientationSignal();

    EntSignal::Type getType() const;
    
    Quate mOrientationUpdate;
};

}

#endif // VSE_ORIENATIONSIGNAL_HPP
