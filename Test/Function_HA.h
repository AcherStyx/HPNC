#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
/*====================定义常量====================*/
#define PRECISION 1 //用在F_HA_INPUT中，决定分数和所给小数允许多大的误差，数字n表示误差小于E-(n+1)
/*====================工具函数====================*/
//打印Bar
void F_HA_BAR(char what, int num,int enter)
{
	int count;
	for (count = 0; count < num; count++)
		putchar(what);
	if (enter != 0)
		putchar('\n');
}

//找到第一个不为0的数，第三个参数决定从哪里开始寻找，0从头开始寻找，不为0从末尾开始，返回值是对应的数组下标
int F_HA_FIND(char *a, int lena, char where)
{
	int count = 0;
	if (where == 0)//where=0从0开始查找
	{
		for (count = 0; count < lena; count++)
			if (a[count] != 0)
				return count;
	}
	else//where=1从末尾开始找
	{
		for (count = (lena - 1); count >= 0; count--)
			if (a[count] != 0)
				return count;
	}
	return 0;
}

//将包含整数与小数两个部分的两个数组打印成一个完整的小数
void F_HA_PRINT(char *a1, char *a2, int lena1, int lena2,int printenter)
{
	int count;
	for (count = (lena1 - 1); count >= 0; count--)
		printf("%d", a1[count]);
	printf(".");
	for (count = 0; count < lena2; count++)
		printf("%d", a2[count]);

	if (printenter == 1)
		printf("\n");
}

//打印单个数组，第三个参数可以选择从末尾还是从开头开始打印，0从开头，不为0从末尾
void F_HA_PRINTS(char *a, int len, int start, int enter)
{
	int count;
	if (start == 0)
	{
		for (count = 0; count < len; count++)
			printf("%d", a[count]);
	}
	else
		for (count = (len - 1); count >= 0; count--)
			printf("%d", a[count]);

	if (enter != 0)
		printf("\n");
}

//打印一个完整的数，但是去掉两端多余的0
void F_HA_PRINTC(char *a1, char *a2, int lena1, int lena2, int enter)
{
	int end1;
	int end2;
	end1 = F_HA_FIND(a1, lena1, 1) + 1;
	end2 = F_HA_FIND(a2, lena2, 1) + 1;
	F_HA_PRINT(a1, a2, end1, end2, enter);
}

//低级整理，针对完整的两数组组成的小数，只能处理小于20、大于0的，用于加法
int F_HA_MA(char *a1, char *a2, int lena1, int lena2)
{
	short mid=0;
	int count;
	for (count = (lena2 - 1); count >= 0; count--)
	{
		a2[count] += mid;
		if (a2[count] >= 10)
		{
			a2[count] -= 10;
			mid = 1;
		}
		else if (a2[count] < 0)
		{
			a2[count] += 10;
			mid = -1;
		}
		else
		{
			mid = 0;
		}
	}
	for (count = 0; count < lena1; count++)
	{
		a1[count] += mid;
		if (a1[count] >= 10)
		{
			a1[count] -= 10;
			mid = 1;
		}
		else if (a1[count] < 0)
		{
			a1[count] += 10;
			mid = -1;
		}
		else
		{
			mid = 0;
		}
	}
	return mid;
}

//高级整理，针对完整的两数组组成的小数，能处理大于0的任意整理
int F_HA_MAP(char *a1, char *a2, int lena1, int lena2)//Manage plus version,could handle more work
{
	int count;
	int mid=0;//initializing

	for (count = (lena2 - 1); count >= 0; count--)
	{
		a2[count] += mid;
		if (a2[count] >= 10)
		{
			mid = (a2[count] - a2[count] % 10) / 10;
			a2[count] -= mid * 10;
		}
		else
			mid = 0;
	}
	for (count = 0; count < lena1; count++)
	{
		a1[count] += mid;
		if (a1[count] >= 10)
		{
			mid = (a1[count] - a1[count] % 10) / 10;
			a1[count] -= mid * 10;
		}
		else
			mid = 0;
	}

	return mid;
}

//高级整理，只针对一组数组，能处理大于0的任意整理
int F_HA_MASINGLE(int *temp,int len)
{
	int mid=0;/*initializing*/
	int count;

	for (count = 0; count < len; count++)
	{
		temp[count] += mid;
		if (temp[count] >= 10)
		{
			mid = (temp[count] - temp[count] % 10) / 10;
			temp[count] -= mid * 10;
		}
		else
			mid = 0;
	}

	return mid;
}

//累加，从最小一位开始进行的累加1，效率比较低
int F_HA_ACC(char *a1, char *a2, int lena1, int lena2)
{
	a2[(lena2 - 1)] += 1;
	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

//累加，从自定义位数开始累加1，最后一个参数n决定从哪里开始，自最后一位数起第n位开始累加
int F_HA_ACCP(char *a1, char *a2, int lena1, int lena2, int n)
{
	if (n <= lena2 && n != 0)
		a2[lena2 - n] += 1;
	else if (n > lena2 && n <= (lena1 + lena2))
		a1[n - lena2 - 1] += 1;

	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

//累减，从自定义位数开始累减1，最后一个参数n决定从哪里开始，自最后一位数起第n位开始累减
int F_HA_ACCM(char *a1, char *a2, int lena1, int lena2, int n)
{
	if (n <= lena2 && n != 0)
		a2[lena2 - n] -= 1;
	else if (n > lena2 && n <= (lena1 + lena2))
		a1[n - lena2 - 1] -= 1;

	F_HA_MA(a1, a2, lena1, lena2);
	
	return 0;
}

//比大小a>b 0 ; a<b 1 ; a=b 2
int F_HA_COMP(char *a1, char *a2, char *b1, char *b2,int lena1,int lena2,int lenb1,int lenb2)
{
	int amaxplace;
	int bmaxplace;
	int count;

	amaxplace = F_HA_FIND(a1, lena1, 1);
	bmaxplace = F_HA_FIND(b1, lenb1, 1);

	if (amaxplace > bmaxplace)
			return 0;
	if (amaxplace < bmaxplace)
			return 1;
	if (amaxplace == bmaxplace)
	{
		if (a1[amaxplace] > b1[bmaxplace])
			return 0;
		if (a1[amaxplace] < b1[bmaxplace])
			return 1;
		if (a1[amaxplace] == b1[bmaxplace])
		{
			for (count = amaxplace; count >= 0; count--)
			{
				if (a1[count] > b1[count])
					return 0;
				if (a1[count] < b1[count])
					return 1;
			}
		}
	}
	

	int len;
	int mark;

	/*
	if (lena2 < lenb2)
	{
		len = lena2;
		placeb = F_HA_FIND(b2, lenb2, 1);
		placea = (lena2-1);
		mark = 0;
	}
	if (lena2 > lenb2)
	{
		len = lenb2;
		placea = F_HA_FIND(a2, lena2, 1);
		placeb = (lenb2-1);
		mark = 1;
	}
	if (lena2 = lenb2)
		len = lena2;
	*/

	amaxplace = F_HA_FIND(a2, lena2, 1);
	bmaxplace = F_HA_FIND(b2, lenb2, 1);

	/*
	if (amaxplace < bmaxplace)
		return 0;
	if (amaxplace > bmaxplace)
		return 1;
	if (amaxplace == bmaxplace)
	{
		for (count = amaxplace; count <= len; count++)
		{
			if (a2[count] > b2[count])
				return 0;
			if (a2[count] < b2[count])
				return 1;
		}
	}
	*/

	if (amaxplace > bmaxplace)
	{
		len = bmaxplace;
		mark = 0;
	}
	if (amaxplace < bmaxplace)
	{
		len = amaxplace;
		mark = 1;
	}
	if (amaxplace == bmaxplace)
	{
		len = amaxplace;
		mark = 2;
	}
	
	for (count = 0; count <= len; count++)
	{
		if (a2[count] > b2[count])
			return 0;
		else if (a2[count] < b2[count])
			return 1;
	}

	return mark;
}

//打印[test%d]
void F_HA_TEST(short num)
{
	printf("[TEST%d]:\n", num);
}

//初始化，为单个数组填充0
void F_HA_ZEROS(char *a, int len)
{
	int count;
	for (count = 0; count < len; count++)
		a[count] = 0;
}

//初始化，为两个数组组成的一个完整数填充0
void F_HA_ZEROD(char *a1, char*a2, int lena1, int lena2)
{
	int count;
	for (count = 0; count < lena1; count++)
		a1[count] = 0;
	for (count = 0; count < lena2; count++)
		a2[count] = 0;
}

//将一个完整数的值移动到另一个上
void F_HA_MOVE(char *a1, char *a2, char *b1, char *b2, int lena1, int lena2, int lenb1, int lenb2)
{
	int count;
	int len1;
	int len2;

	F_HA_ZEROD(b1, b2, lenb1, lenb2);
	//the smaller one
	if (lena1 > lenb1)
		len1 = lenb1;
	else
		len1 = lena1;
	if (lena2 > lenb2)
		len2 = lenb2;
	else
		len2 = lena2;

	for (count = 0; count < len1; count++)
		b1[count] = a1[count];
	for (count = 0; count < len2; count++)
		b2[count] = a2[count];


}

//将一个浮点数转存到两个数组中
void F_HA_TRANS(double flo, char *a1, char *a2, int lena1, int lena2)
{
	int floget1;
	int floget2;
	int floget;
	int floget3;
	double volum;

	F_HA_ZEROD(a1, a2, lena1, lena2);

	if (lena1 >= 3)
	{
		volum = 99.9999999999;
		floget1 = flo / volum;
		floget2 = (flo / volum) / 10;
		floget = floget1 - floget2 * 10;
		a1[2] = floget;
	}

	volum = 9.9999999999;
	floget1 = flo / volum;
	floget2 = (flo / volum) / 10;
	floget = floget1 - floget2 * 10;
	a1[1] = floget;

	volum = 0.9999999999;
	floget1 = flo / volum;
	floget2 = (flo / volum) / 10;
	floget = floget1 - floget2 * 10;
	a1[0] = floget;

	volum = 0.09999999999;
	floget1 = flo / volum;
	floget2 = (flo / volum) / 10;
	floget = floget1 - floget2 * 10;
	a2[0] = floget;

	printf("%d", floget2);

	volum = 0.009999999999;
	floget1 = flo / volum;
	floget2 = (flo / volum) / 10;
	floget = floget1 - floget2 * 10;
	a2[1] = floget;

	if (lena2 >= 3)
	{
		volum = 0.0009999999999;
		floget1 = flo / volum;
		floget2 = (flo / volum) / 10;
		floget = floget1 - floget2 * 10;
		a2[2] = floget;
	}

	printf("【TRANS内部测试】");
	printf("%f|", flo);
	F_HA_PRINT(a1, a2, lena1, lena2, 1);


}

//获得用户输入的小数，转存到两个数组中形成一个完整数
int F_HA_INPUT(char *a1, char *a2, int lena1, int lena2)
{
	//clear
	F_HA_ZEROD(a1, a2, lena1, lena2);

	int error=0;
	int count=0;
	int countp;
	int mark;
	char *temp;
	int alllen = lena1 + lena2 + 2;
	temp = (char*)malloc(sizeof(char)*alllen);
	while ((temp[count] = getchar()) != '.')
	{
		temp[count] -= '0';
		if (temp[count] >= 0 && temp[count] < 10)
			count++;
		else
			error += 10;
		if (count >= lena1)
		{
			printf("【!】整数部分超过给定位数\n");
			error += 1;
			break;
		}
	}
	mark = count;
	temp[count] = '.';
	count++;
	while ((temp[count] = getchar()) != '\n')
	{
		temp[count] -= '0';
		if (temp[count] >= 0 && temp[count] < 10)
			count++;
		else
			error += 10;
		if (count >= (alllen-1))
		{
			printf("【!】小数部分超过给定位数\n");
			error += 1;
			break;
		}
	}
	temp[count] = '\n';
	for (countp = mark; countp > 0; countp--)
	{
		a1[mark - countp] = temp[countp - 1];
	}
	for (countp = mark; countp < (count-1); countp++)
	{
		a2[countp - mark] = temp[countp + 1];
	}


	printf("实际录入的值为：");
	F_HA_PRINTC(a1, a2, lena1, lena2, 1);

	free(temp);
	return error;
}

/*====================运算函数====================*/

//加法
int F_HA_P(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)
{
	int error = 0;
	int count;

	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	//找到右边符合要求，能正常完成运算的最后一位
	int find = 0;
	while ((find < lena2 || find < lenb2) && find < lenc2)
		find += 1;

	char mid = 0;//初始化
	for (count = find; count >= 0; count--)
	{
		if (a2[count] + b2[count] + mid < 10)
		{
			c2[count] = a2[count] + b2[count] + mid;
			mid = 0;
		}
		else
		{
			c2[count] = a2[count] + b2[count] + mid - 10;
			mid = 1;
		}
	}

	for (count = 0; count < lenc1 && (count < lena1 && count < lenb1); count++)
	{
		if ((a1[count] + b1[count] + mid) < 10)
		{
			c1[count] = a1[count] + b1[count] + mid;
			mid = 0;
		}
		else
		{
			c1[count] = a1[count] + b1[count] + mid - 10;
			mid = 1;
		}
	}
	//错检
	if (mid = 1)
		error += 10;

	mid = 0;
	if (lenc2 < lenb2)
	{
		for (count = lenc2; count < lenb2; count++)
			if (b2[count] != 0)
				mid = 1;
	}

	if (lenc2 < lena2)
	{
		for (count = lenc2; count < lena2; count++)
			if (a2[count] != 0)
				mid = 1;
	}

	error += mid;

	return error;
}

//减法
int F_HA_M(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)//默认认为a>b
{
	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	int error = 0;
	short count = 0;
	char mid=0;

	int find = 0;
	while ((find < lena2 && find < lenb2) && find < lenc2)
		find += 1;

	for (count = find; count >= 0; count--)
	{
		c2[count] = a2[count] - b2[count] - mid;
		if (c2[count] < 0)
		{
			c2[count] += 10;
			mid = 1;
		}
		else
			mid = 0;
	}

	for (count = 0; (count < lena1 && count < lenb1) && count < lenc1; count++)
	{
		c1[count] = a1[count] - b1[count] - mid;
		if (c1[count] < 0)
		{
			c1[count] += 10;
			mid = 1;
		}
		else
			mid = 0;
	}



	return 0;
}

//乘法
int F_HA_MU(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)
{
	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	int finda2;
	int findb2;
	int count;
	int countp;
	int *temp;
	int lentemp;
	int stand10;
	int stand20;

	if ((lena1 + lenb1 + lena2 + lenb2) > ((lenc1 + lenc2) * 2))
	{
		stand10 = lena2 + lenb2;
		stand20 = lena2 + lenb2 - 1;
		lentemp = lena1 + lenb1 + lena2 + lenb2 + 2;
	}
	if ((lena1 + lenb1 + lena2 + lenb2) <= ((lenc1 + lenc2) * 2))
	{
		stand10 = lenc2 * 2;
		stand20 = lenc2 * 2 - 1;
		lentemp = (lenc1 + lenc2) * 2;
	}

	temp = (int*)malloc(sizeof(int)*lentemp);/*这里采用分配内存的方法来使用变量建立一定长度的数组*/
	
	for (count = 0; count < lentemp; count++)/*initializing*/
		temp[count] = 0;

	


	finda2 = F_HA_FIND(a2, lena2, 1);
	findb2 = F_HA_FIND(b2, lenb2, 1);

	
	for (count = findb2; count >= 0; count--)
	{
		for (countp = finda2; countp >= 0; countp--)
		{
			temp[stand20 - count - countp - 1] += (b2[count] * a2[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand10 + count + countp] += (b1[count] * a1[countp]);
		}
	}
	
	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp <= finda2; countp++)
		{
			temp[stand20 + count - countp] += (b1[count] * a2[countp]);
		}
	}

	for (count = 0; count <= findb2; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand20 + countp - count] += (a1[countp] * b2[count]);
		}
	}

	
	F_HA_MASINGLE(temp, lentemp);

	//TEST
	//printf("[乘法 内部temp]:");
	//for (count = lentemp - 1; count >= 0; count--)
	//	printf("%d", temp[count]);
	//printf("\n");

	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	free(temp);

	return 0;
}

//乘法 MOD A 第一个数为浮点数
int F_HA_MUA(double a, char *b1, char *b2, char *c1, char *c2, int lenb1, int lenb2, short lenc1, short lenc2)
{
	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	int finda2;
	int findb2;
	int count;
	int countp;
	int *temp;
	int lentemp;
	int stand10;
	int stand20;

	char a1[3];
	char a2[3];
	int lena1 = 3;
	int lena2 = 3;
	
	F_HA_TRANS(a, a1, a2, lena1, lena2);

	if ((lena1 + lenb1 + lena2 + lenb2) > ((lenc1 + lenc2) * 2))
	{
		stand10 = lena2 + lenb2;
		stand20 = lena2 + lenb2 - 1;
		lentemp = lena1 + lenb1 + lena2 + lenb2 + 2;
	}
	if ((lena1 + lenb1 + lena2 + lenb2) <= ((lenc1 + lenc2) * 2))
	{
		stand10 = lenc2 * 2;
		stand20 = lenc2 * 2 - 1;
		lentemp = (lenc1 + lenc2) * 2;
	}

	temp = (int*)malloc(sizeof(int)*lentemp);/*这里采用分配内存的方法来使用变量建立一定长度的数组*/

	for (count = 0; count < lentemp; count++)/*initializing*/
		temp[count] = 0;




	finda2 = F_HA_FIND(a2, lena2, 1);
	findb2 = F_HA_FIND(b2, lenb2, 1);


	for (count = findb2; count >= 0; count--)
	{
		for (countp = finda2; countp >= 0; countp--)
		{
			temp[stand20 - count - countp - 1] += (b2[count] * a2[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand10 + count + countp] += (b1[count] * a1[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp <= finda2; countp++)
		{
			temp[stand20 + count - countp] += (b1[count] * a2[countp]);
		}
	}

	for (count = 0; count <= findb2; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand20 + countp - count] += (a1[countp] * b2[count]);
		}
	}


	F_HA_MASINGLE(temp, lentemp);

	//TEST
	//printf("[乘法 内部temp]:");
	//for (count = lentemp - 1; count >= 0; count--)
	//	printf("%d", temp[count]);
	//printf("\n");

	//更改在计算完成后应用到结果中，但c不可以为a,b之中的数字，因为在开头就对结果进行的初始化
	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	free(temp);

	return 0;
}

//乘法 MOD B 第二个数为浮点数
int F_HA_MUB(char *a1, char *a2, double b, char *c1, char *c2, int lena1, int lena2, int lenc1, int lenc2)
{
	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	int finda2;
	int findb2;
	int count;
	int countp;
	int *temp;
	int lentemp;
	int stand10;
	int stand20;

	//这个函数新增的部分，用来吧float转化为之后运算用的数字
	char b1[3] = { 0,0,0 };
	char b2[3] = { 0,0,0 };
	int lenb1 = 3;
	int lenb2 = 3;
	F_HA_TRANS(b, b1, b2, lenb1, lenb2);

	if ((lena1 + lenb1 + lena2 + lenb2) > ((lenc1 + lenc2) * 2))
	{
		stand10 = lena2 + lenb2;
		stand20 = lena2 + lenb2 - 1;
		lentemp = lena1 + lenb1 + lena2 + lenb2 + 2;
	}
	if ((lena1 + lenb1 + lena2 + lenb2) <= ((lenc1 + lenc2) * 2))
	{
		stand10 = lenc2 * 2;
		stand20 = lenc2 * 2 - 1;
		lentemp = (lenc1 + lenc2) * 2;
	}

	temp = (int*)malloc(sizeof(int)*lentemp);/*这里采用分配内存的方法来使用变量建立一定长度的数组*/

	for (count = 0; count < (lentemp); count++)/*initializing*/
		temp[count] = 0;




	finda2 = F_HA_FIND(a2, lena2, 1);
	findb2 = F_HA_FIND(b2, lenb2, 1);


	for (count = findb2; count >= 0; count--)
	{
		for (countp = finda2; countp >= 0; countp--)
		{
			temp[stand20 - count - countp - 1] += (b2[count] * a2[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand10 + count + countp] += (b1[count] * a1[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp <= finda2; countp++)
		{
			temp[stand20 + count - countp] += (b1[count] * a2[countp]);
		}
	}

	for (count = 0; count <= findb2; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand20 + countp - count] += (a1[countp] * b2[count]);
		}
	}


	F_HA_MASINGLE(temp, lentemp);

	//TEST
	//printf("[乘法 内部temp]:");
	//for (count = lentemp - 1; count >= 0; count--)
	//	printf("%d", temp[count]);
	//printf("\n");

	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	free(temp);

	return 0;
}

//乘法 MOD C 两个数全为浮点数
int F_HA_MUC(double a, double b, char *c1, char *c2, int lenc1, int lenc2)
{
	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	int finda2;
	int findb2;
	int count;
	int countp;
	int *temp;
	int lentemp;
	int stand10;
	int stand20;

	char a1[3];
	char a2[3];
	int lena1 = 3;
	int lena2 = 3;

	char b1[3];
	char b2[3];
	int lenb1 = 3;
	int lenb2 = 3;

	F_HA_TRANS(a, a1, a2, lena1, lena2);
	F_HA_TRANS(b, b1, b2, lenb1, lenb2);

	if ((lena1 + lenb1 + lena2 + lenb2) > ((lenc1 + lenc2) * 2))
	{
		stand10 = lena2 + lenb2;
		stand20 = lena2 + lenb2 - 1;
		lentemp = lena1 + lenb1 + lena2 + lenb2 + 2;
	}
	if ((lena1 + lenb1 + lena2 + lenb2) <= ((lenc1 + lenc2) * 2))
	{
		stand10 = lenc2 * 2;
		stand20 = lenc2 * 2 - 1;
		lentemp = (lenc1 + lenc2) * 2;
	}

	temp = (int*)malloc(sizeof(int)*lentemp);/*这里采用分配内存的方法来使用变量建立一定长度的数组*/

	for (count = 0; count < lentemp; count++)/*initializing*/
		temp[count] = 0;




	finda2 = F_HA_FIND(a2, lena2, 1);
	findb2 = F_HA_FIND(b2, lenb2, 1);


	for (count = findb2; count >= 0; count--)
	{
		for (countp = finda2; countp >= 0; countp--)
		{
			temp[stand20 - count - countp - 1] += (b2[count] * a2[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand10 + count + countp] += (b1[count] * a1[countp]);
		}
	}

	for (count = 0; count < lenb1; count++)
	{
		for (countp = 0; countp <= finda2; countp++)
		{
			temp[stand20 + count - countp] += (b1[count] * a2[countp]);
		}
	}

	for (count = 0; count <= findb2; count++)
	{
		for (countp = 0; countp < lena1; countp++)
		{
			temp[stand20 + countp - count] += (a1[countp] * b2[count]);
		}
	}


	F_HA_MASINGLE(temp, lentemp);

	//TEST
	//printf("[乘法 内部temp]:");
	//for (count = lentemp - 1; count >= 0; count--)
	//	printf("%d", temp[count]);
	//printf("\n");

	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	free(temp);

	return 0;
}

//n次方
int F_HA_POWN(char *a1, char *a2, int lena1, int lena2, char *b1, char *b2, int lenb1, int lenb2, int n)
{
	F_HA_ZEROD(b1, b2, lenb1, lenb2);

	char *temp1;
	char *temp2;

	temp1 = (char*)malloc(sizeof(char)*lenb1);
	temp2 = (char*)malloc(sizeof(char)*lenb2);

	int count;

	if (n >= 1)
		F_HA_MOVE(a1, a2, b1, b2, lena1, lena2, lenb1, lenb2);

	if (n >= 2)
	{
		for (count = 1; count < n; count++)
		{
			F_HA_MU(b1, b2, a1, a2, temp1, temp2, lenb1, lenb2, lena1, lena2, lenb1, lenb2);
			F_HA_MOVE(temp1, temp2, b1, b2, lenb1, lenb2, lenb1, lenb2);
		}
	}

	return 0;
}

//开根号
int F_HA_ROOT(char *a1, char *a2, char *b1, char *b2, int lena1, int lena2, int lenb1, int lenb2)
{
	//Initialzing B
	F_HA_ZEROD(b1, b2, lenb1, lenb2);

	int deep = 0;
	int all;
	int all1;
	int all2;
	int fin;
	int tencount;
	int check;
	int count;

	if (lena1 > (lenb1 * 2))
		all1 = lena1;
	else
		all1 = lenb1 * 2;

	if (lena2 > (lenb2) * 2)
		all2 = lena2;
	else
		all2 = lenb2 * 2;

	all = all1 + all2;//注意是一和二

	int lenc1 = all1;
	int lenc2 = all2;
	char *c1;
	char *c2;
	c1 = (char*)malloc(sizeof(char)*lenc1);
	c2 = (char*)malloc(sizeof(char)*lenc2+2);
	for (count = 0; count < lenc1; count++)
		c1[count] = 0;
	for (count = 0; count < (lenc2+2); count++)
		c2[count] = 0;

	for (deep = all; deep >= 0; deep--)
	{
		fin = 0;
		for (tencount = 1; fin == 0 ; tencount++) 
		{
			F_HA_ACCP(b1, b2, lenb1, lenb2, deep);
			F_HA_MU(b1, b2, b1, b2, c1, c2, lenb1, lenb2, lenb1, lenb2, lenc1, lenc2);
			
			/*
			//TEST
			printf("[root内部的b和c]%d:",tencount);
			F_HA_PRINT(b1, b2, lenb1, lenb2, 0);
			printf(" ");
			F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			*/

			check = F_HA_COMP(a1, a2, c1, c2, lena1, lena2, lenc1, lenc2);
			if (check == 1)
			{ 
				F_HA_ACCM(b1, b2, lenb1, lenb2, deep);
				fin = 1;
			}
			if (check == 2)
				return 0;
			if (tencount == 9)
				fin = 1;
		
		}
	}

	return 0;
}

//除法
int F_HA_DIV(char *a21, char *a22, char *b1, char *b2, char *c1, char *c2, int lena1, int lena2, int lenb1, int lenb2, int lenc1, int lenc2)
{
	int count;
	int tencount;
	int ok = 0;
	int check;

	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	//Create array a
	char *a1;
	char *a2;
	a1 = (char*)malloc(sizeof(char)*lena1);
	a2 = (char*)malloc(sizeof(char)*lena2);
	F_HA_MOVE(a21, a22, a1, a2, lena1, lena2, lena1, lena2);
	char *a31;
	char *a32;
	a31 = (char*)malloc(sizeof(char)*lena1);
	a32 = (char*)malloc(sizeof(char)*lena2);

	//Create array d
	char *d1;
	char *d2;
	int lend1 = lenc1 + lenb1;
	int lend2 = lenc2 + lenb2;
	d1 = (char*)malloc(sizeof(char)*lend1);
	d2 = (char*)malloc(sizeof(char)*lend2);

	F_HA_ZEROD(d1, d2, lend1, lend2);

	for (count = lenc1; count >= 0; count--)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, count + lenc2);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, count + lenc2);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}

	for (count = 0; count < lenc2; count++)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, lenc2 - count);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, lenc2 - count);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}


	return 0;
}

//除法 MOD A 第一个数为浮点数
int F_HA_DIVA(double a, char *b1, char *b2, char *c1, char *c2, int lenb1, int lenb2, int lenc1, int lenc2)
{
	int count;
	int tencount;
	int ok = 0;
	int check;
	char a21[3];
	char a22[3];
	int lena1 = 3;
	int lena2 = 3;

	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	F_HA_ZEROD(a21, a22, 3, 3);
	F_HA_TRANS(a, a21, a22, 3, 3);

	//Create array a
	char *a1;
	char *a2;
	a1 = (char*)malloc(sizeof(char)*lena1);
	a2 = (char*)malloc(sizeof(char)*lena2);
	F_HA_MOVE(a21, a22, a1, a2, lena1, lena2, lena1, lena2);
	char *a31;
	char *a32;
	a31 = (char*)malloc(sizeof(char)*lena1);
	a32 = (char*)malloc(sizeof(char)*lena2);

	//Create array d
	char *d1;
	char *d2;
	int lend1 = lenc1 + lenb1;
	int lend2 = lenc2 + lenb2;
	d1 = (char*)malloc(sizeof(char)*lend1);
	d2 = (char*)malloc(sizeof(char)*lend2);

	F_HA_ZEROD(d1, d2, lend1, lend2);

	for (count = lenc1; count >= 0; count--)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, count + lenc2);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, count + lenc2);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}

	for (count = 0; count < lenc2; count++)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, lenc2 - count);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, lenc2 - count);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}


	return 0;
}

//除法 MOD B 第二个数为浮点数
int F_HA_DIVB(char *a21, char *a22, double b, char *c1, char *c2, int lena1, int lena2, int lenc1, int lenc2)
{
	int count;
	int tencount;
	int ok = 0;
	int check;
	int lenb1 = 3;
	int lenb2 = 3;
	char b1[3];
	char b2[3];

	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	F_HA_TRANS(b, b1, b2, 3, 3);

	//Create array a
	char *a1;
	char *a2;
	a1 = (char*)malloc(sizeof(char)*lena1);
	a2 = (char*)malloc(sizeof(char)*lena2);
	F_HA_MOVE(a21, a22, a1, a2, lena1, lena2, lena1, lena2);
	char *a31;
	char *a32;
	a31 = (char*)malloc(sizeof(char)*lena1);
	a32 = (char*)malloc(sizeof(char)*lena2);

	//Create array d
	char *d1;
	char *d2;
	int lend1 = lenc1 + lenb1;
	int lend2 = lenc2 + lenb2;
	d1 = (char*)malloc(sizeof(char)*lend1);
	d2 = (char*)malloc(sizeof(char)*lend2);

	F_HA_ZEROD(d1, d2, lend1, lend2);

	for (count = lenc1; count >= 0; count--)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, count + lenc2);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, count + lenc2);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}

	for (count = 0; count < lenc2; count++)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, lenc2 - count);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, lenc2 - count);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}


	return 0;
}

//除法 MOD C 两个数全为浮点数
int F_HA_DIVC(double a, double b, char *c1, char *c2, int lenc1, int lenc2)
{
	int count;
	int tencount;
	int ok = 0;
	int check;
	char a21[3];
	char a22[3];
	char b1[3];
	char b2[3];
	int lena1 = 3;
	int lena2 = 3;
	int lenb1 = 3;
	int lenb2 = 3;

	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	F_HA_ZEROD(a21, a22, 3, 3);
	F_HA_TRANS(a, a21, a22, 3, 3);
	F_HA_ZEROD(b1, b2, 3, 3);
	F_HA_TRANS(b, b1, b2, 3, 3);

	//F_HA_PRINT(a21, a22, 3, 3, 1);
	//F_HA_PRINT(b1, b2, 3, 3, 1);

	//Create array a
	char *a1;
	char *a2;
	a1 = (char*)malloc(sizeof(char)*lena1);
	a2 = (char*)malloc(sizeof(char)*lena2);
	F_HA_MOVE(a21, a22, a1, a2, lena1, lena2, lena1, lena2);
	char *a31;
	char *a32;
	a31 = (char*)malloc(sizeof(char)*lena1);
	a32 = (char*)malloc(sizeof(char)*lena2);

	//Create array d
	char *d1;
	char *d2;
	int lend1 = lenc1 + lenb1;
	int lend2 = lenc2 + lenb2;
	d1 = (char*)malloc(sizeof(char)*lend1);
	d2 = (char*)malloc(sizeof(char)*lend2);

	F_HA_ZEROD(d1, d2, lend1, lend2);

	for (count = lenc1; count >= 0; count--)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, count + lenc2);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, count + lenc2);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}

	for (count = 0; count < lenc2; count++)
	{
		ok = 0;
		for (tencount = 0; ok == 0; tencount++)
		{
			F_HA_ACCP(c1, c2, lenc1, lenc2, lenc2 - count);
			F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
			check = F_HA_COMP(a1, a2, d1, d2, lena1, lena2, lend1, lend2);
			//printf("[除法内部]：\n");
			//F_HA_PRINT(c1, c2, lenc1, lenc2, 1);
			if (tencount == 8)
				ok = 1;
			if (check == 2)
				return 0;
			if (check == 1)
			{
				ok = 1;
				F_HA_ACCM(c1, c2, lenc1, lenc2, lenc2 - count);
				//F_HA_MU(c1, c2, b1, b2, d1, d2, lenc1, lenc2, lenb1, lenb2, lend1, lend2);
				//F_HA_MOVE(a1, a2, a31, a32, lena1, lena2, lena1, lena2);
				//F_HA_M(a21, a21, d1, d2, a1, a2, lena1, lena2, lend1, lend2, lena1, lena2);
			}
		}
	}


	return 0;
}

//求和一个数最接近的分数，第一个参数传递需要转换的浮点数，第二个参数传递一个有两个int类型元素的数组,num[0]为分子，num[1]为分母
int F_HA_FTOFR(char *co1, char *co2, int lenco1, int lenco2, int *num)
{
	int len1 = lenco1;
	int len2 = lenco2 + PRECISION;

	char *com1;
	char *com2;
	com1 = (char*)malloc(sizeof(char)*len1);
	com2 = (char*)malloc(sizeof(char)*len2);

	F_HA_MOVE(co1, co2, com1, com2, lenco1, lenco2, len1, len2);

	char *pre1;
	char *pre2;
	pre1 = (char*)malloc(sizeof(char)*len1);
	pre2 = (char*)malloc(sizeof(char)*len2);

	F_HA_ZEROD(pre1, pre2, len1, len2);
	F_HA_ACCP(pre1, pre2, len1, len2, len2 - PRECISION);

	//TEST
	F_HA_PRINT(pre1, pre2, len1, len2, 1);

	char out11[10] = { 1 };//分子
	char out12[1] = { 0 };
	char out21[10] = { 1 };//分母
	char out22[1] = { 0 };
	int lenout1 = 10;
	int lenout2 = 1;
	int comp = 0;

	char *try1;
	char *try2;
	try1 = (char*)malloc(sizeof(char)*len1);//这里两个分配保守了，以后考虑好可以去掉点
	try2 = (char*)malloc(sizeof(char)*len2);

	char *trydiff1;//结果的误差
	char *trydiff2;
	trydiff1 = (char*)malloc(sizeof(char)*len1);//这里两个分配保守了，以后考虑好可以去掉点
	trydiff2 = (char*)malloc(sizeof(char)*len2);

	int count;
	int tencount;
	int tentemp;

	while (comp == 0)
	{
		//比较决定增加哪个部分
		F_HA_DIV(out11, out12, out21, out22, try1, try2, lenout1, lenout2, lenout1, lenout2, len1, len2);
		comp = F_HA_COMP(try1, try2, com1, com2, len1, len2, len1, len2);
		//TEST
		F_HA_PRINT(out11, out12, lenout1, lenout2, 1);
		F_HA_PRINT(out21, out22, lenout1, lenout2, 1);
		F_HA_PRINT(try1, try2, len1, len2, 1);
		
		//增加值
		if (comp == 1)
			F_HA_ACCP(out11, out12, lenout1, lenout2, 2);
		if (comp == 0)
			F_HA_ACCP(out21, out22, lenout1, lenout2, 2);
		if (comp == 2)
			continue;

		//再次比较，求误差
		F_HA_DIV(out11, out12, out21, out22, try1, try2, lenout1, lenout2, lenout1, lenout2, len1, len2);//求此时分数值try
		comp = F_HA_COMP(try1, try2, com1, com2, len1, len2, len1, len2);//决定用哪个减哪个得到的误差为正数
		if (comp == 0)
			F_HA_M(try1, try2, com1, com2, trydiff1, trydiff2, len1, len2, len1, len2, len1, len2);
		if (comp == 1)
			F_HA_M(com1, com2, try1, try2, trydiff1, trydiff2, len1, len2, len1, len2, len1, len2);
		if (comp == 2)
			continue;

		//TEST
		F_HA_PRINT(com1, com2, len1, len2, 1);
		F_HA_PRINT(try1, try2, len1, len2, 1);
		F_HA_PRINT(trydiff1, trydiff2, len1, len2, 1);

		putchar('\n');

		comp = F_HA_COMP(trydiff1, trydiff2, pre1, pre2, len1, len2, len1, len2);
	}

	num[1] = 0;
	num[0] = 0;

	for (count = 0; count < lenout1; count++)
	{
		if (out11[count] != 0)
		{
			tentemp = out11[count];
			for (tencount = 0; tencount < count; tencount++)
				tentemp *= 10;
			num[0] += tentemp;
		}
	}

	for (count = 0; count < lenout1; count++)
	{
		if (out21[count] != 0)
		{
			tentemp = out21[count];
			for (tencount = 0; tencount < count; tencount++)
				tentemp *= 10;
			num[1] += tentemp;
		}
	}

	return 0;
}

//次方
int F_HA_POW(char *a1, char *a2, char *b1, char *b2, char *n1, char *n2, int lena1, int lena2, int lenb1, int lenb2, int lenn1, int lenn2)
{
	int markroot;
	int mark;


	return 0;
}

/*====================识别式子====================*/
int F_HA_DEFINE(const char *in, char nameout[][11], int lenout[][2], int *name_count)
{
	int len1 = 0;
	int len2 = 0;
	int cursor = 0;
	char name[11] = { 0 };

	while (in[cursor] != ' ')//排除说明字符
		cursor++;
	while (in[cursor] == ' ')//允许两个量之间多个空格
		cursor++;

	for (int i = 0; in[cursor] != ' '; i++, cursor++)//记录变量名字
	{
		if ((in[cursor] <= 'z'&&in[cursor] >= 'a') || (in[cursor] <= 'Z'&&in[cursor] >= 'A'))
		{
			name[i] = in[cursor];
			if (i == 10)
			{
				name[i] = '0';
				while (in[cursor] != ' ')
				{
					cursor++;
					continue;
				}
				break;
			}
		}
	}

	while (in[cursor] == ' ')//允许两个量之间多个空格
		cursor++;

	while (in[cursor] != ' ')//记录第一个长度
	{
		if (in[cursor] <= '9'&&in[cursor] >= '0')
		{
			len1 *= 10;
			len1 += in[cursor] - '0';
			cursor++;
		}
		else
			return -1;
	}

	while (in[cursor] == ' ')//允许两个量之间多个空格
		cursor++;

	while (in[cursor] != ' '&&in[cursor]!='\n'&&in[cursor]!='\0')//记录第二个长度
	{
		if (in[cursor] <= '9'&&in[cursor] >= '0')
		{
			len2 *= 10;
			len2 += in[cursor] - '0';
			cursor++;
		}
		else
			return -2;
	}

	strncpy(nameout[*name_count], name, 11);
	lenout[*name_count][0] = len1;
	lenout[*name_count][1] = len2;
	*name_count++;

	return 0;
}

int F_HA_EXPLAIN(char *in)
{
	//利用全局变量计算
	static char name[10][11];
	static int name_count = 0;
	static int len[10][2];
	static char *single_line;//分解出的单行储存在这里
	
	single_line = (char*)malloc(sizeof(char) * 100);

	int len1temp = 0;
	int len2temp = 0;

	int cursor = 0;
	int i;
	int error = 0;
	int inlen;
	inlen = strlen(in);

	

	//提取第一段文字
	for (i = 0; in[cursor] != '\n'&&cursor < inlen; i++, cursor++)
	{
		single_line[i] = in[cursor];
	}
	single_line[i] = '\0';//格式化为字符串


	switch (single_line[0])
	{
	case '#'://用#开头表示说明
		switch (single_line[1])
		{
		case 'd'://define
			char nametemp[11];
			len1temp = 0;
			len2temp = 0;
			error = F_HA_DEFINE(single_line, name, len, &name_count);
			if (error != 0)
			{
				printf("ERROER:定义错误\n");
				break;
			}
			break;
		case 'p'://print

			break;
		default:

			break;
		}
	default:

		break;
	}
	

	return 0;
	//-1 识别错误
}




/*
====================程序报错====================
##加法
00000010 前端溢出
00000001 后端溢出

##比大小返回:
a>b 0
a<b 1
a=b 2

====================必要说明====================
数组中0为最接近小数点的一位
数组长度不能为0（？）



====================输入示例====================
#define a 100 100
#define b 100 100
#define c 100 50
#c=a+b
#print c
*/
