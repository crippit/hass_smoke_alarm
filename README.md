# hass_smoke_alarm

This is a project designed to send an alert to Home-Assistant via MQTT from a ESP8266 D1 mini. 

Power is provided to the ESP8266 using a Kidde SM120x Relay connected to 120v interconnected smoke alarms. This powers up the ESP8266 when the smoke alarm sounds, then triggering an alert to be sent to Home Assistant.

What you're going to need:

- Smoke Alarm Relay (I'm using the Kidde SM120X as I have Kidde Interconnected Smoke Alarms)
- A ESP8266 board (I'm using the Wemos D1 Mini)
- A USB Charger
- A Micro USB Cable
- Either a 120V power Outlet, or an extension cord

Steps:

1. Wire the relay into the Smoke Alarm circuit. You want to use the Normally Open to connect to the power outlet
2. Wire your outlet into the relay and back into the neutral of your circuit
3. Program your ESP8266 using the code here (making sure to update some info - see below)
4. Plug the ESP8266 into the USB Charger

When the alarm sounds the realy will switch the 120v supply onto the charger, powering up the ESP8266 and broadcasting a message via MQTT.


