#include <iostream>
#include <iomanip>

using namespace std;

// recursive quicksort
void quicksort(double *arr, int left, int right) {
    int i = left, j = right;
    double tmp;
    double pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
}

//find median of the array
double findMedian(double *arr, int size) {
    quicksort(arr, 0, size - 1);
    double median;
    if (size % 2 == 0) {
        median = (arr[size / 2] + arr[size / 2 - 1]) / 2;
    } else {
        median = arr[size / 2];
    }
    return median;
}

int main() {
    int size;
    cout << "Enter the size of the array:";
    std::cin >> size;
    auto *arr = new double [size];
    std::cout << "Enter the elements of the array:";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    for (int i = 0; i < size; i++) {
        auto *arr1 = new double [i+1];
        for (int j = 0; j < i+1; j++) {
            arr1[j] = arr[j];
        }
        if (i == 0) {
            std::cout << "The median for first element is " << std::fixed << std::setprecision(1) << findMedian(arr1, i+1) << std::endl;
            delete[] arr1;
        }
        else{
            std::cout << "The median for first " << i+1 << " elements is "  << std::fixed << std::setprecision(1) << findMedian(arr1, i+1) << std::endl;
            delete[] arr1;
        }
    }
    delete[] arr;
    return 0;
}
