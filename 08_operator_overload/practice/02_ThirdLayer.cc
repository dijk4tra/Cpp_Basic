#include <iostream>
#include <sys/types.h>

using std::cout;
using std::endl;

class Data
{
private:
    int m_data;

public:
    Data(int data = 0)
    : m_data(data)
    {
        cout << "Data()" << endl;
    }

    ~Data()
    {
        cout << "~Data()" << endl;
    }

    int getData() const
    {
        return m_data;
    }
};


class MiddleLayer
{
private:
    Data* m_pdata;

public:
    MiddleLayer(Data *p)
    : m_pdata(p)
    {
        cout << "MiddleLayer()" << endl;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;
        delete m_pdata;
        m_pdata = nullptr;
    }

    Data* operator->()
    {
        return m_pdata;
    }

    const Data* operator->() const
    {
        return m_pdata;
    }

};


class ThirdLayer
{
private:
    MiddleLayer* m_pml;

public:
    ThirdLayer(MiddleLayer* pm)
    : m_pml(pm)
    {
        cout << "ThirdLayer()" << endl;
    }

    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        delete m_pml;
        m_pml = nullptr;
    }

    MiddleLayer& operator->()
    {
        return *m_pml;
    }

    const MiddleLayer& operator->() const
    {
        return *m_pml;
    }
};

int main(int argc, char *argv[])
{
    ThirdLayer t1{new MiddleLayer{new Data{100}}};

    cout << t1->getData() << endl;

    return 0;
}

