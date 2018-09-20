#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>

//Перевод целой части числа из b1-ной системы счисления в 10-ую и затем в b2-ую
void  befdot_b1_to_b2(char x[15], int b1, int b2)
{
	long long d = 0; 
        int st = 1; 

	char final_num[100]; //Число в b2-ой сс
	for (int j = strlen(x) - 1; j >= 0; j--)
	{
		if ((x[j] - 48 >= 0) && (x[j] - 48 <= 9))
		{
			d = d + (x[j] - 48)*st;
			st = st * b1;
		}
		else if ((x[j] - 55 >= 10) && (x[j] - 55 <= 15))
		{
			d = d + (x[j] - 55)*st;
			st = st * b1;
		}
	}

	int u = 0; 
	while (d > 0)
	{
		if (((d % b2) >= 10) && ((d % b2) <= 15))
		{
			final_num[u] = ((d % b2) + 55);
		}
		else if (((d % b2) >= 0) && ((d % b2) <= 9))
		{
			final_num[u] = ((d % b2) + 48);
		}
		u = u + 1;
		d = d / b2;
	}

	for (int j = u - 1; j >= 0; j--)
		printf("%c", final_num[j]); //Выводим целую часть
}


//Перевод дробной части числа b1-ой сс в 10-ую и затем в b2-ую
void afterdot_b1_to_b2(char x[15], int b1, int b2)
{
	double c = 0.0;//Представление дробной части в 10 сс
	double degree_negative = (double)b1;//Степень основания первоначальной системы
	int m = 0;//Длина строки дробной части
	int num_fract;//Цифра дробной части числа в конечной сс
	for (int z = 0; z <= strlen(x) - 1; z++)
	{
		if ((x[z] - 48 >= 0) && (x[z] - 48 <= 9))
		{
			c = c + (x[z] - 48) / degree_negative;
			degree_negative = degree_negative * (double)b1;
		}
		else if ((x[z] - 55 >= 10) && (x[z] - 55 <= 15))
		{
			c = c + (x[z] - 55) / degree_negative;
			degree_negative = degree_negative * (double)b1;
		}
	}

	while (((c - trunc(c)) != 0.0) && (m < 12)) //При необходимости нам нужно избавляться от целой части, и пока дробная не = 0 выполнять перевод
	{
		if ((trunc(c*b2) >= 0) && (trunc(c*b2) <= 9))
		{
			num_fract = trunc(c*b2);
			printf("%c", num_fract + 48);
			c = (c*b2 - trunc(c*b2)); //Отделяем целую часть для использования
			m = m + 1; //Учитываем кол-во знаков после запятой в ответе
		}
		else if ((trunc(c*b2) >= 10) && (trunc(c*b2) <= 15))
		{
			num_fract = trunc(c*b2);
			printf("%c", num_fract + 55);
			c = (c*b2 - trunc(c*b2));
			m = m + 1;
		}

	}

}

int main()
{
	int b1; //Начальная система счисления
	int b2; //Конечная система счисления
	int dot = 0; //Кол-во точек в записи числа, не больше 1
	int length = 0; //Длина строки
	int k = 0; //Кол-во цифр в целой части числа
	char x[15]; //Вводимое число с клавиатуры
	char befdot[100] = { '\0' }; //Строка целой части (Массив должен оканчиваться нуль-символом, иначе это ведет к неправильному чтению строки)
	char afterdot[100] = { '\0' }; //Строка дробной части
	scanf("%d %d\n", &b1, &b2);
	scanf("%s", x);
	//Переводим строку к верхнему регистру
	for (int i = 0; i < strlen(x); i++)
	{
		if (((x[i] - 7) >= 90) && ((x[i] - 7) <= 95))
		{
			x[i] = x[i] - 32;
		}
	}

	if (((b1 < 2) || (b1 > 16)) || ((b2 < 2) || (b2 > 16)))
	{
		printf("Bad input");
	}
	else
	{
		for (int i = 0; i <= strlen(x) - 1; i ++)
		{
			if (x[i] == '.') //Поиск точки
			{
				dot++;
			}
			else if (((x[i] - 48 >= 0) && (x[i] - 48 < b1)) || ((x[i] - 55 >= 0) && (x[i] - 55 < b1)))
				length = length + 1;
		}
		//Проверяем на случай, когда число целое без дробной части, учтём, что число не может начинаться с '.' и заканчиваться '.'
		if ((length == strlen(x)) && (dot == 0) && (x[strlen(x) - 1] != '.') && (x[0] != '.'))
		{
			//Провека на введеный '0'
			if ((x[0] == ('0')) && (strlen(x) == 1))
			{
				printf("0");
			}
			else
				befdot_b1_to_b2(x, b1, b2);
		}
		else if ((length == strlen(x) - 1) && (dot == 1) && (x[strlen(x) - 1] != '.') && (x[0] != '.'))
		{
			//Отделяем целую часть числа
			while (x[k] != '.')
				k ++; //Считаем кол-во цифр в целой части
			for (int i = 0; i < k; i ++)
				befdot[i] = x[i]; //Заполняем массив для целой части

			for (int i = k + 1; i < strlen(x); i ++)
				afterdot[i - k - 1] = x[i]; //Заполняем массив для дробной части

			if ((befdot[0] == ('0')) && (strlen(befdot) == 1))
				printf("0");
			else
				befdot_b1_to_b2(befdot, b1, b2);
			printf("."); //Так как точку мы ни в один массив не записывали, выведем её отдельно
			if ((afterdot[0] == ('0')) && (strlen(afterdot) == 1))
				printf("0");
			else
				afterdot_b1_to_b2(afterdot, b1, b2);
		}
		else
			printf("Bad input");
	}
	return 0;
}
