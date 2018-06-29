#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MIN_INT (1 << (8 * sizeof(int) - 1))

#define STK_MAX 10
#define QUE_MAX STK_MAX

#define IN_LEN (STK_MAX * 11)

typedef struct stk_node
{
	unsigned data;
	struct stk_node *next;
}stk_node_t;

stk_node_t *stk_entry;

void QUE_Init()
{
	register unsigned i = 0;
	stk_node_t *p = (stk_node_t *)calloc(QUE_MAX, sizeof(stk_node_t));
	stk_entry = p;
	while (i++ < QUE_MAX - 1)
	{
		p->next = p + 1;
		p++;
	}
}

void STK_Init()
{
	register unsigned i = 0;
	stk_node_t *p = (stk_node_t *)malloc(sizeof(stk_node_t));
	memset(p, 0, sizeof(stk_node_t));
	stk_entry = p;

	do
	{
		p = (stk_node_t *)malloc(sizeof(stk_node_t));
		memset(p, 0, sizeof(stk_node_t));
		p->next = stk_entry;
		stk_entry = p;
	}while(++i < STK_MAX -1);
}

void QUE_Destroy()
{
	stk_node_t *p, *q;
	p = q = stk_entry;
	while (p)
	{
		if (p < q)q = p;
		p = p->next;
	}
	free(q);
}

void STK_Destroy()
{
	stk_node_t *t, *p = stk_entry;
	while (p)
	{
		t = p;
		p = p->next;
		free(t);
	}
}

int QUE_Add(const unsigned num)
{
	stk_node_t *p = stk_entry;
	while (p && p->data)p = p->next;
	if (!p)return -1;
	p->data = num;
	return 0;
}

#if STK_MAX < 2
#error STK_MAX must be more than 2
#endif
int STK_Push(const unsigned num)
{
	stk_node_t *p = stk_entry;
	while(p->next->next)p = p->next;
	if(p->next->data)return -1;
	p->next->data = num;
	p->next->next = stk_entry;
	stk_entry = p->next;
	p->next = NULL;
	return 0;
}

int QUE_Get(unsigned * const num)
{
	stk_node_t *p = stk_entry;
	if(!p->data)return -1;
	*num = p->data;
	while (p->next->next)p = p->next;
	p->next->next = stk_entry;
	p = stk_entry;
	stk_entry = p->next;
	memset(p, 0, sizeof(stk_node_t));
	return 0;
}

#define STK_Pop(A) QUE_Get(A)

void QUE_GetAndPrintAll()
{
	unsigned num, i = 0;
	puts("print all numbers in stack: ");
	while (!STK_Pop(&num))
	{
		if(i++)printf(" %d", num);
		else printf("%d", num);
	}
	putchar('\n');
}

#define STK_PopAndPrintAll() QUE_GetAndPrintAll()

void QUE_PrintAll()
{
	unsigned i = 0;
	stk_node_t *p = stk_entry;
	while(p->data)
	{
		if(i++)printf(" %d", p->data);
		else printf("%d", p->data);
		p = p->next;
	}
	putchar('\n');
}

#define STK_PrintAll() QUE_PrintAll()

#if defined(USE_QUEUE) & defined(USE_STACK)
#error Macro USE_QUEUE and USE_STACK conflict.
#elif !defined(USE_QUEUE) & !defined(USE_STACK)
#error Macro USE_QUEUE or USE_STACK has not been defined.
#elif defined(USE_QUEUE)
int main()
{
	int num;
	unsigned *q;
	QUE_Init();

	puts("Input positive numbers to initialize the queue, end with negative or 0.");
	do
	{
		scanf("%d", &num);
		//scanf_s("%d", &num);
	} while ((num > 0 && !QUE_Add(num)));

	q = (unsigned *)&num;
	QUE_Get(q) ? puts("queue null.") : 0;
	QUE_Get(q) ? puts("queue null.") : 0;

	QUE_Add(30) ? puts("queue full.") : 0;
	QUE_Add(40) ? puts("queue full.") : 0;
	QUE_Add(50) ? puts("queue full.") : 0;

	QUE_GetAndPrintAll();

	QUE_Destroy();

	while (getchar() != '\n');
	printf("\nPress any keys to continue...");
	getchar();
	return EXIT_SUCCESS;
}
#else
int main()
{
	int l, num;
	unsigned *q;
	STK_Init();

	char *p, in[IN_LEN] = { 0 };
	printf("Input positive numbers to initialize the stack. no more than %d\n", STK_MAX);

	fgets(in, IN_LEN, stdin);
	in[strlen(in) - 1] = 0;

	//filtration of 0, not yet realized.

	for (p = in; *p != '-' && *p != 0; p++);
	if (*p)
	{
		printf("Negative number detected, exit...");
		getchar();
		return EXIT_FAILURE;
	}

	for (l = 0, p = in; *p;)
	{
		l = sscanf(p, "%d", &num);
		//l = sscanf_s(p, "%d", &num);
		if (STK_Push(num))break;
		//while (*p != ' ' && *p != '\t' && *p != 0)p++;
		p += l; l = 0;
		while (*p == ' ' || *p == '\t')p++;
	}

	q = (unsigned *)&num;
	STK_Pop(q) ? puts("Stack null.") : 0;
	STK_Pop(q) ? puts("Stack null.") : 0;

	STK_Push(30) ? puts("Stack full.") : 0;
	STK_Push(40) ? puts("Stack full.") : 0;
	STK_Push(50) ? puts("Stack full.") : 0;

	STK_PopAndPrintAll();

	STK_Destroy();

	printf("\nPress any keys to continue...");
	getchar();
	return EXIT_SUCCESS;
}
#endif
