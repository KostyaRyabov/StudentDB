#pragma once
#include "BDDlg.h"
#include "CStudentDlg.h"

class DataBaseController
{
private:
	CDatabase database;
	CString SqlString, SqlString1, SqlString2;
	CString str[28];
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
	CListCtrl *Table;

	CString ColomnName[10] = { _T("№"),_T("Фамилия"),_T("Имя"),_T("Отчество"),_T("Дата рождения"),_T("Год поступления"),_T("Номер студенческого"),_T("Группа"),_T("Кафедра"),_T("Факультет") };
	CString DBtableName[19] = { _T("id_s"),_T("FamilyName"),_T("FirstName"),_T("Patronymic"),_T("DateOfBirth"),_T("AdmissionYear"),_T("ClassNumber"),_T("group"),_T("kafedra"),_T("fakultet"),_T("Session1"),_T("Session2"),_T("Session3"),_T("Session4"),_T("Session5"),_T("Session6"),_T("Session7"),_T("Session8"),_T("Session9")};

	CString TMP, Reg, S1, S9;

	int iRec = 0;
	int i,j,k;

	void AddMarkup();
	void FillTable(CRecordset *recset);
	void getMarks(CString id_s, CString id_p);
public:
	int size;
	int Trigger = 0;

	DataBaseController(CString NameFile, CListCtrl &Table);
	virtual ~DataBaseController();

	void init(CString NameFile);
	void clean();
	CString* getLists(int *size1, int *size2, CStudentDlg *dlg, CString ID);
	CString* getLists(int *size1, int *size2, CStudentDlg *dlg);
	void getSession(CString id);
	void addSession();
	void delStudent(CString id);
	bool Selector(int mark, int s1, int s2);
};