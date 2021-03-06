#ifndef SALE_UI_H_
#define SALE_UI_H_
#include <stdio.h>

#include "../Common/Common.h"
#include "../Common/List.h"
#include "../Persistence/Sale_Persist.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Ticket.h"

/**
 * @brief 管理售票主界面
 */
void Sale_UI_MgtEntry(void);

/**
 * @brief 根据剧目id显示演出计划
 * @param playID int剧目id
 */
void Sale_UI_ShowScheduler(int playID);

/**
 * @brief 售票
 * @param tickList 票列表
 * @param seatList 座位列表
 * @return int 售出票的座位id
 */
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList);

/**
 * @brief 退票
 */
void Sale_UI_RetfundTicket(void);

//显示演出票
void Sale_UI_ShowTicket(play_t p_t);

#endif