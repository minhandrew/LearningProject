/* Đề bài: 			ĐỀ THI VỀ PHƯƠNG PHÁP SUY LUẬN
 
Animals Race là cuộc đua thường niên diễn ra vào mua xuân tại ngôi làng Ankoslus của các con vật sinh sống. Cuộc đua Animals Race 2016 năm nay sẽ có 3 loại con vật tham dự với thông tin cơ bản của 1 con vật bao gồm:
 - m_Code (mã số): Kiểu chuỗi
 - m_Speed (tốc độ): Kiểu số nguyên (km/h)
 -  m_Equipment (trang bị): Kiểu số nguyên (1 là có trang bị, 0 là không trang bị)
 
Đường đua năm nay dài 210km từ thung lũng Busa xinh đẹp đi đến thảo nguyên Hasga mộng mơ được bắt đầu lúc 7h sáng đến 12h trưa. Những con vật nào đến đích sau 12h trưa sẽ bị cho là bỏ cuộc.
 
Mỗi loại con vật đều quy định riêng như sau:
 - Lion (sư tử): Khởi hành lúc 9h. Nếu sư tử có trang bị thêm móng sắt thì tốc độ sẽ được tăng lên gấp đôi.
 - Rabbit (thỏ): Khởi hành sớm lúc 8h. Nếu thỏ có trang bị thêm tai thông minh thì tốc độ sẽ tăng thêm 30km/h
 - Tortoise (rùa): Được ưu tiên khởi hành lúc 7h và được ưu tiên bắt đầu đi từ khu vườn Taka cách thung lũng Busa 75km. Nếu rùa có trang bị thêm mai vàng thì tốc độ sẽ tăng gấp 5 lần.
 
Viết chương trình nhập từ file vào danh sách các con vật tham gia cuộc đua và tìm ra danh sách các con vật về đích:
 - Đầu tiên nhập n (1 <= n <= 10 000) là số lượng con vật tham gia cuộc đua (mỗi loại con vật có thể tham gia nhiều con), các dòng nhập tiếp theo lần lượt là thông tin nhập của từng con vật.
 - Thông tin xuất chứa những con vật chạy được hết đoạn đường trên và xếp hạng từ cao đến thấp (dựa theo con nào về đích sớm nhất sẽ xếp hạng cao nhất). Những con vật không hoàn thành đường đua sẽ không nằm trong danh sách này. Nếu 2 con vật tới đích cùng 1 lúc thì sẽ xếp hạng theo Alphabet của mã số.
 
Áp dụng struct để giải quyết những việc sau:
 - Xây dựng trò chơi có các chức năng sau:
  a. Xây dựng các struct và đọc thông tin các con vật từ file theo mẫu nhập bên dưới:
	6
	L001 50 1 => Đến đích lúc 11:06
	R001 70 0 => Đến đích lúc 11:00
	T001 10 1 => Đến đích lúc 9:42
	T002 15 0 => Đến đích lúc 16:00 => Không có trong danh sách
	T003 20 1 => Đến đích lúc 8:21
	R003 35 0 => Đến đích lúc 14:00 => Không có trong danh sách
  b. Viết các hàm xử lý tìm ra những con vật về đích và sắp xếp chúng. VD: Xử lý của các con vật trên thì kết quả là:
	4
	1. T003 20 1
	2. T001 10 1
	3. R001 70 0
	4. L001 50 1
 - Lưu ý:
  + Các hàm phải được chú thích rõ ràng.
  + Phải dùng con trỏ hoặc vector.
* DEADLINE: 1 tuan.
*/
/*
INPUT:
12
L001 50 1
R001 70 0
T001 10 1
T002 15 0
T003 20 1
R003 35 0
T004 60 0
R004 100 0
R005 65 1
L004 40 1
L005 120 0
T005 200 0
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
 
typedef struct animal ANM; // lưu thông tin 1 con vật
typedef struct animals ANMS; // lưu thông tin nhiều con vật
void ReadFile(std::ifstream &, ANMS *); // đọc thông tin các con vật từ file cho trước
void WriteFile(std::ofstream &, ANMS *); // ghi thông tin các con vật xuống file
double RaceResult(ANM, char); // trả về thời gian hoàn thành cuộc đua của 1 con vật
void SortRank(ANMS *); // sắp xếp lại thứ tự các con vật theo mức độ con nào tới đích sớm nhất
std::ostream& operator << (std::ostream&, ANM); // định nghĩa toán tử xuất thông tin cho 1 con vật
 
struct animal {
	std::string m_code; // mã số con vật
	int m_speed, m_equipment; // tốc độ và trang bị (0 hoặc 1) con vật
};
 
struct animals {
	int n_animals; // số lượng con vật tham gia
	ANM *_animals; // mảng thông tin con vật
};
 
std::ostream& operator << (std::ostream& os, ANM animal)
{
	os << animal.m_code << " " << animal.m_speed << " " << animal.m_equipment;
	return os;
}
 
void ReadFile(std::ifstream &FileIn, ANMS *a)
{
	FileIn >> a->n_animals;
	a->_animals = new ANM[a->n_animals];
	for (int i = 0; i < a->n_animals; ++i)
	{
		FileIn >> a->_animals[i].m_code >> a->_animals[i].m_speed >> a->_animals[i].m_equipment;
	}
}
 
double RaceResult(ANM animal, char type)
{
	if (type == 'L') // sư tử
	{
		if (animal.m_equipment == 1) // có trang bị
		{
			double time = 210.0 / (animal.m_speed * 2);
			return 9 + time;
		}
		else if (animal.m_equipment == 0) // không trang bị
		{
			double time = 210.0 / animal.m_speed;
			return 9 + time;
		}
	}
	else if (type == 'R') // thỏ
	{
		if (animal.m_equipment == 1) // có trang bị
		{
			double time = 210.0 / (animal.m_speed + 30);
			return 8 + time;
		}
		else if (animal.m_equipment == 0) // không trang bị
		{
			double time = 210.0 / animal.m_speed;
			return 8 + time;
		}
	}
	else if (type == 'T') // rùa
	{
		if (animal.m_equipment == 1) // có trang bị
		{
			double time = 135.0 / (animal.m_speed * 5);
			return 7 + time;
		}
		else if (animal.m_equipment == 0) // không trang bị
		{
			double time = 135.0 / animal.m_speed;
			return 7 + time;
		}
	}
	return 0.0;
}
 
void SortRank(ANMS *a)
{
	for (int i = 0; i < a->n_animals - 1; ++i)
	{
		for (int j = i + 1; j < a->n_animals; ++j)
		{
			if (RaceResult(a->_animals[i], a->_animals[i].m_code.at(0)) > RaceResult(a->_animals[j], a->_animals[j].m_code.at(0)))
				std::swap(a->_animals[i], a->_animals[j]);
		}
	}
}
 
void WriteFile(std::ofstream &FileOut, ANMS *a)
{
	int c = 0;
	FileOut << "sss" << std::endl; // something you like
	for (int i = 0; i < a->n_animals; ++i)
	{
		if (RaceResult(a->_animals[i], a->_animals[i].m_code.at(0)) <= 12)
		{
			FileOut << ++c << ". " << a->_animals[i] << std::endl;
		}
	}
	FileOut.seekp(0, std::ios::beg);
	FileOut << c << std::endl;
}
 
int main()
{
	ANMS *a = new ANMS;
 
	std::ifstream FileIn("INPUT.txt");
	ReadFile(FileIn, a);
	FileIn.close();
 
	SortRank(a);
 
	std::ofstream FileOut("OUTPUT.txt");
	WriteFile(FileOut, a);
	FileOut.close();
	system("pause");
	return 0;
}