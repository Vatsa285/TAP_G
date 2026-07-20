#include <iostream>
#include "InputManager.h"

int main(){
    try
    {
        InputManager manager;
        std::cout<<"Libinput initialized successfully\n";
        manager.run();
    }
    catch(const std::exception& e)
    {
        std::cerr<<"Error: "<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }
}