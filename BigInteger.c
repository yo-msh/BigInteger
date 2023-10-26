#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "BigInteger.h"

struct BigInteger reverse(struct BigInteger a)
{
    struct node *prev = NULL;
    struct node *current = a.head;
    struct node *next = NULL;
    while (current != NULL)
    {
        next = current->next;

        current->next = prev;
        prev = current;
        current = next;
    }
    a.head = prev;
    return a;
}
int isZero(struct BigInteger a)
{
    if (!(a.head) || (a.length == 1 && a.head->data == 0))
    {
        return 1;
    }
    struct node *itr = a.head;
    while (itr != NULL)
    {
        if (itr->data != 0)
            return 0;
        itr = itr->next;
    }
    return 1;
}

struct node *createNode(int value)
{
    struct node *t = (struct node *)malloc(sizeof(struct node));
    if (t == NULL)
    {
        printf("Memory ERROR!\n");
        return NULL;
    }
    t->data = value;
    t->next = NULL;
    return t;
}
struct node *addition(struct node *num1, struct node *num2)
{
    int sum, carry = 0;
    struct node *res = NULL;
    struct node *itr = NULL;
    while (num1 && num2)
    {
        sum = num1->data + num2->data + carry;
        carry = sum / 10;
        if (res == NULL)
        {
            res = createNode(sum % 10);
            itr = res;
        }
        else
        {
            itr->next = createNode(sum % 10);
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1)
    {
        sum = num1->data + carry;
        carry = sum / 10;
        itr->next = createNode(sum % 10);
        num1 = num1->next;
        itr = itr->next;
    }
    while (num2)
    {
        sum = num2->data + carry;
        carry = sum / 10;
        itr->next = createNode(sum % 10);
        num2 = num2->next;
        itr = itr->next;
    }
    if (carry > 0)
    {
        itr->next = createNode(carry);
    }
    return res;
}

int compare(struct BigInteger a, struct BigInteger b)
{

    if (a.length > b.length)
        return 1;
    else if (a.length < b.length)
        return -1;
    else
    {
        a = reverse(a);
        b = reverse(b);

        struct node *i1 = a.head, *i2 = b.head;

        while (i1 != NULL && i2 != NULL)
        {
            if (i1->data > i2->data)
            {
                a = reverse(a);
                b = reverse(b);
                return 1;
            }
            else if (i1->data < i2->data)
            {
                a = reverse(a);
                b = reverse(b);
                return -1;
            }
            i1 = i1->next;
            i2 = i2->next;
        }
    }

    return 0;
}
void displayLLrev(struct node *temp)
{
    if (temp != NULL)
    {
        displayLLrev(temp->next);
        printf("%d", temp->data);
    }

    return;
}

void display(struct BigInteger a)
{
    struct node *temp = a.head;
    if (a.sign == -1)
    {
        printf("-");
    }
    displayLLrev(temp);
}

void insertHead(struct node **head, int data)
{
    struct node *itr = *head, *temp = (struct node *)malloc(sizeof(struct node));

    if (temp == NULL)
    {
        printf("dma not allocated");
        return;
    }

    temp->data = data;
    temp->next = NULL;

    if ((*head) == NULL)
    {
        *head = temp;
        return;
    }

    temp->next = *head;
    *head = temp;
    return;
}

void insertEnd(struct node **head, int data)
{
    struct node *itr = *head, *temp = (struct node *)malloc(sizeof(struct node));

    if (!temp)
        return;

    temp->data = data;
    temp->next = NULL;

    if ((*head) == NULL)
    {
        *head = temp;
        return;
    }

    while (itr->next != NULL)
        itr = itr->next;

    itr->next = temp;
    return;
}

struct BigInteger initialize(char *s)
{
    struct BigInteger newStruct;
    newStruct.head = NULL;
    newStruct.length = 0;
    newStruct.sign = 1;

    struct node *temp = NULL;
    int i = 0, cnt = 0, sign = 1;
    ;

    if (s[i] == '-')
    {
        newStruct.sign = -1;
        i++;
    }

    for (; s[i] != '\0'; i++)
    {
        insertHead(&temp, s[i] - '0');
        cnt++;
    }

    newStruct.length = cnt;
    newStruct.head = temp;
    return newStruct;
}

struct BigInteger truncateZeros(struct BigInteger num)
{

    num = reverse(num);
    while (num.head != NULL && num.head->data == 0)
    {
        struct node *temp = num.head;
        num.head = num.head->next;
        free(temp);
        num.length--;

        if (num.length == 0)
        {
            num.sign = 1; // Set the sign to positive if the number is zero
            break;
        }
    }

    // Ensure that the head node stores the unit place
    if (num.head == NULL)
    {
        insertEnd(&(num.head), 0);
        num.length = 1;
        num.sign = 1;
    }
    num = reverse(num);

    return num;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger newStruct;
    newStruct.head = NULL;
    newStruct.length = 0;

    int sum = 0, carry = 0, cnt = 0;

    struct node *i1 = a.head, *i2 = b.head, *i3 = newStruct.head;

    if (a.sign == b.sign)
    {
        newStruct.sign = a.sign;

        while (i1 != NULL && i2 != NULL)
        {
            sum = i1->data + i2->data + carry;
            carry = sum / 10;
            sum = sum % 10;

            insertEnd(&i3, sum);
            cnt++;
            i1 = i1->next;
            i2 = i2->next;
        }

        while (i1 != NULL)
        {
            sum = i1->data + carry;
            carry = sum / 10;
            sum = sum % 10;
            insertEnd(&i3, sum);
            cnt++;
            i1 = i1->next;
        }

        while (i2 != NULL)
        {
            sum = i2->data + carry;
            carry = sum / 10;
            sum = sum % 10;
            insertEnd(&i3, sum);
            cnt++;
            i2 = i2->next;
        }
        if (carry != 0)
        {
            insertEnd(&i3, carry);
            cnt++;
        }
    }
    else
    {
        if (a.sign == -1)
        {
            a.sign = 1;
            newStruct = sub(b, a);
        }
        else
        {
            b.sign = 1;
            newStruct = sub(a, b);
        }
    }

    newStruct.head = i3;
    newStruct.length = cnt;

    return newStruct;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger newStruct;
    newStruct.head = NULL;
    newStruct.length = 0;

    int borrow = 0, diff = 0, cnt = 0;

    struct node *i1 = a.head, *i2 = b.head, *i3 = newStruct.head;

    if ((a.sign == -1) && (b.sign == 1))
    {
        b.sign = -1;
        newStruct = add(a, b);
        return newStruct;
    }
    else if ((a.sign == 1) && (b.sign == 1))
    {
        if (compare(a, b) == -1)
        {
            newStruct = sub(b, a);
            newStruct.sign = -1;
            return newStruct;
        }
    }
    else if ((a.sign == -1) && (b.sign == -1))
    {
        a.sign = 1;
        b.sign = 1;
        newStruct = sub(b, a);
        return newStruct;
    }

    while (i1 != NULL && i2 != NULL)
    {
        diff = i1->data - i2->data - borrow;
        borrow = 0;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }

        insertEnd(&i3, diff);
        cnt++;
        i1 = i1->next;
        i2 = i2->next;
    }

    while (i1 != NULL)
    {
        diff = i1->data - borrow;
        borrow = 0;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }

        insertEnd(&i3, diff);
        cnt++;
        i1 = i1->next;
    }

    newStruct.head = i3;
    newStruct.length = cnt;

    truncateZeros(newStruct);
    return newStruct;
}

struct node *multiply(struct node *num1, struct node *num2)
{
    struct node *result = createNode(0);
    struct node *currentResult = NULL;
    int pos = 0; // For the position of the second number's digit

    while (num2)
    {
        int carry = 0;
        struct node *num1Copy = num1;
        currentResult = NULL;
        for (int i = 0; i < pos; i++)
            insertHead(&currentResult, 0); // Initialize with trailing zeros

        while (num1Copy)
        {
            int product = 0;
            product = (num1Copy->data) * (num2->data) + carry;
            carry = product / 10;
            insertEnd(&currentResult, product % 10); // Append the result to the currentResult
            num1Copy = num1Copy->next;
        }

        if (carry > 0)
        {
            insertEnd(&currentResult, carry); // If there is a carry, add it
        }

        result = addition(result, currentResult); // Add currentResult to the overall result
        num2 = num2->next;
        pos++;
    }
    return result;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger result;
    result.head = (struct node *)malloc(sizeof(struct node));

    if (isZero(a) || isZero(b))
    {
        result.head = createNode(0);
        result.sign = 1;
    }
    else
    {
        result.head = multiply(a.head, b.head);
        result.sign = a.sign * b.sign;
    }
    return result;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger newStruct, temp, copyA, copyB;
    copyA = a;
    copyB = b;
    newStruct.head = NULL;
    newStruct.length = 0;

    long long int quotient = 0, cnt = 0;

    struct node *i1 = a.head, *i2 = b.head, *i3 = newStruct.head;
    if (compare(a, b) == -1)
    {
        insertEnd(&i3, 0);
        newStruct.head = i3;
        return newStruct;
    }

    else if (compare(a, b) == 0)
    {
        if (a.sign == b.sign)
        {
            insertEnd(&i3, 1);
            newStruct.head = i3;
            return newStruct;
        }
    }
    else
    {
        newStruct.sign = a.sign * b.sign;


        while (compare(a, b) != -1)
        {
            a = sub(a, b);
            quotient++;
        }

        insertEnd(&i3, quotient);
        // cnt++;

        newStruct.head = i3;
        newStruct.length = quotient;
        return newStruct;
    }
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger newStruct;
    newStruct.head = NULL;
    newStruct.length = 0;

    newStruct = add(a,b);
    a = sub(a,b);
    b = add(a,b);
    newStruct = sub(newStruct,b);
    newStruct = add(newStruct,a);
    newStruct = sub(newStruct,a);
    newStruct.sign = 1;
    // int sum = 0, carry = 0, cnt = 0;

    // struct node *i1 = a.head, *i2 = b.head, *i3 = newStruct.head;

    // if (a.sign == b.sign)
    // {
    //     newStruct.sign = a.sign;

    //     while (i1 != NULL && i2 != NULL)
    //     {
    //         sum = i1->data + i2->data + carry;
    //         carry = sum / 10;
    //         sum = sum % 10;

    //         insertEnd(&i3, sum);
    //         cnt++;
    //         i1 = i1->next;
    //         i2 = i2->next;
    //     }

    //     while (i1 != NULL)
    //     {
    //         sum = i1->data + carry;
    //         carry = sum / 10;
    //         sum = sum % 10;
    //         insertEnd(&i3, sum);
    //         cnt++;
    //         i1 = i1->next;
    //     }

    //     while (i2 != NULL)
    //     {
    //         sum = i2->data + carry;
    //         carry = sum / 10;
    //         sum = sum % 10;
    //         insertEnd(&i3, sum);
    //         cnt++;
    //         i2 = i2->next;
    //     }
    //     if (carry != 0)
    //     {
    //         insertEnd(&i3, carry);
    //         cnt++;
    //     }
    // }
    // else
    // {
    //     if (a.sign == -1)
    //     {
    //         a.sign = 1;
    //         newStruct = sub(b, a);
    //     }
    //     else
    //     {
    //         b.sign = 1;
    //         newStruct = sub(a, b);
    //     }
    // }

    // newStruct.head = i3;
    // newStruct.length = cnt;

    return newStruct;
}