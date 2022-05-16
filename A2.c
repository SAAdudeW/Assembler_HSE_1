#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <locale.h>

// функция вычисления на Ассемблере
short int asm(short int x, char y, char z) {

	// определение вспомогательной переменной
	short int v_f;

		// вычисление, используя Ассемблер
	__asm {
	
		mov al, z; // размещение z в AL
		cbw; // расширение AL до AX
		dec ax; // z-1 или AX-1
		mov bx, ax; // размещение знаменателя в BX

		mov al, y; // размещение y в AL
		cbw; // расширение AL до AX
		mov cx, 5; // размещение 5 в CX
		imul cx; // y*5 или AX*CX
		mov si, ax; // размещение AX или младшего слова y*5 в SI
		mov di, dx; // размещение DX или старшего слова y*5 в DI

		mov al, z; // размещение z в AL
		cbw; // расширение AL до AX
		add ax, 2; // z+2 или AX+2
		mov cx, x; // размещение x в CX 
		imul cx; // (z+2)*x или AX*CX
		xchg di, dx; // обмен DI и DX, или старших слов y*5 и (z+2)*x  
		xchg si, ax; // обмен SI и AX, или младших слов y*5 и (z+2)*x  

		sub ax, si; // разность AX и SI, или младшее слово y*5-(z+2)*x
		sbb dx, di; // разность с заемом DX и DI, или старшее слово y*5-(z+2)*x

		idiv bx; // частное DX:AX и BX, или y*5-(z+2)*x и z-1
		inc ax; // AX+1, или (y*5-(z+2)*x) / (z-1) + 1
		mov v_f, ax; // размещение AX или (y*5-(z+2)*x) / (z-1) + 1 в v_f

	}

	return v_f;
}

int main() {

	setlocale(LC_ALL, "rus");
	setlocale(LC_NUMERIC, "eng");

	// определение переменных
	int i, j, re = 1;
	short int x, v, v_C, v_as;
	char y, z;

	while (re) {

		printf("\n Введите номер теста. 1 и 2 - прописанные в условии. 3 - свои значения\n");
		scanf("%d", &i);

		// условный оператор, в котором происходит инициализация переменных в соответствии с номером теста 
		switch (i) {

			case 1:
				x = -0x1;
				y = 0x3;
				z = 0x2;
				v = 0x14;
			break;

			case 2:
				x = -0x2F3;
				y = 0x5B;
				z = 0x7F;
				v = 0x309;
			break;

			case 3:
				printf("\n Слово x = ");
				scanf("%x", &j);
				x = (short int) j;
				printf(" Байт y = ");
				scanf("%x", &j);
				y = (char) j;
				printf(" Байт z = ");
				scanf("%x", &j);
				z = (char) j;
			break;

		}

		// вычисление, используя C
		v_C = (5 * y - (z + 2) * x) / (z - 1) + 1;

		// инициализация v_as, приваивание ей результата на Ассемблере
		v_as = asm(x, y, z);

		// вывод результатов
		printf("\n v_as = %d в десятичной v_as = %x в шестнадцатеричной\n", v_as, v_as);
		printf(" v_C = %d в десятичной или v_C = %x в шестнадцатеричной\n", v_C, v_C);
		if ((i == 1) || (i == 2)) {
			printf(" v = %d в десятичной или v = %x в шестнадцатеричной", v, v);
		}

		printf("\n\n Запустить еще раз? Если да, нажмите 1. Если нет, нажмите 0\n re = ");
		scanf("%d", &re);
	}

return 0;
}