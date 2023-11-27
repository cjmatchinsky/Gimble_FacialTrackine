
## Gimble_FacialTrackine.py 
## Cameron Matchinsky
 import cv2
import serial
import time

ser = serial.Serial('COM8', 9600)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
center_X = 360
center_Y = 360


def to_servos_coms(servo_id, speed_step):
    message = str(servo_id) + str(speed_step)
    serial_comms_breakdown(message)

def serial_comms_breakdown(msg):
    print(msg)
    msg = "a" + msg + "z"
    char_array = list(msg)
    i = 0
    
    while i < len(char_array):
        ser.write(bytes(char_array[i], 'utf-8'))
        i += 1

def main():
    cap = cv2.VideoCapture(0, cv2.CAP_MSMF)

    while True:
        ret, frame = cap.read()
        frame = cv2.flip(frame, 0)
        frame = cv2.resize(frame, (720, 720))

        cv2.imshow('frame', frame)
        cv2.rectangle(frame, (345, 345), (375, 375), (255, 205, 0), 2)
        cv2.line(frame, (0, 360), (720, 360), (255, 205, 0), 2)
        cv2.line(frame, (360, 0), (360, 720), (255, 205, 0), 2)

        faces = face_cascade.detectMultiScale(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), scaleFactor=1.3, minNeighbors=5)
        tempx = 360
        tempy = 360

        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
            tempx = (x + w/2)
            tempy = (y + h/2)

        cv2.imshow('Face Detection', frame)
        time.sleep(0.01)

        if tempx > center_X +10:
            print('6')
            to_servos_coms(1, 6)  # Camera Need to move left 
        if tempx < center_X-10:
            print('4')
            to_servos_coms(1, 4)  # Camera Need to move Right 
        if tempy > center_Y+10:
            print('2')
            to_servos_coms(0, 2)  # Camera Need to move down
        if tempy < center_Y-10:
            print('8')
            to_servos_coms(0, 8)  # Camera Need to move up

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
