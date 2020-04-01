/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(const T& a, L1Item<T>* p): data(a), pNext(p) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
        L1Item<T> *p = _pHead;
        while (p){
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
        L1Item<T> *p = _pHead;
        while (p){
            op(p->data, pParam);
            p = p->pNext;
        }
    }
	L1Item<T> *get_pHead() {
		if (!isEmpty())return _pHead;
	}
};
/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
    if (isEmpty()) return -1;
    L1Item<T> *pPre = _pHead, *pCur = pPre->pNext;
    int i = _size - 1;
    while (i > 1 && pCur){
            pPre = pCur;
            pCur = pCur->pNext;
            i--;
    }
    pPre->pNext = new L1Item<T>(a, pCur);
    _size++;
    return 0;
}
/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    //if (isEmpty()) return -1;
    // TODO: Your code goes here
    _pHead = new L1Item<T>(a,_pHead);
    _size++;
    return 0;
}
/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
    if (isEmpty()) return -1;
    L1Item<T> *p = _pHead;
    _pHead = p->pNext;
    delete p;
    _size--;
    return 0;    
}
/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
    if (isEmpty()) return -1;
    L1Item<T> *pPre = _pHead, *pCur = pPre->pNext;
    int i=_size-1;
    while (i > 1 && pCur){
            pPre = pCur;
            pCur = pCur->pNext;
            i--;
    }
    if (pCur){
        pPre->pNext = pCur->pNext;
        delete pCur;
        _size--;
        return 0;
    }
}
//////////////////////////
template <class T>
void  L1List<T>::clean(){
    while (_pHead) {
		L1Item<T> p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
	}
}
//////////////////////////
template <class T>
T& L1List<T>:: at(int i){
  // if (i<0 || i>_size) return pN ;
   L1Item<T> *p=_pHead;
   while (i){
       p=p->pNext;
       i--;
   }
   return p->data;
} // give the reference to the element i-th in the list

template <class T>
T& L1List<T>::operator[](int i){
    //if (i<0 || i>=_size) return nullptr;
    L1Item<T> *p = _pHead;
    while (i){
       p=p->pNext;
       i--;
    }
    return p->data;
} //give the reference to the element i-th in the list
template <class T>
bool  L1List<T>::find(T& a, int& idx) {
    L1Item<T> *p = _pHead;
    idx = 0;
    while (p){
       p = p->pNext;
       if (p->data == a) return true;
       idx++;
    }
}   // find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. 
    //Return true if success.
template <class T>
int  L1List<T>::insert(int i, T& a){
    if (i<0 || i>_size) return -1;
	if (i) {
        L1Item<T> *pPre = _pHead, *pCur = pPre->pNext;
        while (i > 1 && pCur){
            pPre = pCur;
            pCur = pCur->pNext;
            i--;
        }
        pPre->pNext = new L1Item<T>(a, pCur);
    }
    else _pHead = new L1Item<T>(a,_pHead);
    _size++;
    return 0;
}   // insert an element into the list at location i. Return 0 if success, -1 otherwise
template <class T>
int  L1List<T>::remove(int i){
    if (i<0 || i>_size || isEmpty()) return -1;
    if (i){
        L1Item<T> *pPre = _pHead, *pCur = pPre->pNext;
        while (i > 1 && pCur){
            pPre = pCur;
            pCur = pCur->pNext;
            i--;
        }
        if (pCur){
            pPre->pNext = pCur->pNext;
            delete pCur;
            _size--;
            return 0;
        }
        return -1;
    }
    else {
        L1Item<T> *p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
		return 0;
    }
}   // remove an element at position i in the list. Return 0 if success, -1 otherwise.
template <class T>
void L1List<T>::reverse(){
	L1Item<T> *pPre = _pHead, *pCur = pPre->pNext, *p = new L1Item<T>;
	pPre->pNext = NULL;
        while (pCur){
            p = pCur->pNext;
            pCur->pNext = pPre;
            pPre = pCur;
            pCur = p;
        }
		_pHead = pPre;
}
#endif //DSA191_A1_DSALIB_H