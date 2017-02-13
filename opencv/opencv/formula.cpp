/*
#include<cstdarg>
#include<iostream>
using namespace std;

int size(const variable* para) {
return sizeof para / sizeof(variable);
}
*/

/*
variable* extend(variable* value, char add_name) {
int orig = size(value);
variable* val_return = new variable[orig + 1];

for (int i = 0; i < orig; i++)
val_return[i].name = value[i].name;

delete[] value;
val_return[orig].name = add_name;

return val_return;
}

struct variable {
	char name;
	double sum = 0;
};
union str_module {
	char sym;
	double sum = NULL;
};

void clear(str_module str[]);
int str_size(const char& para[]);
bool unequal(const char&, variable serh[], const int&);
double equal(const char&, variable serh[]);
double power(double, double);
double formula(char str[], variable value[]);
*/

/*
double formula(char str[], ...) {
	int count = 0;
	const int size = str_size(str)-1;
	variable value[size/2+1];
	for (int i = 0; i < size; i++) {
		if (((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) && unequal(str[i], value, count)){
				value[count].name = str[i];
				count++;
		}
	}
	va_list ptr;
	va_start(ptr, str);
	for (int i = 0; i < count; i++)
		value[i].sum = va_arg(ptr, double);

//數學式計算處理
//第一步為搜索並遞迴括弧+方程式數值化

	str_module strA[size];
	for (int i = 0, j = 0, k = 0, bracket = 0, bool tpswh = false, char inner_str[size - 2]; i < size; i++) {
		if (bracket != 0)
			if (str[i] != ')') {
				inner_str[j] = str[i];
				j++;
			}
			else {
				strA[k].sum = formula(inner_str, j, value);
				k++;
			}
		else {
			j = 0;
			if (str[i] <= '0' && str[i] >= '9') {
				strA[k].sum = strA[k].sum * 10 + (str[i] - '0');
				tpswh = true;
			}
			else if (tpswh == true) {
				k++;
				tpswh = false;
			}else if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
				strA[k].sum = equal(str[i], value);
				k++;
			}else {
				switch (str[i]) {
				case '(':
					bracket++;
					break;
				case ')':
					bracket--;
					break;
				default:
					strA[k].sym = str[i];
					k++;
				}
			}
		}
	}
	
	//第二步為左搜索合併次方
	
	str_module strB[size];
	count = 0;
	for (; strA[count].sum != NULL; count++);
	count--;
	for (int i = 0, j = 0; i <= count; i++) {
		if (strA[count - i].sum == '^') {
			strB[j - 1] = power(strA[count - i - 1], strB[j - 1]);
			i++;
		}
		else {
			strB[j] = strA[count - i];
			j++;
		}
	}
	
	clear(strA);
	count = 0;
	
	//第三步為右搜索合併乘除  式子逆向閱讀
	
	for (; strB[count].sum != NULL; count++);
	count--;
	for (int i = 0, j = 0; i <= count; i++) {
		switch (strB[count - i].sum) {
			case '*' :
				strA[j - 1].sum *= strB[count - i - 1].sum;
				i++;
				break;
			case '/' :
				strA[j - 1].sum /= strB[count - i - 1].sum;
				i++;
				break;
			default :
				strA[j] = strB[count - i];
				j++;
		}
	}
	
	//第四為右搜索合併加減  請注意  此時的式子strA為順向閱讀 
	
	double result = 0;
	if (strA[0].sum != '-')
		result = strA[0];
	for (int i = 0; strA[i].sum != NULL; i++) {
		switch (strA[i].sum) {
		case '+':
			result += strA[i + 1];
			i++;
			break;
		case '-':
			result -= strA[i + 1];
			i++;
		}
	}
	return result;
}
*/

/*
void clear(str_module str[]) {
	for (int i = 0; i < str_size(str); i++) {
		str[i].sum = NULL;
	}
}
int str_size(const char& para[]) {
	int i = 0;
	for (auto j : para)
		i++;
	return i;
}
bool unequal(const char& elm, variable serh[], const int& count) {
	int i = 0;
	for (; (i < count) && (serh[i].name != elm); i++);
	return i == count;
}
double equal(const char& elm, variable serh[]) {
	int i = 0;
	for (; serh[i].name != elm; i++);
	return serh[i].sum;
}
double power(double P, double p) {         //暫時
	double w = 0;
	int n = 0;
	int a = 0;
	double x = 0;
	for (int h = 0; h < 1000; h++, x = w) {
		w = 0;
		for (int i = 1,double j = x; i < n; i++, w = i == n ? x*j - a : 0)
			x *= j;
		w /= x * n;
	}
	return 0;
}
double formula(char str[], variable value[]) {
	int count = 0;
	const int size = str_size(str) - 1;
	str_module strA[size];
	for (int i = 0, j = 0, k = 0, bracket = 0, bool tpswh = false, char inner_str[size - 2]; i < size; i++) {
		if (bracket != 0)
			if (str[i] != ')') {
				inner_str[j] = str[i];
				j++;
			}
			else {
				strA[k].sum = formula(inner_str, j, value);
				k++;
			}
		else {
			j = 0;
			if (str[i] <= '0' && str[i] >= '9') {
				strA[k].sum = strA[k].sum * 10 + (str[i] - '0');
				tpswh = true;
			}
			else if (tpswh == true) {
				k++;
				tpswh = false;
			}
			else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
				strA[k].sum = equal(str[i], value);
				k++;
			}
			else {
				switch (str[i]) {
				case '(':
					bracket++;
					break;
				case ')':
					bracket--;
					break;
				default:
					strA[k].sym = str[i];
					k++;
				}
			}
		}
	}
	str_module strB[size];
	int k = 0;

	for (; strA[k].sum != NULL; k++);
	k--;
	for (int i = 0, j = 0; i <= k; i++) {
		if (strA[k - i].sum == '^') {
			strB[j - 1] = power(strA[k - i - 1], strB[j - 1]);
			i++;
		}
		else {
			strB[j] = strA[k - i];
			j++;
		}
	}

	clear(strA);
	k = 0;

	for (; strB[k].sum != NULL; k++);
	k--;
	for (int i = 0, j = 0; i <= k; i++) {
		switch (strB[k - i].sum) {
		case '*':
			strA[j - 1].sum *= strB[k - i - 1].sum;
			i++;
			break;
		case '/':
			strA[j - 1].sum /= strB[k - i - 1].sum;
			i++;
			break;
		default:
			strA[j] = strB[k - i];
			j++;
		}
	}

	double result = 0;
	if (strA[0].sum != '-')
		result = strA[0];
	for (int i = 0; strA[i].sum != NULL; i++) {
		switch (strA[i].sum) {
		case '+':
			result += strA[i + 1];
			i++;
			break;
		case '-':
			result -= strA[i + 1];
			i++;
		}
	}
	return result;
}
*/