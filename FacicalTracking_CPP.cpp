#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>

HANDLE serialHandle;

void to_servos_coms(int servo_id, int speed_step) {
    std::string message = std::to_string(servo_id) + std::to_string(speed_step);
    serial_comms_breakdown(message);
}

void serial_comms_breakdown(std::string msg) {
    std::cout << msg << std::endl;
    msg = "a" + msg + "z";
    for (char c : msg) {
        WriteFile(serialHandle, &c, 1, NULL, NULL);
    }
}

int main() {
    serialHandle = CreateFile(L"COM8", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    cv::CascadeClassifier face_cascade;
    face_cascade.load(cv::samples::findFile(cv::data::haarcascades() + "haarcascade_frontalface_default.xml"));

    int center_X = 360;
    int center_Y = 360;

    cv::VideoCapture cap(0, cv::CAP_MSMF);
    
    while (true) {
        cv::Mat frame;
        cap >> frame;
        cv::flip(frame, frame, 0);
        cv::resize(frame, frame, cv::Size(720, 720));

        cv::imshow("frame", frame);
        cv::rectangle(frame, cv::Rect(345, 345, 30, 30), cv::Scalar(255, 205, 0), 2);
        cv::line(frame, cv::Point(0, 360), cv::Point(720, 360), cv::Scalar(255, 205, 0), 2);
        cv::line(frame, cv::Point(360, 0), cv::Point(360, 720), cv::Scalar(255, 205, 0), 2);

        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_frame, gray_frame);

        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray_frame, faces, 1.3, 5);

        int tempx = 360;
        int tempy = 360;

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
            tempx = face.x + face.width / 2;
            tempy = face.y + face.height / 2;
        }

        cv::imshow("Face Detection", frame);
        Sleep(10);

        if (tempx > center_X + 10) {
            std::cout << "6" << std::endl;
            to_servos_coms(1, 6);  // Camera Need to move left
        }
        if (tempx < center_X - 10) {
            std::cout << "4" << std::endl;
            to_servos_coms(1, 4);  // Camera Need to move Right
        }
        if (tempy > center_Y + 10) {
            std::cout << "2" << std::endl;
            to_servos_coms(0, 2);  // Camera Need to move down
        }
        if (tempy < center_Y - 10) {
            std::cout << "8" << std::endl;
            to_servos_coms(0, 8);  // Camera Need to move up
        }

        char c = cv::waitKey(1);
        if (c == 'q') {
            break;
        }
    }

    CloseHandle(serialHandle);
    cv::destroyAllWindows();
    return 0;
}
