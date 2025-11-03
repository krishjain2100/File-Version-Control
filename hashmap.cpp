#include "hashmap.hpp"
#include "file.hpp"
using namespace std;

size_t HashMap::bucket_index(const string& key) const { 
    return hash_str(key) % bucket_count;
}

HashMap::HashMap(size_t capacity) {
    buckets.resize(capacity);
    bucket_count = capacity;
}

File* HashMap::get(const string& key) const {
    size_t idx = bucket_index(key);
    const auto &vec = buckets[idx];
    for (const auto &p : vec) {
        if (p.first == key) return p.second;
    }
    return nullptr;
}

File*& HashMap::operator[](const string& key) {
    size_t idx = bucket_index(key);
    auto &vec = buckets[idx];
    for (auto &p : vec) {
        if (p.first == key) return p.second;
    }
    vec.push_back({key, nullptr});
    return vec.back().second;
}

void HashMap::clear() {
    for (auto &bucket : buckets) {
        for (auto &p : bucket) { 
            if (p.second) delete p.second;
        }
        bucket.clear();
    }
}