#pragma once
#include <vector>
#include <string>
#include <utility>
#include "utils.hpp"
using namespace std;

struct File; 

struct HashMap {
    vector<vector<pair<string, File*>>> buckets;
    size_t bucket_count;
    size_t bucket_index(const string& key) const;
    HashMap(size_t capacity = 1024);
    File* get(const string& key) const;
    File*& operator[](const string& key);
    void clear();
};