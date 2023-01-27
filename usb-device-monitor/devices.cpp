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

void split(const string &subj, const regex &rgx, array<string, 2> &vars) {
    smatch match;
    regex_search(subj, match, rgx);
    vars[0] = subj.substr(0, match.position(0));
    replace(vars[0].begin(), vars[0].end(), '_', ' ');
    vars[1] = match.str(0).erase(0,1);
    vars[1].erase(vars[1].end()-1);
}

device_collection getDevices() {
    const string DEVICE_PATH{"/dev/serial/by-id/"};
    const regex hregex{"_[0-9A-Fa-f]+-"};
    device_collection devices;

    for (const auto &entry : directory_iterator(DEVICE_PATH)) {
        if (entry.is_symlink()) {
            string slink = read_symlink(entry).stem().generic_string();
            string sname = entry.path().stem().generic_string().erase(0,4);
            array<string, 2> results;
            split(sname, hregex, results);
            devices[slink] = results;
        }
    }

    return devices;
}
