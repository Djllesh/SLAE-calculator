#include "Screen.h"
//2x2 --> 38x13
//3x3 --> 28х8
//4x4 --> 22x5
//5x5 --> 18x4


void Screen::Bond(HANDLE h, COORD t, COORD b) const
{
	int lenx = b.X - t.X - 1, leny = b.Y - t.Y;
	COORD f = t;
	unsigned char c;
	c = 457;// |-
	SetConsoleCursorPosition(h, f);
	cout << c;
	c = 461;// =
	for (int i = 0; i < lenx; i++) cout << c;
	c = 443; cout << c << endl; // -|
	c = 442; f = t;// |
	f.Y++;
	for (int i = 0; i < leny - 1; i++)
	{
		SetConsoleCursorPosition(h, f);
		c = 442;
		cout << c;
		SetConsoleCursorPosition(h, { f.X + (SHORT)lenx + 1, f.Y });
		cout << c;
		f.Y++;
	}
	SetConsoleCursorPosition(h, f);
	c = 456;
	cout << c;
	c = 461;
	for (int i = 0; i < lenx; i++) cout << c;
	c = 444;
	cout << c;
}

void Screen::Vertical_line(HANDLE h, COORD top, size_t length, char c)const
{
	COORD cur_pos = top;
	for (int i = 0; i < length; i++)
	{
		SetConsoleCursorPosition(h, cur_pos);
		cout << c;
		cur_pos.Y++;
	}
}

void Screen::Horizontal_line(HANDLE h, COORD top, size_t lenght, char c)const
{
	COORD cur_pos = top;
	for (int i = 0; i < lenght; i++)
	{
		SetConsoleCursorPosition(h, cur_pos);
		cout << c;
		cur_pos.X++;
	}
}

void Screen::Diagonal(HANDLE h, COORD top, size_t lenght, char c)const
{
	COORD cur_pos = top;
	for (int i = 0; i < lenght; i++)
	{
		SetConsoleCursorPosition(h, cur_pos);
		cout << c;
		cur_pos.X++;
		cur_pos.Y++;
	}
}

void Screen::Inverse_diagonal(HANDLE h, COORD bot, size_t lenght, char c)const
{
	COORD cur_pos = bot;
	for (int i = 0; i < lenght; i++)
	{
		SetConsoleCursorPosition(h, cur_pos);
		cout << c;
		cur_pos.X++;
		cur_pos.Y--;
	}
}

void Screen::Resize(const Matrix& m)
{
	matrix = m;
	if (matrix.Size() == 2)//2х2
	{
		settings.top = { 1,1 };
		settings.Size = { 38, 13 };
		settings.line_top = { 80, 1 };
		settings.digit_place = { 18, 8 };
		settings.free_place = { 98, 8 };
	}
	else if (matrix.Size() == 3) //3х3
	{
		settings.top = { 1,1 };
		settings.Size = { 28, 8 };
		settings.line_top = { 90, 1 };
		settings.digit_place = { 11, 5 };
		settings.free_place = { 101, 5 };
	}
	else if (matrix.Size() == 4)//4х4
	{
		settings.top = { 1,2 };
		settings.Size = { 22, 5 };
		settings.line_top = { 96, 1 };
		settings.digit_place = { 9, 5 };
		settings.free_place = { 105, 5 };
	}
	else if (matrix.Size() == 5)//5х5
	{
		settings.top = { 1,1 };
		settings.Size = { 18, 4 };
		settings.line_top = { 100, 1 };
		settings.digit_place = { 7, 3 };
		settings.free_place = { 107, 3 };
	}
}

Screen::Screen()
{
	matrix = Matrix();
}

void Screen::Grid(HANDLE h, bool to_fill)
{
	if (matrix.Size() == 0)//якщо матриця пуста
	{
		cout << "No elements in the matrix. Could not draw a grid. Terminate.\n";
		return;
	}
	COORD top_pos = { settings.top.X, settings.top.Y };
	SetConsoleCursorPosition(h, { 1,1 });

	//перевіряє розмірність матриці, відповідно до розміру, малює поле
	for (int i = 0; i < matrix.Size(); i++) // по рядках
	{
		for (int j = 0; j < matrix.Size() + 1; j++) // по стовпчиках
		{
			Bond(h, top_pos, { top_pos.X + settings.Size.X, top_pos.Y + settings.Size.Y }); // рамка від вершини рамки (в налаштуваннях) до її нижнього краю (варшина.х + ширина, вершина.у + висота)
			top_pos.X += settings.Size.X + 2; // інтервал по ширині
		}
		top_pos.X = 1; // повертаємося на початок рядка
		top_pos.Y += settings.Size.Y + 2; //інтервал по висоті
	}
	Vertical_line(h, settings.line_top, 30, '|');//вертикальна лінія від вершини (налаштування)
	
	SetConsoleCursorPosition(h, { 0,0 });//повертає курсор на початок екрану, щоб не заважав
	if (to_fill) Fill(h); //якщо переданий параметр to_fill справджується - заповнюємо
}

void Screen::ConsecutiveGrid(HANDLE h, bool to_fill)
{
	if (matrix.Size() == 0)//якщо матриця пуста
	{
		cout << "No elements in the matrix. Could not draw a grid. Terminate.\n";
		return;
	}

	COORD top_pos;

	if (current_pos.X == 0 && current_pos.Y == 0)//якщо малюємо вперше 
	{
		top_pos = settings.top; 
		current_pos = settings.top; //і вершину, і поточну позицію необхідно запам'ятати
		//поточна буде змінюватись з кожним елементом сітки, вершина потрібна для правильного відображення вертикальної лінії
	}
	else top_pos = current_pos;//інакше просто копіюємо поточну позицію 



	for (int i = 0; i < matrix.Size(); i++) // по рядках
	{
		for (int j = 0; j < matrix.Size() + 1; j++) // по стовпчиках
		{
			Bond(h, current_pos, { current_pos.X + settings.Size.X, current_pos.Y + settings.Size.Y }); // рамка від вершини рамки (в налаштуваннях) до її нижнього краю (варшина.х + ширина, вершина.у + висота)
			current_pos.X += settings.Size.X + 2; // інтервал по ширині
		}
		current_pos.X = 1; // повертаємося на початок рядка
		current_pos.Y += settings.Size.Y + 2; //інтервал по висоті
	}

	Vertical_line(h, {settings.line_top.X, top_pos.Y - 1}, 30, '|');//вертикальна лінія від вершини (відповідно до початку функції)
	//...цей загадковий блок коду дозволяє отримати дані про консоль і витягти з буфера позицію курсора в координатах
	CONSOLE_SCREEN_BUFFER_INFO csbuf;
	GetConsoleScreenBufferInfo(h, &csbuf);
	current_pos = csbuf.dwCursorPosition;
	current_pos.X = settings.top.X;
	current_pos.Y += 2;
	if (to_fill) Fill(h); //якщо переданий параметр to_fill справджується - заповнюємо
}

void Screen::Fill(HANDLE h) const
{
	if (matrix.Size() == 0)//якщо матриця пуста 
	{
		cout << "No elements in the matrix. Nothing to fill. Terminate.\n";
		return;
	}
	//відповідно до розміру матриці, заповнює поле в правильних місцях
	COORD place;//позиція, куди пишеться число
	if(!settings.consecutive) place = settings.digit_place;//якщо не послідовно заповнюємо - встановлюємо курсор на позицію з налаштувань
	else //якщо послідовно - проводимо розрахунки по позиції курсора 
	{
		place.X = current_pos.X + settings.digit_place.X - settings.top.X;
		// позиція по Х = поточна позиція по Х + зміщення по Х для чисел з налаштувань - зміщення по Х для вершини з налаштувань
		place.Y = current_pos.Y + settings.digit_place.Y - settings.top.Y - 30;
		// позиція по У = поточна позиція по У + зміщення по У для чисел з налаштувань - зміщення по У для вершини з налаштувань - 30  
	}
	vector<vector<double>> table = matrix.GetTable(); // матриця, в якій зберігаються числа (квадратна)
	for (const auto& row : table) // по рядках
	{
		for (const auto& digit : row) //по стовпчиках
		{
			SetConsoleCursorPosition(h, place);
			cout << fixed;//курсор на позицію числа
			cout << setprecision(settings.precision) << digit; //виводимо число        
			place.X += settings.Size.X + 2; //інтервал по ширині
		}
		place.X = settings.digit_place.X; //повертаємося на початок рядка
		place.Y += settings.Size.Y + 2; //інтервал по висоті
	}
	
	vector<double> free = matrix.GetFree(); //стовпичк вільних членів
	COORD free_place = settings.free_place; // позиція для чисел стовпчика
	if(!settings.consecutive) free_place = settings.free_place;//якщо не послідовно заповнюємо - встановлюємо курсор на позицію з налаштувань
	else //якщо послідовно - проводимо розрахунки по позиції курсора 
	{
		free_place.X = current_pos.X + settings.free_place.X - settings.top.X;
		// позиція по Х = поточна позиція по Х + зміщення по Х для чисел з налаштувань - зміщення по Х для вершини з налаштувань
		free_place.Y = current_pos.Y + settings.free_place.Y - settings.top.Y - 30;
		// позиція по У = поточна позиція по У + зміщення по У для чисел з налаштувань - зміщення по У для вершини з налаштувань - 30  
	}
	for (const auto& digit : free) //для кожного числа
	{
		SetConsoleCursorPosition(h, free_place); //курсор на позицію
		cout << setprecision(settings.precision) << digit;//виводимо на екран
		free_place.Y += settings.Size.Y + 2;//інтервал по висоті
	}
	if (!settings.consecutive) SetConsoleCursorPosition(h, { 0,0 });//повертає курсор на початок екрану, щоб не заважав(якщо заповнюємо не послідовно)
	else SetConsoleCursorPosition(h, { current_pos.X, current_pos.Y - 1 });//якщо послідовно - ставимо курсор на поточну позицію 
}

void Screen::FullScreen(HANDLE h) const
{
	SetConsoleDisplayMode(h, CONSOLE_FULLSCREEN_MODE, { 0 });//стандартна функція бібліотеки widows.h з флагом CONSOLE_FULLSCREEN_MODE
}

void Screen::WindowMode(HANDLE h) const
{
	SetConsoleDisplayMode(h, CONSOLE_WINDOWED_MODE , { 0 });//стандартна функція бібліотеки widows.h з флагом CONSOLE_WINDOWED_MODE
}

void Screen::ChangePrecision(int new_prec)
{
	settings.precision = new_prec;//змінюємо точність
}

void Screen::SetConsecutive(bool c)
{
	settings.consecutive = c;//змінюємо значення consecutive
}

void Screen::Solve(HANDLE h)
{
	matrix.SolveGauss();//вирішуємо систему
	Grid(h, 1);//малюємо і заповнюємо
	system("pause");
	ShowAnswer();//виводимо відповідь 
}

void Screen::SolveSbS(HANDLE h)
{
	matrix.SolveGauss();//вирішуємо
	if (matrix.Size() == 0)//якщо матриця пуста
	{
		cout << "Empty matrix, nothing to draw. Terminate!\n";
		return;
	}
	SetConsecutive(true);
	const vector<Matrix>& steps = matrix.GetSteps();//запам'ятовуємо кроки
	int it_num = 0;//номер колонок в прямому порядку
	int rev_col = matrix.Size();//в зворотньому
	for (const Matrix& step : steps)//по кроках в масиві Steps
	{
		if (it_num == matrix.Size() - 1)//якщо остання колонка
		{
			cout << "Normalizing column #" << it_num + 1 << endl;
		}
		else if (it_num < matrix.Size() - 1)//якщо прямий порядок
		{
			cout << "Making zeroes under column #" << it_num + 1 << endl;
		}
		else if (it_num >= matrix.Size())//якщо зворотній порядок
		{
			cout << "Making zeroes above column #" << rev_col << endl;
			rev_col--;
		}
		matrix = step;//записуємо матрицю всередину класу Screen
		ConsecutiveGrid(h, 1);//покроково малюємо
		it_num++;
	}

	SetConsoleCursorPosition(h, current_pos);//встановлюємо курсор на поточній позиціїї
	system("pause");
	ShowAnswer();//виводимо відповідь 
}

Screen::~Screen()
{
	system("CLS");//очистка екрану 
}

void Screen::ShowAnswer() const
{
	//метод викликається гарантовано після вирішення системи ==> значення, які виведуться (якщо виведуться) будуть коренями
	system("CLS");
	if (matrix.Size() == 0) //якщо матриця пуста
	{
		cout << "Empty matrix, no solution!\n";
		return;
	}
	
	cout << "x = {";
	for (int i = 0; i < matrix.Size() - 1; i++)//по стовпчику 
	{
		cout << matrix.GetFree()[i] << ", "; //виводимо значення
	}
	cout << matrix.GetFree().back() <<"}\n"; //останнє без коми
}
