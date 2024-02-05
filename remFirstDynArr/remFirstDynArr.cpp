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

    void remove_dynamic_array_head()
    {
        if (logicSize == 0)
        {
            throw std::invalid_argument("Невозможно удалить первый элемент, так как массив пустой. До свидания!\n");
        }
        else if (logicSize - 1 > factSize/3)
        {
            for (int i = 1; i < logicSize; ++i)
            {
                data[i - 1] = data[i];
            }
            --logicSize;
        }
        else 
        {
            int* temp = new int[factSize / 3]; // создаем массив меньше, иначе будет слишком много запаса
            for (int i = 1; i < logicSize; ++i)
            {
                temp[i - 1] = data[i];
            }
            --logicSize;
            factSize = factSize / 3;
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
    if (actual_size == 0)
    {
        std::cout << "_ ";
    }
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
        std::string answer = "";

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

        while (answer != "no")
        {
            try {
                std::cout << "Удалить первый элемент? ";
                std::cin >> answer;
                if (answer == "yes")
                {
                    dynArr.remove_dynamic_array_head();
                    std::cout << "Динамический массив: ";
                }
                else if (answer == "no")
                {
                    std::cout << "Спасибо! Ваш динамический массив: ";
                }
                print_dynamic_array(dynArr.getData(), dynArr.getLogSize(), dynArr.getFactSize());
            }
            catch (std::invalid_argument& err)
            {
                std::cout << err.what();
                break;
            }
        }
    }
    catch (std::invalid_argument& err)
    {
        std::cout << err.what();
    }
}
