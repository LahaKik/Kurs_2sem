#pragma warning(disable : 4996)
#include "UIWriter.h"


using namespace std;
using namespace std::filesystem;

void SelectLabToProcessing(path p);

char path1[] = "C:\\Users\\hotki\\source\\repos\\Lab_2_1\\x64\\Debug\\Lab_2_1.exe ";

int main()
{
	setlocale(LC_ALL, "");
	path p("C:\\");
	directory_entry DE(p);
	directory_iterator DI(p);
	recursive_directory_iterator RDI(p);
	UIWriter UI;

	bool isExit = false;
	bool isChanged = true;
	int selected = 0;
	vector<directory_entry> filesInDir;
	while (!isExit)
	{
		if (selected < 0)
			selected = 0;
		else if (selected >= filesInDir.size())
		{
			if (filesInDir.size() == 0)
				selected = 0;
			else
				selected = filesInDir.size() - 1;
		}
			
		if(isChanged)
		{
			filesInDir.clear();
			for (directory_entry file : DI)
			{
				filesInDir.push_back(file);
				isChanged = false;
			}
		}

		UI.CollectUI(filesInDir, p, selected);

		char inp = _getch();
		if (inp == -32)
		{
			inp = _getch();
			if (inp == 80)
				selected++;
			if (inp == 72)
				selected--;
		}
		else if (inp == 13)
		{
			p = filesInDir[selected].path();
			if (!p.has_extension())
			{
				DI = directory_iterator(p);

				isChanged = true;
				selected = 0;
			}
			else
			{
				SelectLabToProcessing(p);
				p = p.parent_path();
			}
		}
		else if (inp == '\b')
		{
			if (p.has_parent_path())
				p = p.parent_path();
			DI = directory_iterator(p);

			isChanged = true;
			selected = 0;
			UI.HighlightUI(BKSP);
		}
		else if (inp == 27)
		{
			isExit = true;
			UI.HighlightUI(ESC);
		}
	}
	system("cls");
}

void SelectLabToProcessing(path p)
{
	char path1[1024] = "C:\\Users\\hotki\\source\\repos\\Lab_2_1\\x64\\Debug\\Lab_2_1.exe ";
	char path2[1024] = "C:\\Users\\hotki\\source\\repos\\Lab_2_2\\x64\\Debug\\Lab_2_2.exe ";
	char path3[1024] = "C:\\Users\\hotki\\source\\repos\\Lab_2_3\\x64\\Debug\\Lab_2_3.exe ";
	bool Success = false;

	while(!Success)
	{
		system("cls");
		cout << "Selected file: " << p << endl;
		cout << "Select Lab to processing: \n" <<
			"1 - Wav-file processing \n" <<
			"2 - BMP-file processing \n" <<
			"3 - Statictic of used bytes" << endl;
		char inp = _getche();
		cout << endl;
		if (inp == '1')
		{
			Success = true;
			strcat(path1, p.string().c_str());
			system(path1);
		}
		else if (inp == '2')
		{
			Success = true;
			strcat(path2, p.string().c_str());
			system(path2);
		}
		else if (inp == '3')
		{
			Success = true;
			strcat(path3, p.string().c_str());
			system(path3);
		}
		else if (inp == 27)
			Success = true;
	}

}