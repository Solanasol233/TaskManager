#include <windows.h>
#include <commctrl.h>
#define BUTTON_1_ID 101


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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	HWND Button;
	WNDCLASS windowClass;
	MSG msg;

	ZeroMemory(&windowClass, sizeof(WNDCLASS));

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszClassName = "WINAPI_Test";
	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL, "Failed to register window class.", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	hWnd = CreateWindow("WINAPI_Test", "Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	Button = CreateWindow("button", "Drücken!", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 70, 200, 50, hWnd, (HMENU)BUTTON_1_ID, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, "Failed to create window.", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}
	
	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
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