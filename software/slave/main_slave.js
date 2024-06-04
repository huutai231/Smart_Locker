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

let myPhone = localStorage.getItem('myPhone');


firebase.database().ref(`/user/${myPhone}/name`).on("value",function(snapshot){
     let name = snapshot.val()   
     document.querySelector(".content__header").innerHTML = name   
});


var addLocker
var timeLocker = []

firebase.database().ref(`/user/${myPhone}/using_locker`).on("value",function(snapshot){
     var data = snapshot.val()  
     document.querySelector(".content__list").innerHTML = ""
     addLocker = Object.keys(data)
     addLocker.forEach(function(add) {
          timeLocker.push(data[add]) 
     })
     addLocker.forEach(function(add, i) {
          document.querySelector(".content__list").innerHTML += `
               <div class="content__list__item">
                    <div class="content__list__item__name">${add}</div>
                    <div class="content__list__item__time">${timeLocker[i]}</div>
               </div>
          `
     })
});

var otp_btn = document.querySelector(".otp__confirm")
otp_btn.addEventListener('click', function() {
     while (1) {
          let num1 = Math.floor(Math.random() * 10)
          let num2 = Math.floor(Math.random() * 10)
          let num3 = Math.floor(Math.random() * 10)
          let num4 = Math.floor(Math.random() * 10)
          let num = num1*1000 + num2*100 + num3*10 + num4
          let otp
          let check = 1
          firebase.database().ref("/otp").on("value",function(snapshot){
               let data = snapshot.val()   
               otp = Object.keys(data)
               otp.forEach(function(e) {
                    if (e == num) {
                         check = 0
                    }
               })
          });
          if (check == 1) {
               let otp_value = document.querySelectorAll(".otp__number")
               otp_value[0].innerHTML = num1
               otp_value[1].innerHTML = num2
               otp_value[2].innerHTML = num3
               otp_value[3].innerHTML = num4
               firebase.database().ref("/otp").update({
                    [num]: myPhone 
               })
               break;
          }
     }
})
