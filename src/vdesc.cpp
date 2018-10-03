#include "vdesc.h"
#include "ui_vdesc.h"
#include "qdebug.h"
#include<QStringList>
#include <QTime>
#include <QIcon>


vDesc::vDesc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vDesc)
{
    setWindowIcon(QIcon(":/vDesc.png"));
    ui->setupUi(this);
    //ui->messages->setWordWrap(true);
    ui->messages->setTextElideMode(Qt::ElideNone);
    manager = new QNetworkAccessManager(this);
    manager2 = new QNetworkAccessManager(this);
    manager3 = new QNetworkAccessManager(this);
    manager4 = new QNetworkAccessManager(this);
    manager5 = new QNetworkAccessManager(this);

    connect(ui->tokenEdit,&QLineEdit::returnPressed,this,&vDesc::onReturnPressed);
    connect(ui->messageInput,&QLineEdit::returnPressed,this,&vDesc::sendMessage);
    connect(ui->changeTokenPb,&QPushButton::clicked,this,&vDesc::onChangeTokenClicked);
    connect(ui->getFriendsPb,&QPushButton::clicked,this,&vDesc::onGetFriendsClicked);
    connect(manager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(onReplyFinished(QNetworkReply*)));
    connect(ui->friendsOnline, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(chooseIdOnline()));
    connect(ui->allFriends, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(chooseId()));
    connect(ui->sendMessagePb,&QPushButton::clicked,this,&vDesc::sendMessage);
    connect(ui->getMessagesPb,&QPushButton::clicked,this,&vDesc::onGetMessagesClicked);
    connect(manager3, SIGNAL(finished(QNetworkReply*)),this, SLOT(onReplyForMessagesFinished(QNetworkReply*)));
    connect(manager4, SIGNAL(finished(QNetworkReply*)),this, SLOT(onReplyForSenderNameFinished(QNetworkReply*)));
    connect(ui->messages, &QListWidget::doubleClicked, this, &vDesc::onDialogDoubleClicked);
    connect(manager5, SIGNAL(finished(QNetworkReply*)),this, SLOT(onCurrentDialogLoaded(QNetworkReply*)));
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
    ui->messageInput->clear();
    manager->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.send?user_id=" + current_id + "&message="+ message +"&access_token="+token+"&v=5.85")));
    ui->messages->addItem(ui->nameEdit->text() + " : " + message);
}

void vDesc::onGetMessagesClicked(){
    ui->getMessagesPb->setText("Get messages");
    connect(ui->messages, &QListWidget::doubleClicked, this, &vDesc::onDialogDoubleClicked);
    ui->messages->clear();
    text.clear();
    sender_first_name.clear();
    sender_last_name.clear();
    from_id.clear();
    id.clear();
    chat_name.clear();

    int count = ui->spinBox->value();
    manager3->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.getConversations?count=" + QString::number(count) + "&access_token="+token+"&v=5.85")));
}

void vDesc::onReplyForMessagesFinished(QNetworkReply *reply){
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    jsonObject = jsonObject["response"].toObject();
    QJsonArray jsonArray = jsonObject["items"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject obj2 = value.toObject();
        obj = obj["conversation"].toObject();
        QJsonObject obj3 = obj;
        obj = obj["peer"].toObject();


        if(obj["type"].toString() == "user"){
            id.append(QString::number(obj["id"].toInt()));
        }
        else if(obj["type"].toString() == "chat"){
            obj3 = obj3["chat_settings"].toObject();
            chat_name.append(obj3["title"].toString());
             id.append(QString::number(obj["id"].toInt()));
        }
        else{id.append(QString::number(obj["id"].toInt()));}

        obj2 = obj2["last_message"].toObject();
        from_id.append(QString::number(obj2["from_id"].toInt()));
        text.append(obj2["text"].toString());
    }
    int i = 0;
    foreach (const QString &str, id) {
            if(str.startsWith("-")){                //фикс бага с отрицательными id
               id.removeOne(str);
               text.removeAt(i);
            }
            i++;
        }

    QString url = "https://api.vk.com/method/users.get?user_ids="+ id.join(",") + "&access_token="+token+"&v=5.85";
    manager4->get(QNetworkRequest(QUrl(url)));
    qDebug() << chat_name;
}

void vDesc::onReplyForSenderNameFinished(QNetworkReply* reply){
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["response"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString fn = obj["first_name"].toString();
        if(fn != "DELETED"){
        sender_first_name.append(fn);
        }else{
            sender_first_name.append(chat_name.at(0));
            chat_name.removeAt(0);
        }
        sender_last_name.append(obj["last_name"].toString());
        for(int i =0; i<from_id.length(); i++){
            if(from_id.at(i) == QString::number(obj["id"].toInt())){
                from_id.replace(i,QString(obj["first_name"].toString() + " " +obj["last_name"].toString() ));
            }
        }
    }

   for(int i = 0; i<text.length(); i++){
   /*    QString data_all = text.at(i);
           QString data_left = "";
           QString data_right;
           int offset = 60;
           if(data_all.length() > offset){
               data_left = data_all.left(offset);
               data_right = data_all.mid(offset);
               data_all = data_left;
               while(data_right.length() > offset){
                   QString data_temp = data_right.left(offset);
                   data_right = data_right.mid(offset);
                   data_all += "\n";
                   data_all += data_temp;

      ui->messages->addItem("[" + sender_first_name.at(i)+" "+sender_last_name.at(i)  + "]" + " от " + from_id.at(i) + " : " + data_all);
      data_all.clear();
      data_left.clear();
      data_right.clear();
        }
      }else{ */
               ui->messages->addItem("[" + sender_first_name.at(i)+" "+sender_last_name.at(i)  + "]" + " от " + from_id.at(i) + " : " + text.at(i));
           }

   }
//}

void vDesc::onDialogDoubleClicked(){
    disconnect(ui->messages, &QListWidget::doubleClicked, this, &vDesc::onDialogDoubleClicked);
    current_row = ui->messages->currentIndex().row();
    current_name = sender_first_name.at(current_row)+" "+sender_last_name.at(current_row);
    current_id = id.at(current_row);
    ui->messages->clear();
    QString url = "https://api.vk.com/method/messages.getHistory?count=" + QString::number(ui->spinBox->value()) + "&user_id="+ current_id + "&access_token="+token+"&v=5.85";
    manager5->get(QNetworkRequest(QUrl(url)));
    ui->getMessagesPb->setText("Back");
}

void vDesc::onCurrentDialogLoaded(QNetworkReply *reply){
    attachment_type.clear();
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    jsonObject = jsonObject["response"].toObject();
    QJsonArray jsonArray = jsonObject["items"].toArray();
    QStringList message_items;
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QString from_who;

        if(obj["from_id"].toInt() == current_id.toInt()){
            from_who = current_name;
        }else{
            from_who = ui->nameEdit->text();
        }
        QString text_m = obj["text"].toString();
        QString item = from_who + " : " + text_m ;
        message_items.append(item);
        QString type;
        QJsonArray attachments = value.toArray();
        attachments = obj["attachments"].toArray();
        if(attachments.empty()){
            type = "";
            attachment_type.append(type);
        }else{
        foreach (const QJsonValue & value, attachments) {
            QJsonObject obj = value.toObject();
            type = obj["type"].toString();
            attachment_type.append(type);
        }
      }
    }

    for(int i = message_items.length()-1; i >= 0; --i){
        QString data_all = message_items.at(i);
        if(attachment_type.at(i) == ""){
          /*  QString data_left = "";
            QString data_right;
            int offset = 60;
            if(data_all.length() > offset){
                data_left = data_all.left(offset);
                data_right = data_all.mid(offset);
                data_all = data_left;
                while(data_right.length() > offset){
                    QString data_temp = data_right.left(offset);
                    data_right = data_right.mid(offset);
                    data_all += "\n";
                    data_all += data_temp;
                }
            }*/
            ui->messages->addItem(data_all + attachment_type.at(i));
        }else{
            ui->messages->addItem(data_all + " [" + attachment_type.at(i) + "]");
        }
    }
}



