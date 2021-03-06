#include "Ticket_Persist.h"
int Ticket_Perst_Update(const ticket_t *data)
{
    ticket_t ret;
    int rtn  = -1;
    FILE *fp = fopen("Ticket.dat", "rb+");
    if (fp == NULL || data == NULL)
    {
        printf("file open fiaied or data is NULL\n");
        return -1;
    }
    while (!feof(fp))
    {
        fread(&ret, sizeof(ticket_t), 1, fp);
        if (ret.id == data->id)
        {
            fseek(fp, -((int)sizeof(ticket_t)), SEEK_CUR);
            fwrite(data, sizeof(ticket_t), 1, fp);
            rtn = 1;
        }
    }
    fclose(fp);
    return rtn;
}

int Ticket_Perst_Insert(ticket_list_t list)
{
    int count = 0, x;
    ticket_list_t tmp;
    FILE *fp = fopen("Ticket.dat", "ab");
    if (fp == NULL)
    {
        printf("打开失败");
        return 0;
    }
    // BUG:

    // seat_list_t seat;
    // List_Init(seat, seat_node_t);

    // schedule_t sch;
    // ticket_list_t tmp;
    // play_t play;
    // int a           = 0;
    // seat_node_t *ww = NULL;
    // Seat_Perst_SelectAll(seat);

    // int key[a + 1] = {0};
    // List_ForEach(seat, ww) { EntKey_Perst_GetNewKeys(); }
    List_ForEach(list, tmp)
    {
        fwrite(&tmp->data, sizeof(ticket_t), 1, fp);
        count++;
        // Schedule_Perst_SelectByID(tmp->data.schedule_id, &sch);
        // Play_Perst_SelectByID(sch.play_id, &play);
    }
    // seat_t data;
    // while (seat != NULL)
    // {
    //     seat = seat->next;
    //     data = seat->data;
    //     x    = fwrite(&data, sizeof(ticket_t), 1, fp);
    // }
    fclose(fp);
    return count;
}

int Ticket_Perst_Rem(int schedule_id)
{
    int found = 0;
    if (rename("Ticket.dat", "TicketTmp.dat") == -1)
    {
        printf("改名失败");
        return found;
    }
    FILE *fp  = fopen("TicketTmp.dat", "r");
    FILE *fp2 = fopen("Ticket.dat", "w");
    if (fp && fp2)
    {
        return found;
    }
    while (feof(fp))
    {
        ticket_t buf;
        fread(&buf, sizeof(ticket_t), 1, fp);
        if (buf.schedule_id == schedule_id)
        {
            found++;
        }
        else
        {
            fwrite(&buf, sizeof(ticket_t), 1, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    rename("TicketTmp.dat", "Ticket.dat");
    return found;
}
int Ticket_Perst_SelByID(int id, ticket_t *buf)
{
    int found = 0;
    FILE *fp  = fopen("Ticket.dat", "rb+");
    if (fp == NULL)
    {
        printf("Cannot open file !\n");
        exit(1);
    }
    while (!feof(fp))
    {
        ticket_t data;
        fread(&data, sizeof(ticket_t), 1, fp);
        
        if (data.id == id)
        {
            found = 1;
            *buf  = data;
            break;
        }
    }
    fclose(fp);
    return found;
}

int Ticket_Perst_SelBySchID(ticket_list_t ticket, int schedule_id)
{
    List_Free(ticket, ticket_node_t);
    int recCount = 0;
    assert(NULL != ticket);
    FILE *fp = fopen("Ticket.dat", "rb");
    if (NULL == fp)
    {
        printf("Cannot open file\n");
        return 0;
    }
    ticket_t data;
    // printf("HERE\n");
    while (!feof(fp))
    {
        if (fread(&data, sizeof(ticket_t), 1, fp))
        {
            // printf("data: %d %d\n", schedule_id, data.schedule_id);
            if (data.schedule_id == schedule_id)
            {
                ticket_node_t *newNode =
                    (ticket_node_t *)malloc(sizeof(ticket_node_t));
                if (!newNode)
                {
                    printf("Warning,Memory OverFlow!!!\n");
                    break;
                }
                newNode->data = data;
                List_AddTail(ticket, newNode);
                recCount++;
                // printf("count++\n");
            }
            // printf("read\n");
        }
    }
    // printf("over %d\n", recCount);
    fclose(fp);
    return recCount;
}