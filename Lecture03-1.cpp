#include <iostream>

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

void drawBlock(int colorCode) {
    std::cout << "\x1b[" << colorCode << "m██";
}

int main() {
    int studentID = 202427042;
    std::string studentName = "최민석"; 

    std::cout << "화면에 그림을 그리는 프로그램입니다." << std::endl;
    std::cout << "학번: " << studentID << std::endl;
    std::cout << "이름: " << studentName << std::endl;

    int objectCode;
    while (true) {
        std::cout << std::endl;
        std::cout << "화면에 그릴 물체 코드를 입력하세요: ";
        std::cin >> objectCode;

        if (objectCode == 1) {
            drawBlock(White);
        } else if (objectCode == 2) {
            drawBlock(Red);
        } else if (objectCode == 4) { 
            drawBlock(Green);
        } else if (objectCode == 8) { 
            drawBlock(Yellow);
        } else if (objectCode == 16) { 
            drawBlock(Cyan);
        } else if (objectCode == 32) { 
            drawBlock(Magenta);
        } else if (objectCode == 64) { 
            break;
        } else {
            std::cout << "유효하지 않은 물체 코드입니다. 다시 입력해주세요." << std::endl;
        }
    }

    std::cout << std::endl << "프로그램을 종료합니다." << std::endl;

    return 0;
}