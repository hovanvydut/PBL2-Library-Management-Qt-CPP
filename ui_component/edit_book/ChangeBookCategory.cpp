#include "ChangeBookCategory.h"
#include "ui_ChangeBookCategory.h"

ChangeBookCategory::ChangeBookCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBookCategory)
{
    ui->setupUi(this);
    this->categoryList = new LinkedListt<Category>();
    ui->table_category->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ChangeBookCategory::~ChangeBookCategory()
{
    delete ui;
}

Category ChangeBookCategory::getCategory()
{
    return this->category;
}

void ChangeBookCategory::setCategory(Category category)
{
    this->category = category;
}

int ChangeBookCategory::getIndexRow()
{
    return this->indexRow;
}

void ChangeBookCategory::setIndexRow(int idx)
{
    this->indexRow = idx;
}

void ChangeBookCategory::on_btn_search_clicked()
{
    QString searchValue = ui->input_search_category->text();
    CategoryService *categoryService = CategoryService::initCategoryService();
    this->categoryList = categoryService->findByName(searchValue);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
    horizontalHeader.append(QString::fromUtf8("Cập nhật lần cuối"));
    horizontalHeader.append(QString::fromUtf8("Xóa mềm"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_category->setModel(model);

    for (int i = 0; i < this->categoryList->getSize(); i++) {
        Category category = this->categoryList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(category.getId()));
        QStandardItem *nameCol = new QStandardItem(category.getName());
        QStandardItem *created_at = new QStandardItem(category.getCreatedAt().toString("dd.MM.yyyy"));
        QStandardItem *updated_at = new QStandardItem(category.getUpdatedAt().toString("dd.MM.yyyy"));
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << created_at << updated_at);
    }
}

void ChangeBookCategory::on_table_category_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (idx >= 0) {
        Category category = this->categoryList->get(idx);

        this->setCategory(category);
        this->setIndexRow(idx);

        ui->current_category->setText(category.getName());
    }
}

void ChangeBookCategory::on_btn_update_clicked()
{
    this->close();
}
