#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;

    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    while (count < 100)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "카운트 : " << count << endl;


        prev_end = end;
        end = chrono::steady_clock::now();
        count++;
        cout << "카운트 : " << count << endl;
        chrono::steady_clock::duration diff = end - prev_end;
        int duration_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
        if (duration_ms < 1000)
            this_thread::sleep_for(chrono::milliseconds(1000 - duration_ms));
    }

    //count++;
    //cout << "카운트 : " << count << endl;
    //// cout << "실제시간 : " << chrono::duration_cast<chrono::milliseconds>(diff).count() << endl;
    //start = end;
    //end = chrono::steady_clock::now();
    //chrono::steady_clock::duration diff = end - prev_start;
    //this_thread::sleep_for(chrono::milliseconds(1000 - chrono::duration_cast<chrono::milliseconds>(diff).count()));
}
