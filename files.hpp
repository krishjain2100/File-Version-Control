#pragma once
#include "hashmap.hpp"
#include "file_priority_queue.hpp"
#include "file.hpp"

using TimePriorityQueue = FilePriorityQueue<&File::last_modified, &File::recent_files_idx>;
using SizePriorityQueue = FilePriorityQueue<&File::total_versions, &File::biggest_trees_idx>;

struct Files {
    HashMap files;
    TimePriorityQueue recent_files;
    SizePriorityQueue biggest_trees;
    int count;

    Files();
    ~Files();

    File* Retriever(const std::string& name) const;
    void Create(const std::string& name);
    void Read(const std::string& name) const;
    void Insert(const std::string& name, const std::string& content_to_append);
    void Update(const std::string& name, const std::string& new_content);
    void Snapshot(const std::string& name, const std::string& message);
    void Rollback(const std::string& name, const std::string& version_id = "");
    void History(const std::string& name) const;
    void Recent(int num);
    void Biggest(int num);
    bool interface();
};