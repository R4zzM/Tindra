/*
 * TinderDataModel.cpp
 *
 *  Created on: 11 feb 2015
 *      Author: rasmus
 */

#include <src/TinderDataModel.h>
#include <QDateTime>

TinderDataModel::TinderDataModel(QObject *parent) :
    m_matchesDataModel(new GroupDataModel(this)),
    m_chatMessagesDataModel(new GroupDataModel(this)),
    m_currentMatchIdx(0),
    m_lastActivityDate("")
{
    setParent(parent);

    QStringList matchesSortingKeys("last_activity_date");
    m_matchesDataModel->setSortingKeys(matchesSortingKeys);
    m_matchesDataModel->setGrouping(ItemGrouping::None);
    m_matchesDataModel->setSortedAscending(false); // Newest at the top of the list

    QStringList chatMessageSortingKeys("timestamp"); // Sort messages on timestamp
    m_chatMessagesDataModel->setSortingKeys(chatMessageSortingKeys);
    m_chatMessagesDataModel->setGrouping(ItemGrouping::None); // No headers, just a flat list.
    m_chatMessagesDataModel->setSortedAscending(true); // Newest message is at the end of the list
}

TinderDataModel::~TinderDataModel()
{
    delete m_matchesDataModel;
    delete m_chatMessagesDataModel;
}

void TinderDataModel::newMatchData(QVariantList& matchData)
{
    // First attempt
    m_matchData.clear();
    m_matchData = matchData;

    m_matchesDataModel->clear();
    m_matchesDataModel->insertList(matchData);

    emit matchDataUpdated();

    if(m_currentMatchIdx >= 0) {
        updateChatMessagesModel();
    }
}

void TinderDataModel::updatedMatchData(QVariantList& data)
{
    qDebug("TinderDataModel::updatedMatchData - About to update...");
    for (int i = 0; i < data.length(); i++) {
        QVariantMap newMatchData = data.at(i).toMap();
        bool foundMatch = false;
        for (QVariantList indexPath = m_matchesDataModel->first(); !indexPath.isEmpty();
                indexPath = m_matchesDataModel->after(indexPath))
            {
                QVariant item = m_matchesDataModel->data(indexPath);
                QVariantMap currentMatchData = item.toMap();
                if(newMatchData["_id"] == currentMatchData["_id"]) {
                    foundMatch = true;
                    QVariantList newMessages = newMatchData["messages"].toList();
                    if(newMessages.length() > 0) {
                        QVariantList currentMessages = currentMatchData["messages"].toList();
                        currentMessages.append(newMessages);
                        currentMatchData.insert("messages", currentMessages);
                        // currentMatchData.insert("dirty", "true");
                        m_matchesDataModel->updateItem(indexPath, currentMatchData);
                        qDebug("TinderDataModel::updatedMatchData - m_matchesDataModel updated!");
                        updateChatMessagesModel();
                    }
                    // Only new messages are interesting for partial updates
                }
            }

        if(!foundMatch) {
            // New match. Add to list!
            // emit matchDataUpdated();
            // TODO
        }
    }

}

void TinderDataModel::newPersonalData(QVariant& authData)
{
    QVariantMap root = authData.toMap();
    m_myToken = root["token"].value<QString>();

    qDebug() << "TinderDataModel::newPersonalData: " << "m_myToken = " << m_myToken;

    QVariantMap user = root["user"].toMap();
    m_myApiToken = user["api_token"].value<QString>();
    m_myBio = user["bio"].value<QString>();
    m_myCreatedDate = user["create_date"].value<QString>();
    m_myActiveTime = user["active_time"].value<QString>();
    m_myPingTime = user["ping_time"].value<QString>();
    m_myIsDiscoverable = user["discoverable"].value<bool>();
    m_myGender = user["gender"].value<int>();
    m_myGenderFilter = user["gender_filter"].value<int>();
    m_myName = user["name"].value<QString>();
    m_myAgeFilterMin = user["age_filter_min"].value<int>();
    m_myAgeFilterMax = user["age_filter_max"].value<int>();

    QVariantMap versions = root["versions"].toMap();
    m_activeTextVersion = versions["active_text"].value<QString>();
    m_ageFilterVersion = versions["age_filter"].value<QString>();
    m_matchmakerVersion = versions["matchmaker"].value<QString>();
    m_trendingVersion = versions["trending"].value<QString>();
    m_trendingActiveTextVersion = versions["trending_active_text"].value<QString>();

    emit personalDataUpdated();
}

// -- //

QString TinderDataModel::getMyActiveTime()
{
    return m_myActiveTime;
}

QString TinderDataModel::getMyId()
{
    return m_myId;
}

QString TinderDataModel::getMyToken()
{
    return m_myToken;
}

QString TinderDataModel::getMyApiToken()
{
    return m_myApiToken;
}

QString TinderDataModel::getMyBio()
{
    return m_myBio;
}

QString TinderDataModel::getMyCreatedDate()
{
    return m_myCreatedDate;
}

QString TinderDataModel::getMyPingTime()
{
    return m_myPingTime;
}

QString TinderDataModel::getMyName()
{
    return m_myName;
}

bool TinderDataModel::getMyIsDiscoverable()
{
    return m_myIsDiscoverable;
}

int TinderDataModel::getMyGenderFilter()
{
    return m_myGenderFilter;
}

int TinderDataModel::getMyAgeFilterMin()
{
    return m_myAgeFilterMin;
}

int TinderDataModel::getMyAgeFilterMax()
{
    return m_myAgeFilterMax;
}

int TinderDataModel::getMyGender()
{
    return m_myGender;
}

QString TinderDataModel::getMyActiveTextVersion()
{
    return m_activeTextVersion;
}

QString TinderDataModel::getMyAgeFilterVersion()
{
    return m_ageFilterVersion;
}

QString TinderDataModel::getMyMatchmakerVersion()
{
    return m_matchmakerVersion;
}

QString TinderDataModel::getMyTrendingVersion()
{
    return m_trendingVersion;
}

QString TinderDataModel::getMyTrendingActiveTextVersion()
{
    return m_trendingActiveTextVersion;
}

// --- //

int TinderDataModel::matchCount()
{
    return m_matchData.count();
}

MatchData* TinderDataModel::getMatch(int index)
{
    QVariantMap match = m_matchData.at(index).toMap();
    bool closed = match["closed"].value<bool>();
    bool dead = match["dead"].value<bool>();
    bool following = match["following"].value<bool>();
    bool followingMoments = match["following_moments"].value<bool>();
    bool pending = match["pending"].value<bool>();

    int commonFriendCount = match["common_friend_count"].value<int>();
    int commonLikeCount = match["common_like_count"].value<int>();
    int messageCount = match["message_count"].value<int>();

    QString idUnderscore = match["_id"].value<QString>();
    QString accountCreated = match["created_date"].value<QString>();
    QString id = match["id"].value<QString>();
    QString lastActivityDate = match["last_activity_date"].value<QString>();

    QVariantMap person = match["person"].toMap(); // Person is a map in itself
    QString personId = person["_id"].value<QString>();
    // QString bio = person["_id"].value<QString>(); // TODO Add to model.
    QString birthDate = person["birth_date"].value<QString>();
    // QString gender = person["gender"].value<QString>(); // TODO Add to model.
    QString name = person["name"].value<QString>();
    QString pingTime = person["ping_time"].value<QString>();

    // Add data to match object
    MatchData *matchObj = new MatchData();
    matchObj->isClosed(closed);
    matchObj->isDead(dead);
    matchObj->isFollowing(following);
    matchObj->isFollowingMoments(followingMoments);
    matchObj->isPending(pending);

    matchObj->commonFriendCount(commonFriendCount);
    matchObj->commonLikeCount(commonLikeCount);
    matchObj->messageCount(messageCount);

    matchObj->personId(personId);
    matchObj->birthDate(birthDate);
    matchObj->name(name);
    matchObj->pingTime(pingTime);

    // Create the messages and append them to the MatchData
    QVariantList chatMessages = match["messages"].toList();
    for(int i = 0; i < chatMessages.count(); i++)
    {
        QVariantMap chatMessage = chatMessages[i].toMap();
        QString messageId = chatMessage["_id"].value<QString>();
        QString createdDate = chatMessage["created_date"].value<QString>();
        QString from = chatMessage["from"].value<QString>();
        QString to = chatMessage["to"].value<QString>();
        QString matchId = chatMessage["match_id"].value<QString>();
        QString message = chatMessage["message"].value<QString>();
        QString sentDate = chatMessage["sent_date"].value<QString>();
        QString timestamp = chatMessage["timestamp"].value<QString>();

       /* ChatMessage *msg = new ChatMessage(matchObj);
        msg->messageId(messageId);
        msg->createdDate(createdDate);
        msg->from(from);
        msg->to(to);
        msg->matchId(matchId);
        msg->message(message);
        msg->sentDate(sentDate);
        msg->timestamp(timestamp);

        matchObj->addMessage(msg);*/
    }

    return matchObj;
}

DataModel *TinderDataModel::matchesDataModel()
{
    return m_matchesDataModel;
}

void TinderDataModel::prepareMatch(int idx)
{
    // Set current match
    m_currentMatchIdx = idx;
    updateChatMessagesModel();
}

DataModel *TinderDataModel::currentMatchMessagesDataModel()
{
    return m_chatMessagesDataModel;
}

QVariantMap TinderDataModel::preparedMatch()
{
    return m_preparedMatch;
}

bool TinderDataModel::hasValidFacebookAuthToken()
{
    // Should check expire time in the future
    qDebug("m_facebookAuthToken.length() > 0" + (m_facebookAuthToken.length() > 0));
    return m_facebookAuthToken.length() > 0;
}

QString TinderDataModel::facebookAuthToken()
{
    return m_facebookAuthToken;
}

void TinderDataModel::setLastActivityDate(QString lastActivityDate)
{
    if(m_lastActivityDate != lastActivityDate) {
        m_lastActivityDate = lastActivityDate;
    }
}

QString TinderDataModel::getLastActivityDate()
{
    return m_lastActivityDate;
}

void TinderDataModel::setFacebookAuthToken(QVariant token)
{
    m_facebookAuthToken = token.value<QString>();
    emit gotFacebookAuthToken();
}

void TinderDataModel::updateChatMessagesModel()
{
    qDebug("Updating chatMessageModel for idx = " + QString::number(m_currentMatchIdx).toLatin1());
    // Prepare current chat messages
    m_chatMessagesDataModel->clear();

    QVariantList indexPath;
    indexPath.append(m_currentMatchIdx);
    QVariantMap match = m_matchesDataModel->data(indexPath).toMap();
    m_preparedMatch = match;

    QVariantList messages = match["messages"].toList();
    m_chatMessagesDataModel->insertList(messages);

    emit chatMessagesDataUpdated();
}

///////////////////
// Utility stuff //
///////////////////

int TinderDataModel::secondsSinceOnline(QString iso8601Date)
{
    QDateTime lastOnline = QDateTime::fromString(iso8601Date, Qt::ISODate);
    QDateTime now = QDateTime::currentDateTimeUtc();
    int diff = lastOnline.secsTo(now);
    return diff;
}

QString TinderDataModel::formattedLastOnlineText(QString iso8601Date)
{
    QDateTime lastOnline = QDateTime::fromString(iso8601Date, Qt::ISODate);
    QDateTime now = QDateTime::currentDateTimeUtc();
    int secs = lastOnline.secsTo(now);
    int days = secs / 86400;
    int hours = secs / 3600;
    int minutes = secs / 60;
    if(days > 1)
        return QString(QString::number(days) + " dagar");
    else if(days == 1)
        return QString(QString::number(days) + " dag");
    else if(hours > 1)
        return QString(QString::number(hours) + " timmar");
    else if(hours == 1)
        return QString(QString::number(hours) + " timma");
    else if(minutes > 1)
        return QString(QString::number(minutes) + " minuter");
    else if(minutes == 1)
        return QString(QString::number(minutes) + " minut");
    else if(secs > 1)
        return QString(QString::number(secs) + " sekunder");
    else
        return QString("Loggade in precis nu!!!");
}
