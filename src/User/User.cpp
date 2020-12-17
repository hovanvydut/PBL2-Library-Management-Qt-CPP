#include "User.h"

User::User()
{
    // Nothing
}

User::User(int userId, QString fullname, QDate birthday, int gender, QString email, QString phone, QString username, QString password, int roleId, QString address, QDate created_at, QDate updated_at){
    this->user_id = userId;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
    this->username = username;
    this->password = password;
    this->role_id = roleId;
    this->address = address;
    this->created_at = created_at;
    this->updated_at = updated_at;
}

User::User(int userId, QString fullname, QDate birthday, int gender, QString email, QString phone, QString username, QString password, int roleId, QString address){
    this->user_id = userId;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
    this->username = username;
    this->password = password;
    this->role_id = roleId;
    this->address = address;
}

User::User(int user_id, QString fullname, QDate birthday, int gender, QString phone, QString email){
    this->user_id = user_id;
    this->fullname = fullname;
    this->birthday = birthday;
    this->gender = gender;
    this->email = email;
    this->phone = phone;
}

User::User(int user_id, QString fullname){
    this->user_id = user_id;
    this->fullname = fullname;
}

User::~User()
{
    // Nothing
}

// getter - setter
int User::getUserId(){
    return this->user_id;
}
void User::setUserId(int user_id){
    this->user_id = user_id;
}
QString User::getFullname(){
    return this->fullname;
}
void User::setFullName(QString fullname){
    this->fullname = fullname;
}
QDate User::getBirthday(){
    return this->birthday;
}
void User::setBirthday(QDate birthday){
    this->birthday = birthday;
}
int User::getGender(){
    return this->gender;
}
void User::setGender(int gender){
    this->gender = gender;
}
QString User::getEmail(){
    return this->email;
}
void User::setEmail(QString email){
    this->email = email;
}
QString User::getPhone(){
    return this->phone;
}
void User::setPhone(QString phone){
    this->phone = phone;
}
QString User::getUsername(){
    return this->username;
}
void User::setUsername(QString username){
    this->username = username;
}
QString User::getPassword(){
    return this->password;
}
void User::setPassword(QString password){
    this->password = password;
}
int User::getRoleId(){
    return this->role_id;
}
void User::setRoleId(int role_id){
    this->role_id = role_id;
}
QString User::getAddress(){
    return this->address;
}
void User::setAddress(QString address){
    this->address = address;
}
QDate User::getCreatedAt(){
    return this->created_at;
}
void User::setCreatedAt(QDate created_at){
    this->created_at = created_at;
}
QDate User::getUpdatedAt(){
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
