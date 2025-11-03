#pragma once
#include <vector>
#include <utility> 
#include "file.hpp" 

template <int File::*KeyMember, int File::*IdxMember>
struct FilePriorityQueue {
    std::vector<File*> arr;

    FilePriorityQueue() { 
        arr.push_back(nullptr);
    }

    int size() const { return (int)arr.size() - 1; }
    bool empty() const { return size() == 0; }
    File* top() const { return (size() >= 1) ? arr[1] : nullptr; }

    void up(int idx) {
        while (idx > 1) {
            int par = idx / 2;
            if (arr[idx]->*KeyMember > arr[par]->*KeyMember) {
                arr[idx]->*IdxMember = par;
                arr[par]->*IdxMember = idx;
                std::swap(arr[idx], arr[par]);
                idx = par;
            } 
            else break;
        }
    }

    void down(int idx) {
        int n = size();
        while (true) {
            int l = idx * 2, r = l + 1;
            if (l > n) break;
            int best = l;
            if (r <= n && arr[r]->*KeyMember > arr[l]->*KeyMember) best = r;
            if (arr[best]->*KeyMember > arr[idx]->*KeyMember) {
                arr[idx]->*IdxMember = best;
                arr[best]->*IdxMember = idx;
                std::swap(arr[best], arr[idx]);
                idx = best;
            } 
            else break;
        }
    }

    void push(File* file) {
        int pos = file->*IdxMember;
        if (pos) up(pos);
        else {
            arr.push_back(file);
            file->*IdxMember = size();
            up(size());
        }
    }

    void pop() {
        int n = size();
        if (n == 0) return;
        File* removed = arr[1];
        if (n == 1) {
            arr.pop_back();
            removed->*IdxMember = 0; 
            return;
        }
        arr[1] = arr.back();
        arr.pop_back();
        arr[1]->*IdxMember = 1;
        down(1);
        removed->*IdxMember = 0;
    }
};