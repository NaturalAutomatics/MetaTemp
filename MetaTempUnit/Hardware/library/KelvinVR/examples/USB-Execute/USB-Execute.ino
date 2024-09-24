#include "Kelvin.h"

Kelvin kelvin("Mk1-Alpha"); // Create a Kelvin object with a model name

void setup()
{
    Serial.begin(9600);    // Initialize serial communication at 9600 baud
    kelvin.begin();        // Initialize the Kelvin object
    kelvin.fullPinSetup(); // Set up all pins for the Kelvin device

    Serial.println("KelvinVR Mk1-Alpha ready to receive commands.");
    Serial.println("Type 'HELP' for a list of available commands.");
}

void loop()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n'); // Read the incoming command
        command.trim();                                // Remove any leading or trailing whitespace

        if (command.length() > 0)
        {
            if (command.equalsIgnoreCase("HELP"))
            {
                printHelp();
            }
            else
            {
                kelvin.processCommand(command); // Process the command using the Kelvin object
            }
        }
    }

    // You can add any other continuous operations here if needed
}

void printHelp()
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
