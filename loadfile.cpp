#include "loadfile.h"
#include <string>
#include <iostream>
#include <fstream>
std::string loadFile(std::string filedir){
    std::ifstream f(filedir);
    
    
    FILE *filep;

    std::string file = std::string();
    f >> file;
    std::cout << file;
    return file;
}