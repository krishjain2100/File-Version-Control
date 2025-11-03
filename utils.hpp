#pragma once
#include <string>
#include <vector>
#include <chrono>

#define ull unsigned long long
#define uc unsigned char

const ull OFFSET = 14695981039346656037ULL;
const ull PRIME = 1099511628211ULL;

extern ull counter;

ull hash_str(const std::string& s);
std::vector<std::string> split(const std::string& s);
time_t time_now();