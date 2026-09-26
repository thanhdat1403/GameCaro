#pragma once
#include <Windows.h>
#include <iostream>

class Screen {
	HANDLE hwnd;
public:
	Screen() {
		hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	Screen& SetCursorPos(int x, int y) {
		COORD pt = { SHORT(x), SHORT(y) };
		SetConsoleCursorPosition(hwnd, pt);

		return *this;
	}

	Screen& SetColor(int text, int background = 0) {
		SetConsoleTextAttribute(hwnd, (background << 4) | text);
		return *this;
	}

	Screen& ShowCursor(bool b = true) {
		CONSOLE_CURSOR_INFO i;
		GetConsoleCursorInfo(hwnd, &i);

		i.bVisible = b;
		SetConsoleCursorInfo(hwnd, &i);

		return *this;
	}



	template<class T>
	Screen& Write(const T& value) {
		std::cout << value;
		return *this;
	}


};