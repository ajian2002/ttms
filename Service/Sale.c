#include "Sale.h"


int Sale_Srv_Add(sale_t* data) { return Sale_Perst_Insert(data); }
int Sale_Srv_FetchByTicketID(int ticket_id, sale_t* sale)
{
    return Sale_Perst_SelByTicketID(ticket_id, sale);
}