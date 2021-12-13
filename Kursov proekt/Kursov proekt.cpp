/*Да се дефинира клас масив, с данна указател към n обекти от клас Person с данни име char *, единен граждански
номер и адрес char *, който да включва конструктор, деструктор, добавяне, изтриване, за извеждане на член
данните на екрана, подредени по азбучен ред, за запис в двоичен файл на информацията, за определяне на
броят на лицата, живущи на един и същи адрес. Предефиниране на операцията << за извеждане на данните.*/

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

//брояч на броя на членовете/обектите на PersonArray
int cnt = 0;

//спомагателна променлива за четене на поредица от char от конзолата
char buffer[50];

//Клас Pеrson
class Person
{
private:
    int egn;
    char* name;
    char* address;

public:

    //getter-и
    int const GetEgn()
    {
        return egn;
    }

    char* GetName()
    {
        return name;
    }

    char* GetAddress()
    {
        return address;
    }

    //setter-и
    void SetEgn(int value)
    {
        this->egn = value;
    }

    void SetName(char* value)
    {
        this->name = value;
    }

    void SetAddress(char* value)
    {
        this->address = value;
    }
};

//клас array, съдържащ обекти от person
class PersonArray
{
private:

    //самият array от обекти
    Person persons[5];

    //приятелска фукнция, с която предефинираме << оператора
    friend ostream& operator <<(ostream& stream, const PersonArray& list);

public:

    Person* Persons;

    //коснтруктор
    PersonArray()
    {
        Persons = persons;
    }

    //деструктор
    ~PersonArray()
    {
        //минаваме през всеки един елемент от масива, за да можем да освободим
        //заделената памет за char* име и адрес, след което се изтрива самият пойнтър

        for (int i = 0; i < cnt; i++)
        {
            free(persons[i].GetName());
            free(persons[i].GetAddress());
        }
        delete[] persons;
    }

    //добавяне на person
    void AddPerson()
    {
        //създаваме празен обект
        Person p;

        //дължината на думата, прочетена от конзолата
        int size;

        //попълване на егн от конзола
        int egn;
        cout << "Enter egn:";
        cin >> egn;
        p.SetEgn(egn);

        //попълване на име от конзола
        //става, като се прочитат даден брой елементи от конзолата
        //в size, след което се заделя памет за тези елементи 
        //и се копира съдържанието на buffer в току-що заделената памет
        cout << "Enter name:";
        cin >> buffer;
        size = strlen(buffer);
        char* name = (char*)calloc(size, 1);
        memcpy(name, buffer, size);
        p.SetName(name);

        //попълване на адрс от конзола
        //работи по идентичен начин на четенето на име
        cout << "Enter Address:";
        cin >> buffer;
        size = strlen(buffer);
        char* address = (char*)calloc(size, 1);
        memcpy(address, buffer, size);
        p.SetAddress(address);

        //създаденият обект се слага в масива
        persons[cnt] = p;
        cnt++;
    }

    //триене на person по място в масива
    void DeletePersons()
    {
        //въвеждаме мястото от клавиатурата
        int id;
        cout << "Enter ID person to delete: " << endl;
        cin >> id;

        //самата позиция, -1, за да не се въвежда от 0
        int num = id - 1;

        //ако въведеното е повече от самата големина на масива няма смисъл да се търси
        if (!(num > cnt))
            for (int i = 0; i < cnt; i++)
            {
                if (i == num)
                {
                    //ако е последна позиция се намаля броя на масива,
                    //като по този начин псоледния елемент остава извън масива
                    //и не се брои, като част от него
                    if (i == cnt)
                    {
                        cnt--;
                        break;
                    }
                    //Ако не е последен член на масива се намира на коя позиция е,
                    //след което всички след него се избутват едно място наляво(на предишното място),
                    //като по този начин се override-ва 'изтритата' стойност и за финал
                    //се намаля мястото на масива (логката е същата, като при последната позиция)
                    else
                    {
                        for (int j = i; j < cnt - i; j++)
                        {
                            persons[j] = persons[j + 1];
                        }
                        cnt--;
                        break;
                    }
                }
            }
    }

    //сортиране по име
    //прост bubble sort
    void SortByName()
    {
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < i; j++) {
                if (strcmp(persons[i].GetName(), persons[j].GetName()) < 0) {
                    Person temp = persons[i];
                    persons[i] = persons[j];
                    persons[j] = temp;
                }
            }
        }
    }

    //брои колко хора има на въведен адрес
    int CountOfPeopleByAddress(const char* value)
    {
        int sum = 0;

        //сравнява адреса на всеки в масива с въведения и връша брой
        for (int i = 0; i < cnt; i++) {
            if (strcmp(value, persons[i].GetAddress()) == 0)
                sum++;
        }

        return sum;
    }

    //writes to a binary file
    void WriteBin()
    {
        //създаваме стрийм за бинарно писане
        ofstream bf;

        //отваряме бинарен файл
        bf.open("hello.dat", ios::binary | ios::out);

        //записване всеки елемент от масива в файла
        for (int i = 0; i < cnt; i++)
        {
            bf.write((char*)&persons[i], sizeof(Person));
        }

        bf.close();
    }
};

//предефиниране на опратора << чрез приятелска функция
//за да може тя да има достъп до private променливите
ostream& operator<<(ostream& stream, const PersonArray& list)
{
    PersonArray people = const_cast <PersonArray&>(list);

    //за всеки елемент на масива се гетват променливите през
    //съответните гетъри и се създава един общ stream за целия обект,
    //който замества << операцията само за този клас
    for (int i = 0; i < cnt; i++)
    {
        stream << " EGN: " << people.persons[i].GetEgn() << " Name: " << people.persons[i].GetName() << " Address: " << people.persons[i].GetAddress() << endl;
    }

    return stream;
}

int main()
{
    //създаваме си масив
    PersonArray people;

    //попълваме масива
    for (int i = 0; i < 3; i++)
    {
        people.AddPerson();
    }

    //записваме в двоичен файл
    people.WriteBin();

    //въвеждане на адрес от клавиатура
    //и викане на метода
    /*cout << "Enter address to search by: " << endl;
    cin >> buffer;
    int size;
    size = strlen(buffer);
    char* address = (char*)calloc(size, 1);
    memcpy(address, buffer, size);
    cout << "people living in asd: " << people.CountOfPeopleByAddress(address) << endl;*/

    //викане на метода за намиране на броя на
    //живущи лица на един адрес с тестова стойност
    cout << "people living in asd: " << people.CountOfPeopleByAddress("asd") << endl;
    cout << endl;

    //сортиране по име
    people.SortByName();
    cout << people << endl;

    return 0;
}
