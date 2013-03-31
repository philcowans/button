#include <SPI.h>
#include <Ethernet.h>

int ledPin = 3;
int switchPin = 2;
int lastVal = LOW;

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

EthernetClient client;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;) {}
  }

  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);  
  
  client.connect("192.168.1.136", 3333);
}

void loop() {
  int val;
  val = digitalRead(switchPin);
  if(val == LOW) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    if(lastVal != val) {
      Serial.print("Button");
      client.println("Button!");
    }
    digitalWrite(ledPin, LOW);
  }
  lastVal = val;
}
