// Valovlay.cpp : This file contains the '
// 
// 
// 
// 
// ' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "game.h"
#include <d3d9.h>
#include <tchar.h>
#include <WinUser.h>

#include <windows.h>
#include <iostream>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#include <stdlib.h>
#include <fstream>
#include <chrono> // for high_resolution_clock
#include <list>
#include <wrl/client.h>
#include <thread>
#include <iostream>
#include <string>
#include <iomanip>


bool Checkd4riverhaknaopStatus() {
   


    uintptr_t BaseAddr = d4riverhaknaop::GetBaseAddress(d4riverhaknaop::currentProcessId);
    std::cout << "-> B*a*s*e*A*d*d*r :: " << BaseAddr << std::endl;
    if (BaseAddr == 0)
    {
        return false;
    }

    int icheck = 29;
    NTSTATUS status = 0;
    int checked = d4riverhaknaop::read<int>(d4riverhaknaop::currentProcessId, (uintptr_t)&icheck, &status);
    std::cout << "-> checked :: " << checked << std::endl;
    std::cout << "-> icheck :: " << icheck << std::endl;
    if (checked != icheck)
    {
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{



    bool ready = false;
    if (d4riverhaknaop::initialize())
    {
        if (Checkd4riverhaknaopStatus())
        {
            ready = true;
        }
        else
        {
            wchar_t VarName[] = { 'E','R','C','K','E','r','i','v','e','z','\0' };
            UNICODE_STRING FVariableName = UNICODE_STRING();
            FVariableName.Buffer = VarName;
            FVariableName.Length = 28;
            FVariableName.MaximumLength = 30;
            // UNICODE_STRING VariableName = RTL_CONSTANT_STRING(VARIABLE_NAME);
            d4riverhaknaop::myNtSetSystemEnvironmentValueEx(&FVariableName, &d4riverhaknaop::ghgmamamahmrmhs43434, 0, 0, ATTRIBUTES);
            memset(VarName, 0, sizeof(VarName));
            // memset(VariableName.Buffer, 0, VariableName.Length);
            // VariableName.Length = 0;
            Beep(1250, 1000);
            std::cout << "no found" << std::endl;
        }
    }
    else
    {
        std::cout << "no found." << std::endl;
        Beep(1250, 500);
    }

    if (ready)
    {
        Beep(1250, 250);
        game::run();
    }

    std::cout << "gg" << std::endl;
    system("pause");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
