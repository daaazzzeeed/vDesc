#include "vdesc.h"
#include "ui_vdesc.h"
#include "qdebug.h"
#include<QStringList>
#include <QTime>


vDesc::vDesc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vDesc)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    manager2 = new QNetworkAccessManager(this);
    connect(ui->tokenEdit,&QLineEdit::returnPressed,this,&vDesc::onReturnPressed);
    connect(ui->changeTokenPb,&QPushButton::clicked,this,&vDesc::onChangeTokenClicked);
    connect(ui->getFriendsPb,&QPushButton::clicked,this,&vDesc::onGetFriendsClicked);
    connect(manager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(onReplyFinished(QNetworkReply*)));
    connect(ui->friendsOnline, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(chooseIdOnline()));
    connect(ui->allFriends, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(chooseId()));
    connect(ui->sendMessagePb,&QPushButton::clicked,this,&vDesc::sendMessage);

}

vDesc::~vDesc()
{
    delete ui;
}

void vDesc::replyFinished(QNetworkReply *reply){
     QString strReply = (QString)reply->readAll();
     disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
     parseUsersJsonArray(strReply);
}

void vDesc::replyFinished2(QNetworkReply *reply){
     QString strReply = (QString)reply->readAll();
     disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished2(QNetworkReply*)));
     QStringList values;
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonArray jsonArray = jsonObject["response"].toArray();

     int count = 0;
     foreach (const QJsonValue & value, jsonArray) {
         QJsonObject obj = value.toObject();
         QString first_name = obj["first_name"].toString();
         QString last_name = obj["last_name"].toString();
         QString sum = first_name + " " + last_name;

         ui->allFriends->addItem(sum);
         count++;
     }
     ui->friendsTabWidget->setTabText(1, "Друзья " + QString::number(count));
     getInfoByUserId2(valuesOnline);

}

void vDesc::replyFinished3(QNetworkReply *reply){
     QString strReply = (QString)reply->readAll();
     disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished3(QNetworkReply*)));
     QStringList values;
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonArray jsonArray = jsonObject["response"].toArray();
     int count = 0;
     foreach (const QJsonValue & value, jsonArray) {
         QJsonObject obj = value.toObject();
         QString first_name = obj["first_name"].toString();
         QString last_name = obj["last_name"].toString();
         QString sum = first_name + " " + last_name;
         ui->friendsOnline->addItem(sum);
         count++;

     }
     ui->friendsTabWidget->setTabText(0, "Онлайн " + QString::number(count));
}

void vDesc::onReturnPressed(){
    ui->tokenEdit->setReadOnly(true);
    token = ui->tokenEdit->text();
    ui->tokenEdit->setText("************");
    manager2->get(QNetworkRequest(QUrl("https://api.vk.com/method/account.getProfileInfo?access_token="+token+"&v=5.85")));
}

void vDesc::onChangeTokenClicked(){
    ui->tokenEdit->setReadOnly(false);
}

void vDesc::onGetFriendsClicked(){
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/friends.get?user_id=32432594&order=name&fields=online&access_token="+token+"&v=5.85")));
}

QStringList vDesc::parseUsersJsonArray(QString jsonString){
    QStringList values;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    jsonObject = jsonObject["response"].toObject();
    QJsonArray jsonArray = jsonObject["items"].toArray();
    for(int i=0; i<jsonArray.count(); i++){

        jsonObject = jsonArray.at(i).toObject();
        values.append(QString::number(jsonObject["id"].toInt()));
        if(jsonObject["online"].toInt() == 1){
            valuesOnline.append(QString::number(jsonObject["id"].toInt()));
        }
    }
    val = values;
    getInfoByUserId(values);
    return values;
}

void vDesc::getInfoByUserId(QStringList str){
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished2(QNetworkReply*)));
    QString list = str.join(",");
    manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?user_ids=" + list + "&access_token="+token+"&v=5.85")));
}

void vDesc::getInfoByUserId2(QStringList str){
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished3(QNetworkReply*)));
    QString list = str.join(",");
    manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/users.get?user_ids=" + list + "&access_token="+token+"&v=5.85")));
}

void vDesc::onReplyFinished(QNetworkReply *reply){
    QString strReply = (QString)reply->readAll();
    QString first_name;
    QString last_name;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    jsonObject = jsonObject["response"].toObject();
    first_name = jsonObject["first_name"].toString();
    last_name = jsonObject["last_name"].toString();
    QString sum = first_name + " " + last_name;
    ui->nameEdit->setText(sum);
}
void vDesc::chooseIdOnline(){
    QString id = valuesOnline.at(ui->friendsOnline->currentIndex().row());
    name = ui->friendsOnline->currentIndex().data().toString();
    currentId = id;
}

void vDesc::chooseId(){
    QString id = val.at(ui->allFriends->currentIndex().row());
    name = ui->allFriends->currentIndex().data().toString();
    currentId = id;
}

void vDesc::sendMessage(){
    QString message = ui->messageInput->text();
    manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.send?user_id=" + currentId + "&message="+ message +"&access_token="+token+"&v=5.85")));
    ui->history->append("[" + QTime::currentTime().toString() + "] Сообщение: " + message +" отправлено: " + name );
}
