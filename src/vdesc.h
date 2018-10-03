#ifndef VDESC_H
#define VDESC_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class vDesc;
}

class vDesc : public QMainWindow
{
    Q_OBJECT

public:
    explicit vDesc(QWidget *parent = 0);
    ~vDesc();
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manager2;
    QNetworkAccessManager *manager3;
    QNetworkAccessManager *manager4;
    QNetworkAccessManager *manager5;
    void getMyName();
    void getInfoByUserId(QStringList str);
    void getInfoByUserId2(QStringList str);
    QStringList parseUsersJsonArray(QString jsonString);
    QStringList values_list;
    QStringList first_name;
    QStringList last_name;
    QStringList valuesOnline;
    QStringList val ;
    QString currentId;
    QString name;
    QStringList text;
    QStringList sender_first_name, sender_last_name;
    QStringList from_id;
    QStringList id;
    int current_row;
    QString current_name;
    QString current_id;
    QStringList attachment_type;
    QStringList chat_name;

private:
    Ui::vDesc *ui;
    QString token;
private slots:
    void onReplyFinished(QNetworkReply*);
    void replyFinished(QNetworkReply*);
    void replyFinished2(QNetworkReply*);
    void replyFinished3(QNetworkReply*);
    void onReturnPressed();
    void onChangeTokenClicked();
    void onGetFriendsClicked();
    void chooseIdOnline();
    void chooseId();
    void sendMessage();
    void onGetMessagesClicked();
    void onReplyForMessagesFinished(QNetworkReply*);
    void onReplyForSenderNameFinished(QNetworkReply*);
    void onDialogDoubleClicked();
    void onCurrentDialogLoaded(QNetworkReply*);
};

#endif // VDESC_H
