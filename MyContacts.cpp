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
	Friend *next;//������һ���α�
}Friend,*lFriend;

typedef struct{

	char number[20];
	char GroupName[20];
	Friend *fd;
	int nFriend;//��¼�����������ϵ�˵ĸ���
}Group;

void InitGroup(Group &myGroup)//��ʼ������
{
	myGroup.nFriend=0;
	myGroup.fd=NULL;
}

void InitFriend(Friend myFriend)//��ʼ���ļ�����ĺ���
{
	strcpy(myFriend.name,"");
	strcpy(myFriend.sex,"");
	strcpy(myFriend.Birthday,"");
	strcpy(myFriend.phonenumber,"");
	strcpy(myFriend.location,"");
	strcpy(myFriend.group,"");
	myFriend.next=NULL;//��֤�˿�ʼʱÿһ��Ԫ�غ���
}

void putInFriend(lFriend &f)//������ϵ��
{
	int length;
	f=(Friend*)malloc(sizeof(Friend));
	if(!f)
	{
		printf("�����ڴ�ʧ��!!!\n");
		exit(-1);
	}
	printf("ÿһ���Ϊ����:\n");
	scanf("%s%s%s%s%s%s",f->name,f->sex,f->Birthday,f->phonenumber,f->location,f->group);
	length=strlen(f->group);
	f->group[length]='\n';
	f->group[length+1]='\0';
	f->next=NULL;
}


Status CreateFList(lFriend &lfriend,Friend friends[],int count)//��һ��Ϊ��
{
	int i;
	Friend *p;
	lfriend=(Friend*)malloc(sizeof(Friend));
	if(!lfriend)return ERROR;

	p=lfriend;
	for(i=1;i<count;i++)//�������б�����
	{
		p->next=&friends[i];
		p=p->next;
	}
	p->next=NULL;
	return OK;
}

void copy(char a[],char b[])//��дcopy����
{
	int length;
	int i=0,j=0;
	length=strlen(a);
	while((b[i++]=a[j++])!='0');
	b[i-1]=b[i];
	
}

void setFriend(lFriend &myFriend,lFriend MyFriend)//copy Friend����
{
	strcpy(myFriend->name,MyFriend->name);
	strcpy(myFriend->sex,MyFriend->sex);
	strcpy(myFriend->Birthday,MyFriend->Birthday);
	strcpy(myFriend->group,MyFriend->group);
	strcpy(myFriend->location,MyFriend->location);
	strcpy(myFriend->phonenumber,MyFriend->phonenumber);
}


Status addFriend(lFriend &lfriend,lFriend myFriend)//�����ϵ��
{
	//���ݲ��������÷�ֹϵͳ�����ʱ����
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

lFriend getFriendName(lFriend lfriend,char name[])//��ȡ����
{
	Friend *p;
	int flag=0;//����Ƿ��ҵ�
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

lFriend getNumber(lFriend fd,char number[])//ͨ��������в�ѯ
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

void updateFriend(lFriend lf,char str[])//�����û�����Ϣ
{
	if(strcmp(str,"����")==0)
	{
		printf("%s-->",lf->name);
		scanf("%s",lf->name);
	}
	else if(strcmp(str,"�Ա�")==0)
	{
		printf("%s-->",lf->sex);
		scanf("%s",lf->sex);
	}
	else if(strcmp(str,"����")==0)
	{
		printf("%s-->",lf->Birthday);
		scanf("%s",lf->Birthday);
	}
	else if(strcmp(str,"�绰")==0)
	{
		printf("%s-->",lf->phonenumber);
		scanf("%s",lf->name);
	}
	else if(strcmp(str,"���ڵ�")==0)
	{
		printf("%s-->",lf->location);
		scanf("%s",lf->location);
	}
	else if(strcmp(str,"����")==0)
	{
		printf("%s-->",lf->group);
		scanf("%s",lf->group);
	}

	if(strcmp(str,"all")==0)
		scanf("%s%s%s%s%s%s",lf->name,lf->sex,lf->Birthday,lf->phonenumber,lf->location,lf->group);
}



void deleteFriend(lFriend &lfriend,char name[],int mcount)
{
	int flag=0;//�ж��ǹ�����ɾ���Ķ���
	Friend *p,*la;
	p=la=lfriend->next;
	while(strcmp(p->name,name)!=0)
	{
		la=p;
		p=p->next;
	}

	if(!p)
		printf("�޸���ϵ��!\n");
	else
	{
		if(p==lfriend->next)//ɾ��Ԫ������λ
		{
			lfriend->next=p->next;
		}
		else if(p->next)//ɾ��Ԫ�����м�
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


	length=strlen(p->name);//�洢����
	for(j=0;j<length;j++)
		a[i++]=p->name[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->sex);//�洢�Ա�
	for(j=0;j<length;j++)
		a[i++]=p->sex[j];
	for(j=0;j<4;j++)
		a[i++]=' ';

	length=strlen(p->Birthday);//��ȡ����
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

		//��ȡ����
	length=strlen(p->group);
	for(j=0;j<length;j++)
		a[i++]=p->group[j];	
	a[i]='\0';

}




Status addGroupFriend(Group &myGroup,lFriend lf)//�ڷ����������ϵ��
{
	Friend *p,*temp=NULL;
	temp=(Friend*)malloc(sizeof(Friend));
	if(!temp)return ERROR;
//	temp=lf;  ������ֱ�Ӹ�ֵ������������Ϊ���߷�����ͬһ���ڴ�
	setFriend(temp,lf);
	p=myGroup.fd;
	if(p==NULL)//���ӵ�һ����ϵ��
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

void CreateGroup(Group group[],int mcount)//��������
{
	if(mcount>10)
		printf("�������!");
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


void getsuitFriend(lFriend lf,char a[],char b[],char c[],int k,Group myGroup[],int mcount)//ɸѡ
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
		printf("�޷�����������ϵ��\n");
	
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

void deleteGroupFriend(Group myGroup[],lFriend lf,int mcount)//ɾ���ڷ��鵱��
{
	lFriend p,current;
	int flag=0;//�ж��Ƿ���Ҫɾ������ϵ��
	int m=lf->group[0]-'0';
	p=current=p=myGroup[m].fd;
	while(strcmp(current->name,lf->name)!=0)
	{
		p=current;
		current=current->next;
	}

	if(!current)
		printf("û�и���ϵ��!\n");
	else
	{
		if(current==myGroup[m].fd)//ɾ���������ڵ�һ��
			myGroup[m].fd=current->next;
		else if(current->next)//�������м�
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

void deleteGroup(Group myGroup[],int m,int mcount)//ֱ��ɾ�����еĺ���
{
	int i;
	Friend *p,*t;
	//��ɾ��ͨѶ¼����ϵ��
	p=myGroup[m].fd;
	while(p!=NULL)
	{
		t=p;
		p=p->next;
	}
	//ɾ������
	for(i=m;i<mcount;i++)
		myGroup[i]=myGroup[i+1];	
}

int selectFriend(char a[],char b[],char c[])
{
	int kind;
	printf("������ɸѡ����:");
	printf("���/�Ա�/��ס��\nע��:0��ʾ��ɸѡ����Ϊ��\n");
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

	char words[10][100];//���ڴ�������ȡ������

	for(int i=0;i<10;i++)
		InitFriend(MyFriend[i]);

	fFriend=fopen("E:\\Study\\���ݽṹ\\���ݽṹ�γ����\\Friend.txt","r");
	if(fFriend==NULL)
	{
		printf("can't not open Friend.txt\n");
		exit(-1);
	}

	count=0;
	while(fgets(words[count],100,fFriend)!=NULL)//һ��һ�еĶ�ȡ
	{

	//	printf("%s",words);
		int i=0,j=0;
		length=strlen(words[count]);
		printf("%s",words[count]);
		j=0;
		while(words[count][i]!=' ')//��ȡ����
		{
			MyFriend[count].name[j++]=words[count][i];
			i++;
		}
		MyFriend[count].name[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//��ȡ�Ա�
		{
			MyFriend[count].sex[j++]=words[count][i];
				i++;
		}
		MyFriend[count].sex[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//��ȡ����
		{
			MyFriend[count].Birthday[j++]=words[count][i];
				i++;
		}
		MyFriend[count].Birthday[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//��ȡ��ַ
		{
			MyFriend[count].phonenumber[j++]=words[count][i];
				i++;
		}
		MyFriend[count].phonenumber[j]='\0';


		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' ')//��ȡ���ڵ�
		{
			MyFriend[count].location[j++]=words[count][i];
				i++;
		}
		MyFriend[count].location[j]='\0';

		while(words[count][i]==' ')
			i++;

		j=0;
		while(words[count][i]!=' '&&i<length)//��ȡ����
		{
			MyFriend[count].group[j++]=words[count][i];
				i++;
		}

		MyFriend[count].group[j]='\0';	
		count++;		
	}
	printf("\n");

	//�Է�����г�ʼ��
	for(i=0;i<10;i++)
		InitGroup(myGroup[i]);

	fGroup=fopen("E:\\Study\\���ݽṹ\\���ݽṹ�γ����\\Group.txt","r");
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

		while(word[mcount][i]!=' ')//��ȡ���
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
	while(p)//����ϵ����ӵ�Ⱥ�鵱��
	{
		i=p->group[0]-'0';
		addGroupFriend(myGroup[i],p);
		p=p->next;
	}
	//��ʾͨѶ¼
	printf("ͨѶ¼:\n");
	char str[5],str2[5],str3[20];
	printf("�˵�:\n");
	printf("1    ��ʾ������ϵ��\n2    ��ʾ���з���\n3    ɸѡ\n");
	printf("4    ��ѯ\n");
	printf("������:");
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
			printf("�Ӳ˵�:\n1     �����ϵ��\n2     ɾ����ϵ��\n");
			printf("3     ��ʾ��ϵ��\n4     ������ϵ��\n5     ɾ������\n6     ��ʾ����\n");
			printf("7     ������ϵ��\n");
			printf("ctrl+z   ������һ��\n");
			while(scanf("%s",str2)!=EOF)
			{
				if(strcmp(str2,"1")==0)
				{
					lFriend lf;
					putInFriend(lf);
					if(!addFriend(lfriend,lf))
						printf("���ʧ��\n");//��ͨѶ¼�����
					else
						count++;
					//�ڷ��������
					int m=lf->group[0]-'0';
					addGroupFriend(myGroup[m],lf);
				}
				else if(strcmp(str2,"2")==0)
				{
					printf("ɾ����ϵ������:");
					scanf("%s",str3);//ͨ������ɾ����ϵ��
					//��ɾ�������е���ϵ��
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
					printf("����Ҫ�޸��˵�����:");
					char name[20];
					scanf("%s",name);
					lFriend lf=getFriendName(lfriend,name);
					printf("����Ҫ�޸ĵ���Ŀ:����/�Ա�/����/�绰/���ڵ�/����/all\n");
					scanf("%s",str3);
					updateFriend(lf,str3);
					updateGroup(myGroup,str3,lf,mcount);				
				}
				else if(strcmp(str2,"5")==0)
				{
					int n;
					printf("������Ҫɾ��������--->%d",&n);
					deleteGroup(myGroup,n,mcount);
				}
				else if(strcmp(str2,"6")==0)
					showGroup(myGroup,mcount);
				
				else if(strcmp(str2,"7")==0)
				{
					char groupname[20];
					printf("�����������:");
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

		else if(strcmp(str,"3")==0)//���в�ѯ
		{
			char group[20],sex[20],location[20];
			int k=selectFriend(group,sex,location);
			getsuitFriend(lfriend,group,sex,location,k,myGroup,mcount);
		}

		else if(strcmp(str,"4")==0)
		{
			char ss[5];
			printf("��ѯ��ʽ\n");
			printf("1     �绰��ѯ\n2     ������ѯ\n");
			scanf("%s",ss);
			if(strcmp(ss,"1")==0)
			{
				char phone[20];
				printf("������绰:");
				scanf("%s",phone);
				lFriend fd=getNumber(lfriend,phone);
				showFriend(fd);

			}
			else if(strcmp(ss,"2")==0)
			{
				char  Named[20];
				printf("������ϵ������:");
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
	ff=fopen("E:\\Study\\���ݽṹ\\���ݽṹ�γ����\\Friend.txt","w+");
	fg=fopen("E:\\Study\\���ݽṹ\\���ݽṹ�γ����\\Group.txt","w+");

	for(i=0;i<count;i++)
		fwrite(a[i],sizeof(char),strlen(a[i]),ff);
	for(i=0;i<mcount;i++)
		fwrite(word[i],sizeof(char),strlen(word[i]),fg);
	return 0;  	
}