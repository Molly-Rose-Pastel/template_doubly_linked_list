#include <QtTest>

#include "DLinkedList.h"

using namespace std;

class DLinkedList_UnitTest : public QObject
{
    Q_OBJECT

private slots:
    void test_append();
    void test_clear();
    void test_contains();
    void test_find();
    void test_first();
    void test_last();
    void test_prepend();
    void test_remove();
    void test_removeFirst();
    void test_removeLast();
    void test_takeFirst();
    void test_takeLast();
};

/**
 * To test if the append() function works correctly we have
 * to see if appended values are added in the correct order
 * and if the next and previous pointer actually point to
 * the correct node.
 *
 * we do this by appending values to a list in a loop and
 * then starting from begin iterate over the list while
 * checking the values.
 *
 * likewise we do the reverse, starting from the end.
 */
void DLinkedList_UnitTest::test_append() {

    DLinkedList<int> list;
    DNode<int> *iter;
    int value;

    for( int i=0; i<5; i++){

        list.append(i);
    }

    /* testing correct assignment of next pointer */
    iter = list.begin()->next;
    value = 0;
    while( iter != list.end() ){

        QCOMPARE(*iter->item, value);
        ++value;
        iter = iter->next;
    }

    /* testing correct assignment of end-pointer */
    QCOMPARE(*iter->previous->item, 4);

    /* testing correct assignment of previous pointer */
    iter = list.end()->previous;
    value = 4;
    while( iter != list.begin() ){

        QCOMPARE(*iter->item, value);
        --value;
        iter = iter->previous;
    }

    /* testing correct assignment of begin-pointer */
    QCOMPARE(*iter->next->item, 0);

}

/**
 * To test if the clear() function works correctly we need
 * to clear a list, check if the item_amount variable == 0,
 * and check if the begin->next pointer is pointing to end,
 * likewise check if the end->previous pointer is pointing to begin.
 * Finally we need to check if the values we cleared still exist
 * as we only want to remove the elements from the list but not
 * destroy the elements themselves.
 */
void DLinkedList_UnitTest::test_clear() {

    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.append(rValue0);
    rList.append(rValue1);
    rList.append(rValue2);

    pList.append(pValue0);
    pList.append(pValue1);
    pList.append(pValue2);

    /* clear the lists and check if they are empty and if the
     * original values still exist */

    rList.clear();
    pList.clear();

    /* testing item_amount */
    QCOMPARE(rList.size(), 0);
    QCOMPARE(pList.size(), 0);

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());

    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);

}

/**
 * To test if the contains() function works correctly we need
 * to add values to the list and then check if one of the added
 * values exists meaning if the function returns true.
 *
 * Likewise we need to check if the list contains a value that was not
 * added meaning if the function returns false.
 */
void DLinkedList_UnitTest::test_contains() {

    DLinkedList<int> rList;
    DLinkedList<int*> pList;
    for( int i=0; i<10; i++ ){

        rList.append(i);

    }

    int *pInt0 = new int(0);
    int *pInt1 = new int(1);
    pList.append(pInt0);

    QVERIFY(rList.contains(5));
    QCOMPARE(rList.contains(100), false);

    QVERIFY(pList.contains(pInt0));
    QCOMPARE(pList.contains(pInt1), false);

}

/**
 * To test if the find() function works correctly we need to
 * add value to the list and then check if find() returns
 * the value we adde.
 * Likewise we need to check if find() throws and exception if we try
 * to find a value that does not exist.
 */
void DLinkedList_UnitTest::test_find() {

    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    for( int i=0; i<10; i++ ){

        rList.append(i);
    }

    int *pInt0 = new int(0);
    pList.append(pInt0);

    int *pInt1 = new int(1);

    QCOMPARE(rList.find(5), 5);
    QCOMPARE(pList.find(pInt0), pInt0);

    QVERIFY_EXCEPTION_THROWN(rList.find(10), runtime_error);
    QVERIFY_EXCEPTION_THROWN(pList.find(pInt1), runtime_error);
}

/**
 * To test if the first() function works correctly we need to add
 * items to the list and then check if first() returns the first
 * item we added.
 *
 * Likewise we need to check if first() throws an exception if the
 * list is empty.
 */
void DLinkedList_UnitTest::test_first()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    QVERIFY_EXCEPTION_THROWN(rList.first(), runtime_error);
    QVERIFY_EXCEPTION_THROWN(pList.first(), runtime_error);

    for( int i=0; i<10; i++ ){

        rList.append(i);

    }

    int * pInt0 = new int(0);
    pList.append(pInt0);

    QCOMPARE(rList.first(), 0);
    QCOMPARE(*pList.first(), 0);
    QCOMPARE(pList.first(), pInt0);
}

/**
 * To test if the last() function works correctly we need to add
 * items to the list and then check if last() returns the last
 * item we added.
 *
 * Likewise we need to check if last() throws an exception if the
 * list is empty.
 */
void DLinkedList_UnitTest::test_last()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    QVERIFY_EXCEPTION_THROWN(rList.last(), runtime_error);
    QVERIFY_EXCEPTION_THROWN(pList.last(), runtime_error);

    for( int i=0; i<10; i++ ){

        rList.append(i);

    }

    int * pInt0 = new int(10);
    pList.append(pInt0);

    QCOMPARE(rList.last(), 9);
    QCOMPARE(*pList.last(), 10);
    QCOMPARE(pList.last(), pInt0);
}

/**
 * To test if the prepend() function works correctly we have
 * to see if prepended values are added in the correct order
 * and if the next and previous pointer actually point to
 * the correct node.
 *
 * we do this by prepending values to a list in a loop and
 * then starting from begin iterate over the list while
 * checking the values.
 *
 * likewise we do the reverse, starting from the end.
 */
void DLinkedList_UnitTest::test_prepend()
{
    DLinkedList<int> list;
    DNode<int> *iter;
    int value;

    for( int i=0; i<5; i++){

        list.prepend(i);
    }

    /* testing correct assignment of next pointer */
    iter = list.begin()->next;
    value = 4;
    while( iter != list.end() ){

        QCOMPARE(*iter->item, value);
        --value;
        iter = iter->next;
    }

    /* testing correct assignment of end-pointer */
    QCOMPARE(*iter->previous->item, 0);

    /* testing correct assignment of previous pointer */
    iter = list.end()->previous;
    value = 0;
    while( iter != list.begin() ){

        QCOMPARE(*iter->item, value);
        ++value;
        iter = iter->previous;
    }

    /* testing correct assignment of begin-pointer */
    QCOMPARE(*iter->next->item, 4);
}

/**
 * To Test the remove() function we need to add items to the list
 * and then remove an item that we added.
 * We have to check if the item we removed is still valid, if the next,
 * previous, begin and end pointers are still pointing to the correct nodes
 * and if the function returns true.
 * Finally we have to check if remove() returns false if we try to remove an
 * item that does not exist.
 */
void DLinkedList_UnitTest::test_remove()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.append(rValue0);
    rList.append(rValue1);
    rList.append(rValue2);

    pList.append(pValue0);
    pList.append(pValue1);
    pList.append(pValue2);

    rList.remove(1);
    pList.remove(pValue1);

    /* testing item_amount */
    QCOMPARE(rList.size(), 2);
    QCOMPARE(pList.size(), 2);

    /* clear the lists and check if they are empty and if the
     * original values still exist */

    while ( !rList.empty() ){

        rList.remove(rList.first());
    }

    while ( !pList.empty() ){

        pList.remove(pList.first());
    }

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());

    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);
}

/**
 * To Test the removeFirst() function we need to add items to the list
 * and then remove the first item.
 * We need to check if the removed item is the first item we added,
 * if the begin, end, next and previous pointers are still pointing correctly,
 * if the original variables are still valid and if the function returns
 * the correct boolean values if we either successfully remove or if we
 * try to remove from am empty list.
 */
void DLinkedList_UnitTest::test_removeFirst()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.append(rValue0);
    rList.append(rValue1);
    rList.append(rValue2);

    pList.append(pValue0);
    pList.append(pValue1);
    pList.append(pValue2);

    /* clear the lists and check if they are empty and if the
     * original values still exist */

    int counter = 0;
    while ( !rList.empty() ){

        QCOMPARE(rList.first(), counter++);
        rList.removeFirst();
    }

    counter = 0;
    while ( !pList.empty() ){

        QCOMPARE(*pList.first(), counter++);
        QVERIFY(pList.removeFirst());
    }

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());

    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);

    /* testing for false */
    QCOMPARE(rList.removeFirst(), false);
    QCOMPARE(pList.removeFirst(), false);
}

/**
 * To Test the removeLast() function we need to add items to the list
 * and then remove the last item.
 * We need to check if the removed item is the last item we added,
 * if the begin, end, next and previous pointers are still pointing correctly,
 * if the original variables are still valid and if the function returns
 * the correct boolean values if we either successfully remove or if we
 * try to remove from am empty list.
 */
void DLinkedList_UnitTest::test_removeLast()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.prepend(rValue0);
    rList.prepend(rValue1);
    rList.prepend(rValue2);

    pList.prepend(pValue0);
    pList.prepend(pValue1);
    pList.prepend(pValue2);

    /* clear the lists and check if they are empty and if the
     * original values still exist */

    int counter = 0;
    while ( !rList.empty() ){

        QCOMPARE(rList.last(), counter++);
        QVERIFY(rList.removeLast());
    }

    counter = 0;
    while ( !pList.empty() ){

        QCOMPARE(*pList.last(), counter++);
        pList.removeLast();
    }

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());

    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);

    /* testing for false */
    QCOMPARE(rList.removeLast(), false);
    QCOMPARE(pList.removeLast(), false);
}

/**
 * To test the takeFirst() function we need to add items to the list and then
 * take the first item and check if the item is indeed the first item we added,
 * if all the begin, end, next and previous pointers are still pointing correctly
 * and finally we need to check if the function throws an exception if we try
 * to take the first item from an empty list.
 */
void DLinkedList_UnitTest::test_takeFirst()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.append(rValue0);
    rList.append(rValue1);
    rList.append(rValue2);

    pList.append(pValue0);
    pList.append(pValue1);
    pList.append(pValue2);

    int rItem0 = rList.takeFirst();
    QCOMPARE (rItem0, rValue0);
    int rItem1 = rList.takeFirst();
    QCOMPARE (rItem1, rValue1);
    int rItem2 = rList.takeFirst();
    QCOMPARE (rItem2, rValue2);

    int *pItem0 = pList.takeFirst();
    QCOMPARE (pItem0, pValue0);
    int *pItem1 = pList.takeFirst();
    QCOMPARE (pItem1, pValue1);
    int *pItem2 = pList.takeFirst();
    QCOMPARE (pItem2, pValue2);

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());
    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);

    /* testing if exception is thrown */
    QVERIFY_EXCEPTION_THROWN(rList.takeFirst(), runtime_error);
    QVERIFY_EXCEPTION_THROWN(pList.takeFirst(), runtime_error);
}


/**
 * To test the takeLast() function we need to add items to the list and then
 * take the last item and check if the item is indeed the last item we added,
 * if all the begin, end, next and previous pointers are still pointing correctly
 * and finally we need to check if the function throws an exception if we try
 * to take the last item from an empty list.
 */
void DLinkedList_UnitTest::test_takeLast()
{
    DLinkedList<int> rList;
    DLinkedList<int*> pList;

    int rValue0 = 0;
    int rValue1 = 1;
    int rValue2 = 2;

    int *pValue0 = new int(0);
    int *pValue1 = new int(1);
    int *pValue2 = new int(2);

    rList.prepend(rValue0);
    rList.prepend(rValue1);
    rList.prepend(rValue2);

    pList.prepend(pValue0);
    pList.prepend(pValue1);
    pList.prepend(pValue2);

    int rItem0 = rList.takeLast();
    QCOMPARE (rItem0, rValue0);
    int rItem1 = rList.takeLast();
    QCOMPARE (rItem1, rValue1);
    int rItem2 = rList.takeLast();
    QCOMPARE (rItem2, rValue2);

    int *pItem0 = pList.takeLast();
    QCOMPARE (pItem0, pValue0);
    int *pItem1 = pList.takeLast();
    QCOMPARE (pItem1, pValue1);
    int *pItem2 = pList.takeLast();
    QCOMPARE (pItem2, pValue2);

    /* testing begin() and end() */
    QCOMPARE(rList.begin()->next, rList.end());
    QCOMPARE(rList.end()->previous, rList.begin());
    QCOMPARE(pList.begin()->next, pList.end());
    QCOMPARE(pList.end()->previous, pList.begin());

    /* testing if original variables are still valid */
    QCOMPARE(rValue0, 0);
    QCOMPARE(rValue1, 1);
    QCOMPARE(rValue2, 2);

    QCOMPARE(*pValue0, 0);
    QCOMPARE(*pValue1, 1);
    QCOMPARE(*pValue2, 2);

    /* testing if exception is thrown */
    QVERIFY_EXCEPTION_THROWN(rList.takeLast(), runtime_error);
    QVERIFY_EXCEPTION_THROWN(pList.takeLast(), runtime_error);
}


QTEST_APPLESS_MAIN(DLinkedList_UnitTest)

#include "tst_dlinkedlist_unittest.moc"
