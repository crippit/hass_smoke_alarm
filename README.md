# hass_smoke_alarm

This is a project designed to send an alert to Home-Assistant via MQTT from a ESP8266 D1 mini. 

Power is provided to the ESP8266 using a Kidde SM120x Relay connected to 120v interconnected smoke alarms. This powers up the ESP8266 when the smoke alarm sounds, then triggering an alert to be sent to Home Assistant. I used a moulded extension cord as my power outlet wired into the circuit using Marettes.

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
5. In Home Assistant Configuration.yaml you will need to add the following SENSOR:
      #Fire
      - platform: mqtt
        name: Smoke Alarm
        state_topic: home-assistant/security/smoke_alarm
        unit_of_measurement: "Fire"
        
When the alarm sounds the realy will switch the 120v supply onto the charger, powering up the ESP8266 and broadcasting a message via MQTT.

----------------

Customising the Configuration

1. #define WLAN_SSID                 "xxx"
You will need to put the SSID of your WiFi that you want the board to connect to here

2. #define WLAN_PASS                 "xxx"
Enter the Password of the WiFi

3. const char* mqtt_server           = "192.168.0.x";
Choose the IP address of you MQTT Server, for me this was my Home Assistant Install, but it may be different if you're using a cloud based service

4. #define MQTT_PORT                 1883
This is the port for MQTT to connect via

5. String MQTT_CLIENT_NAME           = "home-assistant";
This is the name of the MQTT Client that you installed

6. #define MQTT_USER                 "xxx"
The username of MQTT install

7. #define MQTT_PASS                 "xxx"
The password of the MQTT install

8. String    fire_topic              = "home-assistant/security/smoke_alarm";
You can edit the topic here, however you need to ensure that this topic is matched in cofniguration.yaml


-------------------------
Uploading the File to the ESP8266 (Wemos D1 Mini)

I used the Arduino editor and uploaded from the application, you will need to make sure that you have added all of the libraries which are identified in the top of the file. You can do this by going to Sketch > Include Libraries > Manage Libraries and searching for the library that you require. You will also need to ensure that you have added the ESP8266 board in the Arduino Application Peferences under "Additional Boards Manager" using the URL: http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json 
