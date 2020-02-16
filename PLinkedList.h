/*
 * PLinkedList.h
 *
 *  Created on: 15 Feb 2020
 *      Author: Patrick Wagner
 */

#ifndef PLINKEDLIST_H_
#define PLINKEDLIST_H_

#include <cstddef>
#include <stdio.h>
#include <new>

/* define template for the node */
template<class transferredClass>
class PNode {
public:

	transferredClass item;
	PNode<transferredClass> *next;
	PNode<transferredClass> *previous;

};

/* define template for the list */
template<class transferredClass>
class PLinkedList {
private:

	PNode<transferredClass> *begin = nullptr;
	PNode<transferredClass> *end = nullptr;
	unsigned long item_amount = 0;

public:

	bool append(transferredClass &itemT);
	bool clear();
	bool contains(transferredClass &itemT);
	bool empty();
	transferredClass& find(transferredClass &itemT);
	transferredClass& First();
	transferredClass& Last();
	bool prepend(transferredClass &itemT);
	bool remove(transferredClass &itemT);
	bool removeFirst();
	bool removeLast();
	unsigned long size();
	transferredClass& takeFirst();
	transferredClass& takeLast();
	void printList();
};

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::append(transferredClass &itemT)
 * Appends the transferred item to the end of the list. Will return true if successfull or false if not.
 * @param itemT the transferred item.
 * @return true on success, false on failure
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::append(transferredClass &itemT) {

	try {
		PNode<transferredClass> *node = new PNode<transferredClass>;

		node->item = itemT;

		if (begin == nullptr) {
			begin = node;
			end = node;
			node->previous = nullptr;
			node->next = nullptr;

		} else {

			end->next = node;
			node->previous = end;
			node->next = nullptr;
			end = node;

		}

		item_amount += 1;

		return true;

	} catch (std::bad_alloc &exc) {
		return false;
	}

}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::clear() {

	if (begin == nullptr) {

		return false;

	} else {

		PNode<transferredClass> *pHelp = begin;
		while (pHelp != nullptr) {

			pHelp = pHelp->next;
			delete &begin;
			begin = pHelp;

			item_amount -= 1;

		}

		return true;
	}
}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::contains(transferredClass &itemT) {

	if (begin == nullptr) {

		return false;

	} else {

		bool retval = false;
		PNode<transferredClass> *pHelp = begin;

		while (pHelp != nullptr) {

			if (pHelp->item == itemT) {
				retval = true;
				break;
			}

			pHelp = pHelp->next;

		}

		return retval;

	}
}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::empty() {

	bool retval;

	if (item_amount == 0) {

		retval = true;

	} else {

		retval = false;

	}

	return retval;

}

template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::find(
		transferredClass &itemT) {

	if (item_amount == 0) {

		return begin->item;

	} else {

		PNode<transferredClass> *pHelp = begin;
		while (pHelp != nullptr) {

			if (pHelp->item == itemT) {

				return pHelp->item;

			}

			pHelp = pHelp->next;

		}

		return begin->item;

	}

}

template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::First() {

	if (item_amount == 0) {
		return nullptr;
	} else {
		return begin;
	}

}

template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::Last() {

	if (item_amount == 0) {
		return nullptr;
	} else {
		return end;
	}
}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::prepend(transferredClass &itemT) {

	try {

		PNode<transferredClass> *node = new PNode<transferredClass>;
		node->item = itemT;

		if (begin == nullptr) {
			begin = node;
			end = node;
			node->next = nullptr;
			node->previous = nullptr;
		} else {
			node->next = begin;
			node->previous = nullptr;
			begin->previous = node;
			begin = node;
		}

		item_amount += 1;

		return true;

	} catch (std::bad_alloc &exc) {
		return false;
	}

}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::remove(transferredClass &itemT) {

	if (item_amount == 0) {
		return false;
	} else {

		PNode<transferredClass> *pHelp = begin;
		while (pHelp != nullptr) {

			if (pHelp->item == itemT) {

				/* could be begin, end, neither, both */

				if (begin->item == itemT && end->item != itemT) {

					pHelp = pHelp->next;
					pHelp->previous = nullptr;
					delete &begin;
					begin = pHelp;

				} else if (end->item == itemT && begin->item != itemT) {

					pHelp = pHelp->previous;
					pHelp->next = nullptr;
					delete &end;
					end = pHelp;

				} else if (begin->item != itemT && end->item != itemT) {

					pHelp->previous->next = pHelp->next;
					pHelp->next->previous = pHelp->previous;
					delete pHelp;

				} else if (begin->item == itemT && end->item == itemT) {

					delete &begin;
					delete &end;
				}

				item_amount -= 1;

				return true;

			}

			pHelp = pHelp->next;

		}

		return false;

	}

}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::removeFirst() {

	if (item_amount == 0) {
		return false;
	} else {

		PNode<transferredClass> *pHelp = begin;

		pHelp = pHelp->next;
		pHelp->previous = nullptr;
		delete &begin;
		begin = pHelp;

		item_amount -= 1;

		return true;

	}

}

template<class transferredClass>
inline bool PLinkedList<transferredClass>::removeLast() {

	if (item_amount == 0) {
		return false;
	} else {

		PNode<transferredClass> *pHelp = end;

		pHelp = pHelp->previous;
		pHelp->next = nullptr;
		delete &end;
		end = pHelp;

		item_amount -= 1;

		return true;

	}
}

template<class transferredClass>
inline unsigned long PLinkedList<transferredClass>::size() {

	return item_amount;
}

template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::takeFirst() {

	if (begin != nullptr) {
		transferredClass *pHelp;

		pHelp = &begin->item;

		begin = begin->next;
		begin->previous = nullptr;

		item_amount -= 1;

		return *pHelp;

	} else {
		return begin->item;
	}
}

template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::takeLast() {

	if (end != nullptr) {
		transferredClass *pHelp;
		pHelp = &end->item;

		end = end->previous;
		end->next = nullptr;

		item_amount -= 1;

		return *pHelp;

	} else {
		return end->item;
	}

}

template<class transferredClass>
inline void PLinkedList<transferredClass>::printList() {

	PNode<transferredClass> *pHelp;
	pHelp = begin;
	while (pHelp != nullptr) {
		printf("%p\n", pHelp->item);
		pHelp = pHelp->next;
	}
}

#endif /* PLINKEDLIST_H_ */