import serial
import keyboard
import time
from twilio.rest import Client
import pynmea2
import mysql.connector
sql=mysql.connector.connect(host="localhost",user="root",passwd="nikhil@695521",database="project")
mql=sql.cursor()

# Twilio credentials
account_sid = 'ACf7889ba8284baf0e37e9a5930e1f1dac'
auth_token = '7acca833333abfaf1dd2ede3937c8e38'
twilio_phone_number = '+19182213979'

recipient_phone_number = '+917356098988'

def send_sms(account_sid, auth_token, twilio_phone_number, recipient_phone_number, message_body):
    client = Client(account_sid, auth_token)
    
    message = client.messages.create(
        body=message_body,
        from_=twilio_phone_number,
        to=recipient_phone_number
    )
    
    print("Message SID:", message.sid)

# Define serial port and baud rate
ser = serial.Serial('COM4', 9600)  # Change 'COM7' to your Arduino's serial port
ser2 = serial.Serial('COM6', 9600)

# Function to send command to Arduino
def send_command(command):
    ser.write(command.encode())

# Main loop
while True:
    data = ser2.readline().decode('utf-8').strip()
    '''mrec=mql.fetchall()
    for x in mrec:
        (a,)=x
    print(x)'''
    if data=="Accident":
        print(data)
        send_command('x')
        print("Data:", data)
        data2 = ser2.readline().decode('utf-8').strip()
        print(data2)
        nmea_sentence="$GPRMC"+data2
        msg = pynmea2.parse(nmea_sentence)
        latitude = msg.latitude
        longitude = msg.longitude
        message_body = 'Accident my location is '+"Latitude:"+str(latitude)+" Longitude:"+ str(longitude)
        send_sms(account_sid, auth_token, twilio_phone_number, recipient_phone_number, message_body)
        break;
    elif data=="Stroke":
        print(data)
        send_command('x')
        data2 = ser2.readline().decode('utf-8').strip()
        print(data2)
        try:
            nmea_sentence="$GPRMC"+data2
            msg = pynmea2.parse(nmea_sentence)
            latitude = msg.latitude
            longitude = msg.longitude
            message_body = 'Stroke my location is '+"Latitude:"+str(latitude)+" Longitude:"+ str(longitude)
        except:
            message_body = 'Accident my location is '+data2
        qry="update location set loc=%s where no=%s"
        qry2="update location set status=%s where no=%s"
        mql.execute(qry,(message_body,1))
        sql.commit()
        mql.execute(qry2,(data,1))
        sql.commit()
        print("data:", message_body)
        from sleepmain import*
        #send_sms(account_sid, auth_token, twilio_phone_number, recipient_phone_number, message_body)
        break;
    else:
        if keyboard.is_pressed('up'):
            send_command('w')  # Move forward
        elif keyboard.is_pressed('down'):
            send_command('s')  # Move backward
        elif keyboard.is_pressed('left'):
            send_command('a')  # Turn left
        elif keyboard.is_pressed('right'):
            send_command('d')  # Turn right
        else:
            send_command('x')  # Stop


    time.sleep(0.1)  # Add a small delay to prevent excessive checking of keyboard state and serial input
