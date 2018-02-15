#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/************************* WiFi and MQTT Config *********************************/
#define WLAN_SSID                 "xxx"
#define WLAN_PASS                 "xxx"
const char* mqtt_server           = "192.168.0.x";
#define MQTT_PORT                 1883
String MQTT_CLIENT_NAME           = "home-assistant";
#define MQTT_USER                 "xxx"
#define MQTT_PASS                 "xxx"

/*************************    Configuration     *********************************/
#define DEBUG                     true


/*************************     Sensor Vars     *********************************/
boolean   fire_state_changed      = false;
boolean   fire_switch_closed      = false;
long      fire_last_triggered     = 0;
short     fire_trigger_threshold  = 100;
short     fire_publish_interval   = 10 * 60 * 5; // Every 5 min
short     fire_loop_count         = fire_publish_interval; // Publish immediatley
String    fire_topic              = "security/smoke_alarm" + MQTT_CLIENT_NAME;

/*************************     Global Vars     *********************************/
WiFiClient                      esp_client;
PubSubClient                    mqtt_client(esp_client);

void setup() {
  #if DEBUG == true
    Serial.begin(9600);
  #endif
  
  // Setup WiFi connection & connect to MQTT server
  waitForWiFiConnection();
  connectMqtt();
}

void loop(){
  // Ensure that the MQTT mqtt_client is connected
  if (!mqtt_client.connected()) { reconnect(); }
  mqtt_client.loop();
  
  delay(50);
  publishFireAlert();
}


void publishFireAlert() {
  // Update the state of the client over MQTT
  mqtt_client.publish(fire_topic.c_str(), "Fire");

  #if DEBUG == true
    Serial.print("(MQTT) fire switch state updated: ");
    Serial.println("Fire");
  #endif
}



// ############################## WiFi functions
void waitForWiFiConnection() {
  #if DEBUG == true
    Serial.println("Connecting to WiFi");
  #endif
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    #if DEBUG == true
      Serial.print(".");
    #endif
    
    delay(250);
  }

  #if DEBUG == true
    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
  #endif
}


// ############################## MQTT functions
void connectMqtt() {
  mqtt_client.setServer(mqtt_server, MQTT_PORT);
  mqtt_client.setCallback(callback);
  reconnect();
}

void reconnect() {
  #if DEBUG == true
    Serial.print("Attempting to connect to MQTT server: ");
    Serial.println(mqtt_server);
 #endif

  while (!mqtt_client.connected()) {
    if (mqtt_client.connect(MQTT_CLIENT_NAME.c_str(), MQTT_USER, MQTT_PASS, ("node/" + MQTT_CLIENT_NAME).c_str(), 1, false, "timeout")) {
      mqtt_client.publish(("node/" + MQTT_CLIENT_NAME).c_str(), "connected");
      
      //mqtt_client.subscribe(String("cmd/" + MQTT_CLIENT_NAME).c_str());
      //mqtt_client.subscribe("cmd/node_kitchen");
      mqtt_client.subscribe(String("cmd/" + MQTT_CLIENT_NAME).c_str());
      
      #if DEBUG == true
        Serial.println("connected");
      #endif
    } else {
      #if DEBUG == true
        Serial.println("unable to connect, waiting 5 seconds...");
      #endif
      
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String command = getCommand(payload, length);

  if(command == "update_all") {
    publishFireAlert();
    return;
  }

  if(command == "update_fire") {
    #if DEBUG == true
      Serial.println("(MQTT) Updating fire switch information");
    #endif
    
    publishFireAlert();
    return;
  }
  
  #if DEBUG == true
    Serial.print("UNKNOWN MQTT COMMAND: ");
    Serial.println(command);
  #endif
}

String getCommand(byte* payload, unsigned int length) {
   char msg[length + 1];
   
  for (int i = 0; i < length; i++) {
    msg[i] = (char) payload[i];
  }
  
  msg[length] = '\0';

  return String(msg);
}

