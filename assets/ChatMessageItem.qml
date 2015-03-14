import bb.cascades 1.4

Container {
    
    property alias sender: sender.text;
    property alias message: message.text;
    
    layout: StackLayout {
        orientation: LayoutOrientation.TopToBottom;
    }
    
    Label {
        id: sender;
        
        horizontalAlignment: HorizontalAlignment.Left;
        
    }
    
    Label {
        id: message;
         
        horizontalAlignment: HorizontalAlignment.Left;
        multiline: true;
    }
}
