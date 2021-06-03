#pragma once
#include "Screen.h"
/*
	Цей клас для лаконізації функції main.
    Тут всі функції та методи, які треба викликати при певному сценарії зібрані в одну купу
*/

class Scenario
{
public:
	Scenario();//немає екрану(пустий)
	void FromFile(HANDLE h, const string& filename);//зчитування системи з файлу
	void FromInput(HANDLE h, istream& input);//зчитування системи з потоку 
	void FromMatrix(HANDLE h, const Matrix& m);//зчитування системи з коду
	void Generate(HANDLE h);//генерація системи випадковими числами 
	void FullScreen(HANDLE h) const;//повноекранний режим
	void WindowMode(HANDLE h) const;//віконний режим 
	void ChangePrecision(int new_prec);//змінити точність 
private:
	Screen scr;//екран 
	int prec = 3;//точність 
};

