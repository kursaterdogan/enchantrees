#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node *Tree;

Tree newNode(int key);
Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int x);
void preOrder(Tree root);
void inOrder(Tree root);
void postOrder(Tree root);
void mirror(Tree root);
int size(Tree root);
int height(Tree root);
int numOfNodesInGivenDepth(Tree root, int l);

Tree addNew(Tree n, int key)
{
    // printf("%d====\n",key);
    n = insertNode(n, key);
    // postOrder(n);
    return n;
}

Tree modTree(Tree root, Tree n, int mod)
{
    if (root != NULL)
    {
        if (root->data % mod == 0)
            n = addNew(n, root->data);
        modTree(root->left, n, mod);
        modTree(root->right, n, mod);
    }
    return n;
}

int main()
{
    // A night of december so dark and cold,
    // I walked a path ages old
    // The moon amongst the clouds revealed
    // Lightning valleys, forest and field

    // Embraced by silence i wandered the moor
    // An endless landscape by my side
    // When in the mist i saw a light
    // Dancing through the hazy night

    // I stood and watched the play in awe
    // Was deeply touched by what i saw
    // I told my friends what i did see
    // And what they told did tremble me!

    // It's said the ghost of a young, fair maid
    // Is cursed to dwell beneath the shade
    // Of the olden oak she died below
    // O that was many moons ago

    Tree r = NULL;
    int size;
    printf("Size of the tree?\n");
    scanf("%d", &size);
    int values[size];
    int o;
    
    for (int i = 0; i < size; i++)
    {
        printf("Enter the %d.value\n",i);
        scanf("%d",&o);
        values[i] = o;
    }

    // int values[] = {15, 8, 20, 5, 10, 17, 21};

    for (int i = 0; i < size; i++)
    {
        r = insertNode(r, values[i]);
    }

    // postOrder(r);
    // printf("Heigth:%d\n", height(r));
    // printf("Size:%d\n", size(r));
    // int b = 2;
    // printf("Number of nodes in %d.level:%d\n", b,numOfNodesInGivenDepth(r, 2));

    Tree n = NULL;
    n = modTree(r, n, 5); // take node from old tree(r) by mod 5
    printf("***New Tree***\n");
    postOrder(n);
    printf("***Old Tree***\n");
    postOrder(r);
    printf("***Updated Tree***\n");
    for (int i = 0; i < size; i++)
    {
        if (values[i] % 5 == 0)
            r = deleteNode(r, values[i]); // delete taken nodes
    }
    postOrder(r);

    return 0;
}

Tree newNode(int key)
{
    Tree p;
    p = (Tree)malloc(sizeof(Tree));
    p->data = key;
    p->right = NULL;
    p->left = NULL;
    return p;
}

Tree insertNode(Tree root, int key)
{
    if (root == NULL)
        return newNode(key);
    if (key < root->data)
        root->left = insertNode(root->left, key);
    else if (key > root->data)
        root->right = insertNode(root->right, key);
    return root;
}

void preOrder(Tree root)
{
    if (root != NULL)
    {
        printf("%d\n", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Tree root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d\n", root->data);
        inOrder(root->right);
    }
}

void postOrder(Tree root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d\n", root->data);
    }
}

void mirror(Tree root)
{
    if (root == NULL)
        return;
    else
    {
        Tree temp;
        mirror(root->left);
        mirror(root->right);
        temp = root->left; // swap
        root->left = root->right;
        root->right = temp;
    }
}

int size(Tree root)
{
    if (root == NULL)
        return 0;
    else
        return size(root->right) + 1 + size(root->left);
}

int height(Tree root)
{
    if (root == NULL)
        return -1;
    else
    {
        int leftHeight, rightHeight;
        leftHeight = height(root->left);
        rightHeight = height(root->right);
        if (rightHeight > leftHeight)
            return rightHeight + 1;
        else
            return leftHeight + 1;
    }
}

int numOfNodesInGivenDepth(Tree root, int x)
{
    if (root == NULL)
        return 0;
    if (x == 0)
        return 1;
    return numOfNodesInGivenDepth(root->left, x - 1) + numOfNodesInGivenDepth(root->right, x - 1);
}

Tree deleteNode(Tree root, int x)
{
    Tree p, q;
    if (root == NULL)
        return NULL;
    if (root->data == x)
    {
        if (root->left == root->right)
        {
            free(root);
            return NULL;
        }
        else
        {
            if (root->left == NULL)
            {
                p = root->right;
                free(root);
                return p;
            }
            else if (root->right == NULL)
            {
                p = root->left;
                free(root);
                return p;
            }
            else
            {
                p = q = root->right;
                while (p->left != NULL)
                    p = p->left;
                p->left = root->left;
                free(root);
                return q;
            }
        }
    }
    else if (root->data < x)
        root->right = deleteNode(root->right, x);
    else
        root->left = deleteNode(root->left, x);
    return root;
}