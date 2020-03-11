/*
 * main.cpp
 *
 *  Created on: 15 Feb 2020
 *      Author: Patrick Wagner
 */

#include <string>
#include <stdio.h>
#include <cstddef>
#include <chrono>
#include <unistd.h>
#include <iostream>


#include "PLinkedList.h"

class myClass {
public:
	int attribute1 = 0;
	int attribute2 = 0;

	void someMethod() {
		std::cout << "Hello cruel World!\n";
	}
};

int main() {

	/* It seems that you have to specifically set the next and previous pointers
	 * of begin and end even when you have set the pointers of the node and
	 * now point end and begin to that node.
	 * There seems to be confusing redundancy in it.
	 * Maybe that is because you are allocating new memory for a node.
	 * Which you shouldnt. I think.
	 */

	PLinkedList<myClass*> list;
	myClass *pObject1 = new myClass();
	myClass *pObject2 = new myClass();
	myClass *pObject3 = new myClass();
	myClass *pObject4 = new myClass();

	pObject1->attribute1 = 5;
	pObject1->attribute2 = 10;

//	list.append(pObject1);
//	list.append(pObject2);
//	list.append(pObject3);
	list.prepend(pObject3);
	list.prepend(pObject2);
	list.prepend(pObject1);
	list.printList();
//	list.remove(pObject3);
//	list.clear();

//	list.removeFirst();
//	list.removeFirst();
//	list.removeLast();
//	list.removeLast();
	list.printList();
	myClass *pHelp;
//
	pHelp = list.find(pObject1);
//	pHelp = list.First();
//	pHelp = list.Last();

//	pObject1->attribute1 = 20;
//	pObject1->attribute2 = 30;

//	list.remove(pObject3);
//

//
//	printf("list empty: %i\n", list.empty());
//	printf("elements: %lu \n", list.size());
//	printf("contains: %i\n", list.contains(pObject4));
	printf("item: %p\n", &pHelp);
	if(pHelp != nullptr){
		printf("object has been found!\n");
		printf("attribute1: %i\n", pHelp->attribute1);
		printf("attribute2: %i\n", pHelp->attribute2);
	}else{
		printf("object could not be found!\n");
	}

//	while (1) {
//		myClass *pObject1 = new myClass();
//		myClass *pObject2 = new myClass();
//		myClass *pObject3 = new myClass();
//		list.append(pObject1);
//		list.append(pObject2);
//		list.append(pObject3);
//		myClass *pHelp1 = pObject1;
//		myClass *pHelp2 = pObject2;
//		myClass *pHelp3 = pObject3;
//
//		list.remove(pObject1);
//		list.remove(pObject2);
//		list.remove(pObject3);

//		list.removeFirst();
//		list.removeFirst();
//		list.removeFirst();

//		list.removeLast();
//		list.removeLast();
//		list.removeLast();

//		list.clear();
//		list.printList();
//	}

	return 0;
}

