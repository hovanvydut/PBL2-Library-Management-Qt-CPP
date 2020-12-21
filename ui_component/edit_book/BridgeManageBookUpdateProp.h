#ifndef BRIDGEMANAGEBOOKUPDATEPROP_H
#define BRIDGEMANAGEBOOKUPDATEPROP_H

#include "src/Book/Book.h"

class BridgeManageBookUpdateProp
{
private:
    static BridgeManageBookUpdateProp* _instance;
    Book* book = nullptr;
    BridgeManageBookUpdateProp();
public:
    static BridgeManageBookUpdateProp* getInstance();
    ~BridgeManageBookUpdateProp();
    void setBook(Book*);
    Book* getBook();
};

#endif // BRIDGEBETWEENEDITBOOKANDUPDATEITSPROPERTIES_H
