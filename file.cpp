#include "file.hpp"
using namespace std;

TreeNode::TreeNode() {
    version_id = 0;
    content = "";
    message = "";
    created_timestamp = time_now();
    snapshot_timestamp = 0;
    parent = nullptr;
}

bool TreeNode::make_snapshot(const string& msg) {
    if (isSnapshot()) { 
        cout << "Error: The active version is already a Snapshot." << endl; 
        return false;
    }
    message = msg;
    snapshot_timestamp = time_now();
    return true;
}

File::File(const string& file_name) {
    root = new TreeNode();
    root->version_id = 0;
    root->make_snapshot("Initial Snapshot");
    active_version = root;
    version_array.push_back(root);
    total_versions = 1;
    name = file_name;
    last_modified = time_now();
    recent_files_idx = 0;
    biggest_trees_idx = 0;
}

File::~File() { 
    for (auto &val: version_array) { delete val; }
}

void File::new_version() {
    TreeNode* new_file = new TreeNode();
    new_file->parent = active_version;
    new_file->version_id = total_versions;
    new_file->content = active_version->content;
    version_array.push_back(new_file);
    total_versions++;
    last_modified = time_now();
    active_version = new_file;
}