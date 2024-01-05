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
	int a[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };	//�����е�һ��Ԫ��ֱ�Ӹ�ֵΪ0�����·����Ӧ
	for (i = stTime.Year; i <= edTime.Year; i++) {
		if (i == stTime.Year) month1 = stTime.Month;
		else month1 = 1;   //�����������  �·ݿ�ʼ��ֵΪ1������ʼ��ݺ�Ŀ������⣩
		if (i == edTime.Year) month2 = edTime.Month;
		else month2 = 12;
		for (j = month1; j <= month2; j++) {	  //������Ӧ���·ݲ�
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) a[2] = 29;	//�ж��Ƿ�Ϊ���꣬��Ϊ���꽫���·����¸�ֵΪ29��
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
	return sum - 1;   //����ֵ�������������ķ�����
}
State ShowCityList() {
	if (cityNum == 0) {
		cout << "���޳�����Ϣ" << endl;
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
	FILE* file;	//����д���ļ�
	RouteUnit* currRoute = NULL;
	cout << "���ļ�city.txt..." << endl;
	if ((fopen_s(&file, "city.txt", "w")) != 0) {
		cout << "�޷���city.txt��" << endl;
		return ERROR;
	}
	cout << "�洢����������Ϣ..." << endl;
	fprintf(file, "%d\n", cityNum);
	cout << "�洢��������..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fprintf(file, "%s\n", cityNames[i]);
	}
	fclose(file);

	cout << "���ļ�train.txt..." << endl;
	if ((fopen_s(&file, "train.txt", "w")) != 0) {
		cout << "�޷���train.txt��" << endl;
		return ERROR;
	}
	cout << "�洢�𳵰������..." << endl;
	int trainRouteNum = 0;
	for (int i = 0; i <= cityNum - 1; i++) {
		trainRouteNum = cityGraph.adjlist[i].trainRouteNum;
		fprintf(file, "%d\n", trainRouteNum);
	}
	cout << "�洢�𳵰����Ϣ..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstTrainRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
			//�𳵰�����ƣ�ʼ��վ���յ�վ��ʼ��ʱ�䣨stYear, stMonth, stDay, stHH, stMM������վʱ�䣨ͬ�ϣ�������
			fprintf(file, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n", 
				currRoute->routeName, cityNames[i], cityNames[currRoute->endCity],
				currRoute->startTime.Year, currRoute->startTime.Month, currRoute->startTime.Day, currRoute->startTime.HH, currRoute->startTime.MM,
				currRoute->endTime.Year, currRoute->endTime.Month, currRoute->endTime.Day, currRoute->endTime.HH, currRoute->endTime.MM,
				currRoute->cost);
		}
	}
	fclose(file);

	cout << "���ļ�flight.txt..." << endl;
	if ((fopen_s(&file, "flight.txt", "w")) != 0) {
		cout << "�޷���flight.txt��" << endl;
		return ERROR;
	}
	cout << "�洢��������..." << endl;
	int flightRouteNum = 0;
	for (int i = 0; i <= cityNum - 1; i++) {
		flightRouteNum = cityGraph.adjlist[i].flightRouteNum;
		fprintf(file, "%d\n", flightRouteNum);
	}
	cout << "�洢������Ϣ..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		for (currRoute = cityGraph.adjlist[i].firstFlightRoute; currRoute != NULL; currRoute = currRoute->nextRoute) {
			//�𳵰�����ƣ�ʼ��վ���յ�վ��ʼ��ʱ�䣨stYear, stMonth, stDay, stHH, stMM������վʱ�䣨ͬ�ϣ�������
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
	FILE* file;	//����д���ļ�
	RouteUnit* currRoute = NULL;
	char* find = NULL;	//�����ҵ��ļ��������е�'\n'
	cout << "���ļ�city.txt..." << endl;
	if ((fopen_s(&file, "city.txt", "r")) != 0) {
		cout << "�޷���city.txt��" << endl;
		return ERROR;
	}
	cout << "��ȡ����������Ϣ..." << endl;
	char cont[MaxFileLineReadLength];
	fgets(cont, sizeof(cont), file);
	find = strchr(cont, '\n');
	if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
	cityNum = atoi(cont);
	cout << "��ȡ��������..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
		strcpy_s(cityNames[i], cont);
	}
	fclose(file);
	DestoryGraph();
	cout << "���ļ�train.txt..." << endl;
	if ((fopen_s(&file, "train.txt", "r")) != 0) {
		cout << "�޷���train.txt��" << endl;
		return ERROR;
	}
	cout << "��ȡ�𳵰������..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
		cityGraph.adjlist[i].trainRouteNum = atoi(cont);
	}
	cout << "��ȡ�𳵰����Ϣ..." << endl;
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
			fgets(cont, sizeof(cont), file);	//��ȡ�𳵰������
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			strcpy_s(cityGraph.adjlist[i].firstTrainRoute->routeName, cont);
			fgets(cont, sizeof(cont), file);	//��ȡʼ��վ
			fgets(cont, sizeof(cont), file);	//��ȡ�յ�վ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endCity = SeekCity(cont);

			//��ȡʼ��ʱ��
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//ʱ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->startTime.MM = atoi(cont);

			//��ȡ��վʱ��
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//ʱ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->endTime.MM = atoi(cont);

			fgets(cont, sizeof(cont), file);	//��ȡ����
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstTrainRoute->cost = atof(cont);
		}
	}
	fclose(file);
	cout << "���ļ�flight.txt..." << endl;
	if ((fopen_s(&file, "flight.txt", "r")) != 0) {
		cout << "�޷���flight.txt��" << endl;
		return ERROR;
	}
	cout << "��ȡ��������..." << endl;
	for (int i = 0; i <= cityNum - 1; i++) {
		fgets(cont, sizeof(cont), file);
		find = strchr(cont, '\n');
		if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
		cityGraph.adjlist[i].flightRouteNum = atoi(cont);
	}
	cout << "��ȡ������Ϣ..." << endl;
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
			fgets(cont, sizeof(cont), file);	//��ȡ�𳵰������
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			strcpy_s(cityGraph.adjlist[i].firstFlightRoute->routeName, cont);
			fgets(cont, sizeof(cont), file);	//��ȡʼ��վ
			fgets(cont, sizeof(cont), file);	//��ȡ�յ�վ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endCity = SeekCity(cont);

			//��ȡʼ��ʱ��
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//ʱ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->startTime.MM = atoi(cont);

			//��ȡ��վʱ��
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Year = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Month = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.Day = atoi(cont);
			fgets(cont, sizeof(cont), file);	//ʱ
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.HH = atoi(cont);
			fgets(cont, sizeof(cont), file);	//��
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
			cityGraph.adjlist[i].firstFlightRoute->endTime.MM = atoi(cont);

			fgets(cont, sizeof(cont), file);	//��ȡ����
			find = strchr(cont, '\n');
			if (find) *find = '\0';	//�滻��ȡ����'\n'Ϊ'\0'
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
		cout << "�ó����Ѵ��ڣ�" << endl;
		return ERROR;
	}
}

State DelCity(Name* name) {
	CityNode city = SeekCity(name);
	if (city == -1) {
		cout << "�ó��в����ڣ�" << endl;
		return ERROR;
	}
	RouteUnit* currRoute = NULL, * neRoute = NULL, * temp = NULL;
	for (int i = 0; i <= cityNum - 1; i++) {
		if (strcmp(cityNames[i], name) == 0) {	//�ͷ��ڽӱ����Ըó���Ϊ���ߵ�����·��
			currRoute = cityGraph.adjlist[i].firstTrainRoute;	//ɾ�����л�·��
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
			currRoute = cityGraph.adjlist[i].firstFlightRoute;	//ɾ�����зɻ�·��
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
		else {	//�ͷ��ڽӱ����Ըó���Ϊ��ߵ�����·��
			currRoute = cityGraph.adjlist[i].firstTrainRoute;	//ɾ����·��
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
				if (cityGraph.adjlist[i].firstTrainRoute->endCity == city) {	//����һ��·�ߵ��յ����
					neRoute = cityGraph.adjlist[i].firstTrainRoute->nextRoute;
					free(cityGraph.adjlist[i].firstTrainRoute);
					cityGraph.adjlist[i].firstTrainRoute = neRoute;
					neRoute = NULL;
					cityGraph.adjlist[i].flightRouteNum--;
				}
				neRoute = NULL;
			}

			currRoute = cityGraph.adjlist[i].firstFlightRoute;	//ɾ���ɻ�·��
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
				if (cityGraph.adjlist[i].firstFlightRoute->endCity == city) {	//����һ��·�ߵ��յ����
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
		cout << "���в����ڣ�" << endl;
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
		cout << "���в����ڣ�" << endl;
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
		cout << "��·�߲����ڣ�" << endl;
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
		cout << "��·�߲����ڣ�" << endl;
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
	if (path[edCity] == -1 && cnt == 0) cout << "û��·����";
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
	//���������鸳��ֵ
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
	cout << "��쵽���·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "���ƺ�ʱ��" << dist[edCity] << "����" << endl;
	return OK;
}

State TrainMoneyDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Money dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Money minWeight, weight;
	//���������鸳��ֵ
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
	cout << "��С������·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "���ƿ�����" << dist[edCity] << "Ԫ" << endl;
	return OK;
}

State TrainTransTimesDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	TransTimes dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	TransTimes minWeight, weight;
	//���������鸳��ֵ
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
	cout << "������ת��·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "������ת��" << dist[edCity] - 1 << "��" << endl;
	return OK;
}

State FlightTimeDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Time dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Time minWeight, weight;
	//���������鸳��ֵ
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
	cout << "��쵽���·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "���ƺ�ʱ��" << dist[edCity] << "����" << endl;
	return OK;
}

State FlightMoneyDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	Money dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	Money minWeight, weight;
	//���������鸳��ֵ
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
	cout << "��С������·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "���ƿ�����" << dist[edCity] << "Ԫ" << endl;
	return OK;
}

State FlightTransTimesDijkstra(CityNode stCity, CityNode edCity) {
	int visited[MaxCityNum];
	TransTimes dist[MaxCityNum];
	CityNode path[MaxCityNum];
	int i, j;
	CityNode minNode;
	TransTimes minWeight, weight;
	//���������鸳��ֵ
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
	cout << "������ת��·��Ϊ��";
	PrintPath(path, edCity);
	cout << endl;
	cout << "������ת��" << dist[edCity] - 1 << "��" << endl;
	return OK;
}

State ShowAllTrainRoutes() {
	RouteUnit* currRoute = NULL;
	int cnt = 1;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "���\t�������\tʼ��վ\t�յ�վ\tʼ��ʱ��\t��վʱ��\t\t����" << endl;
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
	cout << "���\t�������\tʼ��վ\t�յ�վ\tʼ��ʱ��\t��վʱ��\t\t����" << endl;
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
	cout << "���\t�������\tʼ��վ\t�յ�վ\tʼ��ʱ��\t��վʱ��\t\t����" << endl;
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
	cout << "���\t�������\tʼ��վ\t�յ�վ\tʼ��ʱ��\t��վʱ��\t\t����" << endl;
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
	cout << "**************ȫ����ͨ��ѯģ��ϵͳ**************" << endl;
	cout << "************************************************" << endl;
}

void ShowAccountMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                  ��¼���                  ||" << endl;
	cout << "||                  1.����Ա                  ||" << endl;
	cout << "||                  2.�ο�                    ||" << endl;
	cout << "||                  3.�˳�                    ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowAdminMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                ѡ�����                    ||" << endl;
	cout << "||                1.��ʾ�˵�                  ||" << endl;
	cout << "||                2.��ȡ�ļ�                  ||" << endl;
	cout << "||                3.�����ļ�                  ||" << endl;
	cout << "||                4.��ʾ�����б�              ||" << endl;
	cout << "||                5.���ӳ���                  ||" << endl;
	cout << "||                6.ɾ������                  ||" << endl;
	cout << "||                7.��ʾ�𳵰��              ||" << endl;
	cout << "||                8.��ʾ����                  ||" << endl;
	cout << "||                9.���ӻ�·��              ||" << endl;
	cout << "||                10.���ӷɻ�·��             ||" << endl;
	cout << "||                11.ɾ����·��             ||" << endl;
	cout << "||                12.ɾ���ɻ�·��             ||" << endl;
	cout << "||                13.�˳�                     ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowRoutesMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||                ѡ��鿴��ʽ                ||" << endl;
	cout << "||                1.ѡ��ʼ������              ||" << endl;
	cout << "||                2.���а��                  ||" << endl;
	cout << "------------------------------------------------" << endl;
}

void ShowUserMenu() {
	cout << "------------------------------------------------" << endl;
	cout << "||            ѡ�����                        ||" << endl;
	cout << "||            1.��ʾ�˵�                      ||" << endl;
	cout << "||            2.��ʾ�����б�                  ||" << endl;
	cout << "||            3.��ʾ�𳵰��                  ||" << endl;
	cout << "||            4.��ʾ����                      ||" << endl;
	cout << "||            5.��ѯ�����ʱ��·��          ||" << endl;
	cout << "||            6.��ѯ�����ٿ���·��          ||" << endl;
	cout << "||            7.��ѯ��������ת·��          ||" << endl;
	cout << "||            8.��ѯ�ɻ����ʱ��·��          ||" << endl;
	cout << "||            9.��ѯ�ɻ����ٿ���·��          ||" << endl;
	cout << "||            10.��ѯ�ɻ�������ת·��         ||" << endl;
	cout << "||            11.�˳�                         ||" << endl;
	cout << "------------------------------------------------" << endl;
}
