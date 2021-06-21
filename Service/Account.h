#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Common/List.h"
#include "../Persistence/Account_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
void Account_Srv_InitSys();
/**
 * @brief 验证系统用户的用户名和密码
 *
 * @param usrName 字符数组类型，存储待验证的用户名
 * @param pwd 字符数组类型，存储待验证的用户名的密码
 * @return int 返回1表示存在，返回0表示不存在
 */
int Account_Srv_Verify(char usrName[], char pwd[]);
int Account_Srv_Add(account_t *data);
int Account_Srv_Modify(account_t *data);  //实际根据用户名来找到修改处
int Account_Srv_DeleteByID(int usrID);
int Account_Srv_FetchAll(account_list_t list);
account_node_t *Account_Srv_FindByUsrName(account_list_t list, char usrName[]);
account_t Account_Srv_FetchbyUser(char usrName[]);
#endif