#include <iostream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <fstream>
#include <random>
#include <chrono>


using namespace std;
using std::chrono::steady_clock;
// using std::chrono::milliseconds;
// using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

int main(int argc,char* argv[]) {
	map<int, string> result_sequence;
	list<string> keys;
	list<string>::iterator it;
	unordered_map<string, string> brick_values;
	unordered_map<string, string> reverse_brick_values;
	string argument;

	if (argc == 2) {
		argument = argv[1];
	}
	else
	{
		return -1;
	}

	string path = argument;
	ifstream infile;
	infile.open(path);
	if (!infile) {
		cout << "Sorry, the algorithm could not find that filepath." << endl;
		return -1;
	}

	string line, key, val;
	int i = 0;

	//Stores all pairs in an unordered_map and all keys in a list from the specified text file
	while (std::getline(infile, line, '\n')) {
		int pos = line.find_first_of(',');
		key = line.substr(0, pos);
		val = line.substr(pos + 1, line.back());

		brick_values.insert({ key, val });
		reverse_brick_values.insert({ val, key });
		keys.push_back(key);
	}
	infile.close();

	// Generates a random number to iterate through the list and retrieve a random key
	int loops = rand() % (keys.size() - 1);
	it = keys.begin();
	for (int i = 0; i <= loops; i++) {
		it++;
	}


	int ordered_key = keys.size();
	result_sequence.insert({ ordered_key,*it });
	bool found_last = false;

	steady_clock::time_point mapSearchStartTime = steady_clock::now();
	for (int i = 0; i <= brick_values.size(); i++) {
		if (!found_last) {
			//checks first, whethert the key exists in the structure
			if (brick_values.find(result_sequence.at(ordered_key)) == brick_values.end()) {
				int j = 1;
				found_last = true;
				ordered_key = keys.size();
			}
			else {
				result_sequence.insert({ ordered_key + 1 ,brick_values.at(result_sequence.at(ordered_key)) });
				ordered_key++;
			}
		}
		else
		{
			if (reverse_brick_values.find(result_sequence.at(ordered_key)) == reverse_brick_values.end()) {
				break;
			}
			else {
				result_sequence.insert({ ordered_key - 1 ,reverse_brick_values.at(result_sequence.at(ordered_key)) });
				ordered_key--;
			}
		}

	}
	steady_clock::time_point mapSearchFinishTime = steady_clock::now();
	nanoseconds mapSearchTimeTaken = duration_cast<nanoseconds>(mapSearchFinishTime - mapSearchStartTime);

	int j = 1;
	for (auto&& element : result_sequence) {
		cout << j << ". " << element.second << endl;
		j++;
	}

	cout << "Map searched in: " << mapSearchTimeTaken.count() << endl;
}