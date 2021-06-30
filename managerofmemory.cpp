#include <iostream>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;
class Section{
public:
    int firstInd;
    int lastInd;
    bool free;
};
void myDelete(int length, multimap <int, list <Section> :: iterator>& freeSections, int firstInd, int lastInd){
        auto iterators = freeSections.equal_range(length);
        for (auto  it = iterators.first; it != iterators.second; it++) {
            if (it->second->firstInd == firstInd && it->second->lastInd == lastInd) {
                freeSections.erase(it);
                break;
            }
        }
}


int main() {
    list <Section> states;// храним все отрезки (и пустые, и занятые)
    multimap <int, list <Section> :: iterator> freeSections; // ключ -- длина, значение итератор states на нужный пустой отрезок
    int countOfMemory;
    int countOfQueries;
    cin >> countOfMemory >> countOfQueries;

    int queries [countOfQueries];
    unordered_map <int, list <Section> :: iterator> iterOfQueries;// мапа, которая нужна для освобождение памяти
    for(int i=0; i<countOfQueries; i++){
        cin >> queries[i];
    }
    Section section;
    section.firstInd = 0;
    section.lastInd = countOfMemory - 1;
    section.free = true;
    states.push_back(section);
    freeSections.insert(pair<int, list<Section> :: iterator>(countOfMemory, states.begin()));

    for(int i=0; i<countOfQueries; i++){

        /*
         * если запрос на выделение памяти, то берем самый большой отрезок среди пустых, проверяем, не меньше ли он, чем запрос.
         * Дальше уменьшаем пустой отрезок и добавляем в states занятый отрезок
         */

        if(queries[i]>0){
            if(!freeSections.empty() && freeSections.rbegin()->first > queries[i]){

                int tmpFirstInd = freeSections.rbegin() -> second -> firstInd; //первый индекс пустого отрезка
                int tmpLastInd = freeSections.rbegin() -> second -> lastInd; //последний индекс пустого отрезка
                cout << tmpFirstInd + 1 << "\n";
                int length = freeSections.rbegin() -> first; //длина пустого отрезка
                freeSections.rbegin() ->second->lastInd = tmpFirstInd + queries[i] - 1; // последний индекс занятого отрезка, первый индекс -- начало пустого
                freeSections.rbegin() -> second -> free = false; //делаем этот отрезок занятым
                // переформируем пустой
                Section section1;
                section1.firstInd = tmpFirstInd + queries[i];
                section1.lastInd = tmpLastInd;
                section1.free = true;

                //кладем новый пустой в freeSections
                freeSections.insert(pair<int, list<Section> :: iterator>(length - queries[i], states.insert(next(freeSections.rbegin() -> second), section1)));

                //кладем мапу ключ -- индекс запроса, значение -- итератор в листе на нужный отрезок
                iterOfQueries[i] = freeSections.rbegin() -> second;
                freeSections.erase(prev(freeSections.end())); // удаляем неактуальный самый большой отрезок
            }
            else if(freeSections.empty()||freeSections.rbegin() -> first < queries[i]){
                cout << "-1\n";
            }

            // если запрос равен свободному отрезку
            else {

                freeSections.rbegin() -> second -> free = false;//меняем статус отрезка

                cout << freeSections.rbegin() ->second -> firstInd +1<<"\n";
                iterOfQueries[i] = freeSections.rbegin() -> second; //кладем в мапу ключ -- индекс запроса, значение -- итератор в листе на нужный отрезок
                freeSections.erase(prev(freeSections.end())); // удаляем неактуальный пустой отрезок
            }
        }
            /*
             * если запрос на освобождение памяти, то рассмтариваем 4 случая:
             * 0 0 -- суммируем отрезки, меняем соотвествующие структуры
             * 1 1 -- удаляем из листа левый отрезок или меня
             * 1 0
             * 0 1
             */
        else {

            /*
             * iterOFQueries хранит только те отрезки, которые потенциально можно освободить, следовательно, если запроса нет в этой мапе,
             * следовательно, либо запрос был изначально отклонен, либо отрезок уже был освобожден ранее
             */

            if(iterOfQueries.count(abs(queries[i])-1)!=0) {
                //получаем по запросу тот отрезок из листа, к которому он относится
                list<Section> :: iterator  current = iterOfQueries[abs(queries[i])-1];

                //если отрезок является началом
                if(current == states.begin()){

                    //если следующий после отрезка тоже свободный отрезок -- объдиняем их
                    //итого: firstInd -- первый индекс текущего отрезка; lastInd -- последний индекс следющего отрезка
                    if(next(current) -> free){
                        int tmpLastInd = next(current) -> lastInd; // последний индекс следующего
                        current -> free = true; // меняем статус текущего отрезка
                        current -> lastInd = tmpLastInd; //меняем на последний индекс следующего
                        int length = next(current) -> lastInd - next(current) -> firstInd +1;
                        int firstIdx = next(current) -> firstInd;
                        int lastIdx = next(current) -> lastInd;
                        myDelete(length, freeSections, firstIdx, lastIdx);
                        //freeSections.erase(freeSections.find(next(current)->lastInd - next(current) -> firstInd + 1)); //удаляем по ключу-длине следующий отрезок из свободных
                        states.erase(next(current)); //удаляем из всех отрезков следующий
                        freeSections.insert(pair<int, list<Section> :: iterator>(tmpLastInd+1, current)); //добавляем новый совмещенный отрезок в пустые
                        iterOfQueries.erase(abs(queries[i])-1); //удаляем данный запрос, так как мы больше не сможем его освободить
                        continue;
                    }

                    else{
                        //если после текущего отрезка идет занятый отрезок, то мы просто меняем статус текущего и добавляем в пустые
                        current -> free = true;
                        freeSections.insert(pair<int, list<Section> :: iterator>(current -> lastInd - current -> firstInd +1, current));
                        iterOfQueries.erase(abs(queries[i])-1);
                        continue;
                    }

                }

                //если отрезок является концом
                list <Section> :: iterator check;
                check = prev(states.end());
                if(current == check){

                    if(prev(current) -> free){
                        int tmpFirstInd = prev(current) -> firstInd;
                        current -> free = true;
                        current -> firstInd = tmpFirstInd;
                        int length = prev(current) -> lastInd - prev(current) -> firstInd +1;
                        int firstIdx = prev(current) -> firstInd;
                        int lastIdx = prev(current) -> lastInd;
                        myDelete(length, freeSections, firstIdx, lastIdx);
                        //freeSections.erase(freeSections.find(prev(current)-> lastInd - prev(current)->firstInd +1));
                        states.erase(prev(current));
                        freeSections.insert(pair<int, list<Section> :: iterator>(current -> lastInd - tmpFirstInd +1, current));
                        iterOfQueries.erase(abs(queries[i])-1);
                        continue;
                    }

                    else {
                        current -> free = true;
                        freeSections.insert(pair<int, list<Section> :: iterator>(current-> lastInd - current -> firstInd +1, current));
                        iterOfQueries.erase(abs(queries[i])-1);
                        continue;
                    }
                }
                //если отрезок в середине

                //если отрезок находится между двумя пустыми
                if (next(current)->free && prev(current)->free) {

                    //будем совмещать отрезки, итого: firstInd -- индекс преды
                    int tmpFirstInd = prev(current)->firstInd;
                    int tmpLastInd = next(current)->lastInd;
                    int first = prev(current)->lastInd -tmpFirstInd  + 1;
                    int second = tmpLastInd - next(current)->firstInd + 1;
                    current->firstInd = tmpFirstInd;
                    current->lastInd = tmpLastInd;
                    current->free = true;
                    freeSections.insert(pair<int, list<Section> :: iterator>(tmpLastInd - tmpFirstInd +1, current));
                    int length1  = next(current) -> lastInd - next(current) -> firstInd +1;
                    int firstIdx1 = next(current) -> firstInd;
                    int lastIdx1 = next(current) -> lastInd;
                    myDelete(length1, freeSections, firstIdx1, lastIdx1);
                    int length = prev(current) -> lastInd - prev(current) -> firstInd +1;
                    int firstIdx = prev(current) -> firstInd;
                    int lastIdx = prev(current) -> lastInd;
                    myDelete(length, freeSections, firstIdx, lastIdx);
                    //freeSections.erase(freeSections.find(prev(current)->lastInd - prev(current)-> firstInd +1));
                    //freeSections.erase(freeSections.find(next(current)->lastInd - next(current)-> firstInd +1));
                    iterOfQueries.erase(abs(queries[i])-1);
                    states.erase(next(current));
                    states.erase(prev(current));

                } else if (!next(current)->free && !prev(current)->free) {

                    current->free = true;
                    freeSections.insert(pair<int, list<Section> :: iterator>(queries[abs(queries[i])-1], current));
                    iterOfQueries.erase(abs(queries[i])-1);

                } else if (!next(current)->free && prev(current)->free) {

                    int tmpFirstInd = prev(current)->firstInd;
                    current->firstInd = tmpFirstInd;
                    current->free = true;
                    freeSections.insert(pair<int, list<Section> :: iterator>(current -> lastInd - current-> firstInd +1, current));
                    iterOfQueries.erase(abs(queries[i])-1);
                    int length = prev(current) -> lastInd - prev(current) -> firstInd +1;
                    int firstIdx = prev(current) -> firstInd;
                    int lastIdx = prev(current) -> lastInd;
                    myDelete(length, freeSections, firstIdx, lastIdx);
                   // freeSections.erase(freeSections.find( prev(current)->lastInd - prev(current)->firstInd + 1));
                    states.erase(prev(current));

                } else if (next(current)->free && !prev(current)->free) {

                    int tmpFirstInd = current->firstInd;
                    int tmpLastInd = next(current)->lastInd;
                    current->free = true;
                    current->lastInd = tmpLastInd;
                    freeSections.insert(pair<int, list<Section> :: iterator>(tmpLastInd - tmpFirstInd +1, current));
                    int length = next(current) -> lastInd - next(current) -> firstInd +1;
                    int firstIdx = next(current) -> firstInd;
                    int lastIdx = next(current) -> lastInd;
                    myDelete(length, freeSections, firstIdx, lastIdx);
                    iterOfQueries.erase(abs(queries[i])-1);
                  //  freeSections.erase(freeSections.find(next(current)->lastInd - next(current) -> firstInd + 1));
                    states.erase(next(current));

                }
            }
            else {
                continue;
            }
        }
    }
}