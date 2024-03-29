/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* Process Hut                                                               */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* This application is for learning to manage Windows processes.             */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Process Hut.cpp:                                                          */
/*                                                                           */
/* Defines the entry point for the console application.                      */
/*                                                                           */
/*****************************************************************************/

#include "stdafx.h"
#include <windows.h>
#include <psapi.h>
#include "CProcess.h"

// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* PrintProcessNameAndID()                                                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[ MAX_PATH ] = TEXT( "<unknown>" );

    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

    // Get the process name.
    if( NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, sizeof( szProcessName ) / sizeof( TCHAR ) );
        }
    }

    // Print the process name and identifier.
    _tprintf( TEXT( "%s  (PID: %u)\n" ), szProcessName, processID );

    // Release the handle to the process.
    CloseHandle( hProcess );
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* _tmain()                                                                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
int _tmain( int argc, _TCHAR* argv[] )
{
    char answer;
    bool done = false;

    wprintf( L"Welcome to Process Hut\n" );
    wprintf( L"\tType \"r\" to refresh process list\n" );
    wprintf( L"\tType \"q\" to quit\n" );
    wprintf( L"Choose your option: " );
    do
    {
        answer = _fgetwchar();
        switch( answer )
        {
            default:
                wprintf( L"Try again, dumbass: " );
                break;
            case 'q':
                return 0;
            case '\n':
                break;
            case 'r':
                done = true;
                break;
        }
    }
    while( !done );

    //CProcess* myProcesses[ 1024 ];

    // Get the list of process identifiers.
    DWORD aProcesses[ 1024 ], cbNeeded, cProcesses;
    unsigned int i;

    if( !EnumProcesses( aProcesses, sizeof( aProcesses ), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof( DWORD );

    // Print the name and process identifier for each process.
    for( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[ i ] != 0 )
        {
            PrintProcessNameAndID( aProcesses[ i ] );
            //myProcesses[ i ] = new CProcess( aProcesses[ i ] );
        }
    }
}
