//#include <iostream>
//#include <thread>
//#include <random>
//#include <vector>
//#include <algorithm>
//#include <cmath>
//#include <chrono>
//
//
//using namespace std;
//using namespace std::chrono;
//
//
//void printArr(std::vector<int>& arr)
//{
//    for (int& item: arr)
//    {
//        cout << item << " ";
//    }
//    cout << endl;
//}
//
//
//void normalPrefixSum(std::vector<int>& arr)
//{
//    for (size_t i = 1; i < arr.size(); ++i)
//    {
//        arr[i] += arr[i-1];
//    }
//}
//
//
//void summator2(int start, int end, int level,  int coreNumber, std::vector<int>& arr){
//    //    printArr(arr);
//    int step = pow(2, level) - 1;
//    for (int i = start + step; i <= end; i+= step)
//    {
//        arr[i] = arr[i] + arr[i - step];
//    }
//}
//
//
//
//void down_summator2(int start , int end, int step, int step_1, std::vector<int>& arr){
//    ;
//}
//
//
//void parallelPrefixSum2(std::vector<int>& arr,int n)
//{
//    int length = arr.size();
//    
//    //Why log2?
//    int coreCount = std::thread::hardware_concurrency();
//    size_t depth = log2 (length);
//    
//    for(size_t level = 1; level < depth+1; level++) {
//        
//        std::thread t[coreCount];
//        
//        int itemsPerCore = pow(2, level);
//        int start = 0;
//        int end = 0;
//        
//        for(int i = 0; i < coreCount; i++)
//        {
//            start = itemsPerCore * i;
//            end = start + itemsPerCore - 1;
//            cout<<"Start "<<start<<endl;
//            cout<<"End "<<end<<endl;
//            t[i] = std::thread(summator2, start, end, level, i, std::ref(arr));
//        }
//        for (int i = 0; i < coreCount; ++i) {
//            t[i].join();
//        }
//        printArr(arr);
//    }
//    
//    arr[length -1] = arr[length -2];
//    arr[length -2] = 0;
//    
//    for(size_t level = depth; level > 0; level--) {
//        
//        std::thread t[coreCount];
//        for(int i = 0; i < coreCount; i++)
//        {
//            //Add code here!
//            //Modify!!!
//            int start = 0; int end = 0; int step = 0; int step1 = 1;
//            t[i] = std::thread(down_summator2, start, end, step, step1, std::ref(arr));
//        }
//        for (int i = 0; i < coreCount; ++i) {
//            t[i].join();
//        }
//    }
//}
//
////int main()
////{
////    unsigned int n = std::thread::hardware_concurrency();
////    std::cout << n << " concurrent threads are supported.\n";
////    
////    //test in on random. But later.
////    std::random_device rd;
////    std::mt19937 gen(rd());
////    std::uniform_int_distribution<> dis(1, 1000);
////    //Do you see +1? Why we need it?
////    //Try to start from 2^3 and uncomment printArr for each iteration
////    size_t size = std::pow (2, 3)+1;
////    std::vector<int> copy1 {0, 1, 2, 3, 4, 5, 6, 7} ;
////    
////    //For now let's test only on '1'
////    high_resolution_clock::time_point start1 = high_resolution_clock::now();
////    parallelPrefixSum2(copy1, n);
////    high_resolution_clock::time_point end1 = high_resolution_clock::now();
////    
////    //printArr(copy1);
////    cout << "parallelPrefixSum execution time " << duration_cast<microseconds>( end1 - start1 ).count() << endl;
////    
////    
////    std::generate(copy1.begin(), copy1.end()-1, [&](){return 1;});
////    //printArr(copy2);
////    high_resolution_clock::time_point start2 = high_resolution_clock::now();
////    normalPrefixSum(copy1);
////    high_resolution_clock::time_point end2 = high_resolution_clock::now();
////    //printArr(copy2);
////    
////    cout << "normalPrefixSum execution time " << duration_cast<microseconds>( end2 - start2 ).count() << endl;
////    
////    std::cout.flush();
////}
////

