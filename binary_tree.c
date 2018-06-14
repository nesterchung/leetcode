typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

void tree_insert(node_t*, int);
void tree_print(node_t*);
void tree_print_dfs(node_t*);

int main(void) {
    return 0;
}
