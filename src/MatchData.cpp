/*
 * MatchData.cpp
 *
 *  Created on: 8 feb 2015
 *      Author: rasmus
 */

#include <src/MatchData.h>

MatchData::MatchData(QObject *parent)
    //m_chatMessages(new QList<ChatMessage *>())
{
    setParent(parent);
}

MatchData::~MatchData()
{
    //delete m_chatMessages;
}

//////////////
// MatchData//
//////////////

QString MatchData::matchIdUnderscore()
{
    return m_matchIdUnderscore;
}

QString MatchData::matchId()
{
    return m_matchId;
}

QString MatchData::accountCreatedDate()
{
    return m_accountCreatedDate;
}

QString MatchData::lastActivityDate()
{
    return m_lastActivityDate;
}

QString MatchData::name()
{
    return m_name;
}

QString MatchData::personId()
{
    return m_personId;
}

QString MatchData::birthDate()
{
    return m_birthDate;
}

QString MatchData::pingTime()
{
    return m_pingTime;
}

bool MatchData::isClosed()
{
    return m_isClosed;
}

bool MatchData::isDead()
{
    return m_isDead;
}

bool MatchData::isFollowing()
{
    return m_isFollowing;
}

bool MatchData::isFollowingMoments()
{
    return m_isFollowingMoments;
}

bool MatchData::isPending()
{
    return m_isPending;
}

int MatchData::commonFriendCount()
{
    return m_commonFriendCount;
}

int MatchData::commonLikeCount()
{
    return m_commonFriendCount;
}

int MatchData::messageCount()
{
    return m_commonFriendCount;
}

int MatchData::nChatMessages()
{
    //return m_chatMessages->count();
}

/*ChatMessage* MatchData::chatMessageAt(int msgNumber)
{
    // Q_ASSERT(msgNumber < m_chatMessages->count());
    // qDebug("MatchData::chatMessageAt(...): Returning ChatMessage* at index " + QString::number(msgNumber).toLatin1());
    ChatMessage *chatMessage = m_chatMessages->at(msgNumber);
    // qDebug("MatchData::chatMessageAt(...): " + chatMessage->message().toLatin1());

    return chatMessage;
}*/



void MatchData::matchIdUnderscore(QString& value)
{
    m_matchIdUnderscore = value;
}

void MatchData::matchId(QString& value)
{
    m_matchId = value;
}

void MatchData::accountCreatedDate(QString& value)
{
    m_accountCreatedDate = value;
}

void MatchData::lastActivityDate(QString& value)
{
    m_lastActivityDate = value;
}

void MatchData::name(QString& value)
{
    m_name = value;
}

void MatchData::personId(QString& value)
{
    m_personId = value;
}

void MatchData::birthDate(QString& value)
{
    m_birthDate = value;
}

void MatchData::pingTime(QString& value)
{
    m_pingTime = value;
}

void MatchData::isClosed(bool value)
{
    m_isClosed = value;
}

void MatchData::isDead(bool value)
{
    m_isDead = value;
}

void MatchData::isFollowing(bool value)
{
    m_isFollowing = value;
}

void MatchData::isFollowingMoments(bool value)
{
    m_isFollowingMoments = value;
}

void MatchData::isPending(bool value)
{
    m_isPending = value;
}

void MatchData::commonFriendCount(int value)
{
    m_commonFriendCount = value;
}

void MatchData::commonLikeCount(int value)
{
    m_commonLikeCount = value;
}

void MatchData::messageCount(int value)
{
    m_messageCount = value;
}

/*void MatchData::addMessage(ChatMessage *chatMessage)
{
    m_chatMessages->append(chatMessage);
}*/
