// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


// Add your test cases here

TEST(test_identical_datum){
    List<int> list;
    list.push_back(1);
    list.push_back(1);
    ASSERT_EQUAL(list.back(),list.front());
    ASSERT_EQUAL(list.back(),1);
    ASSERT_NOT_EQUAL(list.begin(),list.end());

}

TEST(test_duplicate_insert_erase){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int> list_copy = list; 

    list_copy.erase(++++list_copy.begin());
    list_copy.insert(list_copy.begin(),7); 
    list_copy.insert(++list_copy.begin(),10);

    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(*++list.begin(),3);
    ASSERT_EQUAL(list.front(),5);
    ASSERT_EQUAL(list.back(),1);

    ASSERT_EQUAL(list_copy.size(),4);
    ASSERT_EQUAL(*++list_copy.begin(),10);
    ASSERT_EQUAL(*++++--++list_copy.begin(),5);
    ASSERT_EQUAL(list_copy.front(),7);
    ASSERT_EQUAL(list_copy.back(),3);


}

TEST(test_default_ctr){
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin()==list.end());
    List<int>::Iterator iter; 
    ASSERT_TRUE(iter==list.end());
}

TEST(test_minus_operator){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int>::Iterator iter_1(++list.begin());
    --iter_1; 
    ASSERT_EQUAL(*iter_1,5);
}

TEST(test_deep_copy_assign){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int>::Iterator iter_1(list.begin());
    List<int>::Iterator iter_2(iter_1);
    ++iter_2;
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(*iter_1,5);
    ASSERT_EQUAL(*iter_2,3);
}

TEST(test_deep_copy_equal){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int>::Iterator iter_1;
    iter_1 = list.begin();
    List<int>::Iterator iter_2;
    iter_2 = iter_1;
    ++iter_2;
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(*iter_1,5);
    ASSERT_EQUAL(*iter_2,3);
}

TEST(test_iterate_interface){
    List<int> list; 
    list.push_back(1); list.push_back(2);
    list.push_back(3);
    List<int>::Iterator end = list.end();

    stringstream ss;
    for (List<int>::Iterator it = list.begin(); it != end; ++it) {
        ss << *it << " "; 
    }

    string correct = "1 2 3 "; 
    ASSERT_EQUAL(correct,ss.str());

}

TEST(test_insert_back){
    List<int> list;
    list.insert(list.end(),3);
    list.insert(list.end(),4);
    list.insert(list.end(),5);
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(list.front(),3);
    ASSERT_EQUAL(*(++list.begin()),4);
    ASSERT_EQUAL(list.back(),5); 

}

TEST(test_insert_4){
    List<int> list;
    list.insert(list.begin(),3);
    list.insert(list.begin(),4);
    list.insert(++list.begin(),2);
    list.insert(++list.begin(),5);
    List<int>::Iterator iter_1 = list.begin();
    ASSERT_EQUAL(list.size(),4);
    ASSERT_EQUAL(list.front(),4);
    ASSERT_EQUAL(list.back(),3); 
    ASSERT_EQUAL(*(++iter_1),5); 
    ++iter_1;
    ASSERT_EQUAL(*iter_1,2); 
}

TEST(test_insert_to_empty){
    List<int> list;
    list.insert(list.begin(),2);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.front(),2);
}

TEST(test_erase_middle){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    list.push_front(7);
    List<int>::Iterator iter_1 = list.begin();
    ++iter_1;
    list.erase(iter_1);
    List<int>::Iterator iter_2 = list.begin();
    ++iter_2;
    ASSERT_EQUAL(*iter_2,3);
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(list.back(),1);
    ASSERT_EQUAL(list.front(),7);
    iter_2 = list.begin();
    ASSERT_EQUAL(*iter_2,7);
}

TEST(test_erase_zero){
    List<int> list;
    list.push_back(3);
    list.erase(list.begin());
    ASSERT_TRUE(list.empty());
}

TEST(test_erase_back){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int>::Iterator iter_1 = list.begin();
    ++iter_1;++iter_1;
    list.erase(iter_1);
    ASSERT_EQUAL(list.size(),2);
    ASSERT_EQUAL(list.back(),3);
    ASSERT_EQUAL(list.front(),5);
}

TEST(test_erase_start){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    list.push_front(5);
    List<int>::Iterator iter_1 = list.begin();
    list.erase(iter_1);
    ASSERT_EQUAL(list.size(),2);
    ASSERT_EQUAL(list.front(),3);
}
//done
TEST(test_equal_operator){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    List<int>::Iterator iter_1 = list.begin();
    List<int>::Iterator iter_2 = list.begin();
    ASSERT_TRUE(iter_2==iter_1);

}

TEST(test_not_equal_operator){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    List<int>::Iterator iter_1 = list.begin();
    List<int>::Iterator iter_2 = list.begin();
    ++iter_2;
    ASSERT_TRUE(iter_2!=iter_1);
}

TEST(test_assign_constructor){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    List<int>::Iterator iter = list.begin();
    ASSERT_EQUAL(*iter,3);
    ++iter;
    ASSERT_EQUAL(*iter,1);
}

TEST(test_copy_constructor){
    List<int> list;
    list.push_back(3);
    list.push_back(1);
    List<int>::Iterator iter(list.begin());
    ASSERT_EQUAL(*iter,3);
    ++iter;
    ASSERT_EQUAL(*iter,1);
}

TEST(test_list_size){
    List<double> empty_list;
    ASSERT_EQUAL(empty_list.size(),0);
}   

TEST(test_list_push_front_back){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(list.front(),1);
    ASSERT_EQUAL(list.back(),4);
}   

TEST(test_list_edit_front_back){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    list.front() = 7;
    list.back() = 5;
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(list.front(),7);
    ASSERT_EQUAL(list.back(),5);
}   

TEST(test_list_pop_front){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    list.pop_front();
    list.pop_front();
    ASSERT_EQUAL(list.size(),1);
    ASSERT_EQUAL(list.front(),4);
    ASSERT_EQUAL(list.back(),4);
    ASSERT_FALSE(list.empty());
}

TEST(test_list_pop_back){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    list.pop_back();
    ASSERT_EQUAL(list.size(),2);
    ASSERT_EQUAL(list.front(),1);
    ASSERT_EQUAL(list.back(),3);
    ASSERT_FALSE(list.empty());
}

TEST(test_list_zero){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    list.pop_back();
    list.pop_back();
    list.pop_front();
    ASSERT_EQUAL(list.size(),0);
    ASSERT_TRUE(list.empty());
    list.push_front(10);
    ASSERT_EQUAL(list.size(),1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.front(),10);
    ASSERT_EQUAL(list.back(),10);
}

TEST(test_list_copy){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    List<int> list_copy(list);
    ASSERT_EQUAL(list_copy.size(),3);
    ASSERT_EQUAL(list_copy.front(),1);
    ASSERT_EQUAL(list_copy.back(),4);
    ASSERT_FALSE(list_copy.empty());
}

TEST(testing_deep_copy){
    List<int> list;
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    List<int> list_copy(list);
    list_copy.pop_back();
    list_copy.back() = 10;
    ASSERT_EQUAL(list.size(),3);
    ASSERT_EQUAL(list_copy.size(),2);
    ASSERT_EQUAL(list.back(),4);
    ASSERT_EQUAL(list_copy.back(),10);

}

TEST(testing_equal_copy){
    List<int> list,list_copy; 
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    list_copy = list; 
    list_copy.back() = 10; 
    ASSERT_EQUAL(list.back(),4);
    ASSERT_EQUAL(list_copy.size(),3);
    ASSERT_EQUAL(list_copy.back(),10);
    ASSERT_EQUAL(list_copy.front(),1);
}

TEST(testing_clear){
    List<int> list,list_copy; 
    list.push_front(1);
    list.push_back(3);
    list.push_back(4);
    ASSERT_EQUAL(list.size(),3);
    list.clear();
    ASSERT_EQUAL(list.size(),0);
    ASSERT_TRUE(list.empty());

    list.insert(list.end(),2);
    ASSERT_EQUAL(list.size(),1);
    ASSERT_EQUAL(list.front(),2);
    ASSERT_EQUAL(list.back(),list.front());
}

TEST_MAIN()
