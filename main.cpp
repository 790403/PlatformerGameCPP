#pragma execution_character_set("utf-8")
#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<bits/stdc++.h>
#include<conio.h>
#define kd(K) (GetAsyncKeyState(K)&0x8000)
using namespace std;
using namespace std::chrono;
const int scw=200,sch=100,wzcnt=9;
int mobcnt=10,zdcnt;
string die,name;
int wz[wzcnt+1],w,x,y,jh,sc,xd,xl=100,zcount,ht,a,ms,zco,zl=10,zzl,dt[sch][scw][2],ddt[20][40],ccount=rand(),io,r,esc,win,lxl,ca[5000],wznum,pushx=10,pushy=20;
string tt=" =*#+x$0*";
int&sdt(int aa,int bb,int cc){
    static int _0_;
    _0_=0;
    if(aa<0||aa>=sch||bb<0||bb>=scw||cc<0||cc>=2)return _0_;
    return dt[aa][bb][cc];
}
bool ij,gd,fx;
string seed;
long long intseed;
map<pair<bool,int>,string> bl={
{{0,0},"空气"}, 
{{0,1},"地板"}, 
{{0,2},"金币"}, 
{{0,3},"梯子"}, 
{{0,4},"水"}, 
{{0,5},"地刺"}, 
{{0,6},"商店"}, 
{{0,7},"地狱传送门"}, 
{{0,8},"最终金币"},
{{1,0},"空气"}, 
{{1,1},"地板"}, 
{{1,2},"金币"}, 
{{1,3},"梯子"}, 
{{1,4},"岩浆"}, 
{{1,5},"地刺"}, 
{{1,6},"商店"}, 
{{1,7},"主世界传送门"}, 
{{1,8},"最终金币"},
};
map<string,int> gr={
{"cm",0},
{"nm",0}
};
struct mob{
    int x,y,gxl,ht,lxl,gox,goy;
    char name;
    bool czd;
}aa[100000];
struct ZD{
    int x,y,fx;
    string name;
}zd[100000];
struct con{
    bool sfs,w,syc;
    int fs,wz,wzcount,x,y;
};
size_t hf(string a) {
    const size_t prime=0x100000001b3;
    size_t hash=0xcbf29ce484222325;
    for(char c:a){
        hash^=static_cast<size_t>(static_cast<unsigned char>(c));
        hash*=prime;
    }
    return hash;
}
vector<con> conc;
void wtf(string aaa){
    aaa+=".mycraftsave";
    ofstream fout(aaa);
    if(!fout) {
        printf("存档失败！\n");
        Sleep(1000);
        return;
    }
    fout<<win<<' '<<x<<' '<<w<<' '<<y<<' '<<jh<<' '<<sc<<' '<<xd<<' '<<xl<<' '<<zcount<<' '<<ht<<' '<<a<<' '<<ms<<' '<<zco<<' '<<ccount<<' '<<io<<' '<<r<<' '<<ij<<' '<<gd<<' '<<fx<<' '<<esc<<' '<<wznum<<' '<<pushx<<' '<<pushy<<'\n';
    fout<<die<<'\n';
    fout<<seed<<'\n';
    fout<<tt<<'\n';
    for(int i=0;i<wzcnt;i++)fout<<wz[i]<<' ';
    fout<<'\n';
    for(int i=0;i<sch;i++){
        for(int j=0;j<scw;j++)fout<<sdt(i,j,0)<<' ';
        fout<<'\n';
    }
    for(int i=0;i<sch;i++){
        for(int j=0;j<scw;j++)fout<<sdt(i,j,1)<<' ';
        fout<<'\n';
    }
    fout<<mobcnt<<'\n';
    for(int i=0;i<mobcnt;i++)fout<<aa[i].x<<' '<<aa[i].y<<' '<<aa[i].gxl<<' '<<aa[i].name<<' '<<aa[i].czd<<' '<<aa[i].gox<<' '<<aa[i].goy<<'\n';
    fout<<conc.size()<<'\n';
    for(auto& c:conc)fout<<c.sfs<<' '<<c.fs<<' '<<c.wz<<' '<<c.wzcount<<' '<<c.x<<' '<<c.y<<' '<<c.w<<' '<<c.syc<<'\n';
    fout<<zdcnt<<'\n';
    for(int i=0;i<zdcnt;i++)fout<<zd[i].x<<' '<<zd[i].y<<' '<<zd[i].fx<<' '<<zd[i].name<<'\n';
    fout<<gr.size()<<'\n';
    for(auto i:gr)fout<<i.first<<' '<<i.second<<'\n';
    fout.close();
}
bool rif(string aaa){
    aaa+=".mycraftsave";
    ifstream fin(aaa);
    if(!fin) {
        printf("读档失败！存档文件不存在。\n");
        Sleep(1000);
        return 1;
    }
    fin>>win>>x>>w>>y>>jh>>sc>>xd>>xl>>zcount>>ht>>a>>ms>>zco>>ccount>>io>>r>>ij>>gd>>fx>>esc>>wznum>>pushx>>pushy;
    getline(fin,die);
    getline(fin,die);
    getline(fin,seed);
    getline(fin,tt);
    for(int i=0;i<wzcnt;i++)fin>>wz[i];
    for(int i=0;i<sch;i++)for(int j=0;j<scw;j++)fin>>sdt(i,j,0);
    for(int i=0;i<sch;i++)for(int j=0;j<scw;j++)fin>>sdt(i,j,1);
    fin>>mobcnt;
    for(int i=0;i<mobcnt;i++)fin>>aa[i].x>>aa[i].y>>aa[i].gxl>>aa[i].name>>aa[i].czd>>aa[i].gox>>aa[i].goy;
    int cs;fin>>cs;conc.resize(cs);
    for(auto& c:conc)fin>>c.sfs>>c.fs>>c.wz>>c.wzcount>>c.x>>c.y>>c.w>>c.syc;
    fin>>zdcnt;
    for(int i=0;i<zdcnt;i++)fin>>zd[i].x>>zd[i].y>>zd[i].fx>>zd[i].name;
    gr.clear();
    int n;
    fin>>n;
    for(int i=0;i<n;i++){
        string aa;
        int bb;
        fin>>aa>>bb;
        gr[aa]=bb;
    }
    fin.close();
    return 0;
}
string add(string in){
    string out;
    for(int i=0;i<40-in.length();i++)out+=' ';
    out+='\n';
    return out;
}
void ea(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode=0;
    GetConsoleMode(hConsole,&mode);
    mode|=0x0004;
    SetConsoleMode(hConsole,mode);
}
string cl(int a,int aa=0,bool b=0,bool needstring=0){
    string ansi="";
    int colors[]={34,32,36,31,35,33,37,90,94,92,96,91,95,93,97};
    if(a>0&&a<=16){
        ansi="\033["+to_string(colors[a-1])+";40m";
        if(aa){
            if(b){
                ansi="\033["+to_string(colors[a-1])+";10"+to_string(w)+"m";
            }else{
                ansi="\033["+to_string(colors[a-1])+";4"+to_string(w)+"m";
            }
        }
    }else ansi="\033[0;40m";
    if(needstring){
        return ansi;
    }else{
        cout<<ansi;
        return "";
    }
    /*  1    深蓝色
        2    深绿色
        3    深青色
        4    深红色
        5    深粉色
        6    黄色
        7    深白色
        8    灰色
        9    浅蓝色
        10  浅绿色
        11  浅青色
        12  浅红色
        13  浅粉色
        14  浅黄色
        15  浅白色
    */
}
inline long long mms(){
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
void Sleepp(int m){
    long long start=mms();
    while(1){
        long long e=mms()-start;
        if(e>=m)break;
    }
}
inline void cle(bool a=0){
    if(a)printf("\033[1;1H");
    else{
        system("cls");
        printf("\033[1;1H");
    }
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
        printf("%c",s[i]);
        Sleep(vv);
    }
    Sleep(vv);
    printf("\n");
}
void randd(){
    for(int ii=0;ii<2;ii++){
        for(int j=0;j<scw;j++){
            sdt(0,j,ii)=1;
            sdt(sch-1,j,ii)=1;
        }
        for(int i=1;i<sch-1;i++){
            for(int j=0;j<scw;j++){
                sdt(i,j,ii)=0;
            }
        }
        int pd;
        for(int i=0;i<2;i++){
            pd=rand()%2+2;
            for(int i=1;i<sch-1;i+=pd){
                int stc=rand()%scw;
                int l=rand()%25+15;
                int ec=stc+l;
                if(ec>=scw)ec=scw-1;
                for(int j=stc;j<=ec;j++)sdt(i,j,ii)=1;
                if(i+1<sch-1){
                    int sS=ec+rand()%15+10;
                    if(sS>=scw)sS=scw-30;
                    int sl=rand()%20+8;
                    int se=sS+sl;
                    if(se>=scw)se=scw-1;
                    for(int j=sS;j<=se;j++){
                        sdt(i+1,j,ii)=1;
                    }
                }
            }
        }
        int fc=rand()%8+10;
        fc*=4;
        for(int k=0;k<fc;k++){
            int row=rand()%(sch-20)+10;
            int col=rand()%scw;
            int len=rand()%20+5;
            int ef=1;
            for(int j=col;j<col+len&&j<scw;j++){
                if(sdt(row,j,ii)){
                    ef=0;
                    break;
                }
            }
            if(ef){
                for(int j=col;j<col+len&&j<scw;j++){
                    sdt(row,j,ii)=1;
                }
            }
        }
        int scc=rand()%50+100;
        scc*=4;
        for(int k=0;k<scc;k++){
            int row,col;
            do{
                row=rand()%(sch-2)+1;
                col=rand()%scw;
            }while(sdt(row,col,ii)==1||(sdt(row+1,col,ii)!=1&&row+1<sch-1));
            sdt(row,col,ii)=2;
        }
        int nn=rand()%5+3;
        nn*=3;
        for(int i=0;i<nn;i++){
            int xx=rand()%sch;
            int yy=rand()%scw;
            while(sdt(xx,yy,ii)){
                xx=rand()%sch;
                yy=rand()%scw;
            }
            sdt(xx,yy,ii)=4;
        }
        nn=rand()%5+8;
        nn*=3;
        for(int i=0;i<nn;i++){
            int xx=rand()%sch;
            int yy=rand()%scw;
            while(sdt(xx,yy,ii)||sdt(xx+1,yy,ii)!=1){
                xx=rand()%sch;
                yy=rand()%scw;
            }
            sdt(xx,yy,ii)=5;
        }
        nn=rand()%3+3;
        nn*=3;
        for(int i=0;i<nn;i++){
            int xx=rand()%sch;
            int yy=rand()%scw;
            while(sdt(xx,yy,ii)||sdt(xx+1,yy,ii)!=1){
                xx=rand()%sch;
                yy=rand()%scw;
            }
            sdt(xx,yy,ii)=6;
        }
        if(ii==1){
            int scc=rand()%50+50;
            for(int k=0;k<scc;k++){
                int row,col;
                do{
                    row=rand()%(sch-2)+1;
                    col=rand()%scw;
                }while(sdt(row,col,ii)==1||(sdt(row+1,col,ii)!=1&&row+1<sch-1));
                sdt(row,col,ii)=8;
            }
        }
    }
    x=rand()%scw;
    y=rand()%sch;
    while(sdt(y,x,w)==1||sdt(y,x,w)==5||sdt(y+1,x,w)!=1){
        x=rand()%scw;
        y=rand()%sch;
    }
    for(int i=0;i<mobcnt;i++)aa[i].x=rand()%scw,aa[i].gox=aa[i].x;
    for(int i=0;i<mobcnt;i++)aa[i].y=rand()%sch,aa[i].goy=aa[i].y;
    ccount=rand()%10+25;
    conc.resize(ccount);
    for(auto &i:conc)i.w=1;
    ccount+=rand()%10+25;
    conc.resize(ccount);
    for(auto &i:conc)i.syc=!(rand()%10);
    for(int i=0;i<mobcnt;i++)aa[i].gxl=100,aa[i].name=(rand()%26+65),aa[i].czd=!(rand()%5);
    for(int i=0;i<ccount;i++){
        conc[i].sfs=rand()%2;
        if(conc[i].sfs==1){
            conc[i].fs=rand()%100+50;
        }else{
            conc[i].wz=rand()%wzcnt;
            conc[i].wzcount=rand()%100+50;
        }
        int row,col;
        do{
            row=rand()%(sch-2)+1;
            col=rand()%scw;
        }while(sdt(row,col,conc[i].w)==1||(sdt(row+1,col,conc[i].w)!=1&&row+1<sch-1));
        conc[i].x=col;
        conc[i].y=row;
    }
}
bool hasone(){
    for(int i=1;i<sch;i++){
        for(int j=0;j<sch;j++){
            if(sdt(i-1,j,w)==0&&sdt(i,j,w)==1)return 1;
        }
    }
    return 0;
}
void jb(){
    if(sdt(y,x,w)==2){
        sdt(y,x,w)=0;
        sc++;
        xl+=10;
        int maa=10000;
        int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
        if(hasone()){
            while(sdt(yy,xx,w)!=0||sdt(yy+1,xx,w)!=1){
                xx=(rand()%(scw-2))+1;
                yy=(rand()%(sch-2))+1;
            }
        }else{
            xx=x;
            yy=y;
        }
        sdt(yy,xx,w)=2;
    }
    if(sdt(y,x,w)==8&&w==1){
        sdt(y,x,w)=0;
        esc++;
        sc+=250;
        xl+=10;
        int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
        if(hasone()){
            while(sdt(yy,xx,w)!=0||sdt(yy+1,xx,w)!=1){
                xx=(rand()%(scw-2))+1;
                yy=(rand()%(sch-2))+1;
            }
        }else{
            xx=x;
            yy=y;
        }
        sdt(yy,xx,w)=8;
    }
    for(int i=0;i<ccount;i++){
        if(conc[i].x==x&&conc[i].y==y&&w==conc[i].w){
            int maa=10000;
            conc[i].x=-30;
            conc[i].y=-30;
            if(conc[i].sfs==1){
                sc+=conc[i].fs*(conc[i].syc*4+1);
            }else{
                wz[conc[i].wz]+=conc[i].wzcount*(conc[i].syc*4+1);
            }
            conc[i].sfs=rand()%2;
            if(conc[i].sfs==1){
                conc[i].fs=rand()%100+50;
            }else{
                conc[i].wz=rand()%wzcnt;
                conc[i].wzcount=rand()%100+50;
            }
            int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
            if(hasone()){
                while(sdt(yy,xx,w)!=0||sdt(yy+1,xx,w)!=1){
                    xx=(rand()%(scw-2))+1;
                    yy=(rand()%(sch-2))+1;
                }
            }else{
                xx=x;
                yy=y;
            }
            conc[i].x=xx;
            conc[i].y=yy;
            break;
        }
    }
}
void print(){
    if(gr["cm"])ht=0,xl=100;
    string chu;
    int xx=x-20,yy=y-10;
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            if(yy+i>=0&&yy+i<sch&&xx+j>=0&&xx+j<scw)ddt[i][j]=sdt(yy+i,xx+j,w);
            else ddt[i][j]=0;
        }
    }
    int pos=0;
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            bool htt=0;
            bool ok=0;
            char name;
            for(int k=0;k<mobcnt;k++){
                if(j==aa[k].x-xx&&i==aa[k].y-yy&&aa[k].gxl>0){
                    ok=1;
                    name=aa[k].name;
                    htt=aa[k].ht;
                    break;
                }
            }
            bool sfs=0,sycc=0;
            bool okk=0;
            for(int k=0;k<ccount;k++){
                if(j==conc[k].x-xx&&i==conc[k].y-yy&&w==conc[k].w){
                    okk=1;
                    sfs=conc[k].sfs;
                    sycc=conc[k].syc;
                    break;
                }
            }
            bool okkk=0;
            for(int k=0;k<zdcnt;k++){
                if(j==zd[k].x-xx&&i==zd[k].y-yy){
                    okkk=1;
                    break;
                }
            }
            if(j==20&&i==10){
                chu+=xd?'_':'|';
                ca[pos++]=(!ht?1:12);
            }else if(ok&&!gr["nm"]){
                chu+=name;
                ca[pos++]=(!htt?2:12);
            }else if(j==21&&i==10&&gd&&fx){
                chu+='>';
                ca[pos++]=12;
            }else if(j==19&&i==10&&gd&&!fx){
                chu+='<';
                ca[pos++]=12;
            }else if(okkk){
                chu+='-';
                ca[pos++]=6;
            }else if(okk){
                chu+='*';
                if(sycc){
                    if(sfs)ca[pos++]=(rand()%2?7:8);
                    else ca[pos++]=(rand()%2?5:4);
                }else{
                    ca[pos++]=sfs?7:5;
                }
            }else{
                if(w==0){
                    switch(ddt[i][j]){
                        case 1:chu+=tt[1];ca[pos++]=4;break;
                        case 2:chu+=tt[2];ca[pos++]=6;break;
                        case 3:chu+=tt[3];ca[pos++]=1;break;
                        case 4:chu+=tt[4];ca[pos++]=1;break;
                        case 5:chu+=tt[5];ca[pos++]=2;break;
                        case 6:chu+=tt[6];ca[pos++]=14;break;
                        case 7:chu+=tt[7];ca[pos++]=5;break;
                        default:chu+=tt[0];ca[pos++]=7;
                    }
                }else if(w==1){
                    switch(ddt[i][j]){
                        case 1:chu+=tt[1];ca[pos++]=8;break;
                        case 2:chu+=tt[2];ca[pos++]=6;break;
                        case 3:chu+=tt[3];ca[pos++]=1;break;
                        case 4:chu+=tt[4];ca[pos++]=12;break;
                        case 5:chu+=tt[5];ca[pos++]=2;break;
                        case 6:chu+=tt[6];ca[pos++]=14;break;
                        case 7:chu+=tt[7];ca[pos++]=5;break;
                        case 8:chu+=tt[8];ca[pos++]=3;break;
                        default:chu+=tt[0];ca[pos++]=7;
                    }
                }
            }
        }
        chu+='\n';
        ca[pos++]=7;
    }
    string str;
    str="金币:"+to_string(sc);
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=2;
    str="最终金币:"+to_string(esc);
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=2;
    str="血量:";
    for(int i=0;i<10;i++){
        str+=(xl<=i*10)?'-':'=';
    }
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=4;
    str="帧率:"+to_string(1000.0/zzl);
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=4;
    str="物资["+to_string(wznum)+"]:("+bl[{w,wznum}]+')'+to_string(wz[wznum]);
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=4;
    str="坐标  x:"+to_string(x)+"  y:"+to_string(y);
    str+=add(str);
    chu+=str;
    for(int i=0;i<str.length();i++)ca[pos++]=4;
    chu.pop_back(); 
    ostringstream chu1;
    for(int i=0;i<820;i++){
        chu1<<cl(ca[i],1,i==pushx*41+pushy,1)<<chu[i];
    }
    for(int i=820;i<chu.length();i++){
        unsigned char c=chu[i];
        if(c<0x80){
            chu1<<cl(ca[i],0,0,1)<<chu[i];
        }else if((c&0xE0)==0xC0){
            chu1<<cl(ca[i],0,0,1)<<chu[i]<<chu[i+1];
            i+=1;
        }else if((c&0xF0)==0xE0){
            chu1<<cl(ca[i],0,0,1)<<chu[i]<<chu[i+1]<<chu[i+2];
            i+=2;
        }else if((c&0xF8)==0xF0){
            chu1<<cl(ca[i],0,0,1)<<chu[i]<<chu[i+1]<<chu[i+2]<<chu[i+3];
            i+=3;
        }
    }
    cle(1);
    cout<<chu1.str();
}
bool move(){
    zcount++;
    wtf(name);
    for(int i=99;i>=0;i--){
        for(int j=scw-1;j>=0;j--){
            if(sdt(i,j,w)==4){
                if(sdt(i+1,j,w)!=0&&sdt(i+1,j,w)!=4){
                    if(sdt(i,j-1,w)!=4&&sdt(i,j-1,w)==0)sdt(i,j-1,w)=4,j--;
                    if(sdt(i,j+1,w)!=4&&sdt(i,j+1,w)==0)sdt(i,j+1,w)=4;
                }else if(sdt(i+1,j,w)!=4&&sdt(i+1,j,w)==0)sdt(i+1,j,w)=4;
            }
        }
    }
    if(sc>1000&&!r)sdt(y,x+1,w)=7,r=1;
    if(sdt(y,x,w)==7&&x>=0&&y>=0&&x<scw&&y<sch){
        if(w==0){
            w=1;
            sdt(y,x,!w)=0;
            sdt(y,x+1,w)=7;
        }else{
            w=0;
            sdt(y,x,!w)=0;
            sdt(y,x+1,w)=7;
        }
    }
    if(esc>=20&&!io){
        aa[mobcnt-1].gxl=5000;
        aa[mobcnt-1].x=x;
        aa[mobcnt-1].y=y;
        aa[mobcnt-1].name='+';
        io=1;
    }
    if(aa[mobcnt-1].name=='+'&&aa[mobcnt-1].gxl<0&&!win){
        sdt(aa[mobcnt-1].y,aa[mobcnt-1].x,w)=7;
        cle();
        cout<<"      你通关了 Mycraft\n   版本:1.0.0   作者:123\n致谢:DeepSeek网页版,通义网页版";
        win=1;
        Sleepp(4000);
    }
    for(int i=0;i<mobcnt;i++){
        if(fx==0&&aa[i].x==x-1&&aa[i].y==y&&gd&&!gr["nm"]&&aa[i].gxl>0)aa[i].gxl-=20+sc/10;
        if(fx==1&&aa[i].x==x+1&&aa[i].y==y&&gd&&!gr["nm"]&&aa[i].gxl>0)aa[i].gxl-=20+sc/10;
        if(aa[i].gxl<=0&&sdt(aa[i].y,aa[i].x,w)==5&&!gr["nm"])aa[i].y=rand()%sch,aa[i].x=rand()%scw;
        if(!(zcount%5)&&aa[i].name!='+'&&!gr["nm"])aa[i].gxl++;
        if(aa[i].x==aa[i].gox&&aa[i].y==aa[i].goy&&!gr["nm"]){
            int xx=aa[i].x+((rand()%21)-10),yy=aa[i].y+((rand()%21)-10);
            int ma=1000;
            while(sdt(yy,xx,w)==6&&ma--)xx=aa[i].x+((rand()%21)-10),yy=aa[i].y+((rand()%21)-10);
            aa[i].gox=xx;
            aa[i].goy=yy;
        }
        if(((abs(x-aa[i].x)<=10&&abs(y-aa[i].y)<=10)||aa[i].name=='+')&&!gr["cm"]&&sdt(y,x,w)!=6)aa[i].gox=x,aa[i].goy=y;
        if(aa[i].gox<=0)aa[i].gox=0;
        if(aa[i].gox>scw)aa[i].gox=scw-1;
        if(aa[i].goy<=0)aa[i].goy=0;
        if(aa[i].goy>sch)aa[i].goy=sch-1;
        if(zcount%2&&!gr["nm"]&&aa[i].gxl>0){
            if(aa[i].x<aa[i].gox&&abs(aa[i].x-aa[i].gox)>=abs(aa[i].y-aa[i].goy))aa[i].x++;
            if(aa[i].x>aa[i].gox&&abs(aa[i].x-aa[i].gox)>=abs(aa[i].y-aa[i].goy))aa[i].x--;
            if(aa[i].y<aa[i].goy&&abs(aa[i].y-aa[i].goy)>=abs(aa[i].x-aa[i].gox))aa[i].y++;
            if(aa[i].y>aa[i].goy&&abs(aa[i].y-aa[i].goy)>=abs(aa[i].x-aa[i].gox))aa[i].y--;
        }
        if(aa[i].gxl>=100&&aa[i].name!='+'&&!gr["nm"])aa[i].gxl=100;
        if(sdt(aa[i].y,aa[i].x,w)==5&&!gr["nm"]&&aa[i].gxl>0)aa[i].gxl-=10;
        if(sdt(aa[i].y,aa[i].x,w)==4&&w==1&&!gr["nm"]&&aa[i].gxl>0)aa[i].gxl-=5;
        if(sdt(aa[i].y,aa[i].x,w)==4&&w==0&&!gr["nm"]&&aa[i].gxl>0)aa[i].gxl-=2;
        if(aa[i].czd&&!(zcount%10)&&rand()%2&&!gr["nm"]&&aa[i].gxl>0)zd[zdcnt++]={aa[i].x,aa[i].y,aa[i].x<x,string(1,aa[i].name)};
    }
    if(zcount%2)xl++;
    if(xl>=100)xl=100;
    if(!(zcount%4)&&sdt(y,x,w)==4&&w==0)xl-=3,die="你在水里窒息而亡";
    if(sdt(y,x,w)==4&&w==1)xl-=5,die="你试图在岩浆里游泳";
    if(sdt(y,x,w)==5)xl-=10,die="你被地刺扎死了";
    for(int i=0;i<mobcnt;i++)if(x==aa[i].x&&y==aa[i].y&&!gr["cm"]&&!gr["nm"]&&!xd&&aa[i].gxl>0)xl-=5,die="你被"+string(1,aa[i].name)+"杀死了";
    if(y>120)xl-=5,die="你掉入了虚空";
    if(xl<=0&&a==2){
        cle();
        ss(die,100);
        Sleep(1000);
        x=rand()%scw;
        y=rand()%sch;
        while(sdt(y,x,w)==1||sdt(y,x,w)==5||sdt(y+1,x,w)!=1){
            x=rand()%scw;
            y=rand()%sch;
        }
        return 1;
    }
    if(xl<=0&&a==1){
        system(("del /f \""+name+".txt\"").c_str());
        cle();
        ss(die+"\n很遗憾，你丢失了极限世界",100);
        exit(0);
    }
    for(int i=0;i<zdcnt;i++){
        if(zd[i].fx!=-1&&zd[i].x>-30&&zd[i].x<230)zd[i].x+=(zd[i].fx?1:-1);
    }
    for(int i=0;i<zdcnt;i++){
        for(int j=0;j<mobcnt;j++){
            if(zd[i].x==aa[j].x&&zd[i].y==aa[j].y&&aa[j].gxl>0&&!gr["nm"]){
                aa[j].gxl-=50+(sc/20);
                zd[i].x=-30;
                zd[i].fx=-1;
            }
        }
        if(zd[i].x==x&&zd[i].y==y&&zd[i].name!="player"){
            xl-=30;
            die="你被"+zd[i].name+"用子弹射杀了"; 
        }
    }
    for(int i=0;i<zdcnt;i++){
        if(zd[i].x==-30||zd[i].x==230){
            for(int j=i;j<zdcnt;j++){
                zd[j]=zd[j+1];
            }
            zdcnt--;
            i--; 
        }
    }
    if(xl<lxl)ht=1;
    else ht=0;
    lxl=xl;
    for(int i=0;i<mobcnt;i++){
        if(aa[i].gxl<aa[i].lxl)aa[i].ht=1;
        else aa[i].ht=0;
        aa[i].lxl=aa[i].gxl;
    }
    return 0;
}
bool read(){
    if(kd(VK_RIGHT))pushy++;
    if(kd(VK_LEFT))pushy--;
    if(kd(VK_DOWN))pushx++;
    if(kd(VK_UP))pushx--;

    if(pushx<0)pushx=0;
    if(pushy<0)pushy=0;
    if(pushx>19)pushx=19;
    if(pushy>38)pushy=38;

    for(int i=0;i<wzcnt;i++)if(kd(0x60+i))wznum=i;

    for(int i=0;i<wzcnt;i++)if(kd(to_string(i)[0])&&gr["cm"]&&x>=0&&y>=0&&x<scw&&y<sch)sdt(y-10+pushx,x-20+pushy,w)=i;

    if(kd('0')&&!gr["cm"]&&wz[0]&&sdt(y-10+pushx,x-20+pushy,w)!=0&&x-20+pushy>=0&&y-10+pushx>=0&&x-20+pushy<scw&&y-10+pushx<sch)wz[sdt(y-10+pushx,x-20+pushy,w)]++,sdt(y-10+pushx,x-20+pushy,w)=0,wz[0]--;
    for(int i=1;i<wzcnt;i++)if(kd(to_string(i)[0])&&!gr["cm"]&&wz[i]&&sdt(y-10+pushx,x-20+pushy,w)!=i&&x-20+pushy>=0&&y-10+pushx>=0&&x-20+pushy<scw&&y-10+pushx<sch)sdt(y-10+pushx,x-20+pushy,w)=i,wz[i]--;

    if(kd('W')&&(sdt(y+1,x,w)==1||sdt(y,x,w)==4||sdt(y,x,w)==3)&&!gr["cm"]&&sdt(y-1,x,w)!=4&&sdt(y-1,x,w)!=3)ij=1,jh=y-7;
    if(kd('W')&&gr["cm"])y-=1;

    if(sdt(y+1,x,w)!=1&&!ij&&!gr["cm"]&&y<sch)y++;
    if(xd&&sdt(y+1,x,w)!=1&&!ij&&!gr["cm"]&&y<sch)y++;

    if(y>=sch&&!gr["cm"])y++;
    
    if(kd('W')&&!gr["cm"]&&sdt(y-1,x,w)==4)y-=1;
    if(kd('W')&&!gr["cm"]&&sdt(y-1,x,w)==4)y-=1;
    
    if(kd('W')&&!gr["cm"]&&sdt(y-1,x,w)==3)y-=1;
    if(kd('W')&&!gr["cm"]&&sdt(y-1,x,w)==3)y-=1;

    if(kd('A')&&sdt(y,x-1,w)!=1&&!gr["cm"])x--,fx=0;
    if(kd('A')&&gr["cm"])x--,fx=0;

    if(kd('D')&&sdt(y,x+1,w)!=1&&!gr["cm"])x++,fx=1;
    if(kd('D')&&gr["cm"])x++,fx=1;

    jb();

    if(kd(VK_SPACE)&&kd('A')&&sdt(y,x-1,w)!=1&&!gr["cm"])x--,fx=0;
    if(kd(VK_SPACE)&&kd('A')&&gr["cm"])x--,fx=0;

    if(kd(VK_SPACE)&&kd('D')&&sdt(y,x+1,w)!=1&&!gr["cm"])x++,fx=1;
    if(kd(VK_SPACE)&&kd('D')&&gr["cm"])x++,fx=1;

    if(kd('C'))gd=1;
    if(!kd('C'))gd=0;

    if(kd('S')&&!gr["cm"])xd=1;
    if(!kd('S')&&!gr["cm"])xd=0;
    if(kd('S')&&gr["cm"])y++;

    if(x>=scw)x=scw-1;
    if(x<=-1)x=0;

    if(kd(VK_ESCAPE))return 1;

    if(y<jh)ij=0;
    
    if(ij==1){
        if(sdt(y-1,x,w)==1)ij=0;
        else y--;
    }

    if(sdt(y,x,w)==4)ij=0,jh=0;

    if(kd('R')&&sdt(y,x,w)==6){
        int pri[]={2,3,5,6,3,4,5,1000,300};
        cle();
        while(kd('R'))Sleep(10);
        printf("商店\n");
        for(int i=0;i<wzcnt;i++)printf("%s:%d金币(%d)\n",bl[{w,i}].c_str(),pri[i],i);
        while(_kbhit())_getch();
        int aa,bb;
        cin>>aa>>bb;
        for(int i=0;i<wzcnt;i++){
            if(aa==i){
                if(sc<pri[i]*bb)printf("赶出去!"),Sleep(100);
                else sc-=pri[i]*bb,wz[i]+=bb;
            }
        }
    }
    
    if(kd('G')&&sdt(y,x,w)==6){
        int pri[]={2,3,5,6,3,4,5,1000,300};
        cle();
        while(kd('G'))Sleep(10);
        printf("收货\n");
        for(int i=0;i<wzcnt;i++)printf("%s:%d金币(%d)\n",bl[{w,i}].c_str(),pri[i],i);
        while(_kbhit())_getch();
        int aa,bb;
        cin>>aa>>bb;
        for(int i=0;i<wzcnt;i++){
            if(aa==i){
                if(wz[i]<bb)printf("赶出去!"),Sleep(100);
                else sc+=pri[i]*bb,wz[i]-=bb;
            }
        }
    }

    if(kd('T')&&a==1){
        cle();
        printf("极限世界不能使用指令\n");
        Sleepp(2000);
    }
    
    if(kd('F')){
        bool is=0;
        for(int i=0;i<wzcnt;i++){
            is+=!!wz[i];
            if(is==1)break;
        }
        if(is||gr["cm"]){
            int g=rand()%wzcnt;
            if(is)while(!wz[g])g=rand()%wzcnt;
            if(wz[g]||gr["cm"]){
                wz[g]-=!gr["cm"];
                zd[zdcnt++]={x,y,fx,"player"};
            }
        }
        
    }
    
    if(kd('T')&&a!=1){
        cle();
        while(_kbhit())_getch();
        printf("请输入指令:\n");
        string a;
        cin>>a;
        if(a=="gr"){
            string f;
            int ff;
            cin>>f>>ff;
            if(gr.count(f))gr[f]=ff;
        }
        if(a=="grl"){
            for(auto i:gr)cout<<i.first<<' '<<i.second<<'\n';
            _getch();
        }
        if(a=="full"){
            int num;
            cin>>num;
            for(int i=1;i<sch-1;i++){
                for(int j=0;j<scw;j++){
                    sdt(i,j,w)=num;
                }
            }
        }
        if(a=="give"){
            int aaa,bbb;
            cin>>aaa>>bbb;
            wz[aaa]+=bbb;
        }
        if(a=="write"){
            printf("请输入存档名字：");
            string a;
            cin>>a;
            wtf(a);
            printf("读档成功！\n");
            Sleep(1000);
        }
        if(a=="read"){
            printf("请输入存档名字：");
            string a;
            cin>>a;
            rif(a);
            printf("存档成功！\n");
            Sleep(1000);
        }
        if(a=="ovw"){
            if(w==1){
                sdt(y,x+1,w)=7;
                w=0;
            }
        }
        if(a=="nw"){
            if(w==0){
                sdt(y,x+1,w)=7;
                w=1;
            }
        }
        if(a=="kill"){
            xl=-100;
            die="你被命令杀死了";
        }
        if(a=="seed"){
            cout<<"种子:"<<seed;
            while(!_kbhit());
        }
        if(a=="newseed"){
            cin>>seed;
            intseed=hf(seed);
            srand(intseed);
            randd();
        }
        if(a=="tp"){
            int xx,yy;
            cin>>xx>>yy;
            x=xx;
            y=yy;
        }
        cle();
    }
    return 0;
}
int main(){
    system("chcp 65001 > nul");
    system("mode con cols=40 lines=26");
    cout<<"欢迎来到Mycraft\n";
    cout<<"选择：\n";
    ss("1.创建游戏",20);
    ss("2.读取存档",20);
    int a1;
    a1=_getch()-'0';
    if(a1==1){
        cout<<"请输入世界名称：";
        getline(cin,name);
        cout<<"输入种子(留空以随机生成种子):";
        getline(cin,seed);
        if(seed==""){
            srand(time(0));
            string chars={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
            seed.resize(rand()%10+10);
            for(auto &i:seed)i=chars[rand()%chars.size()];
            intseed=hf(seed);
            srand(intseed);
        }else{
            intseed=hf(seed);
            srand(intseed);
        }
        randd();
    }else if(a1==2){
        cout<<"请输入世界名称：";
        getline(cin,name);
        if(rif(name)==1)return 0;
    }
    ea();
    hc();
    while(1){
        start:
        cle();
        ss("选择:",10);
        ss("1.极限模式",10);
        ss("2.生存/创造",10);
        ss("3.退出",10);
        ss("4.设置",10);
        a=_getch()-'0';
        if(a==1){
            while(1){
                while(1){
                    long long s=mms();
                    print();
                    jb();
                    cl(15);
                    if(read()){
                        while(_kbhit())_getch();
                        goto start;
                    }
                    if(move())break;
                    Sleepp(max(1000./(zl*1.)+s-mms(),0.));
                    zzl=mms()-s;
                }
                ij=0,xl=100,zcount=0;
            }
        }else if(a==2){
            while(1){
                while(1){
                    long long s=mms();
                    print();
                    jb();
                    cl(15);
                    if(read()){
                        while(_kbhit())_getch();
                        goto start;
                    }
                    if(move())break;
                    Sleepp(max(1000./(zl*1.)+s-mms(),0.));
                    zzl=mms()-s;
                }
                ij=0,xl=100,zcount=0;
            }
        }else if(a==3){
            return 0;
        }else if(a==4){
            while(_kbhit())_getch();
            while(1){
                cle();
                printf("设置:\n");
                printf("1. 帧率设置\n");
                printf("2. 材质包加载\n");
                printf("3. 退出\n");
                char aa=_getch()-'0';
                if(aa==1){
                    cle();
                    printf("请输入最大帧率:");
                    cin>>zl;
                }else if(aa==2){
                    cle();
                    printf("输入材质包路径：");
                    string path;
                    getline(cin,path);
                    ifstream fin(path);
                    getline(fin,tt);
                    fin.close();
                }else if(aa==3){
                    break;
                }else{
                    cle();
                    printf("请按1、2或3\n");
                    Sleep(1000);
                }
            }
        }else{
            cle();
            printf("请按1,2,3或4\n");
            Sleep(1000);
        }
    }
    return 0;
}
