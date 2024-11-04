/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Syed Ahmad Shah
 * Version     : 1.0
 * Date        : 11/2/2024
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor system
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    // go through all elements and count inversions
    long inversions = 0;
    for (int i = 0; i < length - 1; ++i) {
        for (int j = i + 1; j < length; ++j) {
            if (array[i] > array[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *tempArray = new int[length];
    long inversions = mergesort(array, tempArray, 0, length - 1);
    delete[] tempArray;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    // if there are 0 or 1 elements in the array, then there isn't any inversions
    if (low >= high) {
        return 0;
    }
    int mid = low + (high - low) / 2;
    long inversions = 0;
    // count the left and right parts
    inversions += mergesort(array, scratch, low, mid);
    inversions += mergesort(array, scratch, mid + 1, high);

    int left = low, right = mid + 1, index = low;
    // combine the two parts and count the inversions
    while (left <= mid && right <= high) {
        if (array[left] <= array[right]) {
            scratch[index++] = array[left++];
        } else {
            scratch[index++] = array[right++];
            inversions += (mid - left + 1);
        }
    }
    // if there are any elements left in the left half copy it
    while (left <= mid) {
        scratch[index++] = array[left++];
    }
    // if there are any elements right in the left half copy it
    while (right <= high) {
        scratch[index++] = array[right++];
    }
    // copy the merged arrayu back into the original array
    for (int i = low; i <= high; ++i) {
        array[i] = scratch[i];
    }

    return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc > 1 && string(argv[1]) != "slow") {
        if(string(argv[1]) == "average"){
        cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
        }
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if (values.empty()) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    int length = values.size();
    if (argc > 1 && string(argv[1]) == "slow") {
        // Run slow
        long inversions = count_inversions_slow(&values[0], length);
        cout << "Number of inversions (slow): " << inversions << endl;
    } else {
        // Run fast
        long inversions = count_inversions_fast(&values[0], length);
        cout << "Number of inversions (fast): " << inversions << endl;
    }


    return 0;
}
