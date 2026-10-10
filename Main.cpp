#include <iostream>
#include <vector>
#include "Sorter.cpp" // makes Sorter available here
using namespace std;

int main() {
    Sorter s; int tmp[8];
    int a[] = {64,25,12,22,11,90,45,34}; int n=8;

    // mergeSort
    copy(a,a+n,tmp); s.mergeSort(tmp,0,n-1);
    cout<<"MS: "; for(int x:tmp) cout<<x<<" "; cout<<endl;

    // quickSort
    copy(a,a+n,tmp); s.quickSort(tmp,0,n-1);
    cout<<"QS: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
    
    // worst-case for quickSort: sorted array
    int sorted[] = {1,2,3,4,5,6,7,8};

    copy(sorted,sorted+n,tmp); s.quickSort(tmp,0,n-1);
    cout<<"QS sorted: "; for(int x:tmp) cout<<x<<" "; cout<<endl;

    // quickSortM3 on same sorted array
    copy(sorted,sorted+n,tmp); s.quickSortM3(tmp,0,n-1);
    cout<<"QSM3 sorted: "; for(int x:tmp) cout<<x<<" "; cout<<endl;
    // Section 3: compare both quick sorts using arrays of 16 values
    int randomArr[16] = {12, 5, 9, 1, 15, 3, 8, 14, 2, 11, 6, 16, 4, 10, 13, 7};
    int sortedArr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int reverseArr[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int* tests[3] = {randomArr, sortedArr, reverseArr};
    string names[3] = {"Random", "Sorted", "Reverse sorted"};

    cout << "\nInput type | QS | QSM3 | Better?" << endl;
    for (int t = 0; t < 3; t++) {
        int arr1[16], arr2[16]; // copies so both algorithms get the same input
        copy(tests[t], tests[t] + 16, arr1);
        copy(tests[t], tests[t] + 16, arr2);
        long long qsCount = 0, m3Count = 0; // start counters at zero

        s.quickSort(arr1, 0, 15, qsCount);
        s.quickSortM3(arr2, 0, 15, m3Count);

        cout << names[t] << " | " << qsCount << " | " << m3Count << " | ";
        if (qsCount < m3Count) cout << "QS";
        else if (m3Count < qsCount) cout << "QSM3";
        else cout << "Same";
        cout << endl;
    }
    return 0;
}