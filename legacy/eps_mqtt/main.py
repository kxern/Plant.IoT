import time
import ujson
import dht
import network
import config
from machine import Pin, SoftI2C, reset
from umqtt.simple import MQTTClient
from machine_i2c_lcd import I2cLcd


def connect_wifi(ssid, password):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)

    print('Connecting to Wi-Fi...')
    while not wlan.isconnected():
        print('.', end='')
        time.sleep(1)
    print('\nWLAN Connected:', wlan.ifconfig())


def send_mqtt_message(client, topic, message):
    try:
        client.connect()
        client.publish(topic, message)
        print(f'Message sent: {message}')
        client.disconnect()
    except Exception as e:
        print('Error sending message:', e)


def blink_led(led):
    led.on()
    time.sleep(0.2)
    led.off()


def init_lcd():
    i2c = SoftI2C(sda=Pin(21), scl=Pin(22), freq=400000)
    lcd = I2cLcd(i2c, config.I2C_ADDR, config.I2C_NUM_ROWS, config.I2C_NUM_COLS)
    return lcd


def display_on_lcd(lcd, temperature, humidity):
    lcd.clear()
    lcd.putstr(f'Temp: {temperature}C')
    lcd.move_to(0, 1)
    lcd.putstr(f'Humidity: {humidity}%')

def main():
    error_count = 0
    connect_wifi(config.WIFI_SSID, config.WIFI_PASSWORD)

    client = MQTTClient(config.MQTT_CLIENT_ID, config.MQTT_BROKER, port=config.MQTT_PORT, user=config.MQTT_USERNAME, password=config.MQTT_PASSWORD)

    sensor = dht.DHT11(Pin(config.DHT_PIN))
    led = Pin(config.LED_PIN, Pin.OUT)

    lcd = init_lcd()

    while True:
        try:
            print('Reading sensor...')
            sensor.measure()
            temperature = sensor.temperature()
            humidity = sensor.humidity()

            display_on_lcd(lcd, temperature, humidity)

            blink_led(led)

            # Send MQTT
            data = {
                "temperature": temperature,
                "humidity": humidity
            }
            json_message = ujson.dumps(data)
            print(f'Sensorwerte (JSON): {json_message}')
            send_mqtt_message(client, config.MQTT_TOPIC, json_message)

            error_count = 0
            
        except Exception as e:
            print('Failed to read sensor:', e)
            error_count += 1
            
            if error_count >= 3:
                print("3 errors in a row! Restarting ESP32...")
                reset()

        time.sleep(30)

if __name__ == '__main__':
    main()