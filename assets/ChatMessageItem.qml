import bb.cascades 1.4

Container {
    
    property alias sender: sender.text;
    property alias timestamp: timestamp.text;
    property alias message: message.text;
    property bool incoming;
    
    layout: StackLayout {
        orientation: LayoutOrientation.TopToBottom;
    }
    
    
    Container {
        id: header

        // background: Color.LightGray

        // opacity: 1.0
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight

        }

        leftPadding: ui.sdu(2.0)
        
        Label {
            
            function senderColor() {
                console.log("incoming = " + incoming)
                return (incoming == true)? Color.DarkMagenta : Color.DarkGreen;
            }
            
            id: sender

            textStyle.color: senderColor()

            horizontalAlignment: HorizontalAlignment.Left
            textStyle.fontWeight: FontWeight.Bold
        }
        
        Label {
            id: timestamp
            
            horizontalAlignment: HorizontalAlignment.Right
            textStyle.fontStyle: FontStyle.Italic
        }

    }
    Container {
        
        // background: Color.Red
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom;
        }
        leftPadding: ui.sdu(2.0)
        Label {
            id: message
            
            horizontalAlignment: HorizontalAlignment.Left
            multiline: true
        }
        Label {
            id: spacing
            
            text: "\n"
        }
    }
}
