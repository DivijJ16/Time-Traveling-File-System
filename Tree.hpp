#ifndef tree_hpp
#define tree_hpp
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <optional>
#include "Hash_Map.hpp"
#include "Heap.hpp"
using namespace std;
using namespace chrono;

struct treenode
{
    int version_id;
    string content;
    string message;
    time_point<system_clock> created_timestamp;
    optional<time_point<system_clock>> snapshot_timestamp; // Null if not a snapshot
    treenode *par;
    vector<treenode *> children;

    treenode(int id, treenode *parent = nullptr)
    {
        version_id = id;
        content = "";
        message = "";
        created_timestamp = system_clock::now();
        par = parent;
    }

    void take_snapshot(string msg = "this is a snapshot!")
    {
        snapshot_timestamp = system_clock::now();
        message = msg;
    }
};

class tree
{
private:
    treenode *root;
    treenode *active_version;
    hashmap_int<treenode> version;
    int total_versions;
    max_heap<pair<time_point<system_clock>, treenode *>> hist;

public:
    tree()
    {
        root = new treenode(0);
        root->take_snapshot();
        active_version = root;
        version.insert(0, root);
        total_versions = 1;
    }
    void READ()
    {
        cout << active_version->content << endl;
    }

    void INSERT(string &content)
    {
        if (active_version->snapshot_timestamp.has_value())
        {
            treenode *child = new treenode(total_versions, active_version);
            version.insert(total_versions, child);
            total_versions = total_versions + 1;
            active_version->children.push_back(child);
            active_version = child;
            active_version->content = content;
        }
        else
        {
            active_version->content += content;
        }
    }

    void UPDATE(string &content)
    {
        if (active_version->snapshot_timestamp.has_value())
        {
            treenode *child = new treenode(total_versions, active_version);
            version.insert(total_versions, child);
            total_versions = total_versions + 1;
            active_version->children.push_back(child);
            active_version = child;
            active_version->content = content;
        }
        else
        {
            active_version->content = content;
        }
    }

    void SNAPSHOT(string &message)
    {
        if (active_version->snapshot_timestamp.has_value())
        {
            throw runtime_error("already a snapshot!");
        }
        active_version->take_snapshot(message);
    }

    void ROLLBACK(int versionID = -1e9)
    {
        if (versionID == -1e9)
        {
            if (active_version->par != nullptr)
            {
                active_version = active_version->par;
                return;
            }
            else
            {
                throw runtime_error("No parent exists!");
            }
        }
        else if (versionID >= total_versions || versionID < 0)
        {
            throw runtime_error("This ID DNE!");
        }
        active_version = version.get(versionID);
    }

    void HISTORY()
    {
        hist.clear();
        treenode *curr = active_version;
        while (curr != nullptr)
        {
            if (curr->snapshot_timestamp.has_value())
            {
                hist.push({curr->snapshot_timestamp.value(), curr});
            }
            curr = curr->par;
        }
        // i'm printing the nodes on basis of their snapshotted timestamps chronology...
        while (hist.size())
        {
            time_t snapshotted_time = system_clock::to_time_t((hist.top().first));
            cout << "Version_ID : " << (hist.top().second)->version_id << ", Snapshotted Timestamp : " << ctime(&snapshotted_time) << ", Message : " << hist.top().second->message << endl;
            hist.pop();
        }
    }

    int get_total_versions()
    {
        return total_versions;
    }
};

#endif