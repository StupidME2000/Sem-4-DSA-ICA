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

//recursive quick sort
int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortRecursive(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);

        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

//iterative quick sort
void quickSortIterative(int arr[], int low, int high){
    int stack[high - low + 1];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while(top >= 0){
        high = stack[top--];
        low = stack[top--];

        int pi = partition(arr, low, high);

        if(pi - 1 > low){
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if(pi + 1 < high){
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

//get Execution Time in millisecond Quick Sort Recursive
double getExecutionTimeQuickSortRecursive(int arr[], int size){
    auto start = chrono::high_resolution_clock::now();
    quickSortRecursive(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count()/ 1000000.0;
}

//get Execution Time in millisecond Merge Sort Iterative
double getExecutionTimeQuickSortIterative(int arr[], int size){
    auto start = chrono::high_resolution_clock::now();
    quickSortIterative(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count()/ 1000000.0;
}

//Write to CSV file Array Size and Execution Time for Quick Sort Recursive and Iterative
void writeToFile(int size[], double timeMergeSortRecursive[], double timeMergeSortIterative[], string const& fileName){
    ofstream file;
    file.open(fileName);
    file << "Array Size, quick Sort Recursive, quick Sort Iterative" << endl;
    for(int i = 0; i < 10; i++){
        file << size[i] << "," << timeMergeSortRecursive[i] << "," << timeMergeSortIterative[i] << endl;
    }
    file.close();
}

int main() {
    int const number_of_arrays = 10;
    int size_of_array[number_of_arrays] = {100,500,1000,2000,4000,8000,12000,16000, 20000, 30000};

    double executionTimeQuickSortRecursive_Random[number_of_arrays];
    double executionTimeQuickSortIterative_Random[number_of_arrays];

    double executionTimeQuickSortRecursive_Worst[number_of_arrays];
    double executionTimeQuickSortIterative_Worst[number_of_arrays];


    for(int i = 0; i<number_of_arrays; i++){
        int *random_array = generateRandomArray(size_of_array[i]);
        executionTimeQuickSortRecursive_Random[i] = getExecutionTimeQuickSortRecursive(random_array, size_of_array[i]);
        executionTimeQuickSortIterative_Random[i] = getExecutionTimeQuickSortIterative(random_array, size_of_array[i]);

        int *decendingArray = generateDecreasingArray(size_of_array[i]);
        executionTimeQuickSortRecursive_Worst[i] = getExecutionTimeQuickSortRecursive(decendingArray, size_of_array[i]);
        executionTimeQuickSortIterative_Worst[i] = getExecutionTimeQuickSortIterative(decendingArray, size_of_array[i]);

    }

    writeToFile(size_of_array, executionTimeQuickSortRecursive_Worst, executionTimeQuickSortIterative_Worst, "QuickSortWorst.csv");
    writeToFile(size_of_array, executionTimeQuickSortRecursive_Random, executionTimeQuickSortIterative_Random, "QuickSortRandom.csv");


    return 0;

}


