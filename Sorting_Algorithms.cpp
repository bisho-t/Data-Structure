#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

bool compared_by_name;

class Student{
public:
    string id;
    string name;
    double gpa;

    Student(string id, string name, double gpa){
        this->id = id;
        this->name = name;
        this->gpa = gpa;
    }

    bool operator< (const Student& other) const{
        if(compared_by_name)
            return this->name < other.name;
        else
            return this->gpa < other.gpa;
    }
};

class Insertion_Sort{
public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        int n = arr.size();
        comparisons = 0;
        for (int i = 1; i < n; ++i) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && key < arr[j]) {
                arr[j + 1] = arr[j];
                --j;
                comparisons++;
            }
            arr[j + 1] = key;
        }
    }
};

class Selection_Sort{
public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        int n = arr.size();
        comparisons = 0;
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                comparisons++;
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }
};

class Bubble_Sort{
public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        int n = arr.size();
        comparisons = 0;
        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                comparisons++;
                if (arr[j+1] < arr[j]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }
};

class Shell_Sort{
public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        int n = arr.size();
        comparisons = 0;
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                    comparisons++;
                }
                arr[j] = temp;
            }
        }
    }
};

class Merge_Sort{
private:
    template<typename T>
    void merge(vector<T>& arr, int l, int m, int r, int& comparisons) {
        int n1 = m - l + 1;
        int n2 = r - m;

        vector<T> L(n1, Student("", "", 0)), R(n2, Student("", "", 0));

        for (int i = 0; i < n1; ++i)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            comparisons++;
            if (L[i] < R[j]) {
                arr[k] = L[i];
                ++i;
            } else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    template<typename T>
    void mergeSort(vector<T>& arr, int l, int r, int& comparisons) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m, comparisons);
            mergeSort(arr, m + 1, r, comparisons);
            merge(arr, l, m, r, comparisons);
        }
    }
public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        mergeSort(arr, 0, arr.size() - 1, comparisons);
    }
};

class Quick_Sort{
private:
    template<typename T>
    int partition(vector<T>& arr, int low, int high, int& comparisons) {
        int mid = low+(high-low)/2;
        T pivot = arr[mid];

        int cnt = 0;
        for (int i = low; i <= high; ++i) {
            comparisons++;
            if (arr[i] < pivot)
                cnt++;
        }
        int pivot_idx = low+cnt;
        swap(arr[mid], arr[pivot_idx]);

        for (int s = low, e = high; s < pivot_idx && high > pivot_idx ; ++s, --e) {
            while (arr[s] < pivot) {
                comparisons++;
                s++;
            }
            while (pivot < arr[e]) {
                comparisons++;
                e--;
            }

            if(s < pivot_idx && e > pivot_idx)
                swap(arr[s], arr[e]);
        }
        return pivot_idx;
    }

    template<typename T>
    void quickSort(vector<T>& arr, int low, int high, int& comparisons) {
        if (low < high) {
            int pivot = partition(arr, low, high, comparisons);
            quickSort(arr, low, pivot - 1, comparisons);
            quickSort(arr, pivot + 1, high, comparisons);
        }
    }

public:
    template<typename T>
    void sort(vector<T>& arr, int& comparisons) {
        quickSort(arr, 0, arr.size() - 1, comparisons);
    }
};


void writeinfiles(string path, vector<Student> students, bool append, string algo_name, duration<long long, ratio<1, 1000>> time, int comparisons){
    auto status = ios::in | ios::out | ios::app;

    if (!append)
        status = ios::in | ios::out | ios::trunc;

    fstream file(path.c_str(), status);

    if (file.fail()) {
        cout << "Can't open the file" << endl;
        return;
    }

    file << "Algorithm: " << algo_name << endl;
    file << "Running Time: " << (double)(time.count()) << " milliseconds" << endl;
    file << "Comparisons: " << comparisons << endl;
    for (int i = 0; i < students.size(); ++i) {
        file << students[i].name << endl;
        file << students[i].id << endl;
        file << students[i].gpa << endl;
    }
    file << endl;
}

void Sorting_Process(vector<Student> &students, string path){
    Insertion_Sort insertionSort;
    Selection_Sort selectionSort;
    Bubble_Sort bubbleSort;
    Shell_Sort shellSort;
    Merge_Sort mergeSort;
    Quick_Sort quickSort;

    vector<Student> copy;
    int comparisons = 0;
    copy = students;
    auto start = high_resolution_clock::now();
    insertionSort.sort(copy, comparisons);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, false, "Insertion Sort", duration, comparisons);

    comparisons = 0;
    copy = students;
    start = high_resolution_clock::now();
    selectionSort.sort(copy, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, true, "Selection Sort", duration, comparisons);

    comparisons = 0;
    copy = students;
    start = high_resolution_clock::now();
    bubbleSort.sort(copy, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, true, "Bubble Sort", duration, comparisons);

    comparisons = 0;
    copy = students;
    start = high_resolution_clock::now();
    shellSort.sort(copy, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, true, "Shell Sort", duration, comparisons);

    comparisons = 0;
    copy = students;
    start = high_resolution_clock::now();
    mergeSort.sort(copy, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, true, "Merge Sort", duration, comparisons);

    comparisons = 0;
    copy = students;
    start = high_resolution_clock::now();
    quickSort.sort(copy, comparisons);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    writeinfiles(path, copy, true, "Quick Sort", duration, comparisons);
}

int main() {
    ifstream inputFile("students.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return 0;
    }

    int numStudents;
    inputFile >> numStudents;

    vector<Student> students;

    for (int i = 0; i < numStudents; ++i) {
        string id, name, line;
        double gpa;

        getline(inputFile, line);
        getline(inputFile, name);
        getline(inputFile, id);
        inputFile >> gpa;
        students.push_back(Student(id, name, gpa));
    }
    inputFile.close();
//----------------------------------------------------------------------
    compared_by_name = true;
    Sorting_Process(students, "SortedByName.txt");
    compared_by_name = false;
    Sorting_Process(students, "SortedByGPA.txt");
    return 0;
}
