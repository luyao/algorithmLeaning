#if 0
~/bin/g++ -std=c++0x -o `echo $0 |sed -e 's/\..*//'` -g $0
exit
#endif
/**
 * @file kindsOfSorts.cpp
 * @author Yao Lu(yaolu1103@gmail.com)
 * @date 2014/04/12 20:57:42
 * @version 1.0 
 * @brief 
 **/

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>

using namespace std;

void initVector(vector<int> &vec, int count)
{
    vec = vector<int>(count, 0);
    generate(vec.begin(), vec.end(), []{return (std::rand()%10);});
}

void printVector(const vector<int> &vec)
{
    for_each(vec.begin(), vec.end(), [](const int& val)
    {
        cout<<val<<" ";
    });
    cout<<endl;
}

int sortTemplate(const function<int(vector<int>&)> &handle,
                 const string &name, size_t len, vector<int> &vec)
{
    initVector(vec, len);
    cout<<__FUNCTION__<<":"<<name<<endl<<"before sort the array is:"<<endl;
    printVector(vec);
    if(len > 1)handle(vec);
    cout<<"After sort the array is:\n";
    printVector(vec);
}

int insertSort(vector<int> &vec)
{
    for (size_t i=1; i<vec.size();++i) {
        int key = vec.at(i);
        int j = i-1;
        while (j>=0 && vec.at(j) > key) vec[j+1] = vec[j--];  //move the card
        vec[j+1] = key;  //set the value to the position
    }
    return 0;
}

int bubbleSort(vector<int> &vec)
{
    for (size_t i=0; i<vec.size(); ++i) {
        bool flag = false;
        for (size_t j=0; j<vec.size()-i; ++j) {
            if (vec[j] > vec[j+1]) {
                swap(vec[j+1], vec[j]);
                flag = true;
            }
        }
        if (!flag) break;
    }
    return 0;
}

int mergeSort(vector<int> &vec)
{
    return 0;
}

int quickSort(vector<int> &vec, const vector<int>::iterator &bg,
              const vector<int>::iterator &end)
{
    printVector(vec);
    if (vec.empty() || bg == end) return 0;
    auto key = vec[0];
    auto bound = partition(bg, end, [&key](const int &val)->bool{
        return  val < key;
    });
    quickSort(vec, bg, bound);
    quickSort(vec, bound, end);
    return 0;
}

int bucketSort(vector<int> &vec)
{
    return 0;
}

#define SORT_TEMPLATE(function, vec, len) do{   \
    sortTemplate(function, #function, len, vec);\
}while(0);

int main()
{
    vector<int> vec;

    SORT_TEMPLATE(insertSort, vec, 10);

    SORT_TEMPLATE(bubbleSort, vec, 10);    

    initVector(vec, 10);
    printVector(vec);
    quickSort(vec, vec.begin(), vec.end());
    printVector(vec);
    return 0;
}








/* vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet: */
