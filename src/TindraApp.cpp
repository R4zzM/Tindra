/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "TindraApp.h"

#include "MatchData.h"
// #include "ChatMessage.h"
#include "TinderDataModel.h"
#include "TinderManager.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <QDebug>

using namespace bb::cascades;

TindraApp::TindraApp() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    QCoreApplication::setOrganizationName("Komulva AB");
    QCoreApplication::setApplicationName("Tindra");

    // Register C++ Types
    // qmlRegisterType<MatchData>("Tindra", 1, 0, "MatchData");
    // qmlRegisterType<ChatMessage>("Tindra", 1, 0, "ChatMessage");

    qmlRegisterType<QTimer>("QtCore", 1, 0, "QTimer");

    // Create the Model (TinderDataModel) and the controller (TinderManager)
    TinderDataModel *dataModel = new TinderDataModel(this);
    TinderManager *tinderManager = new TinderManager(dataModel, this);

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///Main.qml").parent(this);

    // Register the model and the controller with the GUI.
    qml->setContextProperty("tinderDataModel", dataModel);
    qml->setContextProperty("tinderManager", tinderManager);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);
}

void TindraApp::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("Tindra_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
