import bb.cascades 1.4

Page {
    Container {
        
        TitleLabelItem {
            title: "Name: "
            info: tinderDataModel.myName
        }
        
        TitleLabelItem {
            title: "Ping Time: "
            info: tinderDataModel.myPingTime
        }
        
        TitleLabelItem {
            title: "Active Date: "
            info: tinderDataModel.myActiveDate
        }
        
        TitleLabelItem {
            title: "Created Date: "
            info: tinderDataModel.myCreatedDate
        }
        
        TitleLabelItem {
            title: "Discoverable: "
            info: tinderDataModel.myIsDiscoverable.toString()
        }
        
        TitleLabelItem {
            title: "Token: "
            info: tinderDataModel.myToken
        }
        
        TitleLabelItem {
            title: "Gender: "
            info: tinderDataModel.myGender.toString()
        }
        
        TitleLabelItem {
            title: "Gender Filter: "
            info: tinderDataModel.myGenderFilter.toString()
        }
        
        TitleLabelItem {
            title: "Min Age: "
            info: tinderDataModel.myAgeFilterMin.toString()
        }
        
        TitleLabelItem {
            title: "Max Age: "
            info: tinderDataModel.myAgeFilterMax.toString()
        }
        
        TitleLabelItem {
            title: "Bio: "
            info: tinderDataModel.myBio        
        }
        
        TitleLabelItem {
            title: "Last activity date: "
            info: tinderDataModel.lastActivityDate      
        }
    }
}
