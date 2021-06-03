#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include "Matrix.h"

/*
	��� ���� ������� �� ���� ������� �� �����, �������� ������������
*/
using namespace std;

class Screen
{
public:
	void Resize(const Matrix& m); //����� �������, �� ������ ��������
	Screen();//����������� �� �����������
	Screen(const Matrix& m) : matrix(m) { Resize(m); } //����� ������ ����� ����������� �������, �������� �� ������������
	void Bond(HANDLE h, COORD t, COORD b) const;  //����� �����
	void Vertical_line(HANDLE h, COORD top, size_t lenght, char c = 442) const; //����� ����������� ���
	void Horizontal_line(HANDLE h, COORD top, size_t lenght, char c = 442) const; //����� ������������� ���
	void Diagonal(HANDLE h, COORD top, size_t lenght, char c) const;        // �� �������, ���� �� ����������� ���� ��
	void Inverse_diagonal(HANDLE h, COORD bot, size_t lenght, char c) const; //
	void Grid(HANDLE h, bool to_fill = false); //������� ������ ���� � ��������
	void Fill(HANDLE h) const; //�������� ���� ���������� �������
	void FullScreen(HANDLE h) const; //�������� ���� �� ������ �����
	void WindowMode(HANDLE h) const; //������ � ����
	void ChangePrecision(int new_prec); //����� ������� ����� ���� ����
	void SetConsecutive(bool c); //���������� ����� consecutive 
	void ConsecutiveGrid(HANDLE h, bool to_fill); //����� ���� ���������(���� �� �����)
	void Solve(HANDLE h); //����� ������� � �������� �� �����
	void SolveSbS(HANDLE h);//����� ������� � �������� �� ����� �� �����
	~Screen();//����� ����� 
	void ShowAnswer() const;//������ �������
	bool ToAnalyze() const { return matrix.ToAnalyze(); }//������ to_analyze 
	COORD GetCurrentPos() const { return current_pos; }//������ current_pos

private: 
	struct ScreenSettings //��������� ����������� ������ (���������� ��� ������ � �������)
	{
		COORD top = {-1,-1}; //������� ������
		COORD Size = { -1,-1 }; //����� ������ � - ������, � - ������
		COORD line_top = { -1,-1 }; //������� ���, ��� ������� ������� ������� �� ��������� ������ �����
		COORD digit_place = { -1,-1 }; //���������� �����, ������� ������� ������ 
		COORD free_place = { -1,-1 }; //���������� ����� � ��������� ������ ����� ������� ������� ������
		int precision = 3; //������� ����� ���� ����
		bool consecutive = false; //�� ����� �������� ��������� 
	};
	COORD current_pos = {0,0};//������� ������� ������� 
	Matrix matrix; //�������, � ��� ����������� �� ���
	ScreenSettings settings; //�������� �����, ��� �������� �������� ������ �� ����������� ������
};
