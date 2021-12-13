/*�� �� �������� ���� �����, � ����� �������� ��� n ������ �� ���� Person � ����� ��� char *, ������ ����������
����� � ����� char *, ����� �� ������� �����������, ����������, ��������, ���������, �� ��������� �� ����
������� �� ������, ��������� �� ������� ���, �� ����� � ������� ���� �� ������������, �� ���������� ��
����� �� ������, ������ �� ���� � ���� �����. ������������� �� ���������� << �� ��������� �� �������.*/

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

//����� �� ���� �� ���������/�������� �� PersonArray
int cnt = 0;

//������������ ���������� �� ������ �� �������� �� char �� ���������
char buffer[50];

//���� P�rson
class Person
{
private:
    int egn;
    char* name;
    char* address;

public:

    //getter-�
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

    //setter-�
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

//���� array, �������� ������ �� person
class PersonArray
{
private:

    //������ array �� ������
    Person persons[5];

    //���������� �������, � ����� ������������� << ���������
    friend ostream& operator <<(ostream& stream, const PersonArray& list);

public:

    Person* Persons;

    //�����������
    PersonArray()
    {
        Persons = persons;
    }

    //����������
    ~PersonArray()
    {
        //�������� ���� ����� ���� ������� �� ������, �� �� ����� �� ���������
        //���������� ����� �� char* ��� � �����, ���� ����� �� ������� ������ �������

        for (int i = 0; i < cnt; i++)
        {
            free(persons[i].GetName());
            free(persons[i].GetAddress());
        }
        delete[] persons;
    }

    //�������� �� person
    void AddPerson()
    {
        //��������� ������ �����
        Person p;

        //��������� �� ������, ��������� �� ���������
        int size;

        //��������� �� ��� �� �������
        int egn;
        cout << "Enter egn:";
        cin >> egn;
        p.SetEgn(egn);

        //��������� �� ��� �� �������
        //�����, ���� �� �������� ����� ���� �������� �� ���������
        //� size, ���� ����� �� ������ ����� �� ���� �������� 
        //� �� ������ ������������ �� buffer � ����-�� ���������� �����
        cout << "Enter name:";
        cin >> buffer;
        size = strlen(buffer);
        char* name = (char*)calloc(size, 1);
        memcpy(name, buffer, size);
        p.SetName(name);

        //��������� �� ���� �� �������
        //������ �� ��������� ����� �� �������� �� ���
        cout << "Enter Address:";
        cin >> buffer;
        size = strlen(buffer);
        char* address = (char*)calloc(size, 1);
        memcpy(address, buffer, size);
        p.SetAddress(address);

        //����������� ����� �� ����� � ������
        persons[cnt] = p;
        cnt++;
    }

    //������ �� person �� ����� � ������
    void DeletePersons()
    {
        //��������� ������� �� ������������
        int id;
        cout << "Enter ID person to delete: " << endl;
        cin >> id;

        //������ �������, -1, �� �� �� �� ������� �� 0
        int num = id - 1;

        //��� ���������� � ������ �� ������ �������� �� ������ ���� ������ �� �� �����
        if (!(num > cnt))
            for (int i = 0; i < cnt; i++)
            {
                if (i == num)
                {
                    //��� � �������� ������� �� ������ ���� �� ������,
                    //���� �� ���� ����� ��������� ������� ������ ����� ������
                    //� �� �� ����, ���� ���� �� ����
                    if (i == cnt)
                    {
                        cnt--;
                        break;
                    }
                    //��� �� � �������� ���� �� ������ �� ������ �� ��� ������� �,
                    //���� ����� ������ ���� ���� �� �������� ���� ����� ������(�� ���������� �����),
                    //���� �� ���� ����� �� override-�� '���������' �������� � �� �����
                    //�� ������ ������� �� ������ (������� � ������, ���� ��� ���������� �������)
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

    //��������� �� ���
    //����� bubble sort
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

    //���� ����� ���� ��� �� ������� �����
    int CountOfPeopleByAddress(const char* value)
    {
        int sum = 0;

        //�������� ������ �� ����� � ������ � ��������� � ����� ����
        for (int i = 0; i < cnt; i++) {
            if (strcmp(value, persons[i].GetAddress()) == 0)
                sum++;
        }

        return sum;
    }

    //writes to a binary file
    void WriteBin()
    {
        //��������� ������ �� ������� ������
        ofstream bf;

        //�������� ������� ����
        bf.open("hello.dat", ios::binary | ios::out);

        //��������� ����� ������� �� ������ � �����
        for (int i = 0; i < cnt; i++)
        {
            bf.write((char*)&persons[i], sizeof(Person));
        }

        bf.close();
    }
};

//������������� �� �������� << ���� ���������� �������
//�� �� ���� �� �� ��� ������ �� private ������������
ostream& operator<<(ostream& stream, const PersonArray& list)
{
    PersonArray people = const_cast <PersonArray&>(list);

    //�� ����� ������� �� ������ �� ������ ������������ ����
    //����������� ������ � �� ������� ���� ��� stream �� ����� �����,
    //����� �������� << ���������� ���� �� ���� ����
    for (int i = 0; i < cnt; i++)
    {
        stream << " EGN: " << people.persons[i].GetEgn() << " Name: " << people.persons[i].GetName() << " Address: " << people.persons[i].GetAddress() << endl;
    }

    return stream;
}

int main()
{
    //��������� �� �����
    PersonArray people;

    //��������� ������
    for (int i = 0; i < 3; i++)
    {
        people.AddPerson();
    }

    //��������� � ������� ����
    people.WriteBin();

    //��������� �� ����� �� ����������
    //� ������ �� ������
    /*cout << "Enter address to search by: " << endl;
    cin >> buffer;
    int size;
    size = strlen(buffer);
    char* address = (char*)calloc(size, 1);
    memcpy(address, buffer, size);
    cout << "people living in asd: " << people.CountOfPeopleByAddress(address) << endl;*/

    //������ �� ������ �� �������� �� ���� ��
    //������ ���� �� ���� ����� � ������� ��������
    cout << "people living in asd: " << people.CountOfPeopleByAddress("asd") << endl;
    cout << endl;

    //��������� �� ���
    people.SortByName();
    cout << people << endl;

    return 0;
}
