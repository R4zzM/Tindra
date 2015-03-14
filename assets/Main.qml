import bb.cascades 1.3

NavigationPane {
  id: navigationPane

  Page {

    Container {
      layout: DockLayout {}

      function facebookLoginSuccessful() {
        console.log("Main.qml: facebookLoginSuccessful tiggered!");

        facebookLoginWebView.close();

        createConnectionChain();   
      }

      function createConnectionChain() {
        tinderManager.sentAuthRequest.connect(startAuthIndicator);
        tinderManager.sentUpdatesRequest.connect(startUpdateIndicator);
        tinderDataModel.personalDataUpdated.connect(stopNetworkIndicator);
        tinderDataModel.matchDataUpdated.connect(stopNetworkIndicator);

        tinderDataModel.personalDataUpdated.connect(updateMatchData);

        console.log("MatchList.qml: sending auth...");

        tinderManager.sendAuth();
      }

      function startAuthIndicator(){
        console.log("Starting authorizing indicator...");
        nwActivityIndicator.title = "Authorizing"
        startNetworkIndicator();
      }

      function startUpdateIndicator() {
        console.log("Starting match updtate indicator...");
        nwActivityIndicator.title = "Updating matches"
        startNetworkIndicator();
      }

      function startNetworkIndicator(infoMsg) {

        nwActivityIndicator.active = true;
        nwActivityIndicator.visible = true;
      }

      function stopNetworkIndicator() {
        console.log("Stopping nwActivityIndicator...")
        nwActivityIndicator.active = false;
        nwActivityIndicator.visible = false;
      }

      function updateMatchData() {
        tinderManager.sendUpdates();
      }

      onCreationCompleted: {    
        console.log("Main.qml: Root view created!");
        tinderDataModel.gotFacebookAuthToken.connect(facebookLoginSuccessful)
        if(tinderManager.hasValidFacebookAuthToken) {
          var page = matchListPage.createObject();
          navigationPane.push(page);
        } else {
          console.log("Main.qml: No facebook authtoken. Launching login page...");
          // var page = facebookLoginPage.createObject();
          facebookLoginWebView.open();
        }
      }

      MatchListItem {
        id: matchList
      }

      NetworkActivity {
        id: nwActivityIndicator

        title: ""
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
      }
    }

    actions: [
      ActionItem {
        id: sendAuthAction
        title: "Send Auth"
        ActionBar.placement: ActionBarPlacement.InOverflow
        onTriggered: {
          console.log("MatchList.qml: Send auth button triggered.");
          tinderManager.sendAuth();
        }
      },

      ActionItem {
        id: sendUpdateAction
        title: "Refresh"
        ActionBar.placement: ActionBarPlacement.OnBar
        onTriggered: {
          console.log("MatchList.qml: Send updated button triggered.");
          tinderManager.sendUpdates();
        }
      },

      ActionItem {
        id: showMyInfo
        title: "Watashi"
        ActionBar.placement: ActionBarPlacement.InOverflow
        onTriggered: {
          console.log("MatchList.qml: Watashi button clicked!");
          var watashi = watashiPage.createObject()
          navigationPane.push(watashi)
        }
      }
    ]

    attachedObjects: [
      FacebookLoginWebView {
        id: facebookLoginWebView 
      }, 

      ComponentDefinition {
        id: chatPage
        source: "ChatPage.qml"
      },

      ComponentDefinition {
        id: watashiPage
        source: "WatashiPage.qml"
      }
    ]
  }

  onPopTransitionEnded: {
    page.destroy();
  }
}
