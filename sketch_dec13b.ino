int led = 5;     // LED pin
int button = 16; // push button is connected
int temp = 0;    // temporary variable for reading the button pin status

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
                          
#define FIREBASE_HOST "smart-doorbell-96925-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "qOQuQ8umMP0SqoGGec6mJorQHUYOrbQlYWVQ7mLF" //Your Firebase Database Secret goes here

#define WIFI_SSID "Trojan Hax"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "DDNSS@8#"                                      //Password of your wifi network 
 
  

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;
bool val = false;


void setup() {

  Serial.begin(115200);  // Select the same baud rate if you want to see the datas on Serial Monitor


  pinMode(LED_BUILTIN, OUTPUT);   // declare LED as output
  pinMode(button, INPUT); // declare push button as input
  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() { 

// Firebase Error Handling And Writing Data At Specifed Path************************************************

 if (Firebase.getBool(firebaseData,"/data")) {

      val = firebaseData.boolData();
      Serial.print("Val = ");
               Serial.println(val);
    }

   else {
    Serial.println(firebaseData.errorReason());
  }

 temp = digitalRead(button);

Serial.print("Val = ");
               Serial.println(val);
   if (temp == HIGH && !val) {
        digitalWrite(LED_BUILTIN, HIGH);
     //   Serial.println("LED Turned ON");

           val = !val;
      if (Firebase.setBool(firebaseData, "/data", val)) {    // On successful Write operation, function returns 1  
               Serial.println("Value Uploaded Successfully");
               Serial.print("Val = ");
               Serial.println(val);
               Serial.println("\n");
              
            //   delay(60000);

     }

else {        
    Serial.println(firebaseData.errorReason());
  }

   
    

   }
}


/* NOTE:
 *  To upload value, command is ===> Firebase.setInt(firebaseData, "path", variable);
 *  Example                     ===>  Firebase.setInt(firebaseData, "/data", val);
 */
