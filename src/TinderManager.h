/*
 * updateresponse.h
 *
 *  Created on: 7 feb 2015
 *      Author: rasmus
 */

#ifndef UPDATERESPONSE_H_
#define UPDATERESPONSE_H_

#include "TinderDataModel.h"

#include <QtCore/QObject>
#include <QNetworkAccessManager>

class TinderManager : public QObject
{
    Q_OBJECT
public:
    TinderManager(TinderDataModel *dataModel, QObject *parent = 0);
    virtual ~TinderManager();

    // Checks with the Tinder server if something new has happend
    Q_INVOKABLE void sendAuth();
    Q_INVOKABLE void sendUpdates();
    Q_INVOKABLE void sendPartialUpdate(QString iso8601Since);
    Q_INVOKABLE void sendMessage(QString matchId, QString message);

Q_SIGNALS:
    void sentAuthRequest();
    void sentUpdatesRequest();
    void sentMessage();
    void sentMessageDelivered();
    void matchesChanged();

    // Could be prefixed with "handle" e.g handleAuthReply
private Q_SLOTS:
    void onAuthReply();
    void onUpdatesReply();
    void onPartialUpdateReply();
    void onSentMessageReply();

private:
    bool getReplyData(QNetworkReply *reply, int& responseCode, QByteArray& buffer);
    TinderDataModel *m_dataModel;
    QNetworkAccessManager *m_networkAccessManager;
};

#endif /* UPDATERESPONSE_H_ */
