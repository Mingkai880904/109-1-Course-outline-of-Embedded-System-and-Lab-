#!/usr/bin/python3
#Ref: https://oranwind.org/-raspberry-pi-tou-guo-python-chuan-song-wen-shi-du-zi-xun-dao-thingspeak/
#**************************************************** 
# Import Package                                                                           
#**************************************************** 
#import Adafruit_DHT
import sys  
import time  
import http.client, urllib.parse, serial  
#sys.path.append('/home/pi/rpi/code/Package')  

#**************************************************** 
# Set Pin No, ThingSpeak Key                                                                          
#**************************************************** 

#sensor = Adafruit_DHT.DHT22
#pin =  24 #GPIO24

#Write API Key
#Replace it with your Write API Key
thingSpeakApiKey = "VXBKUVPJ127WFHS6"
ser = serial.Serial(
 port='/dev/ttyUSB0',
 baudrate = 115200,
 parity=serial.PARITY_NONE,
 stopbits=serial.STOPBITS_ONE,
 bytesize=serial.EIGHTBITS,
 timeout=3)
#**************************************************** 
# Set ThingSpeak Connection                                                   
#**************************************************** 

def post_to_thingspeak(payload):  
    headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
    not_connected = 1
    while (not_connected):
        try:
            conn = http.client.HTTPConnection("api.thingspeak.com:80")
            conn.connect()
            not_connected = 0
        except (httplib.HTTPException, socket.error) as ex:
            print("Error: %s" % ex)
            time.sleep(10)  # sleep 10 seconds

    conn.request("POST", "/update", payload, headers)
    response = conn.getresponse()
    print( response.status, response.reason, payload, time.strftime("%c"))
    data = response.read()
    conn.close()
	
def get_to_thingspeak(payload):  
    headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
    not_connected = 1
    while (not_connected):
        try:
            conn = http.client.HTTPConnection("api.thingspeak.com:80")
            conn.connect()
            not_connected = 0
        except (httplib.HTTPException, socket.error) as ex:
            print("Error: %s" % ex)
            time.sleep(10)  # sleep 10 seconds

    conn.request("GET", "/update", payload, headers)
    response = conn.getresponse()
    print( response.status, response.reason, payload, time.strftime("%c"))
    data = response.read()
    conn.close()		

#**************************************************** 
# Post ThingSpeak                                                  
#**************************************************** 
while True:
    str=ser.readline()
    if str!="":
        print(str)	
        data=str.decode().split(',')
    if(data[0]=='s') and (data[3]=='e\r\n'):
        humidity = float(data[1])
        temp = float(data [2])
        print(data)
        print(humidity)
        print(temp)	
    #[humidity, temp] = Adafruit_DHT.read_retry(sensor, pin)  
    print("temp = %.02f*C humidity =%.02f%%"%(temp, humidity))
    params = urllib.parse.urlencode({'field1': temp, 'field2': humidity, 'key': thingSpeakApiKey})
    print("************HTTP POST Request***********")
    post_to_thingspeak(params)
    time.sleep(15)	
    print("************HTTP GET Request***********")
    get_to_thingspeak(params)
    time.sleep(15)
