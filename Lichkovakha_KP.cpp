#define MINIMP3_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>
#include <set>
#include "minimp3.h"
#include "minimp3_ex.h"

using namespace std;
const double pi = M_PI;
const int WSIZE = 4096, WSTEP = 1024;
using complexVector = vector<complex<double>>;


vector<int> decoder(const string& filename) {
	mp3dec_t mp3d;
	mp3dec_file_info_t info;
	if (mp3dec_load(&mp3d, filename.data(), &info, NULL, NULL)) {
		throw runtime_error("Decode error");
	}
	vector<int> res(info.buffer, info.buffer + info.samples);
	free(info.buffer);
	return res;
}

complexVector hunn(vector<int>& fullMP3, int start, int end) 
{
	complexVector afterHunn;
	for (int i = start; i < end; i++)
	{
		afterHunn.push_back(fullMP3[i] * 0.5 * (1 - cos(2 * pi * (i-start) / (4096-1))));
	}

	return afterHunn;
}

void fastAndFurryious(complexVector& original) {
	int size = original.size();
	if (size == 1) { 
		return;
	}
	else {
		complexVector even(size / 2), uneven(size / 2);
		for (int i = 0; i < size; i += 2) {
			even[i / 2] = original[i];
			uneven[i / 2] = original[i + 1];
		}
		fastAndFurryious(even);
		fastAndFurryious(uneven);

		double angle = (2 * pi / size);
		complex<double> omegus = 1.0;
		complex<double> omegusSize(cos(angle), sin(angle));
		for (int k = 0; k < size / 2; k++) {
			original[k] = even[k] + omegus * uneven[k];
			original[k + (size / 2)] = even[k] - omegus * uneven[k];
			omegus *= omegusSize;
		}
		return;
	}
}
bool comparator(complex<double> uno, complex<double> dos) {
	return abs(uno) < abs(dos);
}

int main() {
	string filename;
	filename = "input.mp3";
	vector<int> fullMP3 = decoder(filename);
	int n = fullMP3.size();
	double currentMax = 0;
	double out = 0.0;
	for (int i = 0; i + 4096 < n; i += 1024) {
		complexVector afterHunn = hunn(fullMP3, i, i + 4096);
		fastAndFurryious(afterHunn);
		auto out  = max_element(afterHunn.begin(), afterHunn.end(), comparator);
		cout << fixed << setprecision(26) << abs(*out) << '\n';
	}
	return 0;
}
