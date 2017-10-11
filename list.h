struct handler_node {
    void *data;
    struct node *next;
};

struct node *create_list();
void append(struct node *list, void *data);
void free_list(struct node *list);
