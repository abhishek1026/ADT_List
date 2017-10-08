//
// Created by Abhishek on 9/8/2017.
//

#ifndef COP3530_PROJECT_1_SLL_H
#define COP3530_PROJECT_1_SLL_H
#include <iostream>
#include <stdexcept>
#include "ADT_List.h"
using namespace std;

namespace cop3530{
    template <class T>
    class SLL: public ADT_LIST<T>{

    private:
        struct Node {
            T data;
            Node *next;
        };
        typedef struct Node *NodePtr;

        NodePtr head = nullptr;
        NodePtr tail = nullptr;


    public:
            template<class DataT>
            class SSLL_Iter: public  std::iterator<std::forward_iterator_tag,DataT>{
            public:

                typedef DataT value_type;
                typedef std::ptrdiff_t difference_type;
                typedef DataT& reference;
                typedef DataT* pointer;
                typedef std::forward_iterator_tag iterator_category;

                typedef SSLL_Iter self_type;
                typedef SSLL_Iter& self_reference;

            private:
                Node* here;

            public:
                explicit SSLL_Iter(Node* start = nullptr) {
                    here = start;
                }
                SSLL_Iter(const SSLL_Iter& src) {
                    here = src.here;
                }

                reference operator*() const {
                    if (!here) {
                        throw std::logic_error("Can't evaluate at null node location!");
                    }
                    return here->data;
                }

                pointer operator->() const {
                    if (!here) {
                        throw std::logic_error("Can't use -> operator with a null node");
                    }
                    return &(here->data);
                }

                self_reference operator=(SSLL_Iter<DataT>const& src) {
                    if (*this == src) {
                        return *this;
                    }
                    here = src.here;
                    return *this;
                }

                self_reference operator++() {
                    if (!here) {
                        throw std::logic_error("Can't use ++(pre) operator at null position");
                    }
                    here = here->next;
                    return *this;
                }

                self_type operator++(int) {
                    if (!here) {
                        throw std::logic_error("Can't use ++(post) operator with a null node");
                    }
                    SSLL_Iter<DataT> hold(*this);
                    here = here->next;
                    return hold;
                }

                bool operator==(SSLL_Iter<DataT>const& test) const {
                    return here == test.here;
                }

                bool operator!=(SSLL_Iter<DataT>const& test) const {
                    return here != test.here;
                }
            };

        typedef std::size_t size_t;
        typedef T value_type;
        typedef SSLL_Iter<T> iterator;
        typedef SSLL_Iter<T const> const_iterator;

        iterator begin(){
            return iterator(head);
        }
        iterator end(){
            return iterator();
        }

        const_iterator begin() const{
            return const_iterator(head);
        }

        const_iterator end() const{
            return const_iterator();
        }

        iterator grab(SSLL_Iter<T>& src){
            return SSLL_Iter<T>(src);
        }

        SLL(){

            cout << "Created a Simple Singly Linked-List!!!" << endl;

        }

        SLL(const SLL& src) {

            cout << "Created a Simple Singly Linked-List!!!" << endl;

            head = nullptr;
            tail = nullptr;
            Node* temp = src.head;
            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }
        }

        ~SLL(){

            cout << "Destroying Simple Singly Linked-List!!!" << endl;

            NodePtr temp = this->head;

            while(temp!= nullptr){
                NodePtr deleteThis = temp;
                temp = deleteThis->next;
                delete  deleteThis;
            }

            this->head = this->tail = nullptr;

        }

        SLL& operator=(const SLL& src) {
            if (&src == this)
                return *this;

            clear();
            Node* temp = src.head;
            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }
            return *this;

        }

        T& operator[](size_t position) {
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }
            Node* temp = head;

            int cnt = position;

            while(--cnt >= 0){
                temp = temp->next;
            }

            return temp->data;
        }

        size_t length(){
            if(this->head == nullptr){
                return 0;
            }
            NodePtr temp = this->head;
            size_t cnt = 0;
            while(temp != nullptr){
                cnt++;
                temp = temp->next;
            }

            return cnt;
        }

        bool is_empty(){
            return (this->head == nullptr);
        }

        bool is_full(){
            NodePtr test = new(std::nothrow) Node;
            if(!test)
                return true;

            delete test;
            return false;
        }

        void clear(){

            NodePtr temp = this->head;

            while(temp!= NULL){
                NodePtr deleteThis = temp;
                temp = deleteThis->next;
                delete  deleteThis;
            }

            this->head = this->tail = NULL;

            return;
        }

        void print(ostream& stream){
            if(is_empty()){
                stream << "<empty list>" << endl;
                return;
            }

            NodePtr temp = this->head;

            stream << "[";

            while(temp->next != NULL){
                stream << temp->data << ", ";
                temp = temp->next;
            }

            stream << temp->data << "]" << endl;

            return;
        }

        T peek_back(){
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't peek at back of SLL because SLL is empty!!!");
            }
            return this->tail->data;
        }

        T peek_front(){
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't peek at front of SLL because SLL is empty!!!");
            }
            return this->head->data;
        }

        T pop_back(){
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't pop at back of SLL because SLL is empty!!!");
            }

            if(length() == 1){
                T result = this->tail->data;
                NodePtr deleteThis = this->tail;
                delete deleteThis;
                this->head = nullptr;
                this->tail = nullptr;
                return result;
            }

            NodePtr temp = this->head;

            while(temp->next->next != nullptr){
                temp = temp->next;
            }

            T result = temp->next->data;
            NodePtr deleteThis = temp->next;
            temp->next = nullptr;
            this->tail = temp;
            delete deleteThis;
            return result;
        }

        T pop_front(){

            if(is_empty()){
                throw std::runtime_error("ERROR: Can't pop at front of SLL because SLL is empty!!!");
            }
            if(length() == 1){
                this->tail = nullptr;
            }
            T result = this->head->data;
            NodePtr newHead = this->head->next;
            delete this->head;
            this->head = newHead;
            return result;
        }

        void push_front(T item){
            if(is_full()){
                throw std::runtime_error("ERROR: Can't push at front of SLL because SSL is full!!!");
            }
            NodePtr newNode = new Node;
            newNode->data = item;
            newNode->next = this->head;
            this->head = newNode;
            if(this->tail == nullptr){
                this->tail = newNode;
            }
            return;

        }

        void push_back(T item){
            if(is_full()){
                throw std::runtime_error("ERROR: Can't push at back of SLL because SSL is full!!!");
            }
            NodePtr newNode = new Node;
            newNode->data = item;
            if(this->tail != nullptr){
                this->tail->next = newNode;
            }
            else{
                this->head = newNode;
            }
            newNode->next = nullptr;
            this->tail = newNode;
            return;
        }

        T item_at(unsigned int position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid Input for position in T SLL::item_at(unsigned int position)!!!");
            }

            if(position == 0){
                return peek_front();
            }
            if((position + 1) == length()){
                return peek_back();
            }

            int cnt = static_cast<int>(position);
            NodePtr temp = this->head;
            while(--cnt>=0){
                temp = temp->next;
            }

            return temp->data;

        }

        T* contents(){
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't return contents because SLL is empty!!!");
            }

            T* arr = new T[length()];
            NodePtr temp = this->head;
            for(int i = 0; i < length(); i++){
                arr[i] = temp->data;
                temp = temp->next;
            }

            return arr;
        }

        T remove(unsigned int position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid input for position in T SLL:remove(unsigned int position)!!!");
            }

            if(position == 0){
                return pop_front();
            }
            if((position + 1) == length()){
                return pop_back();
            }
            NodePtr temp = this->head;
            int cnt = static_cast<int>(position);
            while(--cnt>0){
                temp = temp->next;
            }

            NodePtr removeThis = temp->next;
            T result = removeThis->data;
            NodePtr newNext = removeThis->next;
            temp->next = newNext;
            removeThis->next = nullptr;
            delete removeThis;
            return result;
        }

        bool contains(T element, bool (*equals)(T,T)){
            if(is_empty()){
                return false;
            }

            NodePtr temp = this->head;

            while(temp != nullptr){
                if(equals(element, temp->data)){
                    return true;
                }
                temp = temp->next;
            }

            return false;
        }

        void insert(T element, unsigned int position){
            if(position < 0 || position >= (length()+1)){
                throw std::runtime_error("ERROR: Invalid input for position in void SLL:insert(T element,unsigned int position)!!!");

            }
            if(position == 0){
                push_front(element);
                return;
            }
            if(position == length()){
                push_back(element);
                return;
            }
            int cnt = static_cast<int>(position);
            NodePtr temp = this->head;
            while(--cnt > 0){
                temp = temp->next;
            }
            NodePtr newNode = new(std::nothrow) Node;
            if(!newNode)
                return;

            newNode->data = element;
            NodePtr oldNext = temp->next;
            temp->next = newNode;
            newNode->next = oldNext;
            return;
        }

        T replace(T element, unsigned int position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid Input for position in T SLL:replace(T element,unsigned int position)!!!");
            }
            int cnt = static_cast<int>(position);
            NodePtr temp = this->head;

            while(--cnt >= 0){
                temp = temp->next;
            }

            T result = temp->data;
            temp->data = element;
            return result;
        }

        static bool equals(T element, T test){
            return (element == test);
        }



    };

}


#endif //COP3530_PROJECT_1_SLL_H