游戏整体框架

```c
int main(){
    GameBegin();
    return 0;
}
//开始游戏
void GameBegin(){
    //确定游戏初始设置
    srand(time(0));//srand()很耗性能，故只引用一次于此
    HideCursor();//隐藏光标
    system("chcp 65001 > nul");//中文库
    system("title Greedy Snake");//设置窗口名称
    system("mode con cols=100 lines=40");//设置窗口大小
    //进入标题页、欢迎页与目录页
    GameTitle();
    Welcome();
    Menu();
}
//进入菜单并通过选项进入不同界面
void Menu(){
    MenuAppearance();

    while(1){
        if(optionDefault) {
            StressOption(option);
            optionDefault = 0;
        }else {
            int prvoption = option;
            int ch = getch();
            if (ch == 'q') exit(0);
            if (ch == UP || ch == 'w') option = (--option + 4) % 5 + 1;
            else if (ch == DOWN || ch == 's') option = (++option + 4) % 5 + 1;
            else if(ch == 13){//回车
                ChooseOption(option);
            }else continue;

            StressOption(option);
            RenewPrvOption(prvoption);


        }
    }
}
//全局参数
int wallcolor = 3,snakeheadcolor = 10,snakebodycolor = 10;
int moder = 0,model = 0,moden = 1,modee = 0;
int recordbroken = 0;
int wallxlen = 60;
int wallylen = 30;
int bornx = 12;
int borny = 6;
int bornlen = 4;
int curlen;
int option = 1;
int optionDefault = 1;
int speed = 150;
int speed_change = 1;
int curscore = 0;
int maxscore = 0;
int coindoubled = 0;
int totalcoins = 0;
int foodweight = 100;
int direction = RIGHT;

//函数结构
//开始游戏
void GameBegin();
//欢迎
void Welcome();
//游戏标题
void GameTitle();
//进入菜单
void Menu();
void MenuAppearance();
void StressOption(int option);
void RenewPrvOption(int prvoption);
void ChooseOption(int option);
//进入商城
void Shop();
void ShopAppearance();
//添加提示
void Notes();
//创建地图
void CreateMap();
//移动光标
void gotoxy(int x,int y);
//定义蛇的单个节点
typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE *next;
} Snake;
//创建初始蛇头
Snake *linked_list_head = NULL;
//生成初始蛇
void CreateSnake();
//运行游戏
void GameRun();
//移动蛇身
void MoveSnake(int direction);
enum{UP = 72,LEFT = 75,RIGHT = 77,DOWN = 80};
int direction = RIGHT;
//移动蛇身的四种情况
void Move(int direction);
void EatFood(int direction);
void EatCoin(int direction);
void Failed();
//隐藏光标
void HideCursor();
void color(int c);
typedef struct FOOD{
    int x;
    int y;
} Food;
Food food;
void CreateFood();
typedef struct COIN{
    int x;
    int y;
} Coin;
Coin coin;
typedef struct GOODS{
    int shop_amount;
    int player_amount;
    int price;
} Goods;
Goods goods1_SpeedDown = {10,4,10};
Goods goods2_SpeedMid = {10,4,10};
Goods goods3_SpeedUp = {10,4,10};
Goods goods4_CoinDoubled = {10,4,10};
void CreateCoin();
int is_contradicted(int x,int y);
void GameReplay();
void GameIntro();
void AboutUs();
void LongSnakeMode();
void RandSmallWallMode();
void ExtremeSmallMode();
void OrderPage();
void OrderPageAppearance();
void CheatProgramme();
void EasterEgg();
void HiddenAboutUs();
void HiddenGameIntro();
void HiddenEasterEgg();
```

核心之一：创建蛇及食物与金币

```c
//创建初始蛇头
Snake *linked_list_head = NULL;
void CreateSnake(){
    Snake *head = malloc(sizeof(Snake));
    head->x = bornx;
    head->y = borny;
    head->next = NULL;
    linked_list_head = head;//赋值蛇头

    for(int i = 1;i <= bornlen;i++){
        Snake *tail = malloc(sizeof(Snake));
        tail->x = bornx + i * 2;
        tail->y = borny;
        tail->next = NULL;
        head->next = tail;
        head = tail;
    }
    //Print
    head = linked_list_head;
    while(head->next != NULL){
        color(snakebodycolor);
        gotoxy(head->x,head->y);
        printf("□");
        head = head->next;
    }
    color(snakeheadcolor);
    gotoxy(head->x,head->y);
    printf("■");
    head = head->next;
}
//基础函数：判断生成的食物、金币处是否原先有物体
int is_contradicted(int x,int y){
    if(x <= 1|| x >= wallxlen - 3 || y <= 0 || y >= wallylen - 1) return 1;
    Snake *p = linked_list_head;
    while(p != NULL && p->next != NULL){
        if(p->x == x && p->y == y) return 1;
        p = p->next;
    }
    return 0;
}
void CreateCoin(){
    int newx,newy;
    do {
        int x = 2 * rand();
        newx = 2 * (x % 20);
        newy = x % 25;
    }while(is_contradicted(newx,newy) || (coin.x == food.x && coin.y == food.y));

    coin.x = newx;
    coin.y = newy;
    color(14);
    gotoxy(coin.x,coin.y);
    printf("◆");
}
void CreateFood(){
    int newx,newy;
    do {
        newx = 2 * (rand() % 20);
        newy = rand() % 25;
    }while(is_contradicted(newx,newy));

    food.x = newx;
    food.y = newy;
    color(12);
    gotoxy(food.x,food.y);
    printf("●");

}
```

核心之二：移动蛇及吃食物、金币与撞到墙或蛇身

```c
void MoveSnake(int direction){

    Snake *p = linked_list_head;
    while(p != NULL && p->next != NULL){
        p = p->next;
    }
    if(p->x == food.x && p->y == food.y){
        EatFood(direction);

    }else if(is_contradicted(p->x,p->y)){
        Failed();

    }else if(p->x == coin.x && p->y == coin.y){
        EatCoin(direction);
    }else {
        Move(direction);
    }
}
//移动蛇身的四种情况
void Move(int direction){
    //找到链表尾部
    Snake *p = linked_list_head;
    while(p != NULL && p->next != NULL){
        p = p->next;
    }

    Snake *temp = malloc(sizeof(Snake));
    temp->next = NULL;
    if(direction == RIGHT) {
        temp->x = p->x + 2;
        temp->y = p->y;
    }else if(direction == LEFT){
        temp->x = p->x - 2;
        temp->y = p->y;
    }else if(direction == UP){
        temp->x = p->x;
        temp->y = p->y - 1;
    }else if(direction == DOWN){
        temp->x = p->x;
        temp->y = p->y + 1;
    }
    p->next = temp;
    color(snakeheadcolor);
    gotoxy(temp->x,temp->y);
    printf("■");
    color(snakebodycolor);
    gotoxy(p->x,p->y);
    printf("□");
    gotoxy(linked_list_head->x, linked_list_head->y);
    printf("  ");
    //删除尾部
    temp = linked_list_head->next;
    free(linked_list_head);
    linked_list_head = temp;


}
void EatFood(int direction){
    Snake *p = linked_list_head;
    while(p != NULL && p->next != NULL){
        p = p->next;
    }

    Snake *temp = malloc(sizeof(Snake));
    temp->next = NULL;
    if(direction == RIGHT) {
        temp->x = p->x + 2;
        temp->y = p->y;
    }else if(direction == LEFT){
        temp->x = p->x - 2;
        temp->y = p->y;
    }else if(direction == UP){
        temp->x = p->x;
        temp->y = p->y - 1;
    }else if(direction == DOWN){
        temp->x = p->x;
        temp->y = p->y + 1;
    }
    p->next = temp;
    color(snakebodycolor);
    gotoxy(p->x,p->y);
    printf("□");
    color(snakeheadcolor);
    gotoxy(temp->x,temp->y);
    printf("■");

    curscore += foodweight;
    if(curscore >= 500 && curscore <= 1500 && speed_change){
        speed = 140;
        foodweight += 100;
    }else if(curscore >= 1500 && curscore <= 3000 && speed_change){
        speed = 120;
        foodweight += 100;
    }else if(curscore >= 3000 && curscore <= 6000 && speed_change){
        speed = 100;
        foodweight += 100;
    }else if(curscore >= 6000 && curscore <= 15000 && speed_change){
        speed = 80;
        foodweight += 100;
    }else if(curscore >= 15000 && speed_change){
        speed = 60;
        foodweight += 100;
    }
    if(curscore > maxscore)  recordbroken = 1;
    maxscore = maxscore < curscore ? curscore : maxscore;
    curlen++;
    Notes();


    CreateFood();
}
void EatCoin(int direction){
    Move(direction);
    totalcoins += 1 + coindoubled;
    Notes();
    CreateCoin();
}
void Failed(){
    //MessageBox(NULL,TEXT("Sorry,you failed.\nDo you want to replay the game?"),L"",MB_YESNO);
    if(moder == 0 && model == 0 && moden == 1 && modee == 0)
        GameReplay();
    else if(moder == 1 && model == 0 && moden == 0 && modee == 0)
        RandSmallWallMode();
    else if(moder == 0 && model == 1 && moden == 0 && modee == 0)
        LongSnakeMode();
    else if(moder == 0 && model == 0 && moden == 0 && modee == 1)
        ExtremeSmallMode();
    //MessageBeep(MB_OK);
    //TODO

}
```

核心之三：新增游戏模式

```c
//只用改变一下参数即可，这里体现了用参数代替数值的好处
void ExtremeSmallMode(){
    system("cls");//清屏
    color(7);//调回白色
    //全局变量赋回初值
    moder = 0,model = 0,moden = 0,modee = 1;
    recordbroken = 0;
    wallxlen = 20;
    wallylen = 10;
    bornx = 2;
    borny = 1;
    bornlen = 4;
    curlen = 5;
    curscore = 0;
    coindoubled = 0;
    foodweight = 100;
    speed = 150;
    speed_change = 1;
    linked_list_head = NULL;
    direction = RIGHT;
    //从游戏界面重新开始
    GameRun();
}
```

核心之四：切换游戏界面

```c
void GameIntro(){
    system("cls");
    color(7);
    printf("\n                              Some Game Information");
    gotoxy(0,4);
    printf("一、About Pages:\n\n"
           "1.There are many pages (including hidden pages) in this game.  :-)\n"
           "\n二、About Press Keys:\n\n"
           "1.On every game, you can press 'q' to quit the game at any time.\n"
           "2.There are tips (If it is hard to think of) .\n"
           "\n三、About Game:\n\n"
           "1.Regular rules in the game Greedy Snake.\n"
           "2.Yellow diamonds are coins while red circulars are food.\n"
           "3.There are Best Score and Current Score on the right in the game running page.\n"
           "4.There are speed and score of each food too and they will increase as score grows.\n"
           "5.There are total coins and your goods which you should use it properly.\n"
           "6.You can go shopping.\n"
           "7.There are many modes you can explore.\n"
           "\n四、About Game Version:\n"
           " \n"
           "1.It takes plenties of version to create this immature game.\n\n"
           "etc......");

    gotoxy(65,35);
    printf("Press \"b\" to get back to menu.");
    while(1){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 'b') break;
        if(ch == 'h') HiddenGameIntro();
    }
    color(3);
    Menu();
}
```

头文件

```c
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include <time.h>//随机数
```

游戏初始设置（窗口名称、大小、引用中文库）

```c
 system("chcp 65001 > nul");//中文库
 system("title Greedy Snake");//设置窗口名称
 system("mode con cols=100 lines=40");//设置窗口大小
```

*响应键盘操作

```c
//用循环和int ch = getch();
//example：
while(1){
    int ch = getch();
    if(ch == 'q') exit(0);
    if(ch == 'b') break;
    if(ch == 'h') HiddenGameIntro();
}
//tips：上下左右键是双键值，需特殊处理
while(1){
    int ch = getch();
    
    if(ch == 224) ch = getch();//解决上下左右是双键值的问题
    
    if(ch == 'q') exit(0);
    if(ch == 'b') break;
    if(ch == 'h') HiddenGameIntro();
}
```

枚举型方便一些

```c
enum{UP = 72,LEFT = 75,RIGHT = 77,DOWN = 80};
```

隐藏光标

```c
void HideCursor()
{
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;
    curInfo.bVisible = FALSE;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);
}
```

改变颜色

```c
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
    //注：SetConsoleTextAttribute是一个API（应用程序编程接口）
    // GetConsole
    //SetCurrentConsoleFontEx();
}
```

移动光标

```c
void gotoxy(int x,int y){
    COORD position = {x,y};
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handleOut,position);
}
```

一种比较麻烦的游戏结束重新开始或回到原来模式的方法（即用全局变量参数）

```c
void Failed(){
    if(moder == 0 && model == 0 && moden == 1 && modee == 0)
        GameReplay();
    else if(moder == 1 && model == 0 && moden == 0 && modee == 0)
        RandSmallWallMode();
    else if(moder == 0 && model == 1 && moden == 0 && modee == 0)
        LongSnakeMode();
    else if(moder == 0 && model == 0 && moden == 0 && modee == 1)
        ExtremeSmallMode();
}
```

一种比较麻烦的商店体系

```c
typedef struct COIN{
    int x;
    int y;
} Coin;
Coin coin;
typedef struct GOODS{
    int shop_amount;
    int player_amount;
    int price;
} Goods;
Goods goods1_SpeedDown = {10,4,10};
Goods goods2_SpeedMid = {10,4,10};
Goods goods3_SpeedUp = {10,4,10};
Goods goods4_CoinDoubled = {10,4,10};

void Shop(){
    ShopAppearance();

    while(1){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 'b') Failed();
        if(ch == 'm') Menu();
        if(ch == '1'){
            if(totalcoins >= goods1_SpeedDown.price && goods1_SpeedDown.shop_amount > 0){
                totalcoins -= goods1_SpeedDown.price;
                goods1_SpeedDown.player_amount++;
                goods1_SpeedDown.shop_amount--;
                ShopAppearance();
                MessageBox(NULL,TEXT("Purchase successful!"),L"",MB_OK);
            }else {
                MessageBox(NULL,TEXT("Sorry, you can not buy it."),L"",MB_OK);
            }
        }
        if(ch == '2'){
            if(totalcoins >= goods2_SpeedMid.price && goods2_SpeedMid.shop_amount > 0){
                totalcoins -= goods2_SpeedMid.price;
                goods2_SpeedMid.player_amount++;
                goods2_SpeedMid.shop_amount--;
                ShopAppearance();
                MessageBox(NULL,TEXT("Purchase successful!"),L"",MB_OK);
            }else {
                MessageBox(NULL,TEXT("Sorry, you can not buy it."),L"",MB_OK);
            }
        }
        if(ch == '3'){
            if(totalcoins >= goods3_SpeedUp.price && goods3_SpeedUp.shop_amount > 0){
                totalcoins -= goods3_SpeedUp.price;
                goods3_SpeedUp.player_amount++;
                goods3_SpeedUp.shop_amount--;
                ShopAppearance();
                MessageBox(NULL,TEXT("Purchase successful!"),L"",MB_OK);
            }else {
                MessageBox(NULL,TEXT("Sorry, you can not buy it."),L"",MB_OK);
            }
        }
        if(ch == '4'){
            if(totalcoins >= goods4_CoinDoubled.price && goods4_CoinDoubled.shop_amount > 0){
                totalcoins -= goods4_CoinDoubled.price;
                goods4_CoinDoubled.player_amount++;
                goods4_CoinDoubled.shop_amount--;
                ShopAppearance();
                MessageBox(NULL,TEXT("Purchase successful!"),L"",MB_OK);
            }else {
                MessageBox(NULL,TEXT("Sorry, you can not buy it."),L"",MB_OK);
            }
        }
    }
}
```

一种比较麻烦的伪命令行界面（即用gets(str)函数输入以换行键为结束标志的字符串）

```c
void OrderPage(){
    system("cls");//清屏
    color(7);//调回白色
    OrderPageAppearance();
    while(1){
        char s[100];
        gotoxy(33,0);
        gets(s);
        if(strcmp(s,"back") == 0) Failed();
        if(strcmp(s,"quit") == 0) exit(0);
        if(strcmp(s,"go to shop") == 0) Shop();
        if(strcmp(s,"go to menu") == 0) Menu();
        if(strcmp(s,"go to LongSnakeMode") == 0) LongSnakeMode();
        if(strcmp(s,"go to RandSmallWallMode") == 0) RandSmallWallMode();
        if(strcmp(s,"go to ExtremeSmallMode") == 0) ExtremeSmallMode();
        if(strcmp(s,"color turns red") == 0){
            wallcolor = 4;
            snakeheadcolor = 4;
            snakebodycolor = 14;
        }
        if(strcmp(s,"color turns blue") == 0){
            wallcolor = 3;
            snakeheadcolor = 10;
            snakebodycolor = 10;
        }
        if(strcmp(s,"color turns purple") == 0){
            wallcolor = 5;
            snakeheadcolor = 5;
            snakebodycolor = 5;
        }
            //if(strcmp(s,"fire up") == 0) FireUp();
        if(strcmp(s,"cheat the programme") == 0){
            CheatProgramme();
            MessageBox(NULL,TEXT("You cheat the programme successful!"),L"",MB_OK);
            OrderPage();
        }
        if(strcmp(s,"The blue wind will let the world rest") == 0) EasterEgg();
        else OrderPage();
    }
}
```

弹窗

```c
MessageBox(NULL,TEXT("You can press \"b\" to begin the game now !"),L"",MB_OK);
```

大字体生成器网站

在线tools：https://tools.kalvinbg.cn/txt/ascii

