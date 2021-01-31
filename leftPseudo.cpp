//for left foot arduino

//setup

//User stands and sense push button
  //if user pushes button, record standing weight
  //get RSSI data from right to left foot
  //shutoff RSSI
//user sits and sense push button
  //if user pushes button, record sitting weight
//tx sitting and standing calibration DATA

//loop

//wait for user to stand on both feet
  //detect standing weight on both pressure sensors
//if user is standing
  //begin timer (can be done in python)
  //begin RSSI from right to left foot
  //detect walk (function)
    //if left foot no longer has weight
    //sense when left foot detects standing weight
    //stop and record RSSI DATA
    //tx RSSI data to central
    //resume RSSI to right foot

//
