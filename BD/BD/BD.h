
// BD.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CBDApp:
// Сведения о реализации этого класса: BD.cpp
//

class CBDApp : public CWinApp
{
public:
	CBDApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CBDApp theApp;
