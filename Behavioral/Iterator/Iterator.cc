// 迭代器模式的示例
#include <iostream>
#include <vector>

class MyIterator {
   private:
    std::vector<int> data;
    int index;

   public:
    MyIterator(std::vector<int>& d) : data(d), index(0) {}
    bool hasNext() { return index < data.size(); }
    int next() {
        if (!hasNext())
            throw std::out_of_range("Reached end of iteration");
        return data[index++];
    }
};

int main() {
    std::vector<int> data{1, 2, 3};
    MyIterator iterator(data);
    while (iterator.hasNext()) {
        std::cout << iterator.next() << std::endl;
    }
    return 0;
}
