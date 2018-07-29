#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(char));}

/*====================模块工具====================*/
void F_HA_PRINT(char *a1, char *a2, int lena1, int lena2,int printenter)
{
	int count;
	for (count = (lena1 - 1); count >= 0; count--)
		printf("%d", a1[count]);
	printf(".");
	for (count = 0; count < lena2; count++)
		printf("%d", a2[count]);

	if (printenter = 1)
		printf("\n");
}

int F_HA_FIND(char *a,int lena,char where)
{
	int count = 0;
	if (where = 0)//where=0从0开始查找
		for (count = 0; count < lena; count++)
			if (a[count] != 0)
				return count;
	if (where = 1)//wwhere=1从末尾开始找
		for (count = (lena - 1); count >= 0; count--)
			if (a[count] != 0)
				return count;
	return 0;
}

int F_HA_MA(char *a1, char *a2, int lena1, int lena2)//simple manage,only teens
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
		else
		{
			mid = 0;
		}
	}
	return mid;
}

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

int F_HA_ACC(char *a1, char *a2, int lena1, int lena2)
{
	a2[(lena2 - 1)] += 1;
	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

int F_HA_ACCP(char *a1, char *a2, int lena1, int lena2, int n)
{
	if (n <= lena2 && n != 0)
		a2[lena2 - n] += 1;
	else if (n > lena2)
		a1[n - lena2 - 1] += 1;

	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

int F_HA_COMP(char *a1, char *a2, char *b1, char *b2,int lena1,int lena2,int lenb1,int lenb2)//返回:a>b 0;a<b 1;a=b 2
{
	int amaxplace;
	int bmaxplace;
	int count;

	amaxplace = F_HA_FIND(a1, lena1, 1);
	bmaxplace = F_HA_FIND(b1, lenb1, 1);

	if (amaxplace != 0 || bmaxplace != 0)
	{
		if (amaxplace > bmaxplace)
			return 0;
		if (amaxplace < bmaxplace)
			return 1;
		if (amaxplace = bmaxplace)
		{
			if (a1[amaxplace] > b1[bmaxplace])
				return 0;
			if (a1[amaxplace] < b1[bmaxplace])
				return 1;
			if (a1[amaxplace] = b1[bmaxplace])
			{
				for (count = amaxplace; count >= 0; count--)
				{
					if (a2[amaxplace] > b2[bmaxplace])
						return 0;
					if (a2[amaxplace] < b2[bmaxplace])
						return 1;
				}
			}
		}
	}

	int placea;
	int placeb;
	int len;
	int mark;
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

	amaxplace = F_HA_FIND(a2, lena2, 0);
	bmaxplace = F_HA_FIND(b2, lenb2, 0);

	if (amaxplace < bmaxplace)
		return 0;
	if (amaxplace > bmaxplace)
		return 1;
	if (amaxplace = bmaxplace)
	{
		for (count = amaxplace; count <= len; count++)
		{
			if (a2[amaxplace] > b2[bmaxplace])
				return 0;
			if (a2[amaxplace] < b2[bmaxplace])
				return 1;
		}
	}

	if (mark == 0)
		if (placeb > placea)
			return 1;
	if (mark == 1)
		if (placeb < placea)
			return 0;

	return 2;
}

void F_HA_TEST(short num)
{
	printf("[TEST%d]:\n", num);
}
/*====================加法运算====================*/
int F_HA_P(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)
{
	int error = 0;
	int count;

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

int F_HA_M(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)//默认认为a>b
{
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

int F_HA_MU(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)
{
	int finda2;
	int findb2;
	int count;
	int countp;
	int *temp;

	temp = (int*)malloc(sizeof(int)*(lena1 + lenb1 + lena2 + lenb2));/*这里采用分配内存的方法来使用变量建立一定长度的数组*/
	for (count = 0; count < (lena1 + lenb1 + lena2 + lenb2 - 1); count++)/*initializing*/
		temp[count] = 0;


	int stand10 = lena2 + lenb2;
	int stand20 = lena2 + lenb2 - 1;

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

	
	F_HA_MASINGLE(temp, lena1 + lena2 + lenb1 + lenb2);


	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	return 0;
}

int F_HA_ROOT(char *a1, char *a2, char *b1, char *b2, int lena1, int lena2, int lenb1, int lenb2)
{
	int deep = 0;
	int count;
	int all = (lena1 + lena2);
	int fin;
	int tencount;

	char *c1;
	char *c2;
	c1 = (char*)malloc(sizeof(char)*lena1);
	c2 = (char*)malloc(sizeof(char)*lena2);

	for (deep = all; deep >= 0; deep--)
	{
		fin = 0;
		for (tencount = 0; fin = 0; tencount++)
		{
			F_HA_ACCP(b1, b2, lenb1, lenb2, deep);
			F_HA_MU(b1, b2, b1, b2, c1, c2, lenb1, lenb2, lenb1, lenb2, lena1, lena2);
		}
	}

	return 0;
}

/*====================程序报错====================*/
//00000010 前端溢出
//00000001 后端溢出
//

/*====================必要说明====================*/
//数组中0为最接近小数点的一位
//数组长度不能为0