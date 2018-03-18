#include "arrayhandler.hpp"

class ArrayHandler::Impl {

public:

    int* array;
    std::size_t amount {0};
};

/**
 *
 */
ArrayHandler::ArrayHandler() : impl(std::make_unique<Impl>())
{
}

/**
 *
 */
ArrayHandler::~ArrayHandler() = default;

/**
 *
 */
void ArrayHandler::createArray(const std::size_t size) const & noexcept
{
    auto& array = impl->array;
    array = new int[size];

    impl->amount = size;

    for (
        unsigned int index = 0;
        index < size;
        index += 1
    ) {
        array[index] = 0;
    }
}

/**
 *
 */
void ArrayHandler::dropArray() const & noexcept
{
    free(impl->array);

    impl->amount = 0;
}

/**
 *
 */
std::size_t ArrayHandler::getAmount() const & noexcept
{
    return impl->amount;
}

/**
 *
 */
int ArrayHandler::getData(const std::size_t index) const & noexcept
{
    return impl->array[index];
}

/**
 *
 */
LineItem* ArrayHandler::getConnectorFromItems(
    const QGraphicsItem* const firstItem,
    const QGraphicsItem* const secondItem
)
{
    return new LineItem(firstItem, secondItem);
}
