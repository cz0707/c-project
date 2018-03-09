#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf\n"
#define LEN sizeof(struct student)
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum

typedef struct student {
	int num;               //学号
	char name[15];         //姓名
	double elec;           //选修课
	double expe;           //实验课
	double requ;           //必修课
	double sum;
}student;

student stu[50];
void in();                 //录入学生成绩
void show();               //显示学生信息
void order();              //按总分排序
void del();                //删除学生信息
void modify();             //修改学生成绩
void menu();               //主菜单
void insert();             //插入学生信息
void total();              //计算总人数
void search();             //查找学生信息

void menu() {
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|-----------------STUDENT------------------|\n");
	printf("\t\t|0.exit                                    |\n");
	printf("\t\t|1.input record                            |\n");
	printf("\t\t|2.search record                           |\n");
	printf("\t\t|3.delet record                            |\n");
	printf("\t\t|4.modify record                           |\n");
	printf("\t\t|5.insert record                           |\n");
	printf("\t\t|6.order                                   |\n");
	printf("\t\t|7.number                                  |\n");
	printf("\t\t|8.show                                    |\n");
	printf("\t\t|------------------------------------------|\n\n");
	printf("\t\t\tchoose(0-8):");
}

void in() {
	int i, m = 0;                 //m是记录的条数
	char ch[2];
	FILE *fp;
	if ((fp = fopen("data.txt", "a+")) == NULL) {
		printf("can not open!\n");
		return;
	}
	while (!feof(fp)) {                 //feof是C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0，文件结束符只能被clearerr()清除。
		if (fread(&stu[m], LEN, 1, fp) == 1) {          //若文件指针不在尾部，需要读取文件中的数据
			m++;                                        //fread读取1个元素，每个元素LEN长度，如果读取成功返回count，即1
		}
	}
	fclose(fp);
	if (m == 0)
		printf("No record!");
	else
	{
		system("cls");
		show();
	}
	if ((fp = fopen("data.txt", "wb")) == NULL) {
		printf("can not open!\n");
		return;
	}
	for (i = 0; i < m; i++)
		fwrite(&stu[i], LEN, 1, fp);
	fclose(fp);
	printf("please input(y/n):");
	scanf("%s", ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("number:");
		scanf("%d", &stu[m].num);
		for (i = 0; i < m; i++) {
			if (stu[i].num == stu[m].num) {
				printf("the number is existing,press any to conyinue!");
				getch();
				return;
			}
		}
		printf("name :");
		scanf("%s", stu[m].name);
		printf("elective:");
		scanf("%lf", &stu[m].elec);
		printf("experiment:");
		scanf("%lf", &stu[m].expe);
		printf("required course:");
		scanf("%lf", &stu[m].requ);
		stu[m].sum = stu[m].elec + stu[m].requ + stu[m].expe;
		if ((fp = fopen("data.txt", "a+")) == NULL) {
			printf("can not open!\n");
			return;
		}
		m++;
		//for (i = 0; i < m; i++) {
			if (fwrite(&stu[i], LEN, 1, fp) != 1) {
				printf("can not save!\n");
				getch();
			}
		//}
		printf("%s is sucessfully saved!", stu[m-1].name);
		fclose(fp);
		printf("continue?(y/n):");
		scanf("%s", ch);
	}
	printf("OK!");
}
void show() {
	FILE *fp;
	int i, m = 0;
	if ((fp=fopen("data.txt", "a+")) ==	NULL) {
		printf("can not open!");
		return;
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {          
			m++;                                        
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!");
	}
	else {
		printf("number  name           elective    experiment  required    sum\t\n");
		for (i = 0; i < m; i++)
			printf(FORMAT, DATA);
	}
}
void search() {
	FILE *fp;
	int i, m = 0;
	int num;
	if ((fp = fopen("data.txt", "rb")) == NULL) {
		printf("can not open!");
		return;
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!\n");
		return;
	}
	printf("please input the number you want to search:");
	scanf("%d", &num);
	for (i = 0; i < m; i++) {
		if (num == stu[i].num) {
			printf("number  name           elective    experiment  required    sum\t\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	if (i == m)
		printf("can not find the number!");
	printf("\npress any to continue");
}
void delet() {
	FILE *fp;
	int i, m = 0, num = 0, j = 0;
	char ch[2];
	if ((fp = fopen("data.txt", "r+")) == NULL) {
		printf("can not open!");
		return;
	}
	while(!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!");
		return;
	}
	show();
	printf("Do you want to delet(y/n)?:");
	scanf("%s", ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("Please insert the number you want to delet:");
		scanf("%d", &num);
		for (i = 0; i < m; i++) {
			if (num == stu[i].num) {
				for (j = i; j < m; j++) {
					stu[j] = stu[j + 1];
				}
				break;
			}
		}
		if (i == m) {
			printf("NO THIS NUMBER!");
			return;
		}
		else {
			m--;
		}
		if ((fp = fopen("data.txt", "wb")) == NULL) {
			printf("can not open!");
			return;
		}
		for (i = 0; i < m; i++) {
			if (fwrite(&stu[i], LEN, 1, fp) != 1) {
				printf("fail to save");
				getch();
			}
		}
		fclose(fp);
		printf("operation sucessful!\n");
		show();
		printf("continue to delet?(y/n):");
		scanf("%s", ch);
	}
}
void modify() {
	FILE *fp;
	int i, m = 0;
	int num;
	char ch[2];
	if ((fp = fopen("data.txt", "r+")) == NULL) {
		printf("can not open!\n");
		getch();
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	if (m == 0) {
		printf("No record!\n");
		return;
	}
	system("cls");
	show();
	printf("modify the data?(y/n):");
	scanf("%s", ch);
	if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("Please input number:");
		scanf("%d", &num);
		for (i = 0; i < m; i++) {
			if (num == stu[i].num) {
				printf("find th student!next to modify:\n");
				printf("name :");
				scanf("%s", stu[i].name);
				printf("elective:");
				scanf("%lf", &stu[i].elec);
				printf("experiment:");
				scanf("%lf", &stu[i].expe);
				printf("required course:");
				scanf("%lf", &stu[i].requ);
				stu[i].sum = stu[i].elec + stu[i].requ + stu[i].expe;
				printf("operation sucessfully!");
				break;
			}
		}
		if (i == m) {
			printf("NO THIS RECORD!\n");
			return;
		}
		if ((fp = fopen("data.txt", "wb")) == NULL) {
			printf("can not open!");
			return;
		}
		for (i = 0; i < m; i++) {
			if (fwrite(&stu[i], LEN, 1, fp) != 1) {
				printf("fail to save");
				getch();
			}
		}
		fclose(fp);
		system("cls");
		show();
	}
}
void insert() {
	FILE *fp;
	int m = 0;
	int num,snum;
	int i, j;
	char ch[2];
	if ((fp = fopen("data.txt", "r+")) == NULL) {
		printf("can not open!\n");
		getch();
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!\n");
		return;
	}
	system("cls");
	show();
	printf("insert?(y/n):");
	scanf("%s", ch);
	if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("Please input the number you want to insert behind:");
		scanf("%d", &num);
		for (i = 0; i < m; i++) {
			if (num == stu[i].num) {
				for (j = m; j>i+1; j--) {
					stu[j] = stu[j - 1];
				}
				m++;
				printf("number:");
				scanf("%d", &snum);
				for (j = 0; j < m; j++) {
					if (snum == stu[j].num) {
						printf("the number is existing!press any to conyinue\n");
						getch();
						return;
					}
				}
				stu[i + 1].num = snum;
				printf("name :");
				scanf("%s", stu[i+1].name);
				printf("elective:");
				scanf("%lf", &stu[i + 1].elec);
				printf("experiment:");
				scanf("%lf", &stu[i + 1].expe);
				printf("required course:");
				scanf("%lf", &stu[i + 1].requ);
				stu[i + 1].sum = stu[i + 1].elec + stu[i + 1].requ + stu[i + 1].expe;
				printf("operation sucessful!\n");
				if ((fp = fopen("data.txt", "wb")) == NULL) {
					printf("can not open\n");
					getch();
				}
				for (j = 0; j < m; j++) {
					if (fwrite(&stu[j], LEN, 1, fp) != 1) {
						printf("can not save!\n");
						getch();
					}
				}
				fclose(fp);
				show();
				getch();
				return;
			}
		}
		printf("the number is not existing!\n");
	}
}
void order() {
	FILE *fp;
	int i, j, m = 0;
	student temp;
	if ((fp = fopen("data.txt", "r+")) == NULL) {
		printf("can not open!\n");
		getch();
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!\n");
		return;
	}
	for (i = 0; i < m - 1; i++) {
		for (j = 0; j < m - i - 1; j++) {
			if (stu[j].sum < stu[j + 1].sum) {
				temp = stu[j];
				stu[j] = stu[j + 1];
				stu[j + 1] = temp;
			}
		}
	}
	if ((fp = fopen("data.txt", "wb")) == NULL) {
		printf("can not open\n");
		getch();
	}
	for (j = 0; j < m; j++) {
		if (fwrite(&stu[j], LEN, 1, fp) != 1) {
			printf("can not save!\n");
			getch();
		}
	}
	fclose(fp);
	system("cls");
	show();
}
void total() {
	FILE *fp;
	int i, m = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL) {
		printf("can not open!\n");
		getch();
	}
	while (!feof(fp)) {
		if (fread(&stu[m], LEN, 1, fp) == 1) {
			m++;
		}
	}
	fclose(fp);
	if (m == 0) {
		printf("No record!\n");
		return;
	}
	else {
		printf("the class now have %d students' score record.\n", m);
	}
}
int main() {
	int n;
	menu();
	scanf("%d",&n);
	while (n) {
		switch(n) 
		{
			case 1:
				in();
				break;
			case 2:
				search();
				break;
			case 3:
				delet();
				break;
			case 4:
				modify();
				break;
			case 5:
				insert();
				break;
			case 6:
				order();
				break;
			case 7:
				total();
				break;
			case 8:
				show();
				break;
			defualt:
				break;
		}
		getch();                 //按任意键返回菜单
		menu();
		scanf("%d", &n);
	}
	return 0;
}