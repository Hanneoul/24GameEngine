#include <iostream>

using namespace std;

int main()
{
	int num = 0;
	string name;
	while (num != 9999)
	{
		cout << "게임이 실행됐습니다" << endl;
		cout << "내가 싫어하는 숫자를 써봐 : ";
		cin >> name >> num;
		cout << name << " 왜그러니..." << endl;
	}

	cout << "9999맞아 잘했어... 그럼 이제 9999대 맞자" << endl;

	return 0;
}