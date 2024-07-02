#pragma once
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include <fstream>
#include <sstream>
#include <string.h>

class FileSystem {
public:
    static const char* ReadFromFile(const std::string& path);
};