#include <iostream>
#include "Thanksgiving.cpp"
#include "qsort.h"

using namespace std;

template<class Comparator>
void static DoStringCompare(const std::string &s1, const std::string &s2, Comparator comp) {
    cout << comp(s1, s2) << endl;  // calls comp.operator()(s1,s2);
}

void printNice(std::vector<std::pair<int, int>> &result) {
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i].first << " " << result[i].second << endl;
    }
}

void testProblem1b() {
    vector<int> intTest = {3, 4, 2, 4, 1};
    const int size = 100;
    for (int i = 0; i < size; ++i) {
        intTest.push_back(rand() % size);
    }
    QuickSort(intTest, std::less<int>());
    for (int j = 0; j < intTest.size(); ++j) {
        cout << intTest[j] << " ";
    }
    cout << endl;
}

// void InterpolationTest() {
//     int arr[] = { 2, 4, 8,16,3200};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     int x = 16; // Element to be searched
//     int index = interpolationSearch(arr, n, x);

//     // If element was found
//     if (index != -1)
//         printf("Element found at index %d", index);
//     else
//         printf("Element not found.");
// }

void testProblem5() {
    vector<int> turkey1 = {};
    vector<int> turkey2 = {0};
    vector<int> turkey3 = {1};
    vector<int> turkey4 = {1, 2};
    vector<int> turkey5;
    for (int i = 0; i < 50; ++i) {
        turkey5.push_back(i);
    }
    vector<int> potatoes1 = {};
    vector<int> potatoes2 = {0};
    vector<int> potatoes3 = {5};
    vector<int> potatoes4 = {3, 8};
    vector<int> potatoes5;
    for (int i = 0; i < 50; ++i) {
        potatoes5.push_back(100 - i);
    }
    std::vector<std::pair<int, int>> result0
            = assignPlates(turkey1, potatoes1);
    std::vector<std::pair<int, int>> result1
            = assignPlates(turkey2, potatoes2);
    std::vector<std::pair<int, int>> result3
            = assignPlates(turkey3, potatoes3);
    std::vector<std::pair<int, int>> result4
            = assignPlates(turkey4, potatoes4);
    std::vector<std::pair<int, int>> result5
            = assignPlates(turkey5, potatoes5);

    printNice(result0);
    printNice(result1);
    printNice(result3);
    printNice(result4);
    printNice(result5);

    try {
        std::vector<std::pair<int, int>> result2
                = assignPlates(turkey1, potatoes2);
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

}

int main() {
    srand((0));
    if (1) {
//        testProblem1a();
//        testProblem1b();
//        InterpolationTest();
        testProblem5();
    }
}