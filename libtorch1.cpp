#include <iostream>
#include <torch/torch.h>
using namespace std;

int main() {

    torch::Tensor foo=torch::ones({3,4});
    auto xx=foo.data();
    cout<<typeid(foo).name()<<endl;
    cout<<"next"<<endl;
    cout<<typeid(xx).name()<<endl;

    auto foo_a = foo.accessor<float,2>();
    float trace = 0;
    for(int i = 0; i < foo_a.size(0); i++) {
        // use the accessor foo_a to get tensor data.
        trace += foo_a[i][i];
    }


    float data[] = { 1, 2, 3,
                     4, 5, 6 };
    torch::Tensor f = torch::from_blob(data, {2, 3});

    torch::Tensor ch1 = torch::ones({1,3,4}, at::kFloat);

    torch::Tensor ch23 = torch::zeros({2,3,4}, at::kFloat);

    torch::Tensor result = torch::cat({ch1, ch23}, 0);

    auto ans=result==0;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
