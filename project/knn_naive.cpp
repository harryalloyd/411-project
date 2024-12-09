#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct node {
    int val;       // value of the point (0 or 1)
    double x; // X-coordinate
    double y; // Y-coordinate
    double distance; // Distance from the query point
};


bool comparison(node a, node b) { // Sort points by distance
    return (a.distance < b.distance);
}

int classifyAPoint(node arr[], int n, int k, node p) { // Calculate the distance from each point to the query
    for (int i = 0; i < n; i++) {
        arr[i].distance = sqrt(pow((arr[i].x - p.x), 2) 
        + pow((arr[i].y - p.y), 2));
    }

    sort(arr, arr + n, comparison); // Sort the array of points by distance using the comparison function

    int num_group0 = 0;
    int num_group1 = 0;

    for (int i = 0; i < k; i++) {
        if (arr[i].val == 0) {
            num_group0++;
        } else if (arr[i].val == 1) {
            num_group1++;
        }
    }

    if (num_group0 > num_group1) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    const int n = 11; 
    node arr[n] = {
        {0,1,12}, {0,2,5}, {1,5,3}, {1,3,2}, {0,3,6}, {1,7,2}, {1,6,1},
        {0,3,10}, {1,4,2},{0,2,11}, {1,2,5}
    };

   // Test case 1
    node query1 = {0, 10, 10}; // Query point
    int k1 = 3; // Number of neighbors 
    cout << "Test Case 1: Predicted class = " << classifyAPoint(arr, n, k1, query1) << endl;

    // Test case 2
    node query2 = {0, 3, 4}; 
    int k2 = 5; 
    cout << "Test Case 2: Predicted class = " << classifyAPoint(arr, n, k2, query2) << endl;

    // Test case 3
    node query3 = {0, 5, 5}; 
    int k3 = 3; 
    cout << "Test Case 3: Predicted class = " << classifyAPoint(arr, n, k3, query3) << endl;

    // Test case 4
    node query4 = {0, 7, 7}; 
    int k4 = 3; 
    cout << "Test Case 4: Predicted class = " << classifyAPoint(arr, n, k4, query4) << endl;

    // Test case 5
    node query5 = {0, 9, 8}; 
    int k5 = 5; 
    cout << "Test Case 5: Predicted class = " << classifyAPoint(arr, n, k5, query5) << endl;

    return 0;
}
