#pragma once
#ifndef _HPNC_H_
#define _HPNC_H_
/*���������������������������������������������������ļ���������������������������������������������������*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
/*�����������������������������������������������������ݡ�������������������������������������������������*/

/*ʹ�õ���*/
typedef struct HP_NUM
{
	bool sign;	//0�� 1��
	char *A;	//����
	char *B;	//С��
	int LENA;
	int LENB;
}HP_NUM;
/*Debug��ʹ�õ�����*/
#define HP_MESSAGE_LEN 501
#define HP_FUNCTION_LEN 50
struct
{
	char message[HP_MESSAGE_LEN];
	char function[HP_FUNCTION_LEN];
}HPNC_ERROR;
/*Debugģʽ*/
#define HPNC_DEBUG_ON
#ifdef HPNC_DEBUG_ON
#	define HPNC_DEBUG_PRINT_ERROR_ON
#endif
/*���������������������������������������������������ӿڡ�������������������������������������������������*/

/*��������������������������������������������������ʵ�֡�������������������������������������������������*/
/*====================debug====================*/

/*>>>>>>>>>>�������
Ϊһ���������������*/
void HPNC_Randomdata(HP_NUM * num)
{
	static int check = 0;
	int i;

	if (check == 0)
	{
		srand(time(NULL));
		check = 1;
	}

	for (i = 0; i < (num->LENA); i++)
	{
		num->A[i] = rand() % 10;
	}
	for (i = 0; i < (num->LENB); i++)
	{
		num->B[i] = rand() % 10;
	}
}

/*====================����====================*/
/*>>>>>>>>>>��ʼ����
Ϊһ���±��������ڴ�,��ʱû�г�ʼ������Ԫ��Ϊ0*/
HP_NUM * HPNC_Init(int LENA, int LENB)
{
	HP_NUM *temp;

	temp = (HP_NUM*)malloc(sizeof(HP_NUM));
	temp->LENA = LENA;
	temp->LENB = LENB;
	temp->A = (char*)malloc(LENA * sizeof(char));
	temp->B = (char*)malloc(LENB * sizeof(char));
	return temp;
}

/*>>>>>>>>>>�ͷ��ڴ�
�ͷų�ʼ��ʱΪ�ṹ�ͽṹ�ڵ����������ڴ�*/
void HPNC_Free(HP_NUM *num)
{
	free(num->A);
	free(num->B);
	free(num);
}

void HPNC_FreeArg(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i;
	HP_NUM *temp;
	
	for (i = 0; i < n; i++)
	{
		temp = va_arg(ap, HP_NUM*);
		free(temp->A);
		free(temp->B);
		free(temp);
	}
	va_end(ap);
}

/*>>>>>>>>>>���������Ϣ
�����ַ���������Ϣ������HP_ERR��*/
static void HPNC_ErrorInfo(const char * message, const char * function)
{
	if (message == NULL && function == NULL)
	{
		HPNC_ERROR.message[0] = '\0';
		HPNC_ERROR.function[0] = '\0';
	}

	if (message != NULL)
		strncat(HPNC_ERROR.message, message, HP_MESSAGE_LEN);
	if (function != NULL)
		strncat(HPNC_ERROR.function, function, HP_FUNCTION_LEN);
}

/*>>>>>>>>>>��ӡ������Ϣ
��ȫ�ֱ����д�ӡ���������Ϣ��stderr��*/
void HPNC_ShowErrorInfo(void)
{
#ifdef HPNC_DEBUG_PRINT_ERROR
	int i;
	int ii;

	if (HPNC_ERROR.message[0] != '\0')
		fprintf(stderr, "In function %s: ", HPNC_ERROR.function);
	else
		return;

	i = 0;
	while (HPNC_ERROR.message[i] != '\0')
	{
		if (HPNC_ERROR.message[i] != '|'&&HPNC_ERROR.message[i] != '\0')
		{
			putchar(HPNC_ERROR.message[i]);
			i++;
		}
		else
		{
			putchar('\n');
			if (HPNC_ERROR.message[i] == '|')
			{
				i++;
				if (HPNC_ERROR.message[i] != '\0')
					for (ii = 0; ii < (strlen("In function ") + strlen(HPNC_ERROR.function) + 2); ii++)
						putchar(' ');
			}
		}
	}
#endif
}

/*>>>>>>>>>>��ʼ��
����λ��ʼ��Ϊ0*/
void HPNC_Zero(HP_NUM * num)
{
	int i;
	for (i = 0; i < num->LENA; i++)
		num->A[i] = 0;
	for (i = 0; i < num->LENB; i++)
		num->B[i] = 0;
}

/*>>>>>>>>>>��ӡ��
��ӡһ����������������ȥ�����˶����0*/
void HPNC_Print(HP_NUM * num, int mod)
{
	int count;
	for (count = ((num->LENA) - 1); count >= 0; count--)
		printf("%d", num->A[count]);
	printf(".");
	for (count = 0; count < (num->LENB); count++)
		printf("%d", num->B[count]);

	if (mod%10 == 1)
		printf("\n");
}

/*>>>>>>>>>>���ֵ
�Ƚ��ҳ����������е����ֵ*/
static int HPNC_Max(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i;
	int max, temp;
	max = va_arg(ap, int);
	for (i = 0; i < n - 1; i++)
	{
		temp = va_arg(ap, int);
		if (temp > max)
			max = temp;
	}
	va_end(ap);
	return max;
}

/*>>>>>>>>>>��Сֵ
�Ƚ��ҳ����������е���Сֵ*/
static int HPNC_Min(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i;
	int min, temp;
	min = va_arg(ap, int);
	for (i = 0; i < n - 1; i++)
	{
		temp = va_arg(ap, int);
		if (temp < min)
			min = temp;
	}
	va_end(ap);
	return min;
}

/*====================����====================*/
/*>>>>>>>>>>�߼�����
ֻ���һ�����飬�ܴ������0����������*/
static int HPNC_ManageArray(int *temp, int len)
{
	int mid = 0;
	int i;

	for (i = 0; i < len; i++)
	{
		temp[i] += mid;
		if (temp[i] >= 10)
		{
			mid = (temp[i] - temp[i] % 10) / 10;
			temp[i] -= mid * 10;
		}
		else
			mid = 0;
	}

	return mid;
}

/*====================����====================*/
/*>>>>>>>>>>���ҷ�0��
�ҵ���һ����Ϊ0����
�������������������￪ʼѰ�ң�0��ͷ��ʼѰ�ң���Ϊ0��ĩβ��ʼ
����ֵ�Ƿ�0���±�*/
static int HPNC_FindArray(char *a, int len, char way)
{
	int index = 0;
	if (way == 0)//way=0��0��ʼ����
	{
		for (index = 0; index < len; index++)
			if (a[index] != 0)
				return index;
	}
	else//way=1��ĩβ��ʼ��
	{
		for (index = (len - 1); index >= 0; index--)
			if (a[index] != 0)
				return index;
	}
	return 0;
}
/*====================����====================*/
/*>>>>>>>>>>�ӷ�
temp=a+b
û�л��棬tempλ�ò����Ժ�ab�ص�*/
bool HPNC_Plus(HP_NUM *a, HP_NUM *b, HP_NUM *c)
{
	int i;	/*������*/
	int mark;	/*λ�ñ��*/

	bool mid = 0;	/*�ݴ����ʱ�Ľ�λ*/
	bool error = 0;
	bool frac_precision_lose = 0;

	HP_NUM * temp, *change;
	temp = HPNC_Init(c->LENA, c->LENB);

	HPNC_Zero(temp);	/*��ʼ��*/

	mark = HPNC_Min(3, a->LENB, b->LENB, temp->LENB);

	/*��������λ*/
	if (temp->LENB > HPNC_Min(2, a->LENB, b->LENB))
	{
		if (a->LENB > b->LENB)
		{
			for (i = b->LENB; i < temp->LENB&&i < a->LENB; i++)
				temp->B[i] = a->B[i];
		}
		else if (a->LENB < b->LENB)
		{

			for (i = a->LENB; i < temp->LENB&&i < b->LENB; i++)
				temp->B[i] = b->B[i];
		}
	}
	else
	{
		for (i = (HPNC_Max(2, a->LENB, b->LENB) - 1); i >= temp->LENB; i--)
		{
			if (a->LENB > b->LENB)
			{
				if (i >= b->LENB)
				{
					if (((a->B[i]) + mid) < 10)
					{
						mid = 0;
					}
					else
					{
						mid = 1;
					}
					if (a->B[i] % 10 != 0)
					{
						frac_precision_lose = 1;
					}
				}
				else
				{
					if (a->B[i] + b->B[i] + mid < 10)
					{
						mid = 0;
					}
					else
					{
						mid = 1;
					}
					if ((a->B[i] + b->B[i]) % 10 != 0)
					{
						frac_precision_lose = 1;
					}
				}
			}
			else if (a->LENB < b->LENB)
			{
				if (i >= a->LENB)
				{
					if (b->B[i] + mid < 10)
					{
						mid = 0;
					}
					else
					{
						mid = 1;
					}
					if (b->B[i]% 10 != 0)
					{
						frac_precision_lose = 1;
					}
				}
				else
				{
					if (a->B[i] + b->B[i] + mid < 10)
					{
						mid = 0;
					}
					else
					{
						mid = 1;
					}
					if ((a->B[i] + b->B[i]) % 10 != 0)
					{
						frac_precision_lose = 1;
					}
				}
			}
			else
			{
				if (a->B[i] + b->B[i] + mid < 10)
				{
					mid = 0;
				}
				else
				{
					mid = 1;
				}
				if ((a->B[i] + b->B[i]) % 10 != 0)
				{
					frac_precision_lose = 1;
				}
			}
		}
	}
	for (i = mark - 1; i >= 0; i--)	/*����С������*/
	{
		if (a->B[i] + b->B[i] + mid < 10)
		{
			temp->B[i] = a->B[i] + b->B[i] + mid;
			mid = 0;
		}
		else
		{
			temp->B[i] = a->B[i] + b->B[i] + mid - 10;
			mid = 1;
		}
	}
	
	mark = HPNC_Min(3, a->LENA, b->LENA, temp->LENA);
	for (i = 0; i < mark; i++) /*������������*/
	{
		if ((a->A[i] + b->A[i] + mid) < 10)
		{
			temp->A[i] = a->A[i] + b->A[i] + mid;
			mid = 0;
		}
		else
		{
			temp->A[i] = a->A[i] + b->A[i] + mid - 10;
			mid = 1;
		}
	}
	/*����ʣ�²��ֵ�����*/
	if (a->LENA >= b->LENA&&temp->LENA > b->LENA)	/*����ab��һ�����ӳ�*/
	{
		if (temp->LENA > b->LENA&&temp->LENA <= a->LENA)	/*�������ֵ�temp���Ƚ���ab֮��ʱ*/
		{
			for (i = b->LENA; i < temp->LENA; i++)
			{
				if ((a->A[i] + mid) < 10)
				{
					temp->A[i] = a->A[i] + mid;
					mid = 0;
				}
				else
				{
					temp->A[i] = a->A[i] + mid - 10;
					mid = 1;
				}
			}
		}
		else  /*�������ֵ�temp���ȱ�ab����ʱ*/
		{
			for (i = b->LENA; i < a->LENA; i++)
			{
				if ((a->A[i] + mid) < 10)
				{
					temp->A[i] = a->A[i] + mid;
					mid = 0;
				}
				else
				{
					temp->A[i] = a->A[i] + mid - 10;
					mid = 1;
				}
			}
			temp->A[a->LENA] = mid;
			mid = 0;
		}
	}
	else if (a->LENA < b->LENA&&temp->LENA>a->LENA)
	{
		if (temp->LENA > a->LENA&&temp->LENA <= b->LENA)	/*�������ֵ�temp���Ƚ���ab֮��ʱ*/
		{
			for (i = a->LENA; i < temp->LENA; i++)
			{
				if ((b->A[i] + mid) < 10)
				{
					temp->A[i] = b->A[i] + mid;
					mid = 0;
				}
				else
				{
					temp->A[i] = b->A[i] + mid - 10;
					mid = 1;
				}
			}
		}
		else  /*�������ֵ�temp���ȱ�ab����ʱ*/
		{
			for (i = a->LENA; i < b->LENA; i++)
			{
				if ((b->A[i] + mid) < 10)
				{
					temp->A[i] = b->A[i] + mid;
					mid = 0;
				}
				else
				{
					temp->A[i] = b->A[i] + mid - 10;
					mid = 1;
				}
			}
			temp->A[b->LENA] = mid;
			mid = 0;
		}
	}
	
#ifdef HPNC_DEBUG_ON
	HPNC_ErrorInfo(NULL, NULL);	//���ô�����Ϣ
	HPNC_ErrorInfo(NULL, "Plus");

	/*��������������*/
	if (mid == 1)
	{
		HPNC_ErrorInfo("[Overflow]|", NULL);
		error = 1;
	}
	
	/*С�����ֳ��ȵļ��*/
	
	if (temp->LENB < HPNC_Min(2, a->LENB, b->LENB))
	{
		if (frac_precision_lose == 1)
		{
			HPNC_ErrorInfo("[Precision Lose] (c->LENB < a->LENB && b->LENB) && Having data in that part|", "Plus");
		}
	}
	else
	{
		if (temp->LENB < a->LENB)
		{
			for (i = temp->LENB; i < a->LENB; i++)
			{
				if (a->B[i] != 0)
				{
					HPNC_ErrorInfo("[Precision Lose] (c->LENB < a->LENB) && Having data in that part|", "Plus");
					error = 1;
					break;
				}
			}
		}
		if (temp->LENB < b->LENB)
		{
			for (i = temp->LENB; i < b->LENB; i++)
			{
				if (b->B[i] != 0)
				{
					HPNC_ErrorInfo("[Precision Lose] (c->LENB < b->LENB) && Having data in that part|", "Plus");
					error = 1;
					break;
				}
			}
		}
	}

#ifdef HPNC_DEBUG_PRINT_ERROR_ON
	HPNC_ShowErrorInfo();
#endif
#endif

	free(c->A);
	free(c->B);
	*c = *temp;
	free(temp);
	return error;
}

/*>>>>>>>>>>����
temp=a-b*/
bool HPNC_Minus(HP_NUM * a,HP_NUM *b,HP_NUM *c)//Ĭ����Ϊa>b
{
	HPNC_Zero(c);

	int i = 0;
	bool mid = 0;
	bool error = 0;
	int mark;
	
	mark = HPNC_Min(3, a->LENB, b->LENB, c->LENB);	/*�ҵ�С�����ַ���Ҫ�������������������һλ*/

	if (c->LENB > HPNC_Min(2, a->LENB, b->LENB))
	{
		if (a->LENB > b->LENB)
		{
			if (c->LENB < a->LENB)
			{
				for (i = b->LENB; i < c->LENB&&i < a->LENB; i++)
					c->B[i] = a->B[i];
			}
		}
		else if (a->LENB < b->LENB)
		{
			if (c->LENB < b->LENB)
			{
				for (i = HPNC_Min(2, c->LENB, b->LENB) - 1; i >= a->LENB; i--)
				{
					c->B[i] = 0 - b->B[i] - mid;
					if (c->B[i] < 0)
					{
						c->B[i] += 10;
						mid = 1;
					}
					else
						mid = 0;
				}
			}
		}
	}
	else
	{

	}
	for (i = mark - 1; i >= 0; i--)
	{
		c->B[i] = a->B[i] - b->B[i] - mid;
		if (c->B[i] < 0)
		{
			c->B[i] += 10;
			mid = 1;
		}
		else
			mid = 0;
	}
	

	mark = HPNC_Min(3, a->LENA, b->LENA, c->LENA);
	for (i = 0; i < mark; i++)
	{
		c->A[i] = a->A[i] - b->A[i] - mid;
		if (c->A[i] < 0)
		{
			c->A[i] += 10;
			mid = 1;
		}
		else
			mid = 0;
	}
	if (a->LENA >= b->LENA&&c->LENA > b->LENA)	/*����ab��һ�����ӳ�*/
	{
		if (c->LENA > b->LENA&&c->LENA <= a->LENA)	/*�������ֵ�temp���Ƚ���ab֮��ʱ*/
		{
			for (i = b->LENA; i < c->LENA; i++)
			{
				c->A[i] = a->A[i] - b->A[i] - mid;
				if (c->A[i] < 0)
				{
					c->A[i] += 10;
					mid = 1;
				}
				else
					mid = 0;
			}
		}
		else  /*�������ֵ�temp���ȱ�ab����ʱ*/
		{
			for (i = b->LENA; i < a->LENA; i++)
			{
				if ((a->A[i] + mid) < 10)
				{
					c->A[i] = a->A[i] + mid;
					mid = 0;
				}
				else
				{
					c->A[i] = a->A[i] + mid - 10;
					mid = 1;
				}
			}
			c->A[a->LENA] = mid;
			mid = 0;
		}
	}
	else if (a->LENA < b->LENA&&c->LENA>a->LENA)
	{
		if (c->LENA > a->LENA&&c->LENA <= b->LENA)	/*�������ֵ�temp���Ƚ���ab֮��ʱ*/
		{
			for (i = a->LENA; i < c->LENA; i++)
			{
				if ((b->A[i] + mid) < 10)
				{
					c->A[i] = b->A[i] + mid;
					mid = 0;
				}
				else
				{
					c->A[i] = b->A[i] + mid - 10;
					mid = 1;
				}
			}
		}
		else  /*�������ֵ�temp���ȱ�ab����ʱ*/
		{
			for (i = a->LENA; i < b->LENA; i++)
			{
				if ((b->A[i] + mid) < 10)
				{
					c->A[i] = b->A[i] + mid;
					mid = 0;
				}
				else
				{
					c->A[i] = b->A[i] + mid - 10;
					mid = 1;
				}
			}
			c->A[b->LENA] = mid;
			mid = 0;
		}
	}

	return 0;
}

/*>>>>>>>>>>�˷�
temp=a*b
temp��ַ�����ab�ص�*/
int HPNC_Multi(HP_NUM *a, HP_NUM *b, HP_NUM *c)
{
	bool error = 0;
	int i, ii;	/*����*/
	int mark_a;	/*��־aС�����ֵ�һ����0��λ��*/
	int mark_b;	/*��־bС�����ֵ�һ����0��λ��*/
	int *temp;	/*�ݴ�˷��Ľ��*/
	int temp_len;	/*�ݴ�ĳ���*/
	int mark_A0;	/*��־temp����������0��λ��*/
	int mark_B0;	/*��־temp��С������0��λ��*/

	/*ȷ��������ݴ�����ĳ���*/
	if ((a->LENA + b->LENA + a->LENB + b->LENB) > ((c->LENA + c->LENB) * 2))
	{
		mark_A0 = a->LENB + b->LENB;
		mark_B0 = a->LENB + b->LENB - 1;
		temp_len = a->LENA + b->LENA + a->LENB + b->LENB + 2;
	}
	else
	{
		mark_A0 = c->LENB * 2;
		mark_B0 = c->LENB * 2 - 1;
		temp_len = (c->LENA + c->LENB) * 2;
	}

	temp = (int*)malloc(sizeof(int)*temp_len);	/*���䴢��ռ�*/
	if (temp == NULL)
	{
#ifdef HPNC_DEBUG_ON
		HPNC_ErrorInfo(NULL, NULL);	//���ô�����Ϣ
		HPNC_ErrorInfo(NULL, "Mult");
		HPNC_ErrorInfo("[Memory full]|", NULL);
#ifdef HPNC_DEBUG_PRINT_ERROR_ON
		HPNC_ShowErrorInfo();
#endif
#endif
		error = 1;
		return error;
	}
	for (i = 0; i < temp_len; i++)	/*��ʼ��Ϊ0*/
		temp[i] = 0;

	mark_a = HPNC_FindArray(a->B, a->LENB, 1);	/*a�����һ����0�������*/
	mark_b = HPNC_FindArray(b->B, b->LENB, 1);	/*b�����һ����0�������*/

	for (i = mark_b; i >= 0; i--)	/* aС�� x bС�� */
	{
		for (ii = mark_a; ii >= 0; ii--)
		{
			temp[mark_B0 - i - ii - 1] += (b->B[i] * a->B[ii]);
		}
	}
	for (i = 0; i < b->LENA; i++)	/* a���� x b���� */
	{
		for (ii = 0; ii < a->LENA; ii++)
		{
			temp[mark_A0 + i + ii] += (b->A[i] * a->A[ii]);
		}
	}
	for (i = 0; i < b->LENA; i++)	/* aС�� x b���� */
	{
		for (ii = 0; ii <= mark_a; ii++)
		{
			temp[mark_B0 + i - ii] += (b->A[i] * a->B[ii]);
		}
	}
	for (i = 0; i <= mark_b; i++)	/* a���� x bС�� */
	{
		for (ii = 0; ii < a->LENA; ii++)
		{
			temp[mark_B0 + ii - i] += (a->A[ii] * b->B[i]);
		}
	}

	HPNC_ManageArray(temp, temp_len);
	HPNC_Zero(c);
	for (i = 0; i < c->LENB; i++)
		c->B[i] = temp[mark_B0 - i];
	for (i = 0; i < c->LENA; i++)
		c->A[i] = temp[mark_A0 + i];

	/*��ʼ���*/
#ifdef HPNC_DEBUG_ON
	HPNC_ErrorInfo(NULL, NULL);	//���ô�����Ϣ
	HPNC_ErrorInfo(NULL, "Mult");

	/*С�����ֳ��ȵļ��*/
	if ((mark_a + mark_b + 2) > c->LENB)
	{
		for (i = c->LENB - 1; i >= 0; i--)
		{
			if (temp[i] != 0)
			{
				HPNC_ErrorInfo("[Precision Lose]|", NULL);
				error = 1;
				break;
			}
		}
	}
	/*�������ֳ��ȵļ��*/
	if ((a->LENA + b->LENA) > c->LENA)
	{
		for (i = c->LENA + mark_A0; i < temp_len; i++)
		{
			if (temp[i] != 0)
			{
				HPNC_ErrorInfo("[Overflow]|", NULL);
				error = 1;
				break;
			}
		}
	}
#ifdef HPNC_DEBUG_PRINT_ERROR_ON
	HPNC_ShowErrorInfo();
#endif

#endif


	free(temp);
	return error;
}








#endif