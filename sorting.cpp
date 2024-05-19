#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void insertionSort(int arr[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

void heapify(int arr[], int N, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < N && arr[l] > arr[largest])
    largest = l;

  if (r < N && arr[r] > arr[largest])
    largest = r;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, N, largest);
  }
}

void heapSort(int arr[], int N) {
  for (int i = N / 2 - 1; i >= 0; i--)
    heapify(arr, N, i);

  for (int i = N - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void countSort(vector<int>& inputArray, int* outputArray, int N) {
  int M = *max_element(inputArray.begin(), inputArray.end());

  vector<int> countArray(M + 1, 0);

  for (int i = 0; i < N; i++)
    countArray[inputArray[i]]++;

  for (int i = 1; i <= M; i++)
    countArray[i] += countArray[i - 1];

  for (int i = N - 1; i >= 0; i--) {
    outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
    countArray[inputArray[i]]--;
  }
}

void merge(int array[], int tempArray[], int const left, int const mid, int const right) {
  int i = left, j = mid + 1, k = left;
    
  while (i <= mid && j <= right) {
    if (array[i] <= array[j]) {
      tempArray[k++] = array[i++];
    } else {
      tempArray[k++] = array[j++];
    }
  }
    
  while (i <= mid) {
    tempArray[k++] = array[i++];
  }
    
  while (j <= right) {
    tempArray[k++] = array[j++];
  }
    
  for (i = left; i <= right; i++) {
    array[i] = tempArray[i];
  }
}

void mergeSort(int array[], int tempArray[], int const begin, int const end){
  if (begin >= end)
    return;

  int mid = begin + (end - begin) / 2;
  mergeSort(array, tempArray, begin, mid);
  mergeSort(array, tempArray, mid + 1, end);
  merge(array, tempArray, begin, mid, end);
}

void mergeSortWrapper(int arr[], int N) {
  int* tempArray = new int[N];
  mergeSort(arr, tempArray, 0, N - 1);
  delete[] tempArray;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      ++i;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void quickSortWrapper(int arr[], int N) {
  quickSort(arr, 0, N - 1);
}

int readArrayFromFile(const string& filename, vector<int>& arr) {
  ifstream inputFile(filename);
  int number;
  while (inputFile >> number) {
    arr.push_back(number);
  }
  return arr.size();
}

int main() {
  vector<string> filenames = {"case1.txt", "case2.txt", "case3.txt", "case4.txt", "case5.txt"};

  for (const string& filename : filenames) {
    vector<int> arr;
    int N = readArrayFromFile(filename, arr);
        
    int* outputArray = new int[N];

    auto start = high_resolution_clock::now();
    countSort(arr, outputArray, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by counting sort to sort " << filename << ": "
      << duration.count() << " microseconds" << endl;

    delete[] outputArray;
  }

  for (const string& filename : filenames) {
    vector<int> arr;
    int N = readArrayFromFile(filename, arr);
    int* array = new int[N];
    copy(arr.begin(), arr.end(), array);

    auto start = high_resolution_clock::now();
    quickSortWrapper(array, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by quick sort to sort " << filename << ": "
      << duration.count() << " microseconds" << endl;

    delete[] array;
  }

  for (const string& filename : filenames) {
    vector<int> arr;
    int N = readArrayFromFile(filename, arr);

    int* array = new int[N];
    copy(arr.begin(), arr.end(), array);

    auto start = high_resolution_clock::now();
    mergeSortWrapper(array, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by merge sort to sort " << filename << ": "
      << duration.count() << " microseconds" << endl;

    delete[] array;
  }

  for (const string& filename : filenames) {
    vector<int> arr;
    int N = readArrayFromFile(filename, arr);
        
    int* array = arr.data();

    auto start = high_resolution_clock::now();
    heapSort(array, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by heap sort to sort " << filename << ": "
      << duration.count() << " microseconds" << endl;
  }

  for (const string& filename : filenames) {
    vector<int> arr;
    int N = readArrayFromFile(filename, arr);

    int* array = arr.data();

    auto start = high_resolution_clock::now();
    insertionSort(array, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by insertion sort to sort " << filename << ": "
      << duration.count() << " microseconds" << endl;
  }
  return 0;
}