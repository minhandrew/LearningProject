/*
Code written by Minh Andrew
If you run this code by g++ on Linux, type this command: g++ -std=c++11 *.cpp -o main -Wall && ./main
*/
/*
	KÝ PHÁP NGHỊCH ĐẢO BA LAN (REVERSE POLISH NOTATION)
I. Chuẩn bị:
 1. Hàm trả về độ ưu tiên của các toán tử (GetPriority)
 2. Hàm chuẩn hóa chuỗi (xóa hết các khoảng trắng) (DeleteSpace)
 3. Hàm phân biệt toán tử, toán hạng và ký tự mở ngoặc & đóng ngoặc (operatorType)
 4. Hàm xử lý (gồm mảng Output và Stack)
II. Chuyển đổi biểu thức trung tố sang hậu tố: Quy tắc
 1. Nếu là toán hạng, ta add vào mảng Output.
 2. Nếu là toán tử:
  a) Thực hiện vòng lặp kiểm tra, nếu toán tử ở đỉnh stqck có độ ưu tiên >= toán tử hiện tại thì ta Pop toán
  tử đó ra khỏi Stack và Push vào mảng Output
  b) Push toán tử hiện tại vào Stack
 3. Nếu là ký tử mở ngoặc, push vào stack.
 4. Nếu là ký tự đóng ngoặc, ta Pop các phần tử trong Stack vào mảng Output cho đến khi gặp ký tự mở ngoặc
 (nhớ là phải Pop luôn ký tự mở ngoặc đó nhưng không push vào mảng Output)
 5. Hoàn tất vòng lặp, nếu trong stack vẫn còn phần tử thì ra lần lượt Pop các phần tử đó ra khỏi stack và
 Push vào mảng Output.
 6. Mảng Output chính là biểu thức hậu tố thu được.
III. Tính toán dựa trên biểu thức hậu tố: Dùng vòng lặp duyệt mảng Output vừa tìm được
 1. Nếu gặp toán hạng, Pop toán hạng đó khỏi Output và push vào Stack.
 2. Nếu gặp toán tử, ta Pop 2 toán hạng khỏi Stack và tính toán dựa trên toán tử (nhớ là đúng thứ tự) và push
 lại vào Stack.
 3. Kết thúc vòng lặp, phần tử duy nhất trong Stack chính là kết quả.
*/
 
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
 
enum OperatorType { OPERAND, PARENTHESES, OPERATOR }; // toán hạng, cặp ngoặc và toán tử
int getPriority(char); // trả về độ ưu tiên của các toán tử
void DeleteSpace(std::string &); // xóa hết khoảng trắng trong chuỗi
OperatorType operatorType(char); // phân biệt toán tử, toán hạng với cặp ngoặc
std::vector<std::string> ConvertToPostfix(std::string); // chuyển biểu thức trung tố sang hậu tố
double Calculate(std::string); // tính toán kết quả dựa trên biểu thức hậu tố
 
int main()
{ // INPUT.txt : (13 + (25 * 7 - 6 / 3) / (18^3 + 65 * 8 / 4) + 69)^2
	std::fstream FileIn("INPUT.txt", std::ios::in);
	std::string str;
	std::getline(FileIn, str);
	double result = Calculate(str);
	std::cout << str << " = " << result << std::endl;
	FileIn.close(); // Lưu ý là hàm hủy (destructor) lớp fstream trong C++ tự động close giùm.
	system("pause");
	return 0;
}
std::vector<std::string> ConvertToPostfix(std::string str)
{
	DeleteSpace(str); // xóa hết các khoảng trắng
	std::vector<std::string> Output; // Lưu biểu thức hậu tố
	std::stack<char> Stack; // Lưu các toán tử và cặp ngoặc
	std::string number; // Lưu toán hạng
	int length = str.length();
	for (int i = 0; i < length; ++i) {
		char character = str[i];
		if (operatorType(character) == OPERAND)
			number.push_back(character);
		else {
			if (number.length() > 0) {
				Output.push_back(number); // Lưu toán hạng vào mảng Output
				number.clear(); // reset lại string number
			}
			if (operatorType(character) == PARENTHESES) {
				if (character == '(')
					Stack.push(character); // Lưu ký tự mở ngoặc vào Stack
				else if (character == ')') {
					while (Stack.top() != '(') {
						Output.push_back(std::string(1, Stack.top())); // Đây gọi là fill constructor
						//Output.emplace_back(1, Stack.top()); // Công dụng giống trên và thuộc C++11
						Stack.pop();
					}
					Stack.pop();
				}
			}
			if (operatorType(character) == OPERATOR) {
				// Nếu stack vẫn "đặc" và toán tử tại đỉnh Stack có độ ưu tiên lớn hơn toán tử đang xét
				while (!Stack.empty() && getPriority(Stack.top()) >= getPriority(character)) {
					Output.push_back(std::string(1, Stack.top())); // Đây gọi là fill constructor
					//Output.emplace_back(1, Stack.top()); // Công dụng giống trên và thuộc C++11
					Stack.pop();
				}
				Stack.push(character);
			}
		}
	}
	// Nếu string number vẫn "đặc"
	if (!number.empty()) {
		Output.push_back(number);
		number.clear();
	}
	// Nếu trong Stack vẫn còn thì Pop ra và Push vào mảng Output
	while (!Stack.empty()) {
		Output.push_back(std::string(1, Stack.top())); // Đây gọi là fill constructor
		//Output.emplace_back(1, Stack.top()); // Công dụng giống trên và thuộc C++11
		Stack.pop();
	}
	return Output;
}
double Calculate(std::string str)
{
	std::vector<std::string> Output = ConvertToPostfix(str);
	std::stack<std::string> Stack;
	int size = Output.size();
	for (int i = 0; i < size; ++i) {
		// Nếu là toán hạng
		if (operatorType(Output[i][0]) == OPERAND) {
			Stack.push(Output[i]);
			Output.erase(Output.begin() + i); // Pop toán hạng đó ra khỏi mảng Output
			--size; // update lại size
			--i;
		}
		else if (operatorType(Output[i][0]) == OPERATOR) {
			char _char = Output[i][0];
			double operand2 = std::stof(Stack.top()); // convert string sang float
			Stack.pop();
			double operand1 = std::stof(Stack.top()); // convert string sang float
			Stack.pop();
			if (_char == '+')
				Stack.push(std::to_string(operand1 + operand2)); // convert float sang string
			else if (_char == '-')
				Stack.push(std::to_string(operand1 - operand2)); // convert float sang string
			else if (_char == '*')
				Stack.push(std::to_string(operand1 * operand2)); // convert float sang string
			else if (_char == '/')
				Stack.push(std::to_string(operand1 / operand2)); // convert float sang string
			else if (_char == '^')
				Stack.push(std::to_string(powf(operand1, operand2))); // convert float sang string
		}
	}
	return std::stof(Stack.top());
}
int getPriority(char ope)
{
	if (ope == '^')
		return 3; // dấu mũ
	else if (ope == '*' || ope == '/')
		return 2; // dấu nhân hoặc chia
	else if (ope == '+' || ope == '-')
		return 1; // dấu cộng hoặc trừ
	else
		return 0;
}
void DeleteSpace(std::string &str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // dịch các khoảng trắng về cuối chuỗi và xóa
}
OperatorType operatorType(char ope)
{
	if (getPriority(ope) == 0) {
		if (ope != '(' && ope != ')')
			return OPERAND;
		else
			return PARENTHESES;
	}
	return OPERATOR;
}