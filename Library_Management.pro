#-------------------------------------------------
#
# Project created by QtCreator 2020-11-27T22:06:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library_Management
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils/DatabaseConnection/DatabaseConnection.cpp \
    utils/ListPackage/Listt/Listt.cpp \
    utils/ListPackage/ArrayListt/ArrayListt.cpp \
    utils/ListPackage/LinkedListt/LinkedListt.cpp \
    utils/ListPackage/NodeLinkedListt/NodeLinkedListt.cpp \
    src/Publisher/Publisher.cpp \
    base/Repository/Repository.cpp \
    src/Publisher/PublisherRepository.cpp \
    src/Publisher/PublisherService.cpp \
    utils/Comparable/Comparable.cpp \
    src/Category/Category.cpp \
    src/Category/CategoryRepository.cpp \
    src/Category/CategoryService.cpp \
    utils/DotEnv/DotEnv.cpp \
    src/IssuingCompany/IssuingCompany.cpp \
    src/IssuingCompany/IssuingCompanyRepository.cpp \
    src/IssuingCompany/IssuingCompanyService.cpp \
    src/Author/Author.cpp \
    src/Author/AuthorRepository.cpp \
    src/Author/AuthorService.cpp \
    src/Book/Book.cpp \
    logindialog.cpp \
    src/Book/BookRepository.cpp \
    src/Book/BookService.cpp \
    src/User/User.cpp \
    src/User/UserRepository.cpp \
    src/User/UserService.cpp \
    src/BorrowBook/BorrowBook.cpp \
    manageuser.cpp \
    managebook.cpp \
    ui_component/edit_book/ChangeBookPublisher.cpp \
    ui_component/edit_book/BridgeManageBookUpdateProp.cpp \
    ui_component/edit_book/ChangeBookCategory.cpp \
    ui_component/edit_book/ChangeBookIssuingCompany.cpp \
    ui_component/edit_book/ChangeBookAuthors.cpp \
    ui_component/manage_publisher/ManagePublisher.cpp \
    ui_component/manage_category/ManageCategory.cpp \
    ui_component/manage_issuing_company/ManageIssuingCompany.cpp \
    utils/Auth/Password.cpp \
    src/Role/Role.cpp \
    src/Role/RoleRepository.cpp \
    src/Role/RoleService.cpp \
    managerole.cpp \
    utils/Sort/Sort.cpp

HEADERS  += mainwindow.h \
    utils/DatabaseConnection/DatabaseConnection.h \
    utils/ListPackage/Listt/Listt.h \
    utils/ListPackage/ArrayListt/ArrayListt.h \
    utils/ListPackage/LinkedListt/LinkedListt.h \
    utils/ListPackage/NodeLinkedListt/NodeLinkedListt.h \
    src/Publisher/Publisher.h \
    base/Repository/Repository.h \
    src/Publisher/PublisherRepository.h \
    src/Publisher/PublisherService.h \
    utils/Comparable/Comparable.h \
    src/Category/Category.h \
    src/Category/CategoryRepository.h \
    src/Category/CategoryService.h \
    utils/DotEnv/DotEnv.h \
    src/IssuingCompany/IssuingCompany.h \
    src/IssuingCompany/IssuingCompanyRepository.h \
    src/IssuingCompany/IssuingCompanyService.h \
    src/Author/Author.h \
    src/Author/AuthorRepository.h \
    src/Author/AuthorService.h \
    src/Book/Book.h \
    logindialog.h \
    src/Book/BookRepository.h \
    src/Book/BookService.h \
    src/User/User.h \
    src/User/UserRepository.h \
    src/User/UserService.h \
    src/BorrowBook/BorrowBook.h \
    manageuser.h \
    managebook.h \
    ui_component/edit_book/ChangeBookPublisher.h \
    ui_component/edit_book/BridgeManageBookUpdateProp.h \
    ui_component/edit_book/ChangeBookCategory.h \
    ui_component/edit_book/ChangeBookIssuingCompany.h \
    ui_component/edit_book/ChangeBookAuthors.h \
    ui_component/manage_publisher/ManagePublisher.h \
    ui_component/manage_category/ManageCategory.h \
    ui_component/manage_issuing_company/ManageIssuingCompany.h \
    ui_component/edit_book/ChangeBookAuthors.h\
    utils/Auth/Password.h \
    src/Role/Role.h \
    src/Role/RoleRepository.h \
    src/Role/RoleService.h \
    managerole.h \
    utils/Sort/Sort.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    manageuser.ui \
    managebook.ui \
    ui_component/edit_book/changebookpublisher.ui \
    ui_component/edit_book/ChangeBookCategory.ui \
    ui_component/edit_book/ChangeBookIssuingCompany.ui \
    ui_component/edit_book/ChangeBookAuthors.ui \
    ui_component/manage_publisher/ManagePublisher.ui \
    ui_component/manage_category/ManageCategory.ui \
    ui_component/manage_issuing_company/ManageIssuingCompany.ui \
    managerole.ui

DISTFILES += \
    config.txt
