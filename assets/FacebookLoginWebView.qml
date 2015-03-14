import bb.cascades 1.4

        
 // To enable scrolling in the WebView, it is put inside a ScrollView.
 
 Sheet {
     
 
     Page {
         Container {
             
             ScrollView {
                 id: scrollView
                 
                 // We let the scroll view scroll in both x and y and enable zooming,
                 // max and min content zoom property is set in the WebViews onMinContentScaleChanged
                 // and onMaxContentScaleChanged signal handlers.
                 scrollViewProperties {
                     scrollMode: ScrollMode.Both
                     pinchToZoomEnabled: true
                     
                 }
                 
                 WebView {
                     
                     // The URL that is loaded points to the QML of this recipe on GitHub. 
                     // url: "https://github.com/blackberry/Cascades-Samples/blob/master/cascadescookbookqml/assets/WebView.qml"
                     
                     url: "https://www.facebook.com/dialog/oauth?client_id=464891386855067&redirect_uri=https://www.facebook.com/connect/login_success.html&scope=basic_info,email,public_profile,user_about_me,user_activities,user_birthday,user_education_history,user_friends,user_interests,user_likes,user_location,user_photos,user_relationship_details&response_type=token" 
                     
                     // WebView settings, initial scaling and width used by the WebView when displaying its content.
                     settings.viewport: {
                         "width": "device-width",
                         "initial-scale": 1.0
                     }
                     
                     /*onLoadProgressChanged: {
                         // Update the ProgressBar while loading.
                         // progressIndicator.value = loadProgress / 100.0
                         nwActivityIndicator.active = true;
                     }*/
                     
                     onMinContentScaleChanged: {
                         // Update the scroll view properties to match the content scale
                         // given by the WebView.
                         scrollView.scrollViewProperties.minContentScale = minContentScale;
                         
                         // Let's show the entire page to start with.
                         scrollView.zoomToPoint(0,0, minContentScale,ScrollAnimation.None)
                     }
                     
                     onMaxContentScaleChanged: {
                         // Update the scroll view properties to match the content scale 
                         // given by the WebView.
                         scrollView.scrollViewProperties.maxContentScale = maxContentScale;
                     }
                     
    /*                 onLoadingChanged: {
                         
                         if (loadRequest.status == WebLoadStatus.Started) {
                             // Show the ProgressBar when loading started.
                             // progressIndicator.opacity = 1.0
                             nwActivityIndicator.active = true;
                         } else if (loadRequest.status == WebLoadStatus.Succeeded) {
                             // Hide the ProgressBar when loading is complete.
                             // progressIndicator.opacity = 0.0
                             // nwActivityIndicator.active = false;
                             // nwActivityIndicator.visible = false;
                         } else if (loadRequest.status == WebLoadStatus.Failed) {
                             // If loading failed, fallback a local html file which will also send a Java script message                        
                             // url = "local:///assets/WebViewFallback.html"
                             // TODO: Hande!!!
                             // progressIndicator.opacity = 0.0
                             // nwActivityIndicator.active = false;
                             // nwActivityIndicator.visible = false;
                         }
                     }*/
                     
                     // This is the Navigation-requested signal handler so just print to console to illustrate usage. 
                     onNavigationRequested: {
                         // console.debug ("NavigationRequested: " + request.url);
                         
                         // The URL that the access token is parsed from looks like:
                         // https://www.facebook.com/connect/login_success.html#access_token=CAAGm0PX4...nTopgd&expires_in=5183595
                         // TODO: Handle a faulty login!!
                         var splitted = request.url.toString().split("access_token=");
                         if(splitted.length > 1) {
                             stop(); // Stop loading the page
                             var accesstoken = splitted[1].split("&", 1);
                             
                             console.log("FacebookLoginWebview.qml: Parsed token = " + accesstoken);
                             //nwActivityIndicator.active = false;
                             tinderDataModel.setFacebookAuthToken(accesstoken.toString());
                         }
                     }
                     
                     /*onMessageReceived: {
                         // If not connected to a network the Java script in the fallback page
                         // WebViewFallback.html will send a message to this signal handler
                         // illustrating communication between a Java script and Cascades.
                         console.debug("message.origin: " + message.origin);
                         console.debug("message.data: " + message.data);
                     }   */
                 }
             }
             
             /*NetworkActivity {
                 id: nwActivityIndicator
                 
                 title: "Authorizing with Facebook"
                 horizontalAlignment: HorizontalAlignment.Fill
                 verticalAlignment: VerticalAlignment.Fill
                 
                 onCreationCompleted: {
                     visible = false;
                 }
             }*/
             
             /*Container {
                 bottomPadding: ui.du(2)
                 horizontalAlignment: HorizontalAlignment.Center
                 verticalAlignment: VerticalAlignment.Bottom
                 
                 ProgressIndicator {
                     id: progressIndicator
                     opacity: 0
                 }
             }*/
             
    
         }
     }
 }