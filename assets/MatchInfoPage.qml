import bb.cascades 1.4

Page {
    Container {
                
        TitleLabelItem {
            title: "Name: "
            info: tinderDataModel.preparedMatch.person.name
        }
        
        TitleLabelItem {
            title: "Common Friends: "
            info: tinderDataModel.preparedMatch.common_friend_count.toString()
        }
        
        TitleLabelItem {
            title: "Common Interests: "
            info: tinderDataModel.preparedMatch.common_like_count.toString()
        }
        
        TitleLabelItem {
            title: "Created Date: "
            info: tinderDataModel.preparedMatch.created_date
        }
        
        TitleLabelItem {
            title: "Last Activity: "
            info: tinderDataModel.preparedMatch.last_activity_date
        }
        
        TitleLabelItem {
            title: "Ping Time: "
            info: tinderDataModel.preparedMatch.person.ping_time
        }
        
        TitleLabelItem {
            title: "Message Count: "
            info: tinderDataModel.preparedMatch.messages.length
        }
        
        TitleLabelItem {
            title: "Birth Date: "
            info: tinderDataModel.preparedMatch.person.birth_date
        }
        
        TitleLabelItem {
            title: "Gender: "
            info: tinderDataModel.preparedMatch.person.gender
        }
        
        TitleLabelItem {
            title: "Bio: "
            info: tinderDataModel.preparedMatch.person.bio
        }
    }
}
