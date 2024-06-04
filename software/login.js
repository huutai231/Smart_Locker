const firebaseConfig = {
     apiKey: "AIzaSyDE7vWgQe8F9tnaeQDX_8Djd0GZrgyVMqI",
     authDomain: "hw-sw-project-6eb09.firebaseapp.com",
     databaseURL: "https://hw-sw-project-6eb09-default-rtdb.firebaseio.com",
     projectId: "hw-sw-project-6eb09",
     storageBucket: "hw-sw-project-6eb09.appspot.com",
     messagingSenderId: "508982003459",
     appId: "1:508982003459:web:ed1c52787a1fc9ab760b36",
     measurementId: "G-QTWWV67X0R"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);



var phoneData
var passData = []

firebase.database().ref("/user").on("value",function(snapshot){
     var data = snapshot.val()   
     phoneData = Object.keys(data) 
     phoneData.forEach(function(phone) {
          passData.push(data[phone]["pass"])
     })
});


var btn = document.querySelector(".log-in__boder__confirm--btn");

btn.addEventListener('click', function() {
     let phone = document.querySelector(".log-in__boder__name--input").value
     let pass = document.querySelector(".log-in__boder__pass--input").value
     let isValid = false
     phoneData.forEach(function(p, i) {     
          if (p === phone) {
               if (passData[i] === pass) {
                    isValid = true
                    if (p === "admin") {
                         window.open("./masster/index.html")
                         return
                    }
                    else {
                         localStorage.setItem('myPhone', phone);
                         console.log(phone)
                         window.open("./slave/index_slave.html");
                         return
                    }
               }
          }
     })
     if (isValid == false) {
          btnErrorPass.classList += " active"
     }
     
})


var btnErrorPass = document.querySelector(".error-pass")
btnErrorPass.addEventListener('click', function() {
     btnErrorPass.classList.remove("active") 
})

