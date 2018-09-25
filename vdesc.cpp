#include "vdesc.h"
#include "ui_vdesc.h"
#include "qdebug.h"
#include<QStringList>


vDesc::vDesc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vDesc)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->tokenEdit,&QLineEdit::returnPressed,this,&vDesc::onReturnPressed);
    connect(ui->changeTokenPb,&QPushButton::clicked,this,&vDesc::onChangeTokenClicked);
    connect(ui->getFriendsPb,&QPushButton::clicked,this,&vDesc::onGetFriendsClicked);
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

     foreach (const QJsonValue & value, jsonArray) {
         QJsonObject obj = value.toObject();
         QString first_name = obj["first_name"].toString();
         QString last_name = obj["last_name"].toString();
         QString sum = first_name + " " + last_name;

         ui->allFriends->addItem(sum);
     }
     getInfoByUserId2(valuesOnline);

}

void vDesc::replyFinished3(QNetworkReply *reply){
     QString strReply = (QString)reply->readAll();
     disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished3(QNetworkReply*)));
     QStringList values;
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonArray jsonArray = jsonObject["response"].toArray();

     foreach (const QJsonValue & value, jsonArray) {
         QJsonObject obj = value.toObject();
         QString first_name = obj["first_name"].toString();
         QString last_name = obj["last_name"].toString();
         QString sum = first_name + " " + last_name;

         ui->friendsOnline->addItem(sum);
     }

}

void vDesc::onReturnPressed(){
    ui->tokenEdit->setReadOnly(true);
    token = ui->tokenEdit->text();
    ui->tokenEdit->setText("************");
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
