#include <iostream>
#include <windows.h>

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

 
    SetColor(7);

    bool isClicked = false;

    while (true) {
        
        INPUT_RECORD irInBuf[128];
        DWORD dwNumRead;

        ReadConsoleInput(hConsole, irInBuf, 128, &dwNumRead);

        for (DWORD i = 0; i < dwNumRead; ++i) {
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                if (irInBuf[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    if (!isClicked) {
                       
                        SetColor(14);
                        isClicked = true;
                    }
                }
                else {
                   
                    SetColor(7);
                    isClicked = false;
                }
            }
        }

        
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(GetConsoleWindow(), &p);

       
        std::cout << "Mouse X: " << p.x << " Y: " << p.y << std::endl;

        Sleep(100);  
        system("cls");  
    }

    SetConsoleTextAttribute(hConsole, saved_attributes);
    return 0;
}