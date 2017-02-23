#include<iostream>
using namespace std;
#include<string.h>
#define OK 1
#define ERROR 0
#define Status int

typedef struct Friend{

 //   char number[20];
	char name[10];
	char sex[20];
	char Birthday[15];
	char phonenumber[20];
	char location[20];
	char group[10];
	Friend *next;//移向下一个游标
}Friend,*lFriend;

typedef struct{

	char number[20];
	char GroupName[20];
	Friend *fd;
	int nFriend;//记录分组里面的联系人的个数
}Group;

void InitGroup(Group &myGroup)//初始化分组
{
	myGroup.nFriend=0;
	myGroup.fd=NULL;
}

void InitFriend(Friend myFriend)//初始化文件里面的函数
{
	strcpy(myFriend.name,"");
	strcpy(myFriend.sex,"");
	strcpy(myFriend.Birthday,"");
	strcpy(myFriend.phonenumber,"");
	strcpy(myFriend.location,"");
	strcpy(myFriend.group,"");
	myFriend.next=NULL;//保证了开始时每一个元素后面
}

void putInFriend(lFriend &f)//输入联系人
{
	int length;
	f=(Friend*)malloc(sizeof(Friend));
	if(!f)
	{
		printf("申请内存失败!!!\n");
		exit(-1);
	}
	printf("每一项均为必填:\n");
	scanf("%s%s%s%s%s%s",f->name,f->sex,f->Birthday,f->phonenumber,f->location,f->group);
	length=strlen(f->group);
	f->group[length]='\n';
	f->group[length+1]='\0';
	f->next=NULL;
}


Status CreateFList(lFriend &lfriend,Friend friends[],int count)//第一个为空
{
	int i;
	Friend *p;
	lfriend=(Friend*)malloc(sizeof(Friend));
	if(!lfriend)return ERROR;

	p=lfriend;
	for(i=1;i<count;i++)//除掉首列标题行
	{
		p->next=&friends[i];
		p=p->next;
	}
	p->next=NULL;
	return OK;
}

void copy(char a[],char b[])//复写copy函数
{
	int length;
	int i=0,j=0;
	length=strlen(a);
	while((b[i++]=a[j++])!='0');
	b[i-1]=b[i];
	
}

void setFriend(lFriend &myFriend,lFriend MyFriend)//copy Friend对象
{
	strcpy(myFriend->name,MyFriend->name);
	strcpy(myFriend->sex,MyFriend->sex);
	strcpy(myFriend->Birthday,MyFriend->Birthday);
	strcpy(myFriend->group,MyFriend->group);
	strcpy(myFriend->location,MyFriend->location);
	strcpy(myFriend->phonenumber,MyFriend->phonenumber);
}


Status addFriend(lFriend &lfriend,lFriend myFriend)//添加联系人
{
	//传递参数的引用防止系统清除临时变量
	Friend *p;
	p=lfriend;
	while(p->next)
		p=p->next;
	p->next=myFriend;
	return OK;

}

void showFriend(lFriend MyFriend)
{
	printf("%s    %s    %s    %s    %s   %s",MyFriend->name,MyFriend->sex,
		MyFriend->Birthday,MyFriend->phonenumber,MyFriend->location,MyFriend->group);
}



void showFriends(Friend MyFriend[])
{
	for(int m=0;m<6;m++)
		if(m==0)
			printf("%s   %s   %s     %s          %s    %s",MyFriend[m].name,MyFriend[m].sex,MyFriend[m].Birthday,MyFriend[m].phonenumber,MyFriend[m].location,MyFriend[m].group);
		else
			printf("%s    %s    %s    %s    %s   %s",MyFriend[m].name,MyFriend[m].sex,MyFriend[m].Birthday,MyFriend[m].phonenumber,MyFriend[m].location,MyFriend[m].group);

}

lFriend getFriendName(lFriend lfriend,char name[])//获取姓名
{
	Friend *p;
	int flag=0;//标记是否找到
	p=lfriend->next;
	while(p)
	{
		if(strcmp(p->name,name)==0)
		{
			flag=1;
			return p;
		}
		else
			p=p->next;
	}
	return NULL;
	
}

lFriend getNumber(lFriend fd,char number[])//通过号码进行查询
{
	int i;
	int length=strlen(number);
	char partNumber[20];
	Friend *p;
	p=fd->next;
	while(p)
	{
		for(i=0;i<length;i++)
			partNumber[i]=p->phonenumber[i];
		partNumber[length]='\0';
		if(strcmp(partNumber,number)==0)
			return p;
		p=p->next;
	}
	return NULL;
}

void updateFriend(lFriend lf,char str[])//更新用户的信息
{
	if(strcmp(str,"姓名")==0)
	{
		printf("%s-->",lf->name);
		scanf("%s",lf->name);
	}
	else if(strcmp(str,"性别")==0)
	{
		printf("%s-->",lf->sex);
		scanf("%s",lf->sex);
	}
	else if(strcmp(str,"生日")==0)
	{
		printf("%s-->",lf->Birthday);
		scanf("%s",lf->Birthday);
	}
	else if(strcmp(str,"电话")==0)
	{
		printf("%s-->",lf->phonenumber);
		scanf("%s",lf->name);
	}
	else if(strcmp(str,"所在地")==0)
	{
		printf("%s-->",lf->location);
		scanf("%s",lf->location);
	}
	else if(strcmp(str,"分组")==0)
	{
		printf("%s-->",lf->group);
		scanf("%s",lf->group);
	}

	if(strcmp(str,"all")==0)
		scanf("%s%s%s%s%s%s",lf->name,lf->sex,lf->Birthday,lf->phonenumber,lf->location,lf->group);
}



void deleteFriend(lFriend &lfriend,char name[],int mcount)
{
	int flag=0;//判断是够存在删除的对象
	Friend *p,*la;
	p=la=lfriend->next;
	while(strcmp(p->name,name)!=0)
	{
		la=p;
		p=p->next;
	}

	if(!p)
		printf("无该联系人!\n");
	else
	{
		if(p==lfriend->next)//删除元素在首位
		{
			lfriend->next=p->next;
		}
		else if(p->next)//删除元素在中间
		{
			la->next=p->next;
		}
		else
		{
			la->next=p->next;
		}
	}
}

void saveFriend(lFriend p,char a[])
{
	int i,j,length;;
	i=0;


	length=strlen(p->name);//存储姓名
	for(j=0;j<length;j++)
		a[i++]=p->name[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->sex);//存储性别
	for(j=0;j<length;j++)
		a[i++]=p->sex[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->Birthday);//提取生日
	for(j=0;j<length;j++)
		a[i++]=p->Birthday[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->phonenumber);
	for(j=0;j<length;j++)
		a[i++]=p->phonenumber[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->location);
	for(j=0;j<length;j++)
		a[i++]=p->location[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

		//提取分组
	length=strlen(p->group);
	for(j=0;j<length;j++)
		a[i++]=p->group[j];	
	a[i]='\0';

}




Status addGroupFriend(Group &myGroup,lFriend lf)//在分组中添加联系人
{
	Friend *p,*temp=NULL;
	temp=(Friend*)malloc(sizeof(Friend));
	if(!temp)return ERROR;
//	temp=lf;  像这样直接赋值最后编译器还是为两者分配了同一段内存
	setFriend(temp,lf);
	p=myGroup.fd;
	if(p==NULL)//连接第一个联系人
	{
		temp->next=myGroup.fd;
		myGroup.fd=temp;
		myGroup.nFriend++;
	}
	else
	{
		while(p->next!=NULL)
			p=p->next;
		temp->next=p->next;
		p->next=temp;
		myGroup.nFriend++;
	}	
	return OK;
}

void CreateGroup(Group group[],int mcount)//创建分组
{
	if(mcount>10)
		printf("输入错误!");
	else
	{
		scanf("%s%s",group[mcount+1].number,group[mcount+1].GroupName);
	}
}

int getSex(lFriend lf,char sex[])
{
	if(strcmp(lf->sex,sex)==0)
		return OK;

	return ERROR;
}

int getLocation(lFriend lf,char location[])
{
	if(strcmp(lf->location,location)==0)
		return OK;
	return ERROR;
}


Group getGroup(Group myGroup[],char name[],int mcount)
{
	int i;
	char GroupName[20];
	for(i=1;i<mcount;i++)
	{
		strcpy(GroupName,myGroup[i].GroupName);
		int length=strlen(GroupName);
		GroupName[length-1]=GroupName[length];
		if(strcmp(GroupName,name)==0)
			return myGroup[i];
	}
	return myGroup[0];
}


void getsuitFriend(lFriend lf,char a[],char b[],char c[],int k,Group myGroup[],int mcount)//筛选
{
	lFriend p;
	char name[20],test[20]; 
	strcpy(test,b);
	p=lf->next;
	int fn;
	int length;
	int flag=0;
	while(p)
	{
		fn=p->group[0]-'0';
		strcpy(name,myGroup[fn].GroupName);
		
		length=strlen(name);
		name[length-1]=name[length];

		if(k==1)
			if(strcmp(p->sex,b)==0&&strcmp(p->location,c)==0)
			{
				showFriend(p);
				flag=1;
			}
		if(k==2)
			if(strcmp(name,a)==0&&strcmp(p->location,c)==0)
			{
				showFriend(p);
				flag=1;
			}
		if(k==3)
			if(strcmp(name,a)==0&&strcmp(p->sex,b)==0)
			{
				showFriend(p);
				flag=1;
			}
		if(k==4)
			if(strcmp(p->location,c)==0)
			{
				showFriend(p);
				flag=1;
			}
		if(k==5)
			if(strcmp(p->sex,b)==0)
			{
				showFriend(p);
				flag=1;
			}
		if(k==6)
			if(strcmp(name,a)==0)
			{
				showFriend(p);
				flag=1;
			}
	    if(k==7)
			if(strcmp(name,a)==0&&strcmp(p->location,c)==0&&strcmp(p->sex,b))
			{
				showFriend(p);
				flag=1;
			}			
		p=p->next;			
	}
	printf("\n");
	if(!flag)
		printf("无符合条件的联系人\n");
	
}


void SortGroupNumber(Group myGroup[],int mcount)
{
	char a[2];

	for(int i=1;i<mcount;i++)
	{
		a[0]=i+'0';
		a[1]='\0';
		strcpy(myGroup[i].number,a);
	}
}

void deleteGroupFriend(Group myGroup[],lFriend lf,int mcount)//删除在分组当中
{
	lFriend p,current;
	int flag=0;//判断是否有要删除的联系人
	int m=lf->group[0]-'0';
	p=current=p=myGroup[m].fd;
	while(strcmp(current->name,lf->name)!=0)
	{
		p=current;
		current=current->next;
	}

	if(!current)
		printf("没有该联系人!\n");
	else
	{
		if(current==myGroup[m].fd)//删除的数据在第一条
			myGroup[m].fd=current->next;
		else if(current->next)//数据在中间
			p->next=current->next;
		else
			p->next=current->next;
	}

}

void updateGroup(Group myGroup[],char name[],lFriend lf,int mcount)
{
	int i;
	lFriend p;
	for(i=1;i<mcount;i++)
	{
		p=myGroup[i].fd;
		while(p)
		{
			if(strcmp(p->name,name)==0)
				setFriend(p,lf);
			p=p->next;
		}
	}
}

void deleteGroup(Group myGroup[],int m,int mcount)//直接删除所有的函数
{
	int i;
	Friend *p,*t;
	//先删除通讯录中联系人
	p=myGroup[m].fd;
	while(p!=NULL)
	{
		t=p;
		p=p->next;
	}
	//删除分组
	for(i=m;i<mcount;i++)
		myGroup[i]=myGroup[i+1];	
}

int selectFriend(char a[],char b[],char c[])
{
	int kind;
	printf("请输入筛选条件:");
	printf("组别/性别/居住地\n注意:0表示该筛选条件为空\n");
	scanf("%s%s%s",a,b,c);
	if(strcmp(a,"0")==0&&strcmp(b,"0")!=0&&strcmp(c,"0")!=0)
		kind=1;
	else if(strcmp(a,"0")!=0&&strcmp(b,"0")==0&&strcmp(c,"0")!=0)
		kind=2;
	else if(strcmp(a,"0")!=0&&strcmp(b,"0")!=0&&strcmp(c,"0")==0)
		kind=3;
	else if(strcmp(a,"0")==0&&strcmp(b,"0")==0&&strcmp(c,"0")!=0)
		kind=4;
	else if(strcmp(a,"0")==0&&strcmp(b,"0")!=0&&strcmp(c,"0")==0)
		kind=5;
	else if(strcmp(a,"0")!=0&&strcmp(b,"0")==0&&strcmp(c,"0")==0)
		kind=6;
	else 
		kind=7;
	return kind;
}

void saveGroup(Group myGroup,char b[])
{
	int i=0,j;
	int length;
	length=strlen(myGroup.number);
	for(j=0;j<length;j++)
		b[i++]=myGroup.number[j];

	for(j=0;j<7;j++)
		b[i++]=' ';

	length=strlen(myGroup.GroupName);
	for(j=0;j<length;j++)
		b[i++]=myGroup.GroupName[j];
	b[i]='\0';

}

void showGroup(Group myGroup[],int mcount)
{
	int p;
	printf("%s     %s",myGroup[0].number,myGroup[0].GroupName);
	for(p=1;p<mcount;p++)
		printf("%s        %s",myGroup[p].number,myGroup[p].GroupName);
}

int main()
{
	Group myGroup[10];
	Friend MyFriend[10];
	FILE *fFriend,*fGroup;

	int length;
	int count=0,mcount=0;

	char words[10][100];//用于处理所读取的数据

	for(int i=0;i<10;i++)
		InitFriend(MyFriend[i]);

	fFriend=fopen("E:\\Study\\数据结构\\数据结构课程设计\\Friend.txt","r");
	if(fFriend==NULL)
	{
		printf("can't not open Friend.txt\n");
		exit(-1);
	}

	count=0;
	while(fgets(words[count],100,fFriend)!=NULL)//一行一行的读取
	{

	//	printf("%s",words);
		int i=0,j=0;
		length=strlen(words[count]);
		printf("%s",words[count]);
		j=0;
		while(words[count][i]!=' ')//提取姓名
		{
			MyFriend[count].name[j++]=words[count][i];
			i++;
		}
		MyFriend[count].name[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//提取性别
		{
			MyFriend[count].sex[j++]=words[count][i];
				i++;
		}
		MyFriend[count].sex[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//提取生日
		{
			MyFriend[count].Birthday[j++]=words[count][i];
				i++;
		}
		MyFriend[count].Birthday[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//提取地址
		{
			MyFriend[count].phonenumber[j++]=words[count][i];
				i++;
		}
		MyFriend[count].phonenumber[j]='\0';


		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//提取所在地
		{
			MyFriend[count].location[j++]=words[count][i];
				i++;
		}
		MyFriend[count].location[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' '&&i<length)//提取分组
		{
			MyFriend[count].group[j++]=words[count][i];
				i++;
		}

		MyFriend[count].group[j]='\0';	
		count++;		
	}
	printf("\n");

	//对分组进行初始化
	for(i=0;i<10;i++)
		InitGroup(myGroup[i]);

	fGroup=fopen("E:\\Study\\数据结构\\数据结构课程设计\\Group.txt","r");
	if(fGroup==NULL)
	{
		printf("Can't not open Group.txt\n");
		exit(-1);
	}

	char word[10][100];
	mcount=0;
	while(fgets(word[mcount],100,fGroup)!=NULL)
	{
	
		length=strlen(word[mcount]);
		
		int i=0,j=0;

		while(word[mcount][i]!=' ')//获取编号
		{
			myGroup[mcount].number[j++]=word[mcount][i];
			i++;
		}
		myGroup[mcount].number[j]='\0';

		while(word[mcount][i]==' ')
			i++;

		j=0;
		while(word[mcount][i]!=' '&&i<length)
		{
			myGroup[mcount].GroupName[j++]=word[mcount][i];
			i++;
		}

		myGroup[mcount].GroupName[j]='\0';

		mcount++;
	}

	showGroup(myGroup,mcount);
	printf("\n");

	lFriend lfriend,p;
	char groupName[20];
	CreateFList(lfriend,MyFriend,count);
	p=lfriend->next;
	while(p)//将联系人添加到群组当中
	{
		i=p->group[0]-'0';
		addGroupFriend(myGroup[i],p);
		p=p->next;
	}
	//显示通讯录
	printf("通讯录:\n");
	char str[5],str2[5],str3[20];
	printf("菜单:\n");
	printf("1    显示所有联系人\n2    显示所有分组\n3    筛选\n");
	printf("4    查询\n");
	printf("请输入:");
	while(scanf("%s",str)!=EOF)
	{
		if(strcmp(str,"1")==0)
		{
			p=lfriend->next;
			while(p)
			{
				showFriend(p);
				p=p->next;
			}
		}
		else if(strcmp(str,"2")==0)
		{
			showGroup(myGroup,mcount);
			printf("\n");
			printf("子菜单:\n1     添加联系人\n2     删除联系人\n");
			printf("3     显示联系人\n4     更改联系人\n5     删除分组\n6     显示分组\n");
			printf("7     分组联系人\n");
			printf("ctrl+z   返回上一层\n");
			while(scanf("%s",str2)!=EOF)
			{
				if(strcmp(str2,"1")==0)
				{
					lFriend lf;
					putInFriend(lf);
					if(!addFriend(lfriend,lf))
						printf("添加失败\n");//向通讯录中添加
					else
						count++;
					//在分组中添加
					int m=lf->group[0]-'0';
					addGroupFriend(myGroup[m],lf);
				}
				else if(strcmp(str2,"2")==0)
				{
					printf("删除联系人姓名:");
					scanf("%s",str3);//通过姓名删除联系人
					//先删除分组中的联系人
					lFriend lf=getFriendName(lfriend,str3);
					deleteGroupFriend(myGroup,lf,mcount);
					deleteFriend(lfriend,str3,count);
					count--;
										
				}
				else if(strcmp(str2,"3")==0)
				{
					p=lfriend->next;
					while(p)
					{
						showFriend(p);
						p=p->next;
					}
				}
				else if(strcmp(str2,"4")==0)
				{
					printf("输入要修改人的姓名:");
					char name[20];
					scanf("%s",name);
					lFriend lf=getFriendName(lfriend,name);
					printf("输入要修改的项目:姓名/性别/生日/电话/所在地/分组/all\n");
					scanf("%s",str3);
					updateFriend(lf,str3);
					updateGroup(myGroup,str3,lf,mcount);				
				}
				else if(strcmp(str2,"5")==0)
				{
					int n;
					printf("请输入要删除分组编号--->%d",&n);
					deleteGroup(myGroup,n,mcount);
				}
				else if(strcmp(str2,"6")==0)
					showGroup(myGroup,mcount);
				
				else if(strcmp(str2,"7")==0)
				{
					char groupname[20];
					printf("输入分组姓名:");
					scanf("%s",groupname);
					Group gp=getGroup(myGroup,groupname,mcount);
					lFriend p=gp.fd;
					while(p)
					{
						showFriend(p);
						p=p->next;
					}
				}
			}			
		}

		else if(strcmp(str,"3")==0)//进行查询
		{
			char group[20],sex[20],location[20];
			int k=selectFriend(group,sex,location);
			getsuitFriend(lfriend,group,sex,location,k,myGroup,mcount);
		}

		else if(strcmp(str,"4")==0)
		{
			char ss[5];
			printf("查询方式\n");
			printf("1     电话查询\n2     姓名查询\n");
			scanf("%s",ss);
			if(strcmp(ss,"1")==0)
			{
				char phone[20];
				printf("请输入电话:");
				scanf("%s",phone);
				lFriend fd=getNumber(lfriend,phone);
				showFriend(fd);

			}
			else if(strcmp(ss,"2")==0)
			{
				char  Named[20];
				printf("输入联系人姓名:");
				scanf("%s",Named);
				lFriend fd=getFriendName(lfriend,Named);
				showFriend(fd);				
			}
		}
	}
	char a[10][100];
	char b[10][100];
	 i=1;
	 p=lfriend->next;
	 strcpy(a[0],words[0]);
	 strcpy(b[0],word[0]);
	while(p)
	{
		saveFriend(p,a[i++]);
		p=p->next;
	}
	for(i=1;i<mcount;i++)
		saveGroup(myGroup[i],b[i]);	
	fclose(fFriend);
	fclose(fGroup);
	FILE *ff,*fg;
	ff=fopen("E:\\Study\\数据结构\\数据结构课程设计\\Friend.txt","w+");
	fg=fopen("E:\\Study\\数据结构\\数据结构课程设计\\Group.txt","w+");

	for(i=0;i<count;i++)
		fwrite(a[i],sizeof(char),strlen(a[i]),ff);
	for(i=0;i<mcount;i++)
		fwrite(word[i],sizeof(char),strlen(word[i]),fg);
	return 0;  	
}