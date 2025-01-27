#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <commctrl.h>
#include <string.h>
#include <stdio.h>
#include "../include/main.h"
#include "../include/ID.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0; 
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void addMenu(HWND parenthwnd, LPWSTR language)
{
	HMENU hMenubar = CreateMenu();
	HMENU hDataMenu = CreateMenu();
	HMENU hOptionMenu = CreateMenu();
	HMENU hDefTabMenu = CreateMenu();
	HMENU hViewMenu = CreateMenu();
	HMENU hUpdateTimeMenu = CreateMenu();
	if (language == L"german")
	{
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hDataMenu, L"Datei");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hOptionMenu, L"Optionen");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hViewMenu, L"Ansicht");

		/*Stuff for Data-Menu*/
		AppendMenu(hDataMenu, MF_STRING, MENU_DATA_NEW_TASK_ID, L"Neuen Task ausfuehren");
		AppendMenu(hDataMenu, MF_STRING, MENU_DATA_EXIT_ID, L"Beenden");

		/*Stuff for Option-Menu*/
		AppendMenu(hOptionMenu, MF_STRING, MENU_OPT_ALWAYS_PRIO_ID, L"Immer im Vordergrund");
		AppendMenu(hOptionMenu, MF_STRING, MENU_OPT_MIN_START_ID, L"Nach Programmstart minimieren");
		AppendMenu(hOptionMenu, MF_STRING, MENU_OPT_CLOSE_MIN_ID, L"Ausblenden, wenn minimiert");
		AppendMenu(hOptionMenu, MF_POPUP, (UINT_PTR)hDefTabMenu, L"Standartregisterkarte festlegen");

		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_PROC, L"Prozesse");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_POW, L"Leistung");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_HIST, L"APP-Verlauf");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_AST, L"Autostart");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_USR, L"Benutzer");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_DET, L"Details");
		AppendMenu(hDefTabMenu, MF_STRING, MENU_OPT_TAB_SER, L"Dienste");

		AppendMenuW(hOptionMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hOptionMenu, MF_STRING | MF_DISABLED, MENU_OPT_FULL_ACN, L"Vollstaendigen Kontonamen anzeigen");
		AppendMenuW(hOptionMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hOptionMenu, MF_STRING | MF_DISABLED, MENU_OPT_FULL_PROG_HIST, L"Verlauf fuer alle Prozesse anzeigen");

		AppendMenu(hViewMenu, MF_STRING, MENU_VIEW_UPTD_NOW_ID, L"Jetzt aktualisieren");
		AppendMenu(hViewMenu, MF_POPUP, (UINT_PTR)hUpdateTimeMenu, L"Aktualisierungsgeschwindigkeit");

		AppendMenu(hUpdateTimeMenu, MF_STRING, MENU_VIEW_SPD_HIGH_ID, L"Hoch");
		AppendMenu(hUpdateTimeMenu, MF_STRING, MENU_VIEW_SPD_NORM_ID, L"Normal");
		AppendMenu(hUpdateTimeMenu, MF_STRING, MENU_VIEW_SPD_LOW_ID, L"Niedrig");
		AppendMenu(hUpdateTimeMenu, MF_STRING, MENU_VIEW_SPD_STOP_ID, L"Angehalten");
		AppendMenuW(hViewMenu, MF_SEPARATOR, 0, NULL);

		AppendMenu(hViewMenu, MF_STRING, MENU_VIEW_GRP_TYPE_ID, L"Nach Typ gruppieren");
		AppendMenu(hViewMenu, MF_STRING, MENU_VIEW_EXP_ALL_ID, L"Alle erweitern");
		AppendMenu(hViewMenu, MF_STRING, MENU_VIEW_DECR_ALL_ID, L"Alle reduzieren");
	}

	SetMenu(parenthwnd, hMenubar);
}

void addTabItem(HWND Tabhwnd, LPWSTR name, TCITEM item, INT16 position)
{
	item.pszText = name;
	TabCtrl_InsertItem(Tabhwnd, position, &item);
}

HWND createTabControl(HWND parenthwnd, HINSTANCE hInstance, RECT rcClient)
{
	GetClientRect(parenthwnd, &rcClient);
	HWND hWndTAB = CreateWindow(WC_TABCONTROL, L"", WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, rcClient.right, rcClient.bottom, parenthwnd, (HMENU)TAB_CONTOL_ID, hInstance, NULL);

	return hWndTAB;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	HWND Button;
	WNDCLASS windowClass;
	MSG msg;

	/*Stuff for Tab-Control*/
	INITCOMMONCONTROLSEX icex;
	HWND hWndTAB;
	RECT rcClient;
	TCITEM tie;

	ZeroMemory(&windowClass, sizeof(WNDCLASS));

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszClassName = L"WINAPI_Test";

	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL, L"Failed to register window class.", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	hWnd = CreateWindow(L"WINAPI_Test", L"Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	
	InitCommonControlsEx(&icex);
	
	hWndTAB = createTabControl(hWnd, hInstance, rcClient);

	/*Initialize stuff for Tab-Control*/
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;

	if (!hWnd || !hWndTAB)
	{
		MessageBox(NULL, L"Failed to create window.", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	
	/*Create Tabs*/
	tie.mask = TCIF_TEXT;
	addTabItem(hWndTAB, L"Prozesse", tie, 0);
	addTabItem(hWndTAB, L"Leistung", tie, 1);
	addTabItem(hWndTAB, L"App-Verlauf", tie, 2);
	addTabItem(hWndTAB, L"Autostart", tie, 3);
	addTabItem(hWndTAB, L"Benutzer", tie, 4);
	addTabItem(hWndTAB, L"Details", tie, 5);
	addTabItem(hWndTAB, L"Dienste", tie, 6);

	addMenu(hWnd, L"german");

	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	UpdateWindow(hWnd);

	while (TRUE)
	{
		BOOL result = GetMessage(&msg, NULL, 0, 0);
		if ( result > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return result;
		}
	}
	
	return 0;
}