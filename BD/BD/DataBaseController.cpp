#include "stdafx.h"
#include "DataBaseController.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include <list>
#include <fstream>

using namespace std;

void DataBaseController::AddMarkup()
{
	clean();

	Table->SetExtendedStyle(Table->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	Table->InsertColumn(0, ColomnName[0], LVCFMT_LEFT, 0);
	for (i = 1; i < 10; i++) {
		Table->InsertColumn(i, ColomnName[i], LVCFMT_LEFT, 90);
	}

	for (; i < 100; i++)
	{
		SqlString2.Format(L"%d", i / 10);
		
		if (i % 10 == 0) {
			Table->InsertColumn(i, L"/", LVCFMT_LEFT, 50);
		}
		else if (i % 10 == 4) {
			Table->InsertColumn(i, SqlString2, LVCFMT_CENTER, 50);
		}
		else if (i % 10 == 5) {
			Table->InsertColumn(i, L"семестр", LVCFMT_LEFT, 70);
		}
		else if (i % 10 == 9) {
			Table->InsertColumn(i, L"\\", LVCFMT_RIGHT, 50);
		}
		else {
			Table->InsertColumn(i, L"", LVCFMT_LEFT, 50);
		}
	}
}

void DataBaseController::FillTable(CRecordset *recset)
{
	for (i = 0; i < 19; i++) {
		recset->GetFieldValue(DBtableName[i], str[i]);

		if (i == 0) {
			iRec = Table->InsertItem(0, str[0], 10);
		}
		else if (i == 4)
		{
			Table->SetItemText(iRec, i, str[i].Mid(0, 10));
		}
		else if (i > 9) {
			Reg.Format(L"IDP%d", (i - 9));
			recset->GetFieldValue(Reg, TMP);

			getMarks(str[i], TMP);
		}
		else {
			Table->SetItemText(iRec, i, str[i]);
		}
	}
}

void DataBaseController::getMarks(CString id_s, CString id_p) {
	k = 10 * (i - 9);
	
	CRecordset recset1(&database);
	CRecordset recset2(&database);

	SqlString1 = L"SELECT Session.* FROM[Session] WHERE((Session.id_session) = " + id_s + L")";
	SqlString2 = L"SELECT Program.* FROM[Program] WHERE((Program.id_pr) = " + id_p + L")";

	recset1.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString1, CRecordset::readOnly);
	recset2.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString2, CRecordset::readOnly);

	for (j = 0; j < 10; j++) {
		Reg.Format(L"mark%d", (j + 1));
		recset1.GetFieldValue(Reg, TMP);
		
		Reg.Format(L"pr%d", (j + 1));
		recset2.GetFieldValue(Reg, Reg);

		TMP = Reg + L":" + TMP;

		Table->SetItemText(iRec, (k + j), TMP);
	}
	
	recset1.Close();
	recset2.Close();
}

DataBaseController::DataBaseController(CString NameFile, CListCtrl &Table)
{
	this->Table = &Table;

	NameFile = L"DB.mdb";

	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, NameFile);
	TRY{
		database.Open(NULL,false,false,sDsn);

		if (database.IsOpen()) {

			CRecordset recset(&database);

			SqlString = L"SELECT Max(Student.id_s) AS[Max-id_s] FROM [Student]";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
			recset.GetFieldValue(L"Max-id_s", TMP);
			size = _ttoi(TMP);
			recset.Close();

			SqlString = "SELECT Student.*, Student.Session1 AS S1, Student.Session9 AS S9, Group.group, Kafedra.kafedra, Fakultet.* FROM[Group] INNER JOIN((Kafedra INNER JOIN Fakultet ON Kafedra.id_k = Fakultet.IDkafedra) INNER JOIN Student ON Fakultet.id_f = Student.IDspeciality) ON Group.id_g = Student.IDgroup ORDER BY Student.FamilyName DESC, Student.FirstName DESC, Student.Patronymic DESC";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			AddMarkup();
			
			while (!recset.IsEOF()) {
				FillTable(&recset);

				recset.MoveNext();
			}

			recset.Close();
		}
		else {
			AfxMessageBox(L"Wrong path of file!");
		}

		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#1: " + e->m_strError);
	}
	END_CATCH;
}

DataBaseController::~DataBaseController()
{
}

void DataBaseController::init(CString NameFile)
{
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, NameFile);
	TRY{
		database.Open(NULL,false,false,sDsn);

		if (database.IsOpen()) {
			CRecordset recset(&database); 
			
			SqlString = L"SELECT Max(Student.id_s) AS[Max-id_s] FROM [Student]";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
			recset.GetFieldValue(L"Max-id_s", TMP);
			size = _ttoi(TMP);
			recset.Close();

			SqlString = "SELECT Student.*, Student.Session1 AS S1, Student.Session9 AS S9, Group.group, Kafedra.kafedra, Fakultet.* FROM[Group] INNER JOIN((Kafedra INNER JOIN Fakultet ON Kafedra.id_k = Fakultet.IDkafedra) INNER JOIN Student ON Fakultet.id_f = Student.IDspeciality) ON Group.id_g = Student.IDgroup ORDER BY Student.FamilyName DESC, Student.FirstName DESC, Student.Patronymic DESC";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			AddMarkup();

			while (!recset.IsEOF()) {
				recset.GetFieldValue(L"S1", S1);
				recset.GetFieldValue(L"S9", S9);
				
				if (Selector(Trigger, _ttoi(S1), _ttoi(S9))) FillTable(&recset);

				recset.MoveNext();
			}

			recset.Close();
		}
		else {
			AfxMessageBox(L"Wrong path of file!");
		}

		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#3: " + e->m_strError);
	}
	END_CATCH;
}

void DataBaseController::clean()
{
	Table->DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)Table->GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		Table->DeleteColumn(i);
	}
}

CString* DataBaseController::getLists(int *size1, int *size2, CStudentDlg *dlg, CString ID) {
	TRY{
		database.Open(NULL,false,false,sDsn);

		if (database.IsOpen()) {
			CRecordset recset(&database);
			
			SqlString = "SELECT Group.* FROM [Group]";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
			
			CString *txt;
			list<CString> arr;
			list<int> ID_arr;
			list<int> ID_arr1;

			txt = new CString[2];

			while (!recset.IsEOF()) {
				recset.GetFieldValue(L"group", txt[0]);
				arr.push_back(txt[0]);

				recset.GetFieldValue(L"id_g", txt[0]);
				ID_arr.push_back(_ttoi(txt[0]));

				recset.MoveNext();
			}

			recset.Close();

			*size1 = arr.size();
			dlg->id_G = new int[*size1];

			SqlString = "SELECT Fakultet.id_f, Fakultet.fakultet, Kafedra.id_k, Kafedra.kafedra FROM Fakultet INNER JOIN Kafedra ON Kafedra.id_k = Fakultet.IDkafedra ORDER BY Fakultet.id_f ASC";

			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			i = 0;

			for (auto iter = ID_arr.begin(); iter != ID_arr.end(); iter++)
			{
				dlg->id_G[i] = *iter;
				i++;
			}

			ID_arr.clear();

			while (!recset.IsEOF()) {
				recset.GetFieldValue(L"kafedra", txt[0]);
				recset.GetFieldValue(L"fakultet", txt[1]);

				txt[0] = txt[0] + L" -> " + txt[1];

				arr.push_back(txt[0]);

				recset.GetFieldValue(L"id_k", txt[0]);
				recset.GetFieldValue(L"id_f", txt[1]);

				ID_arr.push_back(_ttoi(txt[0]));
				ID_arr1.push_back(_ttoi(txt[1]));

				recset.MoveNext();
			}

			recset.Close();

			*size2 = arr.size();

			txt = new CString[*size2 + 2];
			dlg->id_K = new int[*size2 - *size1];
			dlg->id_F = new int[*size2 - *size1];

			i = 0;

			for (auto iter = arr.begin(); iter != arr.end(); iter++)
			{
				txt[i] = *iter;
				i++;
			}

			SqlString = L"SELECT Student.IDgroup FROM Student WHERE(((Student.id_s) = " + ID + L"))";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
			recset.GetFieldValue(L"IDgroup", txt[i]);
			recset.Close();

			i++;

			SqlString = L"SELECT Fakultet.id_f FROM Fakultet INNER JOIN Student ON Fakultet.id_f = Student.IDspeciality WHERE(((Student.id_s) = " + ID + L"))";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);
			recset.GetFieldValue(L"id_f", txt[i]);
			recset.Close();

			i = 0;

			for (auto iter = ID_arr.begin(); iter != ID_arr.end(); iter++)
			{
				dlg->id_K[i] = *iter;
				i++;
			}

			i = 0;

			for (auto iter = ID_arr1.begin(); iter != ID_arr1.end(); iter++)
			{
				dlg->id_F[i] = *iter;
				i++;
			}

			database.Close();

			return txt;
		}
		else {
			AfxMessageBox(L"Wrong path of file!");

			return NULL;
		}

		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#4: " + e->m_strError);

		return NULL;
	}
	END_CATCH;
}

CString* DataBaseController::getLists(int *size1, int *size2, CStudentDlg *dlg) {
	TRY{
		database.Open(NULL,false,false,sDsn);

		if (database.IsOpen()) {
			CRecordset recset(&database);

			SqlString = "SELECT Group.* FROM [Group]";
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			CString *txt;
			list<CString> arr;
			list<int> ID_arr;
			list<int> ID_arr1;

			txt = new CString[2];

			while (!recset.IsEOF()) {
				recset.GetFieldValue(L"group", txt[0]);
				arr.push_back(txt[0]);

				recset.GetFieldValue(L"id_g", txt[0]);
				ID_arr.push_back(_ttoi(txt[0]));

				recset.MoveNext();
			}

			recset.Close();

			*size1 = arr.size();
			dlg->id_G = new int[*size1];
			
			SqlString = "SELECT Fakultet.id_f, Fakultet.fakultet, Kafedra.id_k, Kafedra.kafedra FROM Fakultet INNER JOIN Kafedra ON Kafedra.id_k = Fakultet.IDkafedra ORDER BY Fakultet.id_f ASC";
			
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			i = 0;

			for (auto iter = ID_arr.begin(); iter != ID_arr.end(); iter++)
			{
				dlg->id_G[i] = *iter;
				i++;
			}

			ID_arr.clear();

			while (!recset.IsEOF()) {
				recset.GetFieldValue(L"kafedra", txt[0]);
				recset.GetFieldValue(L"fakultet", txt[1]);

				txt[0] = txt[0] + L" -> " + txt[1];

				arr.push_back(txt[0]);

				recset.GetFieldValue(L"id_k", txt[0]);
				recset.GetFieldValue(L"id_f", txt[1]);

				ID_arr.push_back(_ttoi(txt[0]));
				ID_arr1.push_back(_ttoi(txt[1]));

				recset.MoveNext();
			}

			recset.Close();

			*size2 = arr.size();

			txt = new CString[*size2 + 2];
			dlg->id_K = new int[*size2 - *size1];
			dlg->id_F = new int[*size2 - *size1];

			i = 0;

			for (auto iter = arr.begin(); iter != arr.end(); iter++)
			{
				txt[i] = *iter;
				i++;
			}

			i = 0;

			for (auto iter = ID_arr.begin(); iter != ID_arr.end(); iter++)
			{
				dlg->id_K[i] = *iter;
				i++;
			}

			i = 0;

			for (auto iter = ID_arr1.begin(); iter != ID_arr1.end(); iter++)
			{
				dlg->id_F[i] = *iter;
				i++;
			}

			database.Close();
			return txt;
		}
		else {
			AfxMessageBox(L"Wrong path of file!");

			return NULL;
		}

		database.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#8: " + e->m_strError);

		return NULL;
	}
	END_CATCH;
}

void DataBaseController::getSession(CString id) {
	TRY{
		database.Open(NULL,false,false,sDsn);

		CString *tmp = new CString[18];

		CString path;

		ofstream file;

		if (database.IsOpen()) {
			CRecordset recset(&database);
			CRecordset recset1(&database);
			CRecordset recset2(&database);

			SqlString = L"SELECT Student.*, Fakultet.* FROM Fakultet, [Student] WHERE Student.id_s = " + id;

			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			for (int i = 0; i < 9; i++) {
				path.Format(L"tmp%d.txt", (i+1));
				
				file.open(path);

				tmp[i].Format(L"Session%d", (i + 1));
				tmp[9 + i].Format(L"IDP%d", (i + 1));

				recset.GetFieldValue(tmp[i], tmp[i]);
				recset.GetFieldValue(tmp[9 + i], tmp[9 + i]);
				
				SqlString1 = L"SELECT Session.* FROM[Session] WHERE(((Session.id_session) = " + tmp[i] + L"))";
				SqlString2 = L"SELECT Program.* FROM[Program] WHERE(((Program.id_pr) = " + tmp[9 + i] + L"))";

				recset1.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString1, CRecordset::readOnly);
				recset2.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString2, CRecordset::readOnly);

				for (int j = 0; j < 10; j++) {
					Reg.Format(L"pr%d", (j + 1));
					recset2.GetFieldValue(Reg, TMP);

					Reg.Format(L"mark%d", (j + 1));
					recset1.GetFieldValue(Reg, TMP);
					file << CT2A(TMP) << endl;
				}

				file << CT2A(tmp[i]) << endl;

				file.close();

				recset1.Close();
				recset2.Close();
			}
			
			recset.Close();
			database.Close();
		}
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#4: " + e->m_strError);
		database.Close();
	}
	END_CATCH;
}

void DataBaseController::addSession() {
	TRY{
		database.Open(NULL,false,false,sDsn);
		CRecordset recset(&database);
		CString tmp;


		SqlString = L"SELECT Max(Session.id_session) AS [Max-id_session] FROM[Session]";
		recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

		recset.GetFieldValue(L"Max-id_session", tmp);

		int index = _ttoi(tmp);

		ofstream file;

		if (database.IsOpen()) {
			for (int i = 0; i < 9; i++) {
				tmp.Format(L"tmp%d.txt", (i + 1));

				file.open(tmp);

				for (int j = 0; j < 10; j++) {
					file << CT2A(L"0") << endl;
				}

				tmp.Format(L"%d", ++index);

				file << CT2A(tmp) << endl;

				file.close();
			}
			recset.Close();
			database.Close();
		}
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#7: " + e->m_strError);
		database.Close();
	}
	END_CATCH;
}		//add 9 free tmp-files

void DataBaseController::delStudent(CString id) {
	TRY{
		database.Open(NULL,false,false,sDsn);

		CString path;

		ofstream file;

		if (database.IsOpen()) {
			CRecordset recset(&database);

			CString tmp[9];

			SqlString = L"SELECT Student.* FROM [Student] WHERE Student.id_s = " + id;
			recset.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString, CRecordset::readOnly);

			for (int i = 0; i < 9; i++) {
				tmp[i].Format(L"Session%d", (i + 1));

				recset.GetFieldValue(tmp[i], tmp[i]);

				SqlString = L"DELETE FROM [Session] WHERE Session.id_session = " + tmp[i];
				database.ExecuteSQL(SqlString);
			}

			SqlString = L"DELETE FROM [Student] WHERE Student.id_s = " + id;
			database.ExecuteSQL(SqlString);

			recset.Close();
			database.Close();
		}
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error#9: " + e->m_strError);
		database.Close();
	}
	END_CATCH;
}

bool DataBaseController::Selector(int mark, int s1, int s2) {
	if (mark == 0) return true;

	--s1;
	++s2;

	CRecordset recset4(&database);
	
	SqlString2.Format(L"SELECT MIN(f) AS val FROM (SELECT MIN(mark1) AS f FROM(SELECT [Session].mark1 FROM[Session] WHERE Session.mark1 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark2) FROM(SELECT [Session].mark2 FROM[Session] WHERE Session.mark2 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark3) FROM(SELECT [Session].mark3 FROM[Session] WHERE Session.mark3 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark4) FROM(SELECT [Session].mark4 FROM[Session] WHERE Session.mark4 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark5) FROM(SELECT [Session].mark5 FROM[Session] WHERE Session.mark5 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark6) FROM(SELECT [Session].mark6 FROM[Session] WHERE Session.mark6 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark7) FROM(SELECT [Session].mark7 FROM[Session] WHERE Session.mark7 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark8) FROM(SELECT [Session].mark8 FROM[Session] WHERE Session.mark8 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark9) FROM(SELECT [Session].mark9 FROM[Session] WHERE Session.mark9 > 0 AND Session.id_session > %d AND Session.id_session < %d) UNION SELECT MIN(mark10) FROM(SELECT [Session].mark10 FROM[Session] WHERE Session.mark10 > 0 AND Session.id_session > %d AND Session.id_session < %d))", s1, s2, s1, s2, s1, s2, s1, s2, s1, s2, s1, s2, s1, s2, s1, s2, s1, s2, s1, s2);

	recset4.Open(AFX_DB_USE_DEFAULT_TYPE, SqlString2, CRecordset::readOnly);
	recset4.GetFieldValue(L"val", TMP);
	recset4.Close();

	if (_ttoi(TMP) == mark) {
		return true;
	}
	return false;
}
