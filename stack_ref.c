struct stack {
    int *s;
    int size;
    int sp;
};

static struct stack *createstack(size_t size)
{
    struct stack *st = NULL;

    if (size == 0)
        return NULL;

    st = malloc(sizeof(struct stack));

    st->s = malloc(size);
    st->size = size;
    st->sp = -1;

    return st;
}

static void destroystack(struct stack *st)
{
    if (st == NULL)
        return;
    
    free(st->s);
    free(st);

    return;
}

static int push(struct stack *st, int val)
{
    if (st == NULL)
        return -1;
    
    if (st->sp == (st->size / sizeof(int)))
        return -2;

    st->sp++;
    st->s[st->sp] = val;

    return 0;
}

static int pop(struct stack *st, int *val)
{
    if (st == NULL)
        return -1;

    if (st->sp < 0)
        return -2;

    *val = st->s[st->sp];
    st->sp--;

    return 0;
}

static int isstackempty(struct stack *st)
{
    if (st)
        if (st->sp == -1)
            return 1;
    
    return 0;
}

static int getval(struct stack *st)
{
        return st->s[st->sp];
}

static void print_stack(struct stack *st)
{
    int i, n = (st->size / sizeof(int));

    printf("---------- Stack Start ---------\n");
    for (i = 0; i < n; i++) {
        printf("%d", st->s[i]);
        if (st->sp == i)
            printf("\t<----");
        
        printf("\n");
    }
    printf("---------- Stack End ---------\n");
}
