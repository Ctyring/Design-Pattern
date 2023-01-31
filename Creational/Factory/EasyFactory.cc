// 简单工厂模式
// 工厂类负责对象的构建
#include <iostream>
#include <vector>
using namespace std;

// Here is the product class
class Operation {
   public:
    int var1, var2;
    virtual double GetResult() {
        double res = 0;
        return res;
    }
};

class Add_Operation : public Operation {
   public:
    virtual double GetResult() { return var1 + var2; }
};

class Sub_Operation : public Operation {
   public:
    virtual double GetResult() { return var1 - var2; }
};

class Mul_Operation : public Operation {
   public:
    virtual double GetResult() { return var1 * var2; }
};

class Div_Operation : public Operation {
   public:
    virtual double GetResult() { return var1 / var2; }
};

// Here is the Factory class
class Factory {
   public:
    static Operation* CreateProduct(char op) {
        switch (op) {
            case '+':
                return new Add_Operation();

            case '-':
                return new Sub_Operation();

            case '*':
                return new Mul_Operation();

            case '/':
                return new Div_Operation();

            default:
                return new Add_Operation();
        }
    }
};

int main() {
    int a, b;
    cin >> a >> b;
    Operation* p = Factory::CreateProduct('+');
    p->var1 = a;
    p->var2 = b;
    cout << p->GetResult() << endl;

    p = Factory::CreateProduct('*');
    p->var1 = a;
    p->var2 = b;
    cout << p->GetResult() << endl;

    return 0;
}