#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "utils.hpp"
using namespace std;

struct TreeNode {
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    time_t snapshot_timestamp;
    TreeNode* parent;
    TreeNode(); 
    bool isSnapshot() const { return snapshot_timestamp != 0; }
    bool make_snapshot(const string& msg);
};

struct File {
    TreeNode* root;
    TreeNode* active_version;
    vector<TreeNode*> version_array; 
    string name;
    int last_modified;
    int total_versions;
    int recent_files_idx;
    int biggest_trees_idx;
    File(const string& file_name);
    ~File();
    void new_version();
};