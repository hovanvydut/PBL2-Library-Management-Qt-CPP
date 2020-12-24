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
    Listt<Category>* findByName(QString byName);
    bool saveCategory(Category category);
    bool updateCategory(Category category);
    bool deleteCategoryById(int id);
};

#endif // CATEGORYSERVICE_H
