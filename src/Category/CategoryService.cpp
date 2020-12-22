#include "CategoryService.h"

CategoryService* CategoryService::_categoryService = nullptr;

CategoryService::CategoryService()
{
    this->_categoryRepository = CategoryRepository::initCategoryRepository();
}

CategoryService::~CategoryService()
{

}

CategoryService* CategoryService::initCategoryService()
{
    if (_categoryService == nullptr)
    {
        _categoryService = new CategoryService();
    }

    return _categoryService;
}

Listt<Category>* CategoryService::findAll()
{
    return this->_categoryRepository->findAll();
}

Listt<Category>* CategoryService::findByName(QString byName)
{
    return this->_categoryRepository->findByName(byName);
}

