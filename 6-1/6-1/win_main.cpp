//p232 6-1대화상자 만들기, p239 6-2버튼 컨트롤 이용하기, p242 6-3버튼 컨트롤 활상화&비활성화하기

#include <Windows.h>
#include <tchar.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hinst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	g_hinst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_CREATE:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_6_1_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_1), hwnd, Dlg6_1Proc);
			break;
		case ID_6_2_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_2), hwnd, Dlg6_2Proc);
			break;
		case ID_6_3_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_3), hwnd, Dlg6_3Proc);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON_PRINT:
			hdc = GetDC(hDlg);
			TextOut(hdc, 0, 0, _T("Hello World"), 11);
			ReleaseDC(hDlg, hdc);
			break;
		case ID_BUTTON_END:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HWND hButton;
		switch (iMsg) {
		case WM_INITDIALOG:
			hButton = GetDlgItem(hDlg, ID_PAUSE);
			EnableWindow(hButton, FALSE);
			return 1;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case ID_START:
				hButton = GetDlgItem(hDlg, ID_START);
				EnableWindow(hButton, FALSE);
				hButton = GetDlgItem(hDlg, ID_PAUSE);
				EnableWindow(hButton, TRUE);
				break;
			case ID_PAUSE:
				hButton = GetDlgItem(hDlg, ID_START);
				EnableWindow(hButton, TRUE);
				hButton = GetDlgItem(hDlg, ID_PAUSE);
				EnableWindow(hButton, FALSE);
				break;
			case ID_CLOSE:
				EndDialog(hDlg, 0);
				break;
			case IDCANCEL:
				EndDialog(hDlg, 0);
				break;
			}
			break;
		}
	return 0;
}