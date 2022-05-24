//
// Created by shaul on 09/05/2022.
//
#include "doctest.h"
#include "sources/OrgChart.hpp"
#include "string"
using namespace ariel;
using namespace std;
TEST_CASE ("Case 1 - Family tree")
{
    //create object person for this test
    class Person {
    public:
        string name;
        int age;

        Person(string Name, int Age) : name(Name), age(Age) {}

        bool operator==(Person &p1) {
            return this->name == p1.name;
        }
    };
    //instantiate People
    Person Great_GrandFather("Great_GrandFather", 85);
    Person Grandfather("GrandFather", 65);
    Person Father("Father", 45);
    Person Uncle("Uncle", 43);
    Person Aunt("Aunt", 43);
    Person Son("Son", 20);
    Person Daughter("Daughter", 18);
    Person Cousin("Cousin", 15);

    OrgChart chart1;
            CHECK_THROWS(chart1.add_sub(Aunt.name, Son.name));//no root
            CHECK_NOTHROW(chart1.add_root(Aunt.name));
            CHECK_NOTHROW(chart1.add_root(Great_GrandFather.name));
            CHECK_THROWS(chart1.add_sub(Aunt.name, Son.name));//root was replaced
            CHECK_THROWS(chart1.add_sub(Son.name, Uncle.name));//no such value
            CHECK_NOTHROW(chart1.add_sub(Great_GrandFather.name, Grandfather.name));
            CHECK_NOTHROW(chart1.add_sub(Grandfather.name, Father.name));
            CHECK_NOTHROW(chart1.add_sub(Grandfather.name, Uncle.name));
            CHECK_NOTHROW(chart1.add_sub(Grandfather.name, Aunt.name));
            CHECK_THROWS(chart1.add_sub(Cousin.name, Father.name));//cousin not added yet
            CHECK_NOTHROW(chart1.add_sub(Father.name, Son.name));
            CHECK_NOTHROW(chart1.add_sub(Father.name, Daughter.name));
            CHECK_NOTHROW(chart1.add_sub(Uncle.name, Cousin.name));

    // test level order
    vector<string> lvl_order;
    for (auto it = chart1.begin_level_order(); it != chart1.end_level_order(); ++it) {
        lvl_order.push_back(*it);
    }
            CHECK_EQ(lvl_order.at(0), Great_GrandFather.name);
            CHECK_EQ(lvl_order.at(1), Grandfather.name);
            CHECK_EQ(lvl_order.at(2), Father.name);
            CHECK_EQ(lvl_order.at(3), Uncle.name);
            CHECK_EQ(lvl_order.at(4), Aunt.name);
            CHECK_EQ(lvl_order.at(5), Son.name);
            CHECK_EQ(lvl_order.at(6), Daughter.name);
            CHECK_EQ(lvl_order.at(7), Cousin.name);


    lvl_order.clear();
    //add another field and check that it works
    Person Cousin2("Cousin2", 14);
            CHECK_NOTHROW(chart1.add_sub(Aunt.name, Cousin2.name));

    //check default iterator
    for (auto person: chart1) {
        lvl_order.push_back(person);
    }
            CHECK_EQ(lvl_order.at(0), Great_GrandFather.name);
            CHECK_EQ(lvl_order.at(1), Grandfather.name);
            CHECK_EQ(lvl_order.at(2), Father.name);
            CHECK_EQ(lvl_order.at(3), Uncle.name);
            CHECK_EQ(lvl_order.at(4), Aunt.name);
            CHECK_EQ(lvl_order.at(5), Son.name);
            CHECK_EQ(lvl_order.at(6), Daughter.name);
            CHECK_EQ(lvl_order.at(7), Cousin.name);
            CHECK_EQ(lvl_order.at(8), Cousin2.name);


    //add another field and check that it works
    Person GreatUncle("GreatUncle", 62);
            CHECK_NOTHROW(chart1.add_sub(Great_GrandFather.name, GreatUncle.name));

    // test reverse level order
    vector<string> rv_lvl_order;
    for (auto it = chart1.begin_reverse_order(); it != chart1.reverse_order(); ++it) {
        rv_lvl_order.push_back(*it);
    }
            CHECK_EQ(rv_lvl_order.at(0), Son.name);
            CHECK_EQ(rv_lvl_order.at(1), Daughter.name);
            CHECK_EQ(rv_lvl_order.at(2), Cousin.name);
            CHECK_EQ(rv_lvl_order.at(3), Cousin2.name);
            CHECK_EQ(rv_lvl_order.at(4), Father.name);
            CHECK_EQ(rv_lvl_order.at(5), Uncle.name);
            CHECK_EQ(rv_lvl_order.at(6), Aunt.name);
            CHECK_EQ(rv_lvl_order.at(7), Grandfather.name);
            CHECK_EQ(rv_lvl_order.at(8), GreatUncle.name);
            CHECK_EQ(rv_lvl_order.at(9), Great_GrandFather.name);

    // Change root check that still works
    Person GreatGrandma("GreatGrandma", 84);
            CHECK_NOTHROW(chart1.add_root(GreatGrandma.name));

    //test preorder
    vector<string> pre_order;
    for (auto it = chart1.begin_preorder(); it != chart1.end_preorder(); ++it) {
        pre_order.push_back(*it);
    }
            CHECK_EQ(pre_order.at(0), GreatGrandma.name);
            CHECK_EQ(pre_order.at(1), Grandfather.name);
            CHECK_EQ(pre_order.at(2), Father.name);
            CHECK_EQ(pre_order.at(3), Son.name);
            CHECK_EQ(pre_order.at(4), Daughter.name);
            CHECK_EQ(pre_order.at(5), Uncle.name);
            CHECK_EQ(pre_order.at(6), Cousin.name);
            CHECK_EQ(pre_order.at(7), Aunt.name);
            CHECK_EQ(pre_order.at(8), Cousin2.name);
            CHECK_EQ(pre_order.at(9), GreatUncle.name);

    //print tree for  convenience
    cout << chart1 << endl;
    //test arrow operator
    vector<int> arrow_test;
    for (auto it = chart1.begin_preorder(); it != chart1.end_preorder(); ++it) {
        arrow_test.push_back(it->length());
    }
            CHECK_EQ(arrow_test.at(0), 12);
            CHECK_EQ(arrow_test.at(1), 11);
            CHECK_EQ(arrow_test.at(2), 6);
            CHECK_EQ(arrow_test.at(3), 3);
            CHECK_EQ(arrow_test.at(4), 8);
            CHECK_EQ(arrow_test.at(5), 5);
            CHECK_EQ(arrow_test.at(6), 6);
            CHECK_EQ(arrow_test.at(7), 4);
            CHECK_EQ(arrow_test.at(8), 7);
            CHECK_EQ(arrow_test.at(9), 10);
}
TEST_CASE ("Case 2 Football Team")
{
    //checking string
    OrgChart chart2;
            CHECK_NOTHROW(chart2.add_root("Owner"));
            CHECK_NOTHROW(chart2.add_root("New_Owner"));
            CHECK_THROWS(chart2.add_sub("Owner" , "General Manager"));//Owner was replaced
            CHECK_THROWS(chart2.add_sub("Lebron James" , "General_Manager"));//no such value
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "General_Manager"));
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "Share_Holders"));
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "Head_of_operations"));
            CHECK_NOTHROW(chart2.add_sub("General_Manager" , "Head_Coach"));
            CHECK_NOTHROW(chart2.add_sub("General_Manager" , "Assistant_Coach"));
            CHECK_NOTHROW(chart2.add_sub("Head_of_operations" , "Team_Doctor"));
            CHECK_NOTHROW(chart2.add_sub("Head_of_operations" , "Head_Scout"));
            CHECK_NOTHROW(chart2.add_sub("Share_Holders" , "Sub_Share_Holder1"));
            CHECK_NOTHROW(chart2.add_sub("Share_Holders" , "Sub_Share_Holder2"));
            CHECK_THROWS(chart2.add_sub("head_of_operations" , "Cheerleader"));//Head not head
            CHECK_NOTHROW(chart2.add_sub("Head_Coach" , "Captain"));
            CHECK_NOTHROW(chart2.add_sub("Team_Doctor" , "Team_Physiotherapist"));
            // test level order
            vector<string> lvl_order;
            for (auto it = chart2.begin_level_order(); it != chart2.end_level_order(); ++it)
            {
               lvl_order.push_back(*it);
            }
            CHECK_EQ(lvl_order.at(0),"New_Owner");
            CHECK_EQ(lvl_order.at(1),"General_Manager");
            CHECK_EQ(lvl_order.at(2),"Share_Holders");
            CHECK_EQ(lvl_order.at(3),"Head_of_operations");
            CHECK_EQ(lvl_order.at(4),"Head_Coach");
            CHECK_EQ(lvl_order.at(5),"Assistant_Coach");
            CHECK_EQ(lvl_order.at(6),"Sub_Share_Holder1");
            CHECK_EQ(lvl_order.at(7),"Sub_Share_Holder2");
            CHECK_EQ(lvl_order.at(8),"Team_Doctor");
            CHECK_EQ(lvl_order.at(9),"Head_Scout");
            CHECK_EQ(lvl_order.at(10),"Captain");
            CHECK_EQ(lvl_order.at(11),"Team_Physiotherapist");
            lvl_order.clear();

            //add another field and check that it works
            CHECK_NOTHROW(chart2.add_sub("Assistant_Coach" , "Water_Boy"));
             cout << chart2 << endl;
            //check default iterator
            for (auto name:chart2)
            {
                lvl_order.push_back(name);
            }
            CHECK_EQ(lvl_order.at(0),"New_Owner");
            CHECK_EQ(lvl_order.at(1),"General_Manager");
            CHECK_EQ(lvl_order.at(2),"Share_Holders");
            CHECK_EQ(lvl_order.at(3),"Head_of_operations");
            CHECK_EQ(lvl_order.at(4),"Head_Coach");
            CHECK_EQ(lvl_order.at(5),"Assistant_Coach");
            CHECK_EQ(lvl_order.at(6),"Sub_Share_Holder1");
            CHECK_EQ(lvl_order.at(7),"Sub_Share_Holder2");
            CHECK_EQ(lvl_order.at(8),"Team_Doctor");
            CHECK_EQ(lvl_order.at(9),"Head_Scout");
            CHECK_EQ(lvl_order.at(10),"Captain");
            CHECK_EQ(lvl_order.at(11),"Water_Boy");
            CHECK_EQ(lvl_order.at(12),"Team_Physiotherapist");

            // test reverse level order
            vector<string> rv_lvl_order;
            for (auto it = chart2.begin_reverse_order(); it != chart2.reverse_order(); ++it)
            {
                rv_lvl_order.push_back(*it);
            }
            CHECK_EQ(rv_lvl_order.at(0),"Captain");
            CHECK_EQ(rv_lvl_order.at(1),"Water_Boy");
            CHECK_EQ(rv_lvl_order.at(2),"Team_Physiotherapist");
            CHECK_EQ(rv_lvl_order.at(3),"Head_Coach");
            CHECK_EQ(rv_lvl_order.at(4),"Assistant_Coach");
            CHECK_EQ(rv_lvl_order.at(5),"Sub_Share_Holder1");
            CHECK_EQ(rv_lvl_order.at(6),"Sub_Share_Holder2");
            CHECK_EQ(rv_lvl_order.at(7),"Team_Doctor");
            CHECK_EQ(rv_lvl_order.at(8),"Head_Scout");
            CHECK_EQ(rv_lvl_order.at(9),"General_Manager");
            CHECK_EQ(rv_lvl_order.at(10),"Share_Holders");
            CHECK_EQ(rv_lvl_order.at(11),"Head_of_operations");
            CHECK_EQ(rv_lvl_order.at(12),"New_Owner");

            // Change root check that still works
            CHECK_NOTHROW(chart2.add_root("Stan_Kronke"));

            //test preorder
            vector<string> pre_order;
            for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
            {
                pre_order.push_back(*it);
            }
            CHECK_EQ(pre_order.at(0),"Stan_Kronke");
            CHECK_EQ(pre_order.at(1),"General_Manager");
            CHECK_EQ(pre_order.at(2),"Head_Coach");
            CHECK_EQ(pre_order.at(3),"Captain");
            CHECK_EQ(pre_order.at(4),"Assistant_Coach");
            CHECK_EQ(pre_order.at(5),"Water_Boy");
            CHECK_EQ(pre_order.at(6),"Share_Holders");
            CHECK_EQ(pre_order.at(7),"Sub_Share_Holder1");
            CHECK_EQ(pre_order.at(8),"Sub_Share_Holder2");
            CHECK_EQ(pre_order.at(9),"Head_of_operations");
            CHECK_EQ(pre_order.at(10),"Team_Doctor");
            CHECK_EQ(pre_order.at(11),"Team_Physiotherapist");
            CHECK_EQ(pre_order.at(12),"Head_Scout");

            //test arrow operator
            vector<char> arrow_test;
            for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
            {
                arrow_test.push_back(it->at(0));
            }
            CHECK_EQ(arrow_test.at(0),'S');
            CHECK_EQ(arrow_test.at(1),'G');
            CHECK_EQ(arrow_test.at(2),'H');
            CHECK_EQ(arrow_test.at(3),'C');
            CHECK_EQ(arrow_test.at(4),'A');
            CHECK_EQ(arrow_test.at(5),'W');
            CHECK_EQ(arrow_test.at(6),'S');
            CHECK_EQ(arrow_test.at(7),'S');
            CHECK_EQ(arrow_test.at(8),'S');
            CHECK_EQ(arrow_test.at(9),'H');
            CHECK_EQ(arrow_test.at(10),'T');
            CHECK_EQ(arrow_test.at(11),'T');
            CHECK_EQ(arrow_test.at(12),'H');
}


