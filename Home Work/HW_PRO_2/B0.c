uint64_t findMaxBlock(list *head)
{
    if (head == NULL) return 0;

    uint64_t max_addr = head->address;
    size_t   max_size = head->size;

    for (list *p = head->next; p != NULL; p = p->next) {
        if (p->size > max_size) {
            max_size = p->size;
            max_addr = p->address;
        }
    }
    return max_addr;
}
