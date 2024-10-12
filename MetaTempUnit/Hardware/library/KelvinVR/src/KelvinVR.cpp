/*
  KelvinVR Mk1-Alpha test module: Arduino Mega Original 2560
  Main class for KelvinVR Library

  Arduino Mega 2560
  ___________________
   |  ___________  USB |
   | |           |     |
   | |           |     |
   | |           |     |
   | |           |     |
   | |___________|     |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
 --+---+---+---+---+---+---+---+---+---+---+---+
   | D | D | D | D | D | D | . | . | . | . | D |
   | 8 | 9 | 1 | 1 | 1 | 1 |   |   |   |   | 3 |
   |   |   | 0 | 1 | 2 | 3 |   |   |   |   | 7 |
 --+---+---+---+---+---+---+---+---+---+---+---+
   |   |   |   |   |   |               |
   |   |   |   |   |   |               |
   |   |   |   |   |   |               |
   |   |   |   |   |   |               Buzzer
   |   |   |   |   |   |
   |   |   |   |   |   +-- Not used
   |   |   |   |   |
   |   |   |   |   +-- Not used
   |   |   |   |
   |   |   |   +-- Red LED
   |   |   |
   |   |   +-- Green LED
   |   |
   |   +-- LED+ (Fading LED Blue)
   |
   +-- LED- (Fading LED Blue)

Note: Pins 9, 10, and 11 support PWM for LED brightness control



*/

#include <Arduino.h>
#include "KelvinVR.h"

Kelvin::Kelvin(const String &modelName)
{
  _modelName = modelName;
}

void Kelvin::begin(unsigned long baudRate = DEFAULT_BAUD_RATE)
{
  Serial.begin(baudRate);
  fullPinSetup();

  Serial.println("");
  Serial.println("KelvinVR Mk1-Alpha ready to receive commands.");
  Serial.println("Type 'HELP' for a list of available commands.");
  Serial.println("");
}

void Kelvin::fullPinSetup()
{
  // Setup Peltier control pins
  pinMode(PIN_PELTIER_ENABLE, OUTPUT);
  pinMode(PIN_PELTIER_IN1, OUTPUT);
  pinMode(PIN_PELTIER_IN2, OUTPUT);

  // Setup LED pins
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_BLUE_MINUS, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // For two-pins LED:
  digitalWrite(PIN_LED_BLUE_MINUS, LOW);

  // Initially stop the Peltier
  stopThermalControl();
}

void Kelvin::startCooling(uint8_t intensity)
{
  analogWrite(PIN_PELTIER_ENABLE, intensity);
  digitalWrite(PIN_PELTIER_IN1, HIGH);
  digitalWrite(PIN_PELTIER_IN2, LOW);

  // Set info:
  _isCooling = true;
  _currentIntensity = intensity;
}

void Kelvin::startHeating(uint8_t intensity)
{
  analogWrite(PIN_PELTIER_ENABLE, intensity);
  digitalWrite(PIN_PELTIER_IN1, LOW);
  digitalWrite(PIN_PELTIER_IN2, HIGH);

  // Set info:
  _isCooling = false;
  _currentIntensity = intensity;
}

void Kelvin::stopCooling()
{
  digitalWrite(PIN_PELTIER_ENABLE, LOW);
  digitalWrite(PIN_PELTIER_IN1, LOW);
  digitalWrite(PIN_PELTIER_IN2, LOW);
}

void Kelvin::stopHeating()
{
  digitalWrite(PIN_PELTIER_ENABLE, LOW);
  digitalWrite(PIN_PELTIER_IN1, LOW);
  digitalWrite(PIN_PELTIER_IN2, LOW);
}

void Kelvin::stopThermalControl()
{
  digitalWrite(PIN_PELTIER_ENABLE, LOW);
  digitalWrite(PIN_PELTIER_IN1, LOW);
  digitalWrite(PIN_PELTIER_IN2, LOW);
}

void Kelvin::blinkLed(int ledPin)
{
  digitalWrite(ledPin, HIGH);
  delay(DEFAULT_BLINK_TIME);
  digitalWrite(ledPin, LOW);
  delay(DEFAULT_BLINK_TIME);
}

void Kelvin::fadeEffect(uint8_t led)
{
  // set the brightness of pin 9:
  analogWrite(led, _brightness);

  // change the brightness for next time through the loop:
  _brightness = _brightness + _fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (_brightness <= MIN_BRIGHTNESS || _brightness >= MAX_BRIGHTNESS)
  {
    _fadeAmount = -_fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(FADE_DELAY_TIME);
}

void Kelvin::ledOn()
{
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_BLUE_MINUS, LOW);
  _ledState = true;
}

void Kelvin::ledOff()
{
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_BLUE_MINUS, LOW);
  _fadeAmount = -_fadeAmount;
}

void Kelvin::blinkFront(int delayTime)
{
  digitalWrite(PIN_LED_BLUE, HIGH);
  delay(delayTime);
  digitalWrite(PIN_LED_BLUE, LOW);
  delay(delayTime);
}

void Kelvin::runThermalCycle(bool isCooling, uint8_t intensity, int durationSeconds)
{

  if (_cycleInProgress)
  {
    Serial.println("Error: A cycle is already in progress");
    return;
  }

  _cycleInProgress = true;

  unsigned long startTime = millis();
  unsigned long lastPrintTime = 0;
  int secondsElapsed = 0;

  while (millis() - startTime < durationSeconds * 1000UL && _cycleInProgress)
  {
    // Check for new commands
    if (Serial.available())
    {
      String command = Serial.readStringUntil('\n');
      processCommand(command);
    }

    // Print status every second
    if (millis() - lastPrintTime >= 1000)
    {
      secondsElapsed++;
      Serial.print(isCooling ? "Cooling: " : "Heating: ");
      Serial.print(secondsElapsed);
      Serial.println(" seconds");
      lastPrintTime = millis();
    }
  }

  stopThermalControl();
  _cycleInProgress = false;
  Serial.println(_cycleInProgress ? "Thermal cycle interrupted" : "Thermal cycle completed");
}

/*
Simple string hash function

Key points about the algorithm:

1. It starts with an initial value of 5381.
2. For each character in the input string, it:
   - Multiplies the current hash value by 33 (which is 2^5 + 1)
   - Adds the ASCII value of the current character
3. The multiplication by 33 is typically implemented as `(hash << 5) + hash` for efficiency.

*/
constexpr unsigned int hash(const char *str, int h = 0)
{
  return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
}

void Kelvin::sendStatus()
{
  Serial.println("KelvinVR Status:");
  Serial.println("----------------");
  Serial.print("Model: ");
  Serial.println(_modelName);
  Serial.print("Thermal State: ");
  if (_isCooling)
  {
    Serial.println("Cooling");
  }
  else if (_isHeating)
  {
    Serial.println("Heating");
  }
  else
  {
    Serial.println("Idle");
  }
  Serial.print("Current Intensity: ");
  Serial.println(_currentIntensity);
  Serial.print("LED State: ");
  Serial.println(_ledState ? "ON" : "OFF");
  Serial.println("----------------");
}

void Kelvin::printHelp()
{
  Serial.println("Available commands:");
  Serial.println("  COOL [intensity] - Start cooling (intensity 0-255, default 255)");
  Serial.println("  HEAT [intensity] - Start heating (intensity 0-255, default 255)");
  Serial.println("  STOP - Stop thermal control");
  Serial.println("  CYCLE <COOL|HEAT> <intensity> <duration> - Run a thermal cycle");
  Serial.println("  STATUS - Get current status");
  Serial.println("  STOPCOOL - Stop cooling");
  Serial.println("  STOPHEAT - Stop heating");
  Serial.println("  LED ON - Turn LED on");
  Serial.println("  LED OFF - Turn LED off");
  Serial.println("  LED BLINK [delay] - Blink LED (delay in ms, default 1000)");
  Serial.println("  LED FADE BLUE - Fade blue LED");
  Serial.println("  LED FADE GREEN - Fade green LED");
  Serial.println("  LED FADE RED - Fade red LED");
}

void Kelvin::ledAction(const String &command)
{
  // Extract the LED sub-command
  String ledCommand = command.substring(4); // Remove "LED " prefix

  // Use a helper function to generate a simple hash for string comparison
  switch (hash(ledCommand.c_str()))
  {
  case hash("ON"):
    ledOn();
    Serial.println("LED turned on");
    break;

  case hash("OFF"):
    ledOff();
    Serial.println("LED turned off");
    break;

  case hash("BLINK"):
  {
    int delay = DEFAULT_BLINK_TIME;
    if (ledCommand.length() > 6) // "BLINK " is 6 characters
    {
      delay = ledCommand.substring(6).toInt();
    }
    blinkFront(delay);
    Serial.println("LED blinking");
    break;
  }

  case hash("FADE BLUE"):
    fadeEffect(PIN_LED_BLUE);
    Serial.println("LED fading BLUE");
    break;

  case hash("FADE GREEN"):
    fadeEffect(PIN_LED_GREEN);
    Serial.println("LED fading GREEN");
    break;

  case hash("FADE RED"):
    fadeEffect(PIN_LED_RED);
    Serial.println("LED fading RED");
    break;

  default:
    Serial.println("Unknown LED command");
    break;
  }
}

void Kelvin::runFirmware()
{
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.length() > 0)
    {
      // Stop the current command if one is running
      stopCommand();
      // Execute the new command
      processCommand(command);
    }
  }

  // Continue executing the current command if one is active
  if (_currentCommand.length() > 0)
  {
    executeCommand(_currentCommand);
  }
}

void Kelvin::processCommand(const String &command)
{
  _currentCommand = command;
  Serial.print("Executing command: ");
  Serial.println(_currentCommand);
  // Initial setup for the command, if needed
  if (_currentCommand.startsWith("COOL"))
  {
    int intensity = _currentCommand.substring(5).toInt();
    startCooling(intensity);
  }
  else if (_currentCommand.startsWith("HEAT"))
  {
    int intensity = _currentCommand.substring(5).toInt();
    startHeating(intensity);
  }
  else if (_currentCommand == "STOP")
  {
    stopThermalControl();
    _currentCommand = ""; // Clear the current command
  }
  else if (_currentCommand.startsWith("LED"))
  {
    bool on = (_currentCommand.substring(4) == "ON");
    ledAction(on ? "on" : "off");
    _currentCommand = ""; // Clear the current command as LED action is immediate
  }
  else
  {
    Serial.println("Unknown command");
    _currentCommand = ""; // Clear the current command
  }
}

void Kelvin::stopCommand()
{
  if (_currentCommand.length() > 0)
  {
    if (_currentCommand.startsWith("COOL") || _currentCommand.startsWith("HEAT"))
    {
      stopThermalControl();
    }
    // Add other command stop logic here if needed
    Serial.println("Stopped previous command: " + _currentCommand);
    _currentCommand = "";
  }
}

void Kelvin::executeCommand(const String &command)
{
  String cmd = command;
  cmd.trim();
  cmd.toUpperCase();

  if (cmd == "HELP" || cmd == "HLP")
  {
    printHelp();
  }
  else if (cmd.startsWith("COOL ") || cmd.startsWith("CL "))
  {
    int intensity = cmd.substring(cmd.indexOf(' ') + 1).toInt();
    intensity = intensity == 0 ? 255 : intensity;
    startCooling(intensity);
  }
  else if (cmd.startsWith("HEAT ") || cmd.startsWith("HT "))
  {
    int intensity = cmd.substring(cmd.indexOf(' ') + 1).toInt();
    intensity = intensity == 0 ? 255 : intensity;
    startHeating(intensity);
  }
  else if (cmd == "STOP" || cmd == "STP")
  {
    stopThermalControl();
  }
  else if (cmd.startsWith("CYCLE ") || cmd.startsWith("CY "))
  {
    bool isCooling = cmd.endsWith("COOL") || cmd.endsWith("CL");
    runThermalCycle(isCooling, 255, 30000); // Default intensity and duration
  }
  else if (cmd == "STATUS" || cmd == "STS")
  {
    sendStatus();
  }
  else if (cmd == "STOPCOOL" || cmd == "STP CL")
  {
    stopCooling();
  }
  else if (cmd == "STOPHEAT" || cmd == "STP HT")
  {
    stopHeating();
  }
  else if (cmd == "LED ON" || cmd == "LD ON")
  {
    ledOn();
  }
  else if (cmd == "LED OFF" || cmd == "LD OFF")
  {
    ledOff();
  }
  else if (cmd.startsWith("LED BLINK ") || cmd.startsWith("LD BLK "))
  {
    int delayTime = cmd.substring(cmd.lastIndexOf(' ') + 1).toInt();
    delayTime = delayTime == 0 ? 1000 : delayTime;
    blinkFront(delayTime);
  }
  else if (cmd == "LED FADE BLUE" || cmd == "LD FDE B")
  {
    fadeEffect(PIN_LED_BLUE);
  }
  else if (cmd == "LED FADE GREEN" || cmd == "LD FDE G")
  {
    fadeEffect(PIN_LED_GREEN);
  }
  else if (cmd == "LED FADE RED" || cmd == "LD FDE R")
  {
    fadeEffect(PIN_LED_RED);
  }
  else
  {
    Serial.println("Unknown command");
  }
}

void Kelvin::continueHeating(uint8_t intensity)
{
  // Check if heating should continue
  if (_isCooling || _currentIntensity == 0)
  {
    Serial.println("Heating stopped.");
    _currentCommand = ""; // Clear the current command
    return;
  }

  // Apply heating
  analogWrite(PIN_PELTIER_ENABLE, intensity);
  digitalWrite(PIN_PELTIER_IN1, LOW);
  digitalWrite(PIN_PELTIER_IN2, HIGH);

  // Update info:
  _currentIntensity = intensity;

  // Print status update
  // Serial.println("Heating - Intensity: " + String(intensity));
}

void Kelvin::continueCooling(uint8_t intensity)
{
  // Check if cooling should continue
  if (!_isCooling || _currentIntensity == 0)
  {
    Serial.println("Cooling stopped.");
    _currentCommand = ""; // Clear the current command
    return;
  }

  // Apply cooling
  analogWrite(PIN_PELTIER_ENABLE, intensity);
  digitalWrite(PIN_PELTIER_IN1, HIGH);
  digitalWrite(PIN_PELTIER_IN2, LOW);

  // Update info:
  _currentIntensity = intensity;

  // Print status update
  // Serial.println("Cooling - Intensity: " + String(intensity));
}
