#pragma once
#include <iostream>
using namespace std;


class CRefCounter
{
public:
    CRefCounter() { i_count = 0; }
    int iAdd() { return(++i_count); }
    int iDec() { return(--i_count); }
    int iGet() { return(i_count); }
private:
    int i_count;
};


template <typename T> class CMySmartPointer
{
public:
    CMySmartPointer();
    CMySmartPointer(T* pcPointer);
    ~CMySmartPointer();
    CMySmartPointer(const CMySmartPointer& pcOther);
    T& operator *();
    T* operator->();
    CMySmartPointer<T>& operator=(const CMySmartPointer<T>& pcOther);
private:
    void v_copy(const CMySmartPointer<T>& pcOther);
    T* pc_pointer;
    CRefCounter* pc_counter;
};

template <typename T>
CMySmartPointer<T>::CMySmartPointer() {
    pc_pointer = nullptr;
    pc_counter = new CRefCounter();
}

template <typename T>
CMySmartPointer<T>::CMySmartPointer(T* pcPointer) {
    pc_pointer = pcPointer;
    pc_counter = new CRefCounter();
    pc_counter->iAdd();
}

template <typename T>
CMySmartPointer<T>::~CMySmartPointer() {
    if (pc_counter->iDec() == 0) {
        delete pc_pointer;
        delete pc_counter;
    }
}

template <typename T>
void CMySmartPointer<T>::v_copy(const CMySmartPointer<T>& pcOther) {
    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
    pc_counter->iAdd();
}

template <typename T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer& pcOther)
{
    v_copy(pcOther);
}

template <typename T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer<T>& pcOther) {
    if (pc_counter->iDec() == 0)
    {
        delete pc_pointer;
        delete pc_counter;
    }
    v_copy(pcOther);
    return *this;
}

template <typename T>
T& CMySmartPointer<T>::operator*() {
    return (*pc_pointer);
}

template <typename T>
T* CMySmartPointer<T>::operator->() {
    return (pc_pointer);
}
