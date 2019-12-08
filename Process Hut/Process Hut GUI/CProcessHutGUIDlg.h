#pragma once
#include "afxcmn.h"

#include "resource.h"

// CProcessHutGUIDlg dialog
class CProcessHutGUIDlg : public CDialog
{
// Construction
public:
    CProcessHutGUIDlg( CWnd* pParent = NULL );  // standard constructor
    
// Dialog Data
    enum { IDD = IDD_EXAMPLE_DLG };

protected:
    virtual void DoDataExchange( CDataExchange* pDX );	// DDX/DDV support

// Implementation
protected:
    virtual BOOL OnInitDialog();

public:    
    CString m_strTree;
    CTreeCtrl m_treeCtrl;
};
