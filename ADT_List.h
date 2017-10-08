//
// Created by Abhishek on 9/10/2017.
//

#ifndef COP3530_PROJECT_1_ADT_LIST_H
#define COP3530_PROJECT_1_ADT_LIST_H

using namespace std;

namespace cop3530{
    template <class T>
    class ADT_LIST{

    public:
        ADT_LIST(){

            cout << "Created an ADT List!!!" << endl;

        }

        virtual ~ADT_LIST(){

            cout << "Destroying ADT List!!!" << endl;

        };

        virtual size_t length() = 0;

        virtual bool is_empty() = 0;

        virtual bool is_full() = 0;

        virtual void clear() = 0;

        virtual void print(ostream& stream) = 0;

        virtual T peek_back() = 0;

        virtual T peek_front() = 0;

        virtual T pop_back() = 0;

        virtual T pop_front() = 0;

        virtual void push_front(T item)= 0;

        virtual void push_back(T item)= 0;

        virtual T item_at(unsigned int position) = 0;

        virtual T* contents() = 0;

        virtual T remove(unsigned int position) = 0;

        virtual bool contains(T element, bool (*fxn)(T,T)) = 0;

        virtual void insert(T element, unsigned int position) = 0;

        virtual T replace(T element, unsigned int position) = 0;

    };
}
#endif //COP3530_PROJECT_1_ADT_LIST_H
