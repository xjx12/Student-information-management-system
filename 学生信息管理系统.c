#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Header printf("学号    姓名    年龄    性别    出生年月    电话号码     家庭地址\n")
#define Print printf("%-8d%-8s%-8d%-8s%-10s  %-.0lf  %-20s\n",stu[p].StuNum,stu[p].StuName,stu[p].StuAge,stu[p].Sex,stu[p].BirthDate,stu[p].TeleNum,stu[p].Home)
struct StuSalary
{
	int StuNum;
	char StuName[6];
	int StuAge;
	char Sex[3];
	char BirthDate[10];
	double TeleNum;
	char Home[20];
}stu[100];
int saveflag=0;
//主菜单 

void Menu()
{
		printf("         **********学生信息管理系统**********\n");
		printf("         *              主菜单              *\n");
		printf("         * 1.添加学生信息    2.显示学生信息 *\n");
		printf("         * 3.修改学生信息    4.删除学生信息 *\n");
		printf("         * 5.查找学生信息    6.保存学生信息 *\n");
		printf("         *           7.退出系统             *\n");
		printf("         *********************Ver 1.0 *******\n");
		printf("         --此应用仅供学习娱乐使用，严禁商用--\n");	
		printf("         -------------最终解释权归开发商所有-\n");
}
//打开文件 

int OpenFile(int cnt)
{
	FILE *fp;
	int i=0;
	fp=fopen("D:\\学生信息.dat","ab+");
	if(fp==NULL)
	{
		printf("打开失败！");
		exit(0);
	}
	while(!feof(fp))
	{
		if(fread(&stu[i],sizeof(struct StuSalary),1,fp)==1)
		{
			cnt++;
			i++;
		}
		
	}
	fclose(fp);
	return cnt;
}
//查找信息 

int Locate(int num,int cnt)
{
	int p=-1,i;
	for(i=0;i<cnt;i++)
	{
		if(stu[i].StuNum==num)
		{
			p=i;
			break;
		}
	}
	return p;
}
//添加信息 

int Add(int cnt)
{
	int choice;
	int i,stuNumTemp,j,recordcnt;
	recordcnt=cnt;
	printf("开始添加学生信息...\n");
	for(i=cnt;i<100;i++)
	{
		printf("学生学号：");
		scanf("%d",&stuNumTemp);
		for(j=0;j<i;j++)
		{
			if(stu[j].StuNum==stuNumTemp)
			{
				printf("学生学号重复，请重新输入：");
				scanf("%d",&stuNumTemp);
				j=-1;
			}
		}
		stu[i].StuNum=stuNumTemp;
		getchar();
		printf("学生姓名:");
		scanf("%s",&stu[i].StuName);
		printf("学生年龄："); 
		scanf("%d",&stu[i].StuAge);
		printf("学生性别：");
		scanf("%s",&stu[i].Sex);
		printf("出生年月：");
		scanf("%s",&stu[i].BirthDate) ;
		printf("电话号码:"); 
		scanf("%lf",&stu[i].TeleNum);
		printf("家庭住址：");
		scanf("%s",&stu[i].Home);
		printf("是否继续输入? 1 继续 0 退出：");
		scanf("%d",&choice);
		recordcnt++;
		if(choice!=1)
			break;
	}
	saveflag=1;
	printf("记录输入完成，按enter键返回主菜单...");
	getchar();
	getchar();
	return recordcnt;
}
//显示信息 

void ShowRecord(int cnt)
{
	int i,p;
	if(cnt!=0)
	{
		Header;
		for(i=0;i<cnt;i++)
		{
			p=i;
			Print;
		}
	}
}
//修改信息 

void Modify(int cnt)
{
	int stunum,p,stuNumTemp,j;
	printf("开始修改学生信息...\n\n");
	printf("请输入要修改学生的学号：");
	scanf("%d",&stunum);
	p=Locate(stunum,cnt);
	if(-1==p)
	{
		printf("\n要修改的学生信息不存在，按enter键返回主菜单...");
	}
	else
	{
		printf("要修改的学生信息如下：\n");
		Header;
		Print;
		printf("请重新输入学生信息：\n");
		printf("学生学号：");
		scanf("%d",&stuNumTemp);
		for(j=0;j<cnt;j++)
		{
			if(stu[j].StuNum==stuNumTemp && j!=p)
			{
				printf("学生学号重复，请重新输入：");
				scanf("%d",&stuNumTemp);
				j=-1;
			}
		}
		stu[p].StuNum=stuNumTemp;
		getchar();
		printf("学生姓名；");
		scanf("%s",&stu[p].StuName);
		printf("学生年龄:");
		scanf("%d",&stu[p].StuAge);
		printf("学生性别：");
		scanf("%s",&stu[p].Sex);
		printf("出生年月：");
		scanf("%s",&stu[p].BirthDate) ;
		printf("电话号码:"); 
		scanf("%lf",&stu[p].TeleNum);
		printf("家庭住址：");
		scanf("%s",&stu[p].Home);
		saveflag=1;
		printf("\n学生信息修改成功，按enter键返回主菜单...");
	}
	getchar();
	getchar();
}
//删除信息 

int Del(int cnt)
{
	int stunum,p,i;
	printf("开始删除学生信息...\n\n");
	printf("请输入要删除学生的学号：");
	scanf("%d",&stunum);
	p=Locate(stunum,cnt);
	if(-1==p)
	{
		printf("\n要删除的学生信息不存在，按enter键返回主菜单...");	
	}
	else
	{
		printf("要删除的学生信息如下：\n\n");
		Header;
		Print;
		for(i=p;i<cnt-1;i++)
		{
			stu[i]=stu[i+1];
		}
		cnt--;
		saveflag=1;
		printf("\n学生信息修改成功，按enter键返回主菜单...");
	}
	getchar();
	getchar();
	return cnt;
}
//查询信息 

void Query(int cnt)
{
	int choice=0,stunum,p,count=0,i;
	char stuname[13];
	printf("开始查询学生信息...\n");
	printf("请选择查询方式（1 按学号  2 按姓名）：");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("请输入要查询学生的学号：");
			scanf("%d",&stunum);
			p=Locate(stunum,cnt);
			if(-1==p)
			{
				printf("\n查询的学生信息不存在，按enter键返回主菜单...");
			 } 
			 else
			 {
			 	printf("查询的学生信息如下：\n\n");
			 	Header;
			 	Print;
			 	printf("\n学生信息查询完成，按enter键返回主菜单...");
			 }
			 getchar();
			 break;
		case 2:
			getchar();
			printf("请输入要查询学生的姓名:");
			scanf("%s",&stuname);
			for(i=0;i<cnt;i++)
			{
				if(strcmp(stuname,stu[i].StuName)==0)
				{
					if(count==0)
					{
						Header;
					}
					p=i;
					Print;
					count++;
				}
			}
			if(0==count)
				printf("\n查询的学生信息不存在，按enter键返回主菜单...");
			else
				printf("\n学生信息查询完成，按enter键返回主菜单...");
			break;
		default:
			printf("选择错误，按enter键返回主菜单...");
	}
	getchar();
}
//保存数据 

void SaveFile(int cnt)
{
	FILE *fp;
	int i=0;
	if(1==saveflag)
	{
		fp=fopen("D:\\学生信息.dat","wb");
		for(;i<cnt;i++)
			fwrite(&stu[i],sizeof(struct StuSalary),1,fp);
		fclose(fp);
		saveflag=0;
	}
}
//退出系统 

void ExitSystem(cnt)
{
	int choice=0;
	if(1==saveflag)
	{
		printf("学生信息有变动，是否保存数据？（1 保存退出  2 不保存退出）：");
		scanf("%d",&choice);
		if(1==choice)
		{
			SaveFile(cnt);
			printf("文件保存成功，按enter键返回主菜单...");
		 } 
	}
	else
	{
		printf("按enter键退出系统...");
	}
	getchar();
	getchar();
	exit(0);
}
//主函数 

void main()
{
	int choice=0,count=0;
	count=OpenFile(count);
	while(1)
	{
		system("cls");
		Menu();
		printf("请输入你的选择:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				count=Add(count);
				break;
				case 2:
				if(0==count)
					printf("当前没有学生信息，按enter键返回主菜单...");
				else
				printf("开始显示学生信息...\n\n");
				printf("所有学生信息如下：\n");
				ShowRecord(count);
				printf("\n记录显示完成，按enter键返回主菜单...");
				getchar();
				getchar();
				break;
				case 3:
				Modify(count);
				break;
				case 4:
				count=Del(count);
				break;
				case 5:
				Query(count);
				break;
				case 6:
				SaveFile(count);
				printf("文件保存成功，按enter键返回主菜单...");
				getchar();
				getchar();
				break;
				case 7:
				ExitSystem(count);
			default:
				printf("选择错误，按enter键返回主菜单...");
				getchar();
				getchar();
		}
	}
}
