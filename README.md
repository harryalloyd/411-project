Download the UC Irvine dataset from https://archive.ics.uci.edu/dataset/17/breast+cancer+wisconsin+diagnostic 
You should take the wdbc.data file out of the folder to the root. I hard coded the wdbc.data file directly into the cpp. 

Run this to compile and you will be able to see the output

g++ -std=c++17 knn_naive.cpp
./a.out

g++ -std=c++17 knn_kdtree.cpp
./a.out

