#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define NUM_Year '0'
#define Char_Year '1'
#define LOWYEAR 1950
#define HIGHYEAR 2050

typedef struct
{
    long unsigned id;
    long unsigned payment;
    char* name;

    union FirstYearOfWork
    {
        unsigned  StartYearsHL;
        char Hys[7];
    }StartWork;
}
Worker;


typedef struct WorkerList
{
    Worker* data;
    struct WorkerList* next;
}WorkerList;

void PrintWorker(char type, const Worker* w);//פונקצייה שמדפיסה עובד חדש
Worker* CreateWorker(char type);//פונקצייה שיוצרת עובד חדש
WorkerList* addWorker(WorkerList* head, Worker* W);//פונקציה שמוסיפה עובד חדש לראש רשימת העובדים הקיימים
int index(WorkerList* head, long unsigned id);//פונקציה המחזירה את מיקומו של העובד ברשימה
WorkerList* deleteWorstWorker(WorkerList* head);//פונקציה המוחקת את העובד בעל השכר הנמוך ביותר
void UpdateWorker(WorkerList* head, float percent);//העלאת שכר באחוזים
WorkerList* reverse(WorkerList* head);//הופכת את הרשימה
void FreeWorkers(WorkerList* head);//משחררת מהזכרון את המשתנחם
void PrintList(WorkerList* head);
void main()
{
    WorkerList* head = NULL; //רשימה ריקה
    Worker* worker = NULL;
    char typeyear, yuserSelt;
    WorkerList* list = head, workerToPrint;
    float percent;
    int i, locwoker, place;
    unsigned long id, idP;
    while (1)
    {
        printf(" \n to Create Worker enter  'C' ,\n \
to Print Worker enter 'P'\n, to ListPrint Worker enter 'LP'\n, to update prcent to all Worker enter 'H' ,\n   to find Worker enter 'F' ,\n\
 to delete worst Worker enter 'D' ,\n to swap the order list enter 'S' ,\n to delet ALL eWorker  enter 'L'\n to exit  menu enter 'X'\n");
        fseek(stdin, 0, SEEK_END);
        scanf("%c", &yuserSelt);
        switch (yuserSelt)
        {
        case 'C': //יצירת כרטיסית עובד
        {
            printf("to create worker, please select a type  of year 0 - for Numbers, 1 - Hebrew:\n");
            do
            {
                scanf("%c", &typeyear);

                if (typeyear != '0' && typeyear != '1')
                    printf("tRY AGAIN\n");

            } while (typeyear != '0' && typeyear != '1'); //קולט סוג שנה ליצירת עובד
            worker = CreateWorker(typeyear);
            head = addWorker(head, worker);
            break;

        }
        case'P'://הדפסת כרטיסית עובד
        {
            if (!head)
            {
                printf("Empty list");
                exit(0);
            }


            printf("select id of worker For print Location ");
            scanf("%lu", &idP); //מחזיר מיקום שנקלט
            place = index(head, idP);
            WorkerList* curr = head;
            WorkerList* ptr = NULL;

            while (curr != NULL && idP != curr->data->id)
            {
                ptr = curr;
                curr = curr->next;

            }
            if (LOWYEAR < &(curr->data->StartWork) && &(curr->data->StartWork) < HIGHYEAR)
                PrintWorker('0', curr->data);
            else
                PrintWorker('1', curr->data);

            break;
        }
        case'LP':
        {
            PrintList(head);
            break;
        }
        case 'H':
        {
            printf("how many percent you want to add?\n");
            scanf("%f", &percent);
            UpdateWorker(head, percent);
            break;
        }
        case'F':
        {
            printf("select id of worker to print him inpormation ");
            place = scanf(index(head, "%lu")); //מחזיר מיקום שנקלט
            printf("the place of the worker in a list is %d", place);
            break;
        }
        case 'D':
        {
            head = deleteWorstWorker(head); //פלט מחיקת עובד עני*
            printf("show update list, \n");

            break;
        }
        case 'S':
        {
            head = reverse(head);
            break;
        }
        case'L':
        {
            FreeWorkers(head);
            break;
        }
        case'X':
        {
            exit(1);
        }
        default:
            printf("wrong Char try again  ");
            break;
        }
    }
}
void PrintWorker(char type, const Worker* w)
{
    printf("\n Printing list : \n");
    printf("ID: %Id\n", w->id);
    printf("Payment:  %Id\n", w->payment);
    printf("Name : %s\n", w->name);

    switch (type)
    {
    case Char_Year:
        printf("First Year hebrew:%c\n", w->StartWork.Hys);//הדפסת תאריך תחילת עבודה תאריך עברי,תווים
        break;
    case NUM_Year:
        printf("First Year numbers:%d\n", w->StartWork.StartYearsHL);//הדפסת תאריך תחילת עבודה תאריך לועזי מספרים
        break;
    default:
        printf("Worong Format Try again\n");
        break;
    }
}
Worker* CreateWorker(char type)
{
    char* V[100];
    Worker* Wnew = (Worker*)malloc(sizeof(Worker));//CHECK
    if (!Wnew) { puts("allocation faild"); exit(0); }

    printf("enter Worker id: ");
    scanf("%lu", &(Wnew->id));
    printf("\nenter Worker Payment: ");
    scanf("%lu", &(Wnew->payment));

    printf("\nenter Worker name: ");
    scanf("%s", V);
    Wnew->name = (char*)malloc(strlen(V) + 1);
    if (!Wnew->name) { puts("allocation faild"); exit(0); }

    strcpy(Wnew->name, V);


    switch (type)
    {
    case Char_Year:
        fseek(stdin, 0, SEEK_END);
        printf("\nYear Start Workig in Hebrew : ");
        gets_s(Wnew->StartWork.Hys, 6);
        break;
    case NUM_Year:
        do {
            printf("\nYear Start Workig Num : ");
            scanf("%d", &Wnew->StartWork.StartYearsHL);
            if ((Wnew->StartWork.StartYearsHL >= HIGHYEAR) ||
                (Wnew->StartWork.StartYearsHL < LOWYEAR))puts("Value shoulde be Right numbesr\n");

        } while ((Wnew->StartWork.StartYearsHL > HIGHYEAR) || (Wnew->StartWork.StartYearsHL < LOWYEAR));
        break;
    }
    return Wnew;

}

WorkerList* addWorker(WorkerList* head, Worker* Wp) //מחזיר את ראש הרשימה המעודכן
{
    WorkerList* newWorkerlist;
    assert(newWorkerlist = (struct WorkerList*)malloc(sizeof(WorkerList)));
    newWorkerlist->data = Wp;
    if (!head || (head->data->payment > Wp->payment)) {//if list is empty or lowest payment
        newWorkerlist->next = head;
        return newWorkerlist;
    }
    WorkerList* curr = head;
    WorkerList* ptr = NULL;

    while (curr != NULL && (curr->data->payment < Wp->payment))
    {
        ptr = curr;
        curr = curr->next;
    }
    newWorkerlist->next = curr;
    ptr->next = newWorkerlist;
    return head;

}
int index(WorkerList* head, long unsigned id)
{
    int count = -1;
    WorkerList* x = head;
    if (x == NULL)
        return count;
    for (x = head; x->next != NULL; x = x->next)
    {
        if (x->data->id == id)
        {
            count++;
            return count;
        }

    }
}
int indexR(WorkerList* head, long unsigned id)
{
    WorkerList* x = head;
    if (x->next != NULL)
        return(indexR(x->next, id));
    {
        if (x->data->id == id)
            return x;
    }
    return -1;

}
WorkerList* deleteWorstWorker(WorkerList* head)//מוחק איבר מתחילת הרשימה
{
    if (head == NULL)
        return head;

    WorkerList* tmp = head;
    head = head->next;
    free(tmp);
    return head;

}
void UpdateWorker(WorkerList* head, float percent)
{
    WorkerList* x = head;
    if (head == NULL)
        return 0;
    while (x != NULL)
    {
        x->data->payment = x->data->payment + x->data->payment * percent;
        x = x->next;
    }
}

WorkerList* reverse(WorkerList* head)
{
    WorkerList* p = head->next;
    WorkerList* x = head;
    WorkerList* newhead;
    if (x->next == NULL)
    {

        newhead = x; //משתנה גלובלי
        return (newhead);
    }
    return(reverse(x->next));
    p->next = x;

}
void FreeWorkers(WorkerList* head)
{
    WorkerList* x = head;
    if (x->next == NULL)
        return 0;
    for (x = head; x->next != NULL; x = x->next)
        free(x->data);

}
void PrintList(WorkerList* head)
{
    if (head == NULL)
    {
        printf("Empty list\n");
        return 0;
    }
    WorkerList* ptt = head;
    while (ptt != NULL)
    {
        if (LOWYEAR < &(ptt->data->StartWork) && &(ptt->data->StartWork) < HIGHYEAR)
            PrintWorker('0', ptt->data);
        else
            PrintWorker('1', ptt->data);
        ptt = ptt->next;

    }

}

