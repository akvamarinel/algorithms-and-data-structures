#include <iostream>
#include <string>
#include <deque>
using namespace std;
int main() {
    string stringNumber;
    getline(cin, stringNumber);
    int number = stoi(stringNumber);

    deque<int> first;
    deque<int> second;
    int fix = 0;
    string line;

    while (getline(cin, line)) {
        if (line.find('+') != string::npos) {
            if (first.size() >= second.size()) {
                second.push_back(stoi(line.substr(1, line.size() - 1)));
            } else {
                first.push_back(second.front());
                second.pop_front();
                second.push_back(stoi(line.substr(1, line.size() - 1)));
            }
        } else if (line.find('*') != string::npos) {
             if (first.size() < second.size()) {// середина во втором векторе
                first.push_back(second.front());
                second.pop_front();
                second.push_front(stoi(line.substr(1, line.size() - 1)));
            } else if(first.size() == second.size()) { // середина в первом векторе
                second.push_front(stoi(line.substr(1, line.size() - 1)));
            }
        } else {
            if (second.size() != first.size()) {
                first.push_back(second.front());
                second.pop_front();
            }
                cout << first.front() << '\n';
                first.pop_front();
            }

            fix++;
            if (fix == number) {
                return 0;
            }
        }

    }
