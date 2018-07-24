#pragma once
#include <windows.h>

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CProcess Class                                                          */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CProcess
{
private:
    int         m_ProcessId;
    DWORD       m_ProcessName;

public:
                CProcess( int ProcessId );
    virtual     ~CProcess();

    int         GetProcessId() { return m_ProcessId; }
    void        SetProcessId( int ProcessId ) { m_ProcessId = ProcessId; }
    DWORD       GetProcessName() { return m_ProcessName; }
    void        SetProcessName( DWORD ProcessName ) { m_ProcessName = ProcessName; }
};

