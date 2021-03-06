
// BDDlg.h: файл заголовка
//

#pragma once

// Диалоговое окно CBDDlg
class CBDDlg : public CDialogEx
{
// Создание
public:
	CBDDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl Table;
	afx_msg void reload();
	CString Path;

	POSITION pos = NULL;
	afx_msg void OnBnAbout();
	afx_msg void OnBnEdit();
	afx_msg void OnBnDelete();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void AddNewStudent();
	afx_msg void ShowAll();
	afx_msg void Show3();
	afx_msg void Show4();
	afx_msg void Show5();
};