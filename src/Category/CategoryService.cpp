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

bool CategoryService::saveCategory(Category category)
{
    return this->_categoryRepository->saveCategory(category);
}

bool CategoryService::updateCategory(Category category)
{
    return this->_categoryRepository->updateCategory(category);
}

bool CategoryService::deleteCategoryById(int id)
{
    return this->_categoryRepository->deleteCategoryById(id);
}

