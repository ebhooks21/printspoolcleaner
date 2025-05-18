/**
* File Name: main.cpp
* Created By: Eric Hooks
* Date of Creation: 11/6/2013
* Purpose: To clean up the print spooler.
*/

//Preprocessor Directive
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;

//Function prototypes
void runCommandWithWait(string cmd);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    //Output info to the user
    MessageBox(NULL, "Attempting to repair printing.  Please Wait...", "Attempting Repair", MB_ICONINFORMATION);

    //Shut off the print spooler
    MessageBox(NULL, "Stopping the Print Spooler...", "Stopping Print Spooler", MB_ICONINFORMATION);
    runCommandWithWait("net stop spooler");

    //Cleaning out the print queue
    MessageBox(NULL, "Cleaning out the print queue.  Please Wait...", "Cleaning Out Print Queue", MB_ICONINFORMATION);
    runCommandWithWait("del %systemroot%\\system32\\spool\\printers\\*.shd");
    runCommandWithWait("del %systemroot%\\system32\\spool\\printers\\*.spl");

    //Restart the print spooler
    MessageBox(NULL, "Restarting the Print Spooler...", "Restarting Print Spooler", MB_ICONINFORMATION);
    runCommandWithWait("net start spooler");

    //Output to user
    MessageBox(NULL, "Done.", "Done", MB_ICONINFORMATION);

    return 0;
}

/**
* Function to run a command.
*/
void runCommandWithWait(string cmd)
{
    //Setup process launching information
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    LPSTR command = const_cast<char *>(cmd.c_str());

    //Clear the structures
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    //Create the process and wait
    CreateProcess( NULL, command, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi );
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
