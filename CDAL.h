//
// Created by Abhishek on 9/13/2017.
//

#ifndef COP3530_PROJECT_1_CDAL_H
#define COP3530_PROJECT_1_CDAL_H

#include "List.h"
#include <stdexcept>
#include <iostream>
using namespace std;

namespace cop3530{
    template<class T>
    class CDAL: public List<T>{
    private:

        struct Node {
            T* data;
            Node* next;
        };

        typedef struct Node* NodePtr;

        NodePtr head_node;
        NodePtr tail_node;
        size_t tail;
        size_t arr_length;

    public:
        template<class DataT>
        class CDAL_Iter: public  std::iterator<std::forward_iterator_tag,DataT>{
        public:

            typedef DataT value_type;
            typedef std::ptrdiff_t difference_type;
            typedef DataT& reference;
            typedef DataT* pointer;
            typedef std::forward_iterator_tag iterator_category;

            typedef CDAL_Iter self_type;
            typedef CDAL_Iter& self_reference;

        private:
            size_t curr_index;
            size_t last_index;
            size_t arr_len;
            NodePtr curr_node;

        public:
            explicit CDAL_Iter(NodePtr node, size_t curr, size_t end, size_t len){
                curr_node = node;
                curr_index = curr;
                last_index = end;
                arr_len = len;
            }
            CDAL_Iter(const CDAL_Iter& src) {
                curr_node = src.curr_node;
                curr_index = src.curr_index;
                last_index = src.last_index;
                arr_len = src.arr_len;
            }

            reference operator*() const {
                if (curr_index == last_index) {
                    throw std::runtime_error("Can't evaluate (*) at null location!");
                }
                return curr_node->data[curr_index % arr_len];
            }

            pointer operator->() const {
                if (curr_index == last_index) {
                    throw std::runtime_error("Can't use -> operator on a null location!");
                }
                return &(operator*());
            }

            self_reference operator=(CDAL_Iter<DataT>const& src) {
                if(this == &src){
                    return *this;
                }
                curr_index = src.curr_index;
                last_index = src.last_index;
                curr_node = src.curr_node;
                arr_len = src.arr_len;
                return *this;
            }

            self_reference operator++() {
                if (curr_index == last_index) {
                    throw std::runtime_error("Can't use ++(pre) operator at null position");
                }
                curr_index+= 1;
                if(curr_index % arr_len == 0)
                    curr_node = curr_node->next;
                return *this;
            }

            self_type operator++(int) {
                if (curr_index == last_index) {
                    throw std::runtime_error("Can't use ++(post) operator with a null node");
                }
                CDAL_Iter<DataT> hold(*this);
                curr_index+= 1;
                if(curr_index % arr_len == 0)
                    curr_node = curr_node->next;
                return hold;
            }

            bool operator==(CDAL_Iter<DataT>const& test) const {
                return (curr_index == test.curr_index && curr_node == test.curr_node);
            }

            bool operator!=(CDAL_Iter<DataT>const& test) const {
                return !(operator==(test));
            }
        };

        //typedef std::size_t size_t;
        typedef T value_type;
        typedef CDAL_Iter<T> iterator;
        typedef CDAL_Iter<T const> const_iterator;

        iterator begin(){
            return iterator(head_node,0,tail,arr_length);
        }
        iterator end(){
            return iterator(tail_node,tail,tail,arr_length);
        }

        const_iterator begin() const{
            return const_iterator(head_node,0,tail,arr_length);
        }

        const_iterator end() const{
            return const_iterator(tail_node,tail,tail,arr_length);
        }

        iterator grab(CDAL_Iter<T> const& src){
            return iterator(src);
        }


         CDAL(size_t capacity = 50){
             if(capacity <= 1)
                 throw std::runtime_error("Error constructing CDAL (Invalid argument passed to constructor!)");
             this->arr_length = capacity;
             NodePtr firstNode = new Node;
             firstNode->data = new T[capacity];
             firstNode->next = nullptr;
             head_node = tail_node = firstNode;
             this->tail = 0;

             cout << "Created Chained Dynamic ArrayList!!!" << endl;
        }

        ~CDAL(){
            NodePtr temp = head_node;
            while(temp != nullptr){
                NodePtr next_temp = temp->next;
                delete [] temp->data;
                delete temp;
                temp = next_temp;
            }

            head_node = tail_node = nullptr;

            this->tail = this->arr_length = 0;

            cout << "Destroying Chained Dynamic ArrayList!!!" << endl;
        }

        CDAL(const CDAL & src){

            NodePtr firstNode = new Node;
            firstNode->data = new T[src.arr_length];
            firstNode->next = nullptr;
            head_node = tail_node = firstNode;

            tail = 0;
            arr_length = src.arr_length;

            for(size_t i = 0; i < src.tail; i++){
                push_back(src.item_at(i));
            }

            cout << "Created Chained Dynamic ArrayList (Copy CTR)!!!" << endl;

        }

        CDAL(CDAL&& src){

            this->head_node = src.head_node;
            this->tail_node = src.tail_node;
            this->tail = src.tail;
            this->arr_length = src.arr_length;

            src.head_node = src.tail_node = nullptr;

            src.tail = src.arr_length = 0;

            cout << "Created Chained Dynamic ArrayList (Move CTR)!!!" << endl;

        }

        CDAL& operator=(const CDAL& src){
            if(this == &src){
                return *this;
            }

            clear();

            delete [] head_node->data;
            delete head_node;

            NodePtr firstNode = new Node;
            firstNode->data = new T[src.arr_length];
            firstNode->next = nullptr;
            head_node = tail_node = firstNode;

            tail = 0;
            arr_length = src.arr_length;

            for(size_t i = 0; i < src.tail; i++){
                push_back(src.item_at(i));
            }

            return *this;
        }

        CDAL& operator=(CDAL&& src){

            if(this == &src){
                return *this;
            }

            clear();

            delete [] head_node->data;
            delete head_node;

            this->head_node = src.head_node;
            this->tail_node = src.tail_node;
            this->tail = src.tail;
            this->arr_length = src.arr_length;

            src.head_node = src.tail_node = nullptr;

            src.tail = src.arr_length = 0;

        }

        T const& operator[](size_t position) const {
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }

            T grab = item_at(position);

            T& result = grab;

            return result;
        }

        T& operator[](size_t position){
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }

            T grab = item_at(position);

            T& result = grab;

            return result;
        }

        void push_back(const T& element){
            if(is_full() && ((this->tail + 1) % this->arr_length == 0))
                throw std::runtime_error("Can't push at back of CDAL since it is full!");
            this->tail_node->data[this->tail % this->arr_length] = element;
            this->tail++;
            if(reached_capacity()){
                NodePtr newLastNode = new Node;
                newLastNode->data = new T[this->arr_length];
                newLastNode->next = nullptr;
                this->tail_node->next = newLastNode;
                this->tail_node = newLastNode;
            }
            
            return;

        }

        std::ostream& print(std::ostream& stream)const{
            if(this->tail == 0){
                stream << "<empty list>";
                return stream;
            }

            stream << "[";

            NodePtr temp = head_node;
            int count = static_cast<int>(this->tail);
            int arr_len = static_cast<int>(this->arr_length);

            for(int i = 0; i < count; i++){
                if((i % arr_len == 0) && i > 0)
                    temp = temp->next;
                if(i != (count - 1)){
                    stream << temp->data[i % arr_len] << ",";
                }
                else{
                    stream << temp->data[i % arr_len] << "]";
                }
            }

            return stream;
        }

        T& item_at(size_t position)const{
            if(position < 0 || position >= this->tail){
                throw std::runtime_error("Error: Invalid input for position in T CDAL<T>::item_at(size_t position)!");
            }
            NodePtr temp = this->head_node;
            int test = static_cast<int>(position);
            int arr_len = static_cast<int>(this->arr_length);
            while((test / arr_len) > 0){
                test-= this->arr_length;
                temp = temp->next;
            }

            return temp->data[test];
        }

        size_t length() const{
            return this->tail;
        }

        T replace(const T& element, size_t position){
            if(position < 0 || position >= this->tail){
                throw std::runtime_error("Error: Invalid input for position in T CDAL<T>::replace(T element, size_t position)!");
            }
            NodePtr temp = this->head_node;
            int test = static_cast<int>(position);
            int arr_len = static_cast<int>(this->arr_length);
            while((test/arr_len)> 0){
                test-= arr_len;
                temp = temp->next;
            }
            T result = temp->data[test];
            temp->data[test] = element;
            return result;
        }

        T pop_back() {
            if (is_empty()) {
                throw std::runtime_error("Can't pop from back of CDAL since it is empty!");
            }
            this->tail--;
            size_t temp_mod = this->tail % this->arr_length;
            if ((temp_mod+1) % this->arr_length == 0) {
                NodePtr temp = this->head_node;
                while (temp->next != tail_node) {
                    temp = temp->next;
                }
                temp->next = nullptr;
                delete [] this->tail_node->data;
                delete this->tail_node;
                this->tail_node = temp;
            }

            return this->tail_node->data[temp_mod];

        }

        T pop_front() {
            return remove(0);
        }

        bool is_empty()const{
            return (this->tail == 0);
        }

        bool is_full()const{
            T* test = new(std::nothrow) T[this->arr_length];
            if(!test)
                return true;

            delete [] test;
            return false;
        }

        bool reached_capacity()const{
            return ((this->tail) % this->arr_length == 0 && this->tail != 0);
        }

        void clear(){
            NodePtr temp = head_node;
            while(temp != nullptr){
                NodePtr next_temp = temp->next;
                delete [] temp->data;
                delete temp;
                temp = next_temp;
            }

            NodePtr newFirst = new Node;
            newFirst->data = new T[this->arr_length];
            newFirst->next = nullptr;
            head_node = tail_node = newFirst;

            this->tail = 0;
        }

        bool contains(const T& element, bool (*fxn)(const T&,const T&))const{

            NodePtr temp = head_node;
            int count = static_cast<int>(this->tail);

            for(int i = 0; i < count; i++){
                if((i % this->arr_length == 0) && i > 0)
                    temp = temp->next;
                if(fxn(temp->data[i % this->arr_length],element))
                    return true;
            }

            return false;
        }

        T* contents()const{
            T* result = new T[length()];

            NodePtr temp = head_node;
            int count = static_cast<int>(this->tail);

            for(int i = 0; i < count; i++){
                if((i % this->arr_length == 0) && i > 0)
                    temp = temp->next;
                result[i] = temp->data[i % this->arr_length];
            }

            return result;
        }

        T& peek_front()const{
            if(is_empty()){
                throw std::runtime_error("Can't peek at front of CDAL since it is empty!");
            }

            return head_node->data[0];
        }

        T& peek_back()const{
            if(is_empty()){
                throw std::runtime_error("Can't peek at back of CDAL since it is empty!");
            }

            if(reached_capacity()){
                NodePtr temp = this->head_node;
                while(temp->next != this->tail_node){
                    temp = temp->next;
                }
                return temp->data[this->arr_length-1];
            }

            return tail_node->data[(this->tail-1) % this->arr_length];
        }

        T remove(size_t position){
            if(position < 0 || position >= this->tail){
                throw std::runtime_error("Invalid input for position in T CDAL:remove(size_t position)!");
            }

            if((position + 1) == this->tail){
                return pop_back();
            }

            bool change_back = false;

            if(reached_capacity())
                change_back = true;

            T result = item_at(position);
            this->tail--;

            NodePtr temp = this->head_node;
            int test = static_cast<int>(position);
            int arr_len = static_cast<int>(this->arr_length);
            while((test / arr_len) > 0){
                test-= this->arr_length;
                temp = temp->next;
            }

            for(size_t i = position; i < this->tail; i++){
                if((i+1) % this->arr_length == 0){
                    temp->data[i % this->arr_length] = temp->next->data[0];
                    temp = temp->next;
                }
                else{
                    temp->data[i % this->arr_length] = temp->data[(i % this->arr_length) + 1];
                }
            }

            if(change_back){
                NodePtr old_last = this->tail_node;
                this->tail_node = temp;
                this->tail_node->next = nullptr;
                delete [] old_last->data;
                delete old_last;
            }

            return result;

        }

        void insert(const T& element, size_t position){
            if(position < 0 || position >= (this->tail+1)){
                throw std::runtime_error("Invalid input for position in T CDAL:insert(size_t position)!");
            }

            if((position) == this->tail){
                push_back(element);
                return;
            }

            bool change_back = false;

            if((this->tail+1) % this->arr_length == 0)
                change_back = true;

            NodePtr temp = this->head_node;
            int test = static_cast<int>(position);
            int arr_len = static_cast<int>(this->arr_length);
            while((test / arr_len) > 0){
                test-= this->arr_length;
                temp = temp->next;
            }

            T carry_over_1, carry_over_2;
            while(true){
                if(test>=0){
                    for(int i = arr_len - 1; i >= test; i--){
                        if(i == arr_len -1){
                            carry_over_1 = temp->data[i];
                        }

                        if(i == test){
                            temp->data[i] = element;
                            continue;
                        }

                        temp->data[i] = temp->data[i-1];

                    }
                    test = -1;
                }
                else{
                    for(int i = arr_len - 1; i >= 0; i--){
                        if(i == 0){
                            temp->data[i] = carry_over_1;
                            carry_over_1 = carry_over_2;
                            continue;
                        }

                        if(i == arr_len -1){
                            carry_over_2 = temp->data[i];
                        }

                        temp->data[i] = temp->data[i-1];

                    }
                }
                if(temp->next == nullptr){
                    break;
                }
                temp = temp->next;
            }

            this->tail++;

            if(change_back){
                NodePtr new_last = new Node;
                new_last->data = new T[this->arr_length];
                new_last->next = nullptr;
                temp->next = new_last;
                this->tail_node = new_last;
            }
            
            return;


        }

        void push_front(const T& element){
            insert(element,0);
            return;
        }
        
        static bool equals(const T& element, const T& test){
            return (element == test);
        }

    };
}
#endif //COP3530_PROJECT_1_CDAL_H
