#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


/*
	��� ���� ������� �� ���������� ��� ����, ������� ��� ��������� 
*/
const string x22 = R"(C_1_1 x_1 + C_1_2 x_2 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 = B_2)""\n";
const string x33 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 = B_3)""\n";
const string x44 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 + C_1_4 x_4 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 + C_2_4 x_4 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 + C_3_4 x_4 = B_3)""\n"
						R"(C_4_1 x_1 + C_4_2 x_2 + C_4_3 x_3 + C_4_4 x_4 = B_4)""\n";                                  //����������� ������ ���� ����� ������
const string x55 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 + C_1_4 x_4 + C_1_5 x_5 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 + C_2_4 x_4 + C_2_5 x_5 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 + C_3_4 x_4 + C_3_5 x_5 = B_3)""\n"
						R"(C_4_1 x_1 + C_4_2 x_2 + C_4_3 x_3 + C_4_4 x_4 + C_4_5 x_5 = B_4)""\n"
						R"(C_5_1 x_1 + C_5_2 x_2 + C_5_3 x_3 + C_5_4 x_4 + C_5_5 x_5 = B_5)""\n";

class Matrix
{
public:
	Matrix();
	Matrix(const vector<vector<double>>& new_matrix, const vector<double>& free_) : table(new_matrix), free(free_) // double [][N] ����������� � ���� ������� 
	{
		size = table.size();
	}
	Matrix(istream& input, bool to_generate = false);		//����������� ��� ������
	Matrix(const vector<vector<double>>& matrix_with_free);	//�����������, ���� ����������� ������� ������� ������� � �������� ������ �����
	Matrix(const string& filename);							//���������� � �����
	int Size() const { return size; } //������ ������
	vector<vector<double>> GetTable() const { return table; }//������ �������
	vector<double> GetFree() const { return free; }//������ ���������
	bool ToAnalyze() const { return to_analyze; } //������ ����� to_analyze 
	void SolveGauss(); //������� ������� ������ 
	double det(const vector<vector<double>>& arr, int rows) const; //��������� �������
	const vector<Matrix>& GetSteps() const { return sbs_matrices; } //������ ������� �����
	Matrix& operator=(const Matrix& other) //�������� ���������
	{
		this->table = other.table;
		this->free = other.free;
		this->size = other.size;
		this->to_analyze = other.to_analyze;
		return *this;
	}
private:

	int pw(int a) const;//����� ��� ���������� ����� ������������ ����������� 
	vector<vector<double>> table; //������� ��������� ������� ����������� ����
	vector<double> free; //������� ������ �����
	int size; //�����
	bool to_analyze = false; //�� ����� �����'��������� ����� 
	vector<Matrix> sbs_matrices; //������ �������, ����� � ���� - ���� � ����� �����
};
