import bb.cascades 1.4

Container {
  
  ListView {                
    
    function lastOnlineSecs(lastPingTime) {
      // console.log("onlineIsoDate: " + lastPingTime)
      var text = tinderDataModel.formattedLastOnlineText(lastPingTime)
      return text 
    }
    
    function updateText(isDirty) {
      // console.log("onlineIsoDate: " + lastPingTime)
        if(isDirty === "true") {
            return "Nytt"   
        } else {
            return ""
        }
    }

    dataModel: tinderDataModel.matchesDataModel

    accessibility.name: "TODO: Add property content"

    onCreationCompleted: {
      console.log("MatchList created!");
    }

    onDataModelChanged: {
      console.log("onDataModelChanged....")
    }

    onTriggered: {

      console.log("onTriggered signal received!");
      console.log("indexPath.length = " + indexPath.length);
      console.log("indexPath[0] = " + indexPath[0]);

      tinderDataModel.prepareMatch(indexPath[0]);

      var chat = chatPage.createObject();
      console.log("Before pushing chatpage.");
      navigationPane.push(chat);
    }

    listItemComponents: [
      ListItemComponent {
        type: "item"

        StandardListItem {

          title: ListItemData.person.name
          description: ListItem.view.lastOnlineSecs(ListItemData.person.ping_time)
          status: ListItem.view.updateText(ListItemData.dirty)

          imageSpaceReserved: false
        }
      }
    ]
  }
}
