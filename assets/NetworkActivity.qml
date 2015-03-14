import bb.cascades 1.3

Container {
    property alias title: activityLabel.text
    property alias active: activityIndicator.running
    
    layout: DockLayout {}
    
    background: Color.create("#aa000000")
    
    //horizontalAlignment: HorizontalAlignment.Fill
    // verticalAlignment: VerticalAlignment.Fill
    
    Label {
        id: activityLabel
        
        horizontalAlignment: HorizontalAlignment.Center
        
        textStyle {
            base: SystemDefaults.TextStyles.BigText;
            color: Color.White
        }
    }
    
    ActivityIndicator {
        id: activityIndicator
        
        horizontalAlignment: HorizontalAlignment.Center
        
        preferredHeight: ui.du(55.6)
        preferredWidth: ui.du(55.6)
    }
}

