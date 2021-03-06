#pragma once
#include <iostream>
#include <sstream>
#include <queue>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
using namespace std;

namespace ariel
{

    class OrgChart
    {
    private:
        struct Node
        {
            string data;
            vector<Node *> children;
            int rank;
            explicit Node(string &val, int r)
            {
                this->data = val;
                this->rank = r;
            }
        };

        Node *root;
        void copy_tree(Node **n, Node *copy);

    public:
        OrgChart()
        {
            this->root = nullptr;
        }

        OrgChart(OrgChart &org)
        {
            this->root = nullptr;
            if (org.root == nullptr)
            {
                return;
            }
            copy_tree(&this->root, org.root);
        };

        OrgChart(OrgChart &&org) noexcept
        {
            this->root = org.root;
            org.root = nullptr;
        };
        OrgChart &operator=(OrgChart &&org) noexcept;

        OrgChart &operator=(const OrgChart &org);

        OrgChart &add_root(const string &root);

        class iterator
        {
        private:
            Node *curr;
            queue<Node *> byOrder;
            void level_order(Node *root);

            void revers_order(Node *root);

            void preorder(Node *root);

        public:
            explicit iterator(int type, Node *start = nullptr)
            {
                curr = start;
                if (curr != nullptr)
                {
                    switch (type)
                    {
                    case 1:
                        level_order(start);
                        break;
                    case 2:
                        revers_order(start);
                        break;
                    case 3:
                        preorder(start);
                        break;
                    default:
                        throw invalid_argument{"type is wrong"};
                        break;
                    }
                    curr = byOrder.front();
                }
            };

            iterator &operator++(); // prefix

            iterator operator++(int); // postfix

            bool operator==(const iterator &itr) const;

            bool operator!=(const iterator &itr) const;

            string operator*();

            string *operator->();

            int get_rank();

            Node *get_curr()
            {
                return this->curr;
            };

            friend ostream &operator<<(ostream &os, const iterator &itr);
        };

        OrgChart::iterator begin();
        OrgChart::iterator end();
        OrgChart::iterator begin_level_order();
        OrgChart::iterator end_level_order();
        OrgChart::iterator begin_reverse_order();
        OrgChart::iterator reverse_order();
        OrgChart::iterator begin_preorder();
        OrgChart::iterator end_preorder();

        OrgChart &add_sub(const string &parent, const string &son);

        friend ostream &operator<<(ostream &os, OrgChart &org);

        ~OrgChart()
        {
            if (root == nullptr)
            {
                return;
            }

            for (OrgChart::iterator it = begin_reverse_order(); it != reverse_order(); it++)
            {
                Node *temp = it.get_curr();
                delete temp;
            }
        };
    };
}