size_t totalMemoryUsage(list *head)
{
    size_t sum = 0;
    for (list *p = head; p != NULL; p = p->next) {
        sum += p->size;
    }
    return sum;
}

