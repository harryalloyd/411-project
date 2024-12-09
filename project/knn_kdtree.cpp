#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <algorithm>
using namespace std;

struct node {
    vector<double> features; // 30 features based on looking inside the data
    int label;               // 0 for benign, 1 for malignant

    node(vector<double> feats, int lbl) : features(feats), label(lbl) {}
};

// Node for the K-d tree
struct KD {
    node point;
    KD* L;
    KD* R;

    KD(node p) : point(p), L(nullptr), R(nullptr) {}
};

// calculate the Euclidean distance
double distance(const node& a, const node& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.features.size(); ++i) {
        sum += pow(a.features[i] - b.features[i], 2);
    }
    return sum;
}

// Function to find the closer node
KD* nearest(const node& target, KD* a, KD* b) {
     if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }

    double dist_a = distance(target, a->point); // Calculate distance between target node and 'a'
    double dist_b = distance(target, b->point); //Calculate distance between target node and 'b'

    if (dist_a < dist_b) {
        return a;
    } else {
        return b;
    }
}

// Recursive function to perform nearest neighbor search
KD* near_neigh(KD* root, const node& target, int depth, int k) {
    if (root == nullptr) {
        return nullptr;
    }
    int axis = depth % k;   // This alternates between X and Y

    KD* next_branch = nullptr; // Determine which subtree to explore
    KD* other_branch = nullptr;
    if (target.features[axis]<root->point.features[axis]) {
        next_branch=root->L;
        other_branch=root->R;
    } else{
        next_branch=root->R;
        other_branch=root->L;
    }

    // Recursive search in the next branch
    KD* temp =near_neigh(next_branch,target,depth+1,k);
    KD* best =nearest(target,temp,root);

    // Calculate the distance between the target and the splitting plane
    double radius =distance(target,best->point);
    double dist_plane =pow(target.features[axis]-root->point.features[axis], 2);

    // Check if the other branch could contain a closer point
    if (radius >=dist_plane) {
        temp =near_neigh(other_branch, target, depth + 1, k);
        best =nearest(target, temp, best);
    }

    return best;
}

// Function to load the dataset
vector<node> loadDataset(const string& filename, int numFeatures) {
    vector<node> dataset;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "File wasn't able to open" << endl;
        return dataset;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, diagnosis, value;
        vector<double> features;
        int label;

        getline(ss, id, ','); // Read and ignore the ID in the dataset

        getline(ss, diagnosis, ',');// map it to a label
        int label;
        if (diagnosis == "M") {
            label = 1; //  1 if diagnosis is "M" 
        } else {
            label = 0; //  0 if diagnosis is "B" 
        }
        for (int i = 0; i < numFeatures; ++i) {  // read the features
            getline(ss, value, ',');
            features.push_back(stod(value));
        }

        dataset.push_back({features, label});         // Add the node to the dataset
    }

    file.close();
    return dataset;
}

// Function to build a K-d tree recursively
KD* build_tree(vector<node>& points, int depth, int k) {
    if (points.empty()) return nullptr;

    int axis = depth % k;

    // Sort points by the current axis
    sort(points.begin(),points.end(),[axis](const node& a,const node& b) {
        return a.features[axis] < b.features[axis];
    });

    int medianIndex = points.size() / 2;
    node medianPoint = points[medianIndex];

    // Split the dataset
    vector<node> left_point(points.begin(), points.begin() + medianIndex);
    vector<node> right_point(points.begin() + medianIndex + 1, points.end());

    KD* tree = new KD(medianPoint);
    tree->L = build_tree(left_point,depth+1,k);
    tree->R = build_tree(right_point,depth+1,k);

    return tree;
}

int main() {
    string filename = "wdbc.data"; // Dataset 

    vector<node> dataset = loadDataset(filename, 30);

    if (dataset.empty()) {
        cerr << "Failed to load dataset!" << endl;
        return 1;
    }
    KD* root = build_tree(dataset, 0, 30);

    // Test case 1
    node query1 = dataset[10]; // Use the 11th point in the dataset
    KD* nearest1 = near_neigh(root, query1, 0, 30);
    if (nearest1) {
        cout << "Test Case 1: Nearest neighbor label = " << nearest1->point.label << endl;
    }
    // Test case 2
    node query2 = dataset[50]; 
    KD* nearest2 = near_neigh(root, query2, 0, 30);
    if (nearest2) {
        cout << "Test Case 2: Nearest neighbor label = " << nearest2->point.label << endl;
    }
    // Test case 3
    node query3 = dataset[100]; 
    KD* nearest3 = near_neigh(root, query3, 0, 30);
    if (nearest3) {
        cout << "Test Case 3: Nearest neighbor label = " << nearest3->point.label << endl;
    }
    // Test case 4
    node query4 = dataset[200]; 
    KD* nearest4 = near_neigh(root, query4, 0, 30);
    if (nearest4) {
        cout << "Test Case 4: Nearest neighbor label = " << nearest4->point.label << endl;
    }
    // Test case 5
    node query5 = dataset[300]; 
    KD* nearest5 = near_neigh(root, query5, 0, 30);
    if (nearest5) {
        cout << "Test Case 5: Nearest neighbor label = " << nearest5->point.label << endl;
    }

    return 0;
}
