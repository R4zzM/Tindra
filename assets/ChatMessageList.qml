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

            message: nameAndMessage()
            // message: ListItemData.message
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
