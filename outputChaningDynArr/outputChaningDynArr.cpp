#include <iostream>

class DynArr {
public:
    DynArr(int _factSize, int _logicSize) 
    {
        if (_logicSize > _factSize)
        {
            throw std::invalid_argument("Ошибка! Логический размер массива не может превышать фактический!\n");
        }
        else
        {
            factSize = _factSize;
            logicSize = _logicSize;
            data = new int[factSize];
        }
    }

    ~DynArr() {
        delete[] data;
    }

    void add(int index, int value)
    {
        if (index < logicSize)
        {
            data[index] = value;
        }
    }

    int* getData()
    {
        return data;
    }

    int operator[](int index)
    {
        if (index <= logicSize)
        {
            return data[index];
        }
        else
        {
            throw std::invalid_argument("Ошибка! Выход за границы массива!\n");
        }
    }

    friend void print_dynamic_array(int* arr, int logical_size, int actual_size);

    //friend std::istream& operator>>(std::istream& in, int right);
    //friend std::ostream& operator<<(std::ostream& out, DynArr right);

private:
    int factSize;
    int logicSize;
    int* data;
};

void print_dynamic_array(int* arr, int logical_size, int actual_size)
{
    std::cout << "Динамический массив: ";
    for (int i = 0; i < actual_size; ++i)
    {
        if (i < logical_size)
        {
            std::cout << arr[i] << " ";
        }
        else
        {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

/*std::ostream& operator<<(std::ostream& out, DynArr right)
{
    out << right.getValue();
    return out;
}*/

/*std::istream& operator>>(std::istream& in, DynArr right)
{
    int value;
    in >> value;
    right.setValue(right.getIndex(), value);
    return in;
}*/


int main()
{
    setlocale(LC_ALL, "Russian");
    try {
        int factSize = 0, logSize = 0;
        std::cout << "Введите фактичеcкий размер массива: \t";
        std::cin >> factSize;
        std::cout << "Введите логический размер массива: \t";
        std::cin >> logSize;

        DynArr dynArr(factSize, logSize);

        for (int i = 0; i < logSize; ++i)
        {
            int num;
            std::cout << "Введите arr[" << i << "] : ";
            std::cin >> num;
            dynArr.add(i, num);
        }

        print_dynamic_array(dynArr.getData(), logSize, factSize);
    }
    catch (std::invalid_argument& err)
    {
        std::cout << err.what();
    }
}
