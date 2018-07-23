#include <stdio.h>
#include "Function_HA.h"

int main(void)
{
	char a1[10] = {1,2,5,6,9,5,0,0,0,0};
	char a2[10] = {7,4,2,1,5,0,0,0,0,0};
	char b1[5] = {1,8,5,6,4};
	char b2[5] = {8,1,2,6,4};
	char c1[7] = {0,0,0,0,0,0,0};
	char c2[3] = {0,0,0};
	int error=0;

	short lena1 = sizeof(a1) / sizeof(a1[0]);
	short lena2 = sizeof(a2) / sizeof(a2[0]);
	short lenb1 = sizeof(b1) / sizeof(b1[0]);
	short lenb2 = sizeof(b2) / sizeof(b2[0]);
	short lenc1 = sizeof(c1) / sizeof(c1[0]);
	short lenc2 = sizeof(c2) / sizeof(c2[0]);

	short count;


	//开始计算
	error += F_HA_P(a1, a2, b1, b2, c1, c2, lena1, lena2, lenb1, lenb2, lenc1, lenc2);

	//plus test
	printf("[TEST1]:\n");
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
	printf("[TEST2]:\n");
	int compare;
	compare = F_HA_COMP(a1, a2, b1, b2, 10, 10, 5, 5);
	if (compare == 0)
		printf("a>b");
	if (compare == 1)
		printf("a<b");
	if (compare == 2)
		printf("a=b");
	printf("\n");
	
	//manage test
	printf("[TEST3]:\n");
	char manage1[5] = { 4,15,18,16,2 };
	char manage2[5] = { 9,12,16,18,14 };
	F_HA_MA(manage1, manage2, 5, 5);
	F_HA_PRINT(manage1, manage2, 5, 5, 1);
	
	//accumulate test
	printf("[TEST4]:\n");
	unsigned long long acccount;
	char accumulate1[5] = { 0,0,0,0,0 };
	char accumulate2[5] = { 0,0,0,0,0 };
	for (acccount = 0; acccount < 9999998; acccount++)
		F_HA_ACC(accumulate1, accumulate2, 5, 5);
	F_HA_PRINT(accumulate1, accumulate2, 5, 5, 1);

	//char test
	printf("[TEST5]:\n");
	char fushu = 0;
	fushu -= 5;
	printf("%d\n", fushu);

	//minus test
	printf("[TEST6]:\n");
	char minuse1[7] = { 0,0,0,0,0,0,0 };
	char minuse2[4] = { 0,0,0,0 };
	F_HA_M(a1, a2, b1, b2, minuse1, minuse2, 10, 10, 5, 5, 7, 4);
	F_HA_PRINT(minuse1, minuse2, 7, 4, 1);

	//% test
	F_HA_TEST(7);
	int bfs=-11;
	int houmiande=10;
	printf("%d\n", bfs%houmiande);

	//manage test
	F_HA_TEST(8);
	char managep1[10] = { 1,65,23,48,25,48,20,15,26,1 };
	char managep2[5] = { 5,20,46,23,15 };
	F_HA_MAP(managep1, managep2, 10, 5);
	F_HA_PRINT(managep1, managep2, 10, 5, 1);

	//multiplication test
	printf("[TEST9]\n");
	char mult1[7] = { 0,0,0,0,0,0,0 };
	char mult2[5] = { 0,0,0,0 };
	F_HA_MU(a1, a2, b1, b2, mult1, mult2, 10, 10, 5, 5, 7, 5);
	F_HA_PRINT(mult1, mult2, 7, 5, 1);

	//pause
	int quit;
	for (quit = 0; quit != 1;)
		scanf("%d", &quit);



	return 0;
}

