#ifndef BigInteger_h
#define BigInteger_h
struct BigInteger
{
    struct node *head;
    int length;
    int sign;
};
struct node
{
    int data;
    struct node *next;
};

struct BigInteger initialize(char *);
struct BigInteger add(struct BigInteger, struct BigInteger);
struct BigInteger sub(struct BigInteger, struct BigInteger);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
struct BigInteger div2(struct BigInteger, struct BigInteger);

struct BigInteger mod(struct BigInteger, struct BigInteger);

struct BigInteger truncateZeros(struct BigInteger);
struct BigInteger reverse(struct BigInteger);
void display(struct BigInteger);
void insertHead(struct node **, int);
void insertTail(struct node **, int);
int compare(struct BigInteger, struct BigInteger);
#endif