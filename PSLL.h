//
// Created by Abhishek on 9/11/2017.
//

#ifndef COP3530_PROJECT_1_PSLL_H
#define COP3530_PROJECT_1_PSLL_H

#include <iostream>
#include <stdexcept>
#include "List.h"
using namespace std;

namespace cop3530{
    template <class T>
    class PSLL: public List<T>{

    private:
        struct Node {
            T data;
            Node *next;
        };
        typedef struct Node *NodePtr;

        NodePtr head = nullptr;
        NodePtr tail = nullptr;
        NodePtr free = nullptr;

        void send_to_pool(NodePtr data){

            if(grab_pool_length() >= 50){
                delete data;
                return;
            }
            //cout << "Sending Node back to Pool!" << endl;
            if(this->free == nullptr){
                this->free = data;
                this->free->next = nullptr;
                return;
            }

            NodePtr temp = this->free;

            while(temp->next != nullptr){
                temp = temp->next;
            }

            temp->next = data;
            temp->next->next = nullptr;
            return;
        }

        NodePtr grab_from_pool(){
            if(grab_pool_length() == 0){
                Node* newNode = new(std::nothrow) Node;
                if(!newNode){
                    throw std::runtime_error("Pool is empty and out of external memory!");
                }
                return newNode;
            }
            NodePtr takeFree = this->free;
            this->free = takeFree->next;
            takeFree->next = nullptr;
            //cout << "Grabbing Node from Pool!" << endl;
            return takeFree;
        }

    public:
            template<class DataT>
            class PSLL_Iter: public  std::iterator<std::forward_iterator_tag,DataT>{
            public:

                typedef DataT value_type;
                typedef std::ptrdiff_t difference_type;
                typedef DataT& reference;
                typedef DataT* pointer;
                typedef std::forward_iterator_tag iterator_category;

                typedef PSLL_Iter self_type;
                typedef PSLL_Iter& self_reference;

            private:
                Node* here;

            public:
                explicit PSLL_Iter(Node* start = nullptr) {
                    here = start;
                }

                PSLL_Iter(const PSLL_Iter& src) {
                    here = src.here;
                }

                reference operator*() const {
                    if (!here) {
                        throw std::runtime_error("Can't evaluate (*) at null node location!");
                    }
                    return here->data;
                }

                pointer operator->() const {
                    if (!here) {
                        throw std::runtime_error("Can't use -> operator with a null node");
                    }
                    return &(operator*());
                }

                self_reference operator=(PSLL_Iter<DataT>const& src) {
                    if(this == &src){
                        return *this;
                    }
                    here = src.here;
                    return *this;
                }

                self_reference operator++() {
                    if (!here) {
                        throw std::runtime_error("Can't use ++(pre) operator at null position");
                    }
                    here = here->next;
                    return *this;
                }

                self_type operator++(int) {
                    if (!here) {
                        throw std::runtime_error("Can't use ++(post) operator with a null node");
                    }
                    PSLL_Iter<DataT> hold(*this);
                    here = here->next;
                    return hold;
                }

                bool operator==(PSLL_Iter<DataT>const& test) const {
                    return here == test.here;
                }

                bool operator!=(PSLL_Iter<DataT>const& test) const {
                    return here != test.here;
                }
            };

        //typedef std::size_t size_t;
        typedef T value_type;
        typedef PSLL_Iter<T> iterator;
        typedef PSLL_Iter<T const> const_iterator;

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

        iterator grab(PSLL_Iter<T>& src){
            return iterator(src);
        }

        PSLL(){

            cout << "Created a Pooled Singly Linked-List!!!" << endl;

            cout << "Created Empty Pool!" << endl;

        }

        ~PSLL(){

            cout << "Destroying Pooled Singly Linked-List!!!" << endl;

            NodePtr temp = this->head;

            while(temp!= nullptr){
                NodePtr deleteThis = temp;
                temp = temp->next;
                delete  deleteThis;
            }

            temp = this->free;

            while(temp!= nullptr){
                NodePtr deleteThis = temp;
                temp = temp->next;
                delete  deleteThis;
            }

            cout << "Destroyed Pool!" << endl;

            this->head = this->tail = this->free = nullptr;

        }

        PSLL(const PSLL& src) {
            Node* temp = src.head;

            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }

            cout << "Created Pooled Singly Linked-List (Copy CTR)!!!" << endl;
            cout << "Created Empty Pool!!!" << endl;

        }

        PSLL(PSLL&& src) {

            this->head = src.head;
            this->tail = src.tail;
            this->free = src.free;

            src.head = src.tail = src.free = nullptr;


            cout << "Created Pooled Singly Linked-List (Move CTR)!!!" << endl;
            cout << "Created Empty Pool!!!" << endl;

        }

        PSLL& operator=(const PSLL& src) {
            if (&src == this)
                return *this;

            clear();

            NodePtr temp = src.head;

            while (temp) {
                push_back(temp->data);
                temp = temp->next;
            }

            return *this;

        }

        PSLL& operator=(PSLL&& src) {
            if (&src == this)
                return *this;

            clear();

            this->head = src.head;
            this->tail = src.tail;
            this->free = src.free;

            src.head = src.tail = src.free = nullptr;

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

        T const& operator[](size_t position) const {
            if (position < 0 || position >= length()) {
                throw std::out_of_range("Array index out of bounds!");
            }
            Node* temp = head;
            
            for (size_t j = 0; j < position; j++) {
                temp = temp->next;
            }
            return temp->data;
        }

        size_t length()const{
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

        bool is_empty()const{
            return (this->head == nullptr);
        }

        bool is_full()const{
            NodePtr test = new(std::nothrow) Node;
            if(!test && grab_pool_length() == 0)
                return true;

            delete test;
            return false;
        }

        void clear(){

            NodePtr temp = this->head;

            while(temp!= nullptr){
                NodePtr thisOne = temp;
                temp = temp->next;
                delete thisOne;
            }

            this->head = this->tail = nullptr;

            return;
        }

        std::ostream& print(std::ostream& stream)const{
            if(is_empty()){
                stream << "<empty list>";
                return stream;
            }

            NodePtr temp = this->head;

            stream << "[";

            while(temp->next != nullptr){
                stream << temp->data << ",";
                temp = temp->next;
            }

            stream << temp->data;

            stream << "]";

            return stream;
        }

        T& peek_back()const{
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't peek at back of PSLL because PSLL is empty!!!");
            }
            return this->tail->data;
        }

        T& peek_front()const{
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't peek at front of PSLL because PSLL is empty!!!");
            }
            return this->head->data;
        }

        T pop_back(){
            if(is_empty()){
                throw std::runtime_error("ERROR: Can't pop at back of PSLL because PSLL is empty!!!");
            }

            if(length() == 1){
                T result = this->tail->data;
                NodePtr send_back = this->tail;
                send_to_pool(send_back);
                this->head = nullptr;
                this->tail = nullptr;
                return result;
            }

            NodePtr temp = this->head;

            while(temp->next->next != nullptr){
                temp = temp->next;
            }

            T result = temp->next->data;
            NodePtr send_back = temp->next;
            temp->next = nullptr;
            this->tail = temp;
            send_to_pool(send_back);
            return result;
        }

        T pop_front(){

            if(is_empty()){
                throw std::runtime_error("ERROR: Can't pop at front of PSLL because PSLL is empty!!!");
            }
            if(length() == 1){
                this->tail = nullptr;
            }
            T result = this->head->data;
            NodePtr newHead = this->head->next;
            this->head->next = nullptr;
            send_to_pool(this->head);
            this->head = newHead;
            return result;
        }

        void push_front(const T& item){
            if(is_full()){
                throw std::runtime_error("ERROR: Can't push at front of PSLL because PSLL is full!!!");
            }
            NodePtr newNode = grab_from_pool();
            newNode->data = item;
            newNode->next = this->head;
            this->head = newNode;
            if(this->tail == nullptr){
                this->tail = newNode;
            }
            return;

        }

        void push_back(const T& item){
            if(is_full()){
                throw std::runtime_error("ERROR: Can't push at back of PSLL because PSLL is full!!!");
            }
            NodePtr newNode = grab_from_pool();
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

        T& item_at(size_t position)const{
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid Input for position in T PSLL::item_at(size_t position)!");
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

        T* contents()const{

            T* arr = new T[length()];
            NodePtr temp = this->head;
            size_t len = length();
            for(size_t i = 0; i < len; i++){
                arr[i] = temp->data;
                temp = temp->next;
            }

            return arr;
        }

        T remove(size_t position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid input for position in T PSLL:remove(size_t position)!");
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
            send_to_pool(removeThis);
            return result;
        }

        bool contains(const T& element, bool (*equals)(const T&,const T&))const{
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

        void insert(const T& element, size_t position){
            if(position < 0 || position >= (length()+1)){
                throw std::runtime_error("ERROR: Invalid input for position in void PSLL:insert(T element,size_t position)!");

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
            NodePtr temp = head;
            while(--cnt > 0){
                temp = temp->next;
            }
            NodePtr newNode = grab_from_pool();
            newNode->data = element;
            NodePtr oldNext = temp->next;
            temp->next = newNode;
            newNode->next = oldNext;
            return;
        }

        T replace(const T& element, size_t position){
            if(position < 0 || position >= length()){
                throw std::runtime_error("ERROR: Invalid Input for position in T PSLL:replace(T element,size_t position)!");
            }
            int cnt = static_cast<int>(position);
            NodePtr temp = head;

            while(--cnt >= 0){
                temp = temp->next;
            }

            T result = temp->data;
            temp->data = element;
            return result;
        }

        unsigned int grab_pool_length() const{

            if(this->free == nullptr)
                return 0;

            NodePtr temp = this->free;

            unsigned int result = 0;

            while(temp != nullptr){
                result++;
                temp = temp->next;
            }

            return result;
        }

        static bool equals(const T& element, const T& compareValue){
            return (element == compareValue);
        }

    };
}

#endif //COP3530_PROJECT_1_PSLL_H
