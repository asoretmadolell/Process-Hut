#include "stdafx.h"
#include "CProcessHutGUIDlg.h"
#include "CProcessHutGUIApp.h"

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
    
    ShowWindow( SW_MINIMIZE );

    HTREEITEM hItem, hCar;
    hItem = m_treeCtrl.InsertItem( L"Car Listing", TVI_ROOT );
    hCar = m_treeCtrl.InsertItem( L"Economy", hItem );
    m_treeCtrl.InsertItem( L"BH-733", hCar );
    m_treeCtrl.InsertItem( L"SD-397", hCar );
    m_treeCtrl.InsertItem( L"JU-538", hCar );
    m_treeCtrl.InsertItem( L"DI-285", hCar );
    m_treeCtrl.InsertItem( L"AK-830", hCar );
    hCar = m_treeCtrl.InsertItem( L"Compact", hItem );
    m_treeCtrl.InsertItem( L"HG-490", hCar );
    m_treeCtrl.InsertItem( L"PE-473", hCar );
    hCar = m_treeCtrl.InsertItem( L"Standard", hItem );
    m_treeCtrl.InsertItem( L"SO-398", hCar );
    m_treeCtrl.InsertItem( L"DF-438", hCar );
    m_treeCtrl.InsertItem( L"IS-833", hCar );
    hCar = m_treeCtrl.InsertItem( L"Full Size", hItem );
    m_treeCtrl.InsertItem( L"PD-304", hCar );
    hCar = m_treeCtrl.InsertItem( L"Mini Van", hItem );
    m_treeCtrl.InsertItem( L"ID-497", hCar );
    m_treeCtrl.InsertItem( L"RU-304", hCar );
    m_treeCtrl.InsertItem( L"DK-905", hCar );
    hCar = m_treeCtrl.InsertItem( L"SUV", hItem );
    m_treeCtrl.InsertItem( L"FE-948", hCar );
    m_treeCtrl.InsertItem( L"AD-940", hCar );
    hCar = m_treeCtrl.InsertItem( L"Truck", hItem );
    m_treeCtrl.InsertItem( L"HD-394", hCar );

    return TRUE;  // return TRUE  unless you set the focus to a control
}
