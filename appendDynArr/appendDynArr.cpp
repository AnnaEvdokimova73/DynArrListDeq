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

    int* getData()
    {
        return data;
    }

    int getLogSize()
    {
        return logicSize;
    }

    int getFactSize()
    {
        return factSize;
    }

    void add(int index, int value)
    {
        if (index < logicSize)
        {
            data[index] = value;
        }
    }

    void append_to_dynamic_array(int value)
    {
        if (logicSize < factSize)
        {
            data[logicSize] = value;
            ++logicSize;
        }
        else
        {
            int* temp = new int[2 * factSize];
            for (int i = 0; i < logicSize; ++i)
            {
                temp[i] = data[i];
            }
            temp[logicSize] = value;
            ++logicSize;
            factSize = 2 * factSize;
            delete[] data;
            data = new int[factSize];
            for (int i = 0; i < logicSize; ++i)
            {
                data[i] = temp[i];
            }
            delete[] temp;
        }
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

private:
    int factSize;
    int logicSize;
    int* data;
};

void print_dynamic_array(int* arr, int logical_size, int actual_size)
{
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

int main()
{
    setlocale(LC_ALL, "Russian");
    try {
        int factSize = 0, logSize = 0;
        int num;

        std::cout << "Введите фактичеcкий размер массива: \t";
        std::cin >> factSize;
        std::cout << "Введите логический размер массива: \t";
        std::cin >> logSize;

        DynArr dynArr(factSize, logSize);

        for (int i = 0; i < logSize; ++i)
        {
            std::cout << "Введите arr[" << i << "] : ";
            std::cin >> num;
            dynArr.add(i, num);
        }

        std::cout << "Динамический массив: ";
        print_dynamic_array(dynArr.getData(), logSize, factSize);

        while (num != 0)
        {
            std::cout << "Введите элемент для добавления: ";
            std::cin >> num;
            if (num != 0)
            {
                dynArr.append_to_dynamic_array(num);
                std::cout << "Динамический массив: ";
            }
            else
            {
                std::cout << "Спасибо! Ваш массив: ";
            }
            print_dynamic_array(dynArr.getData(), dynArr.getLogSize(), dynArr.getFactSize());
        }
    }
    catch (std::invalid_argument& err)
    {
        std::cout << err.what();
    }
}
