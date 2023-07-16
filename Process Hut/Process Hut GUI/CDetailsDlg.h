#pragma once
#include "afxcmn.h"

#include "resource.h"


// CDetailsDlg dialog

class CDetailsDlg : public CDialog
{
	DECLARE_DYNAMIC(CDetailsDlg)

public:
	CDetailsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDetailsDlg();

// Dialog Data
	enum { IDD = IDD_DETAILSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

     // Implementation
protected:
     virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
     CListBox m_listBox;
     CString m_processName;
     CString m_workingDirectory;

};
