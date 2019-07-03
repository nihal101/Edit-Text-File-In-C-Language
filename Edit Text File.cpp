<<<<<<< HEAD
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<conio.h>
# define null 0


struct fileStack* root=null;
struct filePointer* root1=null;
int totalMatchWord=0;
struct fileStack
{
	char fileName[100];
	struct fileStack* next;
};

struct filePointer
{
	long pointer;
	struct filePointer* next;
};

struct fileStack* createfileStackNode()
{
	struct fileStack* obj;
	obj=(struct fileStack*)malloc(sizeof(struct fileStack));
	return obj;
}

struct filePointer* createfilePointerNode()
{
	struct filePointer* obj;
	obj=(struct filePointer*)malloc(sizeof(filePointer));
	return obj;
}

void pushPointer(long pointer1,struct filePointer* obj)
{
	struct filePointer* temp;
	obj->pointer=pointer1;
	obj->next=null;
	if(root1==null)
	{
		root1=obj;
	}else
	{
	   temp=root1;
	   while(temp->next)
	   {
	   	    temp=temp->next;
	   }
	   temp->next=obj;	
	}
}

int findLength(char* string)
{
	int len=0;
	for(int i=0;*(string+i)!='\0';i++)
	{
		len++;
	}
	return len;
}

void push(char* data,struct fileStack* obj)
{
	int len,i;
	struct fileStack* temp;
	len=findLength(data);
	for(i=0;i<len;i++)
	{
		obj->fileName[i]=*(data+i);
	}
	obj->fileName[i]='\0';
	obj->next=null;
	
	if(root==null)
	{
		root=obj;
	}else
	{
		temp=root;
		while(temp->next)
		{
			temp=temp->next;
		}
		temp->next=obj;
	}
}

void popAll()
{
	struct fileStack* temp;
	while(root)
	{
		temp=root;
		root=root->next;
		free(temp);
	}
}

char* pop(int num)
{
	struct fileStack* temp=root;
	for(int i=1;i<num;i++)
	{
		temp=temp->next;
	}
	return (temp->fileName);
}
void printAll()
{
	struct fileStack* temp=root;
	root=root->next;
	free(temp);
	temp=root;
	root=root->next;
	free(temp);
	temp=root;
	int index=1;
	while(temp->next)
	{
		printf("%d  %s\n",index,temp->fileName);
		temp=temp->next;
		index++;
	}
}

void openFile(char* path)
{
	
}
char* createCompletePath(char* fileName,char* path)
{
	int len1,len2,i;
	len1=findLength(fileName);
	len2=findLength(path);
	for(i=0;i<len1;i++)
	{
		*(path+len2+i)=*(fileName+i);
	}
	*(path+len2+i)='\0';
    return path;
}
char* enterChoice(char* path)
{
	int choice;
	char* fileName;
	printf("enter choice\t");
	scanf("%d",&choice);
	fileName=pop(choice);
	popAll();
	path=createCompletePath(fileName,path);
	return path;
}

void fileDescription(FILE* file)
{
	long size;
	int kb=0,mb=0,byte=0;
   fseek(file,0,SEEK_END);
   size=ftell(file);
   byte=size;
   if(size>=1024)
   {
   	    kb=size/1024;
   	    byte=size%1024;
   }if(kb>=1024)
   {
   	    mb=kb/1024;
   	    kb=kb%1024;
   }
    printf("Total Character: %d\n\t\t\t",size);
   	printf("File Size: %d MB  %d  KB  %d B",mb,kb,byte);
}

void checkIsEqual(char* searchWord,char* wordFromFile,FILE* file)
{
	int len1,len2,i,count=0;
	filePointer* obj;
	len1=findLength(searchWord);
	len2=findLength(wordFromFile);
	
		for(i=0;i<len1;i++)
		{
			if(*(searchWord+i)==*(wordFromFile+i))
			{
			    count++;	
			}
		}
		if(count==len1)
		{
		   totalMatchWord++;
		   obj=createfilePointerNode();
		   pushPointer((long)(ftell(file)-len2),obj);		
		}

}

void replaceWord(char* replaceword,FILE* file)
{
	long position;
	int len;
	len=findLength(replaceword);
	rewind(file);
	while(root1)
	{
		position=root1->pointer;
		root1=root1->next;
		fseek(file,position,0);
		//printf("S=%d",SEEK_CUR);
		for(int i=0;i<len;i++)
		{
			putc(*(replaceword+i),file);
		}
		
	}
}

void searchWord(FILE* file)
{
	char searchWord[100];
	char wordFromFile[100];
	char replaceword[100];
	printf("\n\nenter word to be searched\n\n\t\t\t");
	scanf("%s",searchWord);
	
	while(!(feof(file)))
	{
		fscanf(file,"%s",wordFromFile);
		checkIsEqual(searchWord,wordFromFile,file);
	}
	printf("\n\tTotal Match Word:  %d",totalMatchWord);
    if(totalMatchWord==0)
    {
    	exit(0);
	}else
	{
	printf("\n\tenter word to be replaced\t");
	scanf("%s",replaceword);
	replaceWord(replaceword,file);
	}
}
int main()
{
	char path[100];
	char* path1;
    DIR* directory_name;
	struct dirent* dir;	
	FILE* file;
	struct fileStack* obj;
	printf("WARNING: SEARCH WORD AND REPLACE WORD SHOULD BE SAME AND  IN THIS PROGRAM UPPERCASE AND LOWERCASE CONSIDERED\n\n\n");
	printf("enter  path\n\t");
	scanf("%s",path);
	
	directory_name=opendir(path);
	if(directory_name)
	{
	   while((dir=readdir(directory_name))!=NULL)
       {
	   	    obj=createfileStackNode();
	   	    push(dir->d_name,obj);
	   }
	   
	   printAll();
	   path1=enterChoice(path);
	   file=fopen(path,"r+");
	   if(file)
	   {
	   	    printf("File Description:\n\t\t\t");
	   	    fileDescription(file);
	   	    rewind(file);
	   	    searchWord(file);
	   }else
	   {
	   	    printf("unvalid file\n");
	   }
	}else
	{
		file=fopen(path,"r+");
		if(file)
		{
			printf("File Description:\n\t\t\t");
			fileDescription(file);
			rewind(file);
			searchWord(file);
		}else
		{
			printf("unvalid file\n");
		}
	}
	printf("\n\n\tReplace Successfully...");
	getch();	
}
=======
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<conio.h>
# define null 0


struct fileStack* root=null;
struct filePointer* root1=null;
int totalMatchWord=0;
struct fileStack
{
	char fileName[100];
	struct fileStack* next;
};

struct filePointer
{
	long pointer;
	struct filePointer* next;
};

struct fileStack* createfileStackNode()
{
	struct fileStack* obj;
	obj=(struct fileStack*)malloc(sizeof(struct fileStack));
	return obj;
}

struct filePointer* createfilePointerNode()
{
	struct filePointer* obj;
	obj=(struct filePointer*)malloc(sizeof(filePointer));
	return obj;
}

void pushPointer(long pointer1,struct filePointer* obj)
{
	struct filePointer* temp;
	obj->pointer=pointer1;
	obj->next=null;
	if(root1==null)
	{
		root1=obj;
	}else
	{
	   temp=root1;
	   while(temp->next)
	   {
	   	    temp=temp->next;
	   }
	   temp->next=obj;	
	}
}

int findLength(char* string)
{
	int len=0;
	for(int i=0;*(string+i)!='\0';i++)
	{
		len++;
	}
	return len;
}

void push(char* data,struct fileStack* obj)
{
	int len,i;
	struct fileStack* temp;
	len=findLength(data);
	for(i=0;i<len;i++)
	{
		obj->fileName[i]=*(data+i);
	}
	obj->fileName[i]='\0';
	obj->next=null;
	
	if(root==null)
	{
		root=obj;
	}else
	{
		temp=root;
		while(temp->next)
		{
			temp=temp->next;
		}
		temp->next=obj;
	}
}

void popAll()
{
	struct fileStack* temp;
	while(root)
	{
		temp=root;
		root=root->next;
		free(temp);
	}
}

char* pop(int num)
{
	struct fileStack* temp=root;
	for(int i=1;i<num;i++)
	{
		temp=temp->next;
	}
	return (temp->fileName);
}
void printAll()
{
	struct fileStack* temp=root;
	root=root->next;
	free(temp);
	temp=root;
	root=root->next;
	free(temp);
	temp=root;
	int index=1;
	while(temp->next)
	{
		printf("%d  %s\n",index,temp->fileName);
		temp=temp->next;
		index++;
	}
}

void openFile(char* path)
{
	
}
char* createCompletePath(char* fileName,char* path)
{
	int len1,len2,i;
	len1=findLength(fileName);
	len2=findLength(path);
	for(i=0;i<len1;i++)
	{
		*(path+len2+i)=*(fileName+i);
	}
	*(path+len2+i)='\0';
    return path;
}
char* enterChoice(char* path)
{
	int choice;
	char* fileName;
	printf("enter choice\t");
	scanf("%d",&choice);
	fileName=pop(choice);
	popAll();
	path=createCompletePath(fileName,path);
	return path;
}

void fileDescription(FILE* file)
{
	long size;
	int kb=0,mb=0,byte=0;
   fseek(file,0,SEEK_END);
   size=ftell(file);
   byte=size;
   if(size>=1024)
   {
   	    kb=size/1024;
   	    byte=size%1024;
   }if(kb>=1024)
   {
   	    mb=kb/1024;
   	    kb=kb%1024;
   }
    printf("Total Character: %d\n\t\t\t",size);
   	printf("File Size: %d MB  %d  KB  %d B",mb,kb,byte);
}

void checkIsEqual(char* searchWord,char* wordFromFile,FILE* file)
{
	int len1,len2,i,count=0;
	filePointer* obj;
	len1=findLength(searchWord);
	len2=findLength(wordFromFile);
	
		for(i=0;i<len1;i++)
		{
			if(*(searchWord+i)==*(wordFromFile+i))
			{
			    count++;	
			}
		}
		if(count==len1)
		{
		   totalMatchWord++;
		   obj=createfilePointerNode();
		   pushPointer((long)(ftell(file)-len2),obj);		
		}

}

void replaceWord(char* replaceword,FILE* file)
{
	long position;
	int len;
	len=findLength(replaceword);
	rewind(file);
	while(root1)
	{
		position=root1->pointer;
		root1=root1->next;
		fseek(file,position,0);
		//printf("S=%d",SEEK_CUR);
		for(int i=0;i<len;i++)
		{
			putc(*(replaceword+i),file);
		}
		
	}
}

void searchWord(FILE* file)
{
	char searchWord[100];
	char wordFromFile[100];
	char replaceword[100];
	printf("\n\nenter word to be searched\n\n\t\t\t");
	scanf("%s",searchWord);
	
	while(!(feof(file)))
	{
		fscanf(file,"%s",wordFromFile);
		checkIsEqual(searchWord,wordFromFile,file);
	}
	printf("\n\tTotal Match Word:  %d",totalMatchWord);
    if(totalMatchWord==0)
    {
    	exit(0);
	}else
	{
	printf("\n\tenter word to be replaced\t");
	scanf("%s",replaceword);
	replaceWord(replaceword,file);
	}
}
int main()
{
	char path[100];
	char* path1;
    DIR* directory_name;
	struct dirent* dir;	
	FILE* file;
	struct fileStack* obj;
	printf("WARNING: SEARCH WORD AND REPLACE WORD SHOULD BE SAME AND  IN THIS PROGRAM UPPERCASE AND LOWERCASE CONSIDERED\n\n\n");
	printf("enter  path\n\t");
	scanf("%s",path);
	
	directory_name=opendir(path);
	if(directory_name)
	{
	   while((dir=readdir(directory_name))!=NULL)
       {
	   	    obj=createfileStackNode();
	   	    push(dir->d_name,obj);
	   }
	   
	   printAll();
	   path1=enterChoice(path);
	   file=fopen(path,"r+");
	   if(file)
	   {
	   	    printf("File Description:\n\t\t\t");
	   	    fileDescription(file);
	   	    rewind(file);
	   	    searchWord(file);
	   }else
	   {
	   	    printf("unvalid file\n");
	   }
	}else
	{
		file=fopen(path,"r+");
		if(file)
		{
			printf("File Description:\n\t\t\t");
			fileDescription(file);
			rewind(file);
			searchWord(file);
		}else
		{
			printf("unvalid file\n");
		}
	}
	printf("\n\n\tReplace Successfully...");
	getch();	
}
>>>>>>> 785c1be01a576a61643d55518e8b7a2a1c79f214
