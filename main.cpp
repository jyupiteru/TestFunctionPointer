
#include <unordered_map>
#include <iostream>
#include <functional>

class Test
{
public:
    Test(){};
    ~Test(){};
    int member = 0;

    void Print(int num)
    {
        std::cout << "void Print(int)" << std::endl;
        std::cout << member << std::endl;
        std::cout << num << std::endl;
    }

    void Print2(void)
    {
        std::cout << "void Print2(void)" << std::endl;
    }
};

void ko(int)
{
    std::cout << "616" << std::endl;
}

int main(void)
{
    {
        std::cout << "pointer" << std::endl;
        //普通に関数ポインタを格納
        std::function<void(int)> pointer;

        pointer = ko;
    }

    {
        std::cout << "map1" << std::endl;
        //コンテナにメンバの関数ポインタを格納
        Test test1;
        //関数ポインタをいれるコンテナ
        std::unordered_map<int, std::function<void(void)>> map;

        map[0] = std::bind(&Test::Print2, &test1);

        //実行
        map[0]();
    }

    {
        std::cout << "map2" << std::endl;
        //コンテナに引数ありのメンバの関数ポインタを格納
        Test test2;
        //関数ポインタをいれるコンテナ
        std::unordered_map<int, std::function<void(int)>> map2;

        map2[0] = std::bind(&Test::Print, &test2, std::placeholders::_1);

        //引数を入れて実行
        map2[0](2);

        //本体のほうで引数を変更してみる
        test2.member = 100;

        //引数を入れて実行
        map2[0](200);
    }

    {
        std::cout << "map3" << std::endl;
        //コンテナに引数ありのメンバの関数ポインタを格納
        Test test3, test4;
        //関数ポインタをいれるコンテナ
        std::unordered_map<int, std::function<void(int)>> map3;

        map3[0] = std::bind(&Test::Print, &test3, std::placeholders::_1);

        map3[1] = std::bind(&Test::Print, &test4, std::placeholders::_1);

        //引数を入れて実行
        map3[0](2);

        //本体のほうで引数を変更してみる
        test3.member = 100;

        //引数を入れて実行
        map3[0](200);
        map3[1](200);
    }

    getchar();
}