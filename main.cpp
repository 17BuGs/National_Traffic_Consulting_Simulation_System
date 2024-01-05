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
		int ex = 0;	//判断退出
		while (1) {
			ShowAccountMenu();	//显示用户登入菜单
			cin >> temp;
			getchar();
			if (temp == 1) {
				cout << "请输入密码:";
				cin.getline(str, 20);
				if (strcmp(str, "123456") != 0) cout << "密码错误！" << endl;
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
			else cout << "输入错误！" << endl;
		}
		if (account == 1) {
			int flag = 0;
			ShowAdminMenu();	//显示管理员操作菜单
			while (1) {
				cin >> ctrl;
				switch (ctrl) {
				case 1:
					ShowAdminMenu();
					break;
				case 2:
					getchar();	//读取回车
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
					cout << "请输入城市名：";
					cin.getline(str, 40);	//cin.getline()方法可以读取回车，并替换为'\0'
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
						cout << "输入始发城市名：";
						cin.getline(str, 40);
						ShowStCityTrainRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllTrainRoutes();
					}
					else cout << "输入错误！" << endl;
					break;
				case 8:
					getchar();
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "输入始发城市名：";
						cin.getline(str, 40);
						ShowStCityFlightRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllFlightRoutes();
					}
					else cout << "输入错误！" << endl;
					break;
				case 9:
					getchar();
					cout << "输入班次名称：";
					cin.getline(name, 40);
					cout << "输入始发站、终点站名称，以空格分隔：";
					cin >> stCity >> edCity;
					//ch = getchar();	//cin不能读取回车，需要getchar()读取
					cout << "输入班次花费：";
					cin >> mon;
					cout << "输入班次始发时间，格式为year month day hh mm（如2023 5 28 15 14表示2023-5-28 15:14）：";
					cin >> year1 >> month1 >> day1 >> hh1 >> mm1;
					stTime.Year = year1;
					stTime.Month = month1;
					stTime.Day = day1;
					stTime.HH = hh1;
					stTime.MM = mm1;
					cout << "输入班次到站时间，格式为year month day hh mm（如2023 5 28 15 14表示2023-5-28 15:14）：";
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
					cout << "输入班次名称：";
					cin.getline(name, 40);
					cout << "输入始发站、终点站名称，以空格分隔：";
					cin >> stCity >> edCity;
					//ch = getchar();	//cin不能读取回车，需要getchar()读取
					cout << "输入班次花费：";
					cin >> mon;
					cout << "输入班次始发时间，格式为year month day hh mm（如2023 5 28 15 14表示2023-5-28 15:14）：";
					cin >> year1 >> month1 >> day1 >> hh1 >> mm1;
					stTime.Year = year1;
					stTime.Month = month1;
					stTime.Day = day1;
					stTime.HH = hh1;
					stTime.MM = mm1;
					cout << "输入班次到站时间，格式为year month day hh mm（如2023 5 28 15 14表示2023-5-28 15:14）：";
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
					cout << "输入班次名称：";
					cin.getline(name, 40);
					DelTrainPath(name);
					break;
				case 12:
					getchar();
					cout << "输入班次名称：";
					cin.getline(name, 40);
					DelFlightPath(name);
					break;
				case 13:
					flag = 1;
					break;
				default:
					cout << "输入错误！" << endl;
					break;
				}
				if (flag) break;
				system("pause");
			}
		}
		else if (account == 2) {
			int flag = 0;
			ShowUserMenu();	//显示游客操作菜单
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
						cout << "输入始发城市名：";
						cin.getline(str, 40);
						ShowStCityTrainRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllTrainRoutes();
					}
					else cout << "输入错误！" << endl;
					break;
				case 4:
					getchar();
					ShowRoutesMenu();
					cin >> show;
					getchar();
					if (show == 1) {
						cout << "输入始发城市名：";
						cin.getline(str, 40);
						ShowStCityFlightRoutes(SeekCity(str));
					}
					else if (show == 2) {
						ShowAllFlightRoutes();
					}
					else cout << "输入错误！" << endl;
					break;
				case 5:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					TrainTimeDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 6:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					TrainMoneyDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 7:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					TrainTransTimesDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 8:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					FlightTimeDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 9:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					FlightMoneyDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 10:
					cout << "输入出发城市、目的城市名称，以空格分隔：";
					cin >> stCity >> edCity;
					if (SeekCity(stCity) < 0 || SeekCity(edCity) < 0) {
						cout << "无法找到城市" << endl;
						break;
					}
					FlightTransTimesDijkstra(SeekCity(stCity), SeekCity(edCity));
					break;
				case 11:
					flag = 1;
					break;
				default:
					cout << "输入错误！" << endl;
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
