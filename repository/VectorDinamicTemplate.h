#pragma once
#include "../domain/Discipline.h"
#define INITIAL_CAPACITY 5
#include "Repo.h"
template<typename Element>
class IteratorVector;

template<typename Element>
class vectorDinamic {
private:
    int lg;
    int cp;
    Element* vect;

    void redimensionare();
public:
    vectorDinamic(); //constructor

    vectorDinamic(const vectorDinamic& ot);//rules of 3.constructor copiere

    vectorDinamic& operator=(const vectorDinamic& ot);//operator de assignment

    ~vectorDinamic(); //destructor




    __attribute__((unused)) void push_back(const Element& el); //append

    void erase(int poz) noexcept; //delete

    int size() const noexcept; //size

    Element& at(int poz) const noexcept; //replace a element

    __attribute__((unused)) void set(const Element&, int poz) noexcept;

    void exchange(int, int);




    friend class IteratorVector<Element>;

    IteratorVector<Element> begin() noexcept;

    IteratorVector<Element> end() noexcept;
};

template <typename Element>
void vectorDinamic<Element>::redimensionare() {
    cp = cp * 2;
    Element* aux = new Element[2 * cp];
    for (int i = 0; i < lg; i++)
        aux[i] = vect[i];
    delete[] vect;
    vect = aux;
}

template <typename Element> //constructor
vectorDinamic<Element> ::vectorDinamic() :cp{ INITIAL_CAPACITY }, lg{ 0 }, vect{ new Element[INITIAL_CAPACITY] } {}

template <typename Element>//cosntructor de copiere
vectorDinamic<Element>::vectorDinamic(const vectorDinamic& ot){
    vect = new Element[ot.cp];
    for (int i = 0; i < ot.lg; i++)
        vect[i] = ot.vect[i];
    lg = ot.lg;
    cp = ot.cp;
}

template<typename Element>//operatorul de assignment
vectorDinamic<Element>& vectorDinamic<Element>:: operator=(const vectorDinamic<Element>& ot) {
    if (this == &ot)
        return *this;
    delete[] vect;
    vect = new Element[ot.cp];
    for (int i = 0; i < ot.lg; i++)
        vect[i] = ot.vect[i];
    cp = ot.cp;
    lg = ot.lg;
    return *this;
}

template<typename Element> //destructor
vectorDinamic<Element>:: ~vectorDinamic() {
    const auto* p = &vect;
    if(p != nullptr)
        delete[] vect;
}

template<typename Element> //append
__attribute__((unused)) void vectorDinamic<Element>::push_back(const Element& el)
{
    if (lg == cp)
        redimensionare();
    vect[lg++] = el;
}

template<typename Element> //delete
void vectorDinamic<Element>::erase(int poz) noexcept
{
    for (int i = poz; i < lg; i++)
        vect[i] = vect[i + 1];
    lg = lg - 1;

}

template<typename Element> //size
int vectorDinamic<Element>::size() const noexcept {
    return lg;
}

template<typename Element> //element from a position
Element& vectorDinamic<Element>::at(int poz) const noexcept {
    return vect[poz];
}

template<typename Element> //setter
__attribute__((unused)) void vectorDinamic<Element>::set(const Element& el, int poz) noexcept {
    vect[poz] = el;
}

template<typename Element>
void vectorDinamic<Element>::exchange(int poz1, int poz2)
{
    Element aux = vect[poz1];
    vect[poz1] = vect[poz2];
    vect[poz2] = aux;
}



template<typename Element> //1st position
IteratorVector<Element> vectorDinamic<Element>::begin() noexcept {
    return IteratorVector<Element>(*this);
}

template<typename Element> //last position
IteratorVector<Element> vectorDinamic<Element>::end() noexcept {
    return IteratorVector<Element>(*this, lg);
}



//ITERATOR
template<typename Element>
class IteratorVector {
private:
    int curent;
    const vectorDinamic<Element>& v;
public:
    IteratorVector(const vectorDinamic<Element>& v) noexcept; //constructor

    IteratorVector(const vectorDinamic<Element>& v, int lg) noexcept;

    __attribute__((unused)) bool valid() noexcept; //validate

    Element& element() const noexcept;//return elem curent

    void next() noexcept;//itereaza urm elem

    Element& operator*() noexcept;// * - elem curent

    IteratorVector<Element>& operator++() noexcept; // ++ - return iterator de la poz + 1

    bool operator==(const IteratorVector<Element>& ot)noexcept; //verif daca curent == ot.curent

    bool operator!=(const IteratorVector<Element>& ot)noexcept; //verif daca curent != ot.curent
};

template<typename Element> //constructor
IteratorVector<Element>::IteratorVector(const vectorDinamic<Element>& v) noexcept :v{ v }, curent{ 0 }{}

template<typename Element>
IteratorVector<Element>::IteratorVector(const vectorDinamic<Element>& v, int lg) noexcept : v{ v }, curent{ lg } {}

template<typename Element>//validator
__attribute__((unused)) bool IteratorVector<Element>::valid() noexcept {
    return curent < v.lg;
}

template<typename Element>//return elem curesnt
Element& IteratorVector<Element>::element() const noexcept {
    return v.vect[curent];
}

template<typename Element>//itereaza urm element
void IteratorVector<Element>::next() noexcept {
    curent++;
}

template<typename Element>//elem curent
Element& IteratorVector<Element>:: operator*() noexcept {
    return element();
}

template<typename Element>//return iterator vect poz ++
IteratorVector<Element>& IteratorVector<Element>:: operator++() noexcept {
    next();
    return *this;
}

template<typename Element>//iteratori egali
bool IteratorVector<Element>:: operator==(const IteratorVector<Element>& ot)noexcept {
    return curent = ot.curent;
}

template<typename Element>
bool IteratorVector<Element>:: operator!=(const IteratorVector<Element>& ot)noexcept {
    return *this != ot;
}