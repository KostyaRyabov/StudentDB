// CStudentDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "BD.h"
#include "CStudentDlg.h"
#include "DataBaseController.h"
#include "afxdialogex.h"
#include <fstream>
#include <list>

using namespace std;


// Диалоговое окно CStudentDlg

IMPLEMENT_DYNAMIC(CStudentDlg, CDialog)

CStudentDlg::CStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_STUDENT_EDIT, pParent)
	, F(_T(""))
	, I(_T(""))
	, O(_T(""))
	, Time(COleDateTime::GetCurrentTime())
	, GP(_T(""))
	, NS(_T(""))
	, s1(_T(""))
	, s2(_T(""))
	, s3(_T(""))
	, s4(_T(""))
	, s5(_T(""))
	, s6(_T(""))
	, s7(_T(""))
	, s8(_T(""))
	, s9(_T(""))
	, s10(_T(""))
	, s11(_T(""))
	, s12(_T(""))
	, s13(_T(""))
	, s14(_T(""))
	, s15(_T(""))
	, s16(_T(""))
	, s17(_T(""))
	, s18(_T(""))
	, s19(_T(""))
	, s20(_T(""))
	, IDs(_T(""))
{
	
}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, F);	
	DDX_Text(pDX, IDC_EDIT3, I);
	DDX_Text(pDX, IDC_EDIT2, O);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, Time);
	DDX_Text(pDX, IDC_EDIT4, GP);
	DDX_Text(pDX, IDC_EDIT5, NS);
	DDX_Control(pDX, IDC_COMBO2, KF);
	DDX_Control(pDX, IDC_COMBO3, G);

	DDX_Text(pDX, IDC_EDIT6, s1);
	DDX_Text(pDX, IDC_EDIT7, s2);
	DDX_Text(pDX, IDC_EDIT8, s3);
	DDX_Text(pDX, IDC_EDIT9, s4);
	DDX_Text(pDX, IDC_EDIT10, s5);
	DDX_Text(pDX, IDC_EDIT11, s6);
	DDX_Text(pDX, IDC_EDIT12, s7);
	DDX_Text(pDX, IDC_EDIT13, s8);
	DDX_Text(pDX, IDC_EDIT14, s9);
	DDX_Text(pDX, IDC_EDIT15, s10);
	DDX_Text(pDX, IDC_EDIT16, s11);
	DDX_Text(pDX, IDC_EDIT17, s12);
	DDX_Text(pDX, IDC_EDIT18, s13);
	DDX_Text(pDX, IDC_EDIT19, s14);
	DDX_Text(pDX, IDC_EDIT20, s15);
	DDX_Text(pDX, IDC_EDIT21, s16);
	DDX_Text(pDX, IDC_EDIT22, s17);
	DDX_Text(pDX, IDC_EDIT23, s18);
	DDX_Text(pDX, IDC_EDIT24, s19);
	DDX_Text(pDX, IDC_EDIT25, s20);

	DDX_Text(pDX, IDC_EDIT26, IDs);

	if (start) {
		int i;

		CString sss;

		for (i = 0; i < Len2; i++) {
			if (i < Len1) {
				G.AddString(List[i]);
			}
			else {
				KF.AddString(List[i]);
			}
		}

		if (!adding) {
			G.SetCurSel(_ttoi(List[i]) - 1);
			g.Format(L"%d", id_G[_ttoi(List[i]) - 1]);

			i++;

			KF.SetCurSel(_ttoi(List[i]) - 1);

			f.Format(L"%d", id_F[_ttoi(List[i]) - 1]);
			k.Format(L"%d", id_K[_ttoi(List[i]) - 1]);
		}
		else {
			G.SetCurSel(0);
			g.Format(L"%d", id_G[0]);

			KF.SetCurSel(0);

			f.Format(L"%d", id_F[0]);
			k.Format(L"%d", id_K[0]);
		}
		start = false;
	}
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialog)
	ON_BN_CLICKED(IDOK2, &CStudentDlg::LastSession)
	ON_BN_CLICKED(IDOK3, &CStudentDlg::NextSession)
	ON_BN_CLICKED(IDOK, &CStudentDlg::Add)
	ON_BN_CLICKED(IDCANCEL, &CStudentDlg::Cancel)
	ON_EN_CHANGE(IDC_EDIT7, &CStudentDlg::M1Changer)
	ON_EN_CHANGE(IDC_EDIT9, &CStudentDlg::M2Changer)
	ON_EN_CHANGE(IDC_EDIT11, &CStudentDlg::M3Changer)
	ON_EN_CHANGE(IDC_EDIT13, &CStudentDlg::M4Changer)
	ON_EN_CHANGE(IDC_EDIT15, &CStudentDlg::M5Changer)
	ON_EN_CHANGE(IDC_EDIT17, &CStudentDlg::M6Changer)
	ON_EN_CHANGE(IDC_EDIT19, &CStudentDlg::M7Changer)
	ON_EN_CHANGE(IDC_EDIT21, &CStudentDlg::M8Changer)
	ON_EN_CHANGE(IDC_EDIT23, &CStudentDlg::M9Changer)
	ON_EN_CHANGE(IDC_EDIT25, &CStudentDlg::M10Changer)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CStudentDlg::ChangeG)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CStudentDlg::ChangeKF)
END_MESSAGE_MAP()


// Обработчики сообщений CStudentDlg


void CStudentDlg::SetData(CString str) {
	Time.SetDate(_ttoi(str.Mid(0, 4)), _ttoi(str.Mid(5, 2)), _ttoi(str.Mid(8, 2)));
}

CString CStudentDlg::GetData() {
	UpdateData();
	
	CString tmp;

	tmp.Format(L"%d-%d-%d", Time.GetDay(), Time.GetMonth(), Time.GetYear());

	return tmp;
}

void CStudentDlg::ShowMarks(int session) {
	UpdateData(); 
	
	IDs.Format(L"%d сессия", session);
	
	fstream file;
	char *ttt = new char[16];
	CString tmp;

	tmp.Format(L"tmp%d.txt", session);

	file.open(tmp);

	file.getline(ttt, 16); s2 = CString(ttt, 16);
	file.getline(ttt, 16); s4 = CString(ttt, 16);
	file.getline(ttt, 16); s6 = CString(ttt, 16);
	file.getline(ttt, 16); s8 = CString(ttt, 16);
	file.getline(ttt, 16); s10 = CString(ttt, 16);
	file.getline(ttt, 16); s12 = CString(ttt, 16);
	file.getline(ttt, 16); s14 = CString(ttt, 16);
	file.getline(ttt, 16); s16 = CString(ttt, 16);
	file.getline(ttt, 16); s18 = CString(ttt, 16);
	file.getline(ttt, 16); s20 = CString(ttt, 16);

	file.close();

	UpdateData(false);
}

void CStudentDlg::ShowPredmets(int session, int fak) {
	UpdateData(); 
	
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, NameFile);
	TRY{
		database.Open(NULL,false,false,sDsn);
		CRecordset recset(&database);

		SqlString.Format(L"SELECT Program.* FROM [Program] INNER JOIN [Fakultet] ON Fakultet.IDP%d = Program.id_pr WHERE Fakultet.id_f = " + f, session);
		recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
		
		recset.GetFieldValue(L"pr1", s1);
		recset.GetFieldValue(L"pr2", s3);
		recset.GetFieldValue(L"pr3", s5);
		recset.GetFieldValue(L"pr4", s7);
		recset.GetFieldValue(L"pr5", s9);
		recset.GetFieldValue(L"pr6", s11);
		recset.GetFieldValue(L"pr7", s13);
		recset.GetFieldValue(L"pr8", s15);
		recset.GetFieldValue(L"pr9", s17);
		recset.GetFieldValue(L"pr10", s19);

		recset.Close();
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#5: " + e->m_strError);
		database.Close();
	}
	END_CATCH;

	UpdateData(false);
}

void CStudentDlg::SetMarks(int session, int id, CString value) {
	ifstream file;
	ofstream refile;
	CString tmp;
	CString str[11];
	char *ttt = new char[2];
	int i;

	tmp.Format(L"tmp%d.txt", session);

	file.open(tmp);
	
	for (i = 0; i < 11; i++) {
		file.getline(ttt, 8);

		str[i] = CString(ttt, 8);
	}
	file.close();

	refile.open(tmp);

	for (i = 0; i < 11; i++) {
		if (i == id) {
			refile << CT2A(value) << endl;
		}
		else {
			refile << CT2A(str[i]) << endl;
		}
	}

	refile.close();
}
//rewrite tmp-file

void CStudentDlg::LastSession()
{
	UpdateData(); 
	
	ses--;

	if (ses < 1) {
		ses = 1;
	}

	if (ses != 0) {
		ShowMarks(ses);
		ShowPredmets(ses, _ttoi(f));
	}

	UpdateData(false);
}

void CStudentDlg::NextSession()
{
	UpdateData();
	
	ses++;

	if (ses > 9) {
		ses = 9;
	}

	if (ses != 0) {
		ShowMarks(ses);
		ShowPredmets(ses, _ttoi(f));
	}

	UpdateData(false);
}

void CStudentDlg::Add()
{
	UpdateData();

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, NameFile);
	TRY{
		database.Open(NULL,false,false,sDsn);
		
		if (!adding) {
			SqlString = L"UPDATE Student SET FamilyName = '" + F + "', FirstName = '" + I + "', Patronymic = '" + O + "', DateOfBirth = '" + GetData() + "', AdmissionYear = '" + GP + "', ClassNumber = '" + NS + "', IDgroup = '" + g + "', IDspeciality = '" + f + "' WHERE id_s = " + ID;
			database.ExecuteSQL(SqlString);

			for (int i = 0; i < 9; i++) {
				fstream file;
				char *ttt = new char[16];
				CString tmp;
				CString mark[11];

				tmp.Format(L"tmp%d.txt", i + 1);

				file.open(tmp);

				for (int i = 0; i < 11; i++) {
					file.getline(ttt, 16); mark[i] = CString(ttt, 16);

					if (mark[i] == "") {
						mark[i] == "0";
					}
				}

				file.close();

				SqlString = L"UPDATE Session SET mark1 = '" + mark[0] + "', mark2 = '" + mark[1] + "', mark3 = '" + mark[2] + "', mark4 = '" + mark[3] + "', mark5 = '" + mark[4] + "', mark6 = '" + mark[5] + "', mark7 = '" + mark[6] + "', mark8 = '" + mark[7] + "', mark9 = '" + mark[8] + "', mark10 = '" + mark[9] + "' WHERE Session.id_session = " + mark[10];
				database.ExecuteSQL(SqlString);
			}
		}
		else {
			int idSes[9];

			for (int i = 0; i < 9; i++) {
				fstream file;
				char *ttt = new char[16];
				CString tmp;
				CString mark[11];

				tmp.Format(L"tmp%d.txt", i + 1);

				file.open(tmp);

				for (int i = 0; i < 11; i++) {
					file.getline(ttt, 16); mark[i] = CString(ttt, 16);

					if (mark[i] == "") {
						mark[i] == "0";
					}
				}

				file.close();

				idSes[i] = _ttoi(mark[10]);
				SqlString.Format(L"INSERT INTO Session (id_session,mark1,mark2,mark3,mark4,mark5,mark6,mark7,mark8,mark9,mark10) VALUES (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)", idSes[i], _ttoi(mark[0]), _ttoi(mark[1]), _ttoi(mark[2]), _ttoi(mark[3]), _ttoi(mark[4]), _ttoi(mark[5]), _ttoi(mark[6]), _ttoi(mark[7]), _ttoi(mark[8]), _ttoi(mark[9]));

				database.ExecuteSQL(SqlString);
			}
			SqlString.Format(L"INSERT INTO [Student] (id_s,[FirstName],[FamilyName],[Patronymic],[DateOfBirth],[AdmissionYear],[ClassNumber],[IDgroup],[IDspeciality],[Session1],[Session2],[Session3],[Session4],[Session5],[Session6],[Session7],[Session8],[Session9]) VALUES (%s,'%s','%s','%s','%s',%s,'%s',%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d)", ID, I, F, O, GetData(), GP, NS, g, f, idSes[0], idSes[1], idSes[2], idSes[3], idSes[4], idSes[5], idSes[6], idSes[7], idSes[8]);
			
			database.ExecuteSQL(SqlString);
		}
		
		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#6: " + e->m_strError);
		database.Close();
	}
	END_CATCH;

	changed = true;

	CDialog::OnOK();
}


void CStudentDlg::Cancel()
{
	CDialog::OnCancel();
}				//just exit


void CStudentDlg::M1Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s2, 1);
	}else LimitStr(&s2, 0);
	SetMarks(ses, 0, s2);

	UpdateData(false);
}


void CStudentDlg::M2Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s4, 1);
	}else LimitStr(&s4, 0);

	SetMarks(ses, 1, s4);

	UpdateData(false);
}


void CStudentDlg::M3Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s6, 1);
	}
	else LimitStr(&s6, 0);

	SetMarks(ses, 2, s6);

	UpdateData(false);
}


void CStudentDlg::M4Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s8, 1);
	}
	else LimitStr(&s8, 0);
	SetMarks(ses, 3, s8);

	UpdateData(false);
}


void CStudentDlg::M5Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s10, 1);
	}
	else LimitStr(&s10, 0);
	SetMarks(ses, 4, s10);

	UpdateData(false);
}


void CStudentDlg::M6Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s12, 1);
	}
	else LimitStr(&s12, 0);
	SetMarks(ses, 5, s12);

	UpdateData(false);
}


void CStudentDlg::M7Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s14, 1);
	}
	else LimitStr(&s14, 0);
	SetMarks(ses, 6, s14);

	UpdateData(false);
}


void CStudentDlg::M8Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s16, 1);
	}
	else LimitStr(&s16, 0);
	SetMarks(ses, 7, s16);

	UpdateData(false);
}


void CStudentDlg::M9Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s18, 1);
	}
	else LimitStr(&s18, 0);
	SetMarks(ses, 8, s18);

	UpdateData(false);
}


void CStudentDlg::M10Changer()
{
	UpdateData();
	if (ses != 0) {
		LimitStr(&s20, 1);
	}
	else LimitStr(&s20, 0);
	SetMarks(ses, 9, s20);

	UpdateData(false);
}


void CStudentDlg::ChangeG()
{
	UpdateData(); 
	
	g.Format(L"%d", id_G[G.GetCurSel()]);

	UpdateData(false);
}


void CStudentDlg::ChangeKF()
{
	UpdateData();
	
	f.Format(L"%d", id_F[KF.GetCurSel()]);
	k.Format(L"%d", id_K[KF.GetCurSel()]);
	
	if (ses != 0) {
		ShowPredmets(ses, _ttoi(f));
	}

	UpdateData(false);
}

void CStudentDlg::LimitStr(CString *str, int len) {
	if (str->GetLength() > len) str->Delete(str->GetLength() - 1);

	if (_ttoi(*str) > 5) str->Delete(str->GetLength() - 1);
}