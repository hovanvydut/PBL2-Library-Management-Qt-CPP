#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H

#include "utils/ListPackage/Listt/Listt.h"
#include "src/Category/Category.h"
#include "src/Category/CategoryRepository.h"

class CategoryService
{

private:
    static CategoryService* _categoryService;
    CategoryRepository* _categoryRepository;
    CategoryService();
public:
    static CategoryService* initCategoryService();
    ~CategoryService();
    Listt<Category>* findAll();
};

#endif // CATEGORYSERVICE_H
