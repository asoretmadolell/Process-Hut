#include "stdafx.h"
#include "CProcessHutGUIDlg.h"
#include "CProcessHutGUIApp.h"
#include <psapi.h>
#include <string>
#include <TlHelp32.h>

// CProcessHutGUIDlg dialog

CProcessHutGUIDlg::CProcessHutGUIDlg( CWnd* pParent /*=NULL*/ )
    :CDialog( CProcessHutGUIDlg::IDD, pParent )
    , m_strTree( _T( "" ) )
{

}

void CProcessHutGUIDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //DDX_Text( pDX, IDC_STATIC_TXT, m_strTree );
    DDX_Control( pDX, IDC_TREE1, m_treeCtrl );
}

// CProcessHutGUIDlg message handlers

BOOL CProcessHutGUIDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Get the list of process identifiers.
    DWORD aProcesses[ 1024 ], cbNeeded, cProcesses;
    unsigned int i;

    if( !EnumProcesses( aProcesses, sizeof( aProcesses ), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof( DWORD );
    ShowWindow( SW_MINIMIZE );

    HTREEITEM hProcessItem = m_treeCtrl.InsertItem( L"Processes", TVI_ROOT );

    for( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[ i ] != 0 )
        {
             // Insert process item
            CString str;
            str.Format( TEXT( "Process %d" ), aProcesses[ i ] );
            HTREEITEM hProcess = m_treeCtrl.InsertItem( str, hProcessItem );

            // Insert threads as child items for the process
            HANDLE hProcessHandle = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[ i ] );
            if( hProcessHandle != NULL )
            {
                 THREADENTRY32 threadEntry;
                 threadEntry.dwSize = sizeof( THREADENTRY32 );

                 HANDLE hThreadSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
                 if( hThreadSnapshot != INVALID_HANDLE_VALUE )
                 {
                      if( Thread32First( hThreadSnapshot, &threadEntry ) )
                      {
                           do
                           {
                                if( threadEntry.th32OwnerProcessID == aProcesses[ i ] )
                                {
                                     CString threadStr;
                                     threadStr.Format( TEXT( "Thread %d" ), threadEntry.th32ThreadID );
                                     m_treeCtrl.InsertItem( threadStr, hProcess );
                                }
                           }
                           while( Thread32Next( hThreadSnapshot, &threadEntry ) );
                      }
                 }
                 CloseHandle( hThreadSnapshot );
            }
            CloseHandle( hProcessHandle );
        }
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}
