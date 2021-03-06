
// BDDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "BD.h"
#include "BDDlg.h"
#include "DataBaseController.h"
#include "CStudentDlg.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString str[10];
int iRec = 0;

DataBaseController *Controller;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CBDDlg



CBDDlg::CBDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BD_DIALOG, pParent)
	, Path(_T("DB.mdb"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, Table);
	DDX_Text(pDX, IDC_EDIT1, Path);
}

BEGIN_MESSAGE_MAP(CBDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBDDlg::reload)
	ON_BN_CLICKED(IDC_BUTTON2, &CBDDlg::OnBnAbout)
	ON_BN_CLICKED(IDC_BUTTON3, &CBDDlg::OnBnEdit)
	ON_BN_CLICKED(IDC_BUTTON4, &CBDDlg::OnBnDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CBDDlg::OnNMDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON5, &CBDDlg::AddNewStudent)
	ON_BN_CLICKED(IDC_BUTTON6, &CBDDlg::ShowAll)
	ON_BN_CLICKED(IDC_BUTTON7, &CBDDlg::Show3)
	ON_BN_CLICKED(IDC_BUTTON8, &CBDDlg::Show4)
	ON_BN_CLICKED(IDC_BUTTON9, &CBDDlg::Show5)
END_MESSAGE_MAP()

// Обработчики сообщений CBDDlg

BOOL CBDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	Controller = new DataBaseController(L"DB.mdb", Table);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CBDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CBDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CBDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBDDlg::reload()
{
	UpdateData();

	Controller->init(Path);
}

void CBDDlg::OnBnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CBDDlg::OnBnEdit()
{
	pos = Table.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(L"No item were selected!");
	}
	else
	{
		CStudentDlg dlg;

		int nItem = Table.GetNextSelectedItem(pos);

		dlg.ID = Table.GetItemText(nItem, 0);
		dlg.F = Table.GetItemText(nItem, 1);
		dlg.I = Table.GetItemText(nItem, 2);
		dlg.O = Table.GetItemText(nItem, 3);
		dlg.SetData(Table.GetItemText(nItem, 4));
		dlg.GP = Table.GetItemText(nItem, 5);
		dlg.NS = Table.GetItemText(nItem, 6);

		Controller->getSession(dlg.ID);
		dlg.List = Controller->getLists(&dlg.Len1, &dlg.Len2, &dlg, dlg.ID);

		dlg.NameFile = Path;

		dlg.DoModal();

		if (dlg.changed) {
			Controller->init(Path);
		}

		Table.SetItemState(nItem, 0, LVIS_SELECTED);
	}
}


void CBDDlg::OnBnDelete()
{
	pos = Table.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(L"No item were selected!");
	}
	else
	{
		int nItem = Table.GetNextSelectedItem(pos);

		Controller->delStudent(Table.GetItemText(nItem, 0));

		Controller->init(Path);

		Table.SetItemState(nItem, 0, LVIS_SELECTED);
	}
}


void CBDDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;

	pos = Table.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(L"No item were selected!");
	}
	else
	{
		CStudentDlg dlg;

		int nItem = Table.GetNextSelectedItem(pos);

		dlg.ID = Table.GetItemText(nItem, 0);
		dlg.F = Table.GetItemText(nItem, 1);
		dlg.I = Table.GetItemText(nItem, 2);
		dlg.O = Table.GetItemText(nItem, 3);
		dlg.SetData(Table.GetItemText(nItem, 4));
		dlg.GP = Table.GetItemText(nItem, 5);
		dlg.NS = Table.GetItemText(nItem, 6);

		Controller->getSession(dlg.ID);
		dlg.List = Controller->getLists(&dlg.Len1, &dlg.Len2, &dlg, dlg.ID);

		dlg.NameFile = Path;

		dlg.DoModal();

		if (dlg.changed) {
			Controller->init(Path);
		}

		Table.SetItemState(nItem, 0, LVIS_SELECTED);
	}
}


void CBDDlg::AddNewStudent()
{
	CStudentDlg dlg;

	dlg.ID.Format(L"%d",(Controller->size + 1));
	dlg.F = L"";
	dlg.I = L"";
	dlg.O = L"";
	dlg.GP = L"2017";
	dlg.NS = L"";
	dlg.adding = true;

	Controller->addSession();
	dlg.List = Controller->getLists(&dlg.Len1, &dlg.Len2, &dlg);
	dlg.NameFile = Path;

	dlg.DoModal();

	if (dlg.changed) {
		Controller->init(Path);
	}
}


void CBDDlg::ShowAll()
{
	Controller->Trigger = 0;

	Controller->init(Path);
}


void CBDDlg::Show3()
{
	UpdateData();

	Controller->Trigger = 3;
	Controller->init(Path);
}


void CBDDlg::Show4()
{
	UpdateData();

	Controller->Trigger = 4;

	Controller->init(Path);
}


void CBDDlg::Show5()
{
	UpdateData();

	Controller->Trigger = 5;

	Controller->init(Path);
}
