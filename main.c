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
int n,m;                        //n为学生人数,m为科目数量
long long all_id[N+50]={0};           //记录所有学生学号
int all_score[N+50][4]={{0,0,0,0}};         //记录所有学生成绩
int all_sum[N+50]={0};              //记录所有学生总成绩
float all_aver[N+50]={0};           //记录所有学生平均成绩
int del_count=0;                    //记录删除数据个数

void InputArray();        //录入数据
void Sort(int func);      //进行排序
void Sorting_func();      //选择不同排序方法
void Print_all(int func,int number);      //打印排序后的成绩名单  参数func为选择不同打印功能,number为打印不同数据,默认number=-1;
void Delete_id(long long id); //删除某一学号
void Add_id();  //增加某一学号
void Change_id(long long id); //修改某一学号数据
void Search();         //返回满足查询条件的下标个数
void Save();    //保存数据
int main()
{
    //func表示对用功能  flag用来标记是否录入数据
    int func=0,read_flag=0;
    long long id;
    while(func!=8)
    {
        printf("\
*************菜单功能*************\n\
\t1、数据录入\n\
\t2、数据删除\n\
\t3、数据修改\n\
\t4、数据查询\n\
\t5、数据排序\n\
\t6、数据显示\n\
\t7、数据保存\n\
\t8、退出\n\
*********************************\n\
\t请选择菜单功能号：\n");
        scanf("%d",&func);
        switch(func)
        {
            case 1:  //数据录入
                if(read_flag==1){
                    Add_id();
                }
                else
                {
                    InputArray();
                    read_flag=1;
                    printf("如果还想要录入新的数据，请输入1\n");
                    printf("如果录入完毕,请按照菜单对应数字选择其他功能\n");
                    printf("\n");
                }
                break;
            case 2: //数据删除
                if(read_flag==1){
                    printf("请输入你想要删除的学号:\t");
                    scanf("%lld",&id);
                    Delete_id(id);
                }
                else
                    printf("你还没有录入数据！\n");
                break;
            case 3: //数据修改
                if(read_flag==1){
                    printf("请输入你想要修改的学号:\t");
                    scanf("%lld",&id);
                    Change_id(id);
                }
                else
                    printf("你还没有录入数据！\n");
                break;
            case 4:   //数据查询
                if(read_flag==1){
                    Search();
                }
                else{
                    printf("你还没有录入数据！\n");
                }
                break;
            case 5:  //数据排序
                if(read_flag==1){
                    Sorting_func();
                }
                else{
                    printf("你还没有录入数据！\n");
                }
                break;
            case 6: //数据显示
                if(read_flag==1){
                //打印信息
                    Sort(5);
                    Print_all(6,-1);
                }
                else{
                    printf("你还没有录入数据！\n");
                }
                break;
            case 7: //数据保存
                Save();
                break;
        }

    }

    return 0;
}

//交换两个数
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
        printf("文件读取失败\n");
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
    printf("初始数据录入成功!\n");;
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
                        printf("学号:%lld,姓名:%-8s,  排名为:%2d, 数学[MT]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][0]);
                    }
                }
            }
            break;
        case 2:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][1]>number){
                        printf("学号:%lld,姓名:%-8s,  排名为:%2d, 英语[EN]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][1]);
                    }
                }
            }
            break;
        case 3:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][2]>number){
                        printf("学号:%lld,姓名:%-8s,  排名为:%2d, 物理[PH]:%d\n",
                        all_id[i],stu[j].name,i+1,all_score[i][2]);
                    }
                }
            }
            break;
        case 4:
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(all_id[i]==stu[j].id&&all_score[i][3]>number){
                        printf("学号:%lld,姓名:%-8s,  排名为:%2d, 语文[CH]:%d\n",
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
                            printf("学号:%lld,姓名:%-8s,  排名为:%2d, 总分:%d\n",
                            all_id[i],stu[j].name,i+1,all_sum[i]);
                        }
                    }
                }
            }
            else{
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        if(all_id[i]==stu[j].id&&all_aver[i]>number){
                            printf("学号:%lld,姓名:%-8s,  排名为:%2d, 平均分:%.2f\n",
                            all_id[i],stu[j].name,i+1,all_aver[i]);
                        }
                    }
                }
            }
            break;
        case 6:
            printf("\n");
            printf("姓名	   学号     排名  数学[MT]  英语[EN]  物理[PH]  语文[CH]  总分   平均分\n");
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
            printf("没有此功能!\n");
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
***********数据排序功能***********\n\
\t1、按照数学[MT]成绩排序\n\
\t2、按照英语[EN]成绩排序\n\
\t3、按照物理[PH]成绩排序\n\
\t4、按照语文[CH]成绩排序\n\
\t5、按照总成绩排序\n\
\t请选择菜单功能\n\
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
            del_count++;
        }
    }
    if(delete_flag==1){
        printf("学号为%lld的数据删除成功!\n",id);
    }
    else
        printf("不存在学号为%lld的数据\n",id);
}

void Add_id()
{
    printf("姓名	   学号      数学[MT]  英语[EN]  物理[PH]  语文[CH]  \n");
    scanf("%s%lld%d%d%d%d",stu[n].name,&all_id[n],
            &all_score[n][0],&all_score[n][1],&all_score[n][2],&all_score[n][3]);
    all_sum[n]=all_score[n][0]+all_score[n][1]+all_score[n][2]+all_score[n][3];
    all_aver[n]=all_sum[n]/4;
    stu[n].id=all_id[n];
    stu[n].score[0]=all_score[n][0];
    stu[n].score[1]=all_score[n][1];
    stu[n].score[2]=all_score[n][2];
    stu[n].score[3]=all_score[n][3];
    stu[n].aver=all_aver[n];
    stu[n].sum=all_sum[n];
    n++;
    printf("如果还想要录入新的数据，请输入1\n");
    printf("如果录入完毕,请按照菜单对应数字选择其他功能\n");
    printf("\n\n");
}
void Change_id(long long id)
{
    int change_flag=0;
    int mt,en,ph,ch,sum;
    float aver;
    for(int i=0;i<n;i++){
        if(all_id[i]==id){
            printf("请输入新的数据\n");
            printf("数学[MT]  英语[EN]  物理[PH]  语文[CH]\n");
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
        printf("学号为%lld的数据修改成功!\n",id);
    }
    else
        printf("不存在学号为%lld的数据\n",id);

}

void Search()
{
    int func,find_flag=0;     //标记是否找到对应学号的学生
    long long find_id;
    int number;
    printf("\
***********数据查询功能***********\n\
\t1、按照数学[MT]成绩大于number查询\n\
\t2、按照英语[EN]成绩大于number查询\n\
\t3、按照物理[PH]成绩大于number查询\n\
\t4、按照语文[CH]成绩大于number查询\n\
\t5、按照平均分大于number查询\n\
\t6、按照输入的学号find_id查询\n\
\t请选择菜单功能\n\
");
    scanf("%d",&func);
    if(func<=5&&func>=1){
        printf("请输入number的值: ");
        scanf("%d",&number);
        Sort(func);
        Print_all(func,number);
    }
    else if(func==6){
        printf("请输入要查询的学生的学号: ");
        scanf("%lld",&find_id);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(find_id==all_id[i]&&find_id==stu[j].id){
                    printf("姓名	   学号      数学[MT]  英语[EN]  物理[PH]  语文[CH]  总分   平均分\n");
                    printf("%-6s	   %-8lld    %3d      %3d      %3d       %3d       %3d     %.2f\n",stu[j].name,
                                all_id[i],all_score[i][0],all_score[i][1],all_score[i][2],all_score[i][3],all_sum[i],all_aver[i]);
                    find_flag=1;
                }
            }
        }
        if(find_flag==0){
            printf("没有学号为%lld的信息!\n",find_id);
        }
    }
}

void Save()
{
    FILE *fp;
    fp=fopen("score.txt","w");
    if(fp==NULL)
    {
        printf("文件读取失败\n");
        exit(0);
    }
    fprintf(fp,"%d\t%d\n",n-del_count,m);
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
    printf("数据保存成功!\n");
    printf("\n");
}













