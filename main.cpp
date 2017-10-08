#include "PSLL.h"
#include "SLL.h"
#include "SDAL.h"
#include "CDAL.h"

using namespace std;
using namespace cop3530;

int main() {

    auto list = new PSLL<char>();

    for(char i = 'A'; i <= 'Z'; i++)
        list->push_back(i);

    for(char i = 'a';i <='z'; i++)
        list->push_back(i);

    auto iter = list->begin();

    auto iter_end = list->end();

    size_t cnt = 0;

    for(;iter != iter_end;iter++){
        cout << "Item at " << cnt << ": " << *iter << endl;

        if(cnt % 26 == 1){
            *iter = (cnt/25 == 0) ? 'K' : 'k';

            cout << "Updated Item at " << cnt << ": " << *iter << endl;
        }

        cnt++;
    }

    cop3530::PSLL<char> const *  list_1 = list;

    auto iter_1 = list_1->begin();

    auto iter_end_1 = list_1->end();

    cnt = 0;

    for(;iter_1 != iter_end_1;iter_1++){
        cout << "CONST Item at " << cnt << ": " << *iter_1 << endl;

        cnt++;
    }

    delete list;

    return 0;
}