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

	transferredClass *item;
	PNode<transferredClass> *next;
	PNode<transferredClass> *previous;

};

/* define template for the list */
template<class transferredClass>
class PLinkedList {
private:

	PNode<transferredClass> *begin = new PNode<transferredClass>;
	PNode<transferredClass> *end = new PNode<transferredClass>;
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

		node->item = &itemT;

		if (item_amount == 0) {

			begin->previous = nullptr;
			begin->next = node;

			node->previous = begin;
			node->next = end;

			end->next = nullptr;
			end->previous = node;

		} else {

			node->previous = end->previous;
			node->next = end;
			node->previous->next = node;
			end->previous = node;

		}

		item_amount += 1;

		return true;

	} catch (std::bad_alloc &exc) {
		return false;
	}

}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::clear()
 * clears all items from the list and frees the allocated memory.
 * @return true if successfull, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::clear() {

	if (item_amount == 0) {

		return false;

	} else {

		PNode<transferredClass> *pHelp = begin->next;
		while (pHelp != end) {

			begin->next = pHelp->next;
			pHelp->next->previous = begin;

			PNode<transferredClass> *pEraser = pHelp;
			delete pEraser;

			pHelp = pHelp->next;

			item_amount -= 1;

		}

		return true;
	}
}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::contains(transferredClass &itemT)
 * checks the list for the transferred item and returns true if it is in the list
 * and false if not.
 * @param itemT the item to look for.
 * @return true if it is in the list, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::contains(transferredClass &itemT) {

	if (item_amount == 0) {

		return false;

	} else {

		bool retval = false;
		PNode<transferredClass> *pHelp = begin->next;

		while (pHelp != nullptr) {

			if (pHelp->item == &itemT) {
				retval = true;
				break;
			}

			pHelp = pHelp->next;

		}

		return retval;

	}
}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::empty()
 * checks if the list is empty or not.
 * @return true if the list is empty, false if not.
 */
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

/**
 * template<class transferredClass> inline transferredClass& PLinkedList<transferredClass>::find(transferredClass &itemT)
 * checks if the transferred item is in the list and returns a pointer if it is.
 * @param itemT the item to search.
 * @return pointer to the item if it is in the list, nullptr if not.
 */
template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::find(
		transferredClass &itemT) {

	if (item_amount == 0) {

		return *begin->item;

	} else {

		PNode<transferredClass> *pHelp = begin->next;
		while (pHelp != end) {

			if (pHelp->item == &itemT) {

				return *pHelp->item;

			}

			pHelp = pHelp->next;

		}

		return *begin->item;

	}

}

/**
 * template<class transferredClass> inline transferredClass& PLinkedList<transferredClass>::First()
 * If the list is not empty will return a pointer to the item at the begin of the list.
 * @return pointer to the first item, nullptr if the list is empty.
 */
template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::First() {

	if (item_amount == 0) {
		return nullptr;
	} else {
		return begin->next;
	}

}

/**
 * template<class transferredClass> inline transferredClass& PLinkedList<transferredClass>::Last()
 * If the list is not empty will return a pointer to the item at the end of the list.
 * @return pointer to the last item, nullptr if the list is empty.
 */
template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::Last() {

	if (item_amount == 0) {
		return nullptr;
	} else {
		return end->previous;
	}
}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::prepend(transferredClass &itemT)
 * Prepends the transferred item to the beginning of the list.
 * @param itemT the item to prepend.
 * @return true if successfull, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::prepend(transferredClass &itemT) {

	try {

		PNode<transferredClass> *node = new PNode<transferredClass>;
		node->item = itemT;

		if (item_amount == 0) {

			begin->next = node;
			node->previous = begin;
			node->next = end;
			end->previous = node;

		} else {

			begin->next->previous = node;
			node->previous = begin;
			node->next = begin->next;
			begin->next = node;

		}

		item_amount += 1;

		return true;

	} catch (std::bad_alloc &exc) {
		return false;
	}

}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::remove(transferredClass &itemT)
 * Searches for the transferred item, removes it from the list and destroys it.
 * @param itemT the item to be removed.
 * @return true if successfull, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::remove(transferredClass &itemT) {

	if (item_amount == 0) {
		return false;
	} else {

		PNode<transferredClass> *pHelp = begin->next;
		while (pHelp != end) {

			if (pHelp->item == &itemT) {


				/* is the first item but not the only*/
				if (begin->next->item == &itemT && end->previous->item != &itemT) {

					pHelp->next->previous = begin;
					begin->next = pHelp->next;
					delete pHelp;

				/* is the last item but not the only*/
				} else if (end->previous->item == &itemT && begin->next->item != &itemT) {

					pHelp->previous->next = end;
					end->previous = pHelp->previous;
					delete pHelp;

				/* is neither first nor last */
				} else if (begin->next->item != &itemT && end->previous->item != &itemT) {

					pHelp->next->previous = pHelp->previous;
					pHelp->previous->next = pHelp->next;
					delete pHelp;

				/* is the only item */
				} else if (begin->next->item == &itemT && end->previous->item == &itemT) {

					begin->next = end;
					end->previous = begin;
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
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::removeFirst()
 * Removes the item at the beginning of the list and destroys it.
 * @return true if successfull, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::removeFirst() {

	if (item_amount == 0) {
		return false;
	} else {

		PNode<transferredClass> *pHelp = begin->next;

		begin->next = begin->next->next;
		begin->next->previous = begin;
		delete pHelp;

		item_amount -= 1;

		return true;

	}

}

/**
 * template<class transferredClass> inline bool PLinkedList<transferredClass>::removeLast()
 * Removes the item at the end of the list and destroys it.
 * @return true if successfull, false if not.
 */
template<class transferredClass>
inline bool PLinkedList<transferredClass>::removeLast() {

	if (item_amount == 0) {

		return false;

	} else {

		PNode<transferredClass> *pHelp = end->previous;
		pHelp->previous->next = end;
		end->previous = end->previous->previous;
		delete pHelp;

		item_amount -= 1;

		return true;

	}
}

/**
 * template<class transferredClass> inline unsigned long PLinkedList<transferredClass>::size()
 * Returns the size of the list.
 * @return the size of the list.
 */
template<class transferredClass>
inline unsigned long PLinkedList<transferredClass>::size() {

	return item_amount;
}

/**
 * template<class transferredClass> inline transferredClass& PLinkedList<transferredClass>::takeFirst()
 * Removes the item at the beginning of the list and returns a pointer to it.
 * @return A pointer to the first item if successfull, nullptr if not
 */
template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::takeFirst() {

	if (item_amount > 0) {
		transferredClass *pHelp = begin->next->item;

		begin->next = begin->next->next;
		begin->next->previous = begin;

		item_amount -= 1;

		return *pHelp;

	} else {
		return *begin->item;
	}
}

/**
 * template<class transferredClass> inline transferredClass& PLinkedList<transferredClass>::takeLast()
 * Removes the item at the end of the list and returns a pointer to it.
 * @return A pointer to the last item if successfull, nullptr if not
 */
template<class transferredClass>
inline transferredClass& PLinkedList<transferredClass>::takeLast() {

	if (item_amount > 0) {
		transferredClass *pHelp = end->item;

		end->previous = end->previous->previous;
		end->previous->next = end;

		item_amount -= 1;

		return *pHelp;

	} else {
		return end->item;
	}

}

/**
 * template<class transferredClass> inline void PLinkedList<transferredClass>::printList()
 * prints the pointer addresses of the items in the list.
 */
template<class transferredClass>
inline void PLinkedList<transferredClass>::printList() {

	PNode<transferredClass> *pHelp;
	pHelp = begin->next;
	while (pHelp != end) {
		printf("%p\n", pHelp->item);
		pHelp = pHelp->next;
	}
}

#endif /* PLINKEDLIST_H_ */
