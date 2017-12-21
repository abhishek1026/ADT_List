//
// Created by Abhishek on 9/10/2017.
//

#ifndef COP3530_PROJECT_1_ADT_LIST_H
#define COP3530_PROJECT_1_ADT_LIST_H

using namespace std;
#include <iostream>

namespace cop3530{
    template <class T>
    class List{

    public:
        List(){

            std::cout << "Created an ADT List!!!" << std::endl;

        }

        virtual ~List(){

            std::cout << "Destroying ADT List!!!" << std::endl;

        };

        virtual size_t length() const = 0;

        virtual bool is_empty() const = 0;

        virtual bool is_full() const = 0;

        virtual void clear() = 0;

        virtual std::ostream& print(std::ostream& stream) const = 0;
		
        virtual T& peek_back() const = 0;

        virtual T& peek_front() const = 0;

        virtual T pop_back() = 0;

        virtual T pop_front() = 0;

        virtual void push_front(const T& item)= 0;

        virtual void push_back(const T& item)= 0;

        virtual T& item_at(size_t position) const = 0;

        virtual T* contents() const = 0;

        virtual T remove(size_t position) = 0;

        virtual bool contains(const T& element, bool (*fxn)(const T&,const T&)) const = 0;

        virtual void insert(const T& element, size_t position) = 0;

        virtual T replace(const T& element, size_t position) = 0;

        virtual T& operator[](size_t position) = 0;

        virtual T const& operator[](size_t position) const = 0;

    };
}


#endif //COP3530_PROJECT_1_ADT_LIST_H
