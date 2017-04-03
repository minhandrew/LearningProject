/* INPUT:
Barack Obama - +84978817165 - 68/6 Red Street - 9.75 8.5 9
Donald Trump - +84947821558 - 11 Green Street - 8.75 9.5 8.75
Hillary Clinton - +841299992930 - 22 Yellow Street - 9.25 8 9
Bill Clinton - +84988345692 - 69/6 Pink Street - 9 8.75 8.5
George Washington - +84982584394 - 24/5 Brown Street - 9.25 9 8.75
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
 
typedef struct
{
    std::string name, phone_number, address;
    double Math, Physics, Chemistry, AveragePoint;
} stdinf;
 
std::vector<stdinf> ReadFile(std::fstream &); // Read data from a file to a vector
void SortStudent(std::vector<stdinf> &); // Sort the vector by average point
void WriteFile(std::fstream &, std::vector<stdinf>); // Write the vector to a file
 
std::vector<stdinf> ReadFile(std::fstream &FileIn)
{
    std::vector<stdinf> s;
    FileIn.open("INPUT.txt", std::ios::in);
    if (FileIn.fail()) {
        std::cout << "Cannot find this file!\n";
        exit(0);
    }
    std::string Name, Phone_number, Address;
    float math, physics, chemistry, averagePoint;
    while (std::getline(FileIn, Name, '-'))
    {
        Name.erase(Name.end() - 1);
        std::getline(FileIn, Phone_number, '-');
        Phone_number.erase(Phone_number.begin());
        Phone_number.erase(Phone_number.end() - 1);
        std::getline(FileIn, Address, '-');
        Address.erase(Address.begin());
        Address.erase(Address.end() - 1);
        FileIn >> math >> physics >> chemistry;
        averagePoint = (math + physics + chemistry) / 3;
        stdinf f;
        f.name = Name;
        f.phone_number = Phone_number;
        f.address = Address;
        f.Math = math;
        f.Physics = physics;
        f.Chemistry = chemistry;
        f.AveragePoint = averagePoint;
        s.push_back(f);
    }
    return s;
}
 
void SortStudent(std::vector<stdinf> &s)
{
    int length = s.size();
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (s[i].AveragePoint > s[j].AveragePoint)
                std::swap(s[i].AveragePoint, s[j].AveragePoint);
        }
    }
}
 
void WriteFile(std::fstream &FileOut, std::vector<stdinf> s)
{
    FileOut.open("OUTPUT.txt", std::ios::out);
    int length = s.size();
    for (int i = 0; i < length; ++i)
    {
        FileOut << "Student " << i + 1 << ":\n";
        FileOut << "Name: " << s[i].name << std::endl;
        FileOut << "Phone number: " << s[i].phone_number << std::endl;
        FileOut << "Address: " << s[i].address << std::endl;
        FileOut << "Math - Physics - Chemistry point: " << s[i].Math << " " << s[i].Physics << " " << s[i].Chemistry << std::endl;
        FileOut << "Average point: " << s[i].AveragePoint << std::endl;
    }
}
 
int main()
{
    std::fstream FileIn, FileOut;
    std::vector<stdinf> s;
    s = ReadFile(FileIn);
    SortStudent(s);
    WriteFile(FileOut, s);
    FileOut.close();
    FileIn.close();
    return 0;
}