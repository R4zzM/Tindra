/*
 * MatchData.h
 *
 *  Created on: 8 feb 2015
 *      Author: rasmus
 */

#ifndef MATCHDATA_H_
#define MATCHDATA_H_

// #include "ChatMessage.h"

#include <QObject>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/DataModel>


class MatchData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString matchIdUnderscore READ matchIdUnderscore)
    Q_PROPERTY(QString matchId READ matchId)
    Q_PROPERTY(QString accountCreatedDate READ accountCreatedDate)
    Q_PROPERTY(QString lastActivityDate READ lastActivityDate)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString personId READ personId)
    Q_PROPERTY(QString birthDate READ birthDate)
    Q_PROPERTY(QString pingTime READ pingTime)

    Q_PROPERTY(bool isClosed READ isClosed)
    Q_PROPERTY(bool isDead READ isDead)
    Q_PROPERTY(bool isFollowing READ isFollowing)
    Q_PROPERTY(bool isFollowingMoments READ isFollowingMoments)
    Q_PROPERTY(bool isPending READ isPending)

    Q_PROPERTY(int commonFriendCount READ commonFriendCount)
    Q_PROPERTY(int commonLikeCount READ commonLikeCount)
    // Q_PROPERTY(int messageCount READ messageCount)

    Q_PROPERTY(int nChatMessages READ nChatMessages)
public:
    MatchData(QObject *parent = 0);
    virtual ~MatchData();

   //  Q_INVOKABLE ChatMessage *chatMessageAt(int number); // Message numbers start at 0

    // TINDER JSON Getters
    QString matchIdUnderscore();
    QString matchId();
    QString accountCreatedDate();
    QString lastActivityDate();
    QString name();
    QString personId();
    QString birthDate();
    QString pingTime();

    bool isClosed();
    bool isDead();
    bool isFollowing();
    bool isFollowingMoments();
    bool isPending();

    int commonFriendCount();
    int commonLikeCount();
    int messageCount(); // Always returns 0

    // TINDRA getters //
    int nChatMessages(); // Returns the actual number of messages

    // TINDER JSON Setters //
    void matchIdUnderscore(QString& value);
    void matchId(QString& value);
    void accountCreatedDate(QString& value);
    void lastActivityDate(QString& value);
    void name(QString& value);
    void personId(QString& value);
    void birthDate(QString& value);
    void pingTime(QString& value);

    void isClosed(bool value);
    void isDead(bool value);
    void isFollowing(bool value);
    void isFollowingMoments(bool value);
    void isPending(bool value);

    void commonFriendCount(int value);
    void commonLikeCount(int value);
    void messageCount(int value);

    // TINDRA setters //
    // void addMessage(ChatMessage *);

private:
    QString m_matchIdUnderscore;
    QString m_matchId;
    QString m_accountCreatedDate;
    QString m_lastActivityDate;
    QString m_chatHistory;
    QString m_name;
    QString m_personId;
    QString m_birthDate;
    QString m_pingTime;

    bool m_isClosed;
    bool m_isDead;
    bool m_isFollowing;
    bool m_isFollowingMoments;
    bool m_isPending;

    int m_commonFriendCount;
    int m_commonLikeCount;
    int m_messageCount;

    // QList<ChatMessage *> *m_chatMessages;
    // QList<ChatMessage *> *m_chatMessages;
};

#endif /* MATCHDATA_H_ */
