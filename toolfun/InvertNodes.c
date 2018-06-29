/***单链表的反序连接***/
/*Case1, 存在一个指示表头地址的全局变量*/
void InvertNodes(stk_node_t *p)
{
	if (p->next)
	{
		stk_node_t *q = p->next;
		InvertNodes(q);
		q->next = p;
		p->next = NULL;
	}
	else stk_entry = p;
}

/*Case2.1, 不存在指示表头地址的全局变量**
**输入一个入口地址，返回一个新的入口地址*/
stk_node_t *InvertNodes(stk_node_t *p)
{
	if (p->next)
	{
		stk_node_t *q = p->next, *ret;
		ret = InvertNodes(q);
		q->next = p;
		p->next = NULL;
		return ret;
	}
	else return p;
}

/*Case2.2, 不存在指示表头地址的全局变量**
**输入两个参数: 存放入口地址的地址和入口地址*/
void InvertNodes(stk_node_t **h, stk_node_t *p)
{
	if (p->next)
	{
		stk_node_t *q = p->next;
		InvertNodes(h, q);
		q->next = p;
		p->next = NULL;
	}
	else *h = p;
}


/***基于单链表的栈和队列的反序连接***/
/*返回值: 最后一个数据结点的下一结点的地址，对除该
**        函数本身外的其它调用者来说，没有多少意义*/
stk_node_t *InvertNodes(stk_node_t *p)
{
	if (p->next && p->next->data)
	{
		stk_node_t *q = p->next, *ret;
		ret = InvertNodes(q);
		q->next = p;
		p->next = ret;
		return ret;
	}
	else
	{
		stk_entry = p;
		if (!p->next)return NULL;
		else return p->next;
	}
}

void InvertNodes(stk_node_t *p, stk_node_t **k)
{
	if (p->next && p->next->data)
	{
		stk_node_t *q = p->next;
		InvertNodes(q, k);
		q->next = p;
		p->next = *k;
	}
	else
	{
		stk_entry = p;
		if(p->next)*k = p->next;
	}
}
