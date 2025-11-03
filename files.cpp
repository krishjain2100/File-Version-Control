#include "files.hpp"
#include "utils.hpp" 
#include <iostream>
#include <iomanip>

using namespace std;

Files::Files() : files(1024) { 
    count = 0; 
}

Files::~Files() { 
    files.clear(); 
}

File* Files::Retriever(const string& name) const {
    File* f = files.get(name);
    if (!f) { 
        cout << "Error: File '" << name << "' not found." << endl; 
        return nullptr; 
    }
    return f;
}

void Files::Create(const string& name) {
    File* check = files.get(name);
    if (check) { 
        cout << "Error: File with name '" << name << "' already exists." << endl; 
        return; 
    }
    File* ptr = new File(name);
    files[name] = ptr;
    count++;
    ptr->last_modified = ++counter; 
    recent_files.push(ptr);
    biggest_trees.push(ptr);
    cout << "Success: File '" << name << "' was created." << endl;
}

void Files::Read(const string& name) const {
    File* ptr = Retriever(name);
    if(!ptr) return;
    TreeNode* av = ptr->active_version;
    cout << "--- Reading file '" << name << "' ---" << endl;
    cout << av->content << endl;
}

void Files::Insert(const string& name, const string& content_to_append) {
    File* ptr = Retriever(name);
    if(!ptr) return;
    if (ptr->active_version->isSnapshot()) {
        ptr->new_version();
        biggest_trees.push(ptr); 
    }
    ptr->active_version->content += content_to_append;
    ptr->last_modified = ++counter;
    recent_files.push(ptr); 
    cout << "Success: Appended content to file '" << name << "'." << endl;
}

void Files::Update(const string& name, const string& new_content) {
    File* ptr = Retriever(name);
    if(!ptr) return;
    if (ptr->active_version->isSnapshot()) {
        ptr->new_version();
        biggest_trees.push(ptr);
    }
    ptr->active_version->content = new_content;
    ptr->last_modified = ++counter;
    recent_files.push(ptr);
    cout << "Success: File '" << name << "' was updated." << endl;
}

void Files::Snapshot(const string& name, const string& message) {
    File* ptr = Retriever(name);
    if(!ptr) return;
    if (ptr->active_version->make_snapshot(message)) {
        ptr->last_modified = ++counter;
        recent_files.push(ptr);
        cout << "Success: Snapshot created for file '" << name << "' with message: '" << message << "'." << endl;
    }
}

void Files::Rollback(const string& name, const string& version_id) {
    File* ptr = Retriever(name);
    if(!ptr) return;
    if (version_id.empty()) {
        if (ptr->active_version->parent) {
            ptr->active_version = ptr->active_version->parent;
            cout << "Success: Rolled back to previous version for file '" << name << "'." << endl;
        } 
        else {
            cout << "Error: No previous version to rollback to for file '" << name << "'." << endl;
        }
    } else {
        try {
            int vid = stoi(version_id);
            if (vid >= 0 && vid < ptr->total_versions) {
                ptr->active_version = ptr->version_array[vid];
                cout << "Success: Rolled back file '" << name << "' to version ID " << vid << "." << endl;
            } 
            else {
                cout << "Error: Version ID " << vid << " not found for file '" << name << "'." << endl;
            }
        }
        catch (exception& e) { 
            cout << "Error: Invalid Version ID format." << endl;
        }
    }
}

void Files::History(const string& name) const {
    File* ptr = Retriever(name);
    if(!ptr) return;
    
    TreeNode* node = ptr->active_version;
    cout << "--- History for file: " << name << " ---" << endl;
    while (node) {
        if (node->isSnapshot()) {
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&(node->snapshot_timestamp)));
            cout << "ID: " << node->version_id << ", Snapshot Timestamp: " << buffer << ", Message: " << node->message << endl;
        }
        node = node->parent;
    }
}

void Files::Recent(int num) {
    if (num <= 0) { cout << "Error: Number of files must be positive." << endl; return; }
    
    cout << "--- Most Recently Modified Files ---" << endl;
    int count = 0;
    vector <File*> arr;

    while (!recent_files.empty() && count < num) {
        auto file = recent_files.top();
        if (file == nullptr) { recent_files.pop(); continue; } // Should not happen
        
        recent_files.pop();
        arr.push_back(file);
        cout << "Name: " << file->name << endl;
        count++;
    }
    if (count < num) cout << "There are less than " << num << " files" << endl;
    for(auto file : arr) recent_files.push(file);
}

void Files::Biggest(int num) {
    if (num <= 0) { cout << "Error: Number of files must be positive." << endl; return; }
    cout << "--- Files with largest version count ---" << endl;
    int count = 0;
    vector <File*> arr;
    while (!biggest_trees.empty() && count < num) {
        auto file = biggest_trees.top();
        if (file == nullptr) { biggest_trees.pop(); continue; }
        biggest_trees.pop();
        arr.push_back(file);
        cout << "Name: " << file->name << ", Total Versions: " << file->total_versions << endl;
        count++;
    }
    if (count < num) cout << "There are less than " << num << " files" << endl;
    for(auto file : arr) biggest_trees.push(file);
}

bool Files::interface() {
    string input_line;
    cout << "> "; 
    getline(cin, input_line); 
    if (input_line == "END") return false;
    if (input_line.empty()) return true;
    vector<string> input_split = split(input_line);
    if (input_split.empty()) return true;
    string command = input_split[0];
    try {
        if (command == "CREATE" && input_split.size() > 1) Create(input_split[1]);
        else if (command == "READ" && input_split.size() > 1) Read(input_split[1]);
        else if (command == "INSERT" && input_split.size() > 2) Insert(input_split[1], input_split[2]);
        else if (command == "UPDATE" && input_split.size() > 2) Update(input_split[1], input_split[2]);
        else if (command == "SNAPSHOT" && input_split.size() > 2) Snapshot(input_split[1], input_split[2]);
        else if (command == "ROLLBACK" && input_split.size() > 1) {
            if (input_split.size() > 2) Rollback(input_split[1], input_split[2]);
            else Rollback(input_split[1]);
        }
        else if (command == "HISTORY" && input_split.size() > 1) History(input_split[1]);
        else if (command == "RECENT_FILES" && input_split.size() > 1) Recent(stoi(input_split[1]));
        else if (command == "BIGGEST_TREES" && input_split.size() > 1) Biggest(stoi(input_split[1]));
        else cout << "Error: Invalid command or insufficient arguments." << endl;
    }
    catch (exception& e) { cout << "Error processing command: " << e.what() << endl; }
    return true;
}