#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1

struct node{
    int key;
    int color;
    struct node *parent;
    struct node *left;
    struct node *right;
};

/* Global, since all function will access them */
struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(int key);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);
void red_black_transplant(struct node *u, struct node *v);
void red_black_delete(struct node *z);
void red_black_delete_fixup(struct node *x);

int main(){
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    printf("RED-BLACK TREE INSERT\n\n");
    
    srand(time(NULL));
    int array[20];
    for (int i=0; i<20; i++){

        array[i] = rand()%50;
    } 
    for (int i=0; i<20; i++){
        if (tree_search(array[i]) == NILL){
            red_black_insert(array[i]);
        }        
    } 

    printf("TREE PRINT\n\n");
    tree_print(ROOT);
    printf("\n");

    printf("\nTREE INSERT\n");
    printf("INSERT 5: \n");
    if (tree_search(5) == NILL){
        red_black_insert(5);
    } else{
        printf("The key exists\n");
    }  
    tree_print(ROOT);
    printf("\n");

    printf("INSERT 7: \n");
    if (tree_search(7) == NILL){
        red_black_insert(7);
    } else{
        printf("The key exists\n");
    }
    tree_print(ROOT);
    printf("\n");
    printf("INSERT 51: \n");
    if (tree_search(51) == NILL){
        red_black_insert(51);
    }else{
        printf("The key exists\n");
    }   
    tree_print(ROOT);
    printf("\n");
    printf("INSERT 17: \n");
    if (tree_search(17) == NILL){
        red_black_insert(17);
    }else{
        printf("The key exists\n");
    }   
    tree_print(ROOT);
    printf("\n");
    


    printf("\nTREE DELETE\n");
    printf("delete 17: ");
    red_black_delete(tree_search(17));
    tree_print(ROOT);
    printf("\n");
    printf("delete 5: ");
    red_black_delete(tree_search(5));
    tree_print(ROOT);
    printf("\n");
    printf("delete 51: ");
    red_black_delete(tree_search(51));
    tree_print(ROOT);
    printf("\n");
    printf("delete 17: ");
    red_black_delete(tree_search(17));
    tree_print(ROOT);
    printf("\n");

    return 0;
}

/* Print tree keys by inorder tree walk */

void tree_print(struct node *x){
    if(x != NILL){
        tree_print(x->left);
        printf("%d\t", x->key);
        tree_print(x->right);
    }
}

struct node *tree_search(int key){
    struct node *x;

    x = ROOT;
    while(x != NILL && x->key != key){
        if(key < x->key){
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


void red_black_insert(int key){
    struct node *z, *x, *y;
    z = malloc(sizeof(struct node));

    z->key = key;
    z->color = RED;
    z->left = NILL;
    z->right = NILL;

    x = ROOT;
    y = NILL;

    while(x != NILL){
        y = x;
        if(z->key <= x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    if(y == NILL){
        ROOT = z;
    }
    else if(z->key <= y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->parent = y;

    red_black_insert_fixup(z);
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


void left_rotate(struct node *x){
    struct node *y;
    
    /* Make y's left child x's right child */
    y = x->right;
    x->right = y->left;
    if(y->left != NILL){
        y->left->parent = x;
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