//p232 6-1대화상자 만들기, p239 6-2버튼 컨트롤 이용하기, p242 6-3버튼 컨트롤 활상화&비활성화하기
//p253 6-4에디트 컨트롤에 문자열 복사하기, p256 6-5체크박스와 라디오 버튼 이용
//p265 6-6콤보 박스 컨트롤, 6-7리스트 박스 컨트롤, 6-8모덜리스 대화상자, 6-9~6-13리스트 컨트롤

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_3Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_4Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_5Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_6Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_7Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_8Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_9Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
void MakeColumn(HWND hDlg);
void InsertData(HWND hDlg);
int SelectItem(HWND hDlg, LPARAM lParam);
void ModifyItem(HWND hDlg, int selection);
void DeleteItem(HWND hDlg, int selection);


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
	HWND hDlg_8 = NULL;
	HWND hDlg_9 = NULL;
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
		case ID_6_6_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_6), hwnd, Dlg6_6Proc);
			break;
		case ID_6_7_MENU:
			DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_7), hwnd, Dlg6_7Proc);
			break;
		case ID_6_8_MENU:
			if (!IsWindow(hDlg_8)) {
				hDlg_8 = CreateDialog(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_7), hwnd, Dlg6_8Proc);
				ShowWindow(hDlg_8, SW_SHOW);
			}
			break;
		case ID_6_9_MENU:
			if (!IsWindow(hDlg_9)) {
				hDlg_9 = CreateDialog(g_hinst, MAKEINTRESOURCE(IDD_DIALOG6_9), hwnd, Dlg6_9Proc);
				ShowWindow(hDlg_9, SW_SHOW);
			}
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

//p255 엔터처리? 차라리 키다운?
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
	TCHAR hobby[][30] = { _T("독서"), _T("음악감상"), _T("인터넷") };
	TCHAR sex[][30] = { _T("여자"), _T("남자") };
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
			_stprintf_s(output, _T("선택한 취미는 %s %s %s 입니다.\r\n")_T("선택한 성별은 %s입니다."), Check[0] ? hobby[0] : _T(""), Check[1] ? hobby[1] : _T(""), Check[2]
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

//CB 작동 X -> 안나오던 이유: 콤보박스 세로길이가 작았음. 콤보박스 세로길이는 콤보박스펼쳤을때를 포함. 보이지 않기때문에 삽입, 삭제가 안되는거라 생각한듯.
BOOL CALLBACK Dlg6_6Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hCombo;
	static int selection;
	TCHAR name[20];

	switch (iMsg) {
	case WM_INITDIALOG:
		hCombo = GetDlgItem(hDlg, IDC_COMBO_LIST);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)name);
			return 0;
		case IDC_BUTTON_DELETE:
			SendMessage(hCombo, CB_DELETESTRING, selection, 0);
			return 0;
		case IDC_COMBO_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			break;
		case IDCLOSE:
			EndDialog(hDlg, 0);
			return 0;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 0;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK Dlg6_7Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND	hList;
	static int	selection;
	TCHAR		name[20];

	switch (iMsg) {
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST_NAME);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name);
			return 0;
		case IDC_BUTTON_DELETE:
			SendMessage(hList, LB_DELETESTRING, selection, 0);
			return 0;
		case IDC_LIST_NAME:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				selection = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case IDCLOSE:
			EndDialog(hDlg, 0);
			return 0;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return 0;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK Dlg6_8Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HWND	hList;
	static int	selection;
	TCHAR		name[20];

	switch (iMsg) {
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST_NAME);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_INSERT:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			if (_tcscmp(name, _T("")))
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name);
			return 0;
		case IDC_BUTTON_DELETE:
			SendMessage(hList, LB_DELETESTRING, selection, 0);
			return 0;
		case IDC_LIST_NAME:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				selection = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case IDCLOSE:
			DestroyWindow(hDlg);
			EndDialog(hDlg, 0);
			return 0;
		case IDCANCEL:
			DestroyWindow(hDlg);
			EndDialog(hDlg, 0);
			return 0;
		}
		break;
	}
	return 0;
}

#define UNSELECTED -1
BOOL CALLBACK Dlg6_9Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	LPNMHDR		hdr;
	HWND		hList;
	static int	selection;

	switch (iMsg) {
	case WM_INITDIALOG:
		selection = UNSELECTED;
		MakeColumn(hDlg);
		return 1;
	case WM_NOTIFY:
		hdr = (LPNMHDR)lParam;
		hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
		if (hdr->hwndFrom == hList && hdr->code == LVN_ITEMCHANGING) 
			selection = SelectItem(hDlg, lParam);
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_INSERT:
			InsertData(hDlg);
			return 0;
		case IDC_BUTTON_MODIFY:
			if (selection == UNSELECTED) break;
			ModifyItem(hDlg, selection);
			selection = UNSELECTED;
			return 0;
		case IDC_BUTTON_DELETE2:
			if (selection == UNSELECTED) break;
			DeleteItem(hDlg, selection);
			selection = UNSELECTED;
			return 0;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}

void MakeColumn(HWND hDlg) {
	LPTSTR		name[2] = { (LPTSTR)_T("이름"), (LPTSTR)_T("전화번호") };
	LVCOLUMN	lvCol = { 0, };
	HWND		hList;
	int			i;
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;

	for (i = 0; i < 2; i++) {
		lvCol.cx = 90;
		lvCol.iSubItem = i;
		lvCol.pszText = name[i];
		SendMessage(hList, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvCol);
	}
}

void InsertData(HWND hDlg) {
	int			count;
	LVITEM		item;
	HWND		hList;
	TCHAR		name[20], phone[20];

	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	if (_tcscmp(name, _T("")) == 0) return;
	GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	count = ListView_GetItemCount(hList);
	item.mask = LVIF_TEXT;
	item.iItem = count;
	item.iSubItem = 0;
	item.pszText = name;
	ListView_InsertItem(hList, &item);
	ListView_SetItemText(hList, count, 1, phone);
}

int SelectItem(HWND hDlg, LPARAM lParam) {
	LPNMLISTVIEW		nlv;
	HWND				hList;
	TCHAR				name[20], phone[20];
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	nlv = (LPNMLISTVIEW)lParam;
	ListView_GetItemText(hList, nlv->iItem, 0, name, 20);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, name);
	ListView_GetItemText(hList, nlv->iItem, 1, phone, 20);
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, phone);
	return (nlv->iItem);
}

void ModifyItem(HWND hDlg, int selection) {
	static HWND		hList;
	TCHAR			name[20], phone[20];

	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
	GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 20);
	if (_tcscmp(name, _T("")) == 0) return;
	ListView_SetItemText(hList, selection, 0, name);
	ListView_SetItemText(hList, selection, 1, phone);
	if (_tcscmp(name, _T("")) == 0) return;
	ListView_SetItemText(hList, selection, 0, name);
	ListView_SetItemText(hList, selection, 1, phone);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));
	return;
}
void DeleteItem(HWND hDlg, int selection) {
	static HWND hList;
	hList = GetDlgItem(hDlg, IDC_LIST_MEMBER);
	ListView_DeleteItem(hList, selection);
	SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
	SetDlgItemText(hDlg, IDC_EDIT_PHONE, _T(""));
	return;
}