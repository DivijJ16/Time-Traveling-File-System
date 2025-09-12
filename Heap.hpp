#ifndef Heap_hpp
#define Heap_hpp
#include<iostream>
#include <vector>
#include <stdexcept> // for runtime error
using namespace std;

template <typename T>
class max_heap
{
private:
    vector<T> a;

public:
    void heapify(int i)
    {
        int size = a.size();
        while ((2 * i + 1) < size)
        {
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int max_child_idx = left_child;
            if (right_child < size && a[right_child] > a[left_child])
            {
                max_child_idx = right_child;
            }

            if (a[i] < a[max_child_idx])
            {
                swap(a[i], a[max_child_idx]);
                i = max_child_idx;
            }
            else
            {
                break;
            }
        }
    }

    void build(vector<T> &v)
    {
        a = v;
        for (int i = (a.size() / 2) - 1; i >= 0; i--) // since bottom layer is as it is
        {
            heapify(i);
        }
    }

    void push(T x)
    {
        a.push_back(x);
        int i = a.size() - 1;
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (a[parent] < a[i])
            {
                swap(a[i], a[parent]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    T pop()
    {
        if (a.empty())
        {
            throw runtime_error("Heap is empty!");
        }
        T x = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty())
        {
            heapify(0);
        }
        return x;
    }

    T top()
    {
        if (a.empty())
        {
            throw runtime_error("Heap is empty!");
        }
        return a[0];
    }

    bool empty() { return a.empty(); }
    int size() { return a.size(); }
    void clear() { a.clear(); }
};

#endif
