#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup()
{
  //LCD setup
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0); //第一列 第四行（格）
  lcd.print("Good morning ");
  lcd.setCursor(2,1); //第二列 第三行（格）
  lcd.print("Door Security");
  lcd.setCursor(0,2); //第三列 第二行（格）
  lcd.print("Door Bell");
  lcd.setCursor(2,3); //第四列 第三行（格）
  lcd.print("Power By Ec-yuan!");

  //MERC setup
  Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(7,OUTPUT);
}


void loop()
{
// Look for new cards
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
//Show UID on serial monitor
Serial.print("UID tag :");

String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print("Message : ");
content.toUpperCase();


if (content.substring(1) == "03 54 25 97") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access");
Serial.println();

lcd.setCursor(3,0);
lcd.print("Welcome back,");
lcd.setCursor(2,1);
lcd.print("Charlotte!");

delay(3000);
}
else if (content.substring(1) == "93 6C 3D 05") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access");
Serial.println();

lcd.setCursor(3,0);
lcd.print("Welcome back, ");
lcd.setCursor(2,1);
lcd.print("Sandy! Have a nice day !");

delay(3000);
}
else if (content.substring(1) == "75 2E 22 38") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access");
Serial.println();

lcd.setCursor(3,0);
lcd.print("Welcome back, ");
lcd.setCursor(2,1);
lcd.print("Eileen! Have a nice day !");

delay(3000);
}
else {
Serial.println(" Access denied");

lcd.setCursor(3,0);
lcd.print("Leave or I'll ");
lcd.setCursor(2,1);
lcd.print("call the police.");

delay(3000);
}
}
