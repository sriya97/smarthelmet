var express = require('express')

var firebase = require('firebase')


var config = {
    apiKey: "AIzaSyAVL28_y_T55F2rKYddRWV03v4YyKJum6E",
    authDomain: "smart-helmet-app.firebaseapp.com",
    databaseURL: "https://smart-helmet-app.firebaseio.com",
    projectId: "smart-helmet-app",
    storageBucket: "smart-helmet-app.appspot.com",
    messagingSenderId: "912011699557"
  };
  
firebase.initializeApp(config);

const db = firebase.database().ref().child('accident')

var app = express()



app.get('/accident', function (req, res) {
  var timey = new Date() + new Date().getTimezoneOffset()
    res.send('ACCIDENT DETECTED')
    db.set({
        status: 1,
        time: timey
    })
    console.log("Accident detected")
  })

console.log("Server started..")

app.listen(8080)
