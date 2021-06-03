#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include "Matrix.h"

/*
	Цей клас відповідає за друк матриці на екран, виводить прямокутники
*/
using namespace std;

class Screen
{
public:
	void Resize(const Matrix& m); //змінює матрицю, що лежить всередині
	Screen();//конструктор за замовченням
	Screen(const Matrix& m) : matrix(m) { Resize(m); } //тобто одразу пізлся ініціалізації матриці, отримуємо її налаштування
	void Bond(HANDLE h, COORD t, COORD b) const;  //малює рамку
	void Vertical_line(HANDLE h, COORD top, size_t lenght, char c = 442) const; //малює вертикальну лінію
	void Horizontal_line(HANDLE h, COORD top, size_t lenght, char c = 442) const; //малює горизонтальну лінію
	void Diagonal(HANDLE h, COORD top, size_t lenght, char c) const;        // це діагоналі, вони не знадобилися поки що
	void Inverse_diagonal(HANDLE h, COORD bot, size_t lenght, char c) const; //
	void Grid(HANDLE h, bool to_fill = false); //повністю готове поле з розміткою
	void Fill(HANDLE h) const; //заповнює поля значеннями матриці
	void FullScreen(HANDLE h) const; //розгортає вікно на повний екран
	void WindowMode(HANDLE h) const; //згортає у вікно
	void ChangePrecision(int new_prec); //змінює кількість знаків після коми
	void SetConsecutive(bool c); //встановити змінну consecutive 
	void ConsecutiveGrid(HANDLE h, bool to_fill); //малює сітку покроково(сітка за сіткою)
	void Solve(HANDLE h); //вирішує систему і виводить на екран
	void SolveSbS(HANDLE h);//вирішує систему і виводить на екран всі кроки
	~Screen();//очищує екран 
	void ShowAnswer() const;//показує відповідь
	bool ToAnalyze() const { return matrix.ToAnalyze(); }//геттер to_analyze 
	COORD GetCurrentPos() const { return current_pos; }//геттер current_pos

private: 
	struct ScreenSettings //струткура налаштувань екрану (інформація про комірки і матрицю)
	{
		COORD top = {-1,-1}; //вершина комірки
		COORD Size = { -1,-1 }; //розмір комірки х - ширина, у - висота
		COORD line_top = { -1,-1 }; //вершина лініїї, яка розділяє основну матрицю від стовпчика вільних членів
		COORD digit_place = { -1,-1 }; //координата числа, відносно вершини консолі 
		COORD free_place = { -1,-1 }; //координата числа в стовпчику вільних членів відносно вершини консолі
		int precision = 3; //кількість знаків після коми
		bool consecutive = false; //чи треба малювати покроково 
	};
	COORD current_pos = {0,0};//поточна позиція курсору 
	Matrix matrix; //матриця, в якій зберігаються всі дані
	ScreenSettings settings; //приватна змінна, яка дозволяє отримати доступ до налаштувань комірок
};
