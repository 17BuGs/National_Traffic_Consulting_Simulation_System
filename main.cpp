#include "functions.cpp"

int main() {
	ShowTitle();
	char str[40] = {}, ch;
	int temp, account = 0, ctrl, show;
	Name name[40], stCity[20], edCity[20];
	Money mon;
	Time year1, month1, day1, hh1, mm1, year2, month2, day2, hh2, mm2;
	DateTime stTime, edTime;
	while (1) {
		int ex = 0;	//�ж��˳�
		while (1) {
			ShowAccountMenu();	//��ʾ�û�����˵�
			cin >> temp;
			getchar();
			if (temp == 1) {
				cout << "����������:";
				cin.getline(str, 20);
				if (strcmp(str, "123456") != 0) cout << "�������" << endl;
				else {
					account = 1;
					break;
				}
			}
			else if (temp == 2) {
				account = 2;
				break;
			}
			else if (temp == 3) {
				ex = 1;
				break;
			}
			else cout << "�������" << endl;
		}
		if (account == 1) {
			int flag = 0;
			ShowAdminMenu();	//��ʾ����Ա�����˵�
			while (1) {
				cin >> ctrl;
				switch (ctrl) {
				case 1:
					ShowAdminMenu();
					break;
				case 2:
					getchar();	//��ȡ�س�
					ReadFile();
					break;
				case 3:
					getchar();
					SaveFile();
					break;
				case 4:
					ShowCityList();
					break;
				case 5:
					getchar();
					cout << "�������������";
					cin.getline(str, 40);	//cin.getline()�������Զ�ȡ�س������滻Ϊ'\0'
					InsertCity(str);
					break;
				case 6:
					getchar();
					cin.getline(str, 40);
					DelCity(str);
					break;
				case 7:
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "����ʼ����������";
						cin.getline(str, 40);
						ShowStCityTrainRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllTrainRoutes();
					}
					else cout << "�������" << endl;
					break;
				case 8:
					getchar();
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "����ʼ����������";
						cin.getline(str, 40);
						ShowStCityFlightRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllFlightRoutes();
					}
					else cout << "�������" << endl;
					break;
				case 9:
					getchar();
					cout << "���������ƣ�";
					cin.getline(name, 40);
					cout << "����ʼ��վ���յ�վ���ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					//ch = getchar();	//cin���ܶ�ȡ�س�����Ҫgetchar()��ȡ
					cout << "�����λ��ѣ�";
					cin >> mon;
					cout << "������ʼ��ʱ�䣬��ʽΪyear month day hh mm����2023 5 28 15 14��ʾ2023-5-28 15:14����";
					cin >> year1 >> month1 >> day1 >> hh1 >> mm1;
					stTime.Year = year1;
					stTime.Month = month1;
					stTime.Day = day1;
					stTime.HH = hh1;
					stTime.MM = mm1;
					cout << "�����ε�վʱ�䣬��ʽΪyear month day hh mm����2023 5 28 15 14��ʾ2023-5-28 15:14����";
					cin >> year2 >> month2 >> day2 >> hh2 >> mm2;
					edTime.Year = year2;
					edTime.Month = month2;
					edTime.Day = day2;
					edTime.HH = hh2;
					edTime.MM = mm2;
					InsertTrainRoute(name, stCity, edCity, mon, stTime, edTime);
					break;
				case 10:
					getchar();
					cout << "���������ƣ�";
					cin.getline(name, 40);
					cout << "����ʼ��վ���յ�վ���ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					//ch = getchar();	//cin���ܶ�ȡ�س�����Ҫgetchar()��ȡ
					cout << "�����λ��ѣ�";
					cin >> mon;
					cout << "������ʼ��ʱ�䣬��ʽΪyear month day hh mm����2023 5 28 15 14��ʾ2023-5-28 15:14����";
					cin >> year1 >> month1 >> day1 >> hh1 >> mm1;
					stTime.Year = year1;
					stTime.Month = month1;
					stTime.Day = day1;
					stTime.HH = hh1;
					stTime.MM = mm1;
					cout << "�����ε�վʱ�䣬��ʽΪyear month day hh mm����2023 5 28 15 14��ʾ2023-5-28 15:14����";
					cin >> year2 >> month2 >> day2 >> hh2 >> mm2;
					edTime.Year = year2;
					edTime.Month = month2;
					edTime.Day = day2;
					edTime.HH = hh2;
					edTime.MM = mm2;
					InsertFlightRoute(name, stCity, edCity, mon, stTime, edTime);
					break;
				case 11:
					getchar();
					cout << "���������ƣ�";
					cin.getline(name, 40);
					DelTrainPath(name);
					break;
				case 12:
					getchar();
					cout << "���������ƣ�";
					cin.getline(name, 40);
					DelFlightPath(name);
					break;
				case 13:
					flag = 1;
					break;
				default:
					cout << "�������" << endl;
					break;
				}
				if (flag) break;
				system("pause");
			}
		}
		else if (account == 2) {
			int flag = 0;
			ShowUserMenu();	//��ʾ�οͲ����˵�
			while (1) {
				cin >> ctrl;
				switch (ctrl) {
				case 1:
					ShowUserMenu();
					break;
				case 2:
					ShowCityList();
					break;
				case 3:
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "����ʼ����������";
						cin.getline(str, 40);
						ShowStCityTrainRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllTrainRoutes();
					}
					else cout << "�������" << endl;
					break;
				case 4:
					getchar();
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "����ʼ����������";
						cin.getline(str, 40);
						ShowStCityFlightRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllFlightRoutes();
					}
					else cout << "�������" << endl;
					break;
				case 5:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					TrainTimeDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 6:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					TrainMoneyDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 7:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					TrainTransTimesDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 8:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					FlightTimeDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 9:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					FlightMoneyDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 10:
					cout << "����������С�Ŀ�ĳ������ƣ��Կո�ָ���";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "�޷��ҵ�����" << endl;
						break;
					}
					FlightTransTimesDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 11:
					flag = 1;
					break;
				default:
					cout << "�������" << endl;
					break;
				}
				if (flag) break;
				system("pause");
			}
		}
		else if (ex) break;
	}
	return 0;
}
