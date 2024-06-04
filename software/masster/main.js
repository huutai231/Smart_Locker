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



var itemChoosen = document.querySelectorAll(".content-row__item");

//  Creat Account
var accountContainer = document.querySelector(".creat-account--container")
itemChoosen[0].addEventListener('click', function() {
     accountContainer.classList += " active"
})

accountContainer.addEventListener('click', function(event) {
     // Kiểm tra xem sự kiện được kích hoạt từ một phần tử con không phải là creat-account
     if (!event.target.classList.contains("creat-account")) {
         accountContainer.classList.remove("active");
     }
});
accountContainer.querySelector('.creat-account').addEventListener('click', function(event) {
     event.stopPropagation();
});

var btnCreatAccount = document.querySelector(".creat-account__confirm")
btnCreatAccount.addEventListener('click', function() {
     let name = document.querySelectorAll(".creat-account__item--input")[0].value
     let phoneNumber = document.querySelectorAll(".creat-account__item--input")[1].value
     let password = document.querySelectorAll(".creat-account__item--input")[2].value

     let ref = firebase.database().ref("/user")
     let data = {
          [phoneNumber]: {
               "pass": password,
               "name": name
          }
     }
     ref.update(data)
     accountContainer.classList.remove("active");
})

// ========================================================================================
//  Đổi mật khẩu
var changePassContainer = document.querySelector(".change-password--container")
itemChoosen[1].addEventListener('click', function() {
     changePassContainer.classList += " active"
})

changePassContainer.addEventListener('click', function(event) {
     // Kiểm tra xem sự kiện được kích hoạt từ một phần tử con không phải là creat-account
     if (!event.target.classList.contains("change-password")) {
          changePassContainer.classList.remove("active");
     }
});
changePassContainer.querySelector('.change-password').addEventListener('click', function(event) {
     event.stopPropagation();
});

var btnChangePass = document.querySelector(".change-password__confirm")
btnChangePass.addEventListener('click', function() {
     let phoneNumber = document.querySelectorAll(".change-password__item--input")[0].value
     let password = document.querySelectorAll(".change-password__item--input")[1].value

     firebase.database().ref(`/user/${phoneNumber}`).update({
          "pass": password  
     })
     changePassContainer.classList.remove("active");
})


// ======================================================================
//  Xóa tài khoản
var deleteAccountContainer = document.querySelector(".delete-account--container")
itemChoosen[2].addEventListener('click', function() {
     deleteAccountContainer.classList += " active"
})

deleteAccountContainer.addEventListener('click', function(event) {
     // Kiểm tra xem sự kiện được kích hoạt từ một phần tử con không phải là creat-account
     if (!event.target.classList.contains("delete-account")) {
          deleteAccountContainer.classList.remove("active");
     }
});
deleteAccountContainer.querySelector('.delete-account').addEventListener('click', function(event) {
     event.stopPropagation();
});
var btnDeleteAccount = document.querySelector(".delete-account__confirm")
btnDeleteAccount.addEventListener('click', function() {
     let phoneNumber = document.querySelectorAll(".delete-account__item--input")[0].value
     firebase.database().ref(`/user/${phoneNumber}`).remove()
     deleteAccountContainer.classList.remove("active");
});


// ================================================================================
//  Danh sách tài khoản
var listAccountContainer = document.querySelector(".list-account--container")
itemChoosen[3].addEventListener('click', function() {
     var phoneUser
     firebase.database().ref("/user").on("value",function(snapshot){
          let data = snapshot.val()   
          phoneUser = Object.keys(data) 
          phoneUser.forEach(function(phone) {
               if (phone !== "admin") {
                    document.querySelector(".list-account").innerHTML += `
                         <div class="list-account__item">
                              <div class="list-account__item__phone">${phone}</div>
                              <div class="list-account__item__name">${data[phone]["name"]}</div>
                         </div>
                    `
               }
          })
     });
     listAccountContainer.classList += " active"
})

listAccountContainer.addEventListener('click', function(event) {
     // Kiểm tra xem sự kiện được kích hoạt từ một phần tử con không phải là creat-account
     if (!event.target.classList.contains("list-account")) {
          listAccountContainer.classList.remove("active");
          document.querySelector(".list-account").innerHTML = `
               <div class="list-account__header">DANH SÁCH TÀI KHOẢN</div>
          `
     }
});
listAccountContainer.querySelector('.list-account').addEventListener('click', function(event) {
     event.stopPropagation();
});


