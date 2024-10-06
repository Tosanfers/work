#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int size = 0;
typedef struct Node
{
    int id;
    int data;          // 数据域，存储节点数据
    struct Node *next; // 指针域，指向下一个节点
} Node;

Node **FindPointerByData(Node **head, int TargetData);
Node *FindPointerById(Node **head, int id);
int AddAtHead(Node **head, int id, int data);
int AddAtTail(Node **head, int id, int data);
int AddAfterId(Node **head, int TargetId, int id, int data);
void DelByData(Node **head, int TargetData);
int DelById(Node **head, int id);
int UpdataByData(Node **head, int OutData, int ExpectData);
int UpdataById(Node **head, int id, int ExpectData);
void FreeList(Node **head);

int main()
{

    Node *head = NULL;

    // 测试代码
    AddAtHead(&head, 1, 100);
    AddAtTail(&head, 2, 200);
    AddAtTail(&head, 3, 100);
    AddAfterId(&head, 2, 8, 200);

    // 打印链表的内容
    Node *current = head;
    printf("链表:\n");
    while (current != NULL)
    {
        printf("ID: %d, Data: %d\n", current->id, current->data);
        current = current->next;
    }

    // 删除含有数据100的节点
    UpdataByData(&head, 100, 3);
    DelById(&head, 2);

    // 打印链表的内容
    printf("删除100后:\n");
    current = head;
    while (current != NULL)
    {
        printf("ID: %d, Data: %d\n", current->id, current->data);
        current = current->next;
    }

    // 释放链表内存
    FreeList(&head);

    return 0;
}

int AddAtHead(Node **head, int id, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));//为新节点分配内存
    if (!newNode)
    {
        printf("内存分配失败\n");
        return 0;
    }
    newNode->id = id;
    newNode->data = data;//数据写入
    newNode->next = *head;//节点更新
    *head = newNode;
    return 1;
}
int AddAtTail(Node **head, int id, int data)
{
    Node *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }//遍历至链表尾部

    Node *newNode = (Node *)malloc(sizeof(Node));//重复注释
    if (!newNode)
    {
        printf("内存分配失败\n");
        return 0;
    }

    newNode->id = id;
    newNode->data = data;
    newNode->next = NULL;
    current->next = newNode;
    return 1;
}
int AddAfterId(Node **head, int TargetId, int id, int data)
{
    Node *current = FindPointerById(head, TargetId);//寻找目标节点
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("内存分配失败\n");
        return 0;
    }
    newNode->id = id;
    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;
    return 1;
}
void DelByData(Node **head, int TargetData)
{
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data == TargetData)
        {
            if (prev == NULL)
            {
                // 如果要删除的是头节点
                *head = current->next;
                free(current);
                current = *head; // 继续遍历下一个节点
            }
            else
            {
                // 删除当前节点
                prev->next = current->next;
                free(current);
                current = prev->next; // 继续遍历下一个节点
            }
        }
        else
        {
            // 移动到下一个节点
            prev = current;
            current = current->next;
        }
    }
}
int DelById(Node **head, int id)
{

    Node *temp = *head;
    Node *prev = NULL;

    // 如果头节点就是要删除的节点
    if (temp != NULL && temp->id == id)
    {
        *head = temp->next; // 头节点更新为下一个节点
        free(temp);         // 释放当前节点
        return 1;           // 成功返回1
    }

    // 查找要删除的节点
    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    // 未找到节点
    if (temp == NULL)
        return 0;

    // 解除链接并删除节点
    prev->next = temp->next;
    free(temp);
    return 1; // 成功返回1
}
Node **FindPointerByData(Node **head, int TargetData)
{
    Node *current = *head;
    Node **nodes = NULL; // 初始化一个空指针
    int num = 0;

    while (current != NULL)
    {

        if (current->data == TargetData)
        {
            nodes = (Node **)realloc(nodes, sizeof(int) * (num + 1));//动态分配内存
            nodes[num] = current;//写入指针
            num++;
        }
        current = current->next;
    }
    if (nodes == NULL)
    {
        printf("没有此数据\n");
        return NULL;
    }
    printf("记得释放内存");
    size = num;
    return nodes;
    // 记得释放内存
}
Node *FindPointerById(Node **head, int id)
{
    Node *current = *head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current; // 返回节点指针
        }
        current = current->next;
    }
    return NULL; // 未找到返回NULL
}
int FindDataById(Node **head, int id)
{
    Node *temp = FindPointerById(head, id);
    if (temp == NULL)
    {
        printf("没有此id\n");
        return false;
    }
    return temp->data;
}
int UpdataByData(Node **head, int OutData, int ExpectData)
{
    Node *current = *head;
    Node **nodes = FindPointerByData(head, OutData);//获取指针数组
    if (nodes == NULL)
        return 0;
    for (int i = 0; i < size; i++)
    {
        (nodes[i])->data = ExpectData;
    }//遍历修改
    free(nodes);//记得释放内存
    return 1;
}
int UpdataById(Node **head, int id, int ExpectData)
{
    Node *node = FindPointerById(head, id);
    if (node != NULL)
    {
        node->data = ExpectData;
        return 1; 
    }
    return 0; 
}
void FreeList(Node **head)
{
    Node *current = *head;
    Node *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL; // 将头指针设为NULL
}