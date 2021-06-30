#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    int kinds;
    int max;
    int count;
    int actions = 0;
    int kostyl = 0;
    int kostyl2 = 0;
    vector<vector<int>> state2;
    unordered_map<int, vector<int>> state;
    set <int> currentInd;
    unordered_set <int> kostyl3;
    cin >> kinds >> max >> count;
    int zhopa;
    int massive[count];
    for (int i = 0; i < count; i++) {
        cin >> massive[i];
        state[massive[i]].push_back(i);
    }

    if(kinds< max){
        cout << kinds;
    }
    else {
        for (int i = 0; i < count; i++) {
            zhopa = massive[i];
            if (kostyl != max) {
                if (!kostyl3.count(i)) {
                    state[zhopa].erase(state[zhopa].begin());
                    if (!state[zhopa].empty()) {
                        currentInd.insert(state[zhopa][0]);
                        kostyl3.insert(state[zhopa][0]);
                    } else {
                        kostyl2++;
                        //currentInd.insert(i*(-1));
                    }
                    kostyl++;
                    actions++;
                } else {
                    state[zhopa].erase(state[zhopa].begin());
                    if (!state[zhopa].empty()) {
                        currentInd.insert(state[zhopa][0]);
                        kostyl3.insert(state[zhopa][0]);
                    } else {
                        kostyl2++;
                        //currentInd.insert(i*(-1));
                    }
                }
            } else {
                if (!kostyl3.count(i)) {
                    if (kostyl2 > 0) {
                        kostyl2--;
                    } else {
                        int del = *currentInd.rbegin();
                        currentInd.erase(del);
                        kostyl3.erase(del);
                    }
                    state[zhopa].erase(state[zhopa].begin());


                    if (!state[zhopa].empty()) {
                        currentInd.insert(state[zhopa][0]);
                        kostyl3.insert(state[zhopa][0]);
                    } else {
                        kostyl2++;

                    }
                    actions++;
                } else {

                    currentInd.erase(*state[zhopa].begin());
                    state[zhopa].erase(state[zhopa].begin());
                    if (!state[zhopa].empty()) {
                        kostyl3.insert(state[zhopa][0]);
                        currentInd.insert(state[zhopa][0]);
                    } else {
                        kostyl2++;
                    }
                }
            }
        }
        cout << actions;
    }
}