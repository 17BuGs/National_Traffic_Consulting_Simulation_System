#include "traffic.h"

bool JudgeTimeFront(DateTime time1, DateTime time2) {
	if (time1.Year < time2.Year) return 1;
	else if (time1.Year == time2.Year && time1.Month < time2.Month) return 1;
	else if (time1.Year == time2.Year && time1.Month == time2.Month && time1.Day < time2.Day) return 1;
	else if (time1.Year == time2.Year && time1.Month == time2.Month && time1.Day == time2.Day && time1.HH < time2.HH)
		return 1;
	else if (time1.Year == time2.Year && time1.Month == time2.Month && time1.Day == time2.Day && time1.HH == time2.HH
		&& time1.MM < time2.MM) return 1;
	else return 0;
}
Time CalTime(DateTime stTime, DateTime edTime) {
	int i, j, k, p, q, month1, month2, day1, day2, hh1, hh2, mm1, mm2, sum = 0;
	int a[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };	//数组中第一个元素直接赋值为0，与月份相对应
	for (i = stTime.Year; i <= edTime.Year; i++) {
		if (i == stTime.Year) month1 = stTime.Month;
		else month1 = 1;   //当年份自增后  月份开始赋值为1（除起始年份和目标年份外）
		if (i == edTime.Year) month2 = edTime.Month;
		else month2 = 12;
		for (j = month1; j <= month2; j++) {	  //计算相应的月份差
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) a[2] = 29;	//判断是否为闰年，若为闰年将二月份重新赋值为29天
			else a[2] = 28;
			if (i == stTime.Year && j == stTime.Month) day1 = stTime.Day;
			else day1 = 1;
			if (i == edTime.Year && j == edTime.Month) day2 = edTime.Day;
			else day2 = a[j];
			for (k = day1; k <= day2; k++) {
				if (i == stTime.Year && j == stTime.Month && k == stTime.Day) hh1 = stTime.HH;
				else hh1 = 0;
				if (i == edTime.Year && j == edTime.Month && k == edTime.Day) hh2 = edTime.HH;
				else hh2 = 23;
				for (p = hh1; p <= hh2; p++) {
					if (i == stTime.Year && j == stTime.Month && k == stTime.Day && p == stTime.HH) mm1 = stTime.MM;
					else mm1 = 0;
					if (i == edTime.Year && j == edTime.Month && k == edTime.Day && p == edTime.HH) mm2 = edTime.MM;
					else mm2 = 59;
					for (q = mm1; q <= mm2; q++) {
						sum++;
					}
				}
			}
		}
	}
	return sum - 1;   //返回值是两个日期相差的分钟数
}
State ShowCityList() {
	if (cityNum == 0) {
		cout << "暂无城市信息" << endl;
		return OK;
	}
	cout << "------------------------------------------------" << endl;
	for (int i = 0; i <= cityNum - 1; i++)
		cout << i << ' ' << cityNames[i] << endl;
	cout << "------------------------------------------------" << endl;
	return OK;
}

CityNode SeekCity(char* city) {
	short int i;
	for (i = 0; i <= MaxCityNum - 1; i++) {
		if (strcmp(city, cityNames[i]) == 0) return i;
	}
	return -1;
}

State SaveFile() {
	FILE* file;	//用于写入文件
	RouteUnit* currRoute = NULL;
	cout << "打开文件city.txt..." << endl;
	if ((fopen_s(&file, "city.txt", "w")) != 0) {
		cout << "无法打开city.txt！" << endl;
		return ERROR;
	}
	cout << "存储城市数量信息..." << endl;
	fprintf(file, "%d\n", cityNum);
	cout << "存储城市名称..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fprintf(file, "%s\n", cityNames[i]);
	}
	fclose(file);

	cout << "打开文件train.txt..." << endl;
	if ((fopen_s(&file, "train.txt", "w")) != 0) {
		cout << "无法打开train.txt！" << endl;
		return ERROR;
	}
	cout << "存储火车班次数量..." << endl;
	int trainRouteNum = 0;
	for (int i = 0; i <= cityNum - 1; i++) {
		trainRouteNum = cityGraph.adjlist[i].trainRouteNum;
		fprintf(file, "%d\n", trainRouteNum);
	}
	cout << "存储火车班次信息..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstTrainRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
			//火车班次名称，始发站，终点站，始发时间（stYear, stMonth, stDay, stHH, stMM），到站时间（同上），费用
			fprintf(file, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n", 
				currRoute->routeName, cityNames[i], cityNames[currRoute->endCity],
				currRoute->startTime.Year, currRoute->startTime.Month, currRoute->startTime.Day, currRoute->startTime.HH, currRoute->startTime.MM,
				currRoute->endTime.Year, currRoute->endTime.Month, currRoute->endTime.Day, currRoute->endTime.HH, currRoute->endTime.MM,
				currRoute->cost);
		}
	}
	fclose(file);

	cout << "打开文件flight.txt..." << endl;
	if ((fopen_s(&file, "flight.txt", "w")) != 0) {
		cout << "无法打开flight.txt！" << endl;
		return ERROR;
	}
	cout << "存储航班数量..." << endl;
	int flightRouteNum = 0;
	for (int i = 0; i <= cityNum - 1; i++) {
		flightRouteNum = cityGraph.adjlist[i].flightRouteNum;
		fprintf(file, "%d\n", flightRouteNum);
	}
	cout << "存储航班信息..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstFlightRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
			//火车班次名称，始发站，终点站，始发时间（stYear, stMonth, stDay, stHH, stMM），到站时间（同上），费用
			fprintf(file, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n",
				currRoute->routeName, cityNames[i], cityNames[currRoute->endCity],
				currRoute->startTime.Year, currRoute->startTime.Month, currRoute->startTime.Day, currRoute->startTime.HH, currRoute->startTime.MM,
				currRoute->endTime.Year, currRoute->endTime.Month, currRoute->endTime.Day, currRoute->endTime.HH, currRoute->endTime.MM,
				currRoute->cost);
		}
	}
	fclose(file);
	return OK;
}

State ReadFile() {
	FILE* file;	//用于写入文件
	RouteUnit* currRoute = NULL;
	char* find = NULL;	//用于找到文件输入流中的'\n'
	cout << "打开文件city.txt..." << endl;
	if ((fopen_s(&file, "city.txt", "r")) != 0) {
		cout << "无法打开city.txt！" << endl;
		return ERROR;
	}
	cout << "读取城市数量信息..." << endl;
	char cont[MaxFileLineReadLength];
	fgets(cont, sizeof(cont), file);
	find = strchr(cont, '\n');
	if (find) *find = '\0';	//替换读取到的'\n'为'\0'
	cityNum = atoi(cont);
	cout << "读取城市名称..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//替换读取到的'\n'为'\0'
		strcpy_s(cityNames[i], cont);
	}
	fclose(file);
	DestoryGraph();
	cout << "打开文件train.txt..." << endl;
	if ((fopen_s(&file, "train.txt", "r")) != 0) {
		cout << "无法打开train.txt！" << endl;
		return ERROR;
	}
	cout << "读取火车班次数量..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//替换读取到的'\n'为'\0'
		cityGraph.adjlist[i].trainRouteNum = atoi(cont);
	}
	cout << "读取火车班次信息..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (int j = 0; j <= cityGraph.adjlist[i].trainRouteNum - 1; j++) {
			if (cityGraph.adjlist[i].firstTrainRoute == NULL) {
				cityGraph.adjlist[i].firstTrainRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
				currRoute = cityGraph.adjlist[i].firstTrainRoute;
				currRoute->nextRoute = NULL;
			}
			else {
				currRoute = cityGraph.adjlist[i].firstTrainRoute;
				cityGraph.adjlist[i].firstTrainRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
				cityGraph.adjlist[i].firstTrainRoute->nextRoute = currRoute;
			}
			fgets(cont, sizeof(cont), file);	//读取火车班次名称
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			strcpy_s(cityGraph.adjlist[i].firstTrainRoute->routeName, cont);
			fgets(cont, sizeof(cont), file);	//读取始发站
			fgets(cont, sizeof(cont), file);	//读取终点站
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endCity = SeekCity(cont);

			//读取始发时间
			fgets(cont, sizeof(cont), file);	//年
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//月
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//日
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//时
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//分
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.MM = atoi(cont);

			//读取到站时间
			fgets(cont, sizeof(cont), file);	//年
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//月
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//日
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//时
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//分
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.MM = atoi(cont);

			fgets(cont, sizeof(cont), file);	//读取费用
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstTrainRoute->cost = atof(cont);
		}
	}
	fclose(file);
	cout << "打开文件flight.txt..." << endl;
	if ((fopen_s(&file, "flight.txt", "r")) != 0) {
		cout << "无法打开flight.txt！" << endl;
		return ERROR;
	}
	cout << "读取航班数量..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//替换读取到的'\n'为'\0'
		cityGraph.adjlist[i].flightRouteNum = atoi(cont);
	}
	cout << "读取航班信息..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (int j = 0; j <= cityGraph.adjlist[i].flightRouteNum - 1; j++) {
			if (cityGraph.adjlist[i].firstFlightRoute == NULL) {
				cityGraph.adjlist[i].firstFlightRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
				currRoute = cityGraph.adjlist[i].firstFlightRoute;
				currRoute->nextRoute = NULL;
			}
			else {
				currRoute = cityGraph.adjlist[i].firstFlightRoute;
				cityGraph.adjlist[i].firstFlightRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
				cityGraph.adjlist[i].firstFlightRoute->nextRoute = currRoute;
			}
			fgets(cont, sizeof(cont), file);	//读取火车班次名称
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			strcpy_s(cityGraph.adjlist[i].firstFlightRoute->routeName, cont);
			fgets(cont, sizeof(cont), file);	//读取始发站
			fgets(cont, sizeof(cont), file);	//读取终点站
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endCity = SeekCity(cont);

			//读取始发时间
			fgets(cont, sizeof(cont), file);	//年
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//月
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//日
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//时
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//分
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.MM = atoi(cont);

			//读取到站时间
			fgets(cont, sizeof(cont), file);	//年
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//月
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//日
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//时
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//分
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.MM = atoi(cont);

			fgets(cont, sizeof(cont), file);	//读取费用
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//替换读取到的'\n'为'\0'
			cityGraph.adjlist[i].firstFlightRoute->cost = atof(cont);
		}
	}
	fclose(file);
	return OK;
}

State DestoryGraph() {
		for (int i = 0; i <= MaxCityNum - 1; i++){
			if (RouteUnit* pre = cityGraph.adjlist[i].firstTrainRoute){
				RouteUnit* p = pre->nextRoute;
				while (p){
					free(pre);
					pre = p;
					p = p->nextRoute;
				}
				free(pre);
			}
			cityGraph.adjlist[i].firstTrainRoute = NULL;
			cityGraph.adjlist[i].trainRouteNum = 0;
		}
		for (int i = 0; i <= MaxCityNum - 1; i++) {
			if (RouteUnit* pre = cityGraph.adjlist[i].firstFlightRoute) {
				RouteUnit* p = pre->nextRoute;
				while (p) {
					free(pre);
					pre = p;
					p = p->nextRoute;
				}
				free(pre);
			}
			cityGraph.adjlist[i].firstFlightRoute = NULL;
			cityGraph.adjlist[i].flightRouteNum = 0;
		}
		return OK;
}

State InsertCity(Name* name) {
	if (SeekCity(name) == -1) {
		strcpy_s(cityNames[cityNum], name);
		//cityGraph.adjlist[cityNum].city = cityNum;
		cityGraph.adjlist[cityNum].trainRouteNum = 0;
		cityGraph.adjlist[cityNum].flightRouteNum = 0;
		cityNum++;
		return OK;
	}
	else {
		cout << "该城市已存在！" << endl;
		return ERROR;
	}
}

State DelCity(Name* name) {
	CityNode city = SeekCity(name);
	if (city == -1) {
		cout << "该城市不存在！" << endl;
		return ERROR;
	}
	RouteUnit* currRoute = NULL, * neRoute = NULL, * temp = NULL;
	for (int i = 0; i <= cityNum - 1; i++) {
		if (strcmp(cityNames[i], name) == 0) {	//释放邻接表中以该城市为出边的所有路线
			currRoute = cityGraph.adjlist[i].firstTrainRoute;	//删除所有火车路线
			if (currRoute != NULL) {
				neRoute = currRoute->nextRoute;
				while (neRoute != NULL) {
					free(currRoute);
					cityGraph.adjlist[i].trainRouteNum--;
					currRoute = neRoute;
					neRoute = neRoute->nextRoute;
				}
				free(currRoute);
				currRoute = NULL;
				cityGraph.adjlist[i].trainRouteNum = 0;
				cityGraph.adjlist[i].firstTrainRoute = NULL;
			}
			currRoute = cityGraph.adjlist[i].firstFlightRoute;	//删除所有飞机路线
			if (currRoute != NULL) {
				neRoute = currRoute->nextRoute;
				while (neRoute != NULL) {
					free(currRoute);
					cityGraph.adjlist[i].flightRouteNum--;
					currRoute = neRoute;
					neRoute = neRoute->nextRoute;
				}
				free(currRoute);
				currRoute = NULL;
				cityGraph.adjlist[i].flightRouteNum = 0;
				cityGraph.adjlist[i].firstFlightRoute = NULL;
			}
		}
		else {	//释放邻接表中以该城市为入边的所有路线
			currRoute = cityGraph.adjlist[i].firstTrainRoute;	//删除火车路线
			if (currRoute != NULL) {
				neRoute = currRoute->nextRoute;
				for (; neRoute != NULL; ) {
					if (neRoute->endCity == city) {
						temp = neRoute->nextRoute;
						free(neRoute);
						neRoute = temp;
						temp = NULL;
						cityGraph.adjlist[i].trainRouteNum--;
						if (neRoute == NULL) break;
					}
					else {
						currRoute = neRoute;
						neRoute = neRoute->nextRoute;
					}
				}
				currRoute = NULL;
				if (cityGraph.adjlist[i].firstTrainRoute->endCity == city) {	//检查第一条路线的终点城市
					neRoute = cityGraph.adjlist[i].firstTrainRoute->nextRoute;
					free(cityGraph.adjlist[i].firstTrainRoute);
					cityGraph.adjlist[i].firstTrainRoute = neRoute;
					neRoute = NULL;
					cityGraph.adjlist[i].flightRouteNum--;
				}
				neRoute = NULL;
			}

			currRoute = cityGraph.adjlist[i].firstFlightRoute;	//删除飞机路线
			if (currRoute != NULL) {
				neRoute = currRoute->nextRoute;
				for (; neRoute != NULL; ) {
					if (neRoute->endCity == city) {
						temp = neRoute->nextRoute;
						free(neRoute);
						neRoute = temp;
						temp = NULL;
						cityGraph.adjlist[i].flightRouteNum--;
						if (neRoute == NULL) break;
					}
					else {
						currRoute = neRoute;
						neRoute = neRoute->nextRoute;
					}
				}
				currRoute = NULL;
				if (cityGraph.adjlist[i].firstFlightRoute->endCity == city) {	//检查第一条路线的终点城市
					neRoute = cityGraph.adjlist[i].firstFlightRoute->nextRoute;
					free(cityGraph.adjlist[i].firstFlightRoute);
					cityGraph.adjlist[i].firstFlightRoute = neRoute;
					neRoute = NULL;
					cityGraph.adjlist[i].flightRouteNum--;
				}
			}
		}
	}
	for (CityNode i = city; i <= MaxCityNum - 2; i++) {
		strcpy_s(cityNames[i], cityNames[i + 1]);
	}
	cityNum--;
	return OK;
}

State InsertTrainRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime) {
	int i = SeekCity(start), j = SeekCity(end);
	if (i < 0 || j < 0) {
		cout << "城市不存在！" << endl;
		return ERROR;
	}
	if (cityGraph.adjlist[i].firstTrainRoute != NULL) {
		RouteUnit* temp = cityGraph.adjlist[i].firstTrainRoute;
		cityGraph.adjlist[i].firstTrainRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
		cityGraph.adjlist[i].firstTrainRoute->nextRoute = temp;
	}
	else {
		cityGraph.adjlist[i].firstTrainRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
		cityGraph.adjlist[i].firstTrainRoute->nextRoute = NULL;
	}
	cityGraph.adjlist[i].firstTrainRoute->cost = cost;
	cityGraph.adjlist[i].firstTrainRoute->endCity = j;

	cityGraph.adjlist[i].firstTrainRoute->startTime.Year = stTime.Year;
	cityGraph.adjlist[i].firstTrainRoute->startTime.Month = stTime.Month;
	cityGraph.adjlist[i].firstTrainRoute->startTime.Day = stTime.Day;
	cityGraph.adjlist[i].firstTrainRoute->startTime.HH = stTime.HH;
	cityGraph.adjlist[i].firstTrainRoute->startTime.MM = stTime.MM;

	cityGraph.adjlist[i].firstTrainRoute->endTime.Year = edTime.Year;
	cityGraph.adjlist[i].firstTrainRoute->endTime.Month = edTime.Month;
	cityGraph.adjlist[i].firstTrainRoute->endTime.Day = edTime.Day;
	cityGraph.adjlist[i].firstTrainRoute->endTime.HH = edTime.HH;
	cityGraph.adjlist[i].firstTrainRoute->endTime.MM = edTime.MM;

	//cityGraph.adjlist[i].firstFlightRoute->startTime = stTime;
	//cityGraph.adjlist[i].firstFlightRoute->endTime = edTime;


	strcpy_s(cityGraph.adjlist[i].firstTrainRoute->routeName, name);
	cityGraph.adjlist[i].trainRouteNum++;
	return OK;
}

State InsertFlightRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime) {
	int i = SeekCity(start), j = SeekCity(end);
	if (i < 0 || j < 0) {
		cout << "城市不存在！" << endl;
		return ERROR;
	}
	if (cityGraph.adjlist[i].firstFlightRoute != NULL) {
		RouteUnit* temp = cityGraph.adjlist[i].firstFlightRoute;
		cityGraph.adjlist[i].firstFlightRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
		cityGraph.adjlist[i].firstFlightRoute->nextRoute = temp;
	}
	else {
		cityGraph.adjlist[i].firstFlightRoute = (RouteUnit*)malloc(sizeof(RouteUnit));
		cityGraph.adjlist[i].firstFlightRoute->nextRoute = NULL;
	}
	cityGraph.adjlist[i].firstFlightRoute->cost = cost;
	cityGraph.adjlist[i].firstFlightRoute->endCity = j;

	cityGraph.adjlist[i].firstFlightRoute->startTime.Year = stTime.Year;
	cityGraph.adjlist[i].firstFlightRoute->startTime.Month = stTime.Month;
	cityGraph.adjlist[i].firstFlightRoute->startTime.Day = stTime.Day;
	cityGraph.adjlist[i].firstFlightRoute->startTime.HH = stTime.HH;
	cityGraph.adjlist[i].firstFlightRoute->startTime.MM = stTime.MM;

	cityGraph.adjlist[i].firstFlightRoute->endTime.Year = edTime.Year;
	cityGraph.adjlist[i].firstFlightRoute->endTime.Month = edTime.Month;
	cityGraph.adjlist[i].firstFlightRoute->endTime.Day = edTime.Day;
	cityGraph.adjlist[i].firstFlightRoute->endTime.HH = edTime.HH;
	cityGraph.adjlist[i].firstFlightRoute->endTime.MM = edTime.MM;

	strcpy_s(cityGraph.adjlist[i].firstFlightRoute->routeName, name);
	cityGraph.adjlist[i].flightRouteNum++;
	return OK;
}

State DelTrainPath(Name* name) {
	bool flag = 0;
	int i;
	RouteUnit* currRoute = NULL;
	for (i = 0; i <= cityNum - 1; i++) {
		currRoute = cityGraph.adjlist[i].firstTrainRoute;
		if (currRoute == NULL) {
			continue;
		}
		if (strcmp((currRoute->routeName), name) == 0) {
			flag = 1;
			cityGraph.adjlist[i].firstTrainRoute = currRoute->nextRoute;
			free(currRoute);
			cityGraph.adjlist[i].trainRouteNum--;
			return OK;
		}
		else {
			while (currRoute->nextRoute != NULL) {
				if (strcmp((currRoute->nextRoute->routeName), name) == 0) {
					flag = 1;
					break;
				}
				else {
					currRoute = currRoute->nextRoute;
				}
				if (flag) break;
			}
			if (flag) {
				RouteUnit* temp = currRoute->nextRoute->nextRoute;
				free(currRoute->nextRoute);
				currRoute->nextRoute = temp;
				temp = NULL;
				cityGraph.adjlist[i].trainRouteNum--;
				return OK;
			}
		}
	}
	if (!flag) {
		cout << "该路线不存在！" << endl;
		return ERROR;
	}
}

State DelFlightPath(Name* name) {
	bool flag = 0;
	int i;
	RouteUnit* currRoute = NULL;
	for (i = 0; i <= cityNum - 1; i++) {
		currRoute = cityGraph.adjlist[i].firstFlightRoute;
		if (currRoute == NULL) {
			continue;
		}
		if (strcmp((currRoute->routeName), name) == 0) {
			flag = 1;
			cityGraph.adjlist[i].firstFlightRoute = currRoute->nextRoute;
			free(currRoute);
			cityGraph.adjlist[i].flightRouteNum--;
			return OK;
		}
		else {
			while (currRoute->nextRoute != NULL) {
				if (strcmp((currRoute->nextRoute->routeName), name) == 0) {
					flag = 1;
					break;
				}
				else {
					currRoute = currRoute->nextRoute;
				}
				if (flag) break;
			}
			if (flag) {
				RouteUnit* temp = currRoute->nextRoute->nextRoute;
				free(currRoute->nextRoute);
				currRoute->nextRoute = temp;
				temp = NULL;
				cityGraph.adjlist[i].flightRouteNum--;
				return OK;
			}
		}
	}
	if (!flag) {
		cout << "该路线不存在！" << endl;
		return ERROR;
	}
}

RouteUnit* SeekTrainRoute(CityNode st, CityNode ed) {
	RouteUnit* currRoute = NULL;
	int flag = 0;
	for (currRoute = cityGraph.adjlist[st].firstTrainRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
		if (currRoute->endCity == ed) {
			flag = 1;
			break;
		}
	}
	if (flag) return currRoute;
	else return NULL;
}

RouteUnit* SeekFlightRoute(CityNode st, CityNode ed) {
	RouteUnit* currRoute = NULL;
	int flag = 0;
	for (currRoute = cityGraph.adjlist[st].firstFlightRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
		if (currRoute->endCity == ed) {
			flag = 1;
			break;
		}
	}
	if (flag) return currRoute;
	else return NULL;
}

Time GetTrainRouteTimeWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstTrainRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return CalTime(currRoute->startTime, currRoute->endTime);
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

Time GetFlightRouteTimeWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstFlightRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return CalTime(currRoute->startTime, currRoute->endTime);
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

Money GetTrainRouteMoneyWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstTrainRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return currRoute->cost;
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

Money GetFlightRouteMoneyWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstFlightRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return currRoute->cost;
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

TransTimes GetTrainRouteTransTimesWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstTrainRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return 1;
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

TransTimes GetFlightRouteTransTimesWeight(CityNode st, CityNode ed) {
	RouteUnit* currRoute = cityGraph.adjlist[st].firstFlightRoute;
	while (currRoute != NULL) {
		if (currRoute->endCity == ed) return 1;
		currRoute = currRoute->nextRoute;
	}
	return INF;
}

int cnt = 0;
State PrintPath(CityNode* path, CityNode edCity) {
	if (path[edCity] == -1 && cnt == 0) cout << "没有路径！";
	else {
		if (path[edCity] == -1) {
			cout << cityNames[edCity] << ' ';
			cnt = 0;
		}
		else {
			cnt++;
			PrintPath(path, path[edCity]);
			cout << cityNames[edCity] << ' ';
		}
	}
	return OK;
}

State TrainTimeDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Time dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Time minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstTrainRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetTrainRouteTimeWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekTrainRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekTrainRoute(path[minNode], minNode)->endTime, SeekTrainRoute(minNode, j)->startTime))
					weight = GetTrainRouteTimeWeight(minNode, j) + CalTime(SeekTrainRoute(path[minNode], minNode)->endTime, SeekTrainRoute(minNode, j)->startTime);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最快到达的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计耗时：" << dist[edCity] << "分钟" << endl;
	return OK;
}

State TrainMoneyDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Money dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Money minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstTrainRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetTrainRouteMoneyWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekTrainRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekTrainRoute(path[minNode], minNode)->endTime, SeekTrainRoute(minNode, j)->startTime))
					weight = GetTrainRouteMoneyWeight(minNode, j);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最小开销的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计开销：" << dist[edCity] << "元" << endl;
	return OK;
}

State TrainTransTimesDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	TransTimes dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	TransTimes minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstTrainRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetTrainRouteTransTimesWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekTrainRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekTrainRoute(path[minNode], minNode)->endTime, SeekTrainRoute(minNode, j)->startTime))
					weight = GetTrainRouteTransTimesWeight(minNode, j);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最少中转的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计中转：" << dist[edCity] - 1 << "次" << endl;
	return OK;
}

State FlightTimeDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Time dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Time minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstFlightRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetFlightRouteTimeWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekFlightRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekFlightRoute(path[minNode], minNode)->endTime, SeekFlightRoute(minNode, j)->startTime))
					weight = GetFlightRouteTimeWeight(minNode, j) + CalTime(SeekFlightRoute(path[minNode], minNode)->endTime, SeekFlightRoute(minNode, j)->startTime);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最快到达的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计耗时：" << dist[edCity] << "分钟" << endl;
	return OK;
}

State FlightMoneyDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Money dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Money minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstFlightRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetFlightRouteMoneyWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekFlightRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekFlightRoute(path[minNode], minNode)->endTime, SeekFlightRoute(minNode, j)->startTime))
					weight = GetFlightRouteMoneyWeight(minNode, j);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最小开销的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计开销：" << dist[edCity] << "元" << endl;
	return OK;
}

State FlightTransTimesDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	TransTimes dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	TransTimes minWeight, weight;
	//给三个数组赋初值
	for (i = 0; i <= cityNum - 1; i++) {
		visited[i] = 0;
		path[i] = -1;
		dist[i] = INF;
	}
	RouteUnit* currRoute = cityGraph.adjlist[stCity].firstFlightRoute;
	while (currRoute != NULL) {
		dist[currRoute->endCity] = GetFlightRouteTransTimesWeight(stCity, currRoute->endCity);
		path[currRoute->endCity] = stCity;
		currRoute = currRoute->nextRoute;
	}
	path[stCity] = -1;
	visited[stCity] = 1;
	dist[stCity] = 0;
	for (i = 0; i <= cityNum - 2; i++) {
		minWeight = INF;
		for (j = 0; j <= cityNum - 1; j++) {
			if (visited[j] == 0 && dist[j] < minWeight) {
				minWeight = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = 1;
		for (j = 0; j <= cityNum - 1; j++) {
			if (SeekFlightRoute(minNode, j) == NULL) weight = INF;
			else {
				if (JudgeTimeFront(SeekFlightRoute(path[minNode], minNode)->endTime, SeekFlightRoute(minNode, j)->startTime))
					weight = GetFlightRouteTransTimesWeight(minNode, j);
				else weight = INF;
			}
			if (visited[j] == 0 && dist[minNode] + weight < dist[j]) {
				dist[j] = dist[minNode] + weight;
				path[j] = minNode;
			}
		}
	}
	cout << "最少中转的路径为：";
	PrintPath(path, edCity);
	cout << endl;
	cout << "共计中转：" << dist[edCity] - 1 << "次" << endl;
	return OK;
}

State ShowAllTrainRoutes() {
	RouteUnit* currRoute = NULL;
	int cnt = 1;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "序号\t班次名称\t始发站\t终点站\t始发时间\t到站时间\t\t费用" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstTrainRoute; currRoute != NULL; currRoute = currRoute->nextRoute, cnt++) {
			cout << cnt << '\t' << currRoute->routeName << "\t\t" << cityNames[i] << '\t' << cityNames[currRoute->endCity] << '\t' 
				<< currRoute->startTime.Year << '-'  << currRoute->startTime.Month << '-' << currRoute->startTime.Day<< ' ' 
				<< currRoute->startTime.HH << ':' << currRoute->startTime.MM << '\t' 
				<< currRoute->endTime.Year << '-' << currRoute->endTime.Month << '-' << currRoute->endTime.Day << ' '
				<< currRoute->endTime.HH << ':' << currRoute->endTime.MM << "\t\t"
				<< currRoute->cost << endl;
		}
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;
	return OK;
}

State ShowStCityTrainRoutes(CityNode st) {
	RouteUnit* currRoute = NULL;
	int cnt = 1;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "序号\t班次名称\t始发站\t终点站\t始发时间\t到站时间\t\t费用" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (currRoute = cityGraph.adjlist[st].firstTrainRoute; currRoute != NULL; currRoute = currRoute->nextRoute, cnt++) {
		cout << cnt << '\t' << currRoute->routeName << "\t\t" << cityNames[st] << '\t' << cityNames[currRoute->endCity] << '\t'
			<< currRoute->startTime.Year << '-' << currRoute->startTime.Month << '-' << currRoute->startTime.Day << ' '
			<< currRoute->startTime.HH << ':' << currRoute->startTime.MM << '\t'
			<< currRoute->endTime.Year << '-' << currRoute->endTime.Month << '-' << currRoute->endTime.Day << ' '
			<< currRoute->endTime.HH << ':' << currRoute->endTime.MM << "\t\t"
			<< currRoute->cost << endl;
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;
	return OK;
}

State ShowAllFlightRoutes() {
	RouteUnit* currRoute = NULL;
	int cnt = 1;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "序号\t班次名称\t始发站\t终点站\t始发时间\t到站时间\t\t费用" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstFlightRoute; currRoute != NULL; currRoute = currRoute->nextRoute, cnt++) {
			cout << cnt << '\t' << currRoute->routeName << "\t\t" << cityNames[i] << '\t' << cityNames[currRoute->endCity] << '\t'
				<< currRoute->startTime.Year << '-' << currRoute->startTime.Month << '-' << currRoute->startTime.Day << ' '
				<< currRoute->startTime.HH << ':' << currRoute->startTime.MM << '\t'
				<< currRoute->endTime.Year << '-' << currRoute->endTime.Month << '-' << currRoute->endTime.Day << ' '
				<< currRoute->endTime.HH << ':' << currRoute->endTime.MM << "\t\t"
				<< currRoute->cost << endl;
		}
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;
	return OK;
}

State ShowStCityFlightRoutes(CityNode st) {
	RouteUnit* currRoute = NULL;
	int cnt = 1;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "序号\t班次名称\t始发站\t终点站\t始发时间\t到站时间\t\t费用" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (currRoute = cityGraph.adjlist[st].firstFlightRoute; currRoute != NULL; currRoute = currRoute->nextRoute, cnt++) {
		cout << cnt << '\t' << currRoute->routeName << "\t\t" << cityNames[st] << '\t' << cityNames[currRoute->endCity] << '\t'
			<< currRoute->startTime.Year << '-' << currRoute->startTime.Month << '-' << currRoute->startTime.Day << ' '
			<< currRoute->startTime.HH << ':' << currRoute->startTime.MM << '\t'
			<< currRoute->endTime.Year << '-' << currRoute->endTime.Month << '-' << currRoute->endTime.Day << ' '
			<< currRoute->endTime.HH << ':' << currRoute->endTime.MM << "\t\t"
			<< currRoute->cost << endl;
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;
	return OK;
}

void ShowTitle() {
	cout << "************************************************" << endl;
	cout << "**************全国交通咨询模拟系统**************" << endl;
	cout << "************************************************" << endl;
}

void ShowAccountMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                  登录身份                  ||" << endl;
	cout << "||                  1.管理员                  ||" << endl;
	cout << "||                  2.游客                    ||" << endl;
	cout << "||                  3.退出                    ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowAdminMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                选择操作                    ||" << endl;
	cout << "||                1.显示菜单                  ||" << endl;
	cout << "||                2.读取文件                  ||" << endl;
	cout << "||                3.保存文件                  ||" << endl;
	cout << "||                4.显示城市列表              ||" << endl;
	cout << "||                5.增加城市                  ||" << endl;
	cout << "||                6.删除城市                  ||" << endl;
	cout << "||                7.显示火车班次              ||" << endl;
	cout << "||                8.显示航班                  ||" << endl;
	cout << "||                9.增加火车路线              ||" << endl;
	cout << "||                10.增加飞机路线             ||" << endl;
	cout << "||                11.删除火车路线             ||" << endl;
	cout << "||                12.删除飞机路线             ||" << endl;
	cout << "||                13.退出                     ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowRoutesMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                选择查看方式                ||" << endl;
	cout << "||                1.选择始发城市              ||" << endl;
	cout << "||                2.所有班次                  ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowUserMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||            选择操作                        ||" << endl;
	cout << "||            1.显示菜单                      ||" << endl;
	cout << "||            2.显示城市列表                  ||" << endl;
	cout << "||            3.显示火车班次                  ||" << endl;
	cout << "||            4.显示航班                      ||" << endl;
	cout << "||            5.查询火车最短时间路线          ||" << endl;
	cout << "||            6.查询火车最少开销路线          ||" << endl;
	cout << "||            7.查询火车最少中转路线          ||" << endl;
	cout << "||            8.查询飞机最短时间路线          ||" << endl;
	cout << "||            9.查询飞机最少开销路线          ||" << endl;
	cout << "||            10.查询飞机最少中转路线         ||" << endl;
	cout << "||            11.退出                         ||" << endl;
	cout << "------------------------------------------------" << endl;
}
