#include <bits/stdc++.h>
#include <iostream>

using namespace std;

pair<int, int> findMaxArea(vector<int> &heights) {
    int maxArea = 0;
    int height = 0;
    int width = 0;
    int left = 0;
    int right = heights.size() - 1;


    pair<int, int> maxAreaDimensions = make_pair(height, width);
    return maxAreaDimensions;
}

int main() {
    int rows, columns;
    cin >> rows, columns;

    vector<vector<int>> matrix(rows, vector<int>(columns));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<int> rectanglesHeights(columns, 0);

    int maxArea = 0;
    pair<int, int> maxAreaDimensions;

    // if (columns > rows) {
    //     swap(rows, columns);
    // }

    for (int i = 0; i < rows; i++) {
        pair<int, int> dimensions;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == '.') {
                rectanglesHeights[j]++;
            }
            else {
                rectanglesHeights[j] = 0;
            }
        }
        dimensions = findMaxArea(rectanglesHeights);
        int area = dimensions.first * dimensions.second;
        if (area > maxArea) {
            maxArea = area;
            maxAreaDimensions = dimensions;
        }        
    }

    int numberOfTables;
    pair<int,int> maxTable;


    for (int i = 0; i < numberOfTables; i++) {
        pair<int,int> table;
        cin >> table.first >> table.second;
        int tableArea = table.first * table.second;
        if (tableArea > maxArea and (table.first <= maxAreaDimensions.first and table.second <= maxAreaDimensions.second) or (table.first <= maxAreaDimensions.second and table.second <= maxAreaDimensions.first) and ) {
            maxTable.first = table.first;
            maxTable.second = table.second;
        }
        
    }
    
    cout << maxTable.first << " " << maxTable.second << endl;

    return 0;
}