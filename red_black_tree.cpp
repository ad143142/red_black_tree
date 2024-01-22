#include <iostream>
#include <cstdio>
#include <string>

class rb_tree
{
private:
    class node
    {
    public:
        int data;
        node *lchild;
        node *rchild;
        node *parent;
        bool color;
        node(int d) : data(d)
        {
            lchild = rchild = parent = nullptr;
            color = RED;
        }
        node(int d, bool co) : data(d), color(co)
        {
            lchild = rchild = parent = nullptr;
        }
    };
    node *root;

    node *insert(node *now, int data);
    node *check_insert_violation(node *now, node *child);

    node *delete_node(node *now, int data);
    node *successor(node *now);
    node *predecessor(node *now);

    node *RR_rotation(node *now, node *child)
    {
        now->rchild = child->lchild;
        child->lchild = now;
        child->color = BLACK;
        now->color = RED;

        child->parent = now->parent;
        now->parent = child;
        if (now->rchild)
            now->rchild->parent = now;

        return child;
    }
    node *RL_rotation(node *now, node *child)
    {
        node *grandson = child->lchild;
        now->rchild = grandson->lchild;
        child->lchild = grandson->rchild;
        grandson->lchild = now;
        grandson->rchild = child;
        grandson->color = BLACK;
        now->color = RED;

        grandson->parent = now->parent;
        now->parent = grandson;
        child->parent = grandson;
        if (now->rchild)
            now->rchild->parent = now;
        if (child->lchild)
            child->lchild->parent = child;

        return grandson;
    }
    node *LR_rotation(node *now, node *child)
    {
        node *grandson = child->rchild;
        now->lchild = grandson->rchild;
        child->rchild = grandson->lchild;
        grandson->lchild = child;
        grandson->rchild = now;
        grandson->color = BLACK;
        now->color = RED;

        grandson->parent = now->parent;
        now->parent = grandson;
        child->parent = grandson;
        if (now->lchild)
            now->lchild->parent = now;
        if (child->rchild)
            child->rchild->parent = child;

        return grandson;
    }
    node *LL_rotation(node *now, node *child)
    {
        now->lchild = child->rchild;
        child->rchild = now;
        child->color = BLACK;
        now->color = RED;

        child->parent = now->parent;
        now->parent = child;
        if (now->lchild)
            now->lchild->parent = now;

        return child;
    }
    void recolor(node *now, node *child, node *sibling)
    {
        child->color = sibling->color = BLACK;
        now->color = (now == root) ? BLACK : RED;
    }

    void printHelper(node *root, std::string indent, bool last);

    enum RB_TREE_COLOR
    {
        RED,
        BLACK
    };

public:
    rb_tree() { root = nullptr; }
    void insert(int data)
    {
        if (!root)
        {
            root = new node(data);
            root->color = BLACK;
        }
        else
        {
            root = insert(root, data);
        }
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }

    void delete_node(int data)
    {
        if (!root->lchild && !root->rchild && root->data == data)
        {
            delete root;
            root = nullptr;
            return;
        }

        root = delete_node(root, data);
    }

    // delete 90
    void test1()
    {
        root = new node(70);
        root->color = BLACK;
        node *p = root;
        p->lchild = new node(40);
        p->lchild->parent = p;
        p->rchild = new node(90);
        p->rchild->parent = p;
        p->rchild->color = BLACK;
        p = p->lchild;
        p->rchild = new node(50);
        p->rchild->parent = p;
        p->rchild->color = BLACK;
        p->lchild = new node(20);
        p->lchild->parent = p;
        p->lchild->color = BLACK;
        p->rchild->rchild = new node(60);
        p->rchild->rchild->parent = p->rchild;
        p = p->lchild;
        p->rchild = new node(30);
        p->rchild->parent = p;
        p->lchild = new node(10);
        p->lchild->parent = p;
    }

    // all black delete leaf
    void test2()
    {
        root = new node(50, BLACK);
        node *p = root;
        p->lchild = new node(30, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(70, BLACK);
        p->rchild->parent = p;
        p = p->lchild;
        p->rchild = new node(40, BLACK);
        p->rchild->parent = p;
        p->lchild = new node(20, BLACK);
        p->lchild->parent = p;
        p = p->parent->rchild;
        p->rchild = new node(80, BLACK);
        p->rchild->parent = p;
        p->lchild = new node(60, BLACK);
        p->lchild->parent = p;
    }

    // delete 30 (root)
    void test3()
    {
        root = new node(30, BLACK);
        node *p = root;
        p->lchild = new node(10, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(50, RED);
        p->rchild->parent = p;
        p = p->lchild;
        p->rchild = new node(20, RED);
        p->rchild->parent = p;
        p = p->parent->rchild;
        p->rchild = new node(60, BLACK);
        p->rchild->parent = p;
        p->lchild = new node(40, BLACK);
        p->lchild->parent = p;
        p = p->lchild;
        p->rchild = new node(45, RED);
        p->rchild->parent = p;
    }

    // delete 50
    void test4()
    {
        root = new node(40, BLACK);
        node *p = root;
        p->lchild = new node(20, RED);
        p->lchild->parent = p;
        p->rchild = new node(60, RED);
        p->rchild->parent = p;
        p = p->lchild;
        p->lchild = new node(10, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(30, BLACK);
        p->rchild->parent = p;
        p = p->parent->rchild;
        p->lchild = new node(50, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(70, BLACK);
        p->rchild->parent = p;
    }

    // delete 10
    void test5()
    {
        root = new node(20, BLACK);
        node *p = root;
        p->lchild = new node(10, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(40, RED);
        p->rchild->parent = p;
        p = p->rchild;
        p->lchild = new node(30, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(50, BLACK);
        p->rchild->parent = p;
    }

    // delete 10
    void test6()
    {
        root = new node(20, BLACK);
        node *p = root;
        p->lchild = new node(10, BLACK);
        p->lchild->parent = p;
        p->rchild = new node(40, BLACK);
        p->rchild->parent = p;
        p = p->rchild;
        p->lchild = new node(30, RED);
        p->lchild->parent = p;
        p->rchild = new node(50, RED);
        p->rchild->parent = p;
    }
};

rb_tree::node *rb_tree::check_insert_violation(rb_tree::node *now, rb_tree::node *child)
{
    if (now->color == RED || child->color == BLACK || (!child->lchild && !child->rchild))
        return now;

    if (now->rchild == child) // child is now's rchild
    {
        node *sibling = now->lchild;
        if (child->rchild && child->rchild->color == RED)
        {
            if (!sibling || sibling->color == BLACK) // sibling is black
                return RR_rotation(now, child);
            else
                recolor(now, child, sibling);
        }
        else if (child->lchild && child->lchild->color == RED)
        {
            if (!sibling || sibling->color == BLACK) // sibling is black
                return RL_rotation(now, child);
            else
                recolor(now, child, sibling);
        }
    }
    else // child is now's left child
    {
        node *sibling = now->rchild;
        if (child->lchild && child->lchild->color == RED)
        {
            if (!sibling || sibling->color == BLACK) // sibling is black
                return LL_rotation(now, child);
            else
                recolor(now, child, sibling);
        }
        else if (child->rchild && child->rchild->color == RED)
        {
            if (!sibling || sibling->color == BLACK) // sibling is black
                return LR_rotation(now, child);
            else
                recolor(now, child, sibling);
        }
    }
    return now;
}

rb_tree::node *rb_tree::insert(node *now, int data)
{
    if (!now)
        return new node(data);

    node *ret;
    if (data > now->data)
    {
        now->rchild = insert(now->rchild, data);
        now->rchild->parent = now;
        ret = check_insert_violation(now, now->rchild);
    }
    else
    {
        now->lchild = insert(now->lchild, data);
        now->lchild->parent = now;
        ret = check_insert_violation(now, now->lchild);
    }

    return ret;
}

rb_tree::node *rb_tree::successor(node *now)
{
    if (!now->rchild)
        return nullptr;

    now = now->rchild;
    while (now->lchild)
        now = now->lchild;
    return now;
}

rb_tree::node *rb_tree::predecessor(node *now)
{
    if (!now->lchild)
        return nullptr;

    now = now->lchild;
    while (now->rchild)
        now = now->rchild;
    return now;
}

rb_tree::node *rb_tree::delete_node(node *now, int data)
{
    /*
    Three step
    0.find value
    1.find heir
    2.determine it's which case
    3.fix
    */

    // Step 0.find value
    node *del = now;
    while (del)
    {
        if (data > del->data)
        {
            del = del->rchild;
        }
        else if (data < del->data)
        {
            del = del->lchild;
        }
        else
        {
            break;
        }
    }
    if (!del)
        return now;

    //Step 1.find heir
    node *s, *p;
    while (true)
    {
        s = successor(del);
        p = predecessor(del);
        if (s)
        {

            del->data = s->data;
            del = s;
        }
        else if (p)
        {
            del->data = p->data;
            del = p;
        }
        else
        {
            break;
        }
    }

    bool del_color = del->color;
    node *del_p = del->parent;
    bool del_dir = (del_p->lchild == del); // 0 right 1 left
    node *del_s = del_dir ? del_p->rchild : del_p->lchild;
    if (del_dir)
        del_p->lchild = nullptr;
    else
        del_p->rchild = nullptr;

    delete del;

    bool recolor_flag = 0;
    if (del_color == BLACK)
    {
        // step.2
        if ((!del_s || del_s->color == BLACK) && (!del_s->lchild || del_s->lchild->color == BLACK) && (!del_s->rchild || del_s->rchild->color == BLACK))
        {
            recolor_flag = 1;
            // recolor
            del_s->color = RED;
            if (del_p->color == BLACK)
            {
                if (del_p->parent)
                {
                    del_p = del_p->parent;
                    if (del_p->data > del_s->data) // turn left
                    {
                        del_dir = 1; // left
                        del_s = del_p->rchild;
                    }
                    else // turn right
                    {
                        del_dir = 0; // right
                        del_s = del_p->lchild;
                    }
                }
            }
            else
            {
                del_p->color = BLACK;
                return root;
            }
        }

        if (del_dir) // left
        {
            del_s->parent = del_p->parent;
            del_p->rchild = del_s->lchild;
            if (del_s->lchild)
            {
                del_s->lchild->parent = del_p;
                if (!recolor_flag)
                    del_p->rchild->color = RED;
            }
            del_s->lchild = del_p;
            del_p->parent = del_s;

            if (recolor_flag)
                del_p->color = RED;
            del_s->color = BLACK;
            del_s->rchild->color = BLACK;
        }
        else // right
        {
            del_s->parent = del_p->parent;
            del_p->lchild = del_s->rchild;
            if (del_s->rchild)
            {
                del_s->rchild->parent = del_p;
                if (!recolor_flag)
                    del_p->lchild->color = RED;
            }
            del_s->rchild = del_p;
            del_p->parent = del_s;

            if (recolor_flag)
                del_p->color = RED;
            del_s->color = BLACK;
            del_s->lchild->color = BLACK;
        }

        // step.3
        // rotation need to check violation and fix
        // because child has been change color
        if (!recolor_flag)
        {
            if (del_dir) // 0 right 1 left
            {
                if (del_p->rchild && del_p->rchild->color == RED)
                {
                    node *child = del_p->rchild;
                    if (child->rchild && child->rchild->color == RED) // RR rotation
                    {
                        del_p = RR_rotation(del_p, child);
                    }
                    else if (child->rchild && child->rchild->color == RED) // RL rotaton
                    {
                        del_p = RL_rotation(del_p, child);
                    }
                }
                if (del_p->parent)
                    del_p->parent->lchild = del_p;
            }
            else
            {
                if (del_p->lchild && del_p->lchild->color == RED)
                {
                    node *child = del_p->lchild;
                    if (child->lchild && child->lchild->color == RED) // LL rotation
                    {
                        del_p = LL_rotation(del_p, child);
                    }
                    else if (child->rchild && child->rchild->color == RED) // LR rotaton
                    {
                        del_p = LR_rotation(del_p, child);
                    }
                    if (del_p->parent)
                        del_p->parent->rchild = del_p;
                }
            }
        }
        del_p = del_s;
        return del_p;
    }
    else // delete red node
        return root;
}

void rb_tree::printHelper(node *root, std::string indent, bool last)
{
    if (root != nullptr)
    {
        std::cout << indent;
        if (last)
        {
            std::cout << "R----";
            indent += "   ";
        }
        else
        {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = root->color ? "BLACK" : "RED";
        std::cout << root->data << "(" << sColor << ")"
                  << "\n";
        printHelper(root->lchild, indent, false);
        printHelper(root->rchild, indent, true);
    }
}

int main()
{
    // rb_tree tree;
    // tree.insert(70);
    // tree.insert(70);
    // tree.delete_node(70);

    // tree.insert(50);
    // tree.insert(10);
    // tree.insert(40);
    // tree.insert(60);
    // tree.insert(30);
    // tree.insert(20);
    // tree.insert(90);

    rb_tree tree;
    tree.test6();
    // tree.printTree();
    // printf("\n");
    tree.delete_node(10);

    tree.printTree();
}
