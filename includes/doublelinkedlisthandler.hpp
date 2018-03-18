#ifndef DOUBLELINKEDLISTHANDLER_H_
#define DOUBLELINKEDLISTHANDLER_H_

#include "arrowlineitem.hpp"

#include <memory>

class DoubleLinkedListHandler
{

public:

    /**
     * @brief double linked list handler constructor
     */
    DoubleLinkedListHandler();

    /**
     * @brief default destructor
     */
    ~DoubleLinkedListHandler();

    /**
     * @brief called from the double linked list menu create action;
     * create a new double linked list item
     *
     * @param data the data to insert into the first node
     */
    void createDoubleLinkedList(const int& data) const & noexcept;

    /**
     * @brief called from the double linked list menu insert at the end action;
     * add a new node to the double linked list at the end
     *
     * @param data the data to insert into the new node
     */
    void insertAtTheEndDoubleLinkedList(const int& data) const & noexcept;

    /**
     * @brief called from the double linked list menu insert at the beginning action;
     * add a new node to the double linked list at the beginning
     *
     *
     * @param data the data to insert into the new node
     */
    void insertAtTheBeginningDoubleLinkedList(const int& data) const & noexcept;

    /**
     * @brief called from the double linked list menu drop at action;
     * delete the node at the given index
     *
     * @param index the index of the node to remove
     */
    void dropAtDoubleLinkedList(const unsigned int& index) const & noexcept;

    /**
     * @brief getter of the double linked list size
     *
     * @return unsigned int
     */
    unsigned int getSize() const & noexcept;

    /**
     * @brief getter of the double linked list last node index
     *
     * @return unsigned int
     */
    unsigned int getLastIndex() const & noexcept;

    /**
     * @brief getter of the double linked list value at the given index
     *
     * @return unsigned int
     */
    unsigned int getData(const unsigned int& index) const & noexcept;

    /**
     * @brief get the graphical connector of two consecutive items of the list
     * 
     * @param firstItem garphical item of the list
     * @param secondItem garphical item of the list right after firstItem
     * 
     * @return ArrowLineItem*
     */
    static ArrowLineItem* getConnectorFromItems(
        const QGraphicsItem* const firstItem,
        const QGraphicsItem* const secondItem
    );
private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

#endif
