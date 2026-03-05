#pragma once
// -------------------- 数据设计 --------------------
/*
    弹匣：
        magazine[i]表示子弹类型
        0为空位置
        1为真弹
        2为假弹
    如：magazine[3] = 1		表示[3]的位置是真弹
*/
int magazine[8];

//子弹伤害
int bullet_damage;

//真弹数量
int real;

//假弹数量
int fake;

//表示当前回合弹夹中的子弹实际数量（假弹也算子弹）
int bulletCount;

// 当前关卡（1/2/3）
int currentLevel;

// 当前关卡的当前回合
int currentRound;

// 道具结构体
typedef struct
{
    int id;             //道具id（1-小刀，2-放大镜，3-饮料，4-手铐，5 -香烟）
    char name[20];      // 道具名称
    bool isUsed;        // 1表示已使用，0表示未使用
}Prop;

//道具数组（0-小刀，1-放大镜，2-饮料，3-手铐，4-香烟）
Prop Props[5];

//要抽取的道具数
int propdraw_num;

// 角色（玩家/人机）结构体
typedef struct
{
    int hp;             // 当前血量
    int maxhp;           //最大血量
    int roleprops[8];      // 拥有的道具
    int propCount;      // 拥有的道具总数量
}Role;

//玩家信息
Role player;

//人机信息
Role bot;

//霰弹枪控制权 0表示玩家控制，1表示人机控制
bool roleTurn;

//行动次数
int actnums;

ExMessage msg = { 0 };

// -------------------- 数据设计 --------------------


// -------------------- service --------------------
/*
    负责人： -y

    功能：init：初始化游戏数据

        将弹匣的值初始化为0
        子弹伤害设为1
        真假弹设为0
        当前回合子弹实际数量设为0
        当前关卡设为1
        当前回合设为1
        初始化道具数组
        要抽取的道具数设为0;
        初始化角色信息（设为0）
        霰弹枪控制权设为0
        行动次数设为1

    参数：void

    返回值：void
*/
void init();

/*
    负责人：帅小伙

    功能：关卡初始化
        根据当前关卡数，清空角色道具，设置玩家和人机的血量，以及要抽取的道具数

        第一关：血量各 2 点
        第二关：血量各 4 点，2 个道具
        第三关：血量各 6 点，4 个道具

    参数：void

    返回值：void
*/
void level();

void show_level();

/*
    负责人：coke

    功能：按当前关卡及回合规则，设置真假子弹数

        第一关：
            第一回合：一真两假
            第二回合：三真两假
        第二关：
            第一回合：一真一假
            第二回合：两真两假
            第三回合：三真两假
            第四回合：三真三假
            第五回合：五真两假
            若还未结束则使用随机填充函数
        第三关：
            第一回合：一真两假
            第二回合：四真四假
            第三回合：三真两假
            第四回合：四真两假
            若还未结束则使用随机填充函数

    参数：void

    返回值：void
*/
void Bullet();

/*
    负责人：结灯

    功能：随机真假弹数量
        真弹数量范围（3-5）
        假弹数量范围（2-4）

    参数：void

    返回值：void
*/
void randomBullet();

/*
    负责人：结灯

    功能：根据要抽取的道具数抽取道具
        若道具数满则不再抽取

    参数：void

    返回值：void
*/
void draw_props();

/*
    负责人：GUY

    功能：根据真假子弹数填充子弹

    参数：void

    返回值：void
*/
void load_bullets();

/*
    负责人：GUY

    功能：打乱弹匣中的子弹（利用费雪 - 耶茨洗牌算法）

    参数：void

    返回值：void
*/
void shuffle();

/*
    负责人：lllllll

    功能：根据道具id触发对应道具效果

    参数：
        propid：道具的id
        index：数组索引

    返回值：void
*/
void prop_effect(int propid, int propbutton, int index);

/*
    负责人：lllllll

    功能：玩家射击逻辑

        选择射击目标：

                向自己开枪：

                    若为实弹：自身受 1 点伤害，霰弹枪控制权移交人机

                    若为空弹：无伤害，玩家可再次选择操作

                向人机开枪：

                    无论实弹 / 空弹，控制权均移交人机

                    实弹造成 1 点伤害，空弹无伤害

    参数：
        rolebutton：角色按钮返回值
        index：数组索引

    返回值：void
*/
void player_shoot(int rolebutton, int index);

/*
    负责人：九山

    功能：人机行动逻辑

    参数：void

    返回值：void
*/
void bot_action(int index);
// -------------------- service --------------------



// -------------------- view -----------------------
/*
    负责人：Ragland

    功能：menuView：展示选项，玩家可以在这里选择开始游戏,退出游戏(鼠标点击)
        while(1)
        {
            1.展示选项
            2.用户选择
            3.根据选择进行对应处理
                开始游戏：调用gameView();
                退出游戏
        }

    参数：void

    返回值：void

*/
void menuView();

/*
    负责人: 华子
    功能: 打印游戏地图（墙，霰弹枪，恶魔，我，道具栏）
    参数: void
    返回值: void
*/
void gameMap();

/*
    负责人：华子
    功能：根据角色拥有的道具在道具栏中打印对应道具名称
    参数：void
    返回值：void
*/
void me_show_props();
void evil_show_props();

/*
    负责人：华子
    功能：在指定处展示子弹
    参数：void
    返回值：void
*/
void show_bullets();

void show_hp();

/*
    负责人：华子
    功能：在道具栏处设置按钮(返回值0-7)
    参数：void
    返回值：返回对应道具栏位置的值
*/
int pr_button();

/*
    负责人：华子
    功能：在我（0），恶魔（1）处设置按钮
    参数：void
    返回值：void
*/
//int role_button();

/*
    负责人: Ragland
    功能: winView:
        打印游戏胜利界面  用户可以按任意键(使用getch函数)退出当前界面
    参数: void
    返回值: void
*/
void winView();

/*
    负责人: Ragland
    功能: winView:
        打印游戏失败界面  用户可以按任意键(使用getch函数)退出当前界面
    参数: void
    返回值: void
*/
void loseView();

/*
     Ragland
     功能:用于确认鼠标是否在按键区域
*/
bool area(int mx, int my, int x1, int y1, int x2, int y2);

/*
  Ragland
  用于绘制按钮,并且判断是否按下
*/
bool button(int x1, int y1, int x2, int y2, const char* text);

/*
    用于关闭音乐
*/
void stopMusic(int x);

/*
      Ragland
      用于播放音乐
*/
void openMusic(int x);

/*
   Ragland
   用于加载音乐
*/
void loadMusic();

/*
   Ragland
   用于调节音量大小
*/
void musicControl();

/*
打印文字
*/
void text(int x, int y, const char* text);

/*
    负责人: 九山
    功能: gameView: 游戏界面整合
    参数: void
    返回值: void
*/
void gameView();
// -------------------- view -----------------------





