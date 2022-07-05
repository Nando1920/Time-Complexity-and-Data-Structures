#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <chrono>

using namespace std;
using std::chrono::steady_clock;
// using std::chrono::milliseconds;
// using std::chrono::microseconds;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

void rec(list<pair<string, string>>& tape_a, list<pair<int, string>>& tape_b, list<pair<string, string>>& tape_c, int t);

int main(int argc, char* argv[]) {
	list<pair<string, string>> second_element_sorted;
	list<pair<string, string>> first_element_sorted;
	
	list<pair<string, string>> tape_a;
	list<pair<int, string>> tape_b;
	
	
	pair<string, string> lastpair;
	list<pair<string, string>>::iterator it1;
	list<pair<string, string>>::iterator it2;
	
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
	int lines = 0;


	//Stores all pairs in two lists of different orders
	while (std::getline(infile, line, '\n')) {
		int pos = line.find_first_of(',');
		key = line.substr(0, pos);
		val = line.substr(pos + 1, line.back());

		second_element_sorted.push_back({ key,val });
		first_element_sorted.push_back({ key,val });
		lines++;
	}

	first_element_sorted.sort();
	second_element_sorted.sort([](auto const& a, auto const& b) { return a.second < b.second; });

	

	it1 = second_element_sorted.begin();
	it2 = first_element_sorted.begin();
	
	

	for (; it1 != second_element_sorted.end() && it2 != first_element_sorted.end(); it1++, it2++) {
		pair<string, string> pairx = *it1;
		pair<string, string> pairy = *it2;
		if (pairx.second != pairy.first) {
			it2++;
			pairy = *it2;
			if (pairx.second != pairy.first) {
				it2--;
				pairy = *it2;
				lastpair = *it1;
				it1++;
				pairx = *it1;
			}
		}

		if (pairx.second == pairy.first) {
			tape_a.push_back({ pairx.first,pairy.second });
		}
		

		
	}

	tape_b.push_back({ second_element_sorted.size(),lastpair.first });
	tape_b.push_back({ second_element_sorted.size() + 1,lastpair.second });
	
	int t = 2;
	list<pair<string, string>> tape_c(tape_a);

	tape_c.sort();
	tape_a.sort([](auto const& a, auto const& b) { return a.second < b.second; });
	tape_b.sort([](auto const& a, auto const& b) { return a.second < b.second; });
	
	steady_clock::time_point tapesStartTime = steady_clock::now();
	rec(tape_a, tape_b, tape_c, t);
	steady_clock::time_point tapesFinishTime = steady_clock::now();
	nanoseconds tapesSearchTimeTaken = duration_cast<nanoseconds>(tapesFinishTime - tapesStartTime);
	cout << "tapes time: " << tapesSearchTimeTaken.count() << endl;

}

void rec(list<pair<string, string>>& tape_a,list<pair<int, string>>& tape_b, list<pair<string, string>>& tape_c, int t) {
	list<pair<string, string>> tape_a2;
	list<pair<int, string>> tape_b2;
	
	list<pair<string, string>>::iterator ita;
	list<pair<int, string>>::iterator itb;
	list<pair<string, string>>::iterator itc;
	
	pair<string, string> ta;
	pair<int, string> tb;
	pair<string, string> tc;

	
	if (t < tape_c.size() ) {
		ita = tape_a.begin();
		itb = tape_b.begin();
		itc = tape_c.begin();
		while (ita != tape_a.end()) {
			ta = *ita;
			if (itb != tape_b.end()) {
				tb = *itb;
			}
			tc = *itc;

			if (ta.second == tc.first) {
				tape_a2.push_back({ ta.first, tc.second });
				ita++;
				itc++;
				
			}
			else if (ta.second == tb.second) {
				tape_b2.push_back({ tb.first - t,ta.first });
				ita++;
				itb++;
			}
			if (ta.second > tc.first && ita != tape_a.end())
			{
				itc++;
			}
			if (ta.second > tb.second && itb != tape_b.end()) {
				itb++;
			}
		}
		
		tape_a2.sort([](auto const& a, auto const& b) { return a.second < b.second; });
		tape_b.sort();
		tape_b2.sort();
		tape_b2.merge(tape_b);
		tape_b2.sort([](auto const& a, auto const& b) { return a.second < b.second; });
		
		t = t * 2;
		
		rec(tape_a2, tape_b2, tape_c, t);
		
	}
	else {
		tape_b.sort();
		cout << "\n" << t << " tape b'" << endl;
		for (auto&& it : tape_b) {
			cout << it.second << endl;
		}
	}
	
}