
## Gimble_FacialTrackine.py 
## Cameron Matchinsky

import cv2
import sys
import serial
import time
import pygame
ser = serial.Serial('COM8', 9600)

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')


'''
apiPreference    preferred Capture API backends to use. 
Can be used to enforce a specific reader implementation 
if multiple are available: 
e.g. cv2.CAP_MSMF or cv2.CAP_DSHOW.
'''



def map_value(value, from_min, from_max, to_min, to_max):
    # Ensure the value is within the source range
    value = max(min(value, from_max), from_min)
    
    # Map the value to the target range
    mapped_value = (value - from_min) * (to_max - to_min) / (from_max - from_min) + to_min
    
    return mapped_value

def to_servos_coms(   servo_id,speed_step):
    message =  str(servo_id) + (speed_step )
    serial_comms_breakdown(message)
    
def serial_comms_breakdown(msg):   #   a           1               0-9     z
    msg = "a" + msg + "z"  #   a start +  0 = servo1, 1 = servo1  +    +  z end 
    char_array = list(msg)     # is a string 
    i =0
    while( i<len(char_array)):
        ser.write(bytes(char_array[i],'utf-8'))
        i+=1


def main():

    to_servos_coms(0,str(35))
    to_servos_coms(1,str(20))

    pygame.init()
    display = pygame.display.set_mode((200,200))
    servo1 = 10
    servo2 = 10
    # open video0
    cap = cv2.VideoCapture(0, cv2.CAP_MSMF)
    # set width and height

    # set fps
    # cap.set(cv2.CAP_PROP_FPS, 30)
    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()
        frame = cv2.flip(frame, 0)
        frame = cv2.resize(frame, (720, 720))
        # Display the resulting frame
        cv2.imshow('frame', frame)
        cv2.rectangle(frame, (358, 358), (362,362), (255, 205, 0), 2)
         # Detect faces in the frame
        faces = face_cascade.detectMultiScale(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), scaleFactor=1.3, minNeighbors=5)
        tempx = 360
        tempy= 360
        # Draw rectangles around the detected faces
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
            tempx = (x+w)/2
            tempy=  (h+y)/2
        # Display the resulting frame
        cv2.imshow('Face Detection', frame)
        y_map = map_value(tempy, 0, 720 , 0, 40)
        x_map = map_value(tempx, 0, 720 , 0, 40)
        to_servos_coms(0,str(y_map))
        to_servos_coms(1,str(x_map))
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    


        

        # creating a loop to check events that
        # are occurring

        ##                                   0   1  2  3  4  5  6  7   8  9 
     ## Arduino array int array_degrees[10]={11,24,38,52,66,80,94,108,122,148};
     # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()
 

if __name__ == '__main__':
    main()
