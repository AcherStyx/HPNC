#pragma once
#ifndef _HPNC_H_
#define _HPNC_H_
/*■■■■■■■■■■■■■■■■■■■■■■■■■文件■■■■■■■■■■■■■■■■■■■■■■■■■*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
/*■■■■■■■■■■■■■■■■■■■■■■■■■数据■■■■■■■■■■■■■■■■■■■■■■■■■*/
/*=====使用的数=====*/
typedef struct HP_NUM
{
	bool sign;	//0正 1负
	char *A;	//整数
	char *B;	//小数
	int LENA;
	int LENB;
}HP_NUM;
/*Debug中使用的数据*/
#define HP_MESSAGE_LEN 501
#define HP_FUNCTION_LEN 50
struct
{
	char message[HP_MESSAGE_LEN];
	char function[HP_FUNCTION_LEN];
}HPNC_ERROR;
/*=====Debug模式=====*/
#define HPNC_DEBUG_ON
#ifdef HPNC_DEBUG_ON
#	define HPNC_DEBUG_PRINT_ERROR_ON
#	define HPNC_DEBUG_PRINT_NUM_ON
#endif
/*■■■■■■■■■■■■■■■■■■■■■■■■■接口■■■■■■■■■■■■■■■■■■■■■■■■■*/

/*■■■■■■■■■■■■■■■■■■■■■■■■■实现■■■■■■■■■■■■■■■■■■■■■■■■■*/
/*====================debug====================*/

/*>>>>>>>>>>随机数据
为一个数分配随机数据*/
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

/*====================工具====================*/
/*>>>>>>>>>>初始化数
为一个新变量分配内存,暂时没有初始化所有元素为0*/
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

/*>>>>>>>>>>初始化数
可变参量*/
void * HPNC_InitArg(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	int i;

	HP_NUM **temp;
	int LENA;
	int LENB;

	for (i = 0; i < n; i++)
	{
		temp = va_arg(ap, HP_NUM**);
		LENA = va_arg(ap, int);
		LENB = va_arg(ap, int);
		*temp = HPNC_Init(LENA, LENB);
	}
}

/*>>>>>>>>>>释放内存
释放初始化时为结构和结构内的数组分配的内存*/
void HPNC_Free(HP_NUM *num)
{
	free(num->A);
	free(num->B);
	free(num);
}

/*>>>>>>>>>>释放内存
可变参量*/
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

/*>>>>>>>>>>保存错误信息
传入字符串，将信息保存在HP_ERR中*/
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

/*>>>>>>>>>>打印错误信息
从全局变量中打印输出错误信息到stderr流*/
void HPNC_ShowErrorInfo(void)
{
#ifdef HPNC_DEBUG_PRINT_ERROR_ON
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

/*>>>>>>>>>>初始化
所有位初始化为0*/
void HPNC_Zero(HP_NUM * num)
{
	int i;
	for (i = 0; i < num->LENA; i++)
		num->A[i] = 0;
	for (i = 0; i < num->LENB; i++)
		num->B[i] = 0;
}

/*>>>>>>>>>>打印数
打印一个完整的数，但是去掉两端多余的0*/
void HPNC_Print(HP_NUM * num, int mod)
{
#ifdef HPNC_DEBUG_PRINT_NUM_ON
	int count;
	for (count = ((num->LENA) - 1); count >= 0; count--)
		printf("%d", num->A[count]);
	printf(".");
	for (count = 0; count < (num->LENB); count++)
		printf("%d", num->B[count]);

	if (mod%10 == 1)
		printf("\n");
#endif
}

/*>>>>>>>>>>最大值
比较找出所给参数中的最大值*/
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

/*>>>>>>>>>>最小值
比较找出所给参数中的最小值*/
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

/*====================整理====================*/
/*>>>>>>>>>>高级整理
只针对一组数组，能处理大于0的任意整理*/
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

/*====================查找====================*/
/*>>>>>>>>>>查找非0项
找到第一个不为0的数
第三个参数决定从哪里开始寻找，0从头开始寻找，不为0从末尾开始
返回值是非0项下标*/
static int HPNC_FindArray(char *a, int len, char way)
{
	int index = 0;
	if (way == 0)//way=0从0开始查找
	{
		for (index = 0; index < len; index++)
			if (a[index] != 0)
				return index;
	}
	else//way=1从末尾开始找
	{
		for (index = (len - 1); index >= 0; index--)
			if (a[index] != 0)
				return index;
	}
	return 0;
}
/*====================运算====================*/
/*>>>>>>>>>>加法
temp=a+b
没有缓存，temp位置不可以和ab重叠*/
bool HPNC_Plus(HP_NUM *a, HP_NUM *b, HP_NUM *c)
{
	int i;	/*计数器*/
	int mark;	/*位置标记*/

	bool mid = 0;	/*暂存相加时的进位*/
	bool error = 0;
	bool frac_precision_lose = 0;

	HP_NUM * temp, *change;
	temp = HPNC_Init(c->LENA, c->LENB);

	HPNC_Zero(temp);	/*初始化*/

	mark = HPNC_Min(3, a->LENB, b->LENB, temp->LENB);

	/*处理多出的位*/
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
	for (i = mark - 1; i >= 0; i--)	/*计算小数部分*/
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
	for (i = 0; i < mark; i++) /*计算整数部分*/
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
	/*处理剩下部分的运算*/
	if (a->LENA >= b->LENA&&temp->LENA > b->LENA)	/*区分ab哪一个更加长*/
	{
		if (temp->LENA > b->LENA&&temp->LENA <= a->LENA)	/*整数部分的temp长度介于ab之间时*/
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
		else  /*整数部分的temp长度比ab都大时*/
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
		if (temp->LENA > a->LENA&&temp->LENA <= b->LENA)	/*整数部分的temp长度介于ab之间时*/
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
		else  /*整数部分的temp长度比ab都大时*/
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
	HPNC_ErrorInfo(NULL, NULL);	//重置错误消息
	HPNC_ErrorInfo(NULL, "Plus");
	/*整数部分溢出检查*/
	if (mid == 1)
	{
		HPNC_ErrorInfo("[Overflow]|", NULL);
		error = 1;
	}
	/*小数部分长度的检查*/
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

/*>>>>>>>>>>减法
temp=a-b*/
bool HPNC_Minus(HP_NUM * a,HP_NUM *b,HP_NUM *c)//默认认为a>b
{
#ifdef HPNC_DEBUG_ON
	HPNC_ErrorInfo(NULL, NULL);	//重置错误消息
	HPNC_ErrorInfo(NULL, "Plus");
#endif
	HPNC_Zero(c);

	int i = 0;
	bool mid = 0;
	bool error = 0;
	int mark;
	
	mark = HPNC_Min(3, a->LENB, b->LENB, c->LENB);	/*找到小数部分符合要求，能正常完成运算的最后一位*/

	if (c->LENB < HPNC_Min(2, a->LENB, b->LENB))
	{
		if (a->LENB > b->LENB)
		{
			for (i = a->LENB - 1; i >= b->LENB; i--)
			{
				if (a->B[i] - 0 - mid < 0)
				{
					mid = 1;
				}
				else
					mid = 0;
			}
			for (i = b->LENB - 1; i >= c->LENB; i--)
			{
				if (a->B[i] - b->B[i] - mid < 0)
				{
					mid = 1;
				}
				else
					mid = 0;
			}
		}
		else
		{
			for (i = b->LENB - 1; i >= a->LENB; i--)
			{
				if (0 - b->LENB - mid < 0)
				{
					mid = 1;
				}
				else
					mid = 0;
			}
			for (i = a->LENB - 1; i >= c->LENB; i--)
			{
				if (a->B[i] - b->B[i] - mid < 0)
				{
					mid = 1;
				}
				else
					mid = 0;
			}
		}
	}
	else if (c->LENB < HPNC_Max(2, a->LENB, b->LENB))
	{
		if (a->LENB > b->LENB)
		{
			for (i = b->LENB; i < c->LENB&&i < a->LENB; i++)
				c->B[i] = a->B[i];
		}
		else
		{
			for (i = b->LENB - 1; i >= c->LENB; i--)
			{
				if (b->B[i] != 0)
					mid = 1;
			}
			for (i = c->LENB - 1; i >= HPNC_Min(2, a->LENB, b->LENB); i--)
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
	else
	{
		if (a->LENB > b->LENB)
		{
			for (i = b->LENB; i < a->LENB&&i < a->LENB; i++)
				c->B[i] = a->B[i];
		}
		else
		{
			for (i = b->LENB - 1; i >= HPNC_Min(2, a->LENB, b->LENB); i--)
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
	
#ifdef HPNC_DEBUG_ON
	if (c->LENB < HPNC_Min(2, a->LENB, b->LENB))
	{

		if (mid == 1)
		{
			error = 1;
			HPNC_ErrorInfo("[Precision Lose] c->LENB < Min(a->LENB,b->LENB)|", "Minus");
		}

	}
	else if (c->LENB < HPNC_Max(2, a->LENB, b->LENB))
	{
		if (a->LENB > b->LENB)
		{
			for (i = b->LENB; i < a->LENB; i++)
			{
				if (a->B[i] != 0)
				{
					error = 1;
					HPNC_ErrorInfo("[Precision Lose] Min(a->LENB,b->LENB) < c->LENB < Max(a->LENB,b->LENB)|", "Minus");
					break;
				}
			}
		}
		else
		{
			if (mid == 1)
			{
				error = 1;
				HPNC_ErrorInfo("[Precision Lose] Min(a->LENB,b->LENB) <= c->LENB < Max(a->LENB,b->LENB)|", "Minus");
			}
		}
	}
#endif
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
	if (a->LENA >= b->LENA&&c->LENA > b->LENA)	/*区分ab哪一个更加长*/
	{
		if (c->LENA > b->LENA&&c->LENA <= a->LENA)	/*整数部分的temp长度介于ab之间时*/
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
		else  /*整数部分的temp长度比ab都大时*/
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
		if (c->LENA > a->LENA&&c->LENA <= b->LENA)	/*整数部分的temp长度介于ab之间时*/
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
		else  /*整数部分的temp长度比ab都大时*/
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

#ifdef HPNC_DEBUG_PRINT_ERROR_ON
	HPNC_ShowErrorInfo();
#endif

	return 0;
}

/*>>>>>>>>>>乘法
temp=a*b
temp地址允许和ab重叠*/
int HPNC_Multi(HP_NUM *a, HP_NUM *b, HP_NUM *c)
{
	bool error = 0;
	int i, ii;	/*计数*/
	int mark_a;	/*标志a小数部分第一个非0数位置*/
	int mark_b;	/*标志b小数部分第一个非0数位置*/
	int *temp;	/*暂存乘法的结果*/
	int temp_len;	/*暂存的长度*/
	int mark_A0;	/*标志temp中整数部分0的位置*/
	int mark_B0;	/*标志temp中小数部分0的位置*/

	/*确定分配的暂存数组的长度*/
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

	temp = (int*)malloc(sizeof(int)*temp_len);	/*分配储存空间*/
	if (temp == NULL)
	{
#ifdef HPNC_DEBUG_ON
		HPNC_ErrorInfo(NULL, NULL);	//重置错误消息
		HPNC_ErrorInfo(NULL, "Mult");
		HPNC_ErrorInfo("[Memory full]|", NULL);
#ifdef HPNC_DEBUG_PRINT_ERROR_ON
		HPNC_ShowErrorInfo();
#endif
#endif
		error = 1;
		return error;
	}
	for (i = 0; i < temp_len; i++)	/*初始化为0*/
		temp[i] = 0;

	mark_a = HPNC_FindArray(a->B, a->LENB, 1);	/*a中最后一个非0项的坐标*/
	mark_b = HPNC_FindArray(b->B, b->LENB, 1);	/*b中最后一个非0项的坐标*/

	for (i = mark_b; i >= 0; i--)	/* a小数 x b小数 */
	{
		for (ii = mark_a; ii >= 0; ii--)
		{
			temp[mark_B0 - i - ii - 1] += (b->B[i] * a->B[ii]);
		}
	}
	for (i = 0; i < b->LENA; i++)	/* a整数 x b整数 */
	{
		for (ii = 0; ii < a->LENA; ii++)
		{
			temp[mark_A0 + i + ii] += (b->A[i] * a->A[ii]);
		}
	}
	for (i = 0; i < b->LENA; i++)	/* a小数 x b整数 */
	{
		for (ii = 0; ii <= mark_a; ii++)
		{
			temp[mark_B0 + i - ii] += (b->A[i] * a->B[ii]);
		}
	}
	for (i = 0; i <= mark_b; i++)	/* a整数 x b小数 */
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

	/*开始查错*/
#ifdef HPNC_DEBUG_ON
	HPNC_ErrorInfo(NULL, NULL);	//重置错误消息
	HPNC_ErrorInfo(NULL, "Mult");

	/*小数部分长度的检查*/
	if ((mark_a + mark_b + 2) > c->LENB)
	{
		for (i = c->LENB - 1; i >= 0; i--)
		{
			if (temp[mark_B0 - i] != 0)
			{
				HPNC_ErrorInfo("[Precision Lose]|", NULL);
				error = 1;
				break;
			}
		}
	}
	/*整数部分长度的检查*/
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