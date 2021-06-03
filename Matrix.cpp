#include "Matrix.h"

Matrix::Matrix(const vector<vector<double>>& matrix_with_free)
{
	//2x3 -> 2x2 + 2x1 
	//3x4 -> 3x3 + 3x1 
	//4x5 -> 4x4 + 4x1 
	//5x6 -> 5x5 + 5x1 
	if (matrix_with_free.size() <= 5 && matrix_with_free.size() >= 2 && matrix_with_free.size() + 1 == matrix_with_free[0].size())//�������� ������ + �������� �� ���� ����� �� �����
	{
		size = matrix_with_free.size();//����� ������� ������� ������� ����� �������, �� ��������
		table = vector<vector<double>>(size);//������� ������ ������ ������� ������ size

		for (int i = 0; i < size; i++)//��������� �� �����
		{
			for (int j = 0; j < matrix_with_free[i].size() - 1; j++)//�� ��������������� ���������
			{
				table[i].push_back(matrix_with_free[i][j]);//����� ������� ������� �������
			}
		}

		for (const auto& row : matrix_with_free)//�� ������
		{
			free.push_back(row.back());//������ �� ��������� ������ ����� ������� ������� ������� ����� �������
		}
	}
	else//���� ������������ �����
	{
		cout << "Unsupported size of a matrix!\n";
	}
}

Matrix::Matrix(const string& filename)
{
	ifstream input;
	input.open(filename);//��������� ����
	if (!input.is_open())//����������, �� �������
	{
		cout << "Wrong path!\n";
		size = 0;
		return;
	}
	cout << "Reading size...\n";
	input >> size;//������� �����
	if (size > 5 || size < 2)//���������� �����
	{
		size = 0;
		cout << "Wrong size!\n";
		return;
	}
	table = vector<vector<double>>(size);//������� ������ ������ ������� ������ size
	cout << "Size = " << size << endl << "Start reading the matrix...\n";

	for (int i = 0; i < size; i++)//�� ������
	{
		for (int j = 0; j <= size; j++)//�� ����������
		{
			double var;

			if(input) input >> var;//������� �����
			else
			{
				cout << "Input problem!\n";
				return;
			}
			if (j == size)//���� �������, �������� � free
			{
				free.push_back(var);
			}
			else table[i].push_back(var);//������ � �������
		}
	}
	input >> to_analyze;
	if (to_analyze) cout << "SLAE will be solved sted-by-step!\n";
	else cout << "SLAE will be solved right away\n";
	cout << "Reading complete!\n";
}


void Matrix::SolveGauss()
{
	sbs_matrices.clear();//������� ����� ���������, ����� �� ����� �� ������� ����, ���, �� ������ �������� ������� sbs_matrices �������
	if (size == 0)//���� ������� ����� 
	{
		cout << "Empty matrix. Cannot solve!\n";
		return;
	}
	if (det(table, size) == 0)//���� �������� ����� ���� 
	{
		cout << "System has no solution. Clearing...\n";
		table.clear();
		free.clear();
		size = 0;
		return;
	}

	vector<vector<double>> copy(size);//�������, � ���� ������ ��������� � ��������� ���������� ���������� 
	int l = 0;
	//...������� �� �������� � ��
	for (const auto& row : table)
	{
		for (const auto& elem : row)
		{
			copy[l].push_back(elem);
		}
		l++;
	}
	l = 0;
	//���� ����� � ����� ������� �����
	for (const auto& elem : free)
	{
		copy[l].push_back(elem);
		l++;
	}

	for (int k = 0; k < size; k++)//������ �������
	{
		for (int i = 0; i < size + 1; i++)					
		{
			copy[k][i] /= table[k][k];
		}
		for (int i = k + 1; i < size; i++)
		{
			double K = copy[i][k] / copy[k][k];
			for (int j = 0; j < size+1; j++)
			{
				copy[i][j] -= copy[k][j] * K;
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size + 1; j++)
			{
				if (j == size)
				{
					free[i] = copy[i][j];
				}
				else table[i][j] = copy[i][j];
			}
		}
		if(to_analyze) sbs_matrices.push_back({ table, free });//���� ��� ����� ���������� ��������� - �������� �������� ��������� � ���� ����� �������� �����
		//����� �������� - ��������� ������� �� ����������� ��������� �-�� �����
	}

	for (int k = size - 1; k > -1; k--)//�������� �������
	{
		for (int i = size; i > -1; i--)
		{
			copy[k][i] /= table[k][k];
		}
		for (int i = k - 1; i > -1; i--)
		{
			double K = copy[i][k] / copy[k][k];
			for (int j = size; j > -1; j--)
			{
				copy[i][j] -= copy[k][j] * K;
			}
		}
		if (to_analyze)
		{
			//��� ������������ �������������� ����� ������ - � �������� ����������
			vector<vector<double>> table_step(size);//���� ��������� �������
			vector<double> free_step;//���� ���������
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size + 1; j++)
				{
					if (j == size)
					{
						free_step.push_back(copy[i][j]);
					}
					else table_step[i].push_back(copy[i][j]);
				}
			}
			sbs_matrices.push_back({ table_step, free_step });//���� ��� ����� ���������� ��������� - �������� �������� ��������� � ���� ����� �������� �����
		}
	}

	if(!sbs_matrices.empty()) sbs_matrices.pop_back();//������� �������� - ���� ������������� - ��������� 
	free.clear();//������� �������� 
	//...�������� ���������� ���������
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			table[i][j] = copy[i][j];
		}
	}

	for (const auto& row : copy)
	{
		free.push_back(row.back());
	}
}

int Matrix::pw(int a) const
{
	if (a % 2 == 0) return 1;
	return -1;
}

double Matrix::det(const vector<vector<double>>& arr, int rows) const
{
	vector<vector<double> > arr2;
	double dett = 0, hk;
	if (rows == 2) {
		dett = (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]);
	}
	else {
		for (int i = 0; i < rows; i++) {
			hk = arr[0][i];
			arr2 = arr;
			arr2.erase(arr2.begin());
			for (int k = 0; k < rows - 1; k++) arr2[k].erase(arr2[k].begin() + i);
			dett = dett + pw(i) * hk * det(arr2, rows - 1);
		}
	}
	return dett;
}

Matrix::Matrix()
{
	table = vector<vector<double>>();
	free = vector<double>();
	size = 0;
}

Matrix::Matrix(istream& input, bool to_generate)
{
	srand(time(NULL));
	int MAX_VALUE;
	bool satisfied = false;//�� ����� ������� �� "���o�������" ����������� ��������� ���� ����� 
	while (!satisfied)//���� ���������� �� "�����������"
	{
		table.clear();//������� �������
		free.clear();//������� ��������
		size = 0;//������� �����
		cout << "Enter the quantity of variables from 2 to 5, you'll have another try if something goes wrong. To exit, type '-1': ";
		while (size < 2 || size > 5)//������� �����, ���� �� �� � �������� [2,5]
		{
			input >> size;
			if (size == -1)//���� ����� ������� -1 - �������� � ������� (������� ����������� ������)
			{
				size = 0;
				return;
			}
		}
		table = vector<vector<double>>(size);//������� ������ ������ ������� ������ size
		switch (size) //�������� �� ������, �������� ��������� ������ (��� ����� ����� � ���� Matrix.h)
		{
		case 2:
			cout << x22;
			break;

		case 3:
			cout << x33;
			break;

		case 4:
			cout << x44;
			break;

		case 5:
			cout << x55;
			break;
		default:
			break;
		}
		cout << "That's your format of SLAE. Now you will be insering coefficients by obvious order.\n";
		if (to_generate)
		{
			cout << "What will be the maximum value: ";
			input >> MAX_VALUE; 
		}
		for (int i = 0; i < size; i++)//�� ������
		{
			for (int j = 0; j < size; j++)//�� ����������
			{
				double var;
				cout << "C_" << i + 1 << "_" << j + 1 << " = ";//�������� �� �����, ���� ��������� ���������� ��������� 
				if(!to_generate) input >> var;//������� ����������, ���� �� ��������
				else//���� ��������
				{
					if (MAX_VALUE < 5)
					{
						var = 0.01 * (rand() % (2 * (MAX_VALUE * 100 + 1))) - (double)MAX_VALUE;
						cout << var << endl; 
					}
					else
					{
						var = (rand() % (2 * MAX_VALUE)) - (double)MAX_VALUE;
						cout << var << endl;
					}
				}
				table[i].push_back(var);//�������� � �������
			}
		}

		for (int i = 0; i < size; i++)//�� ������
		{
			double var;
			cout << "B_" << i + 1 << " = ";
			if(!to_generate)input >> var;//������� ���� �����, ���� �� ��������
			else//���� ��������
			{
				if (MAX_VALUE < 5)
				{
					var = 0.01 * (rand() % (2 * (MAX_VALUE * 100 + 1))) - (double)MAX_VALUE;
					cout << var << endl;
				}
				else
				{
					var = (rand() % (2 * MAX_VALUE)) - (double)MAX_VALUE;
					cout << var << endl;
				}
			}
			free.push_back(var);//�������� ��
		}

		cout << "Final system (precision can be changed):\n";
		for (int i = 0; i < size; i++)//�� ������
		{
			for (int j = 0; j <= size; j++)//�� ����������
			{
				//�������� ����� ������� � ������� ������� � ��� ��������� �������������
				if (j == size)//���� ������� �������� - ������ � ������� free
				{
					cout << " = " << free[i] << endl;
				}
				else if (j == size - 1) cout << table[i][j] << " * x_" << j + 1 << " "; //���� ������������ - �������� � ������ C_i_j * x_j (��� �����)
				else cout << table[i][j] << " * x_" << j + 1 << " + "; //� ������ ������� �������� � ������ C_i_j * x_j + (� ������)
			}
		}
		cout << "If you want to analyze a solution (step-by-step) type '1', if you want the system to be solved right away type '0':\n";
		input >> to_analyze;//�� ����� ��������� ���������
		cout << "If you are satisfied with the system, type '1', if you want to change it, type '0':\n";
		input >> satisfied;//���� ���������� ����������� ���, �� ������ - ����� 1, ������ - 0 � ��� � �������
	}
}