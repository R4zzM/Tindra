import bb.cascades 1.4

import QtCore 1.0

Page {
  
  property alias messageList: chatMessageList

  function refreshPage() {
    tinderManager.sendUpdates();
    messageList.refreshIndicator.active = true
    messageList.refreshIndicator.visible = true
    messageList.refreshIndicator.title = ""
    tinderDataModel.matchDataUpdated.connect(stopRefreshIndicator);
  }

  function stopRefreshIndicator() {
    console.log("Stop refresh indifcator")
    messageList.refreshIndicator.active = false
    messageList.refreshIndicator.visible = false
    messageList.refreshIndicator.title = ""
    tinderDataModel.matchDataUpdated.disconnect(stopRefreshIndicator);
  }
  
  function partialRefresh() {
      tinderManager.sendPartialUpdate(tinderDataModel.lastActivityDate);
  }

  Container {

    ChatMessageList {
      id: chatMessageList
    }

    ChatInputTextArea {
      id: chatInputTextArea
    }
  }

  paneProperties: NavigationPaneProperties {
    backButton: ActionItem {
      onTriggered: {
        navigationPane.pop();
      }
    }
  }

  actions: [
    ActionItem {
      id: refreshButton
      title: "Refresh"
      ActionBar.placement: ActionBarPlacement.OnBar
      onTriggered: {
        console.log("ChatPage.qml: Refresh button clicked!");
        refreshPage();
      }
    },

    ActionItem {
      id: matchInfoButton
      title: "Info"
      ActionBar.placement: ActionBarPlacement.InOverflow
      onTriggered: {
        console.log("ChatPage.qml: Info button clicked!");
        var page = matchInfoPage.createObject()
        navigationPane.push(page)
      }
    },
    
    ActionItem {
        id: partialRefreshButton
        title: "PartialRefresh"
        ActionBar.placement: ActionBarPlacement.InOverflow
        onTriggered: {
            console.log("ChatPage.qml: Partial refresh clicked!");
            partialRefresh();
        }
    } 
  ]

  onCreationCompleted: {
    console.log("ChatPage.qml - Created. Starting partial refresh timer");
    updateTimer.start()
  }

  attachedObjects: [
    ComponentDefinition {
      id: matchInfoPage
      source: "MatchInfoPage.qml"
    },
    QTimer {
        id: updateTimer
        interval: 1000
        onTimeout: {
            partialRefresh()
        }
    }
  ]
}
