#include "Scenario.h"
Scenario::Scenario()
{
	scr = Screen();//створюЇмо пустий екран 
}

void Scenario::FromFile(HANDLE h, const string& filename)
{
	scr = Screen(Matrix(filename));//створюЇмо екран, матриц€ в ньому - тимчасовий об'Їкт, зчитана з файлу
	scr.ChangePrecision(prec);//встановлюЇмо точн≥сть
	scr.Grid(h, 1);//малюЇмо та заповнюЇмо
	system("pause");
  	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);
	else scr.Solve(h);
}

void Scenario::FromInput(HANDLE h, istream& input)
{
	scr = Screen(Matrix(input));//створюЇмо екран, матриц€ в ньому - тимчасовий об'Їкт, зчитана з потоку
	scr.ChangePrecision(prec);//встановлюЇмо точн≥сть
	scr.Grid(h, 1);//малюЇмо та заповнюЇмо
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//€кщо треба - вир≥шуЇмо покроково
	else scr.Solve(h);					 //€кщо н≥ - просто вир≥шуЇмо 	
}


void Scenario::FromMatrix(HANDLE h, const Matrix& m)
{
	scr = Screen(Matrix(m));//створюЇмо екран, матриц€ в ньому - тимчасовий об'Їкт, зчитана з коду
	scr.ChangePrecision(prec);//встановлюЇмо точн≥сть
	scr.Grid(h, 1);//малюЇмо та заповнюЇмо
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//€кщо треба - вир≥шуЇмо покроково
	else scr.Solve(h);					 //€кщо н≥ - просто вир≥шуЇмо 	
}


void Scenario::Generate(HANDLE h)
{
	scr = Screen(Matrix(cin, 1));//створюЇмо екран, матриц€ в ньому - тимчасовий об'Їкт, згенерована самост≥йно
	scr.ChangePrecision(prec);//встановлюЇмо точн≥сть
	scr.Grid(h, 1);//малюЇмо та заповнюЇмо
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//€кщо треба - вир≥шуЇмо покроково
	else scr.Solve(h);					 //€кщо н≥ - просто вир≥шуЇмо 	
}

void Scenario::FullScreen(HANDLE h) const
{
	scr.FullScreen(h);
}

void Scenario::WindowMode(HANDLE h) const
{
	scr.WindowMode(h);
}

void Scenario::ChangePrecision(int new_prec)
{
	prec = new_prec;//нова точн≥сть 
}
