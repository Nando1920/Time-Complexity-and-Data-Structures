#include <iostream>
#include <cstddef>
#include <fstream>
#include <list>
#include <string>
#include <random>
#include <unordered_map>
#include <chrono>

using namespace std;
using std::chrono::steady_clock;
// using std::chrono::milliseconds;
// using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

int main(int argc, char* argv[]) {
	list<string> result_sequence;
	list<string> keys;
	list<string>::iterator it;
	unordered_map<string, string> brick_values;
	unordered_map<string, string> reverse_brick_values;

	string argument;
	/*string amount;
	cout << "Please enter the path to the desired .txt file containing the symbol pairs:" << endl;
	cin >> amount;*/

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
	int lines = 0;

	steady_clock::time_point mapInsertStartTime = steady_clock::now();
	//Stores all pairs in an unordered_map and all keys in a list from the specified text file
	while (std::getline(infile, line,'\n')) {
		int pos = line.find_first_of(',');
		key = line.substr(0, pos);
		val = line.substr(pos+1, line.back());
		
		brick_values.insert({ key, val });
		reverse_brick_values.insert({ val, key });
		keys.push_back(key);
		lines++;
	}
	infile.close();
	steady_clock::time_point mapInsertFinishTime = steady_clock::now();
	nanoseconds mapInsertTimeTaken = duration_cast<nanoseconds>(mapInsertFinishTime - mapInsertStartTime);
	
	
	//Generates a random number to iterate through the list and retrieve a random key
	int loops = rand() % (keys.size() - 1);
	it = keys.begin();
	for (int i = 0; i <= loops; i++) {
		it++;
	}
	
	//appends the random brick
	result_sequence.push_back(*it);
	bool found_last = false;

	steady_clock::time_point mapSearchStartTime = steady_clock::now();
	for (int i = 0; i <= brick_values.size() ; i++) {
		if (!found_last) {
			//checks first, whethert the key exists in the structure
			if (brick_values.find(result_sequence.back()) == brick_values.end()) {
				found_last = true;
				continue;
			}
			else {
				result_sequence.push_back(brick_values.at(result_sequence.back()));	
			}
		}
		else
		{
			//checks first, whethert the key exists in the structure
			if (reverse_brick_values.find(result_sequence.front()) == reverse_brick_values.end()) {
				break;
			}
			else {
				result_sequence.push_front(reverse_brick_values.at(result_sequence.front()));
			}
		}
	}
	steady_clock::time_point mapSearchFinishTime = steady_clock::now();
	nanoseconds mapSearchTimeTaken = duration_cast<nanoseconds>(mapSearchFinishTime - mapSearchStartTime);
	//display all items
	int j = 1;
	for (auto element : result_sequence) {
		cout << j << ". " << element << endl;
		j++;
	}
	cout << "Map Insert: " <<mapInsertTimeTaken.count() << endl;
	cout << "Map Search: " << mapSearchTimeTaken.count() << endl;
}

