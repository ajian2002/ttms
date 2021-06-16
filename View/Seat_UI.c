/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_02
 * File name: Seat_UI.c
 * Description : 设置座位用例界面层
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include "Seat_UI.h"

#include <stdio.h>

#include "../Common/List.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"

/*
表识符：TTMS_SCU_Seat_UI_S2C
函数功能：根据座位状态获取界面显示符号。
参数说明：status为seat_status_t类型，表示座位状态。
返 回 值：字符型，表示座位的界面显示符号。
*/
inline char Seat_UI_Status2Char(seat_status_t status)
{
    if (status == SEAT_GOOD)
    {
        return '○';
    }
    else if (status == SEAT_NONE)
    {
        return '●';
    }
    else
    {
        return '*';
    }
}

/*
标识符：TTMS_SCU_Seat_UI_C2S
函数功能：根据输入符号获取座位状态。
参数说明：statusChar为字符型，表示设置座位的输入符号。
返 回 值：seat_status_t类型，表示座位的状态。
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) { return SEAT_NONE; }

/*
标识符：TTMS_SCU_Seat_UI_MgtEnt
函数功能：界面层管理座位的入口函数，显示当前的座位数据，并提供座位数据添加、修改、删除功能操作的入口。
参数说明：roomID为整型，是需要设置座位的演出厅ID。
返 回 值：无。
*/
void Seat_UI_MgtEntry(int roomID)
{
    studio_t *buf = NULL;  //存储放映厅信息
    if (Studio_Srv_FetchByID(roomID, buf) == 0)
    {
        printf("不存在此放映厅\n");
        return;
    }
    seat_list_t list = NULL;  //存储座位的链表
    List_Init(list, seat_node_t);
    if (Seat_Srv_FetchByRoomID(list, roomID) == 0)
    {
        printf("此放映厅座位未初始化\n");
        int rowsCount, colsCount;
        while (1)
        {
            printf("输入座位行数:");
            if (scanf("%d", &rowsCount) != 1 || rowsCount <= 0)
            {
                printf("输入有误,请重新输入\n");
                continue;
            }
            printf("输入座位列数:");
            if (scanf("%d", &colsCount) != 1 || colsCount <= 0)
            {
                printf("输入有误,请重新输入\n");
                continue;
            }
            break;
        }
        Seat_Srv_RoomInit(list, roomID, rowsCount, colsCount);  //座位初始化
        studio_t data = {buf->id, buf->name, rowsCount, colsCount,
                         rowsCount * colsCount};
        Studio_Srv_Modify(&data);
    }
    else
    {
        seat_node_t *curPos;
        while (1)
        {
            printf("%d影厅座位情况如下\n", roomID);
            int cnt = 0;
            List_ForEach(list, curPos)
            {
                printf("%c ", Seat_UI_Status2Char(curPos->data.status));
                cnt++;
                if (cnt == buf->colsCount)
                {
                    if (seat[i][j] == NONE)
                    {
                        printf("%c ", NONE);
                    }
                    else
                    {
                        printf("%c ", Seat_UI_Status2Char(seat[i][j]));
                    }
                }
                printf("\n");
            }
            printf(
                "[A]dd    添加座位\n"
                "[U]pdate 修改座位\n"
                "[D]elete 删除座位\n"
                "[R]eturn 返回上一层\n"
                "输入您的选择\n");
            fflush(stdin);
            char choice;
            scanf("%c", choice);
            switch (choice)
            {
                case 'A':
                case 'a':
                    Seat_UI_Add(list, roomID, buf->rowsCount, buf->colsCount);
                    break;
                case 'u':
                case 'U':
                    Seat_UI_Modify(list, buf->rowsCount, buf->colsCount);
                    break;
                case 'd':
                case 'D':
                    Seat_UI_Delete(list, buf->rowsCount, buf->colsCount);
                    break;
                case 'r':
                case 'R':
                    return;
                    break;
                default:
                    printf("输入有误,请重新输入\n");
                    break;
            }
        }
    }
}

/*

识符：TTMS_SCU_Seat_UI_Add
函数功能：用于添加一个新的座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，
         第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功添加了座位的标志。
//输入一个座位
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column)
{
    int newRecCount = 0;
rec:
    printf("\n=======================================================\n");
    printf("****************  增加座位界面  ****************\n");
    printf("-------------------------------------------------------\n");
    printf("输入待添加的座位行和列\n");
    int newRow, newCol;
    scanf("%d%d", &newRow, &newCol);
    if (newRow <= 0 || newCol <= 0 || newRow > row || newCol > column)
    {
        printf("输入有误,请核实后操作");
        return newRecCount;
    }
    if (Seat_Srv_FindByRowCol(list, newRow, newCol))
    {
        printf("此座位已存在,请核实后操作\n");
        return newRecCount;
    }
    printf("输入此座位状态\n");
    printf(
        "%c:有座位\n"
        "%c:无座位\n"
        "%c:损坏的座位\n",
        CHAR_SEAT_GOOD, CHAR_SEAT_NONE, CHAR_SEAT_BROKEN);
    char char_status;
    fflush(stdin);
    scanf("%c", &char_status);
    if (char_status == CHAR_SEAT_GOOD || char_status == CHAR_SEAT_NONE ||
        char_status == CHAR_SEAT_BROKEN)
    {
        seat_t data = {
            0,       //座位id
            roomID,  //所在演出厅id
            newRow,  //座位行号
            newCol,  //座位列号
            Seat_UI_Char2Status(char_status),
        };
        if (Seat_Srv_Add(&data))  //文件中添加
        {
            seat_node_t *node = (seat_node_t *)malloc(sizeof(seat_node_t));
            node->data        = data;
            Seat_Srv_AddToSoftedList(list, node);  //链表中添加
            printf("增加成功\n");
            newRecCount++;
        }
        else
        {
            printf("增加失败\n");
        }
        printf("继续添加输入y");
        char choice;
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == 'y')
        {
            goto rec;
        }
        else
        {
            return newRecCount;
        }
    }
    else
    {
        printf("状态输入有误\n");
        return 0;
    }
}

/*
标识符：TTMS_SCU_Seat_UI_Mod
函数功能：用于修改一个座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_UI_Modify(seat_list_t list, int row, int column)
{
    printf("\n=======================================================\n");
    printf("****************  修改座位状态  ****************\n");
    printf("-------------------------------------------------------\n");
    seat_node_t *nodePtr = Seat_Srv_FindByRowCol(list, row, column);
    if (nodePtr == NULL)
    {
        printf("此座位不存在\n");
        return 0;
    }
    printf(
        "%c:有座位\n"
        "%c:无座位\n"
        "%c:损坏的座位\n",
        CHAR_SEAT_GOOD, CHAR_SEAT_NONE, CHAR_SEAT_BROKEN);
    printf("%02d行%02d列座位状态为:%c", nodePtr->data.row, nodePtr->data.column,
           Seat_UI_Status2Char(nodePtr->data.status));
    printf("请输入修改后座位的状态\n");
    char char_status;
    fflush(stdin);
    scanf("%c", &char_status);
    if (char_status == CHAR_SEAT_GOOD || char_status == CHAR_SEAT_NONE ||
        char_status == CHAR_SEAT_BROKEN)
    {
        nodePtr->data.status = Seat_UI_Char2Status(char_status);  //链表中修改
        return Seat_Srv_Modify(&nodePtr->data);  //文件中修改
    }
    else
    {
        printf("状态输入有误\n");
        return 0;
    }
}

/*
标识符：TTMS_SCU_Seat_UI_Del
函数功能：用于删除一个座位的数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_UI_Delete(seat_list_t list, int row, int column)
{
    printf("\n=======================================================\n");
    printf("****************  删除座位界面  ****************\n");
    printf("-------------------------------------------------------\n");
    seat_node_t *node = Seat_Srv_FindByRowCol(list, row, column);
    if (node)
    {
        if (Seat_Srv_DeleteByID(node->data.id))  //将座位从文件中删除
        {
            List_DelNode(node);  //将座位从链表中删除
            printf("删除成功\n");
            return 1;
        }
        else
        {
            printf("删除失败\n");
            return 0;
        }
    }
    else
    {
        printf("不存在此座位\n");
        return 0;
    }
}
