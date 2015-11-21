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
