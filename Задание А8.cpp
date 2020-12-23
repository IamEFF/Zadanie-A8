#include<Windows.h> //Подключение библиотек
#include<windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//Объявление функции WndPro(что будет происходить в окне)
HPEN hRedPen, hBluePen;//Объявление глобальных переменных ручек
HBRUSH hRedBrush, hBlueBrush;//Объявление глобальных переменных кистей
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { //Главная функция инициализации всего проекта(без нее не будет работать ничего
	HWND hMainWnd; //Дескриптор главного окна программы
	TCHAR szClassName[] = _T("MyClass");//Объявление переменной с именем класса
	MSG msg;//Структура для хранения сообщения
	WNDCLASSEX wc;//Объявление переменной класса вызывающего окно
	//Определение класса окна
	wc.cbSize = sizeof(wc);//Установка размера окна
	wc.style = CS_HREDRAW | CS_VREDRAW;//Задает стиль класса окна
	wc.lpfnWndProc = WndProc;//Имя класса окна
	wc.cbClsExtra = 0;//Нет дополнительных данных класса
	wc.cbWndExtra = 0;//Нет дополнительных данных класса
	wc.hInstance = hInstance;//Инициализация приложения
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Инициализация иконки приложения
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Инициализация курсора приложения
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));////Инициализация заднего фона приложения
	wc.lpszMenuName = NULL;//Нет меню
	wc.lpszClassName = szClassName;//Имя класса окна
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//Инициализация иконки приложения
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}//Регистрация класса окна
	hMainWnd = CreateWindow(szClassName, _T("Задание A8"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);//Создание окна

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}//Вывод ошибки, если не удалось создать окно
	ShowWindow(hMainWnd, nCmdShow);//Показать окно
		//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessageW(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;//Освобождвет память(Прекращает работу всей программы
}

//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;//Экземпляр контекста устройства для нужной ориентации текста в окне
	PAINTSTRUCT ps;//Структура информация об окне для прорисовки
	switch (uMsg) {//Оператор множественного выбора
	case WM_CREATE://Создание основного окна
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));//Создаем ручку
		hBluePen = CreatePen(PS_SOLID, 4, RGB(0, 0, 150));//Создаем ручку
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));//Создаем кисть
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));//Создаем кисть
		break;//Остановка кейса
	case WM_PAINT://Создание процесса рисования
		hdc = BeginPaint(hWnd, &ps);//Начало рисования
		SetBkColor(hdc, RGB(200, 200, 100));//Установка заднего фона
		SelectPen(hdc, hBluePen);//Выбор ручки
		SelectBrush(hdc, hBlueBrush);//Выбор кисти
		Chord(hdc, 0, 0, 200, 200, 200, 100, 0, 100);//Создание полукруга
		SelectPen(hdc, hRedPen);//Выбор ручки
		SelectBrush(hdc, hRedBrush);//Выбор кисти
		Chord(hdc, 0, 0, 200, 200, 0, 100, 200, 100);//Создание полукруга
		EndPaint(hWnd, &ps);//Конец рисования
		break;//Остановка кейса
	case WM_DESTROY://Условие закрытия окна
		DeleteObject(hRedPen);//Удаляем ручку
		DeleteObject(hBluePen);//Удаляем ручку
		DeleteObject(hRedBrush);//Удаляем кисть
		DeleteObject(hBlueBrush);//Удаляем кисть
		PostQuitMessage(0);//Отправка в главный процесс о том, что окно закрыто(отправляем WinMain() сообщение WM_QUIT)
		break;//Остановка кейса
	default://Значение по умолчанию у оператора множественного выбора
		return DefWindowProc(hWnd, uMsg, wParam, lParam);//Если закрыли окно
	}
	return 0;// Возвращаем значение функции

}
