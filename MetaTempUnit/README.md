# KelvinVR Library - USB Command Reference

This document outlines the USB commands available for controlling devices using the KelvinVR Library.

## Thermal Control Commands

### Start Cooling
- Command: `COOL [intensity]`
- Example: `COOL 200` (starts cooling at intensity 200)
- Default: `COOL` (uses default intensity of 255)

### Start Heating
- Command: `HEAT [intensity]`
- Example: `HEAT 180` (starts heating at intensity 180)
- Default: `HEAT` (uses default intensity of 255)

### Stop Thermal Control
- Command: `STOP`

### Run Thermal Cycle
- Command: `CYCLE <COOL|HEAT> <intensity> <duration>`
- Example: `CYCLE COOL 200 30` (runs a cooling cycle at intensity 200 for 30 seconds)
- Example: `CYCLE HEAT 180 45` (runs a heating cycle at intensity 180 for 45 seconds)

### Stop Cooling
- Command: `STOPCOOL`

### Stop Heating
- Command: `STOPHEAT`

## LED Control Commands

### Turn LED On
- Command: `LED ON`

### Turn LED Off
- Command: `LED OFF`

### Blink LED
- Command: `LED BLINK <delay>`
- Example: `LED BLINK 500` (blinks the LED with a 500ms delay)

### Fade LED
- Command: `LED FADE`

## Notes
- Replace `[intensity]` with a value between 0-255 to set the intensity of heating or cooling.
- For the `CYCLE` command, `<duration>` is specified in seconds.
- All commands are case-sensitive.

For more detailed information on using these commands, please refer to the KelvinVR Library documentation.
