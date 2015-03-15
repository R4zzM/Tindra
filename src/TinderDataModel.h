/*
 * TinderDataModel.h
 *
 *  Created on: 11 feb 2015
 *      Author: rasmus
 */

#ifndef TINDERDATAMODEL_H_
#define TINDERDATAMODEL_H_

#include "MatchData.h"

#include <QObject>

#include <bb/cascades/DataModel>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/QListDataModel>

using namespace bb::cascades;

class TinderDataModel : public QObject
{
    Q_OBJECT

    // Properties for match data
    Q_PROPERTY(bb::cascades::DataModel* matchesDataModel READ matchesDataModel NOTIFY matchDataUpdated)
    Q_PROPERTY(QVariant preparedMatch READ preparedMatch)
    Q_PROPERTY(bb::cascades::DataModel* currentMatchMessagesDataModel READ currentMatchMessagesDataModel NOTIFY chatMessagesDataUpdated)
    Q_PROPERTY(QVariant facebookAuthToken READ facebookAuthToken)
    Q_PROPERTY(QVariant lastActivityDate READ getLastActivityDate)

    Q_PROPERTY(QString myId READ getMyId)
    Q_PROPERTY(QString myToken READ getMyToken)
    Q_PROPERTY(QString myApiToken READ getMyApiToken)
    Q_PROPERTY(QString myBio READ getMyBio)
    Q_PROPERTY(QString myCreatedDate READ getMyCreatedDate)
    Q_PROPERTY(QString myActiveDate READ getMyActiveTime)
    Q_PROPERTY(QString myPingTime READ getMyPingTime)
    Q_PROPERTY(QString myName READ getMyName)
    Q_PROPERTY(bool myIsDiscoverable READ getMyIsDiscoverable)
    Q_PROPERTY(int myGender READ getMyGender)
    Q_PROPERTY(int myGenderFilter READ getMyGenderFilter)
    Q_PROPERTY(int myAgeFilterMin READ getMyAgeFilterMin)
    Q_PROPERTY(int myAgeFilterMax READ getMyAgeFilterMax)

    // Properties for personal data
    Q_PROPERTY(bool hasValidFacebookAuthToken READ hasValidFacebookAuthToken)
public:
    TinderDataModel(QObject *parent);
    virtual ~TinderDataModel();

    // Called from the GUI to get data
    Q_INVOKABLE int matchCount(); // Number of matches
    Q_INVOKABLE MatchData *getMatch(int index); // First match has index 0
    Q_INVOKABLE void prepareMatch(int index); // The match that we are currently working on
    Q_INVOKABLE void setFacebookAuthToken(QVariant token);
    Q_INVOKABLE int secondsSinceOnline(QString iso8601LastOnline);
    Q_INVOKABLE QString formattedLastOnlineText(QString iso8601Date);
    Q_INVOKABLE QString prettifyTimestamp(QString iso8601Date);

    // Version information.
    Q_INVOKABLE QString getMyActiveTextVersion();
    Q_INVOKABLE QString getMyAgeFilterVersion();
    Q_INVOKABLE QString getMyMatchmakerVersion();
    Q_INVOKABLE QString getMyTrendingVersion();
    Q_INVOKABLE QString getMyTrendingActiveTextVersion();

    bb::cascades::DataModel *matchesDataModel();
    bb::cascades::DataModel *currentMatchMessagesDataModel();
    QVariantMap preparedMatch();

    bool hasValidFacebookAuthToken();
    QString facebookAuthToken();
    void updateChatMessagesModel();

    // Called from the controller to update the model with data.
    void newMatchData(QVariantList& data);
    void updatedMatchData(QVariantList& data);
    void newPersonalData(QVariant& data);

    QString getLastActivityDate();
    void setLastActivityDate(QString lastActivityDate);

    // Getters for personal info
    QString getMyId();
    QString getMyToken();
    QString getMyApiToken();
    QString getMyBio();
    QString getMyCreatedDate();
    QString getMyActiveTime();
    QString getMyPingTime();
    QString getMyName();
    bool getMyIsDiscoverable();
    int getMyGender();
    int getMyGenderFilter();
    int getMyAgeFilterMin();
    int getMyAgeFilterMax();

Q_SIGNALS:
    void gotFacebookAuthToken();
    void personalDataUpdated();
    void matchDataUpdated();
    void chatMessagesDataUpdated();

private:
    QString m_facebookAuthToken;
    QString m_lastActivityDate;
    GroupDataModel *m_matchesDataModel;
    GroupDataModel *m_chatMessagesDataModel;
    QVariantMap m_preparedMatch;

    QVariantList m_matchData;
    int m_currentMatchIdx;

    // Data given from auth data request
    QString m_myId;
    QString m_myToken;
    QString m_myApiToken; // same as m_token
    QString m_myBio;
    QString m_myCreatedDate;
    QString m_myActiveTime;
    QString m_myPingTime;
    QString m_myName;
    bool m_myIsDiscoverable;
    int m_myGender;
    int m_myGenderFilter;
    int m_myAgeFilterMin;
    int m_myAgeFilterMax;

    // Versions from auth data -- unsure what this is
    QString m_activeTextVersion;
    QString m_ageFilterVersion;
    QString m_matchmakerVersion;
    QString m_trendingVersion;
    QString m_trendingActiveTextVersion;
};

#endif /* TINDERDATAMODEL_H_ */
