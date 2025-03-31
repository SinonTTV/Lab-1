//**����� ����� : ����������� �볺������ ������ �� ���������� �������, ����������� ���� ��� ��� ������������� ������;**
//�������� ����������� ������ ��������� ��� ��������� ��������� ����, ���� ������ ����������� � ����� ����.
//��� ������������� ������ : IDI_INFORMATION.
//��� ������������� ������� : IDC_NO.
//���� ���� ���� : �����.
//��� ����� ���� : ������� ��������(���������� �����).
//����� ���� : ����������� �������� ��������� ����; � ���� � ��������� �� �����.
//������� ���� : �� ��������� ���� ������ ������� 400 ����� � ������� 500 �����.
//� ��������� ���� �������� ������, ������ � ����� ������.�� ��������� ���� ����������� ���� ��������� ����, ������� �� ������ ��������.
//�������� ������� ������ ����, � ����� � ����� ���� ��������, �������� ����, ���������� �������� ���� � ����������� ��� ��������.
//ĳ������� ���� ������� ������ 3 ������ : ��ʻ, ��������, ����������.
//��� ��������� ������ �������� �������� ������������ ������� ���������� ��������� ���� � ������� �� ������������ �������� ����, 
//�� �������� ����� ��� ������� ? � �� 2 ������ : ����, ������� ��� ���� �� �ͳ, ���������� ������.���������� ������ ����, 
//������� ��� ���� ������� ���������� �� �������� ��������.

#include <windows.h> // ���������� �������� � ��������� API
#include "resource.h"

// �������� ����:
HINSTANCE hInst; 	//���������� ��������	
LPCTSTR AndriyenkoSavchenkoPogorelyi = L"QWERTY";
LPCTSTR szTitle = L"Window";
TCHAR buff[50];
HACCEL hAccel;
HWND hWnd;

// ��������� ���� �������
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// ������� �������� 
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	MSG msg;

	// ��������� ����� ���� 
	MyRegisterClass(hInstance);

	// ��������� ���� ��������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ���� ������� ����������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; 		//����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//������ ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//���������� ��������
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); //���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//���������� �������
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //��������� ����
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//���������� ����
	wcex.lpszClassName = AndriyenkoSavchenkoPogorelyi; 		//��� �����
	wcex.hIconSm = NULL;


	return RegisterClassEx(&wcex); 			//��������� ����� ����
}

// FUNCTION: InitInstance (HANDLE, int)
// ������� ���� �������� � ������ ���������� �������� � ����� hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

{
	HWND hWnd;
	// ���������� �� ����� �������
	int screenWidth = GetSystemMetrics(SM_CXSCREEN); //������ ������
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN); //������ ������
	int windowWidth = 400; //������ ����
	int windowHeight = 500; //������ ����

	int xPos = (screenWidth - windowWidth) / 2; //��������� ��������� ���� �� �
	int yPos = (ScreenHeight - windowHeight) / 2; //��������� ��������� ���� �� Y


	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(AndriyenkoSavchenkoPogorelyi,  // ��� ����� ����
		szTitle,  // ����� ��������
		WS_OVERLAPPEDWINDOW,  // ����� ����
		xPos,  // ��������� �� �
		yPos,  // ��������� �� Y
		windowWidth,  // ����� �� �
		windowHeight,  // ����� �� Y
		NULL,  // ���������� ������������ ����
		NULL,  // ���������� ���� ����
		hInstance,  // ���������� ��������
		NULL);  // ��������� ���������.


	if (!hWnd) 	//���� ���� �� ���������, ������� ������� FALSE
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWMINIMIZED); //�������� ���� ����������
	UpdateWindow(hWnd);					//������� ����
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// ³����� ���������. ������ � �������� �� �����������, �� ��������� � �������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{

	case WM_CREATE: 				//����������� ��������� ��� �������� ����
		break;


	case WM_PAINT: 				//������������ ����
		hdc = BeginPaint(hWnd, &ps); 	//������ ��������� ����	
		GetClientRect(hWnd, &rt); 		//������� ���� ��� ���������
		DrawText(hdc, L"Helo, world!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//�������� ��������� ����	
		break;

	case WM_DESTROY: 				//���������� ������
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDBLCLK: //������� ���������� ��� ������ ����

		MessageBox(hWnd, L"������� ���������", L"����", MB_OK);
		break;
		//������� ���� 
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

			//������ ������
		case  ID_CHANGE_CURSOR:
			SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)LoadCursor(hInst, MAKEINTRESOURCE(IDC_NO)));
			break;

			//������ ������
		case ID_CHANGE_ICON:
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_INFORMATION)));
			break;

			//������ ���������
		case ID_CHANGE_HEADLINE:
			LoadString(hInst, IDS_STRING107, buff, 50);
			SetWindowText(hWnd, buff);
			break;

			//���� ���������� ����
		case ID_ABOUT_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT_DIALOG), hWnd, AboutDialogProc);
			break;

		case IDOK:
			break;
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, L"�� �������?", L"ϳ��������� �����", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hWnd);
		}

		break;

			default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// FUNCTION: AboutDialogProc (HWND, UINT, WPARAM, LPARAM)
// ��������� ������� ���������� ���� "��� ��������"
INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK: // ������ "��"
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDCANCEL: // ������ "�������"
			SendMessage(GetParent(hDlg), WM_CLOSE, 0, 0);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDC_DETAILS: // ������ "���������"
			MessageBox(hDlg, L"�� ������� ��������, �������� ��� WinAPI.", L"���������", MB_OK | MB_ICONINFORMATION);
			return TRUE;
		}
		break;
	}
	return FALSE;
}





