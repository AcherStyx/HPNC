#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
/*====================���ߺ���====================*/
//��ӡBar
void F_HA_BAR(char what, int num,int enter)
{
	int count;
	for (count = 0; count < num; count++)
		putchar(what);
	if (enter != 0)
		putchar('\n');
}

//�ҵ���һ����Ϊ0�������������������������￪ʼѰ�ң�0��ͷ��ʼѰ�ң���Ϊ0��ĩβ��ʼ������ֵ�Ƕ�Ӧ�������±�
int F_HA_FIND(char *a, int lena, char where)
{
	int count = 0;
	if (where == 0)//where=0��0��ʼ����
	{
		for (count = 0; count < lena; count++)
			if (a[count] != 0)
				return count;
	}
	else//where=1��ĩβ��ʼ��
	{
		for (count = (lena - 1); count >= 0; count--)
			if (a[count] != 0)
				return count;
	}
	return 0;
}

//������������С���������ֵ����������ӡ��һ��������С��
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

//��ӡ�������飬��������������ѡ���ĩβ���Ǵӿ�ͷ��ʼ��ӡ��0�ӿ�ͷ����Ϊ0��ĩβ
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

//��ӡһ����������������ȥ�����˶����0
void F_HA_PRINTC(char *a1, char *a2, int lena1, int lena2, int enter)
{
	int count;
	int end1;
	int end2;
	end1 = F_HA_FIND(a1, lena1, 1) + 1;
	end2 = F_HA_FIND(a2, lena2, 1) + 1;
	F_HA_PRINT(a1, a2, end1, end2, enter);
}

//�ͼ����������������������ɵ�С����ֻ�ܴ���С��20������0�ģ����ڼӷ�
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

//�߼����������������������ɵ�С�����ܴ������0����������
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

//�߼�����ֻ���һ�����飬�ܴ������0����������
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

//�ۼӣ�����Сһλ��ʼ���е��ۼ�1��Ч�ʱȽϵ�
int F_HA_ACC(char *a1, char *a2, int lena1, int lena2)
{
	a2[(lena2 - 1)] += 1;
	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

//�ۼӣ����Զ���λ����ʼ�ۼ�1�����һ������n���������￪ʼ�������һλ�����nλ��ʼ�ۼ�
int F_HA_ACCP(char *a1, char *a2, int lena1, int lena2, int n)
{
	if (n <= lena2 && n != 0)
		a2[lena2 - n] += 1;
	else if (n > lena2 && n <= (lena1 + lena2))
		a1[n - lena2 - 1] += 1;

	F_HA_MA(a1, a2, lena1, lena2);
	return 0;
}

//�ۼ������Զ���λ����ʼ�ۼ�1�����һ������n���������￪ʼ�������һλ�����nλ��ʼ�ۼ�
int F_HA_ACCM(char *a1, char *a2, int lena1, int lena2, int n)
{
	if (n <= lena2 && n != 0)
		a2[lena2 - n] -= 1;
	else if (n > lena2 && n <= (lena1 + lena2))
		a1[n - lena2 - 1] -= 1;

	F_HA_MA(a1, a2, lena1, lena2);
	
	return 0;
}

//�ȴ�Сa>b 0 ; a<b 1 ; a=b 2
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

//��ӡ[test%d]
void F_HA_TEST(short num)
{
	printf("[TEST%d]:\n", num);
}

//��ʼ����Ϊ�����������0
void F_HA_ZEROS(char *a, int len)
{
	int count;
	for (count = 0; count < len; count++)
		a[count] = 0;
}

//��ʼ����Ϊ����������ɵ�һ�����������0
void F_HA_ZEROD(char *a1, char*a2, int lena1, int lena2)
{
	int count;
	for (count = 0; count < lena1; count++)
		a1[count] = 0;
	for (count = 0; count < lena2; count++)
		a2[count] = 0;
}

//��һ����������ֵ�ƶ�����һ����
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

//��һ��������ת�浽����������
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

	printf("��TRANS�ڲ����ԡ�");
	printf("%f|", flo);
	F_HA_PRINT(a1, a2, lena1, lena2, 1);


}

//����û������С����ת�浽�����������γ�һ��������
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
			printf("��!���������ֳ�������λ��\n");
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
			printf("��!��С�����ֳ�������λ��\n");
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


	printf("ʵ��¼���ֵΪ��");
	F_HA_PRINTC(a1, a2, lena1, lena2, 1);

	free(temp);
	return error;
}

/*====================���㺯��====================*/

//�ӷ�
int F_HA_P(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)
{
	int error = 0;
	int count;

	//Initializing C
	F_HA_ZEROD(c1, c2, lenc1, lenc2);

	//�ҵ��ұ߷���Ҫ�������������������һλ
	int find = 0;
	while ((find < lena2 || find < lenb2) && find < lenc2)
		find += 1;

	char mid = 0;//��ʼ��
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
	//���
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

//����
int F_HA_M(char *a1, char *a2, char *b1, char *b2, char *c1, char *c2, short lena1, short lena2, short lenb1, short lenb2, short lenc1, short lenc2)//Ĭ����Ϊa>b
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

//�˷�
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

	temp = (int*)malloc(sizeof(int)*lentemp);/*������÷����ڴ�ķ�����ʹ�ñ�������һ�����ȵ�����*/
	
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
	//printf("[�˷� �ڲ�temp]:");
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

//�˷� MOD A ��һ����Ϊ������
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

	temp = (int*)malloc(sizeof(int)*lentemp);/*������÷����ڴ�ķ�����ʹ�ñ�������һ�����ȵ�����*/

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
	//printf("[�˷� �ڲ�temp]:");
	//for (count = lentemp - 1; count >= 0; count--)
	//	printf("%d", temp[count]);
	//printf("\n");

	//�����ڼ�����ɺ�Ӧ�õ�����У���c������Ϊa,b֮�е����֣���Ϊ�ڿ�ͷ�ͶԽ�����еĳ�ʼ��
	for (count = 0; count < lenc2; count++)
		c2[count] = temp[stand20 - count];
	for (count = 0; count < lenc1; count++)
		c1[count] = temp[stand10 + count];

	free(temp);

	return 0;
}

//�˷� MOD B �ڶ�����Ϊ������
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

	//������������Ĳ��֣�������floatת��Ϊ֮�������õ�����
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

	temp = (int*)malloc(sizeof(int)*lentemp);/*������÷����ڴ�ķ�����ʹ�ñ�������һ�����ȵ�����*/

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
	//printf("[�˷� �ڲ�temp]:");
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

//�˷� MOD C ������ȫΪ������
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

	temp = (int*)malloc(sizeof(int)*lentemp);/*������÷����ڴ�ķ�����ʹ�ñ�������һ�����ȵ�����*/

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
	//printf("[�˷� �ڲ�temp]:");
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

//n�η�
int F_HA_POW(char *a1, char *a2, int lena1, int lena2, char *b1, char *b2, int lenb1, int lenb2, int n)
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

//������
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

	all = all1 + all2;//ע����һ�Ͷ�

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
			printf("[root�ڲ���b��c]%d:",tencount);
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

//����
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
			//printf("[�����ڲ�]��\n");
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
			//printf("[�����ڲ�]��\n");
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

//���� MOD A ��һ����Ϊ������
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
			//printf("[�����ڲ�]��\n");
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
			//printf("[�����ڲ�]��\n");
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

//���� MOD B �ڶ�����Ϊ������
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
			//printf("[�����ڲ�]��\n");
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
			//printf("[�����ڲ�]��\n");
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

//���� MOD C ������ȫΪ������
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
			//printf("[�����ڲ�]��\n");
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
			//printf("[�����ڲ�]��\n");
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





/*
====================���򱨴�====================
##�ӷ�
00000010 ǰ�����
00000001 ������

##�ȴ�С����:
a>b 0
a<b 1
a=b 2

====================��Ҫ˵��====================
������0Ϊ��ӽ�С�����һλ
���鳤�Ȳ���Ϊ0������

*/ 