// https://www.codeabbey.com/index/task_view/instrument-tuner
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>
#include <numeric>
#include <tuple>
#include <regex> 

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

string PitchToNote(float pitch, vector<float> Octave, vector<double> Ratio, vector<string> Notes);

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Instrument Tuner v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	//printVector(raw_data);
	/***********************/
	vector<string> solution;

	vector<float> data = splitToFloat(raw_data[1], " ");
	//printVector(data);

	vector<string> Notes = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };
	vector<double> Ratio(12);

	for (int i = 0; i < 12; i++) {
		Ratio.at(i) = pow(2, (i / 12.0));
	}

	vector<float> Octave(7);
	Octave.at(0) = 27.5;
	Octave.at(1) = 55;

	for (int i = 2; i < 7; i++) {
		Octave.at(i) = Octave.at(i - 1) * 2;
	}

	for (auto pitch : data) {
		solution.push_back(PitchToNote(pitch, Octave, Ratio, Notes));
	}

	cout << "\nSolution: " << joinVector(solution, " ") << endl;
	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

string PitchToNote(float pitch, vector<float> Octave, vector<double> Ratio, vector<string> Notes) {
	vector<string> REF = { "A", "A#", "B" , "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
	float octave = -1;
	int octaveIndex = -1;
	for (int i = 0; i < Octave.size(); i++) {
		if (pitch < Octave[i]) {
			octaveIndex = i - 1;
			octave = Octave[octaveIndex];
			break;
		}
	}
	float ratio = pitch / octave;
	int i = round(12.0 * log2(ratio));
	if (i > 2) octaveIndex++;
	string note = REF[i] + to_string(octaveIndex);
	return note;
}
