#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30
typedef struct student
{
    char name[10];
    long long id;
    int score[4];
    float aver;
    int sum;
}STUDENT;

STUDENT stu[N+50];
int n,m;                        //nΪѧ������,mΪ��Ŀ����
long long all_id[N];           //��¼����ѧ��ѧ��
int all_score[N+50][4];         //��¼����ѧ���ɼ�
int all_sum[N+50];              //��¼����ѧ���ܳɼ�
float all_aver[N+50];           //��¼����ѧ��ƽ���ɼ�

void InputArray();        //¼������
void Sort(int func);      //��������
void Sorting_func();      //ѡ��ͬ���򷽷�
void Print_all(int func,int number);      //��ӡ�����ĳɼ�����  ����funcΪѡ��ͬ��ӡ����,numberΪ��ӡ��ͬ����,Ĭ��number=-1;
void Delete_id(long long id); //ɾ��ĳһѧ��
void Change_id(long long id); //�޸�ĳһѧ������
void Search();         //���������ѯ�������±����
void Save();    //��������
int main()
{
    //func��ʾ���ù���  flag��������Ƿ�¼������
    int func=0,read_flag=0;
    long long id;
    while(func!=8)
    {
        printf("\
*************�˵�����*************\n\
\t1������¼��\n\
\t2������ɾ��\n\
\t3�������޸�\n\
\t4�����ݲ�ѯ\n\
\t5����������\n\
\t6��������ʾ\n\
\t7�����ݱ���\n\
\t8���˳�\n\
*********************************\n\
\t��ѡ��˵����ܺţ�\n");
        scanf("%d",&func);
        switch(func)
        {
            case 1:  //����¼��
                if(read_flag==1){
                    printf("���Ѿ�¼������ݣ�\n");
                }
                else
                {
                    InputArray();
                    read_flag=1;
                }
                break;
            case 2: //����ɾ��
                if(read_flag==1){
                    printf("����������Ҫɾ����ѧ��:\t");
                    scanf("%lld",&id);
                    Delete_id(id);
                }
                else
                    printf("�㻹û��¼�����ݣ�\n");
                break;
            case 3: //�����޸�
                if(read_flag==1){
                    printf("����������Ҫ�޸ĵ�ѧ��:\t");
                    scanf("%lld",&id);
                    Change_id(id);
                }
                else
                    printf("�㻹û��¼�����ݣ�\n");
                break;
            case 4:   //���ݲ�ѯ
                if(read_flag==1){
                    Search();
                }
                else{
                    printf("�㻹û��¼�����ݣ�\n");
                }
                break;
            case 5:  //��������
                if(read_flag==1){
                    Sorting_func();
                }
                else{
                    printf("�㻹û��¼�����ݣ�\n");
                }
                break;
            case 6: //������ʾ
                if(read_flag==1){
                //��ӡ��Ϣ
                    Sort(5);
                    Print_all(6,-1);
                }
                else{
                    printf("�㻹û��¼�����ݣ�\n");
                }
                break;
            case 7: //���ݱ���
                Save();
                break;
        }

    }

    return 0;
}

//����������
void swap(int *a,int *b)
{
    int t;
    t=*a;
    *a=*b;
    *b=t;
}

void swap1(float *a,float *b)
{
    float t;
    t=*a;
    *a=*b;
    *b=t;
}

void swap2(long long *a,long long *b)
{
    long long t;
    t=*a;
    *a=*b;
    *b=t;
}

void InputArray()
{
    int i,j;
    FILE *fp;
    fp=fopen("score.txt","r");
    if(fp==NULL)
    {
        printf("�ļ���ȡʧ��\n");
        exit(0);
    }
    fscanf(fp,"%d%d",&n,&m);
    for(i=0;i<n;i++){
        fscanf(fp,"%s%lld",stu[i].name,&stu[i].id);
        all_id[i]=stu[i].id;
        for(j=0;j<m;j++){
            fscanf(fp,"%d",&stu[i].score[j]);
            all_score[i][j]=stu[i].score[j];
        }
        fscanf(fp,"%f",&stu[i].aver);
        fscanf(fp,"%d",&stu[i].sum);
        all_aver[i]=stu[i].aver;
        all_sum[i]=stu[i].sum;
    }
    fclose(fp);
    printf("����¼��ɹ�!\n");
    printf("\n");
}

void Print_all(int func,int number)
{
    int count=0;
    switch(func)
    {
        case 1:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][0]>number){
                        printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, ��ѧ[MT]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][0]);
                    }
                }
            }
            break;
        case 2:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][1]>number){
                        printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, Ӣ��[EN]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][1]);
                    }
                }
            }
            break;
        case 3:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][2]>number){
                        printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, ����[PH]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][2]);
                    }
                }
            }
            break;
        case 4:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][3]>number){
                        printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, ����[CH]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][3]);
                    }
                }
            }
            break;
        case 5:
            if(number<0){
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        if(all_id[i]==stu[j].id){
                            printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, �ܷ�:%d\n",
                            all_id[i],stu[j].name,i+1,all_sum[i]);
                        }
                    }
                }
            }
            else{
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        if(all_id[i]==stu[j].id&&all_aver[i]>number){
                            printf("ѧ��:%lld,����:%-8s,  ����Ϊ:%2d, ƽ����:%.2f\n",
                            all_id[i],stu[j].name,i+1,all_aver[i]);
                        }
                    }
                }
            }
            break;
        case 6:
            printf("\n");
            printf("����	   ѧ��     ����  ��ѧ[MT]  Ӣ��[EN]  ����[PH]  ����[CH]  �ܷ�   ƽ����\n");
            for(int i=0;i<n;i++){
                if(all_id[i]!=NULL){
                    count++;
                    for(int j=0;j<n;j++){
                        if(all_id[i]==stu[j].id){
                            printf("%-6s	   %-8lld   %2d    %3d      %3d      %3d       %3d       %3d     %.2f\n",stu[j].name,
                            all_id[i],count,all_score[i][0],all_score[i][1],all_score[i][2],all_score[i][3],all_sum[i],all_aver[i]);
                        }
                    }
                }
            }
            break;
        default:
            printf("û�д˹���!\n");
    }
    printf("*************************************************************\n\n");
}

void Sort(int func)
{
    if(func==1||func==2||func==3||func==4){
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i-1;j++){
                if(all_score[j][func-1]<all_score[j+1][func-1])
                {
                    swap2(&all_id[j],&all_id[j+1]);
                    swap(&all_score[j][0],&all_score[j+1][0]);
                    swap(&all_score[j][1],&all_score[j+1][1]);
                    swap(&all_score[j][2],&all_score[j+1][2]);
                    swap(&all_sum[j],&all_sum[j+1]);
                    swap1(&all_aver[j],&all_aver[j+1]);
                }
            }
        }
    }
    else if(func==5){
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i-1;j++){
                if(all_sum[j]<all_sum[j+1])
                {
                    swap2(&all_id[j],&all_id[j+1]);
                    swap(&all_score[j][0],&all_score[j+1][0]);
                    swap(&all_score[j][1],&all_score[j+1][1]);
                    swap(&all_score[j][2],&all_score[j+1][2]);
                    swap(&all_sum[j],&all_sum[j+1]);
                    swap1(&all_aver[j],&all_aver[j+1]);
                }
            }
        }
    }
}

void Sorting_func()
{
    int func;
    printf("\
***********����������***********\n\
\t1��������ѧ[MT]�ɼ�����\n\
\t2������Ӣ��[EN]�ɼ�����\n\
\t3����������[PH]�ɼ�����\n\
\t4����������[CH]�ɼ�����\n\
\t5�������ܳɼ�����\n\
\t��ѡ��˵�����\n\
");
    scanf("%d",&func);
    printf("\n");
    Sort(func);
    Print_all(func,-1);
}

void Delete_id(long long id)
{
    int delete_flag=0;
    for(int i=0;i<n;i++){
        if(all_id[i]==id){
            all_id[i]=NULL;
            delete_flag=1;
            n--;
        }
    }
    if(delete_flag==1){
        printf("ѧ��Ϊ%lld������ɾ���ɹ�!\n",id);
    }
    else
        printf("������ѧ��Ϊ%lld������\n",id);
}

void Change_id(long long id)
{
    int change_flag=0;
    int mt,en,ph,ch,sum;
    float aver;
    for(int i=0;i<n;i++){
        if(all_id[i]==id){
            printf("�������µ�����\n");
            printf("��ѧ[MT]  Ӣ��[EN]  ����[PH]  ����[CH]\n");
            scanf("%d%d%d%d",&mt,&en,&ph,&ch);
            sum=mt+en+ph+ch;
            aver=sum/4;
            all_score[i][0]=mt;
            all_score[i][1]=en;
            all_score[i][2]=ph;
            all_score[i][3]=ch;
            all_sum[i]=sum;
            all_aver[i]=aver;
            change_flag=1;
        }
    }
    if(change_flag==1){
        printf("ѧ��Ϊ%lld�������޸ĳɹ�!\n",id);
    }
    else
        printf("������ѧ��Ϊ%lld������\n",id);

}

void Search()
{
    int func,find_flag=0;     //����Ƿ��ҵ���Ӧѧ�ŵ�ѧ��
    long long find_id;
    int number;
    printf("\
***********���ݲ�ѯ����***********\n\
\t1��������ѧ[MT]�ɼ�����number��ѯ\n\
\t2������Ӣ��[EN]�ɼ�����number��ѯ\n\
\t3����������[PH]�ɼ�����number��ѯ\n\
\t4����������[CH]�ɼ�����number��ѯ\n\
\t5������ƽ���ִ���number��ѯ\n\
\t6�����������ѧ��find_id��ѯ\n\
\t��ѡ��˵�����\n\
");
    scanf("%d",&func);
    if(func<=5&&func>=1){
        printf("������number��ֵ: ");
        scanf("%d",&number);
        Sort(func);
        Print_all(func,number);
    }
    else if(func==6){
        printf("������Ҫ��ѯ��ѧ����ѧ��: ");
        scanf("%lld",&find_id);
        for(int i=0;i<N;i++){
            if(find_id==all_id[i]){
                printf("����	   ѧ��      ��ѧ[MT]  Ӣ��[EN]  ����[PH]  ����[CH]  �ܷ�   ƽ����\n");
                printf("%-6s	   %-8lld    %3d      %3d      %3d       %3d       %3d     %.2f\n",stu[i].name,
                            all_id[i],all_score[i][0],all_score[i][1],all_score[i][2],all_score[i][3],all_sum[i],all_aver[i]);
                find_flag=1;
            }
        }
        if(find_flag==0){
            printf("û��ѧ��Ϊ%lld����Ϣ!\n",find_id);
        }
    }
}

void Save()
{
    FILE *fp;
    fp=fopen("score.txt","w");
    if(fp==NULL)
    {
        printf("�ļ���ȡʧ��\n");
        exit(0);
    }
    fprintf(fp,"%d\t%d\n",n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(all_id[i]==stu[j].id){
                fprintf(fp,"%s\t%-10lld%-15d%-15d%-15d%-15d%-12.2f%-12d\n",
                        stu[j].name,all_id[i],all_score[i][0],all_score[i][1],
                        all_score[i][2],all_score[i][3],all_aver[i],all_sum[i]);
            }
        }
    }
    fclose(fp);
    printf("���ݱ���ɹ�!\n");
    printf("\n");
}













