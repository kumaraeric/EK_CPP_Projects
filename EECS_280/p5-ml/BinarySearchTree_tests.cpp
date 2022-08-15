// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//testing min_max

TEST(test_min_max){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);
    ASSERT_EQUAL(BST.min_greater_than(20),BST.end());

    ASSERT_EQUAL(*BST.min_greater_than(6),8);
    ASSERT_EQUAL(*BST.min_greater_than(8),9);
    ASSERT_EQUAL(BST.min_greater_than(-2),BST.begin());
    ASSERT_EQUAL(*BST.min_greater_than(0),1);
    ASSERT_EQUAL(*BST.min_greater_than(1),3);
}

//finding

TEST(test_BST_finding){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BinarySearchTree<int>::Iterator itr = BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);

    ASSERT_EQUAL(BST.find(0),BST.begin());
    ASSERT_EQUAL(itr,BST.begin());
    ASSERT_EQUAL(BST.find(1),++BST.begin());
    ASSERT_EQUAL(BST.find(3),++++BST.begin());
    ASSERT_EQUAL(BST.find(5),++++++BST.begin());
    ASSERT_EQUAL(BST.find(6),++++++++BST.begin());
    ASSERT_EQUAL(BST.find(8),++++++++++BST.begin());
    ASSERT_EQUAL(BST.find(9),++++++++++++BST.begin());
    ASSERT_EQUAL(BST.find(10),BST.end());
}

//traversal 

TEST(test_inorder_traversal){
    BinarySearchTree <int> BST; 
    ostringstream ss; 
    string empty= "";
    BST.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(),empty);

    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);

    BST.traverse_inorder(ss);

    ostringstream output;
    output << "0 " << "1 " << "3 " <<"5 "
    << "6 " <<"8 " << "9 ";
    ASSERT_EQUAL(output.str(),ss.str());
}

TEST(test_preorder_traversal){
    BinarySearchTree <int> BST; 
    ostringstream ss; 
    string empty= "";
    BST.traverse_preorder(ss);
    ASSERT_EQUAL(ss.str(),empty);

    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);

    BST.traverse_preorder(ss);

    ostringstream output;
    output << "5 " << "1 " << "0 " <<"3 "
    << "8 " <<"6 " << "9 ";

    ASSERT_EQUAL(output.str(),ss.str());
}

//invariant cases

TEST(test_BST_invariant_fail_trial_4){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);
    *(++++++++BST.begin()) = 1;
    ASSERT_FALSE(BST.check_sorting_invariant());
}

TEST(test_BST_invariant_fail_trial_3){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);
    *(++BST.begin()) = 10;
    ASSERT_FALSE(BST.check_sorting_invariant());
}

TEST(test_BST_invariant_fail_trial_2){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);
    *BST.begin() = 5;
    ASSERT_FALSE(BST.check_sorting_invariant());
}

TEST(test_BST_invariant_empty_and_one_element){
    BinarySearchTree <int> BST; 
    ASSERT_TRUE(BST.check_sorting_invariant());
    BST.insert(1);
    ASSERT_TRUE(BST.check_sorting_invariant());
}

TEST(test_BST_invariant_fail_trial_1){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    *BST.begin() = 2;
    ASSERT_FALSE(BST.check_sorting_invariant());
}

TEST(test_BST_sorting_invariant_trial_2){
    BinarySearchTree <int> BST; 
    BST.insert(5);
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(8);
    BST.insert(6);
    BST.insert(9);
    ASSERT_TRUE(BST.check_sorting_invariant());
}

TEST(test_BST_sorting_invariant_trial_1){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(-2);
    BST.insert(5);
    BST.insert(2);
    ASSERT_TRUE(BST.check_sorting_invariant());

}

//cases where the max has 0 leaf and 1 leaf, 1 element

TEST(test_BST_max_element_zero_leaf){
    BinarySearchTree <int> BST; 
    ASSERT_EQUAL(BST.max_element(),BinarySearchTree<int>::Iterator());
    BST.insert(1);
    BST.insert(0);
    ASSERT_EQUAL(*BST.max_element(),1);
    BST.insert(3);
    BST.insert(-2);
    ASSERT_EQUAL(*BST.max_element(),3);
    BST.insert(5);
    ASSERT_EQUAL(*BST.max_element(),5);
}

TEST(test_BST_max_element_one_leaf){
    BinarySearchTree <int> BST; 
    ASSERT_EQUAL(BST.max_element(),BinarySearchTree<int>::Iterator());
    BST.insert(1);
    ASSERT_EQUAL(*BST.max_element(),1);
    BST.insert(0);
    ASSERT_EQUAL(*BST.max_element(),1);
    BST.insert(3);
    ASSERT_EQUAL(*BST.max_element(),3);
    BST.insert(-2);
    ASSERT_EQUAL(*BST.max_element(),3);
    BST.insert(5);
    BST.insert(4);
    ASSERT_EQUAL(*BST.max_element(),5);
}

TEST(test_BST_min_element_zero_leaf){
    BinarySearchTree <int> BST; 
    ASSERT_EQUAL(BST.min_element(),BinarySearchTree<int>::Iterator());
    BST.insert(1);
    ASSERT_EQUAL(*BST.min_element(),1);
    BST.insert(3);
    ASSERT_EQUAL(*BST.min_element(),1);
    BST.insert(0);
    ASSERT_EQUAL(*BST.min_element(),0);
    ASSERT_EQUAL(BST.min_element(),BST.begin());
    BST.insert(-2);
    ASSERT_EQUAL(*BST.min_element(),-2);
    BST.insert(5);
    ASSERT_EQUAL(*BST.min_element(),-2);
}

TEST(test_BST_min_element_one_leaf){
    BinarySearchTree <int> BST; 
    ASSERT_EQUAL(BST.min_element(),BinarySearchTree<int>::Iterator());
    BST.insert(1);
    ASSERT_EQUAL(*BST.min_element(),1);
    BST.insert(3);
    ASSERT_EQUAL(*BST.min_element(),1);
    BST.insert(0);
    ASSERT_EQUAL(*BST.min_element(),0);
    BST.insert(-2);
    BST.insert(-1);
    ASSERT_EQUAL(*BST.min_element(),-2);
    BST.insert(5);
    ASSERT_EQUAL(*BST.min_element(),-2);
}

TEST(test_BST_min_element_one_element){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    ASSERT_EQUAL(*BST.min_element(),*BST.max_element());
    ASSERT_EQUAL(*BST.min_element(),1);
}

// cases: normal, only left, only right

TEST(test_BST_left_sub_size_height){
    BinarySearchTree <int> BST; 
    BST.insert(10);
    BST.insert(9);
    BST.insert(6);
    BST.insert(8);
    BST.insert(4);
    ASSERT_EQUAL(BST.size(),5);
    ASSERT_EQUAL(BST.height(),4u);
}

TEST(test_BST_right_sub_size_height){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(8);
    BST.insert(5);
    BST.insert(10);
    BST.insert(4);
    ASSERT_EQUAL(BST.size(),5);
    ASSERT_EQUAL(BST.height(),4u);
}

TEST(test_BST_size_height){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);
    BST.insert(5);
    BST.insert(2);
    ASSERT_EQUAL(BST.size(),5);
    ASSERT_EQUAL(BST.height(),3u);
}

//copy cases

TEST(test_BST_copy_value_comparison){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(3);
    BST.insert(-2);
    BST.insert(5);
    BST.insert(2);

    BinarySearchTree <int> BST_copy = BST;  
    BinarySearchTree<int>::Iterator iter = BST.begin();
    BinarySearchTree<int>::Iterator iter_copy = BST_copy.begin();

    for(;iter_copy!=BST_copy.end();++iter_copy){
        ASSERT_EQUAL(*iter,*iter_copy);
        ASSERT_NOT_EQUAL(iter,iter_copy);
       ++iter;
    }

    iter = BST.begin();
    iter_copy = BST_copy.begin();
    *iter = 3; 
    ASSERT_NOT_EQUAL(iter,iter_copy);

}

// add test to check each element are same

TEST(test_BST_copy_begin_values_only){
    BinarySearchTree <int> BST; 
    BST.insert(1);
    BST.insert(0);
    BST.insert(3);

    BinarySearchTree <int> BST_copy = BST; 
    ASSERT_NOT_EQUAL(&BST,&BST_copy);
    ASSERT_EQUAL(*BST.begin(),*BST_copy.begin());
    *BST_copy.begin() = 10;
    ASSERT_NOT_EQUAL(*BST.begin(),*BST_copy.begin());

}

//no special cases

TEST(test_BST_empty) {
    BinarySearchTree <int> BST; 
    ASSERT_TRUE(BST.empty());
    ASSERT_EQUAL(BST.size(),0);
    ASSERT_EQUAL(BST.height(),0u);
    ASSERT_TRUE(BST.max_element() == BST.end());
    ASSERT_TRUE(BST.min_element() == BST.end());
    BST.insert(2);
    ASSERT_FALSE(BST.empty());
}

TEST(test_BST_doubles_diff_type){
    BinarySearchTree<double> BST;
    ASSERT_TRUE(BST.empty());
    BST.insert(2.1);
    ASSERT_FALSE(BST.empty());
}

TEST_MAIN()
