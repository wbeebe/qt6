#pragma once

#include <array>
#include <map>
#include <string>
#include <iostream>

typedef std::map<std::string, std::array<std::string,2>> device_collection;

device_collection getDevices();