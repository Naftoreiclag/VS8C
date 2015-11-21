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

#ifndef VSE_LOCALPLAYERCOMP_HPP
#define VSE_LOCALPLAYERCOMP_HPP

#include "NRES.hpp"

namespace vse {

class LocalPlayerComp : public nres::Component {
public:
    LocalPlayerComp();
    virtual ~LocalPlayerComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;

};

}

#endif // VSE_LOCALPLAYERCOMP_HPP
