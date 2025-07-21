#include <KelvinVR.h>

// Initialize Peltiers (EN, IN1, IN2)
KelvinVR peltier1(9, 8, 7);  // Peltier 1 control pins
KelvinVR peltier2(10, 12, 11); // Peltier 2 control pins

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive commands...");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    // Command format: "K1,50" or "K2,-75"
    int peltierNumber = command.substring(1,2).toInt();
    int commaIndex = command.indexOf(',');
    int power = command.substring(commaIndex + 1).toInt();

    if (command.startsWith("K")) {
      switch (peltierNumber) {
        case 1:
          peltier1.setPower(power);
          break;
        case 2:
          peltier2.setPower(power);
          break;
      }
      Serial.print("Peltier ");
      Serial.print(peltierNumber);
      Serial.print(" set to ");
      Serial.println(power);
    }
  }
}