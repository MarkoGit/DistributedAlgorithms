//
//  PrefixSum.cpp
//  distributed_algorithms
//
//  Created by Markiyan Kostiv on 3/8/18.
//  Copyright © 2018 Cardo Systems. All rights reserved.
//

#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>


using namespace std;
using namespace std::chrono;

void printArr(std::vector<int>& arr)
{
    cout << endl;
    for (int& item: arr)
    {
        cout << item << " ";
    }
    cout << endl;
}


void normalPrefixSum(std::vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        arr[i] += arr[i-1];
    }
}


void summator2(int start, int end, int level,  int coreNumber, std::vector<int>& arr){
    arr[start] += arr[end];
}



void down_summator2(int start , int end, int step, int step_1, std::vector<int>& arr){
    int temp =  arr[start];
    arr[start] += arr[end];
    arr[end] = temp;
}


void parallelPrefixSum2(std::vector<int>& arr,int n)
{
    int length = arr.size();
    
    //Why log2?
    int coreCount = std::thread::hardware_concurrency();
    size_t depth = log2 (length);
    
    for(size_t level = 0; level < depth; level++) {
        
        std::vector<std::thread> t;
        
        size_t works = std::pow (2, depth - level - 1);
        int itemsPerCore = pow(2, level + 1);
        int start = 0;
        int end = 0;
        
        for(int i = 0; i < works; i++)
        {
            int begin = i*itemsPerCore;
            int start = begin + itemsPerCore - 1;
            int end = begin + itemsPerCore/2 - 1;
            t.push_back(std::thread(summator2, start, end, level, i, std::ref(arr)));
        }
        for (int i = 0; i < works; ++i) {
            t[i].join();
        }
    }
    
    arr[length - 1] = 0;
    
    for(int level = depth - 1; level >= 0; level--) {
        
        std::vector<std::thread> t;
        
        int works = std::pow (2, depth - level - 1);
        int itemsPerCore = pow(2, level + 1);
        
        for(int i = 0; i < works; i++)
        {
            int begin = i*itemsPerCore;
            int start = begin + itemsPerCore - 1;
            int end = begin + itemsPerCore/2 - 1;
            
            t.push_back(std::thread(summator2, start, end, level, i, std::ref(arr)));
        }
        for (int i = 0; i < works; ++i) {
            t[i].join();
        }
    }

    printArr(arr);
}

void prefixSumCompare() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    //test in on random. But later.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    //Do you see +1? Why we need it?
    //Try to start from 2^3 and uncomment printArr for each iteration
    size_t size = std::pow (2, 3)+1;
    std::vector<int> arr(size);
    std::generate(arr.begin(), arr.end(), [&](){return 1/*dis(gen)*/;});
    std::vector<int> copy1(arr.begin(), arr.end());

    //For now let's test only on '1'
    high_resolution_clock::time_point start1 = high_resolution_clock::now();
    parallelPrefixSum2(copy1, n);
    high_resolution_clock::time_point end1 = high_resolution_clock::now();

    //printArr(copy1);
    cout << "parallelPrefixSum execution time " << duration_cast<microseconds>( end1 - start1 ).count() << endl;


    std::generate(copy1.begin(), copy1.end()-1, [&](){return 1;});
    //printArr(copy2);
    high_resolution_clock::time_point start2 = high_resolution_clock::now();
//    normalPrefixSum(copy1);
    high_resolution_clock::time_point end2 = high_resolution_clock::now();
    //printArr(copy2);

    cout << "normalPrefixSum execution time " << duration_cast<microseconds>( end2 - start2 ).count() << endl;

    std::cout.flush();
}

