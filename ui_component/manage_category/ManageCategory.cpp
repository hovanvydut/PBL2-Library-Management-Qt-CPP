#include "ManageCategory.h"
#include "ui_ManageCategory.h"

ManageCategory::ManageCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageCategory)
{
    ui->setupUi(this);
    ui->table_category->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->categoryList = new LinkedListt<Category>();
}

int ManageCategory::getIndexRow()
{
    return this->indexRow;
}

bool ManageCategory::setIndexRow(int idx)
{
    if (idx < 0)
        return false;
    this->indexRow = idx;
    return true;
}

void ManageCategory::resetIndexRow()
{
    this->indexRow = -1;
}

Category ManageCategory::getCurrentCategory()
{
    return this->currentCategory;
}

bool ManageCategory::setCurrentCategory(Category category)
{
    this->currentCategory = category;
    return true;
}

ManageCategory::~ManageCategory()
{
    delete ui;
}

void ManageCategory::on_btn_search_clicked()
{
    CategoryService* categoryService = CategoryService::initCategoryService();

     QString byName = ui->input_search->text();

     // Tìm kiếm theo tên sách
     this->categoryList->clear();

     this->categoryList = categoryService->findByName(byName);

     QStandardItemModel *model = new QStandardItemModel();
     QStringList horizontalHeader;
     horizontalHeader.append("Id");
     horizontalHeader.append(QString::fromUtf8("Tên"));
     horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
     horizontalHeader.append(QString::fromUtf8("Cập nhật lần cưới"));
     model->setHorizontalHeaderLabels(horizontalHeader);
     ui->table_category->setModel(model);

     for (int i = 0; i < this->categoryList->getSize(); i++) {
         Category category = this->categoryList->get(i);
         QStandardItem *idCol = new QStandardItem(QString::number(category.getId()));
         QStandardItem *nameCol = new QStandardItem(category.getName());
         QStandardItem *createdAtCol = new QStandardItem(category.getCreatedAt().toString());
         QStandardItem *updatedAtCol = new QStandardItem(category.getUpdatedAt().toString());
         model->appendRow( QList<QStandardItem*>() << idCol << nameCol << createdAtCol << updatedAtCol);
     }
}

void ManageCategory::on_table_category_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (this->setIndexRow(idx))
    {
        if (this->setCurrentCategory(this->categoryList->get(idx)))
        {
            Category category = this->getCurrentCategory();
            ui->category_id->setText(QString::number(category.getId()));
            ui->category_name->setText(category.getName());
            ui->category_created_at->setDate(category.getCreatedAt());
            ui->category_updated_at->setDate(category.getDeletedAt());
        }

    }
}

void ManageCategory::on_btn_add_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn thêm?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi thêm!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        QString name = ui->category_name->text();
        QDate createdAt = ui->category_created_at->date();
        QDate updatedAt = ui->category_updated_at->date();

        if (name.size() > 0) {
            CategoryService* categoryService = CategoryService::initCategoryService();
            Category category(name, createdAt, updatedAt);

            if (categoryService->saveCategory(category))
            {

                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Thêm thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, kiểu dữ liệu có thể không hợp lệ."));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, kiểu dữ liệu có thể không hợp lệ."));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void ManageCategory::on_btn_update_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn cập nhật?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi cập nhật!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        if (this->currentCategory.getId() >= 0)
        {
            int id = this->currentCategory.getId();

            QString name = ui->category_name->text();
            QDate createdAt = ui->category_created_at->date();
            QDate updatedAt = ui->category_updated_at->date();

            Category category(id, name, createdAt, updatedAt);

            CategoryService* categoryService = CategoryService::initCategoryService();

            if (categoryService->updateCategory(category))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Cập nhật thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void ManageCategory::on_btn_delete_clicked()
{
    Category category = this->currentCategory;

    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn xóa?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi xóa!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        if (category.getId() >= 0)
        {
            CategoryService* categoryService = CategoryService::initCategoryService();
            if (categoryService->deleteCategoryById(category.getId()))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Xóa thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }

        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void ManageCategory::on_btn_reset_clicked()
{
    this->currentCategory = Category();
    this->resetIndexRow();

    ui->category_id->setText("");
    ui->category_name->setText("");
    ui->category_created_at->setDate(QDate::currentDate());
    ui->category_updated_at->setDate(QDate::currentDate());
}
