from upm import pyupm_jhd1313m1 as lcd
import pyrebase
import random
import time

def getValue():
    ref_arquivo = open("rtc_write","r")
    print ref_arquivo
    return ref_arquivo

def main():
    # Initialize Jhd1313m1 at 0x3E (LCD_ADDRESS) and 0x62 (RGB_ADDRESS)
    config = {
        "apiKey": "AIzaSyA_IBnpiDjghCQ1vaNh5f6xgQ17DXPOeUI",
        "authDomain": "iot-sistemas-embarcados.firebaseapp.com",
        "databaseURL": "https://iot-sistemas-embarcados.firebaseio.com",
        "storageBucket": "projectId.appspot.com",
        "serviceAccount": "iot-sistemas-embarcados-firebase-adminsdk-us0vt-6cdf4d35cc.json"
    }
    firebase = pyrebase.initialize_app(config)
    db = firebase.database()
    myLcd = lcd.Jhd1313m1(0, 0x3E, 0x62)

    myLcd.setCursor(0, 0)

    while True:
        time.sleep(10)
        myLcd.setColor(255, 0, 0)
        # Rotina para pegar o valor
        val = getValue()
        db.child('temperature').push(val)
        myLcd.write('Valor: %d' % val)



if __name__ == '_main_':
    main()
