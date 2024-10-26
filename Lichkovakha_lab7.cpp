#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    int counter;
    vector<vector<int>> matrix(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        string row;
        cin >> row;
        counter = 1;
        for (int j = 0; j < m; j++) {
            if (row[j] == '1') {
                matrix[i][j] = -1;
                counter = 1;
            }
            else {
                matrix[i][j] = counter;
                counter++;
            }
        }
    }


    int maxArea = 0;
    int minEdge;
    int columnEndFlag = 0;
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][i] != -1) {
                minEdge = 600;
                counter = 0;
                k = j;
                columnEndFlag = 0;
                while (matrix[k][i] != -1 && columnEndFlag != 1) {
                    counter++;
                    if (matrix[k][i] < minEdge) {
                        minEdge = matrix[k][i];
                    }
                    if (counter * minEdge > maxArea) {
                        maxArea = counter * minEdge;
                    }
                    if (k != n - 1) {
                        k++;
                    }
                    else {
                        columnEndFlag = 1;
                    }
                    
                }
                
            }
        }
    }
    cout << maxArea << endl;
   
    return 0;
}
