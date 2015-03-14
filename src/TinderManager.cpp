/*
 * updateresponse.cpp
 *
 *  Created on: 7 feb 2015
 *      Author: rasmus
 */

#include "TinderManager.h"

#include <bb/data/JsonDataAccess>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QUrl>

TinderManager::TinderManager(TinderDataModel *dataModel, QObject *parent) :
    m_dataModel(dataModel),
    m_networkAccessManager(new QNetworkAccessManager(this))
{
    setParent(parent);
}

TinderManager::~TinderManager()
{
    delete m_networkAccessManager;
}

void TinderManager::sendAuth()
{
    const QUrl url("https://api.gotinder.com/auth");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader("User-Agent", "Tinder/3.0.4 (iPhone; iOS 7.1; Scale/2.00)'");

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    QVariantMap jsonBody;
    jsonBody["facebook_token"] = m_dataModel->facebookAuthToken();
    jsonBody["facebook_id"] = "653215659";

    bb::data::JsonDataAccess jda;
    QByteArray postData;
    jda.saveToBuffer(jsonBody, &postData);

    qDebug("TinderManager::sendAuth(): Post data: " + postData);

    qDebug("TinderManager::sendAuth(): About to send!");
    QNetworkReply* reply = m_networkAccessManager->post(request, postData);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onAuthReply()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    emit sentAuthRequest();
}

void TinderManager::onAuthReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning("TinderManager::onAuthReply: reply was NULL");
        return;
    }

    QByteArray data;
    int responseCode;
    bool success = getReplyData(reply, responseCode, data);
    if(success) {
        bb::data::JsonDataAccess jda;
        QVariant authData = jda.loadFromBuffer(data);
        if (jda.hasError()) {
            bb::data::DataAccessError error = jda.error();
            qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
            return;
        }

        m_dataModel->newPersonalData(authData);
    }

    reply->deleteLater();
}

void TinderManager::sendUpdates()
{
    const QUrl url("https://api.gotinder.com/updates");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader("User-Agent", "Tinder/3.0.4 (iPhone; iOS 7.1; Scale/2.00)'");
    request.setRawHeader("X-Auth-Token", m_dataModel->getMyToken().toLatin1());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    // Empty request body
    bb::data::JsonDataAccess jda;
    QVariantMap jsonBody;
    QByteArray postData;
    jda.saveToBuffer(jsonBody, &postData);

    qDebug("TinderManager::sendUpdates(): About to send!");
    QNetworkReply* reply = m_networkAccessManager->post(request, postData);

    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onUpdatesReply()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    emit sentUpdatesRequest();
}

void TinderManager::onUpdatesReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning("TinderManager::onUpdatesReply: reply was NULL");
        return;
    }

    QByteArray data;
    int responseCode;
    bool success = getReplyData(reply, responseCode, data);
    if(success) {
        bb::data::JsonDataAccess jda;
        QVariant updatesData = jda.loadFromBuffer(data);
        if (jda.hasError()) {
            bb::data::DataAccessError error = jda.error();
            qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
            return;
        }

        QVariantMap root = updatesData.toMap();

        m_dataModel->setLastActivityDate(root["last_activity_date"].value<QString>());

        QVariantList matches = root["matches"].toList();

        m_dataModel->newMatchData(matches);
    }

    reply->deleteLater();
}

void TinderManager::sendPartialUpdate(QString lastActivity)
{
    const QUrl url("https://api.gotinder.com/updates");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader("User-Agent", "Tinder/3.0.4 (iPhone; iOS 7.1; Scale/2.00)'");
    request.setRawHeader("X-Auth-Token", m_dataModel->getMyToken().toLatin1());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    QVariantMap jsonBody;
    jsonBody["last_activity_date"] = lastActivity;

    bb::data::JsonDataAccess jda;
    QByteArray postData;
    jda.saveToBuffer(jsonBody, &postData);

    qDebug("TinderManager::sendPartialUpdate(): Post data: " + postData);

    QNetworkReply* reply = m_networkAccessManager->post(request, postData);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onPartialUpdateReply()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void TinderManager::onPartialUpdateReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning("TinderManager::onUpdatesReply: reply was NULL");
        return;
    }

    QByteArray data;
    int responseCode;
    bool success = getReplyData(reply, responseCode, data);
    if(success) {
        bb::data::JsonDataAccess jda;
        QVariant updatesData = jda.loadFromBuffer(data);
        if (jda.hasError()) {
            bb::data::DataAccessError error = jda.error();
            qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
            return;
        }

        QVariantMap root = updatesData.toMap();
        QVariantList matches = root["matches"].toList();

        // Got data
        if(matches.length() > 0) {
            qDebug("Got partial matchData update!");
            m_dataModel->setLastActivityDate(root["last_activity_date"].value<QString>());
            m_dataModel->updatedMatchData(matches);
        }
    }

    reply->deleteLater();
}

void TinderManager::sendMessage(QString matchId, QString message)
{
    const QUrl url("https://api.gotinder.com/user/matches/" + matchId);

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setRawHeader("User-Agent", "Tinder/3.0.4 (iPhone; iOS 7.1; Scale/2.00)'");
    request.setRawHeader("X-Auth-Token", m_dataModel->getMyToken().toLatin1());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    QVariantMap jsonBody;
    jsonBody["message"] = message;

    bb::data::JsonDataAccess jda;
    QByteArray postData;
    jda.saveToBuffer(jsonBody, &postData);

    qDebug("TinderManager::sendUpdates(): Post data: " + postData);

    qDebug("TinderManager::sendUpdates(): About to send!");
    QNetworkReply* reply = m_networkAccessManager->post(request, postData);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onSentMessageReply()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    emit sentMessage();
}

void TinderManager::onSentMessageReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning("TinderManager::onUpdatesReply: reply was NULL");
        return;
    }

    QByteArray data;
    int responseCode;
    bool success = getReplyData(reply, responseCode, data);
    if(success) {
        bb::data::JsonDataAccess jda;
        QVariant updatesData = jda.loadFromBuffer(data);
        if (jda.hasError()) {
            bb::data::DataAccessError error = jda.error();
            qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
            return;
        }

        qDebug("Confirm received, reponseCode = " + QString::number(responseCode).toLatin1());

        // m_dataModel->updateChatMessagesModel();
        emit sentMessageDelivered();

        // QVariantMap root = updatesData.toMap();
        // qDebug("Message sent! Text = " + root["message"].value<QString>().toLatin1());
    }

    reply->deleteLater();
}

bool TinderManager::getReplyData(QNetworkReply *reply, int &responseCode, QByteArray &data)
{
    bool success = false;

    if (reply->error() == QNetworkReply::NoError) {

        responseCode = (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)).value<int>();

        const int available = reply->bytesAvailable();
        if (available > 0) {
            data.append(reply->readAll());
        }

        success = true;
    } else {
        QString response =  tr("TinderManager::getReplyData(): Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        qDebug() << response;
    }

    return success;
}
