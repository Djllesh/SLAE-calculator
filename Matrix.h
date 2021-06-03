#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


/*
	Цей клас відповідає за інформацію про СЛАР, потрібен для обрахунків 
*/
const string x22 = R"(C_1_1 x_1 + C_1_2 x_2 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 = B_2)""\n";
const string x33 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 = B_3)""\n";
const string x44 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 + C_1_4 x_4 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 + C_2_4 x_4 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 + C_3_4 x_4 = B_3)""\n"
						R"(C_4_1 x_1 + C_4_2 x_2 + C_4_3 x_3 + C_4_4 x_4 = B_4)""\n";                                  //стнадартний вигляд СЛАР різних розмірів
const string x55 = R"(C_1_1 x_1 + C_1_2 x_2 + C_1_3 x_3 + C_1_4 x_4 + C_1_5 x_5 = B_1)""\n"
						R"(C_2_1 x_1 + C_2_2 x_2 + C_2_3 x_3 + C_2_4 x_4 + C_2_5 x_5 = B_2)""\n"
						R"(C_3_1 x_1 + C_3_2 x_2 + C_3_3 x_3 + C_3_4 x_4 + C_3_5 x_5 = B_3)""\n"
						R"(C_4_1 x_1 + C_4_2 x_2 + C_4_3 x_3 + C_4_4 x_4 + C_4_5 x_5 = B_4)""\n"
						R"(C_5_1 x_1 + C_5_2 x_2 + C_5_3 x_3 + C_5_4 x_4 + C_5_5 x_5 = B_5)""\n";

class Matrix
{
public:
	Matrix();
	Matrix(const vector<vector<double>>& new_matrix, const vector<double>& free_) : table(new_matrix), free(free_) // double [][N] конструктор с двох векторів 
	{
		size = table.size();
	}
	Matrix(istream& input, bool to_generate = false);		//конструктор для потоку
	Matrix(const vector<vector<double>>& matrix_with_free);	//конструктор, який автоматично розділяє основну матрицю і стовпчик вільних членів
	Matrix(const string& filename);							//констуктор з файлу
	int Size() const { return size; } //геттер розміру
	vector<vector<double>> GetTable() const { return table; }//геттер таблиці
	vector<double> GetFree() const { return free; }//геттер стовпчика
	bool ToAnalyze() const { return to_analyze; } //геттер змінної to_analyze 
	void SolveGauss(); //вирішити методом Гаусса 
	double det(const vector<vector<double>>& arr, int rows) const; //визначник матриці
	const vector<Matrix>& GetSteps() const { return sbs_matrices; } //геттер массиву кроків
	Matrix& operator=(const Matrix& other) //оператор присвоєння
	{
		this->table = other.table;
		this->free = other.free;
		this->size = other.size;
		this->to_analyze = other.to_analyze;
		return *this;
	}
private:

	int pw(int a) const;//метод для визначення знаку алгебраїчного допопвнення 
	vector<vector<double>> table; //основна квадратна матриця коефіцієнтів СЛАР
	vector<double> free; //матриця вільних членів
	int size; //розмір
	bool to_analyze = false; //чи треба запам'ятовувати кроки 
	vector<Matrix> sbs_matrices; //массив матриць, кожна з яких - крок в методі Гауса
};
