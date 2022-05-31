#include <iostream>
#include <sstream>
#include <stack>
using namespace std;
#include "OrgChart.hpp"
using namespace ariel;

namespace ariel
{
    void OrgChart::copy_tree(Node **n, Node *copy)
    {
        if (copy == nullptr)
        {
            return;
        }
        *n = new Node(copy->data, copy->rank);

        for (size_t i = 0; i <= copy->children.size(); i++)
        {
            if (i == copy->children.size())
            {
                copy_tree(nullptr, nullptr);
            }
            else
            {
                copy_tree(&((*n)->children[i]), copy->children[i]);
            }
        }
    }
    OrgChart &OrgChart::operator=(OrgChart &&org) noexcept
    {
        delete this->root;

        this->root = org.root;
        org.root = nullptr;
        return *this;
    }

    OrgChart &OrgChart::operator=(const OrgChart &org)
    {
        if (this != &org)
        {
            copy_tree(&this->root, org.root);
        }
        return *this;
    }

    OrgChart &OrgChart::add_root(const string &root)
    {
        if (this->root == nullptr)
        {
            string s = root;
            Node *node = new Node(s, 0);
            this->root = node;
        }
        else
        {
            this->root->data = root;
        }
        return *this;
    }

    OrgChart &OrgChart::add_sub(const string &parent, const string &son)
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"there are no nodes"};
        }
        bool flag = false;
        for (iterator it = this->begin(); it != this->end(); it++)
        {
            if (*it == parent)
            {
                int rank = it.get_rank() + 1;
                string s = son;
                Node *child = new Node(s, rank);
                it.get_curr()->children.push_back(child);
                flag = true;
            }
        }
        if (!flag)
        {
            throw invalid_argument{"parent is not exist"};
        }
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }

        return OrgChart::iterator(1, root);
    }

    OrgChart::iterator OrgChart::end_level_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node
        return OrgChart::iterator(1);
    }

    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(2, root);
    }

    OrgChart::iterator OrgChart::reverse_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node

        return OrgChart::iterator(2);
    }

    OrgChart::iterator OrgChart::begin_preorder()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(3, root);
    }

    OrgChart::iterator OrgChart::end_preorder()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node

        return OrgChart::iterator(3);
    }

    // workes like level_order
    OrgChart::iterator OrgChart::begin()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(1, root);
    }

    OrgChart::iterator OrgChart::end()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(1);
    }

    ostream &operator<<(ostream &os, OrgChart &org)
    {
        int r = 0;
        for (OrgChart::iterator it = org.begin(); it != org.end(); it++)
        {
            if (it.get_rank() != r)
            {
                os << endl;
                r++;
            }
            else
            {
                os << it << " ";
            }
        }

        return os;
    }

    ////////////////iterator func///////////////

    void OrgChart::iterator::level_order(Node *root)
    {
        queue<Node *> temp;
        temp.push(root);
        while (!temp.empty())
        {
            Node *out = temp.front();
            temp.pop();
            for (Node *n : out->children)
            {
                temp.push(n);
            }
            byOrder.push(out);
        }
    }

    void OrgChart::iterator::revers_order(Node *root)
    {
        queue<Node *> temp;
        stack<Node *> rev;
        temp.push(root);
        while (!temp.empty())
        {
            Node *out = temp.front();
            temp.pop();
            for (Node *n : out->children)
            {
                temp.push(n);
            }
            rev.push(out);
        }
        stack<Node *> temp_rev;
        int r = rev.top()->rank;
        while (!rev.empty())
        {
            if (rev.top()->rank != r)
            {
                while (!temp_rev.empty())
                {
                    byOrder.push(temp_rev.top());
                    temp_rev.pop();
                }
                r--;
            }
            else
            {
                temp_rev.push(rev.top());
                rev.pop();
            }
            if (rev.empty())
            {
                byOrder.push(temp_rev.top());
                temp_rev.pop();
            }
        }
    }
    void OrgChart::iterator::preorder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        byOrder.push(root);
        for (size_t i = 0; i <= root->children.size(); i++)
        {
            if (i == root->children.size())
            {
                preorder(nullptr);
            }
            else
            {
                preorder(root->children.at(i));
            }
        }
    }
    OrgChart::iterator &OrgChart::iterator::operator++() // prefix
    {
        byOrder.pop();
        if (byOrder.empty())
        {
            curr = nullptr;
        }
        else
        {
            curr = byOrder.front();
        }
        return *this;
    }

    OrgChart::iterator OrgChart::iterator::operator++(int) // postfix
    {
        iterator temp = *this;
        // this way we saving codelines
        ++(*this);
        return temp;
    }

    bool OrgChart::iterator::operator==(const iterator &itr) const
    {
        return curr == itr.curr;
    }

    bool OrgChart::iterator::operator!=(const iterator &itr) const
    {
        return curr != itr.curr;
    }

    string OrgChart::iterator::operator*()
    {
        if (curr != nullptr)
        {
            return this->curr->data;
        }
        return "";
    }

    string *OrgChart::iterator::operator->()
    {
        return &(this->curr->data);
    }

    int OrgChart::iterator::get_rank()
    {
        if (curr != nullptr)
        {
            return this->curr->rank;
        }
        return -1;
    }

    ostream &operator<<(ostream &os, const OrgChart::iterator &itr)
    {
        os << itr.curr->data;
        return os;
    };
}
