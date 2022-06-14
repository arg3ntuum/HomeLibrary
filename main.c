#include "source.h"
////////////////////////////////////////////////////////////
// функции с курсовой /*//*/. После обновы для гита /*....*/
////////////////////////////////////////////////////////////
/*.............................*/
/*сохранение масива А в масив Б*/
/*.............................*/
void saveTo(char *a, char *b) {
	for (int i = 0; i < N; i++) {
		a[i] = b[i];
	}
}
/*...........................*/
/*считывание числа безопасное*/
/*...........................*/
void takeNumberWithoutProblem(int *a) {
	char temp[N];
	int error = 0;
	do {
		error = 0;
		scanf_s("%s", &temp, N - 1);
		for (int a = 0; a < strlen(temp); a++)
			if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
				error = 1;
		if (error == 1)
			printf("Вводите только числа!\n");
		else {
			*a = atoi(temp);
			break;
		}
	} while (1);
}
/*////////////////////////*/
/* ініціалізація структур */
/*////////////////////////*/
Book initKniga(Book* massive, int dimension) {
	SLASH;
	int vdoma = 0, marker = 0;
	Book add;
	printf("\nВведите название новой книги: ");
	scanf_s("%s", &add.nazva, N);
	printf("\nВведите автора новой книги: ");
	scanf_s("%s", &add.autor, N);
	printf("\nВведите роздел новой книги: ");
	scanf_s("%s", &add.rozdil, N);
	do {
		printf("\nВведите номер места новой книги: ");
		takeNumberWithoutProblem(&add.nomer_mesta);
		for (int i = 0; i < dimension; i++)
			if ((massive[i].nomer_mesta == add.nomer_mesta) || add.nomer_mesta <= 0)
				marker = 1;
		if (marker == 0)
			break;
		else marker = 0;
	} while (1);

	do {
		printf("Введите статус книги книги(1-дома/0-библиотека): ");
		takeNumberWithoutProblem(&add.vdoma);
		if (add.vdoma == 0)
			break;
		else if (add.vdoma == 1)
		{
			printf("Введите фамилию заемщика книги: ");
			scanf_s("%s", &add.prizvische_pozik, N);
			break;
		}
	} while (1);
	return add;
}
Book initKnigaFileR(FILE* data) {
	Book kniga;
	fscanf_s(data, "%s ", kniga.autor, N);
	fscanf_s(data, "%s ", kniga.nazva, N);
	fscanf_s(data, "%s ", kniga.rozdil, N);
	fscanf_s(data, "%d ", &kniga.nomer_mesta);
	fscanf_s(data, "%d ", &kniga.vdoma);
	fscanf_s(data, "%s ", kniga.prizvische_pozik, N);
	return kniga;
}
/*///////////////////////////////////////*/
/* створення динамічного масиву структур */
 /*///////////////////////////////////////*/
Book* initArray(char fileName[], int dimension) {
	Book* massive = (Book*)malloc(dimension * sizeof(Book));
	if (massive == NULL)
		return NULL;
	int vubor = 0;
	FILE* data;
	fopen_s(&data, fileName, "r");
	if (!data) {
		ERROR;
	}
	for (int i = 0; i < dimension; i++)
		massive[i] = initKnigaFileR(data);
	fclose(data);
	return massive;
}
Book* initArrayStart(int dimension) {
	Book* massive = (Book*)malloc(dimension * sizeof(Book));
	if (massive == NULL)
		return NULL;
}
/*/////////////*/
/*Запись в файл*/
/*/////////////*/
void write(Book kniga, FILE* data) {
	fprintf(data, "%s ", kniga.autor);
	fprintf(data, "%s ", kniga.nazva);
	fprintf(data, "%s ", kniga.rozdil);
	fprintf(data, "%d ", kniga.nomer_mesta);
	if (kniga.vdoma == 1)
		fprintf(data, "%d %s\n", kniga.vdoma, kniga.prizvische_pozik);
	else //(massive.vdoma == 0)
		fprintf(data, "%d -\n", kniga.vdoma);
}
void initWrite(char fileName[], Book* massive, int dimension, int rezum) {
	FILE* data;
	if (rezum == 2)
		fopen_s(&data, fileName, "w");//запись в новый файл
	else fopen_s(&data, fileName, "ab");//дозапись и чтение
	if (!data) {
		ERROR;
	}
	for (int i = 0; i < dimension; i++)
		write(massive[i], data);
	if (rezum == 2)
		fprintf(data, "- - - 0 0 -\n");
	fclose(data);
	//puts("Книги в библиотеке!");
}
/*///////////////////////////////////////*/
/* відображення інформації про структуру */
/*///////////////////////////////////////*/
void displayCalls(Book kniga, int i) {
	printf("|%4d.|%10s | %16s | %10s | %7d | ",i + 1, kniga.autor, kniga.nazva, kniga.rozdil, kniga.nomer_mesta);
	if(kniga.vdoma == 1)
		printf("      дома | %10s |\n", kniga.prizvische_pozik);
	else printf("библиотека |            |\n");
	TIRE;
}
/*///////////////////////////////////////////////////*/
/* передача структури в функцію для друку інформації */
/*///////////////////////////////////////////////////*/
void displayArray(Book* massive, int dimension){
	SLASH;
	TIRE;
	printf("|  #  |   Автор   |     Название     |   Роздел   | # места |   Статус   |   Заемщик  |\n");
	TIRE;
	for (int i = 0; i < dimension; i++) {
		displayCalls(massive[i], i);
	}
}
/*///////////////////////////////*/
/* редактор для массива структур */
/*///////////////////////////////*/
void redactorBookRozdil(Book* massive, int dimension, int choose_book) {
	char str[N] = { 0 };
	int congrats = 0;
	do {
		puts("Введите новый роздел книги: ");
		scanf_s("%s", str, N);
		printf("\nВы подтверждаете вашу строку '%s'(1-да, другое - нет):", str);
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1 && str != "")
		{
			for (int i = 0; i < N; i++) {
				massive[choose_book].rozdil[i] = str[i];
			}
			break;
		}
	} while (1);
}
void redactorBookAutor(Book* massive, int dimension, int choose_book) {
	char str[N] = { 0 };
	int congrats = 0;
	do {
		puts("Введите нового автора книги: ");
		scanf_s("%s", str, N);
		printf("\nВы подтверждаете вашу строку '%s'(1-да, другое - нет):", str);
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1 && str != "")
		{
			for (int i = 0; i < N; i++) {
				massive[choose_book].autor[i] = str[i];
			}
			break;
		}
	} while (1);
}
void redactorBookName(Book* massive, int dimension, int choose_book) {
	char str[N] = { 0 };
	int congrats = 0;
	do {
		puts("Введите новоe название книги: ");
		scanf_s("%s", str, N);
		printf("\nВы подтверждаете вашу строку '%s'(1-да, другое - нет):", str);
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1 && str != "")
			{
			for (int i = 0; i < N; i++) {
				massive[choose_book].nazva[i] = str[i];
			}
			break;
		}
	} while (1);
}
void redactorBookStatusDelete(Book* massive, int dimension, int choose_book) {
	char book_taker[N] = "-\0";
	int congrats = 0;
	do {
		printf("\nВы подтверждаете возвращение книги(1-да, 0 - нет): ");
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1)
		{
			massive[choose_book].vdoma = 0;
			for (int i = 0; i < N; i++) {
				massive[choose_book].prizvische_pozik[i] = book_taker[i];
			}
			puts("Статус успешно изменен!");
			break;
		}
		else if (congrats == 0)
			break;
	} while (1);
}
void redactorBookStatusAdd(Book* massive, int dimension, int choose_book) {
	massive[choose_book].vdoma = 1;
	char book_taker[N] = {0};
	int congrats = 0;
	do {
		puts("Введите нового заемщика: ");
		scanf_s("%s", book_taker, N - 1);
		printf("\nВы подтверждаете вашу строку '%s'(1-да, другое - нет):", book_taker);
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1 && book_taker != "")
		{
			for (int i = 0; i < N; i++) {
				massive[choose_book].prizvische_pozik[i] = book_taker[i];
			}
			puts("Статус успешно изменен!");
			break;
		}
	} while (1);
}
void redactorBookStatusMenu(Book* massive, int dimension, int choose_book) {
	int congrats = 0;
	if (massive[choose_book].vdoma == 1) 
		puts("На данный момент эта книга находится на руках!");
	else puts("На данный момент эта книга находится в библиотеке!");
	do {
		printf("\nВы подтверждаете что хoтите изменить статус книги(1-да, 0 - нет): ");
		takeNumberWithoutProblem(&congrats);
		if (congrats == 1) {
			if (massive[choose_book].vdoma == 1) {
				redactorBookStatusDelete(massive, dimension, choose_book);
				break;
			}
			else {
				redactorBookStatusAdd(massive, dimension, choose_book);
				break;
			}
		}
		else if (congrats == 0)
			break;
	} while (1);
}
void redactorBookNumMesto(Book* massive, int dimension, int choose_book) {
	int new_num_mesto = 0, yes = 0, temp = 0, zanyato = 0;
	SLASH;
	do {
		puts("Введите новый номер:");
		takeNumberWithoutProblem(&new_num_mesto);
		printf("\nВаше новое место = %d\
				\nВы подтверждаете(1-да. 0 - нет): ", new_num_mesto);
		takeNumberWithoutProblem(&yes);
		if (yes == 1 && new_num_mesto > 0)
			break;
	} while (1);
	for (int i = 0; i < dimension; i++)
		if (massive[i].nomer_mesta == new_num_mesto)
			zanyato = i;
	if (zanyato != 0 ) {
	temp = massive[choose_book].nomer_mesta;
	massive[zanyato].nomer_mesta = 99999;
	massive[choose_book].nomer_mesta = new_num_mesto;
	massive[zanyato].nomer_mesta = temp;
	}
	else massive[choose_book].nomer_mesta = new_num_mesto;
	
}
void redactorBookZaemshik(Book* massive, int dimension, int choose_book) {
	if (massive[choose_book].vdoma == 1) 
	{
		char str[N] = {0};
		int congrats = 0;
		do {
			puts("Введите нового заемщика: ");
			scanf_s("%s", str, N);
			printf("\nВы подтверждаете вашу строку '%s'(1-да, другое - нет):", str);
			takeNumberWithoutProblem(&congrats);
			if (congrats == 1 && str != "") {
				for (int i = 0; i < N; i++) 
					massive[choose_book].prizvische_pozik[i] = str[i];
				break;
			}
		} while (1);
	}
	else puts("Книга находится в библиотеке! Используйте другую фукнцию!");
}
void redactorBookMenu(Book* massive, int dimension, int choose_book) {
	 int choose_element = 0;
	 do {
		 SLASH;
		 puts("	  РЕДАКТОР КНИГ\
				\n1.Изменить номер места книги;\
				\n2.Изменить статус книги;\
				\n3.Изменить заемщика книги;\
				\n4.Изменить название книги;\
				\n5.Изменить автора книги;\
				\n6.Изменить роздел книги;\
				\n0.Exit;\
				\nВаш выбор: ");
		 takeNumberWithoutProblem(&choose_element);
		 if (choose_element == 0)
			 break;
		 else if (choose_element == 1)
			 redactorBookNumMesto(massive, dimension, choose_book);
		 else if (choose_element == 2)
			 redactorBookStatusMenu(massive, dimension, choose_book);
		 else if (choose_element == 3)
			 redactorBookZaemshik(massive, dimension, choose_book);
		 else if (choose_element == 4)
			 redactorBookName(massive, dimension, choose_book);
		 else if (choose_element == 5)
			 redactorBookAutor(massive, dimension, choose_book);
		 else if (choose_element == 6)
			 redactorBookRozdil(massive, dimension, choose_book);
	 } while (1);
 }
void redactorBook(Book* massive, int dimension) {
	 int choose_book = 0;
	 displayArray(massive, dimension);
	 SLASH;
	 do {
		 puts("Введите номер книги по таблице, для изменения её параметров(0-exit):");
		 takeNumberWithoutProblem(&choose_book);
		 choose_book -= 1;
		 if (choose_book < dimension && choose_book > -1) {
			 TIRE;
			 displayCalls(massive[choose_book], choose_book);
			 redactorBookMenu(massive, dimension, choose_book);
			 break;
		 }
		 if (choose_book == -1)
			 break;
	 } while (1);
 }
void redactor(Book* massive, int dimension){
	int choose_redaktor = 0;
	do {
		puts("	  РЕДАКТОР КНИГ\
				\n1.Вывести все книги;\
				\n2.Выбрать книгу для изменений;\
				\n0.Exit;\
				\nВаш выбор: ");
		takeNumberWithoutProblem(&choose_redaktor);
		if (choose_redaktor == 0)
			break;
		else if (choose_redaktor == 1){
			displayArray(massive, dimension);
			SLASH;
		}
		else if (choose_redaktor == 2) {
			redactorBook(massive, dimension);
			SLASH;
		}
	} while (1);
}
/*//////////////////////////////////*/
/*Добавление нового елемента массива*/
/*//////////////////////////////////*/
void writeElementInFile(FILE* data, Book add) {
	fprintf(data, "%s ", add.autor);
	fprintf(data, "%s ", add.nazva);
	fprintf(data, "%s ", add.rozdil);
	fprintf(data, "%d ", add.nomer_mesta);
	if (add.vdoma == 1)
		 fprintf(data, "%d %s\n", add.vdoma, add.prizvische_pozik);
	else fprintf(data, "%d -\n", add.vdoma);
}
void addElement(char fileName[], Book* massive, int dimension) {
	FILE* data;
	Book addKniga = initKniga(massive, dimension);
	fopen_s(&data, fileName, "w");//запись в новый файл
	if (!data) {
		ERROR;
	}
	for (int i = 0; i < dimension; i++)
		write(massive[i], data);
	writeElementInFile(data, addKniga);
	fprintf(data, "- - - 0 0 -\n");
	fclose(data);
}
/*//////////////////////////*/
/*Удалить елемент из массива*/
/*//////////////////////////*/
void deleteElementChoosed(char fileName[], Book* massive, int dimension, int choose_book){
	FILE* data;
	fopen_s(&data, fileName, "w");//запись в новый файл
	if (!data) {
		ERROR;
	}
	for (int i = 0; i < dimension; i++)
		if (i != choose_book)
			write(massive[i], data);
	fprintf(data, "- - - 0 0 -\n");
	fclose(data);
}
void deleteElement(char fileName[], Book* massive, int dimension) {
	int choose_book = 0, congrats = 0;
	displayArray(massive, dimension);
	do {
		puts("Введите номер книги по таблице для удаления(0-exit):");
		takeNumberWithoutProblem(& choose_book);
		choose_book -= 1;
		if (choose_book < dimension && choose_book > -1) {
			TIRE;
			displayCalls(massive[choose_book], choose_book);
			printf("\nВы подтверждаете удаление книги(1-да, 0 - нет): ");
			scanf_s("%d", &congrats);
			if (congrats == 1)
				deleteElementChoosed(fileName, massive, dimension, choose_book);
			break;
		}
		if (choose_book == -1)
			break;
	} while (1);
}
/*/////////////////////*/
/* сортування структур */
/*/////////////////////*/
void sortName(Book* massive, int dimension){
	Book temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].autor, massive[j - 1].autor) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortNazva(Book* massive, int dimension) {
	Book temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].nazva, massive[j - 1].nazva) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortNomerMesta(Book* massive, int dimension) {
	Book temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].nomer_mesta < massive[j - 1].nomer_mesta){
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
void sortMenu(Book* massive, int dimension) {
	int sort_vibor = 0;
	puts("Выберете способ сортировки:\n1.Название;\n2.Автор;\n3.Номер места;\nВаш выбор: ");
	takeNumberWithoutProblem(&sort_vibor);
	if (sort_vibor == 1)
		sortNazva(massive, dimension);
	else if (sort_vibor == 2)
		sortName(massive, dimension);
	else if (sort_vibor == 3)
		sortNomerMesta(massive, dimension);
	else puts("Error");
}
/*////////////////*/
/* поиск структур */
/*////////////////*/
int displayChoiseNazva(Book* massive, int dimension, int i, char* poisk_nazva)
{
	if (massive[i].nazva[0] == poisk_nazva[0])
		if (strstr(massive[i].nazva, poisk_nazva))
			return 1;
		else return 0;
	else return 0;
}
int displayChoiseAutor(Book* massive, int dimension, int i, char* poisk_avtor)
{
	if (massive[i].autor[0] == poisk_avtor[0])
		if (strstr(massive[i].autor, poisk_avtor))
			return 1;
		else return 0;
	else return 0;
}
int displayChoiseRozdil(Book* massive, int dimension, int i, char* poisk_vidav)
{
	if (massive[i].rozdil[0] == poisk_vidav[0])
		if (strstr(massive[i].rozdil, poisk_vidav))
			return 1;
		else return 0;
	else return 0;
}
void displayChoise(Book* massive, int dimension)
{
	int sort_vibor[E] = { 0 }, vibor1 = 0, vibor2 = 0, vibor3 = 0;// sort = 0;
	printf("\nВыберете способ искать:\n1.Название;\n2.Автор;\n3.Видом;\n(0 - выход)\nВаш выбор: ");
	for (int i = 0; i < E; i++)
	{
		takeNumberWithoutProblem(&sort_vibor[i]);
		if (sort_vibor[i] == 0)
			break;
	}
	for (int i = 0; i < E; i++)
	{
		if (sort_vibor[i] == 0)
			break;
		else if (sort_vibor[i] == 1)
			vibor1 = 1;
		else if (sort_vibor[i] == 2)
			vibor2 = 1;
		else if (sort_vibor[i] == 3)
			vibor3 = 1;
		else;
	}

	char poisk_nazva[N] = { 0 }, poisk_rozdil[N] = { 0 }, poisk_avtor[N] = { 0 };
	for (int i = 0; i < E; i++) {
		if (vibor1 == 1) {
			printf("\nДля поиска по ключевому названию введите его: ");
			scanf_s("%s", poisk_nazva, N);
			puts(poisk_nazva);
			vibor1 = 2;
		}
		else if (vibor2 == 1)
		{
			printf("\nДля поиска по автору введите ее: ");
			scanf_s("%s", poisk_avtor, N);
			puts(poisk_avtor);
			vibor2 = 2;
		}
		else if (vibor3 == 1)
		{
			printf("\nДля поиска розделу введите ее: ");
			scanf_s("%s", poisk_rozdil, N);
			puts(poisk_rozdil);
			vibor3 = 2;
		}
	}
	int  kostil = 1, oshibka_poiska = 0;
	for (int i = 0, truue = 1; i < dimension; i++, truue = 1)
	{
		switch (kostil)
		{
		case 1:
		{
			if (vibor1 == 2 && truue == 1)
				truue = displayChoiseNazva(massive, dimension, i, poisk_nazva);
		}
		case 2:
		{
			if (vibor2 == 2 && truue == 1)
				truue = displayChoiseAutor(massive, dimension, i, poisk_avtor);
		}
		case 3:
		{
			if (vibor3 == 2 && truue == 1)
				truue = displayChoiseRozdil(massive, dimension, i, poisk_rozdil);
		}
		case 4:
		{
			if (oshibka_poiska == 0 && (i == dimension - 1) && truue == 0) {
				SLASH;
				puts("\nК сожалению, мы ничего не нашли(");
			}

			if (truue == 0)
				break;
			TIRE;
			displayCalls(massive[i], i);
			oshibka_poiska++;
		}
		}
	}
}
void displayСonsensus(Book* massive, int dimension) {
	char slovo[N] = {0};
	int n = 0;
	printf("\nДля поиска по ключевому слову введите его: ");
	scanf_s("%s", slovo, N -1);
	printf("slovo = %s\n", slovo);
	for (int i = 0; i < dimension; i++) {
		if (n == 0)
			n = strstr(massive[i].autor, slovo);
		if (n == 0)
			n = strstr(massive[i].nazva, slovo);
		if (n == 0)
			n = strstr(massive[i].rozdil, slovo);
		if (n != 0) {
			TIRE;
			displayCalls(massive[i], i);
			n = 0;
		}	
	}
}
void displayMenu(Book* massive, int dimension) {
	int choose = 0;
	do {
		printf("\nВыберите режим поиска:\n1.Точный ввод\n2.Поиск по совпадению\n0.Exit\nВаш выбор:");
		takeNumberWithoutProblem(&choose);
		if (choose == 0)
			break;
		else if (choose == 1)
			displayChoise(massive, dimension);
		else if (choose == 2)
			displayСonsensus(massive, dimension);
	} while (1);
}
/*/////////////////////////////////*/
/*Считываем конец структуры в файле*/
/*/////////////////////////////////*/
int check(char fileName[]) {
	int i;
	Book kniga;
	FILE* data;
	fopen_s(&data, fileName, "r");//чтение
	if (!data) {
		ERROR;
	}
	for (i = 0; i < 999; i++) {
		fscanf_s(data, "%s ", kniga.autor, N);
		fscanf_s(data, "%s ", kniga.nazva, N);
		fscanf_s(data, "%s ", kniga.rozdil, N);
		fscanf_s(data, "%d ", &kniga.nomer_mesta);
		fscanf_s(data, "%d ", &kniga.vdoma);
		fscanf_s(data, "%s ", kniga.prizvische_pozik, N);
		if (kniga.nomer_mesta == 0 && kniga.vdoma == 0)
			break;
	}
	fclose(data);
	return i;
}
/*..............*/
/*проверка файла*/
/*..............*/
int checkFileToOpen(char fileName[]) {
	FILE* data;
	char temp[3] = { 0 };
	fopen_s(&data, fileName, "rb+");
	if (!data) {
		printf("Файл не был открыт!\n");
		return 1;//ошибка
	}
	else {
		if (fgets(temp, 2, data) == NULL) {//если ничего не считало
			fclose(data);
			printf("Файл не был считан.\nВозможно в файле отсутствуют данные!\n");
			return 1;//ошибка
		}
		fclose(data);
	}
	return 0;
}
void takeNameFile(char data[]) {
	char dataFile[N] = {0};
	do {
		puts("Введите файл подрузки: ");
		scanf_s("%s", dataFile, N - 1);
		if (checkFileToOpen(dataFile) == 0)
			break;
		else puts("Введите название файла заново.");
	} while (1);
	saveTo(data, dataFile);
}
/*////////////////////*/
/*Головна ф-я програми*/
/*////////////////////*/
void main() {
	setlocale(LC_ALL, "Rus");
	puts("Добрый день! Вас приветствует Библиотека будущего! Библиотека будущего, будущее уже с нами!");
	char data[N] = {0};
	takeNameFile(data);
	int choose_menu = 0, dimension = 0, marker_of_changes = 0;
	Book* massiveStruct = initArrayStart(0);
	do {
		if (marker_of_changes == 0) {
			dimension = check(data);
			massiveStruct = initArray(data, dimension);
			marker_of_changes = 1;
		}
		SLASH;
		puts("	  М Е Н Ю\
			\n1.Редактирование;\
			\n2.Добавление;\
			\n3.Сортировка;\
			\n4.Поиск;\
			\n5.Пересмотр;\
			\n6.Удаление;\
			\n0.Exit;\
			\nВаш выбор: ");
		takeNumberWithoutProblem(&choose_menu);
		SLASH;
		if (choose_menu == 0)
			break;
		else if (choose_menu == 1) {
		redactor(massiveStruct, dimension);
		marker_of_changes == 0;
		}

		else if (choose_menu == 2) {
			addElement(data, massiveStruct, dimension);
			marker_of_changes = 0;
		}
		else if (choose_menu == 3)
			sortMenu(massiveStruct, dimension);
		else if (choose_menu == 4)
			displayMenu(massiveStruct, dimension);
		else if (choose_menu == 5)
			displayArray(massiveStruct, dimension);
		else if (choose_menu == 6) {
			deleteElement(data, massiveStruct, dimension);
			marker_of_changes = 0;
		}
	} while (1);
	initWrite(data, massiveStruct, dimension, 2);
	free(massiveStruct);
	puts("\nНажми чтобы выйти...\n");
}