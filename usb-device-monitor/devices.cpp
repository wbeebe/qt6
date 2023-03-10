/*
 * Copyright (c) 2023 William H. Beebe, Jr.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <regex>

#include "devices.hpp"

using std::array;
using std::string;
using std::pair;
using std::regex;
using std::regex_search;
using std::replace;
using std::smatch;
using std::filesystem::directory_iterator;
using std::filesystem::path;
using std::filesystem::read_symlink;

bool split(const string &subj, const regex &rgx, array<string, 2> &vars) {
    smatch match;
    if (regex_search(subj, match, rgx)) {
        vars[0] = subj.substr(0, match.position(0));
        replace(vars[0].begin(), vars[0].end(), '_', ' ');
        vars[1] = match.str(0).erase(0,1);
        vars[1].erase(vars[1].end()-1);
        return true;
    }

    return false;
}

/* This originally started as a command-line utility, one of three in which
 * the other two were written in Python and Rust. It was a test of language
 * utility.
 * 
 * The function looks down /dev/serial/by-id to find any and all USB devices
 * plugged in. It turns out that the entries down that path are links to
 * equivalent devices in /dev. The function reads them all, follows the links
 * to get the device names, then organizes the information to return to the
 * caller.
 * 
 * The data is returned as an array of device, interface name, and a unique
 * hexadecimal ID. The idea behind this is that while the devices may shift,
 * the unique hexadecimal IDs will not change.
 */

device_collection getDevices() {
    const string DEVICE_PATH{"/dev/serial/by-id/"};
    const regex hregex{"_[0-9A-Fa-f]+I*-"};
    device_collection devices;

    for (const auto &entry : directory_iterator(DEVICE_PATH)) {
        if (entry.is_symlink()) {
            string slink = read_symlink(entry).stem().generic_string();
            string sname = entry.path().stem().generic_string().erase(0,4);
            array<string, 2> results;
            if (split(sname, hregex, results)) {
                devices[slink] = results;
            }
        }
    }

    return devices;
}
