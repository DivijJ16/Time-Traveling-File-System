#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>

using namespace std;

// modulo hash
int hash_int(int key)
{
    return key;
}

// djb2 hash function
int hash_string(const string &key)
{
    long long hash = 5381;
    for (unsigned char c : key)
    {
        hash = hash * 33 + c;
        hash %= 1000000007;
    }
    return (hash);
}

template <typename T>
class hashmap_int
{
private:
    int TABLE_SIZE = 10000;
    vector<vector<pair<int, T *>>> table;

public:
    hashmap_int()
    {
        table.resize(TABLE_SIZE);
    }

    void insert(int key, T *value)
    {
        int index = hash_int(key) % TABLE_SIZE;
        for (auto &pair : table[index])
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    T *get(int key)
    {
        int index = hash_int(key) % TABLE_SIZE;
        for (auto &pair : table[index])
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }
        return nullptr;
    }

    bool contains(int key)
    {
        return get(key) != nullptr;
    }
};

template <typename T>
class hashmap_string
{
private:
    int TABLE_SIZE = 10000;
    vector<vector<pair<string, T *>>> table;

public:
    hashmap_string()
    {
        table.resize(TABLE_SIZE);
    }

    ~hashmap_string()
    {
    }

    void insert(const string &key, T *value)
    {
        int index = (hash_string(key) % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
        for (auto &pair : table[index])
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    T *get(const string &key)
    {
        int index = (hash_string(key) % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
        for (const auto &pair : table[index])
        {
            if (pair.first == key)
            {
                return pair.second;
            }
        }
        return nullptr;
    }

    bool contains(const string &key)
    {
        return get(key) != nullptr;
    }
};

#endif