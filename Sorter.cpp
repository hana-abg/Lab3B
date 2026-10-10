#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Sorter {
public:
    void mergeSort (int arr[], int l, int r); // recursive
    void quickSort (int arr[], int low, int high); // last-element pivot
    void quickSortM3(int arr[], int low, int high); // median-of-three pivot
    void quickSort(int arr[], int low, int high, long long& comparisons); // counts comparisons
    void quickSortM3(int arr[], int low, int high, long long& comparisons); // counts comparisons
private:
    void merge(int arr[], int l, int m, int r);
    int partition (int arr[], int low, int high);
    int partitionM3(int arr[], int low, int high);
    int medianOfThree(int arr[], int low, int high); // returns pivot index
    int partition(int arr[], int low, int high, long long& comparisons);
    int partitionM3(int arr[], int low, int high, long long& comparisons);
    int medianOfThree(int arr[], int low, int high, long long& comparisons);
};

// Merge helper (provided),
// Splits the section at the middle index.
// Sorts each half.
// Uses merge to combine the sorted halves.
void Sorter::merge(int arr[], int l, int m, int r) { //l = first index of left half, m last index of left half
    int n1=m-l+1; // gets length of first half
    int n2 = r-m;  // gets length of second half            
    vector<int> L(n1), R(n2); //makes temp arrays

    for(int i=0; i<n1 ;i++) L[i]=arr[l+i]; // puts first half in L
    for(int j=0; j<n2 ;j++) R[j]=arr[m+1+j]; //puts right half in R

    int i=0,j=0,k=l; // i is 
    while(i<n1&&j<n2) arr[k++]=(L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) arr[k++]=L[i++];
    while(j<n2) arr[k++]=R[j++];
}

void Sorter::mergeSort(int arr[], int l, int r) { // splits array into smaller parts
    if (l >= r) return; 
    int m = (l + r) / 2; //middle of array

    mergeSort(arr, l, m); // takes first half
    mergeSort(arr, m + 1, r); // takes second half

    merge(arr, l, m, r); // combines the two sorted halves into one sorted section
}

int Sorter::partition(int arr[], int low, int high) {
    int pivot = arr[high]; // last number is the pivot
    int i = low - 1;      // tracks number that was <= pivot

    for (int j = low; j < high; j++) { // j is what moves through
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]); // put pivot in its final position
    return i + 1;               // return pivot's index
}

// Chooses the last number as the pivot.
// Uses partition to move numbers ≤ pivot before it and numbers > pivot after it. These parts aren’t necessarily equal halves.
// Sorts those two parts by calling quickSort again.
void Sorter::quickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int p = partition(arr, low, high); // place pivot and get its index

    quickSort(arr, low, p - 1);  // sort the part before the pivot
    quickSort(arr, p + 1, high); // sort the part after the pivot

}

int Sorter::medianOfThree(int arr[], int low, int high) {
     int mid = (low + high) / 2; //middle of array

    if (arr[low] > arr[mid]) //if first value bigger than mid swap
        swap(arr[low], arr[mid]);

    if (arr[low] > arr[high]) //if first value bigger than last swap
        swap(arr[low], arr[high]);

    if (arr[mid] > arr[high]) //if middle value bigger than last swap
        swap(arr[mid], arr[high]);

    // The three values are now ordered:
    // arr[low] <= arr[mid] <= arr[high]

    swap(arr[mid], arr[high]); // move the middle the last
    return high;              // return the pivot's position
}

int Sorter::partitionM3(int arr[], int low, int high) {
    medianOfThree(arr, low, high); // sets pivot at arr[high]
    return partition(arr, low, high);
}

void Sorter::quickSortM3(int arr[], int low, int high) {
  if (low >= high) return; 

    int p = partitionM3(arr, low, high); // choose median pivot, place it, get its index

    quickSortM3(arr, low, p - 1);  // sort left array (before the pivot)
    quickSortM3(arr, p + 1, high); // sort right array (after the pivot)
}

// Same functions but with a counter to see how many comparisons each sort makes
int Sorter::partition(int arr[], int low, int high, long long& comparisons) {
    int pivot = arr[high]; // last value is the pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++; // comparing arr[j] with the pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorter::quickSort(int arr[], int low, int high, long long& comparisons) {
    if (low >= high) return;

    int p = partition(arr, low, high, comparisons); // count comparisons while partitioning
    quickSort(arr, low, p - 1, comparisons);
    quickSort(arr, p + 1, high, comparisons);
}

int Sorter::medianOfThree(int arr[], int low, int high, long long& comparisons) {
    int mid = (low + high) / 2;

    comparisons++; // compare first and middle
    if (arr[low] > arr[mid])
        swap(arr[low], arr[mid]);

    comparisons++; // compare first and last
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);

    comparisons++; // compare middle and last
    if (arr[mid] > arr[high])
        swap(arr[mid], arr[high]);

    swap(arr[mid], arr[high]); // median becomes the pivot
    return high;
}

int Sorter::partitionM3(int arr[], int low, int high, long long& comparisons) {
    medianOfThree(arr, low, high, comparisons); // also count the median comparisons
    return partition(arr, low, high, comparisons);
}

void Sorter::quickSortM3(int arr[], int low, int high, long long& comparisons) {
    if (low >= high) return;

    int p = partitionM3(arr, low, high, comparisons);
    quickSortM3(arr, low, p - 1, comparisons);
    quickSortM3(arr, p + 1, high, comparisons);
}