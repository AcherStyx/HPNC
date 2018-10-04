#include <stdio.h>
#include "Function_HA.h"
#include <math.h>
#include <stdlib.h>

int main(void)
{
	char a1[10] = { 0,0,9,8,0,0,0,8,0,0 };
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

	free(mali1);
	free(mali2);
	free(mal1);
	free(mal2);

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

	free(mal21);
	free(mal22);

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
	char rootm2[100];
	int lenrootm2 = 100;
	printf("需要开平方的数:");
	F_HA_PRINT(rootn1, rootn2, lenrootn1, lenrootn2, 1);
	//conculate
	F_HA_ROOT(rootn1, rootn2, rootm1, rootm2, lenrootn1, lenrootn2, lenrootm1, lenrootm2);
	//result
	printf("结果:");
	F_HA_PRINT(rootm1, rootm2, lenrootm1, lenrootm2, 1);

	//float test
	printf("【Float】\n");
	float flo = 133.567;
	printf("原float类型数值：%f\n", flo);
	int floget1;
	int floget2;
	int floget;
	int floget3;
	float volum = 100;
	floget1 = flo / volum;
	printf("中间值1：%d\n", floget1);
	floget2 = (flo / volum) / 10;
	printf("中间值2：%d\n", floget2);
	floget = floget1 - floget2 * 10;
	printf("分解得到的值：%d\n", floget);

	//muf test
	printf("【乘法B】\n");
	flo = 2.2;
	char floc1[10];
	char floc2[10];
	F_HA_MUB(a1, a2, flo, floc1, floc2, 10, 10, 10, 10);
	F_HA_PRINT(floc1, floc2, 10, 10, 1);

	//malloc size test
	char *mallocs;
	mallocs = (char*)malloc(sizeof(char) * 2);
	mallocs[0] = 1;
	mallocs[1] = 2;
	free(mallocs);

	//division test
	printf("【除法】\n");
	char divi1[2] = { 5,1 };
	char divi2[2] = { 9,7 };
	char div1[10];
	char div2[10];
	printf("a=");
	F_HA_PRINT(a1, a2, lena1, lena2, 1);
	printf("b=");
	F_HA_PRINT(divi1, divi2, 2, 2, 1);
	printf("a/b=");
	F_HA_ZEROD(div1, div2, 10, 10);
	F_HA_DIV(a1, a2, divi1, divi2, div1, div2, 10, 10, 2, 2, 10, 10);
	F_HA_PRINT(div1, div2, 10, 10, 1);

	//divef test
	printf("【除法AB】\n");
	float a = 3.21;
	char divf1[5] = { 1,5,6,0,0 };
	char divf2[5] = { 5,4,8,0,0 };
	char divr1[10];
	char divr2[10];
	F_HA_ZEROD(divr1, divr2, 10, 10);
	F_HA_DIVA(a, divf1, divf2, divr1, divr2, 5, 5, 10, 10);
	F_HA_PRINT(divr1, divr2, 10, 10, 1);

	printf("【除法C】\n");
	float diva = 25.1;
	float divb = 2.2;
	char divr21[50];
	char divr22[100];
	F_HA_DIVC(diva, divb, divr21, divr22, 50, 100);
	F_HA_PRINT(divr21, divr22, 50, 100, 1);

	printf("【乘法C】\n");
	double muca = 1.2;
	double mucb = 5.2;
	char mucc1[10];
	char mucc2[10];
	F_HA_MUC(muca, mucb, mucc1, mucc2, 10, 10);
	F_HA_PRINT(mucc1, mucc2, 10, 10, 1);

	printf("【浮点数转化测试】\n");//error here
	double ftrans = 1.1;
	char ftra1[3];
	char ftra2[3];
	F_HA_TRANS(ftrans, ftra1, ftra2, 3, 3);
	F_HA_PRINT(ftra1, ftra2, 3, 3, 1);

	printf("【次方测试】\n");
	char po1[3] = { 9,0,0 };
	char po2[10] = { 2 };
	char poo1[3];
	char poo2[10];
	F_HA_POWN(po1, po2, 3, 10, poo1, poo2, 3, 10, 3);
	F_HA_PRINT(poo1, poo2, 3, 10, 1);

	printf("【求和一个浮点数最接近的分数】\n");
	char tocom1[3] = { 9,1,0 };
	char tocom2[10] = { 3,1,9 };
	int toout[2];
	F_HA_FTOFR(tocom1, tocom2, 3, 10, toout);
	printf("输入的数为:");
	F_HA_PRINT(tocom1, tocom2, 3, 10, 1);
	printf("得到的分数为:%d/%d\n", toout[0], toout[1]);

	printf("【开方测试】\n");


	/*
	//pi
	printf("【圆周率】\n");
	int pcount;
	//n
	char pn1[10] = { 6,0,0,0,0,0,0,0,0,0 };
	int lenpn1 = 10;
	char pn2[1] = { 0 };
	int lenpn2 = 1;
	char pn21[10];
	int lenpn21 = 10;
	char pn22[1];
	int lenpn22 = 1;
	//x
	char px1[1] = { 1 };
	int lenpx1 = 1;
	char px2[1000];
	int lenpx2 = 1000;
	char px21[1];
	int lenpx21 = 1;
	char px22[1000];
	int lenpx22 = 1000;
	char px31[1];
	int lenpx31 = 1;
	char px32[1000];
	int lenpx32 = 1000;
	//h
	char ph1[1];
	int lenph1 = 1;
	char ph2[1000];
	int lenph2 = 1000;
	char ph21[1];
	int lenph21 = 1;
	char ph22[1000];
	int lenph22 = 1000;
	char ph31[1];
	int lenph31 = 1;
	char ph32[1];
	int lenph32 = 1;
	//s
	char ps1[1];
	int lenps1 = 1;
	char ps2[1000];
	int lenps2 = 1000;
	char ps21[1];
	int lenps21 = 1;
	char ps22[1000];
	int lenps22 = 1000;
	char ps31[1];
	int lenps31 = 1;
	char ps32[1000];
	int lenps32 = 1000;
	//2
	char p21[1] = { 2 };
	int lenp21 = 1;
	char p22[1];
	int lenp22 = 1;
	//0.5
	char p51[1] = { 0 };
	int lenp51 = 1;
	char p52[1] = { 5 };
	int lenp52 = 1;
	//1
	char p11[1] = { 1 };
	int lenp11 = 1;
	char p12[1] = { 0 };
	int lenp12 = 1;

	for (pcount = 1; count < 10; count++)
	{
		F_HA_DIV(px1, px2, p21, p22, px21, px22, lenpx1, lenpx2, lenp21, lenp22, lenpx21, lenpx22);
		F_HA_MU(px21, px22, px21, px22, px31, px32, lenpx21, lenpx22, lenpx21, lenpx22, lenpx31, lenpx32);
		F_HA_M(p11, p12, px31, px32, ph21, ph22, lenp11, lenp12, lenpx31, lenpx32, lenph1, lenph2);
		F_HA_ROOT(ph21, ph22, ph1, ph2, lenph21, lenph22, lenph1, lenph2);

		F_HA_DIV(px1, px2, p21, p22, px21, px22, lenpx1, lenpx2, lenp21, lenp22, lenpx21, lenpx22);
		F_HA_M(p11, p12, ph1, ph2, ph21, ph22, lenp11, lenp12, lenph1, lenph2, lenph21, lenph22);
		F_HA_P(px21, px22, ph21, ph22, px31, px32, lenpx21, lenpx22, lenph21, lenph22, lenpx31, lenpx32);
		F_HA_ROOT(px31, px32, px1, px2, lenpx31, lenpx32, lenpx1, lenpx2);
		
		F_HA_MU(pn1, pn2, p21, p22, pn21, pn22, lenpn1, lenpn2, lenp21, lenp22, lenpn21, lenpn22);
		F_HA_MOVE(pn21, pn22, pn1, pn2, lenpn21, lenpn22, lenpn1, lenpn2);
	}

	F_HA_DIV(px1, px2, p21, p22, px21, px22, lenpx1, lenpx2, lenp21, lenp22, lenpx21, lenpx22);
	F_HA_MU(px21, px22, px21, px22, px31, px32, lenpx21, lenpx22, lenpx21, lenpx22, lenpx31, lenpx32);
	F_HA_M(p11, p12, px31, px32, ph21, ph22, lenp11, lenp12, lenpx31, lenpx32, lenph1, lenph2);
	F_HA_ROOT(ph21, ph22, ph1, ph2, lenph21, lenph22, lenph1, lenph2);

	F_HA_MU(pn1, pn2, px1, px2, ps21, ps22, lenpn1, lenpn2, lenpx1, lenpx2, lenps21, lenps22);
	F_HA_MU(ph1, ph2, p51, p52, ps31, ps32, lenph1, lenph2, lenp51, lenp52, lenps31, lenps32);
	F_HA_MU(ps21, ps22, ps31, ps32, ps1, ps2, lenps21, lenps22, lenps31, lenps32, lenps1, lenps2);
	F_HA_PRINT(ps1, ps2, lenps1, lenps2, 1);
	*/

	/*
	printf("【圆周率】\n");
	double pi1 = 1.0000000;
	int zhengfu = -1;
	char pia1[10];
	char pia2[1000];
	char pis1[10];
	char pis2[1000];
	double picount = 0;
	char pib1[10];
	char pib2[1000];
	F_HA_ZEROD(pib1, pib2, 10, 1000);
	F_HA_ZEROD(pia1, pia2, 10, 1000);

	for (picount = 1.0000000; picount < 999; picount += 2)
	{
		zhengfu *= -1.000000;
		F_HA_DIVC(pi1, picount, pis1, pis2, 10, 1000);
		if (zhengfu > 0)
			F_HA_P(pia1, pia2, pis1, pis2, pib1, pib2, 10, 1000, 10, 1000, 10, 1000);
		else
			F_HA_M(pia1, pia2, pis1, pis2, pib1, pib2, 10, 1000, 10, 1000, 10, 1000);

		F_HA_MOVE(pib1, pib2, pia1, pia2, 10, 1000, 10, 1000);

	}
	float pi4 = 4.0;
	F_HA_MUF(pia1, pia2, pi4, pib1, pib2, 10, 1000, 10, 1000);
	F_HA_PRINT(pib1, pib2, 10, 1000, 1);
	*/

	//====================================================================================================

	/*
	F_HA_BAR('*', 60, 1);

	printf("【最终测试】（录入测试用AB值）\n");
	char ta1[100];
	char ta2[100];
	char tb1[100];
	char tb2[100];
	char tc1[100];
	char tc2[100];
	int lenta1 = 100;
	int lenta2 = 100;
	int lentb1 = 100;
	int lentb2 = 100;
	int lentc1 = 100;
	int lentc2 = 100;
	printf("A:\n");
	F_HA_INPUT(ta1, ta2, lenta1, lenta2);
	printf("B:\n");
	F_HA_INPUT(tb1, tb2, lentb1, lentb2);

	printf("【加法最终调试】\n");
	printf("C:\n");
	F_HA_P(ta1, ta2, tb1, tb2, tc1, tc2, lenta1, lenta2, lentb1, lentb2, lentc1, lentc2);
	F_HA_PRINTC(tc1, tc2, lentc1, lentc2, 1);

	printf("【乘法最终调试】\n");
	printf("C:\n");
	F_HA_MU(ta1, ta2, tb1, tb2, tc1, tc2, lenta1, lenta2, lentb1, lentb2, lentc1, lentc2);
	F_HA_PRINTC(tc1, tc2, lentc1, lentc2, 1);

	printf("【除法最终测试】\n");
	printf("C:\n");
	F_HA_DIV(ta1, ta2, tb1, tb2, tc1, tc2, lenta1, lenta2, lentb1, lentb2, lentc1, lentc2);
	F_HA_PRINTC(tc1, tc2, lentc1, lentc2, 1);

	printf("【减法最终测试】\n");
	printf("C:\n");
	F_HA_M(ta1, ta2, tb1, tb2, tc1, tc2, lenta1, lenta2, lentb1, lentb2, lentc1, lentc2);
	F_HA_PRINTC(tc1, tc2, lentc1, lentc2, 1);
	*/

	//====================================================================================================

	printf("【表达式识别】\n");
	


	//pause
	int quit;
	for (quit = 0; quit != 1;)
		scanf("%d", &quit);



	return 0;
}

