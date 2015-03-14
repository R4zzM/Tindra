import bb.cascades 1.4

Container {

  bottomPadding: ui.du(2.2)
  topPadding: ui.du(2.2)

  layout: StackLayout {
    orientation: LayoutOrientation.LeftToRight
  }

  TextArea {
    id: textInput

    layoutProperties: StackLayoutProperties {
      spaceQuota:  0.9
    }

    hintText: qsTr("Message")

    inputMode: TextAreaInputMode.Chat
    input {
      submitKey: SubmitKey.Send

      onSubmitted: {
        if (text.length > 0) {
          var id = tinderDataModel.preparedMatch.id
          tinderManager.sendMessage(id, text)
          textInput.text = ""
        }
      }
    }

    onTextChanged: {
      // if (text.length > 0) {
      //   textInput.text = ""
      // }
    }
  }
}
