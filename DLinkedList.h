/*
 * DLinkedList.h
 *
 *  Created on: 04 Jun 2021
 *      Author: Patrick Wagner
 */

#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_

#include <iostream>

using namespace std;

/* define template for the node */
template<class T>
class DNode {

public:

    T *item;
    DNode<T> *next = nullptr;
    DNode<T> *previous = nullptr;

};


/* define template for the list */
template<class T>
class DLinkedList {

private:

    DNode<T> *_begin = new DNode<T>;
    DNode<T> *_end = new DNode<T>;
    unsigned long item_amount = 0;

public:

    DLinkedList(){

        _begin->previous = nullptr;
        _begin->next = _end;
        _begin->item = nullptr;

        _end->previous = _begin;
        _end->next = nullptr;
        _end->item = nullptr;
    }

    ~DLinkedList(){
        delete _begin;
        delete _end;
    }

    DNode<T> *begin();
    DNode<T> *end();
    bool append(const T &value);
    bool clear();
    bool contains(const T &value);
    bool empty();
    T& find(const T &value);
    T& first();
    T& last();
    bool prepend(const T &value);
    bool remove(const T &value);
    bool removeFirst();
    bool removeLast();
    unsigned long size();
    T takeFirst();
    T takeLast();
    void print();
    void shuffle();
    void swap(DNode<T> rValue, DNode<T> lValue);
};


/**
 * Returns the _begin pointer.
 */
template<class T>
inline DNode<T> *DLinkedList<T>::begin()
{
    return _begin;
}

/**
 * Returns the _end pointer.
 */
template<class T>
inline DNode<T> *DLinkedList<T>::end()
{
    return _end;
}

/**
 * Appends the transferred reference to the end of the list.
 * Will return true if successfull or false if not.
 * @param value the transferred item.
 * @return true on success, false on failure
 */
template<class T>
inline bool DLinkedList<T>::append(const T &value) {

    DNode<T> *node = new DNode<T>;
    node->item = new T;
    *node->item = value;

    if (item_amount == 0) {

        _begin->next = node;

        node->previous = _begin;
        node->next = _end;

        _end->previous = node;

    } else {

        node->previous = _end->previous;
        _end->previous->next = node;
        node->next = _end;
        _end->previous = node;

    }

    item_amount += 1;

    return true;
}

/**
 * clears all items from the list, does not destroy the items.
 * @return true if successfull, false if not.
 */
template<class T>
inline bool DLinkedList<T>::clear() {

    if (item_amount == 0) {

        cerr << "list is already empty!.\n";
        return false;

    } else {

        DNode<T> *pHelp = begin()->next;
        while ( pHelp != end() ) {

            pHelp->next->previous = _begin;
            _begin->next = pHelp->next;
            delete pHelp;
            pHelp = begin()->next;

            --item_amount;
        }

        return true;
    }
}

/**
 * checks the list for value and returns true if it is in the list
 * and false if not.
 * @param value the item to look for.
 * @return true if it is in the list, false if not.
 */
template<class T>
inline bool DLinkedList<T>::contains(const T &value) {

    if (item_amount == 0) {

        return false;

    } else {

        bool retval = false;
        DNode<T> *pHelp = begin()->next;

        while ( pHelp != end() ) {

            if (*pHelp->item == value) {
                retval = true;
                break;
            }

            pHelp = pHelp->next;

        }

        return retval;

    }
}

/**
 * checks if the list is empty or not.
 * @return true if the list is empty, false if not.
 */
template<class T>
inline bool DLinkedList<T>::empty() {

    bool retval;

    if (item_amount == 0)
        retval = true;

    else
        retval = false;

    return retval;
}

/**
 * checks if value is in the list and returns a pointer to that item if it is.
 * @param value the item to search.
 * @return pointer to the item if it is in the list.
 * throws and exception if the list is empty or if the item is not in the list.
 */
template<class T>
inline T &DLinkedList<T>::find(const T &value) {

    if (item_amount == 0) {

        throw runtime_error("list is empty!\n");

    } else {

        DNode<T> *pHelp = _begin->next;
        while (pHelp != _end) {

            if (*pHelp->item == value)
                return *pHelp->item;

            pHelp = pHelp->next;

        }

        throw runtime_error("item not in list!\n");
    }
}

/**
 * If the list is not empty will return a pointer to the item at the begin of the list.
 * @return pointer to the first item.
 * throws and exception if the list is empty. .
 */
template<class T>
inline T &DLinkedList<T>::first() {

    if (item_amount == 0){
        throw runtime_error("list is empty!\n");
    }
    else
        return *_begin->next->item;
}

/**
 * If the list is not empty will return a pointer to the item at the end of the list.
 * @return pointer to the last item.
 * throws and exception if the list is empty.
 */
template<class T>
inline T &DLinkedList<T>::last() {

    if (item_amount == 0){
        throw runtime_error("list is empty!\n");
    }
    else
        return *_end->previous->item;
}

/**
 * Prepends the transferred item to the beginning of the list.
 * @param itemT the item to prepend.
 * @return true if successfull, false if not.
 */
template<class T>
inline bool DLinkedList<T>::prepend(const T &value) {

    DNode<T> *node = new DNode<T>;
    node->item = new T;
    *node->item = value;

    if (item_amount == 0) {

        _begin->next = node;
        node->previous = _begin;
        node->next = _end;
        _end->previous = node;

    } else {

        DNode<T> *pHelp = _begin->next;

        _begin->next = node;
        pHelp->previous = node;
        node->previous = _begin;
        node->next = pHelp;
    }

    item_amount += 1;

    return true;
}

/**
 * Searches for the transferred item, removes it from the list,
 * but does not destroy it.
 * @param value the item to be removed.
 * @return true if successfull, false if not.
 */
template<class T>
inline bool DLinkedList<T>::remove(const T &value) {

    if (item_amount == 0) {
        return false;
    } else {

        DNode<T> *pHelp = _begin->next;
        while (pHelp != _end) {

            if (*pHelp->item == value) {

                /* is the first item but not the only*/
                if (*_begin->next->item == value
                        && *_end->previous->item != value) {

                    pHelp->next->previous = _begin;
                    _begin->next = pHelp->next;
                    delete pHelp;

                    /* is the last item but not the only*/
                } else if (*_end->previous->item == value
                           && *_begin->next->item != value) {

                    pHelp->previous->next = _end;
                    _end->previous = pHelp->previous;
                    delete pHelp;

                    /* is neither first nor last */
                } else if (*_begin->next->item != value
                           && *_end->previous->item != value) {

                    pHelp->next->previous = pHelp->previous;
                    pHelp->previous->next = pHelp->next;
                    delete pHelp;

                    /* is the only item */
                } else if (*_begin->next->item == value
                           && *_end->previous->item == value) {

                    _begin->next = _end;
                    _end->previous = _begin;
                    delete pHelp;

                }

                item_amount -= 1;

                return true;

            }

            pHelp = pHelp->next;

        }

        return false;

    }

}

/**
 * Removes the item at the beginning of the list but does not destroy it.
 * @return true if successfull, false if not.
 */
template<class T>
inline bool DLinkedList<T>::removeFirst() {

    if (item_amount == 0) {
        return false;
    } else {

        DNode<T> *pHelp = _begin->next;

        _begin->next = _begin->next->next;
        _begin->next->previous = _begin;
        delete pHelp;

        item_amount -= 1;

        return true;

    }

}

/**
 * Removes the item at the end of the list but does not destroy it.
 * @return true if successfull, false if not.
 */
template<class T>
inline bool DLinkedList<T>::removeLast() {

    if (item_amount == 0) {

        return false;

    } else {

        DNode<T> *pHelp = _end->previous;
        pHelp->previous->next = _end;
        _end->previous = _end->previous->previous;
        delete pHelp;

        item_amount -= 1;

        return true;

    }
}

/**
 * Returns the size of the list.
 * @return the size of the list.
 */
template<class T>
inline unsigned long DLinkedList<T>::size() {

    return item_amount;
}

/**
 * Removes the item at the beginning of the list and returns a pointer to it.
 * @return A pointer to the first item if successfull.
 * throws and exception if the list is empty.
 */
template<class T>
inline T DLinkedList<T>::takeFirst() {

    if (item_amount > 0) {

        T *pHelp = _begin->next->item;

        _begin->next = _begin->next->next;
        _begin->next->previous = _begin;

        item_amount -= 1;

        return *pHelp;

    } else
        throw runtime_error("takeFirst: list empty!\n.");

}

/**
 * Removes the item at the end of the list and returns a pointer to it.
 * @return A pointer to the last item if successfull.
 * throws and exception if the list is empty.
 */
template<class T>
inline T DLinkedList<T>::takeLast() {

    if (item_amount > 0) {
        T *pHelp = _end->previous->item;

        _end->previous = _end->previous->previous;
        _end->previous->next = _end;

        item_amount -= 1;

        return *pHelp;

    } else
        throw runtime_error("takeLast: list empty!\n.");


}

/**
 * prints the items in the list.
 */
template<class T>
inline void DLinkedList<T>::print() {

    if(item_amount == 0){

        cout << "list is empty!\n";
    }

    DNode<T> *pHelp;
    pHelp = _begin->next;
    while (pHelp != _end) {
        cout << *pHelp->item << "\n";
        pHelp = pHelp->next;
    }
}

#endif /* DLINKEDLIST_H_ */
