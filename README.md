# hass_smoke_alarm

This is a project designed to send an alert to Home-Assistant via MQTT from a ESP8266 D1 mini. 

Power is provided to the ESP8266 using a Kidde SM120x Relay connected to 120v interconnected smoke alarms. This powers up the ESP8266 when the smoke alarm sounds, then triggering an alert to be sent to Home Assistant.
