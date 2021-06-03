#pragma once
#include "Screen.h"
/*
	��� ���� ��� ���������� ������� main.
    ��� �� ������� �� ������, �� ����� ��������� ��� ������� ������ ����� � ���� ����
*/

class Scenario
{
public:
	Scenario();//���� ������(������)
	void FromFile(HANDLE h, const string& filename);//���������� ������� � �����
	void FromInput(HANDLE h, istream& input);//���������� ������� � ������ 
	void FromMatrix(HANDLE h, const Matrix& m);//���������� ������� � ����
	void Generate(HANDLE h);//��������� ������� ����������� ������� 
	void FullScreen(HANDLE h) const;//������������� �����
	void WindowMode(HANDLE h) const;//������� ����� 
	void ChangePrecision(int new_prec);//������ ������� 
private:
	Screen scr;//����� 
	int prec = 3;//������� 
};

