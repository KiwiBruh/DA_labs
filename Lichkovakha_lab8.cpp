#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <algorithm>

using namespace std;

struct interval {

    int lBound;
    int rBound;
};

std::vector<int> findQuantityIntervals(int intervals, int M, std::vector<interval> matrix) {
    int now = 0;
    std::vector<int> result;
    interval current;
    current.lBound = 0;
    current.rBound = 0;
    int current_i = -1;
    int found_flag = 1;
    std::vector<int> criteria(intervals, 0);
    while (found_flag == 1) {
        found_flag = 0;
        for (int i = 0; i < intervals; i++) {
            if (criteria[i] > 0) {

            }
            else {
                if (matrix[i].lBound <= now) {
                    if (current.rBound < matrix[i].rBound) {
                        current.lBound = matrix[i].lBound;
                        current.rBound = matrix[i].rBound;
                        if (current_i != -1) {
                            criteria[current_i] = 1;
                        }
                        current_i = i;
                        found_flag = 1;
                    }
                    else {
                        criteria[i] = 1;
                    }
                }

            }
        }
        if (found_flag == 1) {
            result.push_back(current_i);
            now = current.rBound;
        }
        if (now >= M) {
            return result;
        }
    }
    result.push_back(-1);
    return result;

}




int main()
{

    int intervals;
    int M;
    ifstream fin("input.txt");
    fin >> intervals;
    std::vector<interval> matrix(intervals);
    int temp_lBound;
    int temp_rBound;
    for (int i = 0; i < intervals; i++) {
        fin >> temp_lBound >> temp_rBound;
        matrix[i].lBound = temp_lBound;
        matrix[i].rBound = temp_rBound;

    }
    fin >> M;
    fin.close();

    std::vector<int> result = findQuantityIntervals(intervals, M, matrix);


    ofstream fout("output.txt");
    if (result[result.size() - 1] != -1) {
        fout << result.size() << endl;
        sort(result.begin(), result.end());
        for (int i = 0; i < result.size(); i++) {
            fout << matrix[result[i]].lBound << " " << matrix[result[i]].rBound << endl;
        }

    }
    else {
        fout << 0 << endl;
    }

    fout.close();
}
