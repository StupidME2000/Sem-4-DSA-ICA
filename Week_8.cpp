#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void displayArray(vector<int>& arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> heap_arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> heap_arr[i];

    cout << "Input array: ";
    displayArray(heap_arr, n);

    heapSort(heap_arr, n);

    cout << "Sorted array: ";
    displayArray(heap_arr, n);

    return 0;
}
