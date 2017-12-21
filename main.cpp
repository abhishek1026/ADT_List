#include "PSLL.h"
#include "SSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include "CBL.h"

using namespace std;
using namespace cop3530;

class Test{
private:
    char x;
public:

    Test(){
        x = 'x';
    }

    Test(char x){
        this->x = x;
    }

    void out_char(){
        cout << x << " " << endl;
    }

    void set_char(char x){
        this->x = x;
    }
    friend std::ostream& operator <<(std::ostream& output, const Test& test);
};

std::ostream& operator <<(std::ostream& output, const Test& test){
    output << test.x;
    return output;
}

int main(void) {

    /*
    cop3530::SDAL<Test> list;

    for(int i = 0; i < 150; i++){
        Test new_test('a' + i);
        list.push_back(new_test);
    }

    auto iter = list.begin();

    auto end = list.end();

    for(;iter != end; iter++){
        iter->out_char();
    }

    auto iter_1 = list.begin();

    for(;iter_1 != end; iter_1++){
        iter_1->set_char('A');
    }

    auto iter_2 = list.begin();

    for(;iter_2 != end; iter_2++){
        iter_2->out_char();
    }

*/
    cop3530::CBL<char> list_0;

    list_0.insert('K',0);

    list_0.push_front('J');

    cop3530::CBL<char> list {std::move(list_0)};
    
    bool (*fxn)(const char &,const char&) = cop3530::CBL<char>::equals;
    
    list.insert('A', 0);
    
    list.insert('B', 1);
    
    for(int i = 0; i < 5; i++){
		list.push_back('C' + i );
	}
	
	for(int i = 0; i < 3; i++){
		list.push_front('X' + i );
	}
	
	cout << "Replace returns (at index 0): " <<  list.replace('z', 0) << endl;
	
	list.remove(1);
	
	list.push_front('x');
	
	list.pop_back();
	
	list.pop_front();
	
	cop3530::CBL<char> const const_list = list;

    list.push_front('^');
	
	auto const_iter = const_list.begin();
    auto const_iter_1 = const_list.begin();

    cout << "Are const iterators equal?: " << (const_iter == const_iter_1) << endl;
	
	auto const_iter_end = const_list.end();

    cout << "Iterating thru const list: ";
	
	for(; const_iter != const_iter_end; const_iter++){
		cout  << *const_iter << " ";
		//*const_iter = 'a';
	}
	
	cout << endl;

    cout << "Are const iterators equal?: " << (const_iter == const_iter_1) << endl;

    cout << "Pre-increment dereference of const iterator: " << *++const_iter_1 << endl;

    cout << "Post-increment dereference of const iterator: " << *const_iter_1++ << endl;

    cout << "Now, it's pointing to: " << *const_iter_1 << endl;

    cout << "Iterating thru non-const list: ";
	
	for(char x: list){
		cout << x << " ";
	}
	
	cout << endl;
	
	cout << "Head of List: " << list.peek_front() << endl;
	
	cout << "Item at Position 2: " << list.item_at(2) << endl;
	
	cout << "Tail of List: " << list.peek_back() << endl;
	
	cout << "Is empty?: " << list.is_empty() << endl;
	
	cout << "Is full?: " << list.is_full() << endl;
	
	cout << "Length: " << list.length() << endl;
	
	cout << "Contain z? " << list.contains('z', fxn) << endl;
	
	cout << "Contain Z? " << list.contains('Z', fxn) << endl;

    cout << "Print function returns: ";

    list.print(std::cout) << endl;

    cout << "Contents of array returned from contents() fxn: ";
	
	char* array = list.contents();
	
	for(size_t i = 0; i < list.length(); i++){
		cout << array[i] << " ";  
	}
	
	cout << endl;
	
	list.clear();
	
	cout << "Length: " << list.length() << endl;

    cout << "Is empty?: " << list.is_empty() << endl;

	delete [] array;
   
    return 0;

}

