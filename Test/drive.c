#include <stdio.h>
#include "Function_HA.h"
#include <math.h>
#include <stdlib.h>

int main(void)
{
	char a1[10] = { 0,0,9,0,0,0,0,0,0,0 };
	char a2[10] = { 0,0,0,1,0,0,1,0,2,4 };
	char b1[5] = { 1,8,5,6,4 };
	char b2[5] = { 8,1,2,6,4 };
	char c1[7] = { 0,0,0,0,0,0,0 };
	char c2[3] = { 0,0,0 };
	int error = 0;

	short lena1 = sizeof(a1) / sizeof(a1[0]);
	short lena2 = sizeof(a2) / sizeof(a2[0]);
	short lenb1 = sizeof(b1) / sizeof(b1[0]);
	short lenb2 = sizeof(b2) / sizeof(b2[0]);
	short lenc1 = sizeof(c1) / sizeof(c1[0]);
	short lenc2 = sizeof(c2) / sizeof(c2[0]);

	int count;


	//开始计算
	error += F_HA_P(a1, a2, b1, b2, c1, c2, lena1, lena2, lenb1, lenb2, lenc1, lenc2);

	//plus test
	printf("【加法】\n");
	printf("a:");
	for (count = 9; count >= 0; count--)
		printf("%d", a1[count]);
	printf(".");
	for (count = 0; count < 10; count++)
		printf("%d", a2[count]);

	printf("\nb:");
	for (count = 4; count >= 0; count--)
		printf("%d", b1[count]);
	printf(".");
	for (count = 0; count < 5; count++)
		printf("%d", b2[count]);

	printf("\nc:");
	for (count = 6; count >= 0; count--)
		printf("%d", c1[count]);
	printf(".");
	for (count = 0; count < 3; count++)
		printf("%d", c2[count]);

	printf("\nError Code:%08hd\n", error);

	//compare tset
	printf("【比大小】\n");
	int compare;
	char compa1[2] = { 4,0 };
	char compa2[5] = { 0,0,0,0,0 };
	char compb1[2] = { 1,0 };
	char compb2[5] = { 0,0,0,0,0 };
	compare = F_HA_COMP(compa1, compa2, compb1, compb2, 2, 5, 2, 5);
	if (compare == 0)
		printf("a>b");
	if (compare == 1)
		printf("a<b");
	if (compare == 2)
		printf("a=b");
	printf("\n");

	//manage test
	printf("【整理】\n");
	char manage1[5] = { 4,15,18,16,2 };
	char manage2[5] = { 9,12,16,18,14 };
	F_HA_MA(manage1, manage2, 5, 5);
	F_HA_PRINT(manage1, manage2, 5, 5, 1);

	//accumulate test
	printf("【积累】\n");
	unsigned long long acccount;
	char accumulate1[5] = { 0,0,0,0,0 };
	char accumulate2[5] = { 0,0,0,0,0 };
	for (acccount = 0; acccount < 9999998; acccount++)
		F_HA_ACC(accumulate1, accumulate2, 5, 5);
	F_HA_PRINT(accumulate1, accumulate2, 5, 5, 1);

	//char test
	printf("【字符】\n");
	char fushu = 0;
	fushu -= 5;
	printf("%d\n", fushu);

	//minus test
	printf("【减法】\n");
	char minuse1[7] = { 0,0,0,0,0,0,0 };
	char minuse2[4] = { 0,0,0,0 };
	F_HA_M(a1, a2, b1, b2, minuse1, minuse2, 10, 10, 5, 5, 7, 4);
	F_HA_PRINT(minuse1, minuse2, 7, 4, 1);

	//% test
	printf("【取余数】\n");
	int bfs = -11;
	int houmiande = 10;
	printf("%d\n", bfs%houmiande);

	//manage test
	printf("【整理P】\n");
	char managep1[10] = { 1,65,23,48,25,48,20,15,26,1 };
	char managep2[5] = { 5,20,46,23,15 };
	F_HA_MAP(managep1, managep2, 10, 5);
	F_HA_PRINT(managep1, managep2, 10, 5, 1);

	//multiplication test
	printf("【乘法】\n");
	char yuansu1[5] = { 9,9,9,9,9 };
	char yuansu2[5] = { 9,9,9,9,9 };
	char yuansu21[5] = { 9,9,9,9,9 };
	char yuansu22[5] = { 9,9,9,9,9 };
	char mult1[10] = { 0,0,0,0,0,0,0 };
	char mult2[10] = { 0,0,0,0,0,0,0,0,0,0 };
	//元素
	printf("a:");
	F_HA_PRINT(yuansu1, yuansu2, 5, 5, 1);
	printf("b:");
	F_HA_PRINT(yuansu21, yuansu22, 5, 5, 1);
	F_HA_MU(yuansu1, yuansu2, yuansu21, yuansu22, mult1, mult2, 5, 5, 5, 5, 10, 10);
	//结果
	printf("结果:");
	F_HA_PRINT(mult1, mult2, 10, 10, 1);

	//malloc test
	printf("【数组变量定义】\n");
	char * mal1; 
	char * mal2;
	mal1 = (char*)malloc(sizeof(char) * 8);
	mal2 = (char*)malloc(sizeof(char) * 5);

	int mal3;
	for (mal3 = 0; mal3 < 8; mal3++)
		mal1[mal3] = mal3;
	for (mal3 = 0; mal3 < 5; mal3++)
		mal2[mal3] = mal3;
	F_HA_PRINT(mal1, mal2, 8, 5, 1);

	for (count = (8 - 1); count >= 0; count--)
		printf("%d", mal1[count]);
	printf(".");
	for (count = 0; count < 5; count++)
		printf("%d", mal2[count]);

	printf("\n");
	int * mali1;
	int * mali2;
	mali1 = (int*)malloc(sizeof(int) * 8);
	mali2 = (int*)malloc(sizeof(int) * 5);
	for (mal3 = 0; mal3 < 8; mal3++)
		mali1[mal3] = mal3;
	for (mal3 = 0; mal3 < 5; mal3++)
		mali2[mal3] = mal3;

	for (count = (8 - 1); count >= 0; count--)
		printf("%d", mali1[count]);
	printf(".");
	for (count = 0; count < 5; count++)
		printf("%d", mali2[count]);
	printf("\n");

	//malloc test 2
	printf("【变量定义数组 乘法】\n");
	char * mal21;
	char * mal22;
	mal21 = (char*)malloc(sizeof(char) * 8);
	mal22 = (char*)malloc(sizeof(char) * 5);

	for (mal3 = 0; mal3 < 8; mal3++)
		mal21[mal3] = mal3;
	for (mal3 = 0; mal3 < 5; mal3++)
		mal22[mal3] = mal3;

	printf("mal:");
	F_HA_PRINT(mal1, mal2, 8, 5, 1);
	printf("mali:");
	F_HA_PRINT(mal21, mal22, 8, 5, 1);

	char malout1[10];
	char malout2[10];
	F_HA_MU(mal1, mal2, mal21, mal22, malout1, malout2, 8, 5, 8, 5, 10, 10);
	F_HA_PRINT(malout1, malout2, 10, 10, 1);

	//ACCP test
	printf("【定量积累】\n");
	char accp1[5] = { 0,0,0,0,0 };
	char accp2[4] = { 0,0,0,0 };
	F_HA_ACCP(accp1, accp2, 5, 4, 0);
	F_HA_PRINT(accp1, accp2, 5, 4, 1);
	F_HA_ACCP(accp1, accp2, 5, 4, 8);
	F_HA_PRINT(accp1, accp2, 5, 4, 1);


	//ACCP test
	printf("【定量减少】\n");
	char accm1[3] = { 0,0,0 };
	char accm2[4] = { 0,0,0,0 };
	F_HA_ACCP(accm1, accm2, 3, 4, 6);
	F_HA_ACCM(accm1, accm2, 3, 4, 5);
	F_HA_PRINT(accm1, accm2, 3, 4, 1);

	//root test
	printf("【开平方根】\n");
	char rootn1[1] = { 9 };
	int lenrootn1 = 1;
	char rootn2[4] = { 5,6,7,5 };
	int lenrootn2 = 4;
	char rootm1[1];
	int lenrootm1 = 1;
	char rootm2[1000];
	int lenrootm2 = 1000;
	printf("需要开平方的数:");
	F_HA_PRINT(rootn1, rootn2, lenrootn1, lenrootn2, 1);
	//conculate
	F_HA_ROOT(rootn1, rootn2, rootm1, rootm2, lenrootn1, lenrootn2, lenrootm1, lenrootm2);
	//result
	printf("结果:");
	F_HA_PRINT(rootm1, rootm2, lenrootm1, lenrootm2, 1);

	//pause
	int quit;
	for (quit = 0; quit != 1;)
		scanf("%d", &quit);



	return 0;
}

