#include "Schedule_Qry.h"



int Schedule_Srv_FetchAll(schedule_list_t list)
{
    // schedule_list_t list_s;
    // List_Init(list_s, schedule_node_t);
    // play_list_t list_p;
    // List_Init(list_p, play_node_t);
    return Schedule_Perst_SelectAll(list);
}
