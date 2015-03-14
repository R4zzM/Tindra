import bb.cascades 1.4


Container {
    property alias title: titleLabel.text;
    property alias info: textLabel.text;
    
    layout: StackLayout {
        orientation: LayoutOrientation.LeftToRight
    }
    
    Label {
        id: titleLabel
        text: ""
        textStyle {
            fontWeight: FontWeight.Bold
        }
    }
    
    Label {
        id: textLabel
        text: ""
        multiline: true
    }
}

