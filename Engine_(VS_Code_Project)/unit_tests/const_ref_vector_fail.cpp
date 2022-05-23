#include <iostream>
#include <vector>

int main(){
    std::vector<int> this_vec={5,6,7,8,9};
    const std::vector<int>& my_const_ref_to_vec = this_vec;

    for(auto element:my_const_ref_to_vec){
        std::cout<< element << std::endl;
    }

    return 0;
}