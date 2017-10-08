//
// Created by Abhishek on 9/13/2017.
//

#ifndef COP3530_PROJECT_1_SDAL_H
#define COP3530_PROJECT_1_SDAL_H

#include "ADT_List.h"
#include <stdexcept>
#include <iostream>
using namespace std;

namespace cop3530{
template<class T>
class SDAL: public ADT_LIST<T>{
private:

    T* arr;
    size_t head = 0;
    size_t tail = 0;
    size_t end_index;

    size_t next_index(size_t x){
        if(x == this->end_index){
            return 0;
        }
        return x + 1;
    }

    size_t prev_index(size_t x){
        if(x == 0){
            return this->end_index;
        }
        return x - 1;
    }
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
        size_t edge;
        T* list;

    public:
        explicit SDAL_Iter(T* list, size_t begin, size_t end, size_t edge) {
            this->list = list;
            here = begin;
            tail = end;
            this->edge = edge;
        }
        SDAL_Iter(const SDAL_Iter& src) {
            this->list = src.list;
            here = src.here;
            tail = src.tail;
            edge = src.edge;
        }

        reference operator*() const {
            if (here == tail) {
                throw std::logic_error("Can't evaluate at null location!");
            }
            return list[here];
        }

        pointer operator->() const {
            if (here == tail) {
                throw std::logic_error("Can't use -> operator with a null position");
            }
            return &(operator*());
        }

        self_reference operator=(SDAL_Iter<DataT>const& src) {
            if(*this == src){
                return *this;
            }
            here = src.here;
            tail = src.tail;
            list = src.list;
            edge = src.edge;
            return *this;
        }

        self_reference operator++() {
            if (here == tail) {
                throw std::logic_error("Can't use ++(pre) operator at null position");
            }
            here = (here == edge) ? 0 : here + 1;
            return *this;
        }

        self_type operator++(int) {
            if (here == tail) {
                throw std::logic_error("Can't use ++(post) operator with a null position");
            }
            SDAL_Iter<DataT> hold(*this);
            here = (here == edge) ? 0 : here + 1;
            return hold;
        }

        bool operator==(SDAL_Iter<DataT>const& test) const {
            return (here == test.here && list == test.list) ;
        }

        bool operator!=(SDAL_Iter<DataT>const& test) const {
            return (here != test.here || list != test.list);
        }
    };

    typedef std::size_t size_t;
    typedef T value_type;
    typedef SDAL_Iter<T> iterator;
    typedef SDAL_Iter<T const> const_iterator;

    iterator begin(){
        return iterator(arr,head,tail,end_index);
    }
    iterator end(){
        return iterator(arr,tail,tail,end_index);
    }

    const_iterator begin() const{
        return const_iterator(arr,head, tail,end_index);
    }

    const_iterator end() const{
        return const_iterator(arr,tail, tail,end_index);
    }

    iterator grab(SDAL_Iter<T>& src){
        return iterator(src);
    }
    SDAL(size_t capacity = 50){

        this->end_index = capacity;
        this->arr = new T[capacity+1];
        cout << "Created a Simple Dynamic ArrayList!!!" << endl;

    }

    ~SDAL(){
        delete [] this->arr;
        this->head = this->tail = this->end_index = 0;
        cout << "Destroying Simple Dynamic ArrayList!!!" << endl;
    }

    size_t length(){
        if(this->head == this->tail)
            return 0;
        else if(this->head < this->tail){
            return this->tail - this->head;
        }
        else{
            return ((this->end_index+1) - this->head + this->tail);
        }
    }

    bool reached_capacity(){
        return (next_index(this->tail) == this->head);
    }

    bool is_full(){
        size_t curr_arr_length = this->end_index + 1;
        T* test = new(std::nothrow) T[2*curr_arr_length];
        if(!test)
            return true;

        delete [] test;
        return false;
    }

    bool is_empty(){
        return (this->head == this->tail);
    }

    void clear(){
        delete [] this->arr;
        this->arr = new T[this->end_index+1];
        this->head = this->tail = 0;
        return;
    }

    void print(ostream& stream){
        if(length() == 0){
            stream << "<empty list>" << endl;
            return;
        }

        stream << "[";

        for(size_t i = this->head; i != this->tail; i= next_index(i)){
            if(next_index(i) == this->tail){
                cout << this->arr[i] << "]" << endl;
                continue;
            }

            cout << this->arr[i] << ", ";
        }
        return;
    }

    T peek_back(){
        if(is_empty()){
            throw std::runtime_error("Can't peek at back since SDAL is empty!");
        }
        return this->arr[prev_index(this->tail)];
    }

    T peek_front(){
        if(is_empty()){
            throw std::runtime_error("Can't peek at front since SDAL is empty!");
        }
        return this->arr[this->head];
    }

    T pop_back(){
        if(is_empty()){
            throw std::runtime_error("Can't pop at back since SDAL is empty!");
        }
        this->tail = prev_index(this->tail);
        return this->arr[this->tail];
    }

    T pop_front(){
        if(is_empty()){
            throw std::runtime_error("Can't peek at front since SDAL is empty!");
        }
        T result = this->arr[this->head];
        this->head = next_index(this->head);
        return result;
    }

    void push_front(T item){
        if(reached_capacity()){
            if(is_full()){
                throw std::runtime_error("Can't push at front since SDAL is full!");
            }
            size_t curr_arr_length = this->end_index + 1;
            T* new_arr = new T[2*curr_arr_length];

            for(size_t i = 0, j = this->head; j != this->tail; i++,j = next_index(j)){
                new_arr[i+1] = arr[j];
            }
            this->arr = new_arr;
            this->head = 0;
            arr[this->head] = item;
            this->tail = curr_arr_length;
            this->end_index = 2*curr_arr_length-1;
            return;
        }

        this->head = prev_index(this->head);
        this->arr[this->head] = item;
        return;
    }

    void push_back(T item){
        if(reached_capacity()){
            if(is_full()) {
                throw std::runtime_error("Can't push at back since SDAL is full!");
            }
            size_t curr_arr_length = this->end_index + 1;
            T* new_arr = new T[2*curr_arr_length];

            for(size_t i = 0, j = this->head; j != this->tail; i++,j = next_index(j)){
                new_arr[i] = arr[j];
            }
            this->arr = new_arr;
            this->tail = this->end_index;
            this->arr[this->tail] = item;
            this->end_index = 2*curr_arr_length-1;
            this->tail = next_index(this->tail);
            this->head = 0;
            return;
        }
        this->arr[this->tail] = item;
        this->tail = next_index(this->tail);
        return;
    }

    T item_at(unsigned int position){
        if(position < 0 || position >= length()){
            throw std::runtime_error("Invalid input for position in T SDAL::item_at(unsigned int position)!");
        }
        if(position == 0){
            return peek_front();
        }
        if(position == (length()-1)){
            return peek_back();
        }
        int displacement = static_cast<int>(position);
        size_t temp_head = this->head;
        while(--displacement>=0)
            temp_head = next_index(temp_head);
        return arr[temp_head];
    }

    T* contents(){

        if(length() == 0)
            throw std::runtime_error("Can't return contents as SDAL is currently empty!");

        T* result = new T[length()];

        size_t traverse = this->head;
        size_t count = 0;
        while(traverse != this->tail){
            result[count] = arr[traverse];
            traverse = next_index(traverse);
            count++;
        }

        return result;
    }

    T remove(unsigned int position){
        if(position < 0 || position >= length()){
            throw std::runtime_error("Invalid input for position in T SDAL:remove(unsigned int position)!");
        }

        if(position == 0){
            return pop_front();
        }
        if((position + 1) == length()){
            return pop_back();
        }
        size_t temp = this->head;
        int cnt = static_cast<int>(position);
        while(--cnt>=0){
            temp = next_index(temp);
        }


        T result = arr[temp];
        while(next_index(temp) != this->tail){
            arr[temp] = arr[next_index(temp)];
            temp = next_index(temp);
        }
        this->tail = temp;
        return result;
    }

    bool contains(T element, bool (*fxn)(T,T)){
        for(int i = this->head; i != this->tail; i = next_index(i)){
            if(fxn(element,arr[i]))
                return true;
        }
        return false;
    }

    void insert(T element, unsigned int position){
        if(is_full()){
            throw std::runtime_error("Can't push at front since SDAL is full!");
        }
        if(position < 0 || position >= (length()+1)){
            throw std::runtime_error("Invalid input for position in void SDAL:insert(T element,unsigned int position)!");
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
            size_t curr_arr_length = this->end_index + 1;
            T* new_arr = new T[2*curr_arr_length];

            for(size_t i = 0, j = this->head; j != this->tail; i++,j = next_index(j)){
                new_arr[i] = arr[j];
            }
            this->arr = new_arr;
            this->head = 0;
            this->tail = this->end_index;
            this->end_index = 2*curr_arr_length-1;
        }

        int cnt = static_cast<int>(position);
        size_t temp = this->head;

        while(--cnt >= 0){
            temp = next_index(temp);
        }

        T saveThis = arr[temp];
        arr[temp] = element;

        size_t temp_back = (this->tail);
        while(temp_back != (temp)){
            temp_back = prev_index(temp_back);
            if(temp_back == temp){
                arr[next_index(temp_back)] = saveThis;
            }
            else{
                arr[next_index(temp_back)] = arr[(temp_back)];
            }

        }

        this->tail = next_index(this->tail);

        return;
    }

    T replace(T element, unsigned int position){
        if(position < 0 || position >= length()){
            throw std::runtime_error("Invalid input for position in T SDAL::replace(unsigned int position)!");
        }

        int displacement = static_cast<int>(position);
        size_t temp_head = this->head;
        while(--displacement>=0)
            temp_head = next_index(temp_head);
        T result = arr[temp_head];
        arr[temp_head] = element;
        return result;
    }

    static bool equals(T element, T test){
        return (element == test);
    }


};
}

#endif //COP3530_PROJECT_1_SDAL_H