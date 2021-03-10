//p232 6-1��ȭ���� �����, p239 6-2��ư ��Ʈ�� �̿��ϱ�, p242 6-3��ư ��Ʈ�� Ȱ��ȭ&��Ȱ��ȭ�ϱ�
//p253 6-4����Ʈ ��Ʈ�ѿ� ���ڿ� �����ϱ�, p256 6-5üũ�ڽ��� ���� ��ư �̿�

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

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
		case ID_6_4_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_4), hwnd, Dlg6_4Proc);
			break;
		case ID_6_5_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_5), hwnd, Dlg6_5Proc);
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

//p255 ����ó��? ���� Ű�ٿ�?
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

BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR word[100];

	switch (iMsg) {
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON_COPY:
			GetDlgItemText(hDlg, IDC_EDIT_SOURCE, word, 100);
			SetDlgItemText(hDlg, IDC_EDIT_COPY, word);
			break;
		case ID_BUTTON_CLEAR:
			SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
			SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
			break;
		case ID_BUTTON_END:
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

BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int Check[3], Radio;
	TCHAR hobby[][30] = { _T("����"), _T("���ǰ���"), _T("���ͳ�") };
	TCHAR sex[][30] = { _T("����"), _T("����") };
	TCHAR output[200];

	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_MALE, IDC_RADIO_FEMALE, IDC_RADIO_MALE);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_CHECK_READING:
			Check[0] = 1 - Check[0];
			break;
		case IDC_CHECK_MUSIC:
			Check[1] = 1 - Check[1];
			break;
		case IDC_CHECK_INTERNET:
			Check[2] = 1 - Check[2];
			break;
		case IDC_RADIO_FEMALE:
			Radio = 0;
			break;
		case IDC_RADIO_MALE:
			Radio = 1;
			break;
		case IDC_BUTTON_OUTPUT:
			_stprintf_s(output, _T("������ ��̴� %s %s %s �Դϴ�.\r\n")_T("������ ������ %s�Դϴ�."), Check[0] ? hobby[0] : _T(""), Check[1] ? hobby[1] : _T(""), Check[2]
				? hobby[2] : _T(""), sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case IDC_BUTTON_CLOSE:
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