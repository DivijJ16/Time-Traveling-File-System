#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "Tree.hpp"
#include "Hash_Map.hpp"
#include "Heap.hpp"
#include <iostream>
#include <ctime>
using namespace chrono;
using namespace std;

struct file_info
{
    string name_file;
    tree t;
    time_point<system_clock> modif_tm_lst;

    file_info(string &s)
    {
        name_file = s;
        modif_tm_lst = system_clock::now();
    }
};

class system_files
{
private:
    vector<file_info *> files;
    hashmap_string<file_info> file_map_string;
    max_heap<pair<time_point<system_clock>, string>> recent_heap;
    max_heap<pair<int, string>> biggest_heap;

public:
    ~system_files()
    {
        for (file_info *f : files)
        {
            delete f;
        }
    }

    void CREATE(string &name_file)
    {
        if (file_map_string.contains(name_file))
        {
            throw runtime_error("already a file with same name exists!");
        }
        file_info *f = new file_info(name_file);
        files.push_back(f);
        file_map_string.insert(name_file, f);
    }

    void READ(string &name_file)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.READ();
    }

    void INSERT(string &name_file, string &content)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.INSERT(content);
        node->modif_tm_lst = system_clock::now();
    }

    void UPDATE(string &name_file, string &content)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.UPDATE(content);
        node->modif_tm_lst = system_clock::now();
    }

    void SNAPSHOT(string &name_file, string &message)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.SNAPSHOT(message);
    }

    void ROLLBACK(string &name_file, int versionID = -1e9)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.ROLLBACK(versionID);
    }

    void HISTORY(string &name_file)
    {
        file_info *node = file_map_string.get(name_file);
        if (node == nullptr)
        {
            throw runtime_error("no such file exists!");
        }
        node->t.HISTORY();
    }

    void RECENT_FILES(int num)
    {
        recent_heap.clear();

        for (file_info *f : files)
        {
            recent_heap.push(make_pair(f->modif_tm_lst, f->name_file));
        }

        if (recent_heap.size() < num)
        {
            throw runtime_error("these many files aren't even available!");
        }

        cout << "Most recently modified files:" << endl;
        for (int i = 0; i < num && !recent_heap.empty(); i++)
        {
            auto top = recent_heap.pop();
            cout << top.second << endl;
        }
    }

    void BIGGEST_TREES(int num)
    {
        biggest_heap.clear();

        for (file_info *f : files)
        {
            biggest_heap.push(make_pair(f->t.get_total_versions(), f->name_file));
        }

        if (biggest_heap.size() < num)
        {
            throw runtime_error("these many files aren't even available!");
        }
        cout << "Files with most versions:" << endl;
        for (int i = 0; i < num && !biggest_heap.empty(); i++)
        {
            auto top = biggest_heap.pop();
            cout << top.second << " (versions: " << top.first << ")" << endl;
        }
    }
};

#endif