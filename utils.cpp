#include "utils.hpp"
using namespace std;

ull counter = 0;

ull hash_str(const string& s) {
    ull h = OFFSET;
    for (uc c : s) { 
        h ^= (ull)c; 
        h *= PRIME; 
    }
    return h;
}

vector<string> split(const string& s) {
    vector<string> parts;
    size_t first_space = s.find(' ');
    if (first_space == string::npos) { parts.push_back(s); return parts; }
    parts.push_back(s.substr(0, first_space));
    size_t second_space = s.find(' ', first_space + 1);
    if (second_space == string::npos) { parts.push_back(s.substr(first_space + 1)); return parts;}
    parts.push_back(s.substr(first_space + 1, second_space - (first_space + 1)));
    parts.push_back(s.substr(second_space + 1));
    return parts;
}

time_t time_now() { 
    auto now = chrono::system_clock::now(); 
    return chrono::system_clock::to_time_t(now);
}