#include "User.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"

User::User()
{
    // Nothing
}

User::User(int userId, QString fullname, QDate birthday, int gender, QString email, QString phone, QString username, QString password, Role role, QString address, QDate created_at, QDate updated_at){
    this->user_id = userId;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
    this->username = username;
    this->password = password;
    this->role = role;
    this->address = address;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->borrowList = nullptr;
}

User::User(int userId, QString fullname, QDate birthday, int gender, QString email, QString phone, QString username, QString password, Role role, QString address){
    this->user_id = userId;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
    this->username = username;
    this->password = password;
    this->role = role;
    this->address = address;
    this->borrowList = nullptr;
}

User::User(int user_id, QString fullname, QDate birthday, int gender, QString phone, QString email){
    this->user_id = user_id;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
    this->borrowList = nullptr;
}

User::User(int user_id, QString fullname){
    this->user_id = user_id;
    this->fullname = fullname;
    this->borrowList = nullptr;
}

User::~User()
{
    // Nothing
}

// getter - setter
int User::getUserId() const{
    return this->user_id;
}
void User::setUserId(int user_id){
    this->user_id = user_id;
}
QString User::getFullname() const{
    return this->fullname;
}
void User::setFullName(QString fullname){
    this->fullname = fullname;
}
QDate User::getBirthday() const{
    return this->birthday;
}
void User::setBirthday(QDate birthday){
    this->birthday = birthday;
}
int User::getGender() const{
    return this->gender;
}
void User::setGender(int gender){
    this->gender = gender;
}
QString User::getEmail() const{
    return this->email;
}
void User::setEmail(QString email){
    this->email = email;
}
QString User::getPhone() const{
    return this->phone;
}
void User::setPhone(QString phone){
    this->phone = phone;
}
QString User::getUsername() const{
    return this->username;
}
void User::setUsername(QString username){
    this->username = username;
}
QString User::getPassword() const{
    return this->password;
}
void User::setPassword(QString password){
    this->password = password;
}
Role User::getRole() const{
    return this->role;
}
void User::setRole(Role role){
    this->role = role;
}
QString User::getAddress() const{
    return this->address;
}
void User::setAddress(QString address){
    this->address = address;
}
QDate User::getCreatedAt() const{
    return this->created_at;
}
void User::setCreatedAt(QDate created_at){
    this->created_at = created_at;
}
QDate User::getUpdatedAt() const{
    return this->updated_at;
}
void User::setUpdatedAt(QDate updated_at){
    this->updated_at = updated_at;
}

void User::setBorrowBook(Listt<BorrowBook> * list){
    if (this->borrowList != NULL) delete this->borrowList;
    //(this->borrowList) = new LinkedListt<BorrowBook>();
    this->borrowList = list;
}

Listt<BorrowBook> *User::getBorrowList(){
    return this->borrowList;
}
//
bool User::operator == (const User& user) const{
    return this->user_id == user.user_id;
}

bool User::operator < (const User& user) const{
    return this->user_id < user.user_id;
}
User& User::operator=(const User& user){
    this->user_id = user.user_id;
    this->fullname = user.fullname;
    this->birthday = user.birthday;
    this->gender = user.gender;
    this->email = user.email;
    this->phone = user.phone;
    this->username = user.username;
    this->password = user.password;
    this->role = user.role;
    this->address = user.address;
    this->created_at = user.created_at;
    this->updated_at = user.updated_at;
    if (user.borrowList == nullptr) this->borrowList = nullptr;
    else {
        this->borrowList = new LinkedListt<BorrowBook>();
        for (int i = 0;i < user.borrowList->getSize();i++){
            this->borrowList->add(user.borrowList->get(i));
        }
    }
    return *this;
}

bool User::compareName(User a, User b){
    return a.getFullname() < b.getFullname();
}
bool User::compareRole(User a, User b){
    return a.getRole().getPriorty() < b.getRole().getPriorty();
}
bool User::compareCreateDate(User a, User b){
    return a.getCreatedAt() < b.getCreatedAt();
}

