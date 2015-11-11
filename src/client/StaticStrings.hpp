#ifndef VSE_STATICSTRINGS_HPP
#define VSE_STATICSTRINGS_HPP

#include <string>

namespace vse {

class StaticStrings {
public:
    std::string ceguiRootName;
    std::string renderTargetName;
    std::string windowTitle;
public:
    StaticStrings();
    ~StaticStrings();
    static StaticStrings& getSingleton();
};

}

#endif // VSE_STATICSTRINGS_HPP
