#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
struct node *head;
struct node
{
    struct node *prev;
    int points;
    char rid[10];
    char name[20];
    char ownrid[10];
    struct node *next;  
};
int hirarchy=1;
void givetoothers(char *rid)
{
    struct node *p;
    p=head;
    while(p!=NULL)
    {
        if(strcmp(p->ownrid,rid)==0)
        {
            p->points=p->points+(int)(100/hirarchy);
            printf("----name:%s,points:%d\n",p->name,p->points);
            hirarchy=hirarchy+1;
            givetoothers(p->rid);
        }
        p=p->next;
    }
    hirarchy=1;
}
int checkrefer(char *rid)
{
    struct node *p;
    p=head;
    while(p!=NULL)
    {
        if(strcmp(p->ownrid,rid)==0)
        {
            return 1;
        }
        p=p->next;
    }
    return 0;
}
struct node* createnode(char *prid,char *pname)
{
    srand(time(0));
    struct node *temp;
    char createrid[10]="";
    temp=(struct node*)malloc(sizeof(struct node));
    if(prid=="")
    {
        strcpy(temp->rid,"");
        temp->points=0;
    }
    else
    {
        if(checkrefer(prid))
        {
            temp->points=50;
            strcpy(temp->rid,prid);
            givetoothers(prid);
        }
        else
        {
            printf("Wrong_Code\n");
            strcpy(temp->rid,"");
            temp->points=0;
        }
    }
    strcpy(temp->name,pname);
    for(int i=0;i<5;i++)
    {
        createrid[i]=(char)(65+rand()%26);
    }
    //printf("%s",createrid);
    strcpy(temp->ownrid,createrid);
    temp->next=NULL;
    printf("Name:%s\n",temp->name);
    printf("Referral_ID:%s\n",temp->ownrid);
    printf("____________\n");
    return temp;
}
void append()
{
    char name[20],rid[10];
    char choice;
    printf("Name:");
    scanf(" %s",name);
    printf("HaveCode:");
    scanf(" %c",&choice);
    if(choice=='Y')
    {
        printf("Referral_Code:");
        scanf("  %s",rid);
    }
    else
    {
        strcpy(rid,"");
    }
    printf("Creating_your_account...\n");
    if(head==NULL)
    {
        head=createnode(rid,name);
    }
    else
    {
        struct node *p;
        p=head;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=createnode(rid,name);
    }
}
void showpoints(char *name)
{
    struct node *p;
    p=head;
    while(p!=NULL)
    {
        if(strcmp(p->name,name)==0)
        {
            printf("Points:%d\n",p->points);
            return;
        }
        p=p->next;
    }
    printf("Name_not_found\n");
}
void main()
{
    int choice;
    while(1)
    {
        printf("Enter_your_choice\n");
        scanf(" %d",&choice);
        fflush(stdin);
        if(choice==1)
        {
            append();
        }
        else if(choice==2)
        {
            char name[20];
            printf("Enter_Name:\n");
            scanf(" %s",name);
            showpoints(name);
        }
    }
}
