#config.py

# WLAN-Settings
WIFI_SSID = 'xxxx' # Wi-Fi network name
WIFI_PASSWORD = 'xxxx'# Wi-Fi password

#MQTT-Settings
MQTT_BROKER = 'xxx' # MQTT broker URL or IP address
MQTT_PORT = 1883 # MQTT port, default is 1883 for unencrypted connections
MQTT_TOPIC = 'topic/esp32'
MQTT_CLIENT_ID = 'esp32_client'
MQTT_USERNAME = 'xxx' # Username for the MQTT
MQTT_PASSWORD = 'xxx' # Password for the MQTT

#Pin-Settings
DHT_PIN = 4
LED_PIN = 2

# LCD-Settings
I2C_ADDR = 0x27 # I2C address of the LCD display
I2C_NUM_ROWS = 2 # Number of rows
I2C_NUM_COLS = 16 # Number of columns