#include "Scenario.h"
using namespace std;

void PaC()
{
	system("pause"); 
	system("CLS");	
}

CONSOLE_SCREEN_BUFFER_INFO csbuf;

void TestMatrices(HANDLE h)
{
	vector<vector<double>> v1 = { {121.312,256.686},
								  {672.788,143.632} };
	vector<double> v2 = { 532.954, 645.745 };
	Matrix m(v1, v2);
	vector<vector<double>> v3 = { {121.312,256.686,143.632},
								  {672.788,143.632,143.632},
								  {672.788,143.632,143.632} };
	vector<double> v4 = { 532.954, 645.745, 143.632 };
	Matrix m1(v3, v4);
	vector<vector<double>> v5 = { {121.312,256.686,143.632,143.632},
								  {672.788,143.632,143.632,143.632},
								  {672.788,143.632,143.632,143.632},
								  {672.788,143.632,143.632,143.632} };
	vector<double> v6 = { 532.954, 645.745,143.632,143.632 };
	Matrix m2(v5, v6);
	vector<vector<double>> v7 = { {121.312,256.686,143.632,143.632,143.632},
								  {672.788,143.632,143.632,143.632,143.632},
								  {672.788,143.632,143.632,143.632,143.632},
								  {672.788,143.632,143.632,143.632,143.632},
								  {121.312,256.686,143.632,143.632,143.632} };
	vector<double> v8 = { 532.954,532.954,645.745,143.632,143.632 };
	Matrix m3(v7, v8);
	Screen scr(m);



	//2x2
	scr.Grid(h);
	system("pause");
	scr.Fill(h);
	PaC();

	//3x3
	scr.Resize(m1);
	scr.Grid(h);
	system("pause");
	scr.Fill(h);
	PaC();


	//4x4
	scr.Resize(m2);
	scr.Grid(h);
	system("pause");
	scr.Fill(h);
	PaC();


	//5x5
	scr.Resize(m3);
	scr.Grid(h);
	system("pause");
	scr.Fill(h);
	PaC();

	SetConsoleCursorPosition(h, { 0,0 });
	system("pause");
	Matrix file({ {2, 2, 2},
				  {1, 1, 1} });
	PaC();

	scr.Resize(file);
	scr.Grid(h, 1);
	PaC();
}


int main()
{
	SetConsoleTitleA("SLAE engine");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbuf);
	SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
	system("CLS");
	bool contin = true;
	Scenario s;
	while (contin)
	{
		cout << "Welcome to SLAE engine! With this program you can easily solve any system of linear equasions.\n" <<
			"You can choose all of this options. In order to start, type the corresponding digit and press 'enter'.\n" <<
			"1 - reading matrix from file (all the requierments will be mentioned)\n" <<
			"2 - reading matrix from the console input\n" <<
			"3 - reading already created matrix in the source code (nothing will be solved if there are no matrix)\n" <<
			"4 - generating matrix randomly\n" << 
			"5 - additional functionality\n";
		int command; 
		cin >> command;
		if (command == 1)
		{
			string filename; 
			cout << "Enter filename. Make sure to add '.txt'\n";
			cin >> filename;
			s.FromFile(h, filename);
			PaC();
		}
		else if (command == 2)
		{
			s.FromInput(h, cin);
			system("pause");
 		}
		else if (command == 3)
		{
			Matrix m = { {{2,2},
						  {4,4}}, {1,8} }; //тут створіть свою матрицю
			s.FromMatrix(h, m);
			PaC();
		}
		else if (command == 4)
		{
			s.Generate(h);
			PaC();
		}
		else if (command == 5)
		{
			cout << "Additional functionality:\n" <<
				"1 - toggle fullsreen\n" <<
				"2 - window mode\n" <<
				"3 - change precision\n";
			int add_comm;
			cin >> add_comm;
			if (add_comm == 1)
			{
				s.FullScreen(h);
				PaC();
			}
			else if (add_comm == 2)
			{
				s.WindowMode(h);
				PaC();
			}
			else if (add_comm == 3)
			{
				int prec;
				cout << "Type new precision:";
				cin >> prec;
				s.ChangePrecision(prec);
				PaC();
			}
			else
			{
				cout << "Wrong command. Would you like to restart? (1 - yes, 0 - no)\n";
				cin >> contin;
				if (contin) continue;
				else break;
				PaC();
			}
		}
		else
		{
			cout << "Wrong command. Would you like to restart? (1 - yes, 0 - no)\n";
			cin >> contin;
			if (contin) continue;
			else break;
			system("CLS");
		}
		cout << "Would you like to continue? (1 - yes, 0 - no)\n";
		cin >> contin;
		system("CLS");
	}
	return 0;
}