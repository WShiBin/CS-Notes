#pragma once

#include <iostream>

using namespace std;

template <class T>
class MyArray
{
public:
    MyArray(int capcity)
    {
        cout << "constrcutor" << endl;
        this->m_Capcity = capcity;
        this->m_Size = 0;
        this->m_Address = new T[capcity];
    }

    // 拷贝
    MyArray(const MyArray &arr)
    {
        cout << "copy constrcutor" << endl;
        MyArray *ret = new MyArray(arr.m_Capcity);
        ret->m_Address = new T(arr.m_Capcity);
        ret->m_Size = arr.m_Size;
        ret->m_Capcity = arr.m_Capcity;
        for (int i = 0; i < arr.m_Size; i++)
            ret->m_Address[i] = arr.m_Address[i];
    }

    // 析构
    ~MyArray()
    {
        cout << "destrcutor" << endl;
        if (m_Address != nullptr)
        {
            // delete 指向数组的指针
            delete[] this->m_Address;
            this->m_Address = nullptr;
        }
    }

    int getSize()
    {
        return this->m_Size;
    }

    int getCapcity()
    {
        return this->m_Capcity;
    }

    void deleteBack()
    {
        if (this->m_Size == 0)
        {
            return;
        }
        this->m_Size--;
    }

    void deleteHead()
    {
        if (this->m_Size == 0)
        {
            return;
        }
        for (int i = 0; i < this->m_Size - 1; i++)
        {
            this->m_Address[i] = this->m_Address[i + 1];
        }
        this->m_Size--;
    }

    void deleteWithIndex(int index)
    {
        if (index < 0 || index >= this->m_Size)
        {
            return;
        }
        for (int i = index; i < this->m_Size - 1; i++)
        {
            this->m_Address[i] = this->m_Address[i + 1];
        }
        this->m_Size--;
    }

    void pushBack(T t)
    {
        if (this->m_Size == 0)
        {
            this->m_Address[0] = t;
            this->m_Size++;
            return;
        }
        if (this->m_Size + 1 > this->m_Capcity)
        {
            T *tmp = this->m_Address;
            this->m_Address = new T[this->m_Capcity * 2];
            this->m_Capcity = this->m_Capcity * 2;
            for (int i = 0; i < this->m_Size; i++)
            {
                this->m_Address[i] = tmp[i];
            }
            // this->m_Address[this->m_Size] = t;
            if (tmp != nullptr)
            {
                delete[] tmp;
                tmp = nullptr;
            }
        }
        this->m_Address[this->m_Size] = t;

        this->m_Size++;
    }

    void pushHead(T t)
    {
        // 没有元素
        if (this->m_Size == 0)
        {
            this->m_Address[0] = t;
            this->m_Size++;
            return;
        }
        // 元素满了
        if (this->m_Size + 1 > this->m_Capcity)
        {
            T *tmp = this->m_Address;
            this->m_Address = new T[this->m_Capcity * 2];
            this->m_Capcity = this->m_Capcity * 2;
            // 移动数据
            for (int i = 1; i < this->m_Size + 1; i++)
            {
                this->m_Address[i] = tmp[i - 1];
            }
            // 删除原来的数据
            if (tmp != nullptr)
            {
                delete[] tmp;
                tmp = nullptr;
            }
        }
        // 元素没满
        // 移动数据
        for (int i = this->m_Size; i > 0; i--)
        {
            this->m_Address[i] = this->m_Address[i - 1];
        }

        // 存放数据
        this->m_Address[0] = t;

        this->m_Size++;
    }

    T operator[](int index)
    {
        if (index < 0 || index > this->m_Size)
        {
            exit(1);
        }
        return this->m_Address[index];
    }
    // 赋值操作符
    MyArray &operator=(MyArray &arr)
    {
        if (this->m_Address != nullptr)
        {
            delete[] this->m_Address;
            this->m_Address = nullptr;
            this->m_Capcity = 0;
            this->m_Size = 0;
        }
        this->m_Address = new T(arr.m_Capcity);
        this->m_Size = arr.m_Size;
        this->m_Capcity = arr.m_Capcity;
        for (int i = 0; i < arr.m_Size; i++)
            this->m_Address[i] = arr.m_Address[i];
        return *this;
    }

private:
    T *m_Address;
    int m_Capcity;
    int m_Size;
};