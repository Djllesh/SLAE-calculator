#include "Scenario.h"
Scenario::Scenario()
{
	scr = Screen();//��������� ������ ����� 
}

void Scenario::FromFile(HANDLE h, const string& filename)
{
	scr = Screen(Matrix(filename));//��������� �����, ������� � ����� - ���������� ��'���, ������� � �����
	scr.ChangePrecision(prec);//������������ �������
	scr.Grid(h, 1);//������� �� ����������
	system("pause");
  	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);
	else scr.Solve(h);
}

void Scenario::FromInput(HANDLE h, istream& input)
{
	scr = Screen(Matrix(input));//��������� �����, ������� � ����� - ���������� ��'���, ������� � ������
	scr.ChangePrecision(prec);//������������ �������
	scr.Grid(h, 1);//������� �� ����������
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//���� ����� - ������� ���������
	else scr.Solve(h);					 //���� � - ������ ������� 	
}


void Scenario::FromMatrix(HANDLE h, const Matrix& m)
{
	scr = Screen(Matrix(m));//��������� �����, ������� � ����� - ���������� ��'���, ������� � ����
	scr.ChangePrecision(prec);//������������ �������
	scr.Grid(h, 1);//������� �� ����������
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//���� ����� - ������� ���������
	else scr.Solve(h);					 //���� � - ������ ������� 	
}


void Scenario::Generate(HANDLE h)
{
	scr = Screen(Matrix(cin, 1));//��������� �����, ������� � ����� - ���������� ��'���, ����������� ���������
	scr.ChangePrecision(prec);//������������ �������
	scr.Grid(h, 1);//������� �� ����������
	system("pause");
	system("CLS");
	if (scr.ToAnalyze()) scr.SolveSbS(h);//���� ����� - ������� ���������
	else scr.Solve(h);					 //���� � - ������ ������� 	
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
	prec = new_prec;//���� ������� 
}
