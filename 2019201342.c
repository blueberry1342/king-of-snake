#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//本代码对应的学号为2019201342
//仓促完成，代码质量不高，仅供参考 


//Cell结构体，储存行row，列col，分数score，权重weight
struct Cell{
    int row;
    int col;
    int value;
    int score;
    int weight;
};

int max(int a, int b, int c){
    if(a>b&&a>c)
        return a;
    else if(b>c)
        return b;
    else
        return c;
}


//求两个Cell之间的“距离”，即所要走的最小格子数
int getdistance(struct Cell c1, struct Cell c2){
    return abs(c1.row-c2.row)+abs(c1.col-c2.col);
}



//判断一个格子的数值是否是脖子
int judgeifBozi(int value)
{
    if(value >= 19213420 && value <=  19213429){return 1;}
    if(value >=  192134210 && value <=  192134299){return 1;}
	return 0;
} 

//判断是否为自己的身体
int judgeifBody(int value){
    if(value ==1921342)
        return 1;
    else
        return 0;
}

//判断当前拥有多少道具
int judgeDaojuNums(int value)
{
    if(value >=  19213420 && value <=  19213429){return value % 10;}
    if(value >=  192134210 && value <=  192134299){return value-192134200;}
}

//判断一个格子的数值是否是头
int judgeifHead(int value)
{
    if(value >= 93420 && value <= 93423){return 1;}
    int negvalue = -value;
    if(negvalue >= 934200 && negvalue <= 934202){return 1;}
    if(negvalue >= 934210 && negvalue <= 934212){return 1;}
    if(negvalue >= 934220 && negvalue <= 934222){return 1;}
    if(negvalue >= 934230 && negvalue <= 934232){return 1;}
    return 0;
}

//判断是否是敌人
int judgeifEnemy(int value){
    if(value>=10000||value<=-100000)
        if(judgeifBody(value)==0&&judgeifBozi(value)==0&&judgeifHead(value)==0)
            return 1;
    return 0;
}

//判断是否是敌人头部
int judgeifEnemyhead(int value){
    if((value>=10000&&value<100000&&(!judgeifHead(value)))||(value>-1000000&&value<=-100000&&(!judgeifHead(value))))
        return 1;
    else
        return 0;
}

//判断是否为敌人尾巴
int judgeifTail(struct Cell c1, struct Cell* xcells){
    if(judgeifEnemy(c1.value)==1&&c1.value>=100000){
        int nbodies=0;
        if(judgeifEnemy(xcells[c1.row*40+c1.col+1].value)==1)
            nbodies++;
        if(judgeifEnemy(xcells[c1.row*40+c1.col-1].value)==1)
            nbodies++;
        if(judgeifEnemy(xcells[(c1.row-1)*40+c1.col].value)==1)
            nbodies++;
        if(judgeifEnemy(xcells[(c1.row+1)*40+c1.col].value)==1)
            nbodies++;
        if(nbodies==1)
            return 1;
    }
    return 0;
}

//判断是否在尾巴附近
int judgeifaroundTail(struct Cell c1, struct Cell* xcells){
        if(judgeifTail(xcells[c1.row*40+c1.col+1],xcells)==1)
            return 1;
        if(judgeifTail(xcells[c1.row*40+c1.col-1],xcells)==1)
            return 1;
        if(judgeifTail(xcells[(c1.row+1)*40+c1.col],xcells)==1)
            return 1;
        if(judgeifTail(xcells[(c1.row-1)*40+c1.col],xcells)==1)
            return 1;
        else
            return 0;
}

//打分函数1，评估weight权重
int caculateweight(struct Cell c1,struct Cell head){
    int distance=getdistance(c1,head);
    switch(distance){
    case 1: return 1024000;
    case 2: return 2048;
    case 3: return 320;
    case 4: return 240;
    case 5: return 200;
    case 6: return 160;
    case 7: return 140;
    case 8: return 120;
    case 9: return  100;
    case 10: return 100;
    case 11: return 90;
    case 12: return 80;
    case 13: return 70;
    case 14: return 6;
    case 15: return 6;
    case 16: return 4;
    case 17: return 4;
    case 18: return 4;
    case 19: return 4;
    case 20: return 3;
    case 21: return 3;
    case 22: return 3;
    case 23: return 2;
    case 24: return 1;
    }
    return 0;
}

//打分函数2，评估score分数
int caculatescore(struct Cell c1, int daojvamount){
    if(judgeifHead(c1.value)==1||judgeifBody(c1.value)==1||judgeifBozi(c1.value)==1)
        return 0;
    switch(c1.value){
    case 0:return 0;
    case -1: return 100;
    case -2: return 200;
    case -3: return 300;
    case -5: return 500;
    case -100: return 50;
    case -10000: if(daojvamount==0) return 10000; else if(daojvamount==1) return 1000;
        else if(daojvamount==2) return 500;
        else if(daojvamount<5) return 200; else return 0;
    }

    if(c1.value>0&&c1.value<=200)
        return c1.value*5000;
    else if(daojvamount<=4){
        if(c1.value>=10000&&c1.value<100000){
            if(daojvamount<=1)
                return -1000;
            else
                return (daojvamount-5)*2;
        }
        else{
            if(daojvamount==0)
                return -200;
            else if(daojvamount==1)
                return -20;
            else
                return daojvamount-5;
        }
    }
    else
        return -1;
}


//求分值函数
int getscore(int xdes, int xrow, int xcol, struct Cell* xcells, int times){

    if(xrow<0||xrow>29||xcol<0||xcol>39)
        return 0;
    else if(times==0){
        if(xcells[xrow*40+xcol].score>=0)
            return xcells[xrow*40+xcol].score;
        else return 0;
    }
    else {
        struct Cell newcells[1200];
        for(int i=0; i<1200; i++){
            newcells[i]=xcells[i];
        }

        if(xcells[xrow*40+xcol].score<0)
            return 0;
        else {
            int myscore=newcells[xrow*40+xcol].score;
            newcells[xrow*40+xcol].score=0;
            if(xdes==0)
                return myscore+0.6*max(getscore(3,xrow+1,xcol,newcells,times-1),getscore(0,xrow,xcol-1,newcells,times-1),getscore(1,xrow-1,xcol,newcells,times-1));
            else if(xdes==1)
                return myscore+0.6*max(getscore(0,xrow,xcol-1,newcells,times-1),getscore(1,xrow-1,xcol,newcells,times-1),getscore(2,xrow,xcol+1,newcells,times-1));
            else if(xdes==2)
                return myscore+0.6*max(getscore(1,xrow-1,xcol,newcells,times-1),getscore(2,xrow,xcol+1,newcells,times-1),getscore(3,xrow+1,xcol,newcells,times-1));
            else
                return myscore+0.6*max(getscore(2,xrow,xcol+1,newcells,times-1),getscore(3,xrow+1,xcol,newcells,times-1),getscore(0,xrow,xcol-1,newcells,times-1));
        }
    }
}


int judge(int * map)
{
    //把1200个value存入Cell，并找到头位置，脖子位置，方向，道具数 ，敌人数。
    struct Cell cells[1200],myhead={-1,-1,-1,-1,-1},mybozi={-1,-1,-1,-1,-1},enemyheads[30];
    int des = 0, daoju_nums = 0,nenemies=0,isprotected=0;

    //存入cells的行、列、数值和分数
    for(int xrow=0; xrow<30 ;xrow++){
        for(int xcol=0; xcol<40; xcol++){

            cells[40*xrow+xcol].row=xrow;
            cells[40*xrow+xcol].col=xcol;
            cells[40*xrow+xcol].value=map[40*xrow+xcol];

            //判断头和方向
            if(judgeifHead(map[40*xrow+xcol])==1){
                myhead=cells[40*xrow+xcol];
                if(myhead.value > 0){
                    des = myhead.value -93420;
                }
                else{
                    des = (-myhead.value) /10%10;
                    if((-myhead.value)%10!=0){
                        isprotected=1;
                    }
                }
            }

            //判断脖子和道具数
            if(judgeifBozi(map[40*xrow+xcol])){
                mybozi=cells[40*xrow+xcol];
                daoju_nums = judgeDaojuNums(mybozi.value);
            }
        }
    }

    //存入cells的权重
    for(int xrow=0; xrow<30 ;xrow++){
        for(int xcol=0; xcol<40; xcol++){
            cells[40*xrow+xcol].score=caculatescore(cells[40*xrow+xcol],daoju_nums);
            cells[40*xrow+xcol].weight=caculateweight(cells[40*xrow+xcol],myhead);
        }
    }

    //判断是否为敌人蛇头
    for(int i=0; i<1200; i++){
        if(cells[i].value>=10000&&cells[i].value<100000&&(!judgeifHead(cells[i].value)))
        {
            enemyheads[nenemies]=cells[i];
            nenemies++;
        }
        else if(cells[i].value>-1000000&&cells[i].value<=-100000&&(!judgeifHead(cells[i].value))){
            enemyheads[nenemies]=cells[i];
            nenemies++;
        }
    }


    //若距敌人蛇头小于安全距离，开扇
    for(int i=0; i<nenemies; i++){
        if(getdistance(enemyheads[i],myhead)<=2&&daoju_nums>0&&isprotected==0)
            return 4;
    }



    //使用排除法，记录哪些方向不能走。包括有其它蛇的情况
    int cannotgo[4] = {0,0,0,0};
    if(isprotected==0){
        if ((myhead.row == 0) || des == 3 ||cells[(myhead.row-1)*40+myhead.col].score<0||judgeifaroundTail(cells[(myhead.row-1)*40+myhead.col],cells)==1 ){cannotgo[1] = 1;  }//有墙，或此时正往下走，则不能往上走
        if((myhead.row == 29 ) || des == 1 ||cells[(myhead.row+1)*40+myhead.col].score<0||judgeifaroundTail(cells[(myhead.row+1)*40+myhead.col],cells)==1 ) {cannotgo[3] = 1; }//有墙，或此时正往上走，则不能往下走
        if ((myhead.col == 0) || des == 2 ||cells[myhead.row*40+myhead.col-1].score<0||judgeifaroundTail(cells[myhead.row*40+myhead.col-1],cells)==1 )  {cannotgo[0] = 1; }//有墙，或此时正往右走，则不能往左走
        if((myhead.col==39 ) ||des == 0 ||cells[myhead.row*40+myhead.col+1].score<0||judgeifaroundTail(cells[myhead.row*40+myhead.col+1],cells)==1 )  {cannotgo[2] = 1; } //有墙，或此时正往左走 ，不能往右走
    }
    else{
        if ((myhead.row == 0) || des == 3 ||judgeifEnemyhead(cells[(myhead.row-1)*40+myhead.col].value)==1 ){cannotgo[1] = 1;  }//有墙，或此时正往下走，则不能往上走
        if((myhead.row == 29 ) || des == 1 ||judgeifEnemyhead(cells[(myhead.row+1)*40+myhead.col].value)==1 ) {cannotgo[3] = 1; }//有墙，或此时正往上走，则不能往下走
        if ((myhead.col == 0) || des == 2 ||judgeifEnemyhead(cells[myhead.row*40+myhead.col-1].value)==1 )  {cannotgo[0] = 1; }//有墙，或此时正往右走，则不能往左走
        if((myhead.col==39 ) ||des == 0 ||judgeifEnemyhead(cells[myhead.row*40+myhead.col+1].value)==1 )  {cannotgo[2] = 1; } //有墙，或此时正往左走 ，不能往右走
    }


    //先用十步策略
    int detective[4];
    switch(des){
    case 0: detective[0]=getscore(0,myhead.row,myhead.col-1,cells,9);
          detective[1]=getscore(1,myhead.row-1,myhead.col,cells,9);
          detective[2]=0;
          detective[3]=getscore(3,myhead.row+1,myhead.col,cells,9);
        break;
    case 1: detective[0]=getscore(0,myhead.row,myhead.col-1,cells,9);
          detective[1]=getscore(1,myhead.row-1,myhead.col,cells,9);
          detective[2]=getscore(2,myhead.row,myhead.col+1,cells,9);
          detective[3]=0;
        break;
    case 2: detective[0]=0;
          detective[1]=getscore(1,myhead.row-1,myhead.col,cells,9);
          detective[2]=getscore(2,myhead.row,myhead.col+1,cells,9);
          detective[3]=getscore(3,myhead.row+1,myhead.col,cells,9);
        break;
    case 3: detective[0]=getscore(0,myhead.row,myhead.col-1,cells,9);
          detective[1]=0;
          detective[2]=getscore(2,myhead.row,myhead.col+1,cells,9);
          detective[3]=getscore(3,myhead.row+1,myhead.col,cells,9);
    }


    //比较出十步策略中最大值，若可行则输出该方向
    int direction[4]={0,1,2,3};
    for(int i=0; i<3; i++){
        for(int j=i+1;j<4;j++){
            if(detective[j]>detective[i]){
                int t=detective[i];
                detective[i]=detective[j];
                detective[j]=t;
                t=direction[i];
                direction[i]=direction[j];
                direction[j]=t;
            }
        }
    }
    for(int i=0; i<4 ;i++){
        if(!cannotgo[direction[i]]&&detective[i]>39)
            return direction[i];
    }


    //十步策略不可行时，采用评估分数策略，计算4个方向的评估分数
    int evascore[4]={0};

    for(int i=0;i<1200;i++){
        if(cells[i].col<myhead.col)
            evascore[0]=evascore[0]+cells[i].score*cells[i].weight;
        if(cells[i].row<myhead.row)
            evascore[1]=evascore[1]+cells[i].score*cells[i].weight;
        if(cells[i].col>myhead.col)
            evascore[2]=evascore[2]+cells[i].score*cells[i].weight;
        if(cells[i].row>myhead.row)
            evascore[3]=evascore[3]+cells[i].score*cells[i].weight;
    }



    //决定输出
    int nlegal=0, legaldirection[4];
    for(int i=0; i<4 ; i++){
        if(cannotgo[i]==0){
             legaldirection[nlegal]=i;
             nlegal++;
        }
    }

    //printf("%d %d\n", des, myhead.col);

    //所有方向均不可行，开盾
    if(nlegal==0){
        if(daoju_nums>0)
            return 4;
        else
            return des;
    }
    for(int i=0;i<nlegal;i++)
    {
        int ismax=1;
        for(int j=0;j<nlegal;j++){
            if(evascore[legaldirection[i]]<evascore[legaldirection[j]])
                ismax=0;
        }
        if(ismax==1)
            return legaldirection[i];
    }


}

int main()
{
    int a[1200]; //存储地图


    for(int i = 0; i<1200; i++){
        scanf("%d",&a[i]); //读入地图      
    }


    int des = judge(a); //你的算法，最终输出一个方向des
    printf("%d", des);
    return 0;
}
