#include <Keypad.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/RTDBHelper.h>
#include "RTClib.h"

RTC_DS1307 rtc;

const char* ssid = "Điện thoại của Khoa";
const char* password = "123456789";
// Thông tin Firebase
#define DATABASE_URL "hw-sw-project-6eb09-default-rtdb.firebaseio.com"

// Tạo đối tượng FirebaseData
FirebaseData firebase;
FirebaseAuth auth;
FirebaseConfig config;

// =====================================================
Servo myservo;
LiquidCrystal_I2C lcd (0x27, 20,2);

Servo myservoA;
Servo myservoB;
Servo myservoC;

#define servoA 27
#define servoB 33
#define servoC 32
#define button_khach 4
#define button_shipper 2

char customKey;
const byte ROWS = 4;
const byte COLS = 4;
String num_string;
String num_string2;
String code;
String name;
String phone;
int shipper_mode;
int khach_mode;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {23, 25, 3, 26};
byte colPins[COLS] = {19, 18, 5, 17};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void readKeypad1();
void readKeypad2();
void openA();
void closeA();
void openB();
void closeB();
void openC();
void closeC();



void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    config.database_url = DATABASE_URL;
    config.signer.test_mode = true;
    Firebase.reconnectWiFi(true);
    Firebase.begin(&config, &auth);

    if (Firebase.ready()) {
      Serial.println("Connected to Firebase");
    } else {
      Serial.println("Failed to connect to Firebase");
    }


    pinMode(button_khach, INPUT);
    pinMode(button_shipper, INPUT);
    myservoA.attach(servoA);
    myservoA.write(180);
    myservoB.attach(servoB);
    myservoB.write(180);
    myservoC.attach(servoC);
    myservoC.write(180);
    lcd.init();                      // initialize the lcd 
    lcd.init();
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0,0);
    shipper_mode = 0;
    khach_mode = 0;

    
    //-----------------------------------------------RTC------------------------------------//
    #ifndef ESP8266
      while (!Serial); // wait for serial port to connect. Needed for native USB
    #endif

    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1) delay(10);
    }

    if (! rtc.isrunning()) {
      Serial.println("RTC is NOT running, let's set the time!");
      // When time needs to be set on a new device, or after a power loss, the
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(2024, 3, 23, 8, 55, 0));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
    
}
//----------------------------------------------------------------------Loop----------------------------------------------------------//
void loop() {
  DateTime now = rtc.now();
  //rtc.adjust(DateTime(2024, 5, 16, 23, 59, 0));
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  int button_khach_value = digitalRead(button_khach);
  int button_shipper_value = digitalRead(button_shipper);
  
  if(button_shipper_value)
  {
    shipper_mode = 1;
    khach_mode = 0;
  }
  if(button_khach_value)
  {
    khach_mode = 1;
    shipper_mode = 0;
  }
  if(khach_mode)
  {
    readKeypad1();
    lcd.setCursor(0,0);
    lcd.print(num_string);
  }
  if(shipper_mode)
  {
    readKeypad2();
    lcd.setCursor(0,0);
    lcd.print(num_string2);
  }
  delay(100);
  Serial.print("Shipper_mode: ");
  Serial.println(shipper_mode);
  Serial.print("Khach_mode: ");
  Serial.println(khach_mode);
}
//------------------------------------------------------------------------------------------------------------------------------------//



void readKeypad1()
{
  int ok;
  char customKey = customKeypad.getKey();
  if(customKey != 'D' && customKey != '#')
  {
    String num_le = String(customKey);
    num_string += num_le;
  }
  if(customKey == '#')
  {
    num_string = "";
    lcd.clear();
    delay(500);
  }


  if(customKey == 'D')
  {

    // Đọc chuỗi từ Firebase
    String refPhone = "/otp/";
    refPhone += num_string;
    String myPhone = "";
    if (Firebase.getString(firebase, refPhone)) {
      myPhone = firebase.stringData();
    }
    String refDoor = "/user/";
    refDoor += myPhone;
    refDoor += "/using_locker";
    String result[10];
    int n = 0;
    if (Firebase.getString(firebase, refDoor)) {
      String dataInf = firebase.stringData();
      if (dataInf.length() != 0) {
        result[n] = dataInf.substring(2, 3);
        n = 1;
        for (int i = 0; i < dataInf.length()-2; i++) {
          if (dataInf[i] == ',') {
            result[n] = dataInf.substring(i+2, i+3);
            n++;
          }
        }
      }
        
      for (int i = 0; i < n; i++) {
        Serial.println(result[i]);
        if (result[i] == "A") {
            openA();
        }
        if (result[i] == "B") {
            openB();
        }
        if (result[i] == "C") {
            openC();
        }
      }

      if (Firebase.deleteNode(firebase, refDoor)) {
        Serial.println("Node deleted successfully");
      }
    }
  }
}
void readKeypad2()
{
  
  char customKey2 = customKeypad.getKey();
  if(customKey2 != 'D' && customKey2 != '#' && customKey2 != '*')
  {
    String num_le2 = String(customKey2);
    num_string2 += num_le2;
  }
  if(customKey2 == '#')
  {
    num_string2 = "";
    lcd.clear();
    delay(500);
  }
  if(customKey2 == 'D')
  {
    code = num_string2;
    name = code.substring(0, 1);
    phone = code.substring(1);
    Serial.println(name);
    Serial.println(phone);
    String ref = "";
    ref += "/user/";
    ref += phone;
    ref += "/using_locker/";
    ref += name;
    DateTime now = rtc.now();
    int year = now.year();
    int month = now.month();
    int day = now.day();
    int hour = now.hour();
    int minute = now.minute();
    int second = now.second();
    
    String datetime = String(day) + "/" + String(month) + "/" + String(year) + " " + String(hour) + ":" + String(minute) + ":" + String(second);

    if (Firebase.setString(firebase,  ref, datetime)) {
      Serial.println("Key added successfully");
    }

    if (name == "A") {
      closeA();
    } 
    if (name == "B") {
      closeB();
    }   
    if (name == "C") {
          closeC();
    }
    
  }

}
void openA(){
  myservoA.write(180);
  int goc = myservoA.read();
  Serial.println(goc);
  delay(500);
}
void closeA(){
  myservoA.write(90);
  int goc = myservoA.read();
  Serial.println(goc);
  delay(500);
}
void openB(){
  myservoB.write(180);
  int goc = myservoB.read();
  Serial.println(goc);
  delay(500);
}
void closeB(){
  myservoB.write(90);
  int goc = myservoB.read();
  Serial.println(goc);
  delay(500);
}
void openC(){
  myservoC.write(180);
  int goc = myservoC.read();
  Serial.println(goc);
  delay(500);
}
void closeC(){
  myservoC.write(90);
  int goc = myservoC.read();
  Serial.println(goc);
  delay(500);
}
