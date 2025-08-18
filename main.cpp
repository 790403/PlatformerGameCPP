#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<thread>
#include<chrono>
#include<profileapi.h>
using namespace std;
#define kd(K)GetAsyncKeyState(K)
int wz[10];
int x,y,cm,jh,sc,xd,xl=90,countt=1,xxx,yyy,zcount,ht,nm,a,gxl=100,ms,zco,zl=10,zzl;
bool ij=0,tc;
void cl(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
/*  1   深蓝色
    2   深绿色
    3   深青色
    4   深红色
    5   深粉色
    6   黄色
    7   深白色
    8   灰色
    9   浅蓝色
    10  浅绿色
    11  浅青色
    12  浅红色
    13  浅粉色
    14  浅黄色
    15  浅白色
*/
}
inline void cle(){
    const HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole==INVALID_HANDLE_VALUE)return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(!GetConsoleScreenBufferInfo(hConsole,&csbi))return;
    const DWORD dwSize=csbi.dwSize.X*csbi.dwSize.Y;
    DWORD dwWritten;
    FillConsoleOutputCharacterA(hConsole,' ',dwSize,{0,0},&dwWritten);
    SetConsoleCursorPosition(hConsole,{0,0});
}
void hc(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole,&cursorInfo);
    cursorInfo.bVisible=FALSE;
    SetConsoleCursorInfo(hConsole,&cursorInfo);
}
void ss(string s,int vv){
    int i,l=s.size();
    for(i=0;i<l;i++){
        cout<<s[i];
        Sleep(vv);
    }
    Sleep(vv);
    cout<<endl;
}
int dt[20][40];
void randd(){
    for(int j=0;j<40;j++){
        dt[0][j]=1;
        dt[19][j]=1;
    }
    for(int i=1;i<19;i++){
        for(int j=0;j<40;j++){
            dt[i][j]=0;
        }
    }
    int pd=rand()%2+2;
    for(int i=1;i<19;i+=pd){
        int stc=rand()%10+5;
        int l=rand()%11+5;
        int ec=stc+l;
        if(ec>=40)ec=39;
        for(int j=stc;j<=ec;j++){
            dt[i][j]=1;
        }
        if(i+1<19){
            int sS=ec+rand()%6+5;
            if(sS>=40)sS=35;
            int sl=rand()%8+3;
            int se=sS+sl;
            if(se>=40)se=39;
            for(int j=sS;j<=se;j++){
                dt[i+1][j]=1;
            }
        }
    }
    int fc=rand()%3+4;
    for(int k=0;k<fc;k++){
        int row=rand()%10+5;
        int col=rand()%30+5;
        int len=rand()%5+2;
        for(int j=col;j<col+len&&j<40;j++){
            dt[row][j]=1;
        }
    }
    int scc=rand()%10+20;
    for(int k=0;k<scc;k++){
        int row,col;
        do{
            row=rand()%18+1;
            col=rand()%40;
        }while(dt[row][col]==1||(dt[row+1][col]!=1&&row+1<19));
        dt[row][col]=2;
    }
    int nn=rand()%2+1;
    for(int i=0;i<nn;i++){
        int xx=rand()%20;
        int yy=rand()%40;
        while(dt[xx][yy]){
            xx=rand()%20;
            yy=rand()%40;
        }
        dt[xx][yy]=4;
    }
    nn=rand()%2+3;
    for(int i=0;i<nn;i++){
        int xx=rand()%20;
        int yy=rand()%40;
        while(dt[xx][yy]||dt[xx+1][yy]!=1){
            xx=rand()%20;
            yy=rand()%40;
        }
        dt[xx][yy]=5;
    }
    nn=rand()%2;
    for(int i=0;i<nn;i++){
        int xx=rand()%20;
        int yy=rand()%40;
        while(dt[xx][yy]||dt[xx+1][yy]!=1){
            xx=rand()%20;
            yy=rand()%40;
        }
        dt[xx][yy]=6;
    }
}
void print(){
    static std::string buffer;
    static WORD colorAttrs[256];
    buffer.clear();
    for(int i=19;i>=0;i--){
        for(int j=39;j>=0;j--){
            if(dt[i][j]==4){
                if(dt[i+1][j]==1){
                    if(dt[i][j-1]!=4&&dt[i][j-1]==0){dt[i][j-1]=4;j--;}
                    if(dt[i][j+1]!=4&&dt[i][j+1]==0)dt[i][j+1]=4;
                }else if(dt[i+1][j]!=4&&dt[i+1][j]==0)dt[i+1][j]=4;
            }
        }
    }
    int pos=0;
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            if(j==x&&i==y){
                buffer+=xd?'_':'|';
                colorAttrs[pos++]=xd?1:(!ht?1:4);
            }else if(j==xxx&&i==yyy&&gxl>0&&!nm&&!cm){
                buffer+='M';
                colorAttrs[pos++]=2;
            }else{
                switch(dt[i][j]){
                    case 1:buffer+='=';colorAttrs[pos++]=4;break;
                    case 2:buffer+='*';colorAttrs[pos++]=6;break;
                    case 3:buffer+='#';colorAttrs[pos++]=1;break;
                    case 4:buffer+='+';colorAttrs[pos++]=1;break;
                    case 5:buffer+='x';colorAttrs[pos++]=2;break;
                    case 6:buffer+='$';colorAttrs[pos++]=14;break;
                    default:buffer+=' ';colorAttrs[pos++]=7;
                }
            }
            if(dt[i][j]==2&&j==x&&i==y){
                dt[i][j]=0;
                sc++;
                xl+=10;
                int xx=rand()%40,yy=rand()%20;
                while(dt[yy][xx]!=0){
                    xx=rand()%40;yy=rand()%20;
                }
                dt[yy][xx]=2;
            }
        }
        buffer+='\n';
        colorAttrs[pos++]=7;
    }
    buffer+="得分:"+to_string(sc)+'\n';
    for(int i=0;i<5+to_string(sc).size();i++)colorAttrs[pos++]=2;
    buffer+="血量:";
    for(int i=0;i<6;i++)colorAttrs[pos++]=4;
    for(int i=0;i<10;i++){
        buffer+=(xl<=i*10)?'-':'=';
        colorAttrs[pos++]=4;
    }
    buffer+='\n';
    colorAttrs[pos++]=7;
    buffer+="M的血量:";
    for(int i=0;i<9;i++)colorAttrs[pos++]=4;
    for(int i=0;i<10;i++){
        buffer+=(gxl<=i*10)?'-':'=';
        colorAttrs[pos++]=4;
    }
    buffer+='\n';
    colorAttrs[pos++]=7;
    buffer+="帧率:"+to_string(1000.0/zzl)+'\n';
    for(int i=0;i<5+to_string(1000.0/zzl).length();i++)colorAttrs[pos++]=4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
    int lon=0;
    for(int i=0;i<=6;i++)buffer+=to_string(wz[i])+' ',lon+=1+to_string(wz[i]).size();
    for(int i=0;i<lon;i++)colorAttrs[pos++]=4;
    for(size_t i=0;i<buffer.length();i++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorAttrs[i]);
        DWORD charsWritten;
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),&buffer[i],1,&charsWritten,NULL);
    }
}
inline long long mms(){
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}
bool move(){
    if(gxl<=0&&dt[yyy][xxx]==5)yyy=rand()%20,xxx=rand()%40;
    if(!(zcount%5))gxl++;
    if(dt[yyy][xxx]==5)gxl-=20;
    if(cm)ht=0,xl=100;
    if(sc==countt*10&&a==1){
        countt++;
        return 1;
    }
    zcount++;
    if(zcount%2&&!nm&&!cm&&gxl>0){
        if(x>xxx)xxx++;
        if(x<xxx)xxx--;
        if(y>yyy)yyy++;
        if(y<yyy)yyy--;
    }
    if(zcount%2)xl++;
    if(!(zcount%4)&&dt[y][x]==4)xl-=3;
    if(x==xxx&&y==yyy&&!cm&&!nm&&!xd&&gxl>0)xl-=5,ht=1;
    if(xl>=100)xl=100;
    if(gxl>=100)gxl=100;
    if(xl<=0){
        cle();
        ss("你死了",100);
        Sleep(1000);
        return 1;
    }
    if(dt[y][x]==5)xl-=10,ht=1;
    else if(!(x==xxx&&y==yyy&&!cm&&!nm&&!xd&&gxl>0))ht=0;
    return 0;
}
bool read(){
    if(kd('0')&&cm)dt[y][x]=0;
    if(kd('1')&&cm)dt[y][x]=1;
    if(kd('2')&&cm)dt[y][x]=2;
    if(kd('3')&&cm)dt[y][x]=3;
    if(kd('4')&&cm)dt[y][x]=4;
    if(kd('5')&&cm)dt[y][x]=5;
    if(kd('6')&&cm)dt[y][x]=6;

    if(kd('0')&&!cm&&wz[0]&&dt[y+1][x]!=0)dt[y+1][x]=0,wz[0]--;
    if(kd('1')&&!cm&&wz[1]&&dt[y][x]!=1)dt[y][x]=1,wz[1]--;
    if(kd('2')&&!cm&&wz[2]&&dt[y][x]!=2)dt[y][x]=2,wz[2]--;
    if(kd('3')&&!cm&&wz[3]&&dt[y][x]!=3)dt[y][x]=3,wz[3]--;
    if(kd('4')&&!cm&&wz[4]&&dt[y][x]!=4)dt[y][x]=4,wz[4]--;
    if(kd('5')&&!cm&&wz[5]&&dt[y][x]!=5)dt[y][x]=5,wz[5]--;
    if(kd('6')&&!cm&&wz[6]&&dt[y][x]!=6)dt[y][x]=6,wz[6]--;

    if(kd('W')&&(dt[y+1][x]==1||dt[y][x]==4)&&!cm&&dt[y-1][x]!=4)ij=1,jh=max(y-7-((dt[y][x]==3)?7:0),2);
    if(kd('W')&&cm)y-=1;
    if(kd('W')&&!cm&&dt[y-1][x]==4)y-=2;

    if(kd('A')&&dt[y][x-1]!=1&&!cm)x--;
    if(kd('A')&&cm)x--;

    if(kd('D')&&dt[y][x+1]!=1&&!cm)x++;
    if(kd('D')&&cm)x++;

    if(kd('S')&&!cm)xd=1;
    if(!kd('S')&&!cm)xd=0;
    if(kd('S')&&cm)y++;

    if(x>=40)x=39;
    if(y>=19)y=18;
    if(x<=-1)x=0;
    if(y<=0)y=1;

    if(dt[y+1][x]!=1&&!ij&&!cm)y++;

    if(kd('O'))return 1;

    if(y<jh)ij=0;
    if(ij==1){
        if(dt[y-1][x]==1)ij=0;
        else y--;
    }

    if(kd('R')&&dt[y][x]==6){
        cle();
        while(kd('R'))Sleep(10);
        cout<<"商店\n";
        cout<<"0.空气(2金币)\n";
        cout<<"1.地板(3金币)\n";
        cout<<"2.金币(5金币)\n";
        cout<<"3.跳板(6金币)\n";
        cout<<"4.水(3金币)\n";
        cout<<"5.地刺(4金币)\n";
        cout<<"6.商店(5金币)\n";
        while(kbhit())getch();
        int aa,bb;
        cin>>aa>>bb;
        if(aa==0){
            if(sc<2*bb)cout<<"赶出去!",Sleep(100);
            else sc-=2*bb,wz[0]+=bb;
        }
        if(aa==1){
            if(sc<3*bb)cout<<"赶出去!",Sleep(100);
            else sc-=3*bb,wz[1]+=bb;
        }
        if(aa==2){
            if(sc<5*bb)cout<<"赶出去!",Sleep(100);
            else sc-=5*bb,wz[2]+=bb;
        }
        if(aa==3){
            if(sc<6*bb)cout<<"赶出去!",Sleep(100);
            else sc-=6*bb,wz[3]+=bb;
        }
        if(aa==4){
            if(sc<3*bb)cout<<"赶出去!",Sleep(100);
            else sc-=3*bb,wz[4]+=bb;
        }
        if(aa==5){
            if(sc<4*bb)cout<<"赶出去!",Sleep(100);
            else sc-=4*bb,wz[5]+=bb;
        }
        if(aa==6){
            if(sc<5*bb)cout<<"赶出去!",Sleep(100);
            else sc-=5*bb,wz[6]+=bb;
        }
    }

    if(kd('T')){
        cle();
        while(kbhit())getch();
        cout<<"请输入指令:\n";
        string a;
        cin>>a;
        if(a=="cm"){
            cm=!cm;
        }
        if(a=="full"){
            int num;
            cin>>num;
            for(int i=1;i<19;i++){
                for(int j=0;j<40;j++){
                    dt[i][j]=num;
                }
            }
        }
        if(a=="nm"){
            nm=!nm;
        }
    }
    return 0;
}
void Sleepp(int microseconds){
    LARGE_INTEGER freq,start,end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    do{
        QueryPerformanceCounter(&end);
    }while((end.QuadPart-start.QuadPart)*1000000LL/freq.QuadPart<microseconds);
}
int main(){
    system("mode con cols=40 lines=25");
    srand(time(0)*time(0));
    while(1){
        hc();
        start:
        cle();
        ss("选择:",20);
        ss("1.闯关",20);
        ss("2.生存/创造",20);
        ss("3.退出",20);
        ss("4.设置",20);
        a=getch()-'0';
        if(a==1){
            while(1){
                bool ok;
                cl(15);
                cle();
                cout<<"第"<<countt<<"关\n"<<"本关成就"<<countt*10<<"个金币";
                Sleep(1000);
                srand(time(0)*time(0));
                randd();
                x=2,y=2,cm=0,jh=0,sc=0,xd=0,xl=100,zcount=0,gxl=100;
                while(1){
                    long long s=mms();
                    print();
                    if(read()){
                        while(kbhit())getch();
                        goto start;
                    }
                    if(move())break;
                    Sleepp(max(1000./(zl*1.)+s-mms(),0.)*1000);
                    zzl=mms()-s;
                }
            }
        }else if(a==2){
            while(1){
                randd();
                x=2,y=2,cm=0,jh=0,xd=0,xl=100,zcount=0;
                while(1){
                    long long s=mms();
                    print();
                    if(read()){
                        while(kbhit())getch();
                        goto start;
                    }
                    if(move())break;
                    Sleepp(max(1000./(zl*1.)+s-mms(),0.)*1000);
                    zzl=mms()-s;
                }
            }
        }else if(a==3){
            return 0;
        }else if(a==4){
            while(kbhit())getch();
            cle();
            cout<<"设置:\n";
            cout<<"1. 帧率设置";
            char aa=getch()-'0';
            if(aa==1){
                cle();
                cout<<"请输入最大帧率(开大了会闪,建议10左右):";
                cin>>zl;
            }
        }else{
            cle();
            cout<<"请按1,2,3或4\n";
            Sleep(1000);
        }
    }
    return 0;
}

