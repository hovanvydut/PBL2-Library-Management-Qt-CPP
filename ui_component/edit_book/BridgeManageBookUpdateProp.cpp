#include "BridgeManageBookUpdateProp.h"

BridgeManageBookUpdateProp* BridgeManageBookUpdateProp::_instance = nullptr;

BridgeManageBookUpdateProp::BridgeManageBookUpdateProp()
{

}

BridgeManageBookUpdateProp::~BridgeManageBookUpdateProp()
{

}

BridgeManageBookUpdateProp* BridgeManageBookUpdateProp::getInstance()
{
    if (_instance == nullptr) {
        _instance = new BridgeManageBookUpdateProp();
    }

    return _instance;
}

void BridgeManageBookUpdateProp::setBook(Book* book)
{
    this->book = book;
}

Book* BridgeManageBookUpdateProp::getBook()
{
    return this->book;
}

