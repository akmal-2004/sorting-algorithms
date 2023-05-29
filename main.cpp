#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;
random_device rnd;

vector<int> values;
vector<string> datasets = {"datasets/btc.csv", "datasets/issues.csv", "datasets/vaccinations.csv"};

auto start = high_resolution_clock::now(), stop = high_resolution_clock::now();
int bubble_sort_duration, insertion_sort_duration, heap_sort_duration, merge_sort_duration, quicksort_sort_duration, radix_sort_duration;


void read_data(string filename) {
    ifstream infile(filename);
    string line;
    values.clear(); // clear array to store values of new dataset

    // read line and push to array
    while (getline(infile, line)) {
        values.push_back(stoi(line));
    }
}


void bubble_sort(vector<int> &a, int N) {
    for (int n = N; n > 1; n --)
        for (int i = 1; i < n; i ++)
            if (a[i] < a[i - 1])
                swap(a[i], a[i - 1]);
}

void insertion_sort(vector<int> &a, int n) {
    for (int i = 0; i < n; i++) {
        int index = i;
        while (index > 0 && a[index] < a[index - 1]) {
            swap(a[index], a[index - 1]);
            index --;
        }
    }
}

void heap(vector<int> &a, int i, int n) {
    int mx_id;
    while(true) {
        mx_id = i;
        if (2 * i <= n && a[2 * i] > a[mx_id])
            mx_id = 2 * i;
        if (2 * i + 1 <= n && a[2 * i + 1] > a[mx_id])
            mx_id = 2 * i + 1;
        if (mx_id == i) break;
        swap(a[mx_id], a[i]);
        i = mx_id;
    }
}
void heap_sort(vector<int> &a, int n) {
    for (int i = n / 2; i >= 1; i --)
        heap(a, i, n);
    for (int i = n; i > 1; i --) {
        swap(a[i], a[1]);
        heap(a, 1, i - 1);
    } 
}

void merge_sort(vector<int> &a, int l, int r) {
    if (r - l < 2) return;
    int m = (l + r) / 2;

    merge_sort(a, l, m);
    merge_sort(a, m, r);

    int n = r - l;
    int *b = new int[n];
    for (int i = 0, u = l, v = m; i < n; i ++)
        b[i] = a[u == m      ? v ++ :
                 v == r      ? u ++ :
                a[u] <= a[v] ? u ++ :
                               v ++];

    for (int i = 0; i < n; i ++) a[l + i] = b[i];
    delete [] b;
}

void quick_sort(vector<int> &a, int L, int R) {
    if (R <= L) return;
    int pivot = a[rnd() % (R - L + 1) + L];
    int l = L, r = R;
    while (l <= r) {
        while (a[l] < pivot) l ++;
        while (a[r] > pivot) r --;
        if (l <= r) {
            swap(a[l], a[r]);
            l ++;
            r --;
        }
    }
    quick_sort(a, L, r);
    quick_sort(a, l, R);
}

int getMax(vector<int> &arr, int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
} 
void countSort(vector<int> &arr, int n, int exp) {
    int output[n];
    int i, count[10] = { 0 };
 
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void radix_sort(vector<int> &arr, int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


int main() {    
    for (auto dataset : datasets) {
        cout << "\n# dataset: " << dataset << endl;

        read_data(dataset);
        start = high_resolution_clock::now();
        bubble_sort(values, values.size());
        stop = high_resolution_clock::now();
        bubble_sort_duration = duration_cast<microseconds>(stop - start).count();

        read_data(dataset);
        start = high_resolution_clock::now();
        insertion_sort(values, values.size());
        stop = high_resolution_clock::now();
        insertion_sort_duration = duration_cast<microseconds>(stop - start).count();

        read_data(dataset);
        start = high_resolution_clock::now();
        heap_sort(values, values.size());
        stop = high_resolution_clock::now();
        heap_sort_duration = duration_cast<microseconds>(stop - start).count();

        read_data(dataset);
        start = high_resolution_clock::now();
        merge_sort(values, 0, values.size());
        stop = high_resolution_clock::now();
        merge_sort_duration = duration_cast<microseconds>(stop - start).count();

        read_data(dataset);
        start = high_resolution_clock::now();
        quick_sort(values, 0, values.size() - 1);
        stop = high_resolution_clock::now();
        quicksort_sort_duration = duration_cast<microseconds>(stop - start).count();

        read_data(dataset);
        start = high_resolution_clock::now();
        radix_sort(values, values.size());
        stop = high_resolution_clock::now();
        radix_sort_duration = duration_cast<microseconds>(stop - start).count();

        cout << "[bubble sort]    execution time: " << bubble_sort_duration << " microseconds" << endl;
        cout << "[insertion sort] execution time: " << insertion_sort_duration << " microseconds" << endl;
        cout << "[heap sort]      execution time: " << heap_sort_duration << " microseconds" << endl;
        cout << "[merge sort]     execution time: " << merge_sort_duration << " microseconds" << endl;
        cout << "[quick sort]     execution time: " << quicksort_sort_duration << " microseconds" << endl;
        cout << "[radix sort]     execution time: " << radix_sort_duration << " microseconds" << endl;
    }

    return 0;
}