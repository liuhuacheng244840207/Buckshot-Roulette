#include"game.h"

void init()
{
    //初始化弹匣值
    for (int i = 0; i < 8; i++)
    {
        magazine[i] = 0;
    }

    //初始化子弹伤害
    bullet_damage = 1;

    //初始化真假子弹数量
    real = 0;
    fake = 0;

    //当前子弹实际数量
    bulletCount = 0;

    //初始化道具数组
    Props[0] = { 1,"小刀",0 };
    Props[1] = { 2,"放大镜",0 };
    Props[2] = { 3,"饮料",0 };
    Props[3] = { 4,"手铐",0 };
    Props[4] = { 5,"香烟",0 };

    //当前关卡与回合;
    currentRound = 1;
    currentLevel = 1;

    //抽取的道具数设置
    propdraw_num = 0;

    //初始化角色的信息

    player.hp = 0;//玩家

    bot.hp = 0;//恶魔

    //初始化霰弹枪控制权
    roleTurn = 0;

    //初始化移动数目
    actnums = 1;

    srand(time(NULL));
}

void level()
{
    //(玩家/人机)信息
    if (currentLevel == 1)
    {
        //给血量和拥有的道具总数量赋值
        player.maxhp = 2;              //玩家初始血量为2
        player.hp = player.maxhp;
        bot.maxhp = 2;                 //人机初始血量为2
        bot.hp = bot.maxhp;
    }
    else if (currentLevel == 2)
    {
        //给血量和拥有的道具总数量赋值
        player.maxhp = 4;              //玩家初始血量为4
        player.hp = player.maxhp;
        bot.maxhp = 4;                 //人机初始血量为4
        bot.hp = bot.maxhp;
        propdraw_num = 2;          //要抽取的道具数为2
    }
    else
    {
        //给血量和拥有的道具总数量赋值
        player.maxhp = 6;              //玩家初始血量为6
        player.hp = player.maxhp;
        bot.maxhp = 6;                 //人机初始血量为6
        bot.hp = bot.maxhp;
        propdraw_num = 4;           //要抽取的道具数为4
        // 清空玩家的道具栏
        for (int i = 0; i < 8; i++) {
            player.roleprops[i] = 0;
            bot.roleprops[i] = 0;
        }
    }
}

void Bullet()
{
    if (currentLevel == 1) // 根据当前关卡和回合设置子弹数量
    {
        switch (currentRound)
        {
        case 1:
            real = 1;
            fake = 2;
            break;
        case 2:
            real = 3;
            fake = 2;
            break;
        }
    }
    else if (currentLevel == 2) // 根据当前关卡和回合设置子弹数量
    {
        switch (currentRound)
        {
        case 1:
            real = 1;
            fake = 1;
            break;
        case 2:
            real = 2;
            fake = 2;
            break;
        case 3:
            real = 3;
            fake = 2;
            break;
        case 4:
            real = 3;
            fake = 3;
            break;
        case 5:
            real = 5;
            fake = 2;
            break;
        default:
            randomBullet();// 超过预设回合，使用随机填充
            break;
        }
    }

    else // 根据当前关卡和回合设置子弹数量
    {
        switch (currentRound)
        {
        case 1:
            real = 1;
            fake = 2;
            break;
        case 2:
            real = 4;
            fake = 4;
            break;
        case 3:
            real = 3;
            fake = 2;
            break;
        case 4:
            real = 4;
            fake = 2;
            break;
        default:
            randomBullet();// 超过预设回合，使用随机填充
            break;
        }
    }
}

void randomBullet()
{
    real = rand() % 3 + 3;
    fake = rand() % 3 + 2;
}

void draw_props()
{
    int i = 0;
    int player_count = 0;
    int num1 = 0;
    while (player_count != propdraw_num)
    {
        if (player.roleprops[i] == 0)
        {
            num1 = rand() % 5 + 1;
            player.roleprops[i] = num1;
            player_count++;
        }

        if (i == 7)
            break;
        else
            i++;
    }

    int j = 0;
    int bot_count = 0;
    int num2 = 0;
    while (bot_count != propdraw_num)
    {
        if (bot.roleprops[j] == 0)
        {
            num2 = rand() % 5 + 1;
            bot.roleprops[j] = num2;
            bot_count++;
        }

        if (j == 7)
            break;
        else
            j++;
    }
}

void load_bullets()
{
    for (int i = 0; i < real; i++)
    {
        magazine[i] = 1;
    }
    for (int i = real; i < real + fake; i++)
    {
        if (i == 8)
            break;
        magazine[i] = 2;
    }
}

void shuffle()
{
    // 从最后一个元素开始，依次与前面随机位置的元素交换
    for (int i = 7; i > 0; i--)
    {
        // 生成0到i之间的随机索引
        int j = rand() % (i + 1);

        // 交换arr[i]和arr[j]
        int temp = magazine[i];
        magazine[i] = magazine[j];
        magazine[j] = temp;
    }
}

void prop_effect(int propid, int propbutton, int index)
{
    BeginBatchDraw();
    settextcolor(BLACK);
    setfillcolor(WHITE);
    settextstyle(WORDSIZE, 0, "宋体");
    while (1)
    {
        //小刀
        if (propid == 1)
        {
            if (Props[0].isUsed == 0)
            {
                openMusic(9);
                bullet_damage++;
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "使用了小刀！");
                EndBatchDraw();
                player.roleprops[propbutton] = 0;
                Props[0].isUsed = 1;
                me_show_props();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            else
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "已经用过了！");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            break;
        }

        //放大镜
        if (propid == 2)
        {
            openMusic(13);
            player.roleprops[propbutton] = 0;
            me_show_props();
            BeginBatchDraw();
            settextstyle(WORDSIZE, 0, "宋体");
            outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "使用了放大镜");
            EndBatchDraw();
            Sleep(3000);
            BeginBatchDraw();
            openMusic(12);
            solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            EndBatchDraw();
            if (magazine[index] == 1)
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "当前子弹为：实弹");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            else
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "当前子弹为：空弹");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            break;
        }


        //饮料
        if (propid == 3)
        {
            openMusic(8);
            BeginBatchDraw();
            settextstyle(WORDSIZE, 0, "宋体");
            outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "使用了饮料");
            EndBatchDraw();
            player.roleprops[propbutton] = 0;
            me_show_props();
            Sleep(3000);
            BeginBatchDraw();
            openMusic(7);
            solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            EndBatchDraw();
            if (magazine[index] == 1)
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "退出了子弹：实弹");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            else
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "退出了子弹：空弹");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            bulletCount--;
            magazine[index] = 0;
            break;
        }

        //手铐
        if (propid == 4)
        {
            if (Props[3].isUsed == 0)
            {
                openMusic(11);
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "使用了手铐！");
                EndBatchDraw();
                Props[3].isUsed = 1;
                player.roleprops[propbutton] = 0;
                me_show_props();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
                break;
            }
            else
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "已经用过了！");
                Sleep(3000);
                fillrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            }
        }

        //香烟
        if (propid == 5)
        {
            if (player.hp < player.maxhp)
            {
                openMusic(10);
                player.hp++;
                show_hp();
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "使用了香烟！");
                EndBatchDraw();
                player.roleprops[propbutton] = 0;
                me_show_props();
                Sleep(3000);
                BeginBatchDraw();
                openMusic(16);
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            else
            {
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "血量已满");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
            }
            break;
        }
    }
}

void player_shoot(int rolebutton, int index)
{
    BeginBatchDraw();
    settextcolor(BLACK);

    settextstyle(WORDSIZE, 0, "宋体");
    //点击“我”向自己开枪：

    if (rolebutton == 9)
    {

        outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "向自己开枪！");
        EndBatchDraw();  // 立即刷新
        Sleep(3000);

        // 清除旁白
        solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
        EndBatchDraw();
        //如果是真子弹
        if (magazine[index] == 1)
        {

            openMusic(14);//实弹
            outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "被实弹击中！");
            EndBatchDraw();
            Sleep(2500);
            BeginBatchDraw();
            player.hp -= bullet_damage;//血量减一
            show_hp();
            openMusic(15);
            setfillcolor(WHITE);
            solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            EndBatchDraw();
            magazine[index] = 0;
            bulletCount--;//总子弹数量减一
            if (Props[3].isUsed == 0)
                roleTurn = 1;//控制权交给人机
            else
                Props[3].isUsed = 0;

        }
        //如果是假子弹
        else
        {
            openMusic(18);
            outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "打出空弹！");
            EndBatchDraw();
            Sleep(3000);
            BeginBatchDraw();
            setfillcolor(WHITE);
            solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            EndBatchDraw();
            magazine[index] = 0;
            bulletCount--;//总子弹数量减一

        }
    }
    //点击“恶魔”向敌人开枪：

    if (rolebutton == 8)
    {
        outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "向恶魔开枪！");
        EndBatchDraw();  // 立即刷新
        Sleep(3000);

        // 清除旁白
        BeginBatchDraw();
        solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
        EndBatchDraw();//如果是真子弹
        if (magazine[index] == 1)
        {
            openMusic(14);//实弹
            outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "被实弹击中！");
            Sleep(2500);
            EndBatchDraw();
            BeginBatchDraw();
            setfillcolor(WHITE);
            solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
            EndBatchDraw();
            bot.hp -= bullet_damage;//血量减少
            show_hp();
            openMusic(15);
            Sleep(1000);
            magazine[index] = 0;
            bulletCount--;//总子弹数量减一
            if (Props[3].isUsed == 0)
                roleTurn = 1;//控制权交给人机
            else
                Props[3].isUsed = 0;

        }
        //如果是假子弹
        else
        {
            openMusic(18);
            outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "打出空弹！");
            EndBatchDraw();
            Sleep(3000);
            BeginBatchDraw();
            setfillcolor(WHITE);
            solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
            EndBatchDraw();
            magazine[index] = 0;
            bulletCount--;//总子弹数量减一
            if (Props[3].isUsed == 0)
                roleTurn = 1;//控制权交给人机
            else
                Props[3].isUsed = 0;

        }
    }
    EndBatchDraw();
    bullet_damage = 1;//重置子弹伤害

}

void bot_action(int index)
{
    BeginBatchDraw();
    settextcolor(BLACK);
    setfillcolor(WHITE);
    settextstyle(WORDSIZE, 0, "宋体");
    // 道具使用逻辑（优先使用有利道具）
    for (int i = 0; i < 8; i++)
    {
        int propId = bot.roleprops[i];
        if (propId == 0) continue; // 跳过空道具位

        // 使用香烟回血
        if (propId == 5)
        {
            if (bot.hp < bot.maxhp)
            {
                openMusic(10);
                bot.hp++;
                show_hp();
                bot.roleprops[i] = 0; // 移除道具
                evil_show_props();
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "使用了香烟！");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                openMusic(15);
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
            }
        }

        // 使用小刀（当前为实弹时）
        else if (propId == 1 && !Props[0].isUsed) {
            // 随机判断是否使用（30%概率）
            if (rand() % 10 < 3) {
                openMusic(9);
                bullet_damage = 2;
                Props[0].isUsed = true;
                bot.roleprops[i] = 0;
                evil_show_props();
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "使用了小刀!");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
            }
        }

        // 使用手铐（获取额外行动机会）
        else if (propId == 4 && !Props[3].isUsed) {
            // 随机判断是否使用（20%概率）
            if (rand() % 10 < 2)
            {
                openMusic(11);
                roleTurn = 1;
                Props[3].isUsed = true;
                bot.roleprops[i] = 0;
                evil_show_props();
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "使用了手铐!");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
            }
        }

        // 使用放大镜查看当前子弹
        else if (propId == 2) {
            // 随机判断是否使用（40%概率）
            if (rand() % 10 < 4) {
                openMusic(13);
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "使用了放大镜!");
                EndBatchDraw();
                bot.roleprops[i] = 0;
                evil_show_props();
                Sleep(3000);
                BeginBatchDraw();
                openMusic(12);
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
            }
        }

        // 使用饮料跳过当前子弹
        else if (propId == 3) {
            // 随机判断是否使用（30%概率）
            if (rand() % 10 < 3) {
                openMusic(8);
                magazine[index] = 0; // 移除当前子弹
                bulletCount--;
                bot.roleprops[i] = 0;
                evil_show_props();
                Sleep(500);
                openMusic(7);
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                char arr[50];
                sprintf(arr, "退出了子弹: %s", magazine[index] == 1 ? "实弹" : "空弹");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, arr);
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
                return; // 重新进入行动流程
            }
        }
    }

    while (1)
    {
        BeginBatchDraw();
        settextstyle(WORDSIZE, 0, "宋体");
        // 射击目标选择逻辑
        int target;
        // 根据血量情况决定策略
        if ((bot.hp <= 2 && real >= 3) || (Props[1].isUsed == 1 && magazine[index] == 1) || (bulletCount == 1 && magazine[index] == 1))
        {
            // 低血量时优先向敌人开枪
            target = 1;
        }
        else {
            // 随机选择目标（60%概率攻击玩家）
            target = rand() % 10 < 6 ? 1 : 0;
        }

        // 执行射击
        BeginBatchDraw();
        settextstyle(WORDSIZE, 0, "宋体");
        outtextxy(25 * WORDSIZE, 2 * WORDSIZE, target == 1 ? "向你开枪!" : "向自己开枪!");
        EndBatchDraw();
        Sleep(3000);
        BeginBatchDraw();
        setfillcolor(WHITE);
        solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
        EndBatchDraw();
        if (target == 0) { // 向自己开枪
            if (magazine[index] == 1) { // 实弹
                openMusic(14);
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "被实弹击中!");
                EndBatchDraw();
                Sleep(3000);
                setfillcolor(WHITE);
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
                bot.hp -= bullet_damage;
                magazine[index] = 0;
                show_hp();
                BeginBatchDraw();
                openMusic(15);
                if (Props[3].isUsed == 0)
                    roleTurn = 0;//控制权交给玩家
                else
                    Props[3].isUsed = 1;
                break;
            }
            else
            { // 空弹
                openMusic(18);
                magazine[index] = 0;
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "打出空弹!");
                EndBatchDraw();
                roleTurn = 1; // 保持控制权
                bulletCount--;
                Sleep(3000);
                BeginBatchDraw();
                setfillcolor(WHITE);
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
                if (Props[3].isUsed == 1)
                    Props[3].isUsed = 0;
                break;
            }
        }
        else { // 向玩家开枪
            if (magazine[index] == 1) { // 实弹
                openMusic(14);
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 23 * WORDSIZE, "被实弹击中!");
                EndBatchDraw();
                Sleep(3000);
                player.hp -= bullet_damage;
                magazine[index] = 0;
                show_hp();
                BeginBatchDraw();
                openMusic(15);
                setfillcolor(WHITE);
                solidrectangle(25 * WORDSIZE, 23 * WORDSIZE, 34 * WORDSIZE, 24 * WORDSIZE);
                EndBatchDraw();
                if (Props[3].isUsed == 0)
                    roleTurn = 0;//控制权交给玩家
                else
                    Props[3].isUsed = 1;
                break;
            }
            else { // 空弹
                openMusic(18);
                magazine[index] = 0;
                BeginBatchDraw();
                settextstyle(WORDSIZE, 0, "宋体");
                outtextxy(25 * WORDSIZE, 2 * WORDSIZE, "打出空弹!");
                EndBatchDraw();
                Sleep(3000);
                BeginBatchDraw();
                setfillcolor(WHITE);
                solidrectangle(25 * WORDSIZE, 2 * WORDSIZE, 34 * WORDSIZE, 3 * WORDSIZE);
                EndBatchDraw();
                if (Props[3].isUsed == 0)
                    roleTurn = 0;//控制权交给玩家
                else
                    Props[3].isUsed = 1;
                break;
            }
        }
    }
    // 重置伤害并减少子弹
    bullet_damage = 1;
    bulletCount--;
    if (Props[0].isUsed == 1)
        Props[3].isUsed = 0;
    if (Props[1].isUsed == 1)
        Props[1].isUsed = 0;
}

void menuView()
{
    //用于加载图片
    initgraph(1380, 780, EX_SHOWCONSOLE);
    IMAGE HomePage;//主页面
    loadimage(&HomePage, "photo&music/menupage.png", 1380, 780);
    stopMusic(3);
    stopMusic(4);
    openMusic(1);

    cleardevice();
    while (true)
    {
        //双缓冲
        BeginBatchDraw();

        //背景
        putimage(0, 0, &HomePage);

        //绘制标题
        settextcolor(WHITE);
        setbkmode(TRANSPARENT);//去除文字黑框
        settextstyle(32, 0, "weiruanyahei");
        outtextxy(480, 200, "恶 魔 轮 盘 赌");


        //获取鼠标消息
        peekmessage(&msg, EX_MOUSE);
        if (button(520, 380, 650, 400, "开始游戏")) gameView();

        if (button(520, 480, 650, 500, "音乐设置")) musicControl();

        if (button(520, 580, 650, 600, "游戏规则"))
        {
            while (true)
            {
                BeginBatchDraw();
                IMAGE rulePage;//规则
                loadimage(&rulePage, "photo&music/游戏规则(1).png", 1380, 780);
                putimage(0, 0, &rulePage);
                text(520, 400, "最好声音开大点,再去声音设置里面调小BGM");
                if (button(1000, 600, 1200, 650, "返回"))
                {
                    break;
                }

                EndBatchDraw();
                msg.message = 0;
            }
        }
        if (button(520, 680, 650, 700, "退出游戏")) exit(0);

        EndBatchDraw();
        msg.message = 0;//清除鼠标消息

        stopMusic(4);
    }
}

void gameMap()
{
    BeginBatchDraw();
    //设置游戏的大小和白色背景
    //initgraph(WIDTH, HEIGHT, EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    //用已设置的背景色填充窗口
    cleardevice();

    //设置字体颜色和大小
    settextcolor(BLACK);
    settextstyle(WORDSIZE, 0, "Silver 中等");

    // 上边框
    for (int i = 0; i < WIDTH; i += WORDSIZE)
    {
        outtextxy(i, 0, "墙");
    }

    // 下边框
    for (int i = 0; i < WIDTH; i += WORDSIZE)
    {
        if (i <= 630 || i >= 720)
            outtextxy(i, HEIGHT - WORDSIZE, "墙");  // 减去文字高度，避免超出窗口
        else
            outtextxy(i, HEIGHT - WORDSIZE, "门");
    }

    // 左边框（跳过上下已经绘制的部分）
    for (int i = WORDSIZE; i < HEIGHT - WORDSIZE; i += WORDSIZE)//是否减去两倍的wordsize，边界问题
    {
        outtextxy(0, i, "墙");
    }
    for (int i = WORDSIZE; i < HEIGHT - WORDSIZE; i += WORDSIZE)
    {
        outtextxy(WIDTH - WORDSIZE, i, "墙");
    }
    outtextxy(660, 60, "恶魔");

    outtextxy(675, 690, "我");

    outtextxy(645, 375, "霰弹枪");

    //左上角
    outtextxy(9 * WORDSIZE, 2 * WORDSIZE, "道具栏");
    //右上角
    outtextxy(34 * WORDSIZE, 2 * WORDSIZE, "道具栏");
    //左下角
    outtextxy(9 * WORDSIZE, (16 + 7) * WORDSIZE, "道具栏");
    //右下角
    outtextxy(34 * WORDSIZE, (16 + 7) * WORDSIZE, "道具栏");
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 5);
    //左下脚矩形
    rectangle(3 * WORDSIZE, 18 * WORDSIZE, 18 * WORDSIZE, 22 * WORDSIZE);
    //右下角矩形
    rectangle(28 * WORDSIZE, 18 * WORDSIZE, 43 * WORDSIZE, 22 * WORDSIZE);
    //左上角矩形
    rectangle(3 * WORDSIZE, 4 * WORDSIZE, 18 * WORDSIZE, 8 * WORDSIZE);
    //右上角矩形
    rectangle(28 * WORDSIZE, 4 * WORDSIZE, 43 * WORDSIZE, 8 * WORDSIZE);

    //左上脚十字
    //竖线
    moveto(10.5 * WORDSIZE, 4 * WORDSIZE);
    lineto(10.5 * WORDSIZE, 8 * WORDSIZE);
    //横线
    moveto(3 * WORDSIZE, 6 * WORDSIZE);
    lineto(18 * WORDSIZE, 6 * WORDSIZE);
    //右上角十字
    //竖线
    moveto(35.5 * WORDSIZE, 4 * WORDSIZE);
    lineto(35.5 * WORDSIZE, 8 * WORDSIZE);
    //横线
    moveto(28 * WORDSIZE, 6 * WORDSIZE);
    lineto(43 * WORDSIZE, 6 * WORDSIZE);
    //左下角十字
    //竖线
    moveto(10.5 * WORDSIZE, 18 * WORDSIZE);
    lineto(10.5 * WORDSIZE, 22 * WORDSIZE);
    //横线
    moveto(3 * WORDSIZE, 20 * WORDSIZE);
    lineto(18 * WORDSIZE, 20 * WORDSIZE);
    //右下角十字
    //竖线
    moveto(35.5 * WORDSIZE, 18 * WORDSIZE);
    lineto(35.5 * WORDSIZE, 22 * WORDSIZE);
    //横线
    moveto(28 * WORDSIZE, 20 * WORDSIZE);
    lineto(43 * WORDSIZE, 20 * WORDSIZE);

    outtextxy(9 * WORDSIZE, 10 * WORDSIZE, "子弹");
    outtextxy(7 * WORDSIZE, 11 * WORDSIZE, "类型以及数量");

    //子弹栏
    setlinestyle(PS_SOLID, 3);
    rectangle(6 * WORDSIZE, 12 * WORDSIZE, 14 * WORDSIZE, 13 * WORDSIZE);
    //子弹栏竖线
    for (int i = 7; i <= 13; i++)
    {
        line(i * WORDSIZE, 12 * WORDSIZE, i * WORDSIZE, 13 * WORDSIZE);
    }
    outtextxy(31 * WORDSIZE, 10 * WORDSIZE, "恶魔     关卡       我");
    //关卡？
    rectangle(38 * WORDSIZE, 10 * WORDSIZE, 39 * WORDSIZE, 11 * WORDSIZE);
    //恶魔和我名字外的圆角矩形
    roundrect(22 * WORDSIZE, 2 * WORDSIZE, 24 * WORDSIZE, 3 * WORDSIZE, 10, 10);        // Draw a rounded rectangle without filling
    roundrect(22 * WORDSIZE, 23 * WORDSIZE, 24 * WORDSIZE, 24 * WORDSIZE, 10, 10);        // Draw a rounded rectangle without filling

    //恶魔生命值
    outtextxy(26 * WORDSIZE, 12 * WORDSIZE, "生命值：");
    rectangle(30 * WORDSIZE, 12 * WORDSIZE, 36 * WORDSIZE, 13 * WORDSIZE);
    //恶魔生命值竖线
    for (int i = 31; i <= 35; i++)
    {
        line(i * WORDSIZE, 12 * WORDSIZE, i * WORDSIZE, 13 * WORDSIZE);
    }
    //我生命值
    rectangle(39 * WORDSIZE, 12 * WORDSIZE, 45 * WORDSIZE, 13 * WORDSIZE);
    //我生命值竖线
    EndBatchDraw();
}

void show_level()
{
    BeginBatchDraw();
    setfillcolor(WHITE);
    settextstyle(WORDSIZE, 0, "Sliver 中等");
    fillrectangle(38 * WORDSIZE, 10 * WORDSIZE, 39 * WORDSIZE, 11 * WORDSIZE);
    if (currentLevel == 1)
        outtextxy(38 * WORDSIZE, 10 * WORDSIZE, "一");
    else if (currentLevel == 2)
        outtextxy(38 * WORDSIZE, 10 * WORDSIZE, "二");
    else
        outtextxy(38 * WORDSIZE, 10 * WORDSIZE, "三");
    EndBatchDraw();
}

void me_show_props()
{
    BeginBatchDraw();
    setfillcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(2 * WORDSIZE, 0, "微软雅黑");
    if (player.roleprops[0] != 0)
        outtextxy(5 * WORDSIZE, 18 * WORDSIZE, Props[player.roleprops[0] - 1].name);
    else
        fillrectangle(3 * WORDSIZE, 18 * WORDSIZE, 10.5 * WORDSIZE, 20 * WORDSIZE);
    if (player.roleprops[1] != 0)
        outtextxy(13 * WORDSIZE, 18 * WORDSIZE, Props[player.roleprops[1] - 1].name);
    else
        fillrectangle(10.5 * WORDSIZE, 18 * WORDSIZE, 18 * WORDSIZE, 20 * WORDSIZE);
    if (player.roleprops[2] != 0)
        outtextxy(30 * WORDSIZE, 18 * WORDSIZE, Props[player.roleprops[2] - 1].name);
    else
        fillrectangle(28 * WORDSIZE, 18 * WORDSIZE, 35.5 * WORDSIZE, 20 * WORDSIZE);
    if (player.roleprops[3] != 0)
        outtextxy(38 * WORDSIZE, 18 * WORDSIZE, Props[player.roleprops[3] - 1].name);
    else
        fillrectangle(35.5 * WORDSIZE, 18 * WORDSIZE, 43 * WORDSIZE, 20 * WORDSIZE);
    if (player.roleprops[4] != 0)
        outtextxy(5 * WORDSIZE, 20 * WORDSIZE, Props[player.roleprops[4] - 1].name);
    else
        fillrectangle(3 * WORDSIZE, 20 * WORDSIZE, 10.5 * WORDSIZE, 22 * WORDSIZE);
    if (player.roleprops[5] != 0)
        outtextxy(13 * WORDSIZE, 20 * WORDSIZE, Props[player.roleprops[5] - 1].name);
    else
        fillrectangle(10.5 * WORDSIZE, 20 * WORDSIZE, 18 * WORDSIZE, 22 * WORDSIZE);
    if (player.roleprops[6] != 0)
        outtextxy(30 * WORDSIZE, 20 * WORDSIZE, Props[player.roleprops[6] - 1].name);
    else
        fillrectangle(28 * WORDSIZE, 20 * WORDSIZE, 35.5 * WORDSIZE, 22 * WORDSIZE);
    if (player.roleprops[7] != 0)
        outtextxy(38 * WORDSIZE, 20 * WORDSIZE, Props[player.roleprops[7] - 1].name);
    else
        fillrectangle(35.5 * WORDSIZE, 20 * WORDSIZE, 43 * WORDSIZE, 22 * WORDSIZE);
    EndBatchDraw();
}

void evil_show_props()
{
    BeginBatchDraw();
    setfillcolor(WHITE);
    //setbkmode(TRANSPARENT);
    settextstyle(2 * WORDSIZE, 0, "微软雅黑");
    if (bot.roleprops[0] != 0)
        outtextxy(5 * WORDSIZE, 4 * WORDSIZE, Props[bot.roleprops[0] - 1].name);
    else
        fillrectangle(3 * WORDSIZE, 4 * WORDSIZE, 10.5 * WORDSIZE, 6 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[1] != 0)
        outtextxy(13 * WORDSIZE, 4 * WORDSIZE, Props[bot.roleprops[1] - 1].name);
    else
        fillrectangle(10.5 * WORDSIZE, 4 * WORDSIZE, 18 * WORDSIZE, 6 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[2] != 0)
        outtextxy(30 * WORDSIZE, 4 * WORDSIZE, Props[bot.roleprops[2] - 1].name);
    else
        fillrectangle(28 * WORDSIZE, 4 * WORDSIZE, 35.5 * WORDSIZE, 6 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[3] != 0)
        outtextxy(38 * WORDSIZE, 4 * WORDSIZE, Props[bot.roleprops[3] - 1].name);
    else
        fillrectangle(35.5 * WORDSIZE, 4 * WORDSIZE, 43 * WORDSIZE, 6 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[4] != 0)
        outtextxy(5 * WORDSIZE, 6 * WORDSIZE, Props[bot.roleprops[4] - 1].name);
    else
        fillrectangle(3 * WORDSIZE, 6 * WORDSIZE, 10.5 * WORDSIZE, 8 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[5] != 0)
        outtextxy(13 * WORDSIZE, 6 * WORDSIZE, Props[bot.roleprops[5] - 1].name);
    else
        fillrectangle(10.5 * WORDSIZE, 6 * WORDSIZE, 18 * WORDSIZE, 8 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[6] != 0)
        outtextxy(30 * WORDSIZE, 6 * WORDSIZE, Props[bot.roleprops[6] - 1].name);
    else
        fillrectangle(28 * WORDSIZE, 6 * WORDSIZE, 35.5 * WORDSIZE, 8 * WORDSIZE);
    EndBatchDraw();
    BeginBatchDraw();
    if (bot.roleprops[7] != 0)
        outtextxy(38 * WORDSIZE, 6 * WORDSIZE, Props[bot.roleprops[7] - 1].name);
    else
        fillrectangle(35.5 * WORDSIZE, 6 * WORDSIZE, 43 * WORDSIZE, 8 * WORDSIZE);
    EndBatchDraw();
}

void show_hp()
{
    BeginBatchDraw();
    setfillcolor(WHITE);
    for (int i = 0; i < 6; i++)    //初始化恶魔生命值
    {

        fillrectangle((30 + i) * WORDSIZE, 12 * WORDSIZE, (31 + i) * WORDSIZE, 13 * WORDSIZE);
    }
    for (int i = 0; i < 6; i++)
    {

        fillrectangle((39 + i) * WORDSIZE, 12 * WORDSIZE, (40 + i) * WORDSIZE, 13 * WORDSIZE);
    }
    EndBatchDraw();
    BeginBatchDraw();
    setfillcolor(RGB(216, 160, 213));//设置恶魔生命值颜色
    for (int i = 0; i < bot.hp; i++)//打印恶魔生命值
    {

        fillcircle((30.5 + i) * WORDSIZE, 12.5 * WORDSIZE, 0.5 * WORDSIZE);
    }
    EndBatchDraw();
    BeginBatchDraw();
    setfillcolor(RGB(255, 143, 107));//设置我生命值颜色
    for (int i = 0; i < player.hp; i++)//打印我生命值
    {

        fillcircle((39.5 + i) * WORDSIZE, 12.5 * WORDSIZE, 0.5 * WORDSIZE);
    }
    EndBatchDraw();
}

void show_bullets()
{
    Sleep(100);
    openMusic(5);
    BeginBatchDraw();
    for (int i = 0; i < 8; i++)//初始化子弹类型何数量
    {
        setfillcolor(WHITE);
        fillrectangle((6 + i) * WORDSIZE, 12 * WORDSIZE, (7 + i) * WORDSIZE, 13 * WORDSIZE);
    }
    int huazi_count = 0;//计数器，用于下面第二个循环，打印空包弹时跳过已打印的部分
    for (int i = 0; i < real; i++)//打印实弹
    {
        setfillcolor(RED);
        fillcircle((6.5 + i) * WORDSIZE, 12.5 * WORDSIZE, 0.5 * WORDSIZE);
        huazi_count++;
    }

    for (int i = 0; i < fake; i++)//打印空包弹
    {
        setfillcolor(BLUE);
        fillcircle((6.5 + huazi_count + i) * WORDSIZE, 12.5 * WORDSIZE, 0.5 * WORDSIZE);
    }
    EndBatchDraw();
    openMusic(6);
}

int pr_button()
{
    ExMessage msg = { 0 };
    while (1)
    {
        if (peekmessage(&msg, EX_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 3 * WORDSIZE && msg.x <= 10.5 * WORDSIZE && msg.y >= 18 * WORDSIZE && msg.y <= 20 * WORDSIZE)
                {
                    return 0;
                }
                if (msg.x >= 10.5 * WORDSIZE && msg.x <= 18 * WORDSIZE && msg.y >= 18 * WORDSIZE && msg.y <= 20 * WORDSIZE)
                {
                    return 1;
                }
                if (msg.x >= 28 * WORDSIZE && msg.x <= 35.5 * WORDSIZE && msg.y >= 18 * WORDSIZE && msg.y <= 20 * WORDSIZE)
                {
                    return 2;
                }
                if (msg.x >= 35.5 * WORDSIZE && msg.x <= 43 * WORDSIZE && msg.y >= 18 * WORDSIZE && msg.y <= 20 * WORDSIZE)
                {
                    return 3;
                }
                if (msg.x >= 3 * WORDSIZE && msg.x <= 10.5 * WORDSIZE && msg.y >= 20 * WORDSIZE && msg.y <= 22 * WORDSIZE)
                {
                    return 4;
                }
                if (msg.x >= 10.5 * WORDSIZE && msg.x <= 18 * WORDSIZE && msg.y >= 20 * WORDSIZE && msg.y <= 22 * WORDSIZE)
                {
                    return 5;
                }
                if (msg.x >= 28 * WORDSIZE && msg.x <= 35.5 * WORDSIZE && msg.y >= 20 * WORDSIZE && msg.y <= 22 * WORDSIZE)
                {
                    return 6;
                }
                if (msg.x >= 35.5 * WORDSIZE && msg.x <= 43 * WORDSIZE && msg.y >= 20 * WORDSIZE && msg.y <= 22 * WORDSIZE)
                {
                    return 7;
                }
                if (msg.x >= 20 * WORDSIZE && msg.x <= 26 * WORDSIZE && msg.y >= 1 * WORDSIZE && msg.y <= 5 * WORDSIZE)
                {
                    return 8;
                }
                if (msg.x >= 20 * WORDSIZE && msg.x <= 26 * WORDSIZE && msg.y >= 22 * WORDSIZE && msg.y <= 26 * WORDSIZE)
                {
                    return 9;
                }
            }
        }
    }
    return -1;
}

void winView()
{
    stopMusic(4);
    openMusic(3);
    while (true)
    {
        BeginBatchDraw();
        solidrectangle(300, 150, 1000, 580);
        settextcolor(WHITE);
        char a[100] = "You Win";
        int Win_x = (700 - textwidth(a)) / 2;
        int Win_y = (430 - textheight(a)) / 2;
        outtextxy(300 + Win_x * 2 / 3, 150 + Win_y * 2 / 3, a);
        peekmessage(&msg, EX_MOUSE);
        if (button(400, 400, 600, 500, "返回主菜单")) exit(0);
        EndBatchDraw();
        msg.message = 0;
    }
}

void loseView()
{
    while (true)
    {
        stopMusic(4);
        BeginBatchDraw();
        solidrectangle(300, 150, 1000, 580);
        settextcolor(WHITE);
        char a[100] = "You lost";
        int L_x = (700 - textwidth(a)) / 2;
        int L_y = (430 - textheight(a)) / 2;
        outtextxy(300 + L_x * 2 / 3, 150 + L_y * 2 / 3, a);
        peekmessage(&msg, EX_MOUSE);
        if (button(400, 400, 600, 500, "返回主菜单")) menuView();
        EndBatchDraw();
        msg.message = 0;
    }
}

void gameView()
{
    stopMusic(1);
    openMusic(4);
    gameMap();
    init();
    while (currentLevel <= 3)//关卡
    {
        level();//根据关卡设置血量 2 4 6 和每次抽取的道具数 0 2 4
        show_hp();
        show_level();
        me_show_props();//在道具栏中打印道具名称
        evil_show_props();
        while (player.hp > 0 && bot.hp > 0)//回合
        {
            peekmessage(&msg, EX_KEY);

            if (msg.message == WM_KEYDOWN)
            {
                printf("keydown\n");
                //判断具体是哪个键按下
                switch (msg.vkcode)
                {
                case 'A':
                    printf("exc按下");
                    while (true)
                    {
                        BeginBatchDraw();
                        solidrectangle(300, 150, 1000, 580);
                        settextcolor(WHITE);
                        char a[100] = "暂停";
                        int Win_x = (700 - textwidth(a)) / 2;
                        int Win_y = (430 - textheight(a)) / 2;
                        text(300 + Win_x * 2 / 3, 150 + Win_y * 2 / 3, a);
                        peekmessage(&msg, EX_MOUSE);
                        if (button(400, 400, 600, 500, "声音设置")) musicControl();
                        EndBatchDraw();
                    }
                    msg.message = 0;
                }
            }
            draw_props();//每回合开始抽取道具

            me_show_props();//在道具栏中打印道具名称

            evil_show_props();

            Bullet();//根据回合数设置真假弹数量

            if (real + fake > 8)
                bulletCount = 8;
            else
                bulletCount = real + fake;

            load_bullets();//填充进数组

            Sleep(1000);

            openMusic(5);
            show_bullets();//展示子弹
            Sleep(2000);

            for (int i = 0; i < 8; i++)//初始化子弹类型何数量
            {
                setfillcolor(WHITE);
                fillrectangle((6 + i) * WORDSIZE, 12 * WORDSIZE, (7 + i) * WORDSIZE, 13 * WORDSIZE);
            }
            openMusic(6);
            Sleep(1000);
            shuffle();//打乱数组
            for (int n = 0; n < bulletCount; n++)
            {
                openMusic(17);
                Sleep(200);
            }
            openMusic(19);
            int index = 0;

            while (bulletCount > 0)
            {
                if (magazine[index] != 0)
                {
                    if (roleTurn == 0)
                    {
                        int prBtn = pr_button();
                        if (prBtn >= 0 && prBtn <= 7)
                        {
                            prop_effect(player.roleprops[prBtn], prBtn, index);
                            continue;
                        }
                        if (prBtn == 8 || prBtn == 9)
                        {
                            player_shoot(prBtn, index);
                        }
                    }
                    else
                        bot_action(index);
                    Props[0].isUsed = 0;
                    Props[3].isUsed = 0;
                    if (player.hp <= 0)
                    {
                        openMusic(21);
                        Sleep(100);
                        loseView();
                    }

                    if (bot.hp <= 0)
                    {
                        roleTurn = 0;
                        break;
                    }
                }
                index++;
            }
            roleTurn = 0;
            if (bot.hp <= 0)
                break;
            currentRound++;
        }
        if (bot.hp <= 0)
        {
            openMusic(20);
            currentLevel++;
            currentRound = 1;
        }
    }
    winView();
}

bool area(int mx, int my, int x1, int y1, int x2, int y2)//用于确认鼠标位置,
{
    if (mx > x1 && mx<x2 && my>y1 && my < y2)//mx和my是鼠标位置
    {
        return true;
    }
    return false;
}

bool button(int x1, int y1, int x2, int y2, const char* text)
{

    if (area(msg.x, msg.y, x1, y1, x2, y2)) setfillcolor(RGB(93, 107, 153));
    else setfillcolor(BLACK);

    solidrectangle(x1, y1, x2, y2);

    int X = (x2 - x1 - textwidth(text)) / 2;
    int Y = (y2 - y1 - textheight(text)) / 2;
    settextcolor(WHITE);//让文字变成白色
    settextstyle(32, 0, "weiruanyahei");
    setbkmode(TRANSPARENT);//去除文字黑框
    outtextxy(X + x1, y1 + Y, text);

    setfillcolor(BLACK);

    peekmessage(&msg, EX_MOUSE);

    if (area(msg.x, msg.y, x1, y1, x2, y2)/*鼠标在该区域*/ && msg.message == WM_LBUTTONDOWN/*左键按下*/)
    {
        openMusic(2);
        return true;
    }
    else return false;
}

void openMusic(int x)
{
    int ret = 0;
    switch (x)
    {
    case 1:
        mciSendString("play BGM1 repeat", NULL, 0, NULL);
        break;
    case 2:
        mciSendString("setaudio BGM2 volume to 100", NULL, 0, NULL);
        mciSendString("play BGM2 from 0", NULL, 0, NULL);
        break;
    case 3:
        mciSendString("play BGM3 repeat", NULL, 0, NULL);
        break;
    case 4:
        mciSendString("play BGM4 repeat", NULL, 0, NULL);
        break;
    case 5:
        mciSendString("setaudio BGM5 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM5 from 0", NULL, 0, NULL);
        break;
    case 6:
        mciSendString("setaudio BGM6 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM6 from 0", NULL, 0, NULL);
        break;
    case 7:
        mciSendString("setaudio BGM7 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM7 from 0", NULL, 0, NULL);
        break;
    case 8:
        mciSendString("setaudio BGM8 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM8 from 0", NULL, 0, NULL);
        break;
    case 9:
        mciSendString("setaudio BGM9 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM9 from 0", NULL, 0, NULL);
        break;
    case 10:
        mciSendString("setaudio BGM10 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM10 from 0", NULL, 0, NULL);
        break;
    case 11:
        mciSendString("setaudio BGM11 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM11 from 0", NULL, 0, NULL);
        break;
    case 12:
        mciSendString("setaudio BGM12 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM12 from 0", NULL, 0, NULL);
        break;
    case 13:
        mciSendString("setaudio BGM13 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM13 from 0", NULL, 0, NULL);
        break;
    case 14:
        mciSendString("setaudio BGM14 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM14 from 0", NULL, 0, NULL);
        break;
    case 15:
        mciSendString("setaudio BGM15 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM15 from 0", NULL, 0, NULL);
        break;
    case 16:
        mciSendString("setaudio BGM16 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM16 from 0", NULL, 0, NULL);
        break;
    case 17:
        mciSendString("setaudio BGM17 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM17 from 0", NULL, 0, NULL);
        break;
    case 18:
        mciSendString("setaudio BGM18 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM18 from 0", NULL, 0, NULL);
        break;
    case 19:
        mciSendString("setaudio BGM19 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM19 from 0", NULL, 0, NULL);
        break;
    case 20:
        mciSendString("setaudio BGM20 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM20 from 0", NULL, 0, NULL);
        break;
    case 21:
        mciSendString("setaudio BGM21 volume to 1000", NULL, 0, NULL);
        mciSendString("play BGM21 from 0", NULL, 0, NULL);
        break;
    }
}

void stopMusic(int x)
{
    switch (x)
    {
    case 1:
        mciSendString("stop BGM1", NULL, 0, NULL);
        break;
    case 3:
        mciSendString("stop BGM3", NULL, 0, NULL);
        break;
    case 4:
        mciSendString("stop BGM4", NULL, 0, NULL);
        break;
    }
}

void loadMusic()
{
    mciSendString("open photo&music/menumusic.wav alias BGM1 type mpegvideo", NULL, 0, NULL);
    mciSendString("open photo&music/anniu.wav alias BGM2 ", NULL, 0, NULL);
    mciSendString("open photo&music/shengli.wav alias BGM3 type mpegvideo", NULL, 0, NULL);
    mciSendString("open photo&music/fight.wav alias BGM4 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/展示子弹-开始/showbulletsbegin.wav alias BGM5 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/展示子弹-结束/showbulletsend.wav alias BGM6 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用饮料退弹/unload.wav alias BGM7 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用饮料/drinks.wav alias BGM8 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用小刀/knife.wav alias BGM9 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用香烟/smoke.wav alias BGM10 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用手铐/handcuff.wav alias BGM11 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用放大镜查看子弹/checkbullets.wav alias BGM12 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/使用放大镜/lens.wav alias BGM13 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/实弹/real.wav alias BGM14 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/扣血/dehp.wav alias BGM15 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/回血/rehp.wav alias BGM16 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/装弹/loadbullets.wav alias BGM17 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/空弹/fake.wav alias BGM18 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/over/over.wav alias BGM19 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/1.mp3 alias BGM20 type mpegvideo", NULL, 0, NULL);
    mciSendString("open 音效/2.mp3 alias BGM21 type mpegvideo", NULL, 0, NULL);
}

void musicControl()
{
    IMAGE HomePage;//主页面
    loadimage(&HomePage, "photo&music/menupage.png", 1380, 780);
    while (true)
    {
        BeginBatchDraw();
        putimage(0, 0, &HomePage);
        if (button(100, 100, 150, 150, "返回"))
        {
            break;
        }

        text(550, 150, "BGM大小");

        char volume[100];
        mciSendString("status BGM1 volume", volume, sizeof(volume), NULL);//获取当前音量
        int sound = atoi(volume);//将音量字符串转换为整数
        sound /= 100;

        int i, n = 0;//打印当前音量
        for (i = 500; n < sound; i += 20)
        {
            text(i, 200, "声");
            n++;
        }
        if (button(400, 200, 450, 230, "减小"))
        {
            sound -= 1;
            printf("%d", sound);
            sprintf(volume, "setaudio BGM1 volume to %d", sound * 100);
            printf(volume);//测试是否调整成功
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM2 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM3 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM4 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

        }
        if (button(720, 200, 770, 230, "增大"))
        {
            sound += 1;
            printf("%d", sound);
            sprintf(volume, "setaudio BGM1 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM2 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM3 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);

            sprintf(volume, "setaudio BGM4 volume to %d", sound * 100);
            printf(volume);
            mciSendString(volume, NULL, 0, NULL);
        }



        EndBatchDraw();
        msg.message = 0;
    }
}

void text(int x, int y, const char* text)
{
    settextcolor(WHITE);//让文字变成白色
    settextstyle(22, 0, "weiruanyahei");
    setbkmode(TRANSPARENT);//去除文字黑框
    outtextxy(x, y, text);
}