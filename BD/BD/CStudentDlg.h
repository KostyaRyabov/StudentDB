#pragma once


// Диалоговое окно CStudentDlg

class CStudentDlg : public CDialog
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CStudentDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_STUDENT_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CDatabase database;
	CString SqlString;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
public:
	CString NameFile;

	int Len1, Len2;
	CString *List, *tmp;

	int *id_K, *id_F, *id_G;
	CString k, f, g;

	int Gsel;
	int KFsel;
	
	CString ID;
	CString F;
	CString I;
	CString O;
	CString GP;
	CString NS;

	CComboBox G;
	CComboBox KF;

	bool start = true;
	
	COleDateTime Time;

	int ses = 0;

	void SetData(CString str);
	CString GetData();
	void ShowMarks(int session);
	void ShowPredmets(int session, int fak);
	void SetMarks(int session, int id, CString value);
	void LimitStr(CString *str, int len);

	CString s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, IDs;


	bool changed = false;
	bool adding = false;

	afx_msg void LastSession();
	afx_msg void NextSession();
	afx_msg void Add();
	afx_msg void Cancel();
	afx_msg void M1Changer();
	afx_msg void M2Changer();
	afx_msg void M3Changer();
	afx_msg void M4Changer();
	afx_msg void M5Changer();
	afx_msg void M6Changer();
	afx_msg void M7Changer();
	afx_msg void M8Changer();
	afx_msg void M9Changer();
	afx_msg void M10Changer();
	afx_msg void ChangeG();
	afx_msg void ChangeKF();
};
