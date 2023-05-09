#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

int* generateRandomArray(int size){
    int* arr = new int[size];
    srand(time(NULL)); // seed the random number generator
    for(int i=0; i<size; i++){
        arr[i] = rand(); // generate a random number
    }
    return arr;
}

void insertionSort(int arr[], int n){
    int key, j;
    for(int i=1; i<n; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

double getExecutionTimeInsertionSort(int arr[], int n){
    auto start = high_resolution_clock::now(); // Get the start time

    insertionSort(arr, n); // Sort the array

    auto stop = high_resolution_clock::now(); // Get the stop time
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate the duration in nanoseconds
    return duration.count() / 1000000.0; // Convert duration to milliseconds and return
}


void bubbleSort_unoptimized(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

double getExecutionTimeBubbleSort_unoptimized(int arr[], int n){
    auto start = high_resolution_clock::now(); // Get the start time

    bubbleSort_unoptimized(arr, n); // Sort the array

    auto stop = high_resolution_clock::now(); // Get the stop time
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate the duration in nanoseconds
    return duration.count() / 1000000.0; // Convert duration to milliseconds and return
}

void bubbleSort_optimized(int arr[], int n){
    bool swapped;
    for(int i=0; i<n-1; i++){
        swapped = false;
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

double getExecutionTimeBubbleSort_optimized(int arr[], int n){
    auto start = high_resolution_clock::now(); // Get the start time

    bubbleSort_optimized(arr, n); // Sort the array using Bubble Sort

    auto stop = high_resolution_clock::now(); // Get the stop time
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate the duration in nanoseconds
    return duration.count() / 1000000.0; // Convert duration to milliseconds and return
}


void selectionSort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        int minIndex = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex != i){
            swap(arr[i], arr[minIndex]);
        }
    }
}

double getExecutionTimeSelectionSort(int arr[], int n){
    auto start = high_resolution_clock::now(); // Get the start time

    selectionSort(arr, n); // Sort the array

    auto stop = high_resolution_clock::now(); // Get the stop time
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate the duration in nanoseconds
    return duration.count() / 1000000.0; // Convert duration to milliseconds and return
}

double* getExecutionTimeAll(int arr[], int n){
    double* arr_new = new double [4];
    arr_new[0] = getExecutionTimeInsertionSort(arr, n);
    arr_new[1] = getExecutionTimeBubbleSort_unoptimized(arr, n);
    arr_new[2] = getExecutionTimeBubbleSort_optimized(arr, n);
    arr_new[3] = getExecutionTimeSelectionSort(arr, n);
    return arr_new;
}

void printArray(double arr[]){
    for(int i = 0; i<4; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}


void writeArrayToCsv(double arr[], int size, std::ofstream& file) {
    for (int i = 0; i < size; i++) {
        file << arr[i];
        if (i < size - 1) {
            file << ",";
        }
    }
    file << std::endl;
}



int main() {
    int size[5] = {500,1000,5000,12000,20000};
    int *arr_1= generateRandomArray(size[0]);
    int *arr_2= generateRandomArray(size[1]);
    int *arr_3= generateRandomArray(size[2]);
    int *arr_4= generateRandomArray(size[3]);
    int *arr_5= generateRandomArray(size[4]);

    double *arr_1_ex= getExecutionTimeAll(arr_1, size[0]);
    double *arr_2_ex= getExecutionTimeAll(arr_2, size[1]);
    double *arr_3_ex= getExecutionTimeAll(arr_3, size[2]);
    double *arr_4_ex= getExecutionTimeAll(arr_4, size[3]);
    double *arr_5_ex= getExecutionTimeAll(arr_5, size[4]);

    printArray(arr_1_ex);
    printArray(arr_2_ex);
    printArray(arr_3_ex);
    printArray(arr_4_ex);
    printArray(arr_5_ex);

//    add_arrays_to_spreadsheet(arr_1_ex,arr_2_ex,arr_3_ex,arr_4_ex,arr_5_ex,"output");

    std::ofstream file("data.csv");
    writeArrayToCsv(arr_1_ex, 4, file);
    writeArrayToCsv(arr_2_ex, 4, file);
    writeArrayToCsv(arr_3_ex, 4, file);
    writeArrayToCsv(arr_4_ex, 4, file);
    writeArrayToCsv(arr_5_ex, 4, file);




}

