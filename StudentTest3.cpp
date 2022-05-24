#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("A child who has no father")
{
    OrgChart organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")    // Now the CTO is subordinate to the CEO
        .add_sub("CEO", "CFO")    // Now the CFO is subordinate to the CEO
        .add_sub("CEO", "COO")    // Now the COO is subordinate to the CEO
        .add_sub("CTO", "VP_SW")  // Now the VP Software is subordinate to the CTO
        .add_sub("COO", "VP_BI"); // Now the VP_BI is subordinate to the COO

    //   cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
    //        CEO
    //        |--------|--------|
    //        CTO      CFO      COO
    //        |                 |
    //        VP_SW             VP_BI
    //  */


    CHECK_NOTHROW(organization.add_sub("VP_BI", "New Employee"));
    CHECK_THROWS(organization.add_sub("ME", "New Employee"));
    CHECK_NOTHROW(organization.add_root("ME"));
    CHECK_NOTHROW(organization.add_sub("ME", "New Employee"));
}
TEST_CASE("Org 1")
{
    vector<string> names = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])  // Now the CTO is subordinate to the CEO
        .add_sub(names[0], names[2])  // Now the CFO is subordinate to the CEO
        .add_sub(names[0], names[3])  // Now the COO is subordinate to the CEO
        .add_sub(names[1], names[4])  // Now the VP Software is subordinate to the CTO
        .add_sub(names[3], names[5]); // Now the VP_BI is subordinate to the COO
    //        CEO
    //        |--------|--------|
    //        CTO      CFO      COO
    //        |                 |
    //        VP_SW             VP_BI
    //  */
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be: CEO CTO CFO COO VP_SW VP_BI
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be: VP_SW VP_BI CTO CFO COO CEO
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to be: CEO CTO VP_SW CFO COO VP_BI
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be: CEO CTO CFO COO VP_SW VP_BI
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be: 3 3 3 3 5 5
}

TEST_CASE("Org 2")
{
    vector<string> names = {"grandfather", "father", "uncle", "mother", "boy", "girl"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}

TEST_CASE("Org 3")
{
    vector<string> names = {"rector", "dean", "department head", "lecture", "practitioner", "student"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 4")
{
    vector<string> names = {"computer", "Hard Disk", "Graphics Card", "keyboard", "bits", "buttons"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 5")
{
    vector<string> names = {"house", "kitchen", "bedroom", "living room", "oven", "couch"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 6")
{
    vector<string> names = {"The Milky Way", "Earth", "Venus", "Mars", "Israel", "Meridiani Planum"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 7")
{
    vector<string> names = {"Mor", "Arhel", "Haim", "Nofar", "Tal", "Yavgni"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 8")
{
    vector<string> names = {"Dvir Gev", "Dvir Biton", "Raz", "Amit", "Ariel", "Aviad"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 9")
{
    vector<string> names = {"Rick", "Morty", "Summer", "Beth", "Jerry", "Mr. Meeseeks"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}
TEST_CASE("Org 10")
{
    vector<string> names = {"Bulbasaur", "Charmander", "Squirtle", "Caterpie", "Weedle", "Pidgey"};
    vector<string> exp_level_order = {names[0], names[1], names[2], names[3], names[4], names[5]};
    vector<string> exp_reverse_order = {names[4], names[5], names[1], names[2], names[3], names[0]};
    vector<string> exp_preorder = {names[0], names[1], names[4], names[2], names[3], names[5]};
    OrgChart organization;
    organization.add_root(names[0])
        .add_sub(names[0], names[1])
        .add_sub(names[0], names[2])
        .add_sub(names[0], names[3])
        .add_sub(names[1], names[4])
        .add_sub(names[3], names[5]);
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++], (*it));
    } // Needs to be like exp_level_order
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(exp_reverse_order[i++], (*it));
    } // Needs to be like exp_reverse_order
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(exp_preorder[i++], (*it));
    } // Needs to belike exp_preorder
    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(exp_level_order[i++], element);
    } // Needs to be like exp_level_order
    i = 0;
    // demonstrate the arrow operator:
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(exp_level_order[i++].size(), it->size());
    } // Needs to be like exp_level_order
}