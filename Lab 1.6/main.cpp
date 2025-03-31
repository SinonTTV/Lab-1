//**Стиль класу : вирівнювання клієнтської області по горизонталі монітора, перерисовка вікна при зміні вертикального розміру;**
//Посилати повідомлення віконної процедури при подвійному натисканні миші, якщо курсор знаходиться в межах вікна.
//Тип завантажується іконки : IDI_INFORMATION.
//Тип завантажується курсору : IDC_NO.
//Колір фону вікна : БІЛИЙ.
//Ім’я класу вікна : прізвище студента(англійською мовою).
//Стиль вікна : створюється спочатку мінімізоване вікно; у вікна є заголовок та рамка.
//Позиція вікна : по верхньому краю екрану шириною 400 точок і висотою 500 точок.
//У ресурсний файл помістити іконку, курсор і рядок тексту.За допомогою меню організувати зміну заголовка вікна, курсору та іконки програми.
//Програма повинна містити меню, в якому є пункт «Про програму», вибравши який, визивається діалогове вікно з інформацією про студента.
//Діалогове вікно повинно містити 3 кнопки : «ОК», «Закрити», «Докладніше».
//При натисканні кнопки закриття програми користувачеві повинно виводитись спливаюче вікно з запитом на підтвердження закриття вікна, 
//що міститиме текст «Ви впевнені ? » та 2 кнопки : «Так, закрити все одно» та «Ні, продовжити роботу».Натискання кнопки «Так, 
//закрити все одно» повинно призводити до закриття програми.

#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR AndriyenkoSavchenkoPogorelyi = L"QWERTY";
LPCTSTR szTitle = L"Window";
TCHAR buff[50];
HACCEL hAccel;
HWND hWnd;

// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Основна програма 
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
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
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); //визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//визначення меню
	wcex.lpszClassName = AndriyenkoSavchenkoPogorelyi; 		//ім’я класу
	wcex.hIconSm = NULL;


	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)

{
	HWND hWnd;
	// Вирівнюваня по цетру монітора
	int screenWidth = GetSystemMetrics(SM_CXSCREEN); //ширина екрану
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN); //висота екрану
	int windowWidth = 400; //ширина вікна
	int windowHeight = 500; //висота вікна

	int xPos = (screenWidth - windowWidth) / 2; //початкове положення вікна по Х
	int yPos = (ScreenHeight - windowHeight) / 2; //початкове положення вікна по Y


	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(AndriyenkoSavchenkoPogorelyi,  // ім’я класу вікна
		szTitle,  // назва програми
		WS_OVERLAPPEDWINDOW,  // стиль вікна
		xPos,  // положення по Х
		yPos,  // положення по Y
		windowWidth,  // розмір по Х
		windowHeight,  // розмір по Y
		NULL,  // дескриптор батьківського вікна
		NULL,  // дескриптор меню вікна
		hInstance,  // дескриптор програми
		NULL);  // параметри створення.


	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWMINIMIZED); //Показати вікно мінімізованим
	UpdateWindow(hWnd);					//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{

	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		break;


	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		DrawText(hdc, L"Helo, world!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDBLCLK: //Подвійне натискання лівої кнопки миші

		MessageBox(hWnd, L"Подвійне натисканя", L"Подія", MB_OK);
		break;
		//Обробка меню 
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

			//Змінити Курсор
		case  ID_CHANGE_CURSOR:
			SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)LoadCursor(hInst, MAKEINTRESOURCE(IDC_NO)));
			break;

			//Змінити Іконку
		case ID_CHANGE_ICON:
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_INFORMATION)));
			break;

			//Змінити Заголовок
		case ID_CHANGE_HEADLINE:
			LoadString(hInst, IDS_STRING107, buff, 50);
			SetWindowText(hWnd, buff);
			break;

			//Вивід діалогового вікна
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
		if (MessageBox(hWnd, L"Ви впевнені?", L"Підтвердити вихід", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hWnd);
		}

		break;

			default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// FUNCTION: AboutDialogProc (HWND, UINT, WPARAM, LPARAM)
// Процедура обробки діалогового вікна "Про програму"
INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK: // Кнопка "ОК"
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDCANCEL: // Кнопка "Закрити"
			SendMessage(GetParent(hDlg), WM_CLOSE, 0, 0);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDC_DETAILS: // Кнопка "Докладніше"
			MessageBox(hDlg, L"Це тестова програма, зроблена для WinAPI.", L"Докладніше", MB_OK | MB_ICONINFORMATION);
			return TRUE;
		}
		break;
	}
	return FALSE;
}





