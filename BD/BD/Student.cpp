// Student.h: ���������� ������ CStudent



// ���������� CStudent

// ����������� ��� 4 ������ 2018 �., 12:45

#include "stdafx.h"
#include "Student.h"
IMPLEMENT_DYNAMIC(CStudent, CRecordset)

CStudent::CStudent(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_Firstname = L"";
	m_Familyname = L"";
	m_Patronymic = L"";
	m_DateofBirth;
	m_Admissionyear = 0;
	m_Classnumber = L"";
	m_id_group = 0;
	m_id_Speciality = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
#error �������� ������������: ������ ����������� ����� ��������� ������ 
// ��������� ������ ����������� ����� ��������� ��������������� ������ ��� 
// ������ ���������������� ����������. ������� #error ����� ��������� ������ ����������� 
// � ����� ������������. ��������, 
// ����������� ��������� ������ � ������ ���� ��� ������������ ������ ��������������.
CString CStudent::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\DB.mdb;DefaultDir=C:;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CStudent::GetDefaultSQL()
{
	return _T("[Student]");
}

void CStudent::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// ����� �������, ��� RFX_Text() � RFX_Int(), ������� �� ���� 
// ���������� �����, � �� �� ���� ���� � ���� ������.
// ODBC ��������� ������� ������������� ������������� �������� ������� � ������� ����
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[First name]"), m_Firstname);
	RFX_Text(pFX, _T("[Family name]"), m_Familyname);
	RFX_Text(pFX, _T("[Patronymic]"), m_Patronymic);
	RFX_Date(pFX, _T("[Date of Birth]"), m_DateofBirth);
	RFX_Long(pFX, _T("[Admission year]"), m_Admissionyear);
	RFX_Text(pFX, _T("[Class number]"), m_Classnumber);
	RFX_Long(pFX, _T("[id_group]"), m_id_group);
	RFX_Long(pFX, _T("[id_Speciality]"), m_id_Speciality);

}
/////////////////////////////////////////////////////////////////////////////
// CStudent �����������

#ifdef _DEBUG
void CStudent::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudent::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


