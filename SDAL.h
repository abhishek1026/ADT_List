//
// Created by Abhishek on 9/13/2017.
//

#ifndef COP3530_PROJECT_1_SDAL_H
#define COP3530_PROJECT_1_SDAL_H

#include "List.h"
#include <stdexcept>
#include <iostream>
using namespace std;

namespace cop3530{
    template<class T>
    class SDAL: public List<T>{
    private:

        T* arr;
        size_t tail = 0;
        size_t end_index;
        size_t original_capacity = 50;

    public:
            template<class DataT>
            class SDAL_Iter: public  std::iterator<std::forward_iterator_tag,DataT>{
            public:

                typedef DataT value_type;
                typedef std::ptrdiff_t difference_type;
                typedef DataT& reference;
                typedef DataT* pointer;
                typedef std::forward_iterator_tag iterator_category;

                typedef SDAL_Iter self_type;
                typedef SDAL_Iter& self_reference;

            private:
                size_t here;
                size_t tail;
                T* list;

            public:
                explicit SDAL_Iter(T* list, size_t begin, size_t end) {
                    this->list = list;
                    here = begin;
                    tail = end;
                }
                SDAL_Iter(const SDAL_Iter& src) {
                    list = src.list;
                    here = src.here;
                    tail = src.tail;
                }

                reference operator*() const {
                    if (here == tail) {
                        throw std::runtime_error("Can't evaluate (*) at null location!");
                    }
                    return list[here];
                }

                pointer operator->() const {
                    if (here == tail) {
                        throw std::runtime_error("Can't use -> operator with a null position");
                    }
                    return &(operator*());
                }

                self_reference operator=(SDAL_Iter<DataT>const& src) {
                    if(this == &src){
                        return *this;
                    }
                    here = src.here;
                    tail = src.tail;
                    list = src.list;
                    return *this;
                }

                self_reference operator++() {
                    if (here == tail) {
                        throw std::runtime_error("Can't use ++(pre) operator at null position");
                    }
                    here++;
                    return *this;
                }

                self_type operator++(int) {
                    if (here == tail) {
                        throw std::runtime_error("Can't use ++(post) operator with a null position");
                    }
                    SDAL_Iter<DataT> hold(*this);
                    here++;
                    return hold;
                }

                bool operator==(SDAL_Iter<DataT>const& test) const {
                    return (here == test.here && list == test.list) ;
                }

                bool operator!=(SDAL_Iter<DataT>const& test) const {
                    return (here != test.here || list != test.list);
                }
            };

        //typedef std::size_t size_t;
        typedef T value_type;
        typedef SDAL_Iter<T> iterator;
        typedef SDAL_Iter<T const> const_iterator;

        iterator begin(){
            return iterator(arr,0,tail);
        }
        iterator end(){
            return iterator(arr,tail,tail);
        }

        const_iterator begin() const{
            return const_iterator(arr,0, tail);
        }

        const_iterator end() const{
            return const_iterator(arr,tail, tail);
        }

        iterator grab(SDAL_Iter<T>& src){
            return iterator(src);
        }

        SDAL(size_t capacity = 50){

            this->end_index = capacity-1;
            this->arr = new T[capacity];
            this->original_capacity = capacity;
            cout << "Created a Simple Dynamic ArrayList!!!" << endl;

        }

        SDAL(const SDAL & src){
            tail = src.tail;
            end_index = src.end_index;
            original_capacity = src.original_capacity;
            this->arr = new T[end_index+1];

            for(size_t i = 0; i < src.length(); i++){
                arr[i] = src.arr[i];
            }

            cout << "Created a Simple Dynamic ArrayList (Copy CTR)!!!" << endl;
        }

        SDAL(SDAL&& src){

            tail = src.tail;
            end_index = src.end_index;
            original_capacity = src.original_capacity;
            this->arr = src.arr;

            src.arr = nullptr;

            src.tail = src.end_index = src.original_capacity = 0;

            cout << "Created a Simple Dynamic ArrayList (Move CTR)!!!" << endl;
        }

        ~SDAL(){
            delete [] this->arr;
            this->tail = this->end_index = 0;
            cout << "Destroying Simple Dynamic ArrayList!!!" << endl;
        }

        SDAL& operator=(const SDAL& src){
            if(this == &src){
                return *this;
            }

            clear();

            tail = src.tail;
            end_index = src.end_index;
            delete [] this->arr;
            this->arr = new T[end_index+1];

            for(size_t i = 0; i < src.length(); i++){
                arr[i] = src.arr[i];
            }

            return *this;
        }

        SDAL& operator=(SDAL&& src){
            if(this == &src){
                return *this;
            }

            clear();

            tail = src.tail;
            end_index = src.end_index;
            delete [] this->arr;
            this->arr = src.arr;

            src.arr = nullptr;

            src.tail = src.end_index = src.original_capacity = 0;

            return *this;
        }

        T const& operator[](size_t position) const {
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }


            return this->arr[position];
        }

        T& operator[](size_t position){
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }

            return this->arr[position];
        }

        size_t length() const{
            return this->tail;
        }

        bool reached_capacity()const{
            return (this->tail > this->end_index);
        }

        bool is_full()const{
            size_t curr_arr_length = this->end_index + 1;
            T* test = new(std::nothrow) T[2*curr_arr_length];
            if(!test)
                return true;

            delete [] test;
            return false;
        }

        bool is_empty()const{
            return (this->tail == 0);
        }

        void clear(){
            delete [] this->arr;
            this->arr = new T[this->end_index+1];
            this->tail = 0;
            return;
        }

        std::ostream& print(std::ostream& stream)const{
            if(length() == 0){
                stream << "<empty list>";
                return stream;
            }

            stream << "[";

            for(size_t i = 0; i < length(); i++){
                if(i+1 == this->tail){
                    stream << this->arr[i] << "]";
                    continue;
                }

                stream << this->arr[i] << ",";
            }
            return stream;
        }

        T& peek_back()const{
            if(is_empty()){
                throw std::runtime_error("Can't peek at back since SDAL is empty!");
            }
            return this->arr[tail-1];
        }

        T& peek_front()const{
            if(is_empty()){
                throw std::runtime_error("Can't peek at front since SDAL is empty!");
            }
            return this->arr[0];
        }

        T pop_back(){
            if(is_empty()){
                throw std::runtime_error("Can't pop at back since SDAL is empty!");
            }
            return this->arr[--this->tail];
        }

        T pop_front(){
            if(is_empty()){
                throw std::runtime_error("Can't pop at front since SDAL is empty!");
            }
            T result = this->arr[0];
            tail--;
            for(size_t i = 0; i < (tail); i++){
                this->arr[i] = this->arr[i+1];
            }

            return result;
        }

        void push_front(const T& item){
            if(reached_capacity()){
                if(is_full()){
                    throw std::runtime_error("Can't push at front since SDAL is full!");
                }
                size_t curr_arr_length = this->end_index + 1;
                T* new_arr = new T[2*curr_arr_length];

                for(size_t i = 0; i < length(); i++){
                    new_arr[i+1] = arr[i];
                }
                T* temp_arr = arr;
                this->arr = new_arr;
                delete temp_arr;
                arr[0] = item;
                this->tail = curr_arr_length+1;
                this->end_index = 2*curr_arr_length-1;
                return;
            }

            for(int i = static_cast<int>(tail); i > 0; i--){
                arr[i] = arr[i-1];
            }
            this->arr[0] = item;
            this->tail++;
            return;
        }

        void push_back(const T& item){
            if(reached_capacity()){
                if(is_full()) {
                    throw std::runtime_error("Can't push at back since SDAL is full!");
                }
                size_t curr_arr_length = this->end_index + 1;
                T* new_arr = new T[2*curr_arr_length];

                for(size_t i = 0; i < length(); i++){
                    new_arr[i] = arr[i];
                }
                T* temp_arr = arr;
                this->arr = new_arr;
                delete temp_arr;
                this->tail = curr_arr_length;
                this->arr[this->tail] = item;
                this->end_index = 2*curr_arr_length-1;
                this->tail++;
                return;
            }
            this->arr[this->tail++] = item;
            return;
        }

        T& item_at(size_t position)const{
            if(position < 0 || position >= length()){
                throw std::runtime_error("Invalid input for position in T SDAL::item_at(size_t position)!");
            }
            if(position == 0){
                return peek_front();
            }
            if(position == (length()-1)){
                return peek_back();
            }

            return arr[position];
        }

        T* contents()const{

            T* result = new T[length()];

            for(size_t i = 0; i < tail; i++){
                result[i] = arr[i];
            }

            return result;
        }

        T remove(size_t position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("Invalid input for position in T SDAL:remove(size_t position)!");
            }

            if(position == 0){
                return pop_front();
            }
            if((position + 1) == length()){
                return pop_back();
            }

            T result = arr[position];

            for(size_t i = position; i < (tail-1); i++){
                arr[i] = arr[i+1];
            }

            tail--;

            return result;
        }

        bool contains(const T& element, bool (*fxn)(const T&,const T&))const{
            for(size_t i = 0; i < tail; i++){
                if(fxn(element,arr[i]))
                    return true;
            }
            return false;
        }

        void insert(const T& element, size_t position){
            if(is_full()){
                throw std::runtime_error("Can't push at front since SDAL is full!");
            }
            if(position < 0 || position >= (length()+1)){
                throw std::runtime_error("Invalid input for position in void SDAL:insert(T element,size_t position)!");
            }
            if(position == 0){
                push_front(element);
                return;
            }
            if(position == length()){
                push_back(element);
                return;
            }

            if(reached_capacity()){
                size_t curr_arr_length = this->tail;

                T* new_arr = new T[2*curr_arr_length];

                for(size_t i = 0; i < length(); i++){
                    new_arr[i] = arr[i];
                }
                T* temp_array = arr;
                this->arr = new_arr;
                delete temp_array;
                this->end_index = 2*curr_arr_length-1;
            }


            T saveThis = arr[position];
            arr[position] = element;

            size_t temp_back = (this->tail);
            while(temp_back != (position)){
                temp_back--;
                if(temp_back == position){
                    arr[temp_back+1] = saveThis;
                }
                else{
                    arr[temp_back+1] = arr[(temp_back)];
                }

            }

            this->tail++;

            return;
        }

        T replace(const T& element, size_t position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("Invalid input for position in T SDAL::replace(size_t position)!");
            }

            T result = arr[position];
            arr[position] = element;
            return result;
        }

        static bool equals(const T& element, const T& test){
            return (element == test);
        }

    };
}

#endif //COP3530_PROJECT_1_SDAL_H
