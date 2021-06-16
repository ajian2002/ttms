/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_01
 * File name: Studio_c
 * Description : 演出厅用例业务逻辑层
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include "Studio.h"

#include <assert.h>
#include <stdlib.h>

#include "../Persistence/Studio_Persist.h"

int Studio_Srv_Add(studio_t *data) { return Studio_Perst_Insert(data); }

int Studio_Srv_Modify(const studio_t *data)
{
    return Studio_Perst_Update(data);
}

int Studio_Srv_DeleteByID(int ID) { return Studio_Perst_DeleteByID(ID); }

int Studio_Srv_FetchByID(int ID, studio_t *buf)
{
    return Studio_Perst_SelectByID(ID, buf);
}

int Studio_Srv_FetchAll(studio_list_t list)
{
    return Studio_Perst_SelectAll(list);
}

studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID)
{
    assert(NULL != list);
    studio_node_t *ptr = list->next;
    while (ptr != list)
    {
        if (ptr->data.id == ID)
            return ptr;
        else
            ptr = ptr->next;
    }

    return NULL;
}
