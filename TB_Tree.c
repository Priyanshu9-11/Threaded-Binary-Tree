#include <stdio.h>
#include <stdlib.h>
struct bintree {
    int info;
    struct bintree *left, *right;
    int leftthread, rightthread;
};
typedef struct bintree node;
node *insucc(node *s) {
    if (s->rightthread == 1) {
        return s->right;
    }
    s = s->right;
    while (s->leftthread != 1) {
        s = s->left;
    }
    return s;
}


void tbtinorder(node *s) {
    if (s == NULL) {
        return;
    }

    // Move to the leftmost node
    while (s->left != NULL) {
        s = s->left;
    }

    // Traverse the tree using inorder successor
    while (s != NULL) {
        printf("%d ", s->info);
        s = insucc(s);
    }
}


node* createNode(int info) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->info = info;
    newNode->left = newNode->right = NULL;
    newNode->leftthread = newNode->rightthread = 1;
    return newNode;
}


node* insert(node* root, int info) {
    node* newNode = createNode(info);
    node* current = root;
    node* parent = NULL;

    
    while (current != NULL) {
        parent = current;

        if (info < current->info) {
            if (current->leftthread == 0) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->rightthread == 0) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    if (parent == NULL) {
        root = newNode;
    } else if (info < parent->info) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftthread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rightthread = 0;
        parent->right = newNode;
    }

    return root;
}

int main() {
    node* root = NULL;
    int choice, val;

    
    while (1) {
        printf("\n1. Insert\n2. Inorder Traversal\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Inorder traversal of the threaded binary tree: ");
                tbtinorder(root);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
