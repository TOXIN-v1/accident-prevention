from twilio.rest import Client

    


account_sid = ''
auth_token = ''

# Twilio phone number and destination phone number
twilio_number = '+123456789'  # Your Twilio phone number
destination_number = '+911234567890'  # Destination phone number

# Message content
sos_message = 'SOS Help Me!!'

# Create Twilio client
client = Client(account_sid, auth_token)

# Send the SOS message
message = client.messages.create(
    body=sos_message,
    from_=twilio_number,
    to=destination_number
)

# Print the message SID
print(f"SOS message sent. Message SID: {message.sid}")
