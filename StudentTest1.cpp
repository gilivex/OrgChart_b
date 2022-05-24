#include "doctest.h"
#include "OrgChart.hpp"
using namespace ariel;

/*Renana Rimon*/

TEST_CASE("BUILD_ORG"){
    OrgChart org;
    OrgChart org_empty;
    OrgChart org_double_names;
    /* create normal tree */
    CHECK_THROWS_MESSAGE(org.add_sub("tal", "renana"), "can't add sub before root");
    CHECK_NOTHROW(org.add_root("dana"));
    CHECK_NOTHROW(org.add_root("shir"));
    CHECK_NOTHROW(org.add_sub("shir", "tal"));
    CHECK_THROWS_MESSAGE(org.add_sub("adi", "sapir"), "employer doesn't exist");
    CHECK_NOTHROW(org.add_sub("shir", "sapir"));
    CHECK_NOTHROW(org.add_sub("sapir", "dan"));
    CHECK_NOTHROW(org.add_sub("dan", "ziv"));
    CHECK_NOTHROW(org.add_sub("tal", "avi"));
    CHECK_NOTHROW(org.add_sub("tal", "yossi"));
    CHECK_NOTHROW(org.add_sub("shir", "ido"));
    CHECK_NOTHROW(org.add_sub("ziv", "shaked"));
    CHECK_NOTHROW(org.add_sub("ziv", "ofer"));


    /* create tree with 1 name*/
    CHECK_NOTHROW(org_double_names.add_root("adi"));
    for (size_t i = 0; i < 11; i++)
    {
        CHECK_NOTHROW(org_double_names.add_sub("adi", "adi"));
    }


    /**************************************************************/
    SUBCASE("level_order"){
        /*check level order with normal tree*/
        std::vector<std::string> v = {"shir", "tal", "sapir", "ido", "avi", "yossi", "dan", "ziv", "shaked", "ofer"};
        size_t i = 0;
        for(auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
            CHECK_EQ(*it, v.at(i++));
        }
    
    

        /*check level order with empty tree*/
        // CHECK_THROWS_MESSAGE(org_empty.begin_level_order(), "chart is empty!");
        CHECK_THROWS_MESSAGE(org_empty.end_level_order(), "chart is empty!");
        

        /*check level order with 1 name tree*/
        for(auto it = org_double_names.begin_level_order(); it != org_double_names.end_level_order(); ++it){
            CHECK(*it == "adi");
        }
    
        /* check iter size*/
        std::vector<int> nums = {4, 3, 5, 3, 3, 5, 3, 3, 6, 4};
        int j = 0;
        for(auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
            CHECK_EQ(it->size(), nums.at((size_t)j));
            j++;
        }

    }

    SUBCASE("reverse_level_order"){
        /*check reverse level order with normal tree*/
        std::vector<std::string> v = {"shaked", "ofer", "ziv", "avi", "yossi", "dan", "tal", "sapir", "ido", "shir"};
        size_t i = 0;
        for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
            CHECK_EQ(*it, v.at(i++));
        }
    
    

        /*check reverse level order with empty tree*/
        CHECK_THROWS_MESSAGE(org_empty.begin_reverse_order(), "chart is empty!");
        CHECK_THROWS_MESSAGE(org_empty.reverse_order(), "chart is empty!");

        /*check reverse level order with 1 name tree*/
        for(auto it = org_double_names.begin_reverse_order(); it != org_double_names.reverse_order(); ++it){
            CHECK(*it == "adi");
        }

        /* check iter size*/
        std::vector<size_t> nums = {6, 4, 3, 3, 5, 3, 3, 5, 3, 4};
        int j = 0;
        for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
            CHECK_EQ(it->size(), nums.at((size_t)j));
            j++;
        }

    }

    SUBCASE("PreOrder"){
        /*check PreOrder with normal tree*/
        std::vector<std::string> v = {"shir", "tal", "avi", "yossi", "sapir", "dan", "ziv", "shaked", "ofer", "ido"};
        size_t i = 0;
        for(auto it = org.begin_preorder(); it != org.end_preorder(); ++it){
            CHECK_EQ(*it, v.at(i++));
        }

        /*check PreOrder with empty tree*/
        CHECK_THROWS_MESSAGE(org_empty.begin_preorder(), "chart is empty!");
        CHECK_THROWS_MESSAGE(org_empty.end_preorder(), "chart is empty!");

        /*check PreOrder with 1 name tree*/
        for(auto it = org_double_names.begin_preorder(); it != org_double_names.end_preorder(); ++it){
            CHECK(*it == "adi");
        }
        /* check iter size*/
        std::vector<size_t> nums = {4, 3, 3, 5, 5, 3, 3, 6, 4, 3};
        int j = 0;
        for(auto it = org.begin_preorder(); it != org.end_preorder(); ++it){
            CHECK_EQ(it->size(), nums.at((size_t)j));
            j++;
        }
    }

    SUBCASE("special"){
        OrgChart org_special;
        CHECK_NOTHROW(org_special.add_root("boss"));
        CHECK_NOTHROW(org_special.add_root("boss1"));
        CHECK_NOTHROW(org_special.add_root("boss2"));
        CHECK_NOTHROW(org_special.add_root("boss3"));
        CHECK_NOTHROW(org_special.add_root("boss4"));
        CHECK_NOTHROW(org_special.add_root("boss5"));
        CHECK_NOTHROW(org_special.add_root("boss6"));

        /*check that org size is 1, and root is the last*/
        int i =0; 
        for(auto it = org_special.begin_preorder(); it != org_special.end_preorder(); ++it){
            CHECK(*it == "boss6");
            CHECK(i==0);
            i++;
        }


    }



}