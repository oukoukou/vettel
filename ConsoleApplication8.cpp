#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>

void getDoubleValue(char* listX, char* listY)
{
	std::string strX(listX);
	std::string strY(listY);
	std::stringstream ssX(strX);
	std::stringstream ssY(strY);

	std::string tmp;
	std::vector<double> xValues;
	std::vector<double> yValues;

	while (std::getline(ssX, tmp, ',')) {
		xValues.push_back(std::stod(tmp));
	}
	while (std::getline(ssY, tmp, ',')) {
		yValues.push_back(std::stod(tmp));
	}
	if (xValues.size() != yValues.size()) {
		std::cout << "param error!" << std::endl;
		return;
	}

	int iPointNum = yValues.size();
	double* arrX = new double[iPointNum];
	double* arrY = new double[iPointNum];
	double* pRetValue = (double*)malloc(sizeof(double) * iPointNum);

	int idX(0);
	for (const auto& value : xValues) {
		arrX[idX++] = value;
	}
	idX = 0;
	for (const auto& value : yValues) {
		arrY[idX++] = value;
	}

}
int *GetNum(char *str, int *count)
{
	int i = 0, j = 0, flag = 1, len = strlen(str);
	int *num = (int *)calloc(len, 4);
	num[0] = 0;
	if (isdigit(str[len - 1]) == 0)
		flag = 0;
	while (len--)					//倒序提取数字
	{
		if (isdigit(str[len]) != 0)
		{
			num[j] = num[j] + ((int)str[len] - 48)*((int)pow(10, i));
			i++;
		}
		else if ((len > 0) && (isdigit(str[len]) == 0) && (isdigit(str[len - 1]) != 0))
		{
			if (flag > 0)
			{
				i = 0;
				j++;
				num[j] = 0;
			}
			flag = 1;
		}
	}
	flag = 0;
	*count = j + 1;					//数字数量
	while (j > flag)					//顺序反转
	{
		i = num[j];
		num[j] = num[flag];
		num[flag] = i;
		j--;
		flag++;
	}
	return num;
}

/*
void main()
{
	char str[100];
	int *num, count = 0;
	gets_s(str);

	getDoubleValue(str, str);
	num = GetNum(str, &count);
	printf("Input %d nmubers:\n", count);
	while (count--)
	{
		printf("%d\t", *num);
		num++;
	}
}
*/

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

volatile int counter(0); // non-atomic counter
std::mutex mtx;           // locks access to counter

void attempt_10k_increases() {
	for (int i = 0; i < 10000; ++i) {
		std::lock_guard<std::mutex> grd(mtx);
		++counter;

		//if (mtx.try_lock()) {   // only increase if currently not locked:
		//	++counter;
		//	mtx.unlock();
		//}
	}
}

int main(int argc, const char* argv[]) {
	std::thread threads[10];
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(attempt_10k_increases);

	for (auto& th : threads) th.join();
	std::cout << counter << " successful increases of the counter.\n";

	return 0;
}
