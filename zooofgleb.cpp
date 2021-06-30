// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class CurrentElem {
public:
    char elem;
    int index;
};

int main(){
    string data;
    cin >> data;

    int indexOfLov = 0;
    int indexOfAnm = 0;

    vector <CurrentElem> all;
    map <int, int> map;

    for(int i=0; i<data.length(); i++){
        if(isupper(data[i])){
            CurrentElem curr;
            curr.elem = data[i];
            curr.index = indexOfLov;
            if(!all.empty()){
                if(islower(all.back().elem)){
                    if(toupper(all.back().elem)!=curr.elem){
                        all.push_back(curr);
                    }
                    else {
                        map[curr.index] = all.back().index+1;
                        all.pop_back();
                    }
                }
                else{
                    all.push_back(curr);
                }
            }
            else {
                all.push_back(curr);
            }
            indexOfLov = indexOfLov + 1;
        }
        else {
            CurrentElem curr;
            curr.elem = data[i];
            curr.index = indexOfAnm;
            if(!all.empty()){
                if(isupper(all.back().elem)){
                    if(tolower(all.back().elem)!=curr.elem){
                        all.push_back(curr);
                    }
                    else {
                        map[all.back().index] = curr.index +1;
                        all.pop_back();
                    }
                }
                else {
                    all.push_back(curr);
                }
            }
            else {
                all.push_back(curr);
            }
            indexOfAnm = indexOfAnm +1;
        }

    }

    if(!all.empty()){
        cout<<"Impossible";
    }
    else {
        cout << "Possible\n";
        for(int i=0; i<map.size(); i++){
            cout << map[i];
            cout << ' ';
        }
    }


}
