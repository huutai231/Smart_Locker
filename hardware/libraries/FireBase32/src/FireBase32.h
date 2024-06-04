#ifndef FireBase32_h
#define FireBase32_h

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>


class FireBase32{
  private:
    char* dbURL;
    char* apiKey;
    FirebaseData fbdata;
    FirebaseJson json;

    //  FirebaseData fbdataInt;
    //  FirebaseData fbdataChar;
    //  FirebaseData fbdataString;
    //  FirebaseData fbdataBool;
    //  FirebaseData fbdataDouble;
    //  FirebaseData fbdataFloat;
  public:

    FireBase32(char* URL, char* Key);
    wifi(char* ssid, char* password);
    WriteData(String info, char* path);
    WriteData(int info, char* path);
    WriteData(float info, char* path);
    WriteData(bool info, char* path);
    WriteData(FirebaseJson info, char* path);
    GetData(char* path, String *dbData);
    GetData(char* path, bool *dbData);
    GetData(char* path, int *dbData);
    GetData(char* path, float *dbData);

};


#endif
