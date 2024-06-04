#include <FireBase32.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>

FireBase32::FireBase32(char* URL, char* Key){
  dbURL = URL;
  apiKey = Key;
}
void FireBase32::wifi(char* ssid, char* password){
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  Firebase.begin(dbURL, apiKey);
  delay(50);
  if(Firebase.ready()){
    Serial.println("FireBase is ready!!!");
  } else {
  Serial.println("Error while trying to connect FireBase");
  }
}

//  WriteData  //
void FireBase32::WriteData(String info, char* path){ 
  // Serial.printf("it's a String");
  Firebase.setString(fbdata, path, info); 
}
void FireBase32::WriteData(int info, char* path){ 
  // Serial.printf("it's an int");
  Firebase.setInt(fbdata, path, info);  
}
//  void WriteData(char* info, char* path){ 
//    Serial.printf("it's a char"); 
//    Firebase.setString(fbdata, path, info);
//  }
void FireBase32::WriteData(float info, char* path){ 
  // Serial.printf("it's a float"); 
  Firebase.setFloat(fbdata, path, info);
}
void FireBase32::WriteData(bool info, char* path){ 
  // Serial.printf("it's a bool");
  Firebase.setBool(fbdata, path, info);
}
void FireBase32::WriteData(FirebaseJson info, char* path){ 
  // Serial.printf("it's a FirebaseJson");
  Firebase.setJSON(fbdata, path, info);
}
//  GetData  //
void FireBase32::GetData(char* path, String *dbData){
  if(Firebase.getString(fbdata, path)){
    *dbData = fbdata.stringData();
  }
}
void FireBase32::GetData(char* path, bool *dbData){ 
  if(Firebase.getBool(fbdata, path)){
    *dbData = fbdata.boolData();
  }
}
void FireBase32::GetData(char* path, int *dbData){ 
  if(Firebase.getInt(fbdata, path)){
    *dbData = fbdata.intData();
  }
}
void FireBase32::GetData(char* path, float *dbData){ 
  if(Firebase.getFloat(fbdata, path)){
    *dbData = fbdata.floatData();
  }
}