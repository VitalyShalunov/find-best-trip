
#include"stdafx.h"
#include<string.h>
#include<Windows.h>
#include <conio.h>
#include <math.h>
#include<time.h>
#include<strsafe.h>

int n, np, mintrip;
int kolcit; //количество городов
int cost[15][15], costf[15][15], costpos[17][17], trippr[40], trip[40], tripback[40];
int posetit[15];
int kolback;
int koltrip = 1;//количество пройденных точек
FILE *file, *city;
const int V = 15;

char cit[15][30];
char map[30][10];
int kolmap;
wchar_t nowmap[30];

struct towns
{
	int x, y;
}tow;

#define WIDTH 1900
#define HEIGHT 700

void FU(int D[][15], int N)
{
	int k;
	int i, j;
	for (k = 0; k<N; k++)
		for (i = 0; i<N; i++)
			for (j = 0; j<N; j++)
				if (D[i][k] && D[k][j] && i != j)
					if (D[i][k] + D[k][j]<D[i][j] || D[i][j] == 0)
						D[i][j] = D[i][k] + D[k][j];

	//for (i = 0; i<N; i++)
	{
		//	for (j = 0; j<N; j++) printf("%d \t",D[i][j]);
		//	printf("\n");
	}
}

void floid()
{
	//printf("Матрица кратчайших путей: \n");
	FU(costf, n);
	//system("pause");
}



int **Dijkstra(int start, int end, int *index, int *p1, int *kol)
{
	int **masindremove;
	masindremove = new int*[2];
	for (int i = 0; i < 2; i++)
		masindremove[i] = new int[15];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 15; j++)
			*(*(masindremove + i) + j) = 0;
	kolback = 0;
	memset(tripback, 0, sizeof(int) * 40);
	int dmin[V]; // минимальное расстояние
	memset(dmin, 0, sizeof(int) * V);
	int visited[V]; // посещенные вершины
					//memset(visited, 0, sizeof(int) * V);

	int temp;
	int minindex, min;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//Инициализация вершин и расстояний
	for (int i = 0; i<n; i++)
	{
		dmin[i] = 10000;
		visited[i] = 1;
	}

	dmin[start] = 0; //от какой вершины
					 // Шаг алгоритма
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i<n; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((visited[i] == 1) && (dmin[i]<min))
			{ // Переприсваиваем значения
				min = dmin[i];
				minindex = i;
			}
		}
		// Добавляем найденный минимальный вес к текущему весу вершины и сравниваем с текущим минимальным весом вершины
		if (minindex != 10000)
		{
			for (int i = 0; i<n; i++)
			{
				if (cost[minindex][i] > 0)
				{
					temp = min + cost[minindex][i];
					if (temp < dmin[i])
					{
						dmin[i] = temp;
					}
				}
			}
			visited[minindex] = 0;
		}
	} while (minindex < 10000);

	// Восстановление пути
	int ver[V]; // массив посещенных вершин

	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = dmin[end]; // вес конечной вершины

	while (end != start) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < n; i++) // просматриваем все вершины
			if (cost[end][i] != 0)   // если связь есть
			{
				int temp = weight - cost[end][i]; // определяем вес пути из предыдущей вершины
				if (temp == dmin[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					ver[k] = i + 1; // и записываем ее в массив

					k++;
				}
			}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	//printf("\nВывод кратчайшего пути\n");
	int in = *index;
	int in1 = *index;
	in++;
	//int kol = 0;
	*kol = 0;
	int b = 0;
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
	for (int i = k - 1; i >= 0; i--)
	{
		if ((i != 0) && (i != (k - 1)))
		{
			trippr[(in)++] = ver[i] - 1; //выстраиваем маршрут 
			*(kol) += 1;
		}
		if (*p1 == 1000)
		{
			tripback[b++] = ver[i] - 1;
			kolback++;
			if ((ver[i] - 1) == (n - 1))
				printf("%d - %s", ver[i] - 1, cit[ver[i] - 1]);
			else printf("%d - %s", ver[i] - 1, cit[ver[i] - 1]);
		}
		//printf("%3d ", ver[i]);
	}

	*(kol) += 1;
	//for (int b = 0; b < 2;b++)
	//memset(masindremove, 0, sizeof(int)*n*2);
	int ind = 0;

	(*index)++;
	for (int a = (*index); a < (*index + (*kol - 1)); a++)
	{
		for (int j = 1; j <= np; j++)
			if (costpos[0][j] == (trippr[a]))
			{
				costpos[np + 1][j]++;
				/*if (costpos[np + 1][j] ==1) {*/

				/**(*(masindremove)+ind)= costpos[0][j];
				*(*(masindremove+1)+ind)= masindremove[1][ind++]++;*/
				masindremove[0][ind] = costpos[0][j];
				masindremove[1][ind++]++;
				//printf("%d", masindremove[1][0]);
				//(*p)++;
				(*p1)++;
				//}
				//else if (costpos[np + 1][j] != 0) {

				//	/**(*(masindremove)+ind) = costpos[0][j];
				//	*(*(masindremove + 1) + ind)++;
				//	ind++;*/
				//	masindremove[0][ind] = costpos[0][j];
				//	masindremove[1][ind++]++;
				//	(*p1)++;
				//	
				//	break;
				//}

			}

	}

	*index = in;
	return masindremove;
}

void newmap()
{

	int k = 0;
	wchar_t masmap[15][30];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(L"*.rtf", &FindFileData);
	//wcscpy(masmap[k], FindFileData.cFileName);
	k++;
	while (FindNextFile(hFind, &FindFileData))
	{
		wcscpy(masmap[k], FindFileData.cFileName);
		k++;
		//wprintf(FindFileData.cFileName);
	};

	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int s;
	wchar_t newmap[30];
	printf("Введите название карты:\n");
	wscanf(L"%s", newmap);
	//wcscpy(newmap, L"map");
	//wchar_t tex[100];
	//swprintf_s(tex, L"%d", k + 1);
	//wsprintf(tex, TEXT("%d"), k+1);
	//wcscat(newmap, tex);
	wcscat(newmap, L".rtf");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Сколько городов будет на карте?\n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	scanf("%d", &s);

	//remove("map2.txt");
	//city = fopen("cities.txt", "w+");
	file = _wfopen(newmap, L"w+");
	fprintf(file, "%d\n", s);
	char gor[30];
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Введите города:\n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	for (int i = 0; i < s; i++)
	{
		printf("%d - ", i); if (i == 0) {
			while (getchar() != '\n');
			gets_s(gor);
			strcpy(cit[i], gor);
		}
		else
		{
			gets_s(gor);
			strcpy(cit[i], gor);
		}
		if ((i + 1) == s)
			fprintf(file, "%d - %s", i, gor);
		else fprintf(file, "%d - %s\n", i, gor);
	}

	memset(cost, 0, sizeof(int) * 11 * 11);

	//remove("matrix.txt");
	//file = fopen("matrix.txt", "w+");
	//file = fopen("matrix.txt", "w+");
	//fprintf(file, "%d", s);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	int r;
	for (int i = 0; i<s; i++)
	{
		cost[i][i] = 0;
		for (int j = i + 1; j<s; j++) {
			printf("Введите расстояние %s - %s: ", cit[i], cit[j]);
			scanf("%d", &r);
			cost[i][j] = r;
			cost[j][i] = r;
		}
	}

	for (int i = 0; i<s; i++)
	{
		fprintf(file, "\n");
		for (int j = 0; j<s; j++) {
			fprintf(file, "%d ", cost[i][j]);
		}
	}

	//fclose(city);
	wcscpy(nowmap, newmap);
	fclose(file);
}

void input(wchar_t in[30])
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;

	memset(cost, 0, sizeof(int)*15 *15);
	memset(costf, 0, sizeof(int)*15*15);
	memset(costpos, 0, sizeof(int)*(17) *(17));
	memset(trip, 0, sizeof(int)*40);
	memset(trippr, 0, sizeof(int) * 40);
	memset(tripback, 0, sizeof(int) * 40);
	memset(posetit, 0, sizeof(int) * n);
	mintrip = 10000;
	koltrip = 1;

	file = _wfopen(in, L"r+");
	if (!file)
	{
		printf("Карта не загружена, следует создать новую\n");
		newmap();
	}

	char cf[30];
	int por = 0;
	fscanf(file, "%d", &kolcit);
	n = kolcit;
	fgets(cf, 30, file);
	int p = 0;
	for (int i = 0; i < kolcit; i++)
	{
		fflush(stdin);
		fseek(file, 4, SEEK_CUR);
		fgets(cit[por], 255, file);

		por++;
		p++;
	}



	for (int i = 0; i < kolcit; i++)
	{

		for (int j = 0; j < kolcit; j++)
		{
			fscanf(file, "%d", &cost[i][j]);
			//	if (cost[i][j]) masst[i]++;
			costf[i][j] = cost[i][j];
		}
	}
	fclose(file);

	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	//printf("\nЗагрузка карты прошла успешна \n");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 4));
	//system("pause");
}

void choosemap()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hcon = GetConsoleWindow();


	system("cls");
	int k = 0;
	wchar_t masmap[15][30];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(L"*.rtf", &FindFileData);
	wcscpy(masmap[k], FindFileData.cFileName);
	k++;
	while (FindNextFile(hFind, &FindFileData))
	{
		wcscpy(masmap[k], FindFileData.cFileName);
		k++;
		//wprintf(FindFileData.cFileName);
	};


	int kolpt = k;			//кол-во пунктов меню
	COORD *position = new COORD[kolpt];
	int punkt = 0;
	do
	{
		int xmax, ymax;
		// получение параметров окна 
		PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
		PWINDOWINFO pgwi = new WINDOWINFO;
		GetConsoleScreenBufferInfo(hConsole, pwi);
		GetWindowInfo(hcon, pgwi);
		xmax = pwi->dwSize.X;
		ymax = pwi->dwSize.Y;
		fflush(stdin);
		//printf("%s",map[0]);
		//puts(map[1]);



		int y0 = 6;

		for (int i = 0; i < kolpt; i++)
		{
			position[i].X = (xmax - 7) / 2;
			position[i].Y = y0 + i;

		}
		SetConsoleTextAttribute(hConsole, (WORD)((0 | 15)));
		system("cls");			// очистка окна
		char title[] = "Choose your map";
		COORD pos;
		pos.X = (xmax - strlen(title)) / 2;
		pos.Y = 5;
		SetConsoleCursorPosition(hConsole, pos);
		puts(title);
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
		//puts(map[0]);
		//puts(map[1]);
		for (int i = 0; i <kolpt; i++)
		{
			SetConsoleCursorPosition(hConsole, position[i]);
			wprintf(masmap[i]);
			printf("\n");
		}
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
		SetConsoleCursorPosition(hConsole, position[punkt]);	// выделение текущего пункта ярким цветом
		wprintf(masmap[punkt]);
		unsigned char ch;




		do
		{
			// обработка перемещения по меню клавишами со стрелками
			ch = getch();
			if (ch == 224)
			{
				ch = getch();
				switch (ch)
				{
				case 72:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					wprintf(masmap[punkt]);
					punkt--;
					if (punkt < 0) punkt = kolpt - 1;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					wprintf(masmap[punkt]); break;
				case 80:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					wprintf(masmap[punkt]);
					punkt++;
					if (punkt >(kolpt - 1)) punkt = 0;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					wprintf(masmap[punkt]); break;
				}
			}
		} while ((ch != 13) && (ch != 27));	// enter - выбор пункта меню
		if (ch == 27) goto tut;
		switch (punkt)
		{
		case 0:
			wcscpy(nowmap, masmap[0]); input(masmap[0]);
			//printf("первый файл"); system("pause");
			break;
		case 1:
			wcscpy(nowmap, masmap[1]); input(masmap[1]);
			break;
		case 2:
			wcscpy(nowmap, masmap[2]); input(masmap[2]);
			break;
		case 3:
			wcscpy(nowmap, masmap[3]); input(masmap[3]);
			break;
		case 4:
			wcscpy(nowmap, masmap[4]); input(masmap[4]);
			break;
		case 5:
			wcscpy(nowmap, masmap[5]); input(masmap[5]);
			break;
		case 6:
			wcscpy(nowmap, masmap[6]); input(masmap[6]);
			break;
		case 7:
			wcscpy(nowmap, masmap[7]); input(masmap[7]);
			break;
		case 8:
			wcscpy(nowmap, masmap[8]); input(masmap[8]);
			break;
		case 9:
			wcscpy(nowmap, masmap[9]); input(masmap[9]);
			break;
		}

	} while (punkt >= kolpt);

tut:
	system("cls");
}



void start() {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Загружены следующие города: \n");
	for (int i = 0; i < kolcit; i++)
	{

		printf("%d - %s", i, cit[i]);

	}
	printf("\n\n");

repeat:
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Введите количество городов, которые вы хотите посетить: \n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	scanf("%d", &np);
	if (np < 2) goto repeat;
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Выберите города, при условии, что первый город будет тот, в котором вы находитесь \n");

	char c[30];

	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));

	for (int i = 0; i < np; i++)
	{
		scanf("%d", &posetit[i]);
	}
	int in = 1, jn = 1;
	for (int i = 0; i < np; i++)
	{
		costpos[i + 1][0] = posetit[i];
		costpos[0][i + 1] = posetit[i];
	}

	for (int i = 0; i <n; i++)

		if ((costpos[in][0]) == i)
		{
			costpos[in][in] = 0;
			for (int c = 1; c <= np; c++)
			{
				costpos[in][c] = cost[i][posetit[jn - 1]];
				jn++;
			}
			in++;
			if (in == np + 1)break;
			jn = 1;
			i = -1;
		}
	for (int i = 0; i <np; i++)
		costpos[in][i] = 0;
	file = fopen("costposetit.txt", "w+");
	for (int i = 0; i <= np; i++)
	{
		fprintf(file, "\n");

		for (int j = 0; j <= np; j++)
			fprintf(file, "%d ", costpos[i][j]);
	}
	fclose(file);
	printf("\n");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 4));
	system("pause");

}

void searchmintrip(int st, int en, int rasst, int *indextrip, int *proidput, int *skud, int **masindrem) //skud - сколько удалить промежуточных точек ; proidenput - для восстановления маршрута
{

	int **masind;
	masind = new int*[2];
	for (int i = 0; i < 2; i++)
		*masind = new int[15]; //для удаления посещенных, хранит индексы 
	int i, j;
	int pos;
	trippr[*indextrip] = en; //посещенная вершина
							 /*if (trippr[1] == 3)
							 printf("");*/
	rasst += costf[st][en]; //
	st = en; //делаем конечную точку из конечной в начальную для дальнейшего движения
	int pornom = 0; //порядковый номер стартовой точки в посещении
	for (int b = 0; b < np; b++)
		if (st == posetit[b])pornom = b;
	costpos[np + 1][pornom + 1]++; //для цикла с вариантами движения

	if (rasst > mintrip)
		goto here;
	pos = 0;
	for (int c = 1; c <= np; c++) {
		if (costpos[np + 1][c] != 0)
			(pos)++;
	}
	while (pos != np)
	{

		{

			{
				for (j = 1; j <= np; j++)
					if (costpos[np + 1][j] == 0)
					{
						int inexstolbca;
						for (int v = 1; v <= np; v++)
							if (st == costpos[v][0]) inexstolbca = v;

						int a, b;
						a = costpos[inexstolbca][0];
						b = costpos[0][j];
						if ((costpos[inexstolbca][j] == 0) || (costf[a][b] != costpos[inexstolbca][j]))
						{
							int *kD; //пройденное количество точек при перемещении от одной к другой для восстановления пути
							int nulkd = 0;
							kD = &nulkd;
							int nul1 = 0;
							int *skst = &nul1;
							masind = Dijkstra(st, costpos[0][j], indextrip, skst, kD); //sk - сколько удалить вершин
																					   //printf("%d", masind[1][0]);
																					   //pos = 0;
																					   /*for (int c = 1; c <= np; c++) {

																					   if (costpos[np + 1][c] != 0)
																					   (pos)++;
																					   }*/
							searchmintrip(st, costpos[0][j], rasst, indextrip, kD, skst, masind); //skts - сколько удалить степеней 
						}
						else
						{

							(*indextrip)++;
							trippr[*indextrip] = costpos[0][j];
							int odin = 1;
							int *pa;
							pa = &odin;
							int null = 0;
							int *nanull = &null;
							searchmintrip(st, costpos[0][j], rasst, indextrip, pa, nanull, masind);
						}

					}

			}
			if (j> np) break;
		}

	}

here:
	if ((rasst < mintrip) && (pos == np)) //проверяем, является ли этот путь наилучшим
	{
		mintrip = rasst;
		memcpy(trip, trippr, sizeof(trippr));
		koltrip = *indextrip + 1;
	}
	for (int v = 0; v < *proidput; v++) { //для возвращения на предыдущую вершину

		trippr[*(indextrip)-v] = 0;
	}

	*indextrip -= *proidput; //изменения индекса для построения дальнейшего маршрута
	for (int a = 0; a < *skud; a++) //вычитаем степени посещенных вершин на данном этапе
		for (int j = 1; j <= np; j++)
		{
			//if (masind[0][a] == costpos[0][j])
			if (masindrem[0][a] == costpos[0][j])
			{

				/*costpos[np + 1][j] = *(*(masind + 1) + a);
				*(*(masind + 1) + a)=0;
				*/
				costpos[np + 1][j] -= masindrem[1][a];
				masindrem[1][a] = 0;
			}

		}
	costpos[np + 1][pornom + 1]--; //вычитаем степень посещенной конечной вершины

								   //pos = 0;
								   //for (int c = 1; c <= np; c++) { //высчитываем количество посещенных точек
								   //	
								   //	if (costpos[np + 1][c] != 0)
								   //		(pos)++;
								   //}

}

void createmap(int wh)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);


	towns *tow = new towns[n];
	int de = 0;
	//puts(cit[0]);
	for (int i = 0; i < kolcit; i++)
	{
		int w = 250 * cos(de*3.1415926 / 180);
		int h = 250 * sin(de*3.1415926 / 180);
		int kolstr = strlen(cit[i]);


		WCHAR  tex[100];
		wsprintf(tex, TEXT("%d"), i);



		TextOut(hDC, WIDTH / 2 + (w)+20 * cos(de*3.1415926 / 180), HEIGHT / 2 + (h)+20 * sin(de*3.1415926 / 180), tex, 2);

		de += 360 / kolcit;
		tow[i].x = WIDTH / 2 + w;
		tow[i].y = HEIGHT / 2 + h;
		///system("pause");
		if (wh == 0) {
			printf("%d - ", i); puts(cit[i]);
		}
	}

	int movx, movy;
	int tox, toy;

	//DeleteObject(hPen);
	//SetTextColor(hDC, RGB(0, 0xFF, 0));
	//if (wh == 1) {
	for (int i = 0; i < n; i++)
	{

		for (int j = i + 1; j < n; j++) {
			if (cost[i][j] != 0)
			{
				int a, b, c;
				if (wh == 0) {
					a = rand() % 256;
					b = rand() % 256;
					c = rand() % 256;
				}
				else
				{
					a = 90;
					b = 94;
					c = 90;

				}
				HPEN hPen = CreatePen(PS_SOLID, 3, RGB(a, b, c));
				HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
				movx = tow[i].x;
				movy = tow[i].y;
				MoveToEx(hDC, movx, movy, NULL);
				tox = tow[j].x;
				toy = tow[j].y;
				LineTo(hDC, tox, toy);
				DeleteObject(hPen);
			}
		}
	}
	//}
	//else
	//{
	float a = 9.0;
	float b = 33.0;
	float c = 7.0;
	float as, bs, cs;
	if (wh == 1) {
		as = (65 - 9) / koltrip;
		bs = (255 - 33) / koltrip;
		cs = (45 - 7) / koltrip;
	}
	else if (wh == 2)
	{
		as = (65 - 9) / kolback;
		bs = (255 - 33) / kolback;
		cs = (45 - 7) / kolback;
	}
	if (wh == 1) {
		for (int i = 0; i < (koltrip - 1); i++)
		{
			for (int j = 0; j < n; j++)
				if (trip[i] == j)
				{
					Sleep(500);
					a = round(a + as);
					b = round(b + bs);
					c = round(c + cs);
					HPEN hPen = CreatePen(PS_SOLID, 5, RGB(a, b, c));
					HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
					movx = tow[j].x;
					movy = tow[j].y;
					MoveToEx(hDC, movx, movy, NULL);
					tox = tow[trip[i + 1]].x;
					toy = tow[trip[i + 1]].y;
					LineTo(hDC, tox, toy);
					DeleteObject(hPen);
				}
		}
	}
	else if (wh == 2)
	{

		for (int i = 0; i < (kolback - 1); i++)
		{
			for (int j = 0; j < n; j++)
				if (tripback[i] == j)
				{
					Sleep(500);
					a = round(a + as);
					b = round(b + bs);
					c = round(c + cs);
					HPEN hPen = CreatePen(PS_SOLID, 5, RGB(a, b, c));
					HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
					movx = tow[j].x;
					movy = tow[j].y;
					MoveToEx(hDC, movx, movy, NULL);
					tox = tow[tripback[i + 1]].x;
					toy = tow[tripback[i + 1]].y;
					LineTo(hDC, tox, toy);
					DeleteObject(hPen);
				}
		}
	}


	//}
	//DeleteObject(hPen);
	delete[]tow;
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 4));
	if (wh == 0)system("pause");
}

void ouput()
{
	int *a;
	int nul = 0;
	a = &nul;
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int por = 0;

	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Маршрут из города:");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
	printf("%s", cit[trip[0]]); SetConsoleTextAttribute(hConsole, (WORD)((0) | 15)); printf("в ");
	if (np>2)
	{
		printf("города: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
		for (int c = 1; c < np; c++)
			if (posetit[c] == (n - 1))
				printf("*%s\n", cit[posetit[c]]);
			else printf("*%s", cit[posetit[c]]);
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
			printf("построен \n\n");
			system("pause");
			system("cls");
			printf("Следуйте в указанном порядке:\n");
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
			for (int i = 0; i < koltrip; i++) {
				if (trip[i] == (n - 1))
					printf("%d - %s\n", trip[i], (cit[trip[i]]));
				else printf("%d - %s", trip[i], (cit[trip[i]]));
			}

	}
	else {
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("город: "); SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
		for (int c = 1; c < np; c++)
			if (posetit[c] == (n - 1))
				printf("*%s\n", cit[posetit[c]]);
			else printf("*%s", cit[posetit[c]]);
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
			printf("построен\n\n");
			system("pause");
			system("cls");
			printf("Следуйте в указанном порядке:\n"); SetConsoleTextAttribute(hConsole, (WORD)((0) | 10));
			for (int i = 0; i < koltrip; i++) {
				if (trip[i] == (n - 1))
					printf("%d - %s\n", trip[i], (cit[trip[i]]));
				else printf("%d - %s", trip[i], (cit[trip[i]]));
			}
	}
	createmap(1);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("\n\nМинимальное расстояние:"); SetConsoleTextAttribute(hConsole, (WORD)((0 | 6))); printf("%d\n", mintrip);
	int otvet;
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("\nВы хотите проложить путь \nдо начальной точки отправления?\nОтветьте 1-ДА; 0-НЕТ\n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	scanf("%d", &otvet);
	printf("\n");
	if (otvet)
	{
		system("cls");
		int k1 = 0, k2 = 1000;
		int *nak1 = &k1, *nak2 = &k2;
		int **p = Dijkstra(trip[koltrip - 1], trip[0], nak1, nak2, a);
		int a = trip[koltrip - 1];
		int b = trip[0];
		createmap(2);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("\nРасстояние на обратную дорогу составляет:");
		SetConsoleTextAttribute(hConsole, (WORD)((0 | 6)));
		printf("%d\n", costf[a][b]);

	}
	printf("\n");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 4));
	system("pause");

}
void main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	wcscpy(nowmap, L"map1.rtf");
	/*file = fopen("masmap.txt", "r+");
	fscanf(file, "%d", &kolmap);
	char f[30];
	fgets(f, 10, file);
	fgets(map[0], 30, file);
	strcpy(nowmap, map[0]);
	fclose(file);
	puts(nowmap);*/


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hcon = GetConsoleWindow();
	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(hConsole, false, &cfi);
	COORD fs = GetConsoleFontSize(hConsole, cfi.nFont);
	PCONSOLE_FONT_INFOEX ccf = new CONSOLE_FONT_INFOEX;
	(*ccf).dwFontSize.X = 12;
	(*ccf).dwFontSize.Y = 20;
	(*ccf).nFont = 11;
	(*ccf).cbSize = sizeof(CONSOLE_FONT_INFOEX);
	ccf->FontWeight = 400;
	lstrcpyW((*ccf).FaceName, L"Lucida Console");
	(*ccf).FontFamily = FF_DONTCARE;
	bool b = SetCurrentConsoleFontEx(hConsole, false, ccf);
	fs = GetConsoleFontSize(hConsole, cfi.nFont);
	int n = 5;			//кол-во пунктов меню
	COORD position[5];
	int punkt = 0;
	char names[5][100] = { "Загрузка имеющейся карты", "Задать новую карту дорог","Выбрать карту","Начать поиск оптимального маршрута","Выход" };
	int xmax, ymax;

	trippr[0] = cost[0][1]; //начальная точка маршрута 
	int ia = 0;
	int p = 0;
	int odin = 1;
	int *naodin;
	int *pa;
	pa = &p;
	naodin = &odin;
	int *indextrip = &ia;
	mintrip = 10000;
	int **mas;
	mas = new int*[2];
	for (int i = 0; i < 2; i++)
		*mas = new int[15]; //для удаления посещенных, хранит индексы 

	do
	{


		// получение параметров окна 
		PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
		PWINDOWINFO pgwi = new WINDOWINFO;
		GetConsoleScreenBufferInfo(hConsole, pwi);
		GetWindowInfo(hcon, pgwi);
		xmax = pwi->dwSize.X;
		ymax = pwi->dwSize.Y;

		int y0 = 8;
		for (int i = 0; i < n; i++)
		{
			position[i].X = (xmax - strlen(names[i])) / 2;
			position[i].Y = y0 + i;
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0 | 15)));
		system("cls");			// очистка окна
		char title[] = "Choose your trip";
		COORD pos;
		pos.X = (xmax - strlen(title)) / 2;
		pos.Y = 5;
		SetConsoleCursorPosition(hConsole, pos);
		puts(title);
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
		for (int i = 0; i < 5; i++)
		{
			SetConsoleCursorPosition(hConsole, position[i]);
			puts(names[i]);
		}
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
		SetConsoleCursorPosition(hConsole, position[punkt]);	// выделение текущего пункта ярким цветом
		puts(names[punkt]);
		unsigned char ch;




		do
		{
			// обработка перемещения по меню клавишами со стрелками
			ch = getch();
			if (ch == 224)
			{
				ch = getch();
				switch (ch)
				{
				case 72:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					puts(names[punkt]);
					punkt--;
					if (punkt < 0) punkt = 4;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
				case 80:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					puts(names[punkt]);
					punkt++;
					if (punkt > 4) punkt = 0;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
				}
			}
		} while (ch != 13);	// enter - выбор пункта меню
		switch (punkt)
		{
		case 0:
			input(nowmap);  createmap(0);
			break;
		case 1:
			newmap();
			break;
		case 2:
			choosemap();
			break;
		case 3:
			input(nowmap); floid(); start(); searchmintrip(costpos[0][1], costpos[0][1], 0, indextrip, pa, pa, mas); ouput();
			break;

		}

	} while (punkt != 4);


	system("cls");

	//system("pause");
}