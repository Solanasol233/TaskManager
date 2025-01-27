#pragma once

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void addTabItem(HWND Tabhwnd, LPWSTR name, TCITEM item, INT16 position);
HWND createTabControl(HWND parenthwnd, HINSTANCE hInstance, RECT rcClient);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void addMenu(HWND parenthwnd, LPWSTR language);