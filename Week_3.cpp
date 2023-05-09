#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;


//Generate a Array with Random Values
int* generateRandomArray(int size){
    int* arr = new int[size];
    srand(time(NULL)); // seed the random number generator
    for(int i=0; i<size; i++){
        arr[i] = rand(); // generate a random number
    }
    return arr;
}

//Generate Decreasing Array
int* generateDecreasingArray(int size){
    int* arr = new int[size];
    for(int i=0; i<size; i++){
        arr[i] = size - i;
    }
    return arr;
}

//Merge Sort Recursive
void mergeRecursive(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortRecursive(int arr[], int l, int r){
    if(l < r){
        int m = l + (r - l) / 2;

        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);

        mergeRecursive(arr, l, m, r);
    }
}

//Merge Sort Iterative
void mergeIterative(int arr[], int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortIterative(int arr[], int n){
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            mergeIterative(arr, left_start, mid, right_end);
        }
    }
}



//get Execution Time in millisecond Merge Sort Recursive
double getExecutionTimeMergeSortRecursive(int arr[], int size){
    auto start = chrono::high_resolution_clock::now();
    mergeSortRecursive(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count()/ 1000000.0;
}

//get Execution Time in millisecond Merge Sort Iterative
double getExecutionTimeMergeSortIterative(int arr[], int size){
    auto start = chrono::high_resolution_clock::now();
    mergeSortIterative(arr, size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count()/ 1000000.0;
}

//Write to CSV file Array Size and Execution Time for Merge Sort Recursive and Iterative
void writeToFile(int size[], double timeMergeSortRecursive[], double timeMergeSortIterative[], string const& fileName){
    ofstream file;
    file.open(fileName);
    file << "Array Size, Merge Sort Recursive, Merge Sort Iterative" << endl;
    for(int i = 0; i < 10; i++){
        file << size[i] << "," << timeMergeSortRecursive[i] << "," << timeMergeSortIterative[i] << endl;
    }
    file.close();
}

//print array
void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    int const number_of_arrays = 10;
    int size_of_array[number_of_arrays] = {100,500,1000,2000,4000,8000,12000,16000, 20000, 30000};

    double executionTimeMergeSortRecursive_Random[number_of_arrays];
    double executionTimeMergeSortIterative_Random[number_of_arrays];

    double executionTimeMergeSortRecursive_Worst[number_of_arrays];
    double executionTimeMergeSortIterative_Worst[number_of_arrays];


    for(int i = 0; i<number_of_arrays; i++){
        int *random_array = generateRandomArray(size_of_array[i]);
        executionTimeMergeSortRecursive_Random[i] = getExecutionTimeMergeSortRecursive(random_array, size_of_array[i]);
        executionTimeMergeSortIterative_Random[i] = getExecutionTimeMergeSortIterative(random_array, size_of_array[i]);

        int *decendingArray = generateDecreasingArray(size_of_array[i]);
        executionTimeMergeSortRecursive_Worst[i] = getExecutionTimeMergeSortRecursive(decendingArray, size_of_array[i]);
        executionTimeMergeSortIterative_Worst[i] = getExecutionTimeMergeSortIterative(decendingArray, size_of_array[i]);

    }

    writeToFile(size_of_array, executionTimeMergeSortRecursive_Worst, executionTimeMergeSortIterative_Worst, "mergeSortWorst.csv");
    writeToFile(size_of_array, executionTimeMergeSortRecursive_Random, executionTimeMergeSortIterative_Random, "mergeSortRandom.csv");


    return 0;
}
