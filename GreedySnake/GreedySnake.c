#include<stdio.h>
//#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include <time.h>
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


int main(){
    GameBegin();
    return 0;
}

//开始游戏
void GameBegin(){
    //确定游戏初始设置
    srand(time(0));//srand()很耗性能，千万不要引用多次！！！TT，一次就好！
    HideCursor();
    system("chcp 65001 > nul");//中文库
    system("title Greedy Snake");
    system("mode con cols=100 lines=40");

    //进入标题页、欢迎页与目录页
    GameTitle();
    Welcome();
    Menu();
}
//欢迎
void Welcome(){

    printf("\n\n");
    printf("       \t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t       Welcome To the Greedy Snake World\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t Here , let us have fun !\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\tPress \"Enter\" to begin the game \t\t\t~\n");
    printf("       \t~\t\t\t    and enter the menu \t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~\t\t\t\t\t\tOr press \"q\" to quit the game .\t~\n");
    printf("       \t~\t\t\t\t\t\t\t\t\t\t~\n");
    printf("       \t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    //暂停
    while(1){
        int ch = getch();
        if(ch == 13) break;
        if(ch == 'q') exit(0);
    }
    //清屏
    system("cls");
}
//游戏标题
void GameTitle(){
    system("cls");

    color(14);//14:light yellow
    gotoxy(18,5);
    printf("  ____                   _         ____              _        \n");
    gotoxy(18,6);
    printf(" / ___|_ __ ___  ___  __| |_   _  / ___| _ __   __ _| | _____ \n");
    gotoxy(18,7);
    printf("| |  _| '__/ _ \\/ _ \\/ _` | | | | \\___ \\| '_ \\ / _` | |/ / _ \\\n");
    gotoxy(18,8);
    printf("| |_| | | |  __/  __/ (_| | |_| |  ___) | | | | (_| |   <  __/\n");
    gotoxy(18,9);
    printf(" \\____|_|  \\___|\\___|\\__,_|\\__, | |____/|_| |_|\\__,_|_|\\_\\___|\n");
    gotoxy(18,10);
    printf("                           |___/                              \n");
    gotoxy(18,11);
    printf(" ");

    color(12);
    gotoxy(18,11);
    printf("______________________________________________________________");
    gotoxy(18,12);
    printf("______________________________________________________________");

    color(7);
    gotoxy(0,23);
    printf(" Tips:");
    gotoxy(5,24);
    printf("Click to pause and press \"Enter\" to resume.");
    gotoxy(5,25);
    printf("Press \"q\" to quit.");
    gotoxy(5,26);
    printf("Press \"Enter\" to turn on curvature drive.");
    gotoxy(66,25);
    printf("Creator : Windloong•Black");
    gotoxy(66,26);
    printf("Creation Time : 2021/12/24 — ?");

    gotoxy(42,17);
    printf("Loading");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    gotoxy(42,17);
    printf("Loading       ");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    gotoxy(49,17);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);
    printf("*");
    if(kbhit()){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 13) goto OverrideTime;
    }
    Sleep(500);

    OverrideTime:
    system("cls");
    color(7);
}
//进入菜单
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
void MenuAppearance(){
    system("cls");

    color(3);//14:light yellow

    printf("            *\n"
           "         **\n"
           "      ***\n"
           "   ****\n"
           "*****\n"
           "   ****\n"
           "      ***\n"
           "         **\n"
           "            *");
    gotoxy(83,0);
    printf("    *\n");
    gotoxy(83,1);
    printf(      "      **\n");
    gotoxy(83,2);
    printf("        ***\n");
    gotoxy(83,3);
    printf(    "          ****\n");
    gotoxy(83,4);
    printf(  "            *****\n");
    gotoxy(83,5);
    printf(  "          ****\n");
    gotoxy(83,6);
    printf( "        ***\n");
    gotoxy(83,7);
    printf("      **\n");
    gotoxy(83,8);
    printf(  "    *");

    gotoxy(35,0);
    printf(" __  __                  \n");
    gotoxy(35,1);
    printf("|  \\/  | ___ _ __  _   _ \n");
    gotoxy(35,2);
    printf("| |\\/| |/ _ \\ '_ \\| | | |\n");
    gotoxy(35,3);
    printf("| |  | |  __/ | | | |_| |\n");
    gotoxy(35,4);
    printf("|_|  |_|\\___|_| |_|\\__,_|\n");
    gotoxy(35,5);
    printf("                         ");


    color(4);
    gotoxy(32,6);
    printf("_________________________________");
    gotoxy(32,7);
    printf("_________________________________");

    color(3);
    gotoxy(40,10);
    printf("Begin The Game");
    gotoxy(43,11);
    printf("开始游戏");

    color(3);
    gotoxy(40,13);
    printf("Game Information");
    gotoxy(43,14);
    printf("游戏介绍");

    color(3);
    gotoxy(38,16);
    printf("Information About Us");
    gotoxy(43,17);
    printf("关于我们");

    color(3);
    gotoxy(40,19);
    printf("Give us praise");
    gotoxy(43,20);
    printf("好评支持");

    color(3);
    gotoxy(40,22);
    printf("Exit The Game");
    gotoxy(43,23);
    printf("退出游戏");

    color(2);
    gotoxy(0,28);
    printf("\n"
           "                  □□□□■  \n"
           "                □□\n"
           "              □□\n"
           "              □\n"
           "      □□□□□\n"
           "      □□□□□□□□□□□□□□□□\n"
           "□□□□□□□□□□□□□□□□□□□\n"
           "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");

    color(12);
    gotoxy(4,28);
    printf("●");
    gotoxy(34,29);
    printf("●");
    gotoxy(65,30);
    printf("●");
    gotoxy(80,28);
    printf("●");
    gotoxy(90,24);
    printf("●");
    gotoxy(90,16);
    printf("●");

    color(14);
    gotoxy(42,30);
    printf("◆");
    gotoxy(50,29);
    printf("◆");
    gotoxy(84,26);
    printf("◆");
    gotoxy(92,20);
    printf("◆");
    gotoxy(81,12);
    printf("◆");

}
void StressOption(int option){
    switch(option) {
        case 1:
            color(1);
            gotoxy(40, 10);
            printf("Begin The Game");
            gotoxy(43, 11);
            printf("开始游戏");
            break;

        case 2:
            color(1);
            gotoxy(40, 13);
            printf("Game Information");
            gotoxy(43, 14);
            printf("游戏介绍");
            break;
        case 3:
            color(1);
            gotoxy(38, 16);
            printf("Information About Us");
            gotoxy(43, 17);
            printf("关于我们");
            break;
        case 4:
            color(1);
            gotoxy(40, 19);
            printf("Give us praise");
            gotoxy(43, 20);
            printf("好评支持");
            break;
        case 5:
            color(1);
            gotoxy(40, 22);
            printf("Exit The Game");
            gotoxy(43, 23);
            printf("退出游戏");
            break;
    }
}
void RenewPrvOption(int prvoption){
    switch(prvoption) {
        case 1:
            color(3);
            gotoxy(40, 10);
            printf("Begin The Game");
            gotoxy(43, 11);
            printf("开始游戏");
            break;

        case 2:
            color(3);
            gotoxy(40, 13);
            printf("Game Information");
            gotoxy(43, 14);
            printf("游戏介绍");
            break;
        case 3:
            color(3);
            gotoxy(38, 16);
            printf("Information About Us");
            gotoxy(43, 17);
            printf("关于我们");
            break;
        case 4:
            color(3);
            gotoxy(40, 19);
            printf("Give us praise");
            gotoxy(43, 20);
            printf("好评支持");
            break;
        case 5:
            color(3);
            gotoxy(40, 22);
            printf("Exit The Game");
            gotoxy(43, 23);
            printf("退出游戏");
            break;
    }
}
void ChooseOption(int option){
    if(option == 1) {
        optionDefault = 1;
        GameReplay();
    }
    if(option == 2){
        optionDefault = 1;
        GameIntro();
    }
    if(option == 3){
        optionDefault = 1;
        AboutUs();
    }
    if(option == 4){
        optionDefault = 1;
        MessageBox(NULL,TEXT("Thank you very much !!!"),L"",MB_OK);
    }
    if(option == 5){
        exit(0);
    }

}
//添加提示
void Notes(){
    color(2);
    gotoxy(0,31);
    printf("\n"
           "                  □□□□■  \n"
           "                □□\n"
           "              □□\n"
           "      □□□□□\n"
           "      □□□□□□□□□□□□□□□□\n"
           "□□□□□□□□□□□□□□□□□□□\n"
           "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
    color(3);
    gotoxy(94,36);
    printf("■■■");
    gotoxy(94,37);
    printf("■");

    color(14);
    gotoxy(64,1);
    printf("□▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫□");
    gotoxy(64,2);
    printf("‖ Best Score : %-15d",maxscore);
    gotoxy(96,2);
    printf("‖");
    gotoxy(64,3);
    printf("□▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫□");
    color(2);
    gotoxy(72,7);
    printf("Speed : %3d",200 - speed);
    color(12);
    gotoxy(67,4);
    printf("Current Snake Length : %d",curlen);
    if(recordbroken){
        color(14);
        gotoxy(64,5);
        printf("(Broken)");
    }
    color(12);
    gotoxy(72,5);
    printf("Current Score : %-d",curscore);
    color(6);
    gotoxy(67,6);
    printf("Score of each food : %-d",foodweight);
    color(7);
    gotoxy(65,9);
    printf("To set up :");
    gotoxy(65,11);
    printf("Press \"Enter\" to move the snake");
    gotoxy(65,12);
    printf("Press \"Space\" to pause the snake");
    gotoxy(65,13);
    printf("Press \"i\" to initialize the game");
    gotoxy(65,14);
    printf("Press \"l\" for ");
    color(2);
    printf("LongSnake");
    color(7);
    printf(" mode");
    gotoxy(65,15);
    printf("Press \"r\" for ");
    color(3);
    printf("RandSmallWall");
    color(7);
    printf(" mode");
    gotoxy(65,16);
    printf("Press \"e\" for ");
    color(14);
    printf("ExtremeSmallWall");
    color(7);
    printf(" mode");
    gotoxy(65,17);
    printf("Press \"m\" to enter the menu");
    gotoxy(65,18);
    printf("Press \"p\" to go purchasing");
    gotoxy(65,19);
    printf("Press \"q\" to quit the game");
    color(6);
    gotoxy(78,22);
    printf("SpeedDown(\"1\"):%2d 件", goods1_SpeedDown.player_amount);
    gotoxy(78,23);
    printf("SpeedMid(\"2\") :%2d 件", goods2_SpeedMid.player_amount);
    gotoxy(78,24);
    printf("SpeedUp(\"3\")  :%2d 件", goods3_SpeedUp.player_amount);
    gotoxy(73,25);
    printf("CoinDoubled(\"4\")   :%2d 件", goods4_CoinDoubled.player_amount);

    if(coindoubled) {
        color(12);
        gotoxy(65,27);
        printf("Coin Doubled!");
    }

    color(14);
    gotoxy(80,27);
    printf("Total Coins : %d $", totalcoins);
    color(7);
}
//创建地图
void CreateMap()
{
    color(wallcolor);//1:deep blue 2:green 3:light blue 4:red 5:purple 6:brown 7:white 8:grey
    for(int i = 0;i < wallxlen;i += 2){
        gotoxy(i,0);
        printf("■");
        gotoxy(i,wallylen - 1);
        printf("■");
    }
    for(int i = 0;i < wallylen;i++){
        gotoxy(0,i);
        printf("■");
        gotoxy(wallxlen - 2,i);
        printf("■");
    }
}
//移动光标
void gotoxy(int x,int y){
    COORD position = {x,y};
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handleOut,position);
}
//生成初始蛇
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
//运行游戏
void GameRun() {
    Notes();
    CreateMap();
    CreateSnake();
    CreateFood();
    CreateCoin();
    //暂停以准备开始
    while(1){
        int ch = getch();
        if(ch == 13) break;//回车
        if(ch == 'q') exit(0);
        if(ch == 'i') GameReplay();
        if(ch == 'l') LongSnakeMode();
        if(ch == 'r') RandSmallWallMode();
        if(ch == 'e') ExtremeSmallMode();
        if(ch == 'h') OrderPage();
        if(ch == 'm') Menu();
        if(ch == 'p') Shop();
        if(ch == '1'&& goods1_SpeedDown.player_amount > 0) {
            speed = 140;
            speed_change = 0;
            goods1_SpeedDown.player_amount--;
            Notes();
        }
        if(ch == '2'&& goods2_SpeedMid.player_amount > 0) {
            speed = 100;
            speed_change = 0;
            goods2_SpeedMid.player_amount--;
            Notes();
        }
        if(ch == '3'&& goods3_SpeedUp.player_amount > 0) {
            speed = 60;
            speed_change = 0;
            goods3_SpeedUp.player_amount--;
            Notes();
        }
        if(ch == '4' && goods4_CoinDoubled.player_amount > 0) {
            coindoubled = 1;
            goods4_CoinDoubled.player_amount--;
            Notes();
        }
    }
    //蛇移动中
    while (1) {
        int curdirection = direction;
        int ch;
        if (kbhit()) {
            //不要直接用ch作为MoveSnake（）的参数，因为不输入时ch是垃圾值?
            ch = getch();
            if(ch == 224) ch = getch();//解决上下左右是双键值的问题
            switch(ch){
                case 72 :
                    direction = UP;
                    break;
                case 'w':
                    direction = UP;
                    break;
                case 75 :
                    direction = LEFT;
                    break;
                case 'a' :
                    direction = LEFT;
                    break;
                case 77:
                    direction = RIGHT;
                    break;
                case 'd':
                    direction = RIGHT;
                    break;
                case 80:
                    direction = DOWN;
                    break;
                case 's':
                    direction = DOWN;
                    break;
                case 'q':
                    exit(0);
                    break;
                case ' ':
                    while(1){
                        int newch = getch();
                        if(newch == 13) break;
                        if(newch == 'i') GameReplay();
                        if(newch == 'l') LongSnakeMode();
                        if(newch == 'r') RandSmallWallMode();
                        if(newch == 'e') ExtremeSmallMode();
                        if(newch == 'h') OrderPage();
                        if(newch == 'q') exit(0);
                        if(newch == 'm') Menu();
                        if(newch == 'p') Shop();
                        if(newch == '1'&& goods1_SpeedDown.player_amount > 0) {//1键
                            speed = 140;
                            speed_change = 0;
                            goods1_SpeedDown.player_amount--;
                            Notes();
                        }
                        if(newch == '2'&& goods2_SpeedMid.player_amount > 0) {
                            speed = 100;
                            speed_change = 0;
                            goods2_SpeedMid.player_amount--;
                            Notes();
                        }
                        if(newch == '3'&& goods3_SpeedUp.player_amount > 0) {
                            speed = 60;
                            speed_change = 0;
                            goods3_SpeedUp.player_amount--;
                            Notes();
                        }
                        if(newch == '4' && goods4_CoinDoubled.player_amount > 0) {
                            coindoubled = 1;
                            goods4_CoinDoubled.player_amount--;
                            Notes();
                        }
                    }

                    break;
                case 'i':
                    GameReplay();
                    break;
                case 'l':
                    LongSnakeMode();
                    break;
                case 'r':
                    RandSmallWallMode();
                    break;
                case 'e':
                    ExtremeSmallMode();
                case 'h':
                    OrderPage();
                case 'm':
                    Menu();
                    break;
                case 'p':
                    Shop();
                    break;
                case '1'://1键
                    if(goods4_CoinDoubled.player_amount > 0)
                    { speed = 140;
                        speed_change = 0;
                        goods1_SpeedDown.player_amount--;
                        Notes();}
                    break;
                case '2':
                { if(goods4_CoinDoubled.player_amount > 0)
                        speed = 100;
                    speed_change = 0;
                    goods2_SpeedMid.player_amount--;
                    Notes();}
                    break;
                case '3':
                    if(goods3_SpeedUp.player_amount > 0)
                    { speed = 60;
                        speed_change = 0;
                        goods3_SpeedUp.player_amount--;
                        Notes();}
                    break;
                case '4':
                    if(goods4_CoinDoubled.player_amount > 0) {
                        coindoubled = 1;
                        goods4_CoinDoubled.player_amount--;
                        Notes();
                    }
                    break;
            }
        }

        //不能180度转动
        if(curdirection + direction == 152)
            direction = curdirection;
        MoveSnake(direction);
        Sleep(speed);
    }
}
//移动蛇身
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
int is_contradicted(int x,int y){
    if(x <= 1|| x >= wallxlen - 3 || y <= 0 || y >= wallylen - 1) return 1;
    Snake *p = linked_list_head;
    while(p != NULL && p->next != NULL){
        if(p->x == x && p->y == y) return 1;
        p = p->next;
    }
    return 0;
}
void HideCursor()
{
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;
    curInfo.bVisible = FALSE;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);
}
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
    //注：SetConsoleTextAttribute是一个API（应用程序编程接口）
    // GetConsole
    //SetCurrentConsoleFontEx();
}
void GameReplay(){
    system("cls");//清屏
    color(7);//调回白色
    //全局变量赋回初值
    moder = 0,model = 0,moden = 1,modee = 0;
    recordbroken = 0;
    wallxlen = 60;
    wallylen = 30;
    bornx = 12;
    borny = 6;
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
//进入商城
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
void ShopAppearance(){
    system("cls");

    color(14);//14:light yellow
    gotoxy(35,0);
    printf(" ____  _                 \n");
    gotoxy(35,1);
    printf("/ ___|| |__   ___  _ __  \n");
    gotoxy(35,2);
    printf("\\___ \\| '_ \\ / _ \\| '_ \\ \n");
    gotoxy(35,3);
    printf(" ___) | | | | (_) | |_) |\n");
    gotoxy(35,4);
    printf("|____/|_| |_|\\___/| .__/ \n");
    gotoxy(35,5);
    printf("                  |_|    ");

    color(14);
    gotoxy(0,6);
    printf("Press key to buy and use");
    gotoxy(0,7);
    printf("Press \"b\" to get back");

    color(14);
    gotoxy(80,7);
    printf("Total Coins : %d $", totalcoins);

    color(7);
    gotoxy(32,6);
    printf("_________________________________");
    gotoxy(32,7);
    printf("_________________________________");

    color(6);
    gotoxy(0,9);
    printf("Goods' PressKey\tGoods' Name\tGoods' usage\t\tGoods' Price\tGoods' Stock\tYou own");
    color(14);
    gotoxy(0,11);
    printf("\"1\"\t\tSpeedDown\tSpeed stays at 60\t%d$\t\t%d件\t\t%d件\n\n",goods1_SpeedDown.price,goods1_SpeedDown.shop_amount,goods1_SpeedDown.player_amount);
    printf("\"2\"\t\tSpeedMid\tSpeed stays at 100\t%d$\t\t%d件\t\t%d件\n\n",goods2_SpeedMid.price,goods2_SpeedMid.shop_amount,goods2_SpeedMid.player_amount);
    printf("\"3\"\t\tSpeedUp\t\tSpeed reaches 140 !!!\t%d$\t\t%d件\t\t%d件\n\n",goods3_SpeedUp.price,goods3_SpeedUp.shop_amount,goods3_SpeedUp.player_amount);
    printf("\"4\"\t\tCoinDoubled\tCoin's value doubled\t%d$\t\t%d件\t\t%d件\n\n",goods4_CoinDoubled.price,goods4_CoinDoubled.shop_amount,goods4_CoinDoubled.player_amount);



}
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
void AboutUs(){
    system("cls");
    color(7);
    printf("\n                                     Something About Us");
    gotoxy(0,4);
    printf("多次修改，多个版本，还有很多隐藏内容等你发现！\n"
           "                                              ——windloong");
    color(14);
    gotoxy(0,34);
    printf("恭喜你，发现了这里的Tips：\n"
           "在某些界面中按下 “h“ (hidden)会有惊喜哦");

    color(7);
    gotoxy(65,35);
    printf("Press \"b\" to get back to menu.");
    while(1){
        int ch = getch();
        if(ch == 'q') exit(0);
        if(ch == 'b') break;
        if(ch == 'h') HiddenAboutUs();
    }
    color(3);
    Menu();
}
void LongSnakeMode(){
    system("cls");//清屏
    color(7);//调回白色
    //全局变量赋回初值
    moder = 0,model = 1,moden = 0,modee = 0;
    recordbroken = 0;
    wallxlen = 60;
    wallylen = 30;
    bornx = 2;
    borny = 2;
    bornlen = 24;
    curlen = 25;
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
void RandSmallWallMode(){
    system("cls");//清屏
    color(7);//调回白色
    //全局变量赋回初值
    moder = 1,model = 0,moden = 0,modee = 0;
    recordbroken = 0;
    int rx = 2 * ((rand() + 666 ) % 8 + 12);
    int ry = (rand() + 999) % 10 + 10;
    wallxlen = rx;
    wallylen = ry;
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
void OrderPageAppearance(){
    gotoxy(0,0);
    printf("windloong@GreedySnake-windows:/# ");
}
void CheatProgramme(){
    goods1_SpeedDown.player_amount = 999;
    goods1_SpeedDown.shop_amount = 999;
    goods2_SpeedMid.player_amount = 999;
    goods2_SpeedMid.shop_amount = 999;
    goods3_SpeedUp.player_amount = 999;
    goods3_SpeedUp.shop_amount = 999;
    goods4_CoinDoubled.player_amount = 999;
    goods4_CoinDoubled.shop_amount = 999;
    totalcoins = 9999;
}
void EasterEgg(){
    system("cls");
    color(14);
    gotoxy(0,0);
    printf("The nonsense of some walking people:\n");
    color(7);
    printf("\n"
           "\n"
           "Sometimes we lose ourselves in the inner volume.\n"
           "Just like Greedy Snake,\n"
           "as we eat more and more food,\n"
           "we cannot help moving more swiftly,\n"
           "which also makes us more easily\n"
           "to loss and die.\n"
           "If you feel sorry for yourself because you are an underdog\n"
           "If you feel anxious about yourself because others are working desperately\n"
           "If you feel regretful because you cannot reach the high expectation of your parents \n"
           "Wake up!\n"
           "Everyone can have everyone's way of life!\n"
           "Because human beings are not qualified to judge anyone's life\n"
           "Even if it's another high sounding speech\n"
           "So,\n"
           "How about going out and having a breath?\n"
           "Outside\n"
           "The blue wind is always blowing\n"
           "through valleys, plains, seas, snow peaks\n"
           "brushing the soul\n"
           "bringing the peace");
    gotoxy(65,35);
    printf("Press \"b\" to get back to menu.");
    while(1){
        char ch = getch();
        if(ch == 'b') OrderPage();
        if(ch == 'q') exit(0);
    }
}
void HiddenAboutUs(){
    system("cls");
    printf("\nhhh,but the hidden pages are not in this page.");
    gotoxy(60,35);
    printf("Press \"b\" to get back to AboutUs page.");
    while(1){
        char ch = getch();
        if(ch == 'q')exit(0);
        if(ch == 'b')AboutUs();
    }
}
void HiddenGameIntro(){
    system("cls");
    color(14);
    printf("\n\nOh,you find one hidden page\nIt is about some orders in the OrderPage.");
    color(7);
    gotoxy(0,8);
    printf("1.\"back\"\n"
           "2.\"quit\"\n"
           "3.\"go to shop\"\n"
           "4.\"go to menu\"\n"
           "5.\"go to LongSnakeMode\"\n"
           "6.\"go to RandSmallWallMode\"\n"
           "7.\"go to ExtremeSmallMode\"\n"
           "8.\"cheat the programme\"\n"
           "9.\"color turns red\"\n"
           "10.\"color turns blue\"\n"
           "11.\"color turns purple\"\n"
           "12.a hidden order for a easter egg");
    gotoxy(60,35);
    printf("Press \"b\" to get back to GameIntro page.");
    while(1){
        char ch = getch();
        if(ch == 'q')exit(0);
        if(ch == 'b')GameIntro();
        if(ch == 'h') HiddenEasterEgg();
    }
}
void HiddenEasterEgg(){
    system("cls");
    color(14);
    printf("\n\nIt really surprises me that you can enter this page.\nIt is about a order to enter EasterEgg page.");
    color(3);
    gotoxy(0,8);
    printf("\"The blue wind will let the world rest\"");
    color(7);

    gotoxy(55,35);
    printf("Press \"b\" to get back to HiddenGameIntro page.");
    while(1){
        char ch = getch();
        if(ch == 'q')exit(0);
        if(ch == 'b')HiddenGameIntro();
    }
}

