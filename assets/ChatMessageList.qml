import bb.cascades 1.4

Container {

  property alias refreshIndicator: refreshIndicator

  layout: StackLayout {
    orientation: LayoutOrientation.TopToBottom
  }

  Container {
    layout: DockLayout { }

    onCreationCompleted: {

    }
    
    ListView {

      function getSenderName(id) {
          var name
          if(id === tinderDataModel.preparedMatch.person._id)
              name =  tinderDataModel.preparedMatch.person.name    
          else
              name = "Jag"
          
          return name
      }
      
      function isIncoming(id) {
          return (id === tinderDataModel.preparedMatch.person._id)? true : false
      }
      
      function prettifyTimeStamp(iso8601Timestamp) {
          return tinderDataModel.prettifyTimestamp(iso8601Timestamp)
      }

      property string herName: tinderDataModel.preparedMatch.person.name
      property string herId: tinderDataModel.preparedMatch.person._id

      accessibility.name: "TODO: Add property content"

      // Always show the latest message if the list is updated.
      stickToEdgePolicy: ListViewStickToEdgePolicy.EndThenBeginning

      dataModel: tinderDataModel.currentMatchMessagesDataModel

      onDataModelChanged: {
        console.log("ChatPage.qml: Data model changed!!")
      }

      onCreationCompleted: { 
        var name = tinderDataModel.preparedMatch.person.name 
        console.log("ListView for " + name + " created!!");
      }

      listItemComponents:[ 

        ListItemComponent {
          type: "item"

          ChatMessageItem {

            function nameAndMessage() {
              if(ListItem.data.from === ListItem.view.herId) {
                return "Hon: " + ListItemData.message;
              } 
              else {
                return "Moi: " + ListItemData.message;
              }
            }
            
            sender: ListItem.view.getSenderName(ListItem.data.from)
            incoming: ListItem.view.isIncoming(ListItem.data.from)
            timestamp: ListItem.view.prettifyTimeStamp(ListItemData.sent_date)
            // message: nameAndMessage()
            message: ListItemData.message
          }
        }
      ]
    }

    NetworkActivity {
      id: refreshIndicator                
      title: ""
      horizontalAlignment: HorizontalAlignment.Fill
      verticalAlignment: VerticalAlignment.Fill
      visible: false
    }
  }
}
