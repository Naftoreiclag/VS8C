#ifndef NRES_SYSTEM_HPP
#define NRES_SYSTEM_HPP

#include <vector>

#include "nresListener.hpp"
#include "nresTypedefs.hpp"

namespace nres {

class System : public Listener {
public:
    System();
    virtual ~System();
public:
    virtual const std::vector<ComponentID>& getRequiredComponents() = 0;
};

}

#endif // NRES_SYSTEM_HPP
