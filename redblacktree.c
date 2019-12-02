#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COUNT 5
#define RED 1
#define BLACK 0

struct node{
    int data;
    int color;
    struct node *parent;
    struct node *left;
    struct node *right;
};

/* Global, since all function will access them */
struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x){
    struct node *y;
    
    /* Make y's left child x's right child */
    y = x->right;
    x->right = y->left;
    if(y->left != NILL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    
    /* Make x, y's left child & y, x's parent */
    y->left = x;
    x->parent = y;
}


void right_rotate(struct node *x){
    struct node *y;

    /* Make y's right child x's left child */
    y = x->left;
    x->left = y->right;
    if(y->right != NILL){
        y->right->parent = x;
    }

    /* Make x's parent y's parent and y, x's parent's child */
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;    
    }
    else{
        x->parent->right = y;
    }

    /* Make y, x's parent and x, y's child */
    y->right = x;
    x->parent = y;
}

void display(struct node *root, int space){
    if (root == NILL) {
        return;
    }
    space += COUNT;
    display(root->right, space);
    printf("\n");
    for(int i = COUNT; i<space;i++)
        printf(" ");
    if(root->color){
        printf("(%d)\n", root->data );
    }
    else{
        printf(" %d \n", root->data );
    }
    display(root->left, space);
}

struct node *tree_search(int data){
    struct node *x;

    x = ROOT;
    while(x != NILL && x->data != data){
        if(data < x->data){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    return x;
}

struct node *tree_minimum(struct node *x){
    while(x->left != NILL){
        x = x->left;
    }
    return x;
}
void red_black_insert_fixup(struct node *z){
    while(z->parent->color == RED){

        /* z's parent is left child of z's grand parent*/
        if(z->parent == z->parent->parent->left){

            /* z's grand parent's right child is RED */
            if(z->parent->parent->right->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->right->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            /* z's grand parent's right child is not RED */
            else{
                
                /* z is z's parent's right child */
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }

        /* z's parent is z's grand parent's right child */
        else{
            
            /* z's left uncle or z's grand parent's left child is also RED */
            if(z->parent->parent->left->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->left->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            /* z's left uncle is not RED */
            else{
                /* z is z's parents left child */
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }

    ROOT->color = BLACK;
}

void red_black_insert(int data){
    struct node *z, *x, *y;
    z = malloc(sizeof(struct node));

    z->data = data;
    z->color = RED;
    z->left = NILL;
    z->right = NILL;

    x = ROOT;
    y = NILL;

    while(x != NILL){
        y = x;
        if(z->data <= x->data){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    if(y == NILL){
        ROOT = z;
    }
    else if(z->data <= y->data){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->parent = y;

    red_black_insert_fixup(z);
}

void red_black_delete_fixup(struct node *x){
    struct node *w; 

    while(x != ROOT && x->color == BLACK){
        
        if(x == x->parent->left){
            w = x->parent->right;

            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x->parent->color = BLACK;
                x = x->parent;
            }
            else{

                if(w->right->color == BLACK){
                    w->color = RED;
                    w->left->color = BLACK;
                    right_rotate(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                x->right->color = BLACK;
                left_rotate(x->parent);
                x = ROOT;       

            }

        }
        else{
            w = x->parent->left;

            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = BLACK;
                right_rotate(x->parent);
                w = x->parent->left;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x->parent->color = BLACK;
                x = x->parent;
            }
            else{

                if(w->left->color == BLACK){
                    w->color = RED;
                    w->right->color = BLACK;
                    left_rotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = ROOT;

            }
        }

    }

    x->color = BLACK;
}

/* replace node u with node v */
void red_black_transplant(struct node *u, struct node *v){
    if(u->parent == NILL){
        ROOT = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}
void red_black_delete(struct node *z){
    if (z == NILL){
        printf("The data is not found\n");
        return;
    }
    struct node *y, *x;
    int yOriginalColor;

    y = z;
    yOriginalColor = y->color;

    if(z->left == NILL){
        x = z->right;
        red_black_transplant(z, z->right);
    }
    else if(z->right == NILL){
        x = z->left;
        red_black_transplant(z, z->left);
    }
    else{
        y = tree_minimum(z->right);
        yOriginalColor = y->color;

        x = y->right;

        if(y->parent == z){
            x->parent = y;
        }
        else{
            red_black_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        red_black_transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOriginalColor == BLACK){
        red_black_delete_fixup(x);
    }
}


int main(){
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    char status[6];
    
    scanf("%s",status);
    // printf("%s\n",status);
    while(strncmp(status,"end",3)){
        
        if(!strncmp(status,"insert",6)){
            // int *data = (int*)malloc(sizeof(int));
            // scanf("%d",data);
            int data;
            scanf("%d",&data);
            // printf("%sooooo%d\n", status,*data);
            if (tree_search(data) == NILL){
                red_black_insert(data);
            }
        }
        else if(!strncmp(status,"delete",6)){
            int data;
            scanf("%d",&data);
            red_black_delete(tree_search(data));
        }
        scanf("%s",status);
        // printf("%sooooo\n", status);
    }
    display(ROOT, 0);
    return 0;
}