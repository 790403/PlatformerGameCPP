#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<chrono>
#include<random>
#define kd(K) (GetAsyncKeyState(K)&0x8000)
using namespace std;
using namespace std::chrono;
const int scw=200,sch=100,block_type_count=10;
int mobcnt=10;
string die,name;
int block[block_type_count+1],world,x,y,jump_height,score,hp=100,total_fps,boss_idx,hit,target_fps=10;
int raw_dt[scw][sch][2],view[20][40],reward_count,can_summon_boss,plr_to_nw,end_score,win,last_hp,color[5000],slot;
int place_x=10,place_y=20,mode,attack_power=20,defense_power=100,defense_shop_buy_count,attack_shop_buy_count,bullet_count=0;
bool is_jump,is_fighting,facing,squat;
int fps;
string seed;
long long hashed_seed;
//------------------------所有贴图和颜色----------------------------------
int block_color[block_type_count][2]={{7,7},{4,8},{6,6},{1,1},{1,12},{2,2},{14,14},{5,5},{0,3},{9,9}};
int mob_color[2]={2,7};
int bullet_color=6;
int reward_color[2]={7,8};
string mob_name_str="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string block_texture=" =*#+x$0*$";
char bullet_texture='-';
char reward_texture='*';
//-----------------------------------------------------------------------
map<string,int> zh_to_color={
    {"深蓝",1},
    {"深绿",2},
    {"深青",3},
    {"深红",4},
    {"深粉",5},
    {"深黄",6},
    {"深白",7},
    {"灰",8},
    {"蓝",9},
    {"绿",10},
    {"青",11},
    {"红",12},
    {"粉",13},
    {"黄",14},
    {"白",15}
};
map<int,string> color_to_zh;
map<pair<bool,int>,string> block_name={
    {{0,0},"空气"},
    {{0,1},"地板"},
    {{0,2},"金币"},
    {{0,3},"梯子"},
    {{0,4},"水"},
    {{0,5},"地刺"},
    {{0,6},"商店"},
    {{0,7},"地狱传送门"},
    {{0,8},"最终金币"},
    {{0,9},"武器商店"},
    {{1,0},"空气"},
    {{1,1},"地板"},
    {{1,2},"金币"},
    {{1,3},"梯子"},
    {{1,4},"岩浆"},
    {{1,5},"地刺"},
    {{1,6},"商店"},
    {{1,7},"主世界传送门"},
    {{1,8},"最终金币"},
    {{1,9},"武器商店"},
};
map<string,int> gr={
    {"cm",0},
    {"nm",0}
};
map<string,char> key_pos={
    {"jump",'W'},
    {"left",'A'},
    {"right",'D'},
    {"squat",'S'},
    {"shop_buy",'R'},
    {"shop_sell",'G'},
    {"shoot",'F'},
    {"fight",'C'},
    {"cmd",'T'},
    {"speed_up",' '},
};
struct mob{
    int x,y,hp,hit,last_hp,target_x,target_y,max_hp;
    char name;
    bool can_shoot;
};
struct bullet{
    int x,y,facing;
    string name;
};
struct reward{
    bool world,is_double;
    int score,x,y;
};
vector<mob>mobs(mobcnt);
vector<bullet>bullets;
vector<reward> rewards;
inline long long get_ms(){
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
void sleep_ms(int m){
    long long start=get_ms();
    while(1){
        long long e=get_ms()-start;
        if(e>=m)break;
    }
}
int&dt(int x,int y,int world){
    static int _0_;
    _0_=0;
    if(x<0||x>=scw||y<0||y>=sch||world<0||world>=2)return _0_;
    return raw_dt[x][y][world];
}
size_t hash_str(string a) {
    const size_t prime=0x100000001b3;
    size_t hash=0xcbf29ce484222325;
    for(char c:a){
        hash^=(int)c;
        hash*=prime;
    }
    return hash;
}
void save(string aaa){
    aaa+=".mycraftsave";
    ofstream fout(aaa);
    if(!fout){
        cout<<"存档失败！\n";
        sleep_ms(1000);
        return;
    }
    fout<<bullet_texture<<' '<<bullet_color<<' '<<reward_texture<<' '<<mode<<' '<<win<<' '<<x<<' '<<world<<' '<<y<<' '<<jump_height<<' '<<score<<' '<<squat<<' '<<hp<<' '<<total_fps<<' '<<hit<<' '<<reward_count<<' '<<can_summon_boss<<' '<<plr_to_nw<<' '<<is_jump<<' '<<is_fighting<<' '<<facing<<' '<<end_score<<' '<<slot<<' '<<place_x<<' '<<place_y<<' '<<boss_idx<<' '<<bullet_count<<'\n';
    fout<<die<<'\n';
    fout<<seed<<'\n';
    fout<<block_texture<<'\n';
    fout<<mob_name_str<<'\n';
    for(int i=0;i<block_type_count;i++)fout<<block[i]<<' ';
    fout<<'\n';
    for(int i=0;i<2;i++)fout<<reward_color[i]<<' ';
    fout<<'\n';
    for(int i=0;i<block_type_count;i++)fout<<block_color[i][0]<<' ';
    fout<<'\n';
    for(int i=0;i<block_type_count;i++)fout<<block_color[i][1]<<' ';
    fout<<'\n';
    for(int i=0;i<2;i++)fout<<mob_color[i]<<' ';
    fout<<'\n';
    for(int i=0;i<sch;i++){
        for(int j=0;j<scw;j++)fout<<dt(j,i,0)<<' ';
        fout<<'\n';
    }
    for(int i=0;i<sch;i++){
        for(int j=0;j<scw;j++)fout<<dt(j,i,1)<<' ';
        fout<<'\n';
    }
    fout<<mobs.size()<<'\n';
    for(int i=0;i<mobs.size();i++)fout<<mobs[i].x<<' '<<mobs[i].y<<' '<<mobs[i].hp<<' '<<mobs[i].name<<' '<<mobs[i].can_shoot<<' '<<mobs[i].target_x<<' '<<mobs[i].target_y<<' '<<mobs[i].last_hp<<' '<<mobs[i].hit<<' '<<mobs[i].max_hp<<'\n';
    fout<<rewards.size()<<'\n';
    for(auto& c:rewards)fout<<c.score<<' '<<c.x<<' '<<c.y<<' '<<c.world<<' '<<c.is_double<<'\n';
    fout<<bullets.size()<<'\n';
    for(int i=0;i<bullets.size();i++)fout<<bullets[i].x<<' '<<bullets[i].y<<' '<<bullets[i].facing<<' '<<bullets[i].name<<'\n';
    fout<<gr.size()<<'\n';
    for(auto i:gr)fout<<i.first<<' '<<i.second<<'\n';
    fout<<key_pos.size()<<'\n';
    for(auto i:key_pos)fout<<i.first<<' '<<'\''<<i.second<<'\''<<'\n';
    fout<<attack_power<<'\n';
    fout<<attack_shop_buy_count<<'\n';
    fout<<defense_power<<'\n';
    fout<<defense_shop_buy_count<<'\n';
    fout.close();
}
struct auto_save{
    ~auto_save(){
        if(total_fps>0)save(name);
    }
}auto_save_example;
bool load(string aaa){
    aaa+=".mycraftsave";
    ifstream fin(aaa);
    if(!fin){
        cout<<"读档失败！存档文件不存在。\n";
        sleep_ms(1000);
        return 1;
    }
    fin>>bullet_texture>>bullet_color>>reward_texture>>mode>>win>>x>>world>>y>>jump_height>>score>>squat>>hp>>total_fps>>hit>>reward_count>>can_summon_boss>>plr_to_nw>>is_jump>>is_fighting>>facing>>end_score>>slot>>place_x>>place_y>>boss_idx>>bullet_count;
    getline(fin,die);
    getline(fin,die);
    getline(fin,seed);
    getline(fin,block_texture);
    getline(fin,mob_name_str);
    for(int i=0;i<block_type_count;i++)fin>>block[i];
    for(int i=0;i<2;i++)fin>>reward_color[i];
    for(int i=0;i<block_type_count;i++)fin>>block_color[i][0];
    for(int i=0;i<block_type_count;i++)fin>>block_color[i][1];
    for(int i=0;i<2;i++)fin>>mob_color[i];
    for(int i=0;i<sch;i++)for(int j=0;j<scw;j++)fin>>dt(j,i,0);
    for(int i=0;i<sch;i++)for(int j=0;j<scw;j++)fin>>dt(j,i,1);
    int size;
    fin>>size;
    mobs.resize(size);
    for(int i=0;i<mobs.size();i++)fin>>mobs[i].x>>mobs[i].y>>mobs[i].hp>>mobs[i].name>>mobs[i].can_shoot>>mobs[i].target_x>>mobs[i].target_y>>mobs[i].last_hp>>mobs[i].hit>>mobs[i].max_hp;
    fin>>size;
    rewards.resize(size);
    for(auto&c:rewards)fin>>c.score>>c.x>>c.y>>c.world>>c.is_double;
    fin>>size;
    bullets.resize(size);
    for(int i=0;i<bullets.size();i++)fin>>bullets[i].x>>bullets[i].y>>bullets[i].facing>>bullets[i].name;
    gr.clear();
    fin>>size;
    for(int i=0;i<size;i++){
        string aa;
        int bb;
        fin>>aa>>bb;
        gr[aa]=bb;
    }
    key_pos.clear();
    fin>>size;
    for(int i=0;i<size;i++){
        string aa;
        string bb(4,'\0');
        fin>>aa;
        fin.read(&bb[0],4);
        key_pos[aa]=bb[2];
    }
    fin>>attack_power;
    fin>>attack_shop_buy_count;
    fin>>defense_power;
    fin>>defense_shop_buy_count;
    fin.close();
    return 0;
}
string pad_line(string in){
    int len=0;
    for(int i=0;i<in.length();i++){
        unsigned char c=in[i];
        if(c<0x80){
            len++;
        }else if((c&0xE0)==0xC0){
            len+=2;
            i+=1;
        }else if((c&0xF0)==0xE0){
            len+=2;
            i+=2;
        }else if((c&0xF8)==0xF0){
            len+=2;
            i+=3;
        }
    }
    return string(40-len,' ')+"\n";
}
void enable_ansi(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode=0;
    GetConsoleMode(hConsole,&mode);
    mode|=0x0004;
    SetConsoleMode(hConsole,mode);
}
string get_color(int type,int use_bg_color=0,bool highlight=0,bool needstring=0){
    string ansi="";
    int colors[]={34,32,36,31,35,33,37,90,94,92,96,91,95,93,97};
    if(type>0&&type<=15){
        ansi="\033["+to_string(colors[type-1])+";40m";
        if(use_bg_color){
            if(highlight){
                ansi="\033["+to_string(colors[type-1])+";10"+to_string(world)+"m";
            }else{
                ansi="\033["+to_string(colors[type-1])+";4"+to_string(world)+"m";
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
inline void clear(bool a=0){
    if(a)cout<<"\033[1;1H";
    else{
        system("cls");
    }
}
void hide_cursor(){
    cout<<"\033[?25l";
}
void show_cursor(){
    cout<<"\033[?25h";
}
void slowly_type(string s,int speed){
    for(int i=0;i<s.size();i++){
        cout<<s[i];
        sleep_ms(speed);
    }
    sleep_ms(speed);
    cout<<'\n';
}
void randd(){
    for(int ii=0;ii<2;ii++){
        for(int j=0;j<scw;j++){
            dt(j,0,ii)=1;
            dt(j,sch-1,ii)=1;
        }
        for(int i=1;i<sch-1;i++){
            for(int j=0;j<scw;j++){
                dt(j,i,ii)=0;
            }
        }
        int space;
        for(int i=0;i<2;i++){
            space=rand()%2+2;
            for(int j=1;j<sch-1;j+=space){
                int start=rand()%scw;
                int len=rand()%25+15;
                int end=start+len;
                if(end>=scw)end=scw-1;
                for(int k=start;k<=end;k++)dt(k,j,ii)=1;
                if(j+1<sch-1){
                    int start=end+rand()%15+10;
                    if(start>=scw)start=scw-30;
                    int len=rand()%20+8;
                    int end=start+len;
                    if(end>=scw)end=scw-1;
                    for(int k=start;k<=end;k++)dt(k,j+1,ii)=1;
                }
            }
        }
        int n=rand()%32+40;
        for(int k=0;k<n;k++){
            int yy=rand()%(sch-20)+10;
            int xx=rand()%scw;
            int len=rand()%20+5;
            int empty=1;
            for(int j=xx;j<xx+len&&j<scw;j++){
                if(dt(j,yy,ii)){
                    empty=0;
                    break;
                }
            }
            if(empty)for(int j=xx;j<xx+len&&j<scw;j++)dt(j,yy,ii)=1;
        }
        vector<int>type={2,4,5,6,8,9};
        vector<pair<int,int>>cnt={{200,400},{15,9},{15,24},{9,9},{50,50},{9,9}};
        vector<bool>on_floor={1,0,1,1,1,1};
        vector<bool>in_nw={0,0,0,0,1,0};
        int xx,yy;
        for(int k=0;k<type.size();k++){
            if(!in_nw[k]||(in_nw[k]&&ii)){
                int count=(rand()%cnt[k].first)+cnt[k].second;
                for(int j=0;j<count;j++){
                    do{
                        xx=rand()%sch;
                        yy=rand()%scw;
                    }while(dt(yy,xx,ii)||(dt(yy,xx+1,ii)!=1&&on_floor[k]));
                    dt(yy,xx,ii)=type[k];
                }
            }
        }
    }
    x=rand()%scw;
    y=rand()%sch;
    while(dt(x,y,world)==1||dt(x,y,world)==5||dt(x,y+1,world)!=1){
        x=rand()%scw;
        y=rand()%sch;
    }
    for(int i=0;i<mobs.size();i++)mobs[i].x=rand()%scw,mobs[i].target_x=mobs[i].x;
    for(int i=0;i<mobs.size();i++)mobs[i].y=rand()%sch,mobs[i].target_y=mobs[i].y;
    for(int i=0;i<mobs.size();i++)mobs[i].max_hp=100;
    reward_count=rand()%5+15;
    rewards.resize(reward_count);
    for(auto &i:rewards)i.world=1;
    reward_count+=rand()%5+15;
    rewards.resize(reward_count);
    for(auto &i:rewards)i.is_double=!(rand()%10);
    for(int i=0;i<mobs.size();i++)mobs[i].hp=100,mobs[i].name=mob_name_str[rand()%mob_name_str.size()],mobs[i].can_shoot=!(rand()%5);
    for(int i=0;i<reward_count;i++){
        rewards[i].score=rand()%100+50;
        int yy,xx;
        do{
            yy=rand()%sch;
            xx=rand()%scw;
        }while(!(dt(xx,yy,rewards[i].world)==0&&dt(xx,yy+1,rewards[i].world)==1));
        rewards[i].x=xx;
        rewards[i].y=yy;
        dt(xx,yy,rewards[i].world)=2;
    }
}
bool hasone(){
    for(int i=1;i<sch;i++){
        for(int j=0;j<scw;j++){
            if(dt(j,i-1,world)==0&&dt(j,i,world)==1)return 1;
        }
    }
    return 0;
}
void check_coin(){
    if(dt(x,y,world)==2){
        dt(x,y,world)=0;
        score++;
        hp+=10;
        int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
        if(hasone()){
            while(dt(xx,yy,world)!=0||dt(xx,yy+1,world)!=1){
                xx=(rand()%(scw-2))+1;
                yy=(rand()%(sch-2))+1;
            }
        }else{
            xx=x;
            yy=y;
        }
        dt(xx,yy,world)=2;
    }
    if(dt(x,y,world)==8&&world==1){
        dt(x,y,world)=0;
        end_score++;
        score+=250;
        hp+=10;
        int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
        if(hasone()){
            while(dt(xx,yy,world)!=0||dt(xx,yy+1,world)!=1){
                xx=(rand()%(scw-2))+1;
                yy=(rand()%(sch-2))+1;
            }
        }else{
            xx=x;
            yy=y;
        }
        dt(xx,yy,world)=8;
    }
    for(int i=0;i<reward_count;i++){
        if(rewards[i].x==x&&rewards[i].y==y&&world==rewards[i].world){
            rewards[i].x=-30;
            rewards[i].y=-30;
            score+=rewards[i].score*(rewards[i].is_double*4+1);
            rewards[i].score=rand()%100+50;
            int xx=(rand()%(scw-2))+1,yy=(rand()%(sch-2))+1;
            if(hasone()){
                while(dt(xx,yy,world)!=0||dt(xx,yy+1,world)!=1){
                    xx=(rand()%(scw-2))+1;
                    yy=(rand()%(sch-2))+1;
                }
            }else{
                xx=x;
                yy=y;
            }
            rewards[i].x=xx;
            rewards[i].y=yy;
            break;
        }
    }
}
string add_color(string out,int colour,int&pos){
    string ans;
    out+=pad_line(out);
    ans+=out;
    for(int i=0;i<out.length();i++)color[pos++]=colour;
    return ans;
}
void print(){
    string out;
    ostringstream final_out;
    int pos=0;
    if(gr["cm"])hit=0,hp=100;
    int xx=x-20,yy=y-10;
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            if(yy+i>=0&&yy+i<sch&&xx+j>=0&&xx+j<scw)view[i][j]=dt(xx+j,yy+i,world);
            else view[i][j]=0;
        }
    }
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            bool find_mob=0;
            mob temp_mob;
            for(int k=0;k<mobs.size();k++){
                if(j==mobs[k].x-xx&&i==mobs[k].y-yy&&mobs[k].hp>0){
                    find_mob=1;
                    temp_mob=mobs[k];
                    break;
                }
            }
            reward temp_reward;
            bool find_reward=0;
            for(int k=0;k<reward_count;k++){
                if(j==rewards[k].x-xx&&i==rewards[k].y-yy&&world==rewards[k].world){
                    find_reward=1;
                    temp_reward=rewards[k];
                    break;
                }
            }
            bool find_bullet=0;
            for(int k=0;k<bullets.size();k++){
                if(j==bullets[k].x-xx&&i==bullets[k].y-yy){
                    find_bullet=1;
                    break;
                }
            }
            if(j==20&&i==10){
                out+=squat?'_':'|';
                color[pos++]=(!hit?1:12);
            }else if(find_mob&&!gr["nm"]){
                out+=temp_mob.name;
                color[pos++]=(!temp_mob.hit?mob_color[temp_mob.can_shoot]:12);
            }else if(j==21&&i==10&&is_fighting&&facing){
                out+='>';
                color[pos++]=12;
            }else if(j==19&&i==10&&is_fighting&&!facing){
                out+='<';
                color[pos++]=12;
            }else if(find_bullet){
                out+=bullet_texture;
                color[pos++]=bullet_color;
            }else if(find_reward){
                out+=reward_texture;
                if(temp_reward.is_double){
                    color[pos++]=reward_color[rand()%2];
                }else{
                    color[pos++]=reward_color[0];
                }
            }else{
                out+=block_texture[view[i][j]];
                color[pos++]=block_color[view[i][j]][world];
            }
        }
        out+='\n';
        color[pos++]=7;
    }
    out+=add_color("金币:"+to_string(score),2,pos);
    out+=add_color("最终金币:"+to_string(end_score),2,pos);
    out+=add_color("血量:"+string(hp/10,'=')+string(10-(hp/10),'-'),4,pos);
    out+=add_color("帧率:"+to_string(fps),4,pos);
    out+=add_color("物资["+to_string(slot)+"]:("+block_name[{world,slot}]+')'+to_string(block[slot]),4,pos);
    out+=add_color("子弹量:"+to_string(bullet_count),4,pos);
    out+=add_color("坐标  x:"+to_string(x)+"  y:"+to_string(y),4,pos);
    out.pop_back(); 
    string last_color="";
    for(int i=0;i<820;i++){
        string this_color=get_color(color[i],1,i==place_x*41+place_y,1);
        if(this_color!=last_color)final_out<<this_color,last_color=this_color;
        final_out<<out[i];
    }
    last_color="";
    for(int i=820;i<out.length();i++){
        string this_color=get_color(color[i],0,0,1);
        unsigned char c=out[i];
        if(this_color!=last_color)final_out<<this_color,last_color=this_color;
        if(c<0x80){
            final_out<<out[i];
        }else if((c&0xE0)==0xC0){
            final_out<<out[i]<<out[i+1];
            i+=1;
        }else if((c&0xF0)==0xE0){
            final_out<<out[i]<<out[i+1]<<out[i+2];
            i+=2;
        }else if((c&0xF8)==0xF0){
            final_out<<out[i]<<out[i+1]<<out[i+2]<<out[i+3];
            i+=3;
        }
    }
    clear(1);
    cout<<final_out.str();
    cout.flush();
}
bool move(){
    total_fps++;
    if(!(total_fps%100))save(name);
    for(int i=99;i>=0;i--){
        for(int j=scw-1;j>=0;j--){
            if(dt(j,i,world)==4){
                if(dt(j,i+1,world)!=0&&dt(j,i+1,world)!=4){
                    if(dt(j-1,i,world)!=4&&dt(j-1,i,world)==0)dt(j-1,i,world)=4,j--;
                    if(dt(j+1,i,world)!=4&&dt(j+1,i,world)==0)dt(j+1,i,world)=4;
                }else if(dt(j,i+1,world)!=4&&dt(j,i+1,world)==0)dt(j,i+1,world)=4;
            }
        }
    }
    if(score>1000&&!plr_to_nw){
        if(x!=scw-1)dt(x+1,y,world)=7,plr_to_nw=1;
        else dt(x-1,y,world)=7,plr_to_nw=1;
    }
    if(dt(x,y,world)==7&&x>=0&&y>=0&&x<scw&&y<sch){
        if(world==0)world=1;
        else world=0;
        dt(x,y,!world)=0;
        if(x!=scw-1)dt(x+1,y,world)=7;
        else dt(x-1,y,world)=7;
    }
    if(end_score>=20&&!can_summon_boss){
        mob a={};
        a.hp=1000;
        a.x=x;
        a.y=y;
        a.name='+';
        a.can_shoot=1;
        a.max_hp=1000;
        boss_idx=mobs.size();
        mobs.push_back(a);
        can_summon_boss=1;
    }
    if(boss_idx<mobs.size()&&mobs[boss_idx].name=='+'&&mobs[boss_idx].hp<=0&&!win){
        dt(mobs[boss_idx].x,mobs[boss_idx].y,world)=7;
        mobs.erase(mobs.begin()+boss_idx);
        boss_idx=-1;
        clear();
        cout<<"          你通关了 Mycraft\n       版本:1.6.3   作者:123";
        win=1;
        sleep_ms(4000);
    }
    for(int i=0;i<mobs.size();i++){
        if(facing==0&&mobs[i].x==x-1&&mobs[i].y==y&&is_fighting&&!gr["nm"]&&mobs[i].hp>0)mobs[i].hp-=attack_power;
        if(facing==1&&mobs[i].x==x+1&&mobs[i].y==y&&is_fighting&&!gr["nm"]&&mobs[i].hp>0)mobs[i].hp-=attack_power;
        if(mobs[i].hp<=0&&dt(mobs[i].x,mobs[i].y,world)==5&&!gr["nm"])mobs[i].y=rand()%sch,mobs[i].x=rand()%scw;
        if(!(total_fps%5)&&!gr["nm"]&&mobs[i].hp<mobs[i].max_hp)mobs[i].hp++;
        if(mobs[i].x==mobs[i].target_x&&mobs[i].y==mobs[i].target_y&&!gr["nm"]){
            int xx=mobs[i].x+((rand()%21)-10),yy=mobs[i].y+((rand()%21)-10);
            int ma=1000;
            while(dt(xx,yy,world)==6&&ma--)xx=mobs[i].x+((rand()%21)-10),yy=mobs[i].y+((rand()%21)-10);
            mobs[i].target_x=xx;
            mobs[i].target_y=yy;
        }
        if(((abs(x-mobs[i].x)<=10&&abs(y-mobs[i].y)<=10)||mobs[i].name=='+')&&!gr["cm"]&&dt(x,y,world)!=6&&dt(x,y,world)!=9)mobs[i].target_x=x,mobs[i].target_y=y;
        if(mobs[i].target_x<=0)mobs[i].target_x=0;
        if(mobs[i].target_x>scw)mobs[i].target_x=scw-1;
        if(mobs[i].target_y<=0)mobs[i].target_y=0;
        if(mobs[i].target_y>sch)mobs[i].target_y=sch-1;
        if(total_fps%2&&!gr["nm"]&&mobs[i].hp>0){
            if(mobs[i].x<mobs[i].target_x&&abs(mobs[i].x-mobs[i].target_x)>=abs(mobs[i].y-mobs[i].target_y))mobs[i].x++;
            if(mobs[i].x>mobs[i].target_x&&abs(mobs[i].x-mobs[i].target_x)>=abs(mobs[i].y-mobs[i].target_y))mobs[i].x--;
            if(mobs[i].y<mobs[i].target_y&&abs(mobs[i].y-mobs[i].target_y)>=abs(mobs[i].x-mobs[i].target_x))mobs[i].y++;
            if(mobs[i].y>mobs[i].target_y&&abs(mobs[i].y-mobs[i].target_y)>=abs(mobs[i].x-mobs[i].target_x))mobs[i].y--;
        }
        if(dt(mobs[i].x,mobs[i].y,world)==5&&!gr["nm"]&&mobs[i].hp>0)mobs[i].hp-=10;
        if(dt(mobs[i].x,mobs[i].y,world)==4&&world==1&&!gr["nm"]&&mobs[i].hp>0)mobs[i].hp-=5;
        if(dt(mobs[i].x,mobs[i].y,world)==4&&world==0&&!gr["nm"]&&mobs[i].hp>0)mobs[i].hp-=2;
        if(mobs[i].can_shoot&&!(total_fps%10)&&rand()%2&&!gr["nm"]&&mobs[i].hp>0)bullets.push_back({mobs[i].x,mobs[i].y,mobs[i].x<x,string(1,mobs[i].name)});
    }
    if(total_fps%2)hp++;
    if(hp>=100)hp=100;
    if(!(total_fps%4)&&dt(x,y,world)==4&&world==0)hp-=3,die="你在水里窒息而亡";
    if(dt(x,y,world)==4&&world==1)hp-=5,die="你试图在岩浆里游泳";
    if(dt(x,y,world)==5)hp-=10,die="你被地刺扎死了";
    for(int i=0;i<mobs.size();i++)if(x==mobs[i].x&&y==mobs[i].y&&!gr["cm"]&&!gr["nm"]&&!squat&&mobs[i].hp>0)hp-=5,die="你被"+string(1,mobs[i].name)+"杀死了";
    if(y>120)hp-=5,die="你掉入了虚空";
    if(hp<=0&&mode==1){
        clear();
        slowly_type(die,100);
        sleep_ms(1000);
        x=rand()%scw;
        y=rand()%sch;
        while(dt(x,y,world)==1||dt(x,y,world)==5||dt(x,y+1,world)!=1){
            x=rand()%scw;
            y=rand()%sch;
        }
        return 1;
    }
    if(hp<=0&&mode==2){
        remove((name+".mycraftsave").c_str());
        clear();
        slowly_type(die+"\n很遗憾，你丢失了极限世界",100);
        exit(0);
    }
    for(int i=0;i<bullets.size();i++){
        if(bullets[i].facing!=-1&&bullets[i].x>-30&&bullets[i].x<230)bullets[i].x+=(bullets[i].facing?1:-1);
    }
    for(int i=0;i<bullets.size();i++){
        bool ok=0;
        for(int j=0;j<mobs.size();j++){
            if(bullets[i].x==mobs[j].x&&bullets[i].y==mobs[j].y&&mobs[j].hp>0&&!gr["nm"]&&bullets[i].name=="player"){
                bullets.erase(bullets.begin()+i);
                mobs[j].hp-=(attack_power*3)>>1;
                ok=1;
                break;
            }
        }
        if(!ok&&bullets[i].x==x&&bullets[i].y==y&&bullets[i].name!="player"){
            die="你被"+bullets[i].name+"用子弹射杀了"; 
            bullets.erase(bullets.begin()+i);
            i--;
            hp-=30;
        }
    }
    for(int i=0;i<bullets.size();i++){
        if(bullets[i].x<=-30||bullets[i].x>=230){
            bullets.erase(bullets.begin()+i);
            i--; 
        }
    }
    if(hp<last_hp){
        hit=1;
        hp+=round(double(last_hp-hp)*(double)(100-defense_power)/100.);
    }
    else hit=0;
    last_hp=hp;
    for(int i=0;i<mobs.size();i++){
        if(mobs[i].hp<mobs[i].last_hp)mobs[i].hit=1;
        else mobs[i].hit=0;
        mobs[i].last_hp=mobs[i].hp;
    }
    return 0;
}
bool load(){
    if(kd(VK_RIGHT))place_y++;
    if(kd(VK_LEFT))place_y--;
    if(kd(VK_DOWN))place_x++;
    if(kd(VK_UP))place_x--;

    if(place_x<0)place_x=0;
    if(place_y<0)place_y=0;
    if(place_x>19)place_x=19;
    if(place_y>39)place_y=39;

    for(int i=0;i<block_type_count;i++)if(kd(0x60+i))slot=i;

    for(int i=0;i<block_type_count;i++)if(kd(to_string(i)[0])&&gr["cm"]&&x>=0&&y>=0&&x<scw&&y<sch)dt(x-20+place_y,y-10+place_x,world)=i;

    if(kd('0')&&!gr["cm"]&&block[0]&&dt(x-20+place_y,y-10+place_x,world)!=0&&x-20+place_y>=0&&y-10+place_x>=0&&x-20+place_y<scw&&y-10+place_x<sch)block[dt(x-20+place_y,y-10+place_x,world)]++,dt(x-20+place_y,y-10+place_x,world)=0,block[0]--;
    for(int i=1;i<block_type_count;i++)if(kd(to_string(i)[0])&&!gr["cm"]&&block[i]&&dt(x-20+place_y,y-10+place_x,world)!=i&&x-20+place_y>=0&&y-10+place_x>=0&&x-20+place_y<scw&&y-10+place_x<sch)dt(x-20+place_y,y-10+place_x,world)=i,block[i]--;

    if(kd(key_pos["jump"])&&(dt(x,y+1,world)==1||dt(x,y,world)==4||dt(x,y,world)==3)&&!gr["cm"]&&dt(x,y-1,world)!=4&&dt(x,y-1,world)!=3)is_jump=1,jump_height=y-7;
    if(kd(key_pos["jump"])&&gr["cm"])y-=1;

    if(dt(x,y+1,world)!=1&&!is_jump&&!gr["cm"]&&y<sch)y++;
    if(squat&&dt(x,y+1,world)!=1&&!is_jump&&!gr["cm"]&&y<sch)y++;

    if(y>=sch&&!gr["cm"])y++;
    
    if(kd(key_pos["jump"])&&!gr["cm"]&&dt(x,y-1,world)==4)y-=1;
    if(kd(key_pos["jump"])&&!gr["cm"]&&dt(x,y-1,world)==4)y-=1;
    
    if(kd(key_pos["jump"])&&!gr["cm"]&&dt(x,y-1,world)==3)y-=1;
    if(kd(key_pos["jump"])&&!gr["cm"]&&dt(x,y-1,world)==3)y-=1;

    if(kd(key_pos["left"])&&dt(x-1,y,world)!=1&&!gr["cm"])x--,facing=0;
    if(kd(key_pos["left"])&&gr["cm"])x--,facing=0;

    if(kd(key_pos["right"])&&dt(x+1,y,world)!=1&&!gr["cm"])x++,facing=1;
    if(kd(key_pos["right"])&&gr["cm"])x++,facing=1;

    check_coin();

    if(kd(key_pos["speed_up"])&&kd(key_pos["left"])&&dt(x-1,y,world)!=1&&!gr["cm"])x--,facing=0;
    if(kd(key_pos["speed_up"])&&kd(key_pos["left"])&&gr["cm"])x--,facing=0;

    if(kd(key_pos["speed_up"])&&kd(key_pos["right"])&&dt(x+1,y,world)!=1&&!gr["cm"])x++,facing=1;
    if(kd(key_pos["speed_up"])&&kd(key_pos["right"])&&gr["cm"])x++,facing=1;

    if(kd(key_pos["fight"]))is_fighting=1;
    if(!kd(key_pos["fight"]))is_fighting=0;

    if(kd(key_pos["squat"])&&!gr["cm"])squat=1;
    if(!kd(key_pos["squat"])&&!gr["cm"])squat=0;
    if(kd(key_pos["squat"])&&gr["cm"])y++;

    if(x>=scw)x=scw-1;
    if(x<=-1)x=0;

    if(kd(VK_ESCAPE))return 1;

    if(y<jump_height)is_jump=0;
    
    if(is_jump==1){
        if(dt(x,y-1,world)==1)is_jump=0;
        else y--;
    }

    if(dt(x,y,world)==4)is_jump=0,jump_height=0;

    if(kd(key_pos["shop_buy"])&&dt(x,y,world)==6){
        int pri[]={2,3,5,6,3,4,5,1000,300,10};
        clear();
        while(kd(key_pos["shop_buy"]))sleep_ms(10);
        cout<<"商店\n";
        for(int i=0;i<block_type_count;i++)cout<<block_name[{world,i}].c_str()<<':'<<pri[i]<<"金币("<<i<<")\n";
        while(_kbhit())_getch();
        show_cursor();
        int aa,bb;
        cin>>aa>>bb;
        hide_cursor();
        if(cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            clear();
            cout<<"输入无效！\n";
            sleep_ms(1000);
        }else if(aa>=0&&aa<block_type_count&&bb>=0&&bb<=(INT_MAX/pri[aa])-10){
            if(score<pri[aa]*bb)cout<<"赶出去!",sleep_ms(1000);
            else score-=pri[aa]*bb,block[aa]+=bb;
        }
    }
    
    if(kd(key_pos["shop_sell"])&&dt(x,y,world)==6){
        int pri[]={2,3,5,6,3,4,5,1000,300,10};
        clear();
        while(kd(key_pos["shop_sell"]))sleep_ms(10);
        cout<<"收货\n";
        for(int i=0;i<block_type_count;i++)cout<<block_name[{world,i}].c_str()<<':'<<pri[i]<<"金币("<<i<<")\n";
        while(_kbhit())_getch();
        show_cursor();
        int aa,bb;
        cin>>aa>>bb;
        hide_cursor();
        if(cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            clear();
            cout<<"输入无效！\n";
            sleep_ms(1000);
        }else if(aa>=0&&aa<block_type_count&&bb>=0&&bb<=(INT_MAX/pri[aa])-10){
            if(block[aa]<bb)cout<<"赶出去!",sleep_ms(1000);
            else score+=pri[aa]*bb,block[aa]-=bb;
        }
    }

    if(kd(key_pos["shop_buy"])&&dt(x,y,world)==9){
        clear();
        while(kd(key_pos["shop_buy"]))sleep_ms(10);
        while(_kbhit())_getch();
        int attack_pri=(1<<attack_shop_buy_count)*100;
        int attack_add_power=attack_shop_buy_count*10+10;
        int defense_pri=(1<<defense_shop_buy_count)*100;
        int defense_add_power=50/pow(2,defense_shop_buy_count+1);
        cout<<"选择:\n";
        cout<<"1.需要消耗"<<attack_pri<<"金币才能升到下一级(增加"<<attack_add_power<<"点攻击力)\n";
        cout<<"2.需要消耗"<<defense_pri<<"金币才能升到下一级(增加"<<defense_add_power<<"%伤害吸收)\n";
        cout<<"3.子弹3金币一颗\n";
        cout<<"4.退出";
        char in=_getch();
        while(!(in=='1'||in=='2'||in=='3'||in=='4')){
            clear();
            cout<<"请按1、2、3或4";
            sleep_ms(1000);
            clear();
            cout<<"选择:\n";
            cout<<"1.需要消耗"<<attack_pri<<"金币才能升到下一级(增加"<<attack_add_power<<"点攻击力)\n";
            cout<<"2.需要消耗"<<defense_pri<<"金币才能升到下一级(增加"<<defense_add_power<<"%伤害吸收)\n";
            cout<<"3.子弹3金币一颗\n";
            cout<<"3.退出";
            in=_getch();
        }
        if(in=='1'){
            if(score>=attack_pri){
                score-=attack_pri;
                attack_shop_buy_count++;
                attack_power+=attack_add_power;
            }else{
                clear();
                cout<<"赶出去!";
                sleep_ms(1000);
            }
        }
        if(in=='2'){
            if(score>=defense_pri){
                score-=defense_pri;
                defense_shop_buy_count++;
                defense_power-=defense_add_power;
            }else{
                clear();
                cout<<"赶出去!";
                sleep_ms(1000);
            }
        }
        if(in=='3'){
            clear();
            cout<<"请输入数量:";
            int x;
            cin>>x;
            if(cin.fail()){
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                clear();
                cout<<"输入无效！\n";
                sleep_ms(1000);
            }else if(score>=3*x){
                score-=3*x;
                bullet_count+=x;
            }else{
                clear();
                cout<<"赶出去!";
                sleep_ms(1000);
            }
        }
    }

    if(kd(key_pos["cmd"])&&mode==2){
        clear();
        cout<<"极限世界不能使用指令\n";
        sleep_ms(2000);
    }
    
    if(kd(key_pos["shoot"])){
        if(bullet_count||gr["cm"]){
            if(!gr["cm"])bullet_count--;
            bullets.push_back({x,y,facing,"player"});
        }
    }
    
    if(kd(key_pos["cmd"])&&mode==1){
        clear();
        while(_kbhit())_getch();
        while(kd(key_pos["cmd"]))sleep_ms(10);
        cout<<"请输入指令(用help查看帮助):\n";
        show_cursor();
        string a;
        cin>>a;
        if(cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            clear();
            cout<<"输入无效！\n";
            sleep_ms(1000);
        }else{
            if(a=="gr"){
                string f;
                int ff;
                cin>>f>>ff;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else if(gr.count(f))gr[f]=ff;
                
            }
            if(a=="grl"){
                for(auto i:gr)cout<<i.first<<' '<<i.second<<'\n';
                _getch();
            }
            if(a=="fill"){
                int num;
                cin>>num;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else if(num>=0&&num<block_type_count){
                    for(int i=1;i<sch-1;i++){
                        for(int j=0;j<scw;j++){
                            dt(j,i,world)=num;
                        }
                    }
                }
            }
            if(a=="give"){
                int a,b;
                cin>>a>>b;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else if(a>=0&&a<block_type_count&&b>0){
                    block[a]+=b;
                }
            }
            if(a=="write"){
                cout<<"请输入存档名字：";
                string a;
                cin>>a;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else{
                    save(a);
                    cout<<"存档成功！\n";
                    sleep_ms(1000);
                }
            }
            if(a=="load"){
                cout<<"请输入存档名字：";
                string a;
                cin>>a;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else{
                    load(a);
                    cout<<"读档成功！\n";
                    sleep_ms(1000);
                }
            }
            if(a=="ovw"){
                if(world==1){
                    dt(x+1,y,world)=7;
                    world=0;
                }
            }
            if(a=="nw"){
                if(world==0){
                    dt(x+1,y,world)=7;
                    world=1;
                }
            }
            if(a=="kill"){
                hp=-100;
                die="你被命令杀死了";
            }
            if(a=="seed"){
                cout<<"种子:"<<seed;
                while(!_kbhit());
            }
            if(a=="tp"){
                int xx,yy;
                cin>>xx>>yy;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    clear();
                    cout<<"输入无效！\n";
                    sleep_ms(1000);
                }else if(xx>=0&&xx<scw&&yy>=0&&yy<sch){
                    x=xx;
                    y=yy;
                }else{
                    cout<<"坐标越界！\n";
                    sleep_ms(1000);
                }
            }
            if(a=="help"){
                cout<<R"(
gr      游戏规则 值         修改游戏规则
grl                     列出所有游戏规则
full    方块类型      把玩家所在世界填充
give    方块类型 数量       给予玩家方块
write   存档名                      存档
load    存档名                      读档
ovw                     传送玩家至主世界
nw                        传送玩家至下界
kill                在所有模式下杀死玩家
seed                            查看种子
tp      x坐标   y坐标 传送至:x坐标,y坐标
help                            查看帮助 
)";
                _getch();
            }
            hide_cursor();
            clear();
        }
    }
    return 0;
}
int main(){
    enable_ansi();
    hide_cursor();
    system("chcp 65001 > nul");
    system("mode con cols=40 lines=27");
    for(auto i:zh_to_color)color_to_zh[i.second]=i.first;
    cout<<"欢迎来到Mycraft\n";
    cout<<"选择：\n";
    cout<<"1.创建游戏\n";
    cout<<"2.读取存档\n";
    int a1;
    a1=_getch()-'0';
    if(a1==1){
        show_cursor();
        cout<<"请输入世界名称：";
        getline(cin,name);
        cout<<"输入种子(留空以随机生成种子):";
        getline(cin,seed);
        if(seed==""){
            srand(time(0));
            string chars={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
            seed.resize(rand()%10+10);
            for(auto &i:seed)i=chars[rand()%chars.size()];
            hashed_seed=hash_str(seed);
            srand(hashed_seed);
        }else{
            hashed_seed=hash_str(seed);
            srand(hashed_seed);
        }
        hide_cursor();
        clear();
        cout<<R"(请输入游戏模式：
1.生存/创造模式
2.极限模式
)";
        mode=_getch()-'0';
        while(mode!=1&&mode!=2){
            clear();
            cout<<"请按1或2\n";
            sleep_ms(1000);
            clear();
            cout<<R"(请输入游戏模式：
1.生存/创造模式
2.极限模式
            )";
            mode=_getch()-'0';
        }
        randd();
    }else if(a1==2){
        show_cursor();
        cout<<"请输入世界名称：";
        getline(cin,name);
        hide_cursor();
        if(load(name)==1)return 0;
    }
    while(1){
        start:
        clear();
        cout<<"选择:\n";
        cout<<"1.开始游戏\n";
        cout<<"2.设置\n";
        cout<<"3.退出\n";
        int a=_getch()-'0';
        if(a==1){
            while(1){
                while(1){
                    long long s=get_ms();
                    print();
                    check_coin();
                    get_color(15);
                    if(load()){
                        while(_kbhit())_getch();
                        goto start;
                    }
                    if(move())break;
                    sleep_ms(max(1000./(target_fps*1.)+s-get_ms(),0.));
                    if(get_ms()-s==0)fps=target_fps;
                    else fps=1000/(get_ms()-s);
                }
                is_jump=0,hp=100,total_fps=0;
            }
        }else if(a==2){
            while(_kbhit())_getch();
            while(1){
                clear();
                cout<<"设置:\n";
                cout<<"1.帧率设置\n";
                cout<<"2.材质包加载\n";
                cout<<"3.查看材质包制作方式\n";
                cout<<"4.原版材质包（示例，能正常加载）\n";
                cout<<"5.按键设置\n";
                cout<<"6.退出\n";
                char a=_getch()-'0';
                if(a==1){
                    clear();
                    show_cursor();
                    while(_kbhit())_getch();
                    cout<<"请输入最大帧率:";
                    cin>>target_fps;
                    if(target_fps>1000||target_fps<=0){
                        clear();
                        cout<<"帧率在1~1000之间(包括)\n";
                        sleep_ms(1000);
                    }
                    if(cin.fail()||target_fps<=0){
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                        clear();
                        cout<<"输入无效！\n";
                        sleep_ms(1000);
                    }
                    hide_cursor();
                }else if(a==2){
                    while(_kbhit())_getch();
                    clear();
                    show_cursor();
                    cout<<"输入材质包路径：";
                    string path;
                    getline(cin,path);
                    hide_cursor();
                    ifstream fin(path);
                    if(fin){
                        string in;
                        int cnt=0;
                        while(fin>>in)cnt++;
                        if(cnt==9+block_type_count*2){
                            fin.clear();
                            fin.seekg(0);
                            getline(fin,block_texture);
                            string in_color;
                            for(int i=0;i<block_type_count;i++){
                                fin>>in_color;
                                block_color[i][0]=zh_to_color[in_color];
                            }
                            for(int i=0;i<block_type_count;i++){
                                fin>>in_color;
                                block_color[i][1]=zh_to_color[in_color];
                            }
                            getline(fin,mob_name_str);
                            getline(fin,mob_name_str);
                            if(mob_name_str.size())for(int i=0;i<mobs.size();i++)mobs[i].name=mob_name_str[rand()%mob_name_str.size()];
                            else{
                                clear();
                                cout<<"材质包格式错误";
                                continue;
                            }
                            for(int i=0;i<2;i++){
                                fin>>in_color;
                                mob_color[i]=zh_to_color[in_color];
                            }
                            fin>>bullet_texture>>in_color;
                            bullet_color=zh_to_color[in_color];
                            fin>>reward_texture;
                            for(int i=0;i<2;i++){
                                fin>>in_color;
                                reward_color[i]=zh_to_color[in_color];
                            }
                        }
                    }
                    fin.close();
                }else if(a==3){
                    clear();
                    cout<<"制作方式：\n";
                    cout<<"每个方块的贴图（"+to_string(block_type_count)+"个字符的字符串）\n";
                    cout<<"主世界方块的颜色"+to_string(block_type_count)+"个\n";
                    cout<<"地狱方块的颜色"+to_string(block_type_count)+"个\n";
                    cout<<"怪物贴图（任意字符串）\n";
                    cout<<"正常怪物的颜色 能发射子弹的怪物的颜色\n";
                    cout<<"子弹的贴图 子弹的颜色\n";
                    cout<<"非正常金币的贴图\n";
                    cout<<"正常的给予金币的金币的颜色\n";
                    cout<<"隐藏的给予金币的金币的颜色\n";
                    cout<<"所有颜色：深蓝、深绿、深青、深红、深粉、黄、深白、灰、蓝、绿、青、红、粉、黄、白";
                    int c=_getch();
                }else if(a==4){
                    clear();
                    cout<<block_texture<<'\n';
                    for(int i=0;i<block_type_count;i++)cout<<color_to_zh[block_color[i][0]]<<' ';
                    cout<<'\n';
                    for(int i=0;i<block_type_count;i++)cout<<color_to_zh[block_color[i][1]]<<' ';
                    cout<<'\n'<<mob_name_str<<'\n'<<color_to_zh[mob_color[0]]<<' '<<color_to_zh[mob_color[1]]<<'\n';
                    cout<<bullet_texture<<' '<<color_to_zh[bullet_color]<<'\n';
                    cout<<reward_texture<<'\n';
                    for(int i=0;i<2;i++)cout<<color_to_zh[reward_color[i]]<<'\n';
                    int c=_getch();
                }else if(a==5){
                    while(_kbhit())_getch();
                    show_cursor();
                    clear();
                    cout<<R"(固定键位：
esc:从游戏退出到设置界面
方向键:更改放方块的位置
数字键:放置物品
小键盘数字键:切换物品栏预览
)";
                    string out="非固定键位：\n";
                    for(auto i:key_pos)out+=i.first+":'"+string(1,i.second)+"'\n";
                    cout<<out;
                    cout<<"输入新键位(按上面顺序输入,大写,必须为可见字符(包括空格),不能和固定键位重合):";
                    string in;
                    getline(cin,in);
                    if(in.size()==key_pos.size()){
                        int cnt=0;
                        for(auto&i:key_pos)i.second=in[cnt],cnt++;
                    }
                    hide_cursor();
                }else if(a==6){
                    break;
                }else{
                    clear();
                    cout<<"请按1、2、3、4、5或6\n";
                    sleep_ms(1000);
                }
            }
        }else if(a==3){
            return 0;
        }else{
            clear();
            cout<<"请按1、2或3\n";
            sleep_ms(1000);
        }
    }
    return 0;
}
