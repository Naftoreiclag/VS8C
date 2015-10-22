#include <iostream>

#include "OgreApp.hpp"

using namespace grt;

int main(int argc, char **argv) {
    OgreApp& app = OgreApp::getSingleton();
    app.run();
    return 0;
}
