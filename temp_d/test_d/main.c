#include	<stdlib.h>
#include	<stdio.h>


typedef struct s_node {
    int data;           //data that the node holds
    struct s_node* left;  //pointer to the left-hand-side node
    struct s_node* right;  //pointer to the right-hand-side node
} t_node;


t_node* creates_node(int data) {
    t_node* news_node;

	news_node = (t_node*)malloc(sizeof(t_node));
    news_node->data = data;
    news_node->left = NULL;
    news_node->right = NULL;
    return news_node;
}

int main(void) {
    // crete nodes
    t_node* root = creates_node(1);
    t_node* node2 = creates_node(2);
    t_node* node3 = creates_node(3);
    t_node* node4 = creates_node(4);
    t_node* node5 = creates_node(5);

    // create a tree structure
    root->left = node2;
    root->right = node3;
    node2->left = node4;
    node2->right = node5;

    // display data
    printf(" -%d\n", root->right->data);
    printf("%d\n", root->data);
    printf(" -%d\n", root->left->data);
    printf("   -%d\n", root->left->left->data);
    printf("   -%d\n", root->left->right->data);
    

    // free memory
    free(root);
    free(node2);
    free(node3);
    free(node4);
    free(node5);

    return 0;
}
