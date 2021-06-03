#include "Screen.h"
//2x2 --> 38x13
//3x3 --> 28�8
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
	if (matrix.Size() == 2)//2�2
	{
		settings.top = { 1,1 };
		settings.Size = { 38, 13 };
		settings.line_top = { 80, 1 };
		settings.digit_place = { 18, 8 };
		settings.free_place = { 98, 8 };
	}
	else if (matrix.Size() == 3) //3�3
	{
		settings.top = { 1,1 };
		settings.Size = { 28, 8 };
		settings.line_top = { 90, 1 };
		settings.digit_place = { 11, 5 };
		settings.free_place = { 101, 5 };
	}
	else if (matrix.Size() == 4)//4�4
	{
		settings.top = { 1,2 };
		settings.Size = { 22, 5 };
		settings.line_top = { 96, 1 };
		settings.digit_place = { 9, 5 };
		settings.free_place = { 105, 5 };
	}
	else if (matrix.Size() == 5)//5�5
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
	if (matrix.Size() == 0)//���� ������� �����
	{
		cout << "No elements in the matrix. Could not draw a grid. Terminate.\n";
		return;
	}
	COORD top_pos = { settings.top.X, settings.top.Y };
	SetConsoleCursorPosition(h, { 1,1 });

	//�������� ��������� �������, �������� �� ������, ����� ����
	for (int i = 0; i < matrix.Size(); i++) // �� ������
	{
		for (int j = 0; j < matrix.Size() + 1; j++) // �� ����������
		{
			Bond(h, top_pos, { top_pos.X + settings.Size.X, top_pos.Y + settings.Size.Y }); // ����� �� ������� ����� (� �������������) �� �� �������� ���� (�������.� + ������, �������.� + ������)
			top_pos.X += settings.Size.X + 2; // �������� �� �����
		}
		top_pos.X = 1; // ����������� �� ������� �����
		top_pos.Y += settings.Size.Y + 2; //�������� �� �����
	}
	Vertical_line(h, settings.line_top, 30, '|');//����������� ��� �� ������� (������������)
	
	SetConsoleCursorPosition(h, { 0,0 });//������� ������ �� ������� ������, ��� �� �������
	if (to_fill) Fill(h); //���� ��������� �������� to_fill ������������ - ����������
}

void Screen::ConsecutiveGrid(HANDLE h, bool to_fill)
{
	if (matrix.Size() == 0)//���� ������� �����
	{
		cout << "No elements in the matrix. Could not draw a grid. Terminate.\n";
		return;
	}

	COORD top_pos;

	if (current_pos.X == 0 && current_pos.Y == 0)//���� ������� ������ 
	{
		top_pos = settings.top; 
		current_pos = settings.top; //� �������, � ������� ������� ��������� �����'�����
		//������� ���� ���������� � ������ ��������� ����, ������� ������� ��� ����������� ����������� ����������� ��
	}
	else top_pos = current_pos;//������ ������ ������� ������� ������� 



	for (int i = 0; i < matrix.Size(); i++) // �� ������
	{
		for (int j = 0; j < matrix.Size() + 1; j++) // �� ����������
		{
			Bond(h, current_pos, { current_pos.X + settings.Size.X, current_pos.Y + settings.Size.Y }); // ����� �� ������� ����� (� �������������) �� �� �������� ���� (�������.� + ������, �������.� + ������)
			current_pos.X += settings.Size.X + 2; // �������� �� �����
		}
		current_pos.X = 1; // ����������� �� ������� �����
		current_pos.Y += settings.Size.Y + 2; //�������� �� �����
	}

	Vertical_line(h, {settings.line_top.X, top_pos.Y - 1}, 30, '|');//����������� ��� �� ������� (�������� �� ������� �������)
	//...��� ���������� ���� ���� �������� �������� ��� ��� ������� � ������� � ������ ������� ������� � �����������
	CONSOLE_SCREEN_BUFFER_INFO csbuf;
	GetConsoleScreenBufferInfo(h, &csbuf);
	current_pos = csbuf.dwCursorPosition;
	current_pos.X = settings.top.X;
	current_pos.Y += 2;
	if (to_fill) Fill(h); //���� ��������� �������� to_fill ������������ - ����������
}

void Screen::Fill(HANDLE h) const
{
	if (matrix.Size() == 0)//���� ������� ����� 
	{
		cout << "No elements in the matrix. Nothing to fill. Terminate.\n";
		return;
	}
	//�������� �� ������ �������, �������� ���� � ���������� �����
	COORD place;//�������, ���� �������� �����
	if(!settings.consecutive) place = settings.digit_place;//���� �� ��������� ���������� - ������������ ������ �� ������� � �����������
	else //���� ��������� - ��������� ���������� �� ������� ������� 
	{
		place.X = current_pos.X + settings.digit_place.X - settings.top.X;
		// ������� �� � = ������� ������� �� � + ������� �� � ��� ����� � ����������� - ������� �� � ��� ������� � �����������
		place.Y = current_pos.Y + settings.digit_place.Y - settings.top.Y - 30;
		// ������� �� � = ������� ������� �� � + ������� �� � ��� ����� � ����������� - ������� �� � ��� ������� � ����������� - 30  
	}
	vector<vector<double>> table = matrix.GetTable(); // �������, � ��� ����������� ����� (���������)
	for (const auto& row : table) // �� ������
	{
		for (const auto& digit : row) //�� ����������
		{
			SetConsoleCursorPosition(h, place);
			cout << fixed;//������ �� ������� �����
			cout << setprecision(settings.precision) << digit; //�������� �����        
			place.X += settings.Size.X + 2; //�������� �� �����
		}
		place.X = settings.digit_place.X; //����������� �� ������� �����
		place.Y += settings.Size.Y + 2; //�������� �� �����
	}
	
	vector<double> free = matrix.GetFree(); //�������� ������ �����
	COORD free_place = settings.free_place; // ������� ��� ����� ���������
	if(!settings.consecutive) free_place = settings.free_place;//���� �� ��������� ���������� - ������������ ������ �� ������� � �����������
	else //���� ��������� - ��������� ���������� �� ������� ������� 
	{
		free_place.X = current_pos.X + settings.free_place.X - settings.top.X;
		// ������� �� � = ������� ������� �� � + ������� �� � ��� ����� � ����������� - ������� �� � ��� ������� � �����������
		free_place.Y = current_pos.Y + settings.free_place.Y - settings.top.Y - 30;
		// ������� �� � = ������� ������� �� � + ������� �� � ��� ����� � ����������� - ������� �� � ��� ������� � ����������� - 30  
	}
	for (const auto& digit : free) //��� ������� �����
	{
		SetConsoleCursorPosition(h, free_place); //������ �� �������
		cout << setprecision(settings.precision) << digit;//�������� �� �����
		free_place.Y += settings.Size.Y + 2;//�������� �� �����
	}
	if (!settings.consecutive) SetConsoleCursorPosition(h, { 0,0 });//������� ������ �� ������� ������, ��� �� �������(���� ���������� �� ���������)
	else SetConsoleCursorPosition(h, { current_pos.X, current_pos.Y - 1 });//���� ��������� - ������� ������ �� ������� ������� 
}

void Screen::FullScreen(HANDLE h) const
{
	SetConsoleDisplayMode(h, CONSOLE_FULLSCREEN_MODE, { 0 });//���������� ������� �������� widows.h � ������ CONSOLE_FULLSCREEN_MODE
}

void Screen::WindowMode(HANDLE h) const
{
	SetConsoleDisplayMode(h, CONSOLE_WINDOWED_MODE , { 0 });//���������� ������� �������� widows.h � ������ CONSOLE_WINDOWED_MODE
}

void Screen::ChangePrecision(int new_prec)
{
	settings.precision = new_prec;//������� �������
}

void Screen::SetConsecutive(bool c)
{
	settings.consecutive = c;//������� �������� consecutive
}

void Screen::Solve(HANDLE h)
{
	matrix.SolveGauss();//������� �������
	Grid(h, 1);//������� � ����������
	system("pause");
	ShowAnswer();//�������� ������� 
}

void Screen::SolveSbS(HANDLE h)
{
	matrix.SolveGauss();//�������
	if (matrix.Size() == 0)//���� ������� �����
	{
		cout << "Empty matrix, nothing to draw. Terminate!\n";
		return;
	}
	SetConsecutive(true);
	const vector<Matrix>& steps = matrix.GetSteps();//�����'������� �����
	int it_num = 0;//����� ������� � ������� �������
	int rev_col = matrix.Size();//� �����������
	for (const Matrix& step : steps)//�� ������ � ����� Steps
	{
		if (it_num == matrix.Size() - 1)//���� ������� �������
		{
			cout << "Normalizing column #" << it_num + 1 << endl;
		}
		else if (it_num < matrix.Size() - 1)//���� ������ �������
		{
			cout << "Making zeroes under column #" << it_num + 1 << endl;
		}
		else if (it_num >= matrix.Size())//���� �������� �������
		{
			cout << "Making zeroes above column #" << rev_col << endl;
			rev_col--;
		}
		matrix = step;//�������� ������� ��������� ����� Screen
		ConsecutiveGrid(h, 1);//��������� �������
		it_num++;
	}

	SetConsoleCursorPosition(h, current_pos);//������������ ������ �� ������� ��������
	system("pause");
	ShowAnswer();//�������� ������� 
}

Screen::~Screen()
{
	system("CLS");//������� ������ 
}

void Screen::ShowAnswer() const
{
	//����� ����������� ����������� ���� �������� ������� ==> ��������, �� ���������� (���� ����������) ������ ��������
	system("CLS");
	if (matrix.Size() == 0) //���� ������� �����
	{
		cout << "Empty matrix, no solution!\n";
		return;
	}
	
	cout << "x = {";
	for (int i = 0; i < matrix.Size() - 1; i++)//�� ��������� 
	{
		cout << matrix.GetFree()[i] << ", "; //�������� ��������
	}
	cout << matrix.GetFree().back() <<"}\n"; //������ ��� ����
}
