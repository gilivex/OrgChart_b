#include <iostream>
#include <sstream>
using namespace std;
#include "OrgChart.hpp"
using namespace ariel;

namespace ariel
{
    void OrgChart::copy_tree(Node **n, Node *copy, unordered_map<int, vector<Node *>> level)
    {
        if (copy == nullptr)
        {
            return;
        }
        *n = new Node(copy->data, copy->rank);
        if (level.find(copy->rank) == level.end())
        {
            vector<Node *> my_copy_rank;
            level[copy->rank] = my_copy_rank;
        }
        level[copy->rank].push_back(*n);

        for (size_t i = 0; i <= copy->children.size(); i++)
        {
            if (i == copy->children.size())
            {
                copy_tree(nullptr, nullptr, level);
            }
            else
            {
                copy_tree(&((*n)->children[i]), copy->children[i], level);
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
            copy_tree(&this->root, org.root, this->level);
        }
        return *this;
    }

    OrgChart &OrgChart::add_root(const string &s)
    {
        if (this->root == nullptr)
        {
            Node *node = new Node(s, 0);
            root = node;
            vector<Node *> lev;
            this->level[0] = lev;
            this->level[0].push_back(root);
        }
        else
        {
            this->root->data = s;
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
                Node *child = new Node(son, rank);
                it.get_curr()->children.push_back(child);
                if (level.find(rank) == level.end())
                {
                    vector<Node *> son_rank;
                    level[rank] = son_rank;
                }
                level[rank].push_back(child);
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

        return OrgChart::iterator(1, level, root);
    }

    OrgChart::iterator OrgChart::end_level_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node
        return OrgChart::iterator(1, level);
    }

    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(2, level, root);
    }

    OrgChart::iterator OrgChart::reverse_order()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node

        return OrgChart::iterator(2, level);
    }

    OrgChart::iterator OrgChart::begin_preorder()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(3, level, root);
    }

    OrgChart::iterator OrgChart::end_preorder()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        // because the default is null no nedeed to send start Node

        return OrgChart::iterator(3, level);
    }

    // workes like level_order
    OrgChart::iterator OrgChart::begin()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(1, level, root);
    }

    OrgChart::iterator OrgChart::end()
    {
        if (this->root == nullptr)
        {
            throw invalid_argument{"not exist"};
        }
        return OrgChart::iterator(1, level);
    }

    ostream &operator<<(ostream &os, OrgChart &org)
    {
        for (int i = 0; org.level.find(i) != org.level.end(); i++)
        {
            for (size_t j = 0; j < org.level[i].size(); j++)
            {
                os << org.level[i][j]->data << "\t";
            }
            os << endl;
        }

        return os;
    }

    ////////////////iterator func///////////////

    void OrgChart::iterator::level_order(unordered_map<int, vector<Node *>> &level)
    {
        for (int i = 0; level.find(i) != level.end(); i++)
        {
            for (size_t j = 0; j < level[i].size(); j++)
            {
                byOrder.push(level[i][j]);
            }
        }
    }

    void OrgChart::iterator::revers_order(unordered_map<int, vector<Node *>> &level)
    {
        int counter = 0;
        while (level.find(counter) != level.end())
        {
            counter++;
        }
        for (int i = counter - 1; i >= 0; i--)
        {
            for (size_t j = 0; j < level[i].size(); j++)
            {
                byOrder.push(level[i][j]);
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

    string &OrgChart::iterator::operator*()
    {
        return this->curr->data;
    }

    string *OrgChart::iterator::operator->()
    {
        return &(this->curr->data);
    }
    int OrgChart::iterator::get_rank()
    {
        return this->curr->rank;
    }

    ostream &operator<<(ostream &os, const OrgChart::iterator &itr)
    {
        os << itr.curr->data;
        return os;
    };
}
