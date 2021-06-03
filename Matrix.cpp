#include "Matrix.h"

Matrix::Matrix(const vector<vector<double>>& matrix_with_free)
{
	//2x3 -> 2x2 + 2x1 
	//3x4 -> 3x3 + 3x1 
	//4x5 -> 4x4 + 4x1 
	//5x6 -> 5x5 + 5x1 
	if (matrix_with_free.size() <= 5 && matrix_with_free.size() >= 2 && matrix_with_free.size() + 1 == matrix_with_free[0].size())//перевірка розміру + стопчиків на один більше за рядків
	{
		size = matrix_with_free.size();//розмір матриці дорівнює кількості рядків матриці, що приймаємо
		table = vector<vector<double>>(size);//створює вектор пустих векторів розміру size

		for (int i = 0; i < size; i++)//проходимо всі рядки
		{
			for (int j = 0; j < matrix_with_free[i].size() - 1; j++)//до передостаннього стовпчика
			{
				table[i].push_back(matrix_with_free[i][j]);//кожен елемент матриці копіюємо
			}
		}

		for (const auto& row : matrix_with_free)//по рядках
		{
			free.push_back(row.back());//додаємо до стовпчика вільних членів останній елемент кожного рядка матриці
		}
	}
	else//якщо неправильний розмір
	{
		cout << "Unsupported size of a matrix!\n";
	}
}

Matrix::Matrix(const string& filename)
{
	ifstream input;
	input.open(filename);//відкриваємо файл
	if (!input.is_open())//перевіряємо, що відкрили
	{
		cout << "Wrong path!\n";
		size = 0;
		return;
	}
	cout << "Reading size...\n";
	input >> size;//зчитуємо розмір
	if (size > 5 || size < 2)//перевіряємо розмір
	{
		size = 0;
		cout << "Wrong size!\n";
		return;
	}
	table = vector<vector<double>>(size);//створює вектор пустих векторів розміру size
	cout << "Size = " << size << endl << "Start reading the matrix...\n";

	for (int i = 0; i < size; i++)//по рядках
	{
		for (int j = 0; j <= size; j++)//по стовпчиках
		{
			double var;

			if(input) input >> var;//зчитуємо змінну
			else
			{
				cout << "Input problem!\n";
				return;
			}
			if (j == size)//якщо останній, записуємо у free
			{
				free.push_back(var);
			}
			else table[i].push_back(var);//інакше в таблицю
		}
	}
	input >> to_analyze;
	if (to_analyze) cout << "SLAE will be solved sted-by-step!\n";
	else cout << "SLAE will be solved right away\n";
	cout << "Reading complete!\n";
}


void Matrix::SolveGauss()
{
	sbs_matrices.clear();//функція тільки викликана, кроків до цього не повинно бути, все, що лежить всередині вектора sbs_matrices очищуємо
	if (size == 0)//якщо матриця пуста 
	{
		cout << "Empty matrix. Cannot solve!\n";
		return;
	}
	if (det(table, size) == 0)//якщо визначни рівний нулю 
	{
		cout << "System has no solution. Clearing...\n";
		table.clear();
		free.clear();
		size = 0;
		return;
	}

	vector<vector<double>> copy(size);//матриця, з якою будемо працювати і проводити математичні обчислення 
	int l = 0;
	//...копіюємо всі значення в неї
	for (const auto& row : table)
	{
		for (const auto& elem : row)
		{
			copy[l].push_back(elem);
		}
		l++;
	}
	l = 0;
	//вільні члени в кінець кожного рядка
	for (const auto& elem : free)
	{
		copy[l].push_back(elem);
		l++;
	}

	for (int k = 0; k < size; k++)//прямий порядок
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
		if(to_analyze) sbs_matrices.push_back({ table, free });//якщо нам треба аналізувати покроково - записуємо проміжний результат в кінці кожної ітерації циклу
		//кожна ітерація - занулення значень під діагональним елементом к-го рядка
	}

	for (int k = size - 1; k > -1; k--)//зворотній порядок
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
			//тут використаний альтернативний спосіб запису - з проміжним копюванням
			vector<vector<double>> table_step(size);//копія квадратної частини
			vector<double> free_step;//копія стовпчика
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
			sbs_matrices.push_back({ table_step, free_step });//якщо нам треба аналізувати покроково - записуємо проміжний результат в кінці кожної ітерації циклу
		}
	}

	if(!sbs_matrices.empty()) sbs_matrices.pop_back();//остання ітерація - копія передостанньої - видаляємо 
	free.clear();//очищуємо стовпчик 
	//...записуємо остаточний результат
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
	bool satisfied = false;//ця змінна відповідає за "задoволення" користувача введенням своїх даних 
	while (!satisfied)//поки користувач не "задоволений"
	{
		table.clear();//очищуємо матрицю
		free.clear();//очищуємо стовпчик
		size = 0;//очищуємо розмір
		cout << "Enter the quantity of variables from 2 to 5, you'll have another try if something goes wrong. To exit, type '-1': ";
		while (size < 2 || size > 5)//зчитуємо розмір, поки він не в інтервалі [2,5]
		{
			input >> size;
			if (size == -1)//якщо розмір дорівнює -1 - виходимо з функції (матриця залишаеться пустою)
			{
				size = 0;
				return;
			}
		}
		table = vector<vector<double>>(size);//створює вектор пустих векторів розміру size
		switch (size) //відподідно до розміру, виводить загальний вигляд (вже готові рядки в файлі Matrix.h)
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
		for (int i = 0; i < size; i++)//по рядках
		{
			for (int j = 0; j < size; j++)//по стовпчиках
			{
				double var;
				cout << "C_" << i + 1 << "_" << j + 1 << " = ";//виводить на екран, який конкретно коефіцієнт вводиться 
				if(!to_generate) input >> var;//зчитуємо коефіцієнт, якщо не генеруємо
				else//якщо генеруємо
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
				table[i].push_back(var);//записуємо в матрицю
			}
		}

		for (int i = 0; i < size; i++)//по рядках
		{
			double var;
			cout << "B_" << i + 1 << " = ";
			if(!to_generate)input >> var;//зчитуємо вільні члени, якщо не генеруємо
			else//якщо генеруємо
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
			free.push_back(var);//записуємо їх
		}

		cout << "Final system (precision can be changed):\n";
		for (int i = 0; i < size; i++)//по рядках
		{
			for (int j = 0; j <= size; j++)//по стовпчиках
			{
				//виводимо повну систему с вільними членами з вже введеними коефіцієнтами
				if (j == size)//якщо останній стовпчик - беремо з вектора free
				{
					cout << " = " << free[i] << endl;
				}
				else if (j == size - 1) cout << table[i][j] << " * x_" << j + 1 << " "; //якщо передостанній - виводимо у вигляді C_i_j * x_j (без плюса)
				else cout << table[i][j] << " * x_" << j + 1 << " + "; //в іншому випадку виводимо у вигляді C_i_j * x_j + (з плюсом)
			}
		}
		cout << "If you want to analyze a solution (step-by-step) type '1', if you want the system to be solved right away type '0':\n";
		input >> to_analyze;//чи треба покроково вирішувати
		cout << "If you are satisfied with the system, type '1', if you want to change it, type '0':\n";
		input >> satisfied;//якщо користувач задоволений тим, що вийшло - тисне 1, інакше - 0 і все з початку
	}
}