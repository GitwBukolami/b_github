#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

#define BLYNK_TEMPLATE_ID "TMPL2wEywxXvc"
#define BLYNK_TEMPLATE_NAME "IoT Gas Level Indicator"
#define BLYNK_AUTH_TOKEN "jkcBLPSAMR4_zCxxnKEBD14DJECbR2_Y"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Pin definitions
#define HX711_DT 33  // HX711 data pin
#define HX711_SCK 32 // HX711 clock pin
#define I2C_SDA 21   // ESP32 I2C SDA pin
#define I2C_SCL 22   // ESP32 I2C SCL pin

// Initialize LCD and HX711
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address if needed
HX711 scale;

#define BLYNK_PRINT Serial
char auth[] = BLYNK_AUTH_TOKEN;
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Love";
char pass[] = "12345678";


void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize LCD
  lcd.begin();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();


  // Initialize HX711
  scale.begin(HX711_DT, HX711_SCK);

  // Wait for scale to stabilize
  delay(1000);


  if (scale.is_ready()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GROUP A ELE 391");
    lcd.setCursor(0, 1);
    lcd.print("2024/2025");
    delay(2000);
    lcd.clear();
    lcd.print("Scale Ready");
    delay(2000);
    lcd.clear();
    scale.set_scale(-110); // Calibration factor placeholder
    scale.tare();      // Reset scale to 0
  } 
    /*else {
    lcd.clear();
    lcd.print("Scale Error");
    Serial.println("HX711 not found. Check wiring.");
    while (1); // Halt
  }*/
    Blynk.begin(auth, ssid, pass);

}

void loop() {

  Blynk.run();

  if (scale.is_ready()) {
    float weight = scale.get_units(1); // Average of 5 readings
    lcd.setCursor(0, 0);
    lcd.print("Weight:");

    lcd.setCursor(0, 1);
    lcd.print(weight, 2); // Print weight with 2 decimal places
    
    float reading;
    //lcd.print(reading);
    lcd.print(" g");                 // Print the unit
    
    Serial.print("Weight: ");
    //Serial.print(reading);
    //Serial.println(" grams");

    
  Blynk.virtualWrite(V0,weight);
  Blynk.virtualWrite(V1,weight);

  } 
   /*else {
    lcd.setCursor(0, 0);
    lcd.print("Scale Error");
    Serial.println("HX711 not found. Check wiring.");
  } */


  delay(5000);
}
