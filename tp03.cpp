#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Struct to store rectangles and tables
struct Rectangle {
    int height = 0;
    int width = 0;
    int area = 0;

    Rectangle(int height, int width) {
        this->height = height;
        this->width = width;
        this->area = height * width;
    }
};

// Compare function to sort rectangles by area and then by width
bool compare(Rectangle a, Rectangle b) {   
    if (a.area == b.area) {
        return a.width > b.width;
    }
    return a.area > b.area;          
    
}

// Function to find and push to a vector all the maximal rectangles that exists until the given row. 
// The function uses a stack to store the current rectangle being considered. If a rectangle is in 
// between smaller rectangles or the ends of the table, push it to the vector.
void findRectangles(vector<int> &heights, vector<Rectangle> &rectangles, vector<vector<int>> &usedRectangles){
    stack<int> stack;
 
    int top; 
    int i = 0;
    while (i < heights.size()) {
        if (stack.empty() || heights[stack.top()] <= heights[i])
            stack.push(i++);
        else {
            top = heights[stack.top()];
            stack.pop();
            if(stack.empty()) {
                // Only add the rectangle if there is no other rectangle with the same area, including rotated ones
                if (usedRectangles[top][i] == 0 && top * i != 0) {
                    rectangles.push_back(Rectangle(top, i));
                    usedRectangles[top][i] = 1;
                    usedRectangles[i][top] = 1;
                }
            }
            else {
                if (usedRectangles[top][i - stack.top() - 1] == 0 && top * (i - stack.top() - 1) != 0) {
                    rectangles.push_back(Rectangle(top, i - stack.top() - 1));
                    usedRectangles[top][i - stack.top() - 1] = 1;
                    usedRectangles[i - stack.top() - 1][top] = 1;
                }
            }
        }
    }
    // Find rectangles from the remaining elements in the stack 
    while (!stack.empty()) {
        top = heights[stack.top()];
        stack.pop();
        if(stack.empty()) {    
            if (usedRectangles[top][i] == 0 && top * i != 0) {
                rectangles.push_back(Rectangle(top, i));
                usedRectangles[top][i] = 1;
                usedRectangles[i][top] = 1;
            }
        }
        else {
            if (usedRectangles[top][i - stack.top() - 1] == 0 && top * (i - stack.top() - 1) != 0) {
                rectangles.push_back(Rectangle(top, i - stack.top() - 1));
                usedRectangles[top][i - stack.top() - 1] = 1;
                usedRectangles[i - stack.top() - 1][top] = 1;
            }
        }
    }

}    

int main() {
    // Receive the number of rows and columns
    int rows, columns;
    cin >> rows >> columns;

    // This is a performance optimization to avoid iterating over the biggest dimension below
    if (columns > rows) {
        swap(rows, columns);
    }

    // Receive the matrix to be considered
    vector<vector<char>> matrix(rows, vector<char>(columns));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> matrix[i][j];
        }
    }

    // Receive the possible tables and sort them by area and then by width
    vector<Rectangle> tables;

    int numberOfTables;
    cin >> numberOfTables;

    for (int i = 0; i < numberOfTables; i++) {
        int height, width;
        cin >> height >> width;
        tables.push_back(Rectangle(height, width));
    }

    // Sort the tables by area and then by width
    sort(tables.begin(), tables.end(), compare);

    // Vector to store all maximal rectangles from the matrix
    vector<Rectangle> rectangles;

    // Used to avoid adding the same rectangle twice
    int maxDimension = max(rows, columns);
    vector<vector<int>> usedRectangles(maxDimension + 1, vector<int>(maxDimension + 1, 0));

    // Find all the maximal rectangles from the matrix, calculating the rectangles
    // sizes above a row and then finding the rectangles until this given row
    vector<int> heightsOfColumns(columns, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == '.') {
                heightsOfColumns[j]++;
            }
            else {
                heightsOfColumns[j] = 0;
            }
        }
        findRectangles(heightsOfColumns, rectangles, usedRectangles);
    }

    // Sort the rectangles by area and then by width
    sort(rectangles.begin(), rectangles.end(), compare);

    // Find the first table that can be placed in the matrix. Since the tables and the maximal rectangles are 
    // sorted in descending order, the first table that can be placed in the matrix will be the first one.
    int maxArea = rectangles[0].area;

    Rectangle maxTable(0, 0);
    for (int i = 0; i < tables.size(); i++) {
        Rectangle table = tables[i];
        if (tables[i].area > maxArea) {
            continue;
        }
        for (int j = 0; j < rectangles.size(); j++) {
            Rectangle rectangle = rectangles[j];
            if ((table.height <= rectangle.height && table.width <= rectangle.width) || (table.height <= rectangle.width && table.width <= rectangle.height)) {
                maxTable = table;
                break;
            }
        }
        if (maxTable.area != 0) {
            break;
        }        
    }

    // Print the table that can be placed in the matrix
    if (maxTable.area == 0) {
        cout << "-1 1" << endl;
    }
    else {
        cout << maxTable.height << " " << maxTable.width << endl;
    }

    return 0;
}