#pragma once
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <string>
using namespace std;

#define MaxFileLineReadLength 100	//���ļ�ʱÿ�����ȡ���ַ���
#define MaxCityNum 672	//����������
#define MaxCityNameLength 20	//�����ַ����������
#define MaxRouteNameLength 50	//����ַ����������
#define MaxRouteUnitNum 50	//��ĳһ���г�����ֱ����е���·�������
#define INF 99999	//infinite

typedef bool State;
typedef short int CityNode;	//���нڵ㣬����������ʾ
typedef int Time;	//ʱ������������ʾ
typedef double Money;
typedef int TransTimes;
typedef char Name;

const bool OK = true;
const bool ERROR = false;

typedef struct DateTime {
	Time Year;
	Time Month;
	Time Day;
	Time HH;
	Time MM;
	Time SS;
} DateTime;

typedef struct RouteUnit {
	Name routeName[MaxRouteNameLength];
	DateTime startTime, endTime;	//��ֹʱ��
	CityNode endCity;	//�յ����
	Money cost;	//Ʊ��
	RouteUnit* nextRoute;
} RouteUnit;

typedef struct CityRoute {
	//CityNode city;
	int trainRouteNum = 0, flightRouteNum = 0;
	RouteUnit* firstTrainRoute;
	RouteUnit* firstFlightRoute;
} CityRoute;	//��ĳһ���г�����ֱ����е���·��Ϣ

typedef struct CityGraph {
	CityRoute adjlist[MaxCityNum];
	//int numNodes, numEdges;
} CityGraph;	//�ڽӱ�

Name cityNames[MaxCityNum][MaxCityNameLength] = {};
short int cityNum = 0;
//Time minTime = INF;
//Money minMoney = INF;
//TransTimes minTranstimes = INF;
CityGraph cityGraph;

bool JudgeTimeFront(DateTime time1, DateTime time2);	//�жϲ���1��ʱ���Ƿ����ڲ���2
Time CalTime(DateTime stTime, DateTime edTime);	//����������������ķ�����
State ShowCityList();	//��ʾ�����б�
CityNode SeekCity(char* city);	//����ĳһ���У����ظó��е��±�
State SaveFile();	//д�뽻ͨ��Ϣ
State ReadFile();	//��ȡ��ͨ��Ϣ
State DestoryGraph();	//�����ڽӱ�
State InsertCity(Name* name);	//��ӳ���
State DelCity(Name* name);	//ɾ������
State InsertTrainRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime);	//��ӻ𳵰��
State InsertFlightRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime);	//��Ӻ���
State DelTrainPath(Name* name);	//ɾ���𳵰��
State DelFlightPath(Name* name);	//ɾ������
RouteUnit* SeekTrainRoute(CityNode st, CityNode ed);	//����ָ��ĳһ��·�ߵ�ָ��
RouteUnit* SeekFlightRoute(CityNode st, CityNode ed);	//����ָ��ĳһ�����ָ��
Time GetTrainRouteTimeWeight(CityNode st, CityNode ed);	//�����ʱ��Ϊ��Ѿ���ʱ��ȡ��·��Ȩ��
Time GetFlightRouteTimeWeight(CityNode st, CityNode ed);	//�����ʱ��Ϊ��Ѿ���ʱ��ȡ�ɻ�·��Ȩ��
Money GetTrainRouteMoneyWeight(CityNode st, CityNode ed);	//�����ٿ���Ϊ��Ѿ���ʱ��ȡ��·��Ȩ��
Money GetFlightRouteMoneyWeight(CityNode st, CityNode ed);	//�����ٿ���Ϊ��Ѿ���ʱ��ȡ�ɻ�·��Ȩ��
TransTimes GetTrainRouteTransTimesWeight(CityNode st, CityNode ed);	//��������ת����Ϊ��Ѿ���ʱ��ȡ��·��Ȩ��
TransTimes GetFlightRouteTransTimesWeight(CityNode st, CityNode ed);	//��������ת����Ϊ��Ѿ���ʱ��ȡ�ɻ�·��Ȩ��
State TrainTimeDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Ի�Ϊ��ͨ��ʽ�����ʱ�����
State TrainMoneyDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Ի�Ϊ��ͨ��ʽ�����ٿ�������
State TrainTransTimesDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Ի�Ϊ��ͨ��ʽ��������ת��������
State FlightTimeDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Էɻ�Ϊ��ͨ��ʽ�����ʱ�����
State FlightMoneyDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Էɻ�Ϊ��ͨ��ʽ�����ٿ�������
State FlightTransTimesDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra�㷨���Էɻ�Ϊ��ͨ��ʽ��������ת��������
State PrintPath(CityNode path[], CityNode edCity, int judge);	//�����ͨ·��
State ShowAllTrainRoutes();	//��ʾ���л𳵰��
State ShowStCityTrainRoutes(CityNode st);	//��ʾ��ĳһ���г����Ļ𳵰��
State ShowAllFlightRoutes();	//��ʾ���к���
State ShowStCityFlightRoutes(CityNode st);	//��ʾ��ĳһ���г����ĺ���
void ShowTitle();	//��ʾ�������
void ShowAccountMenu();	//��ʾ�û�����˵�
void ShowAdminMenu();	//��ʾ����Ա�����˵�
void ShowUserMenu();	//��ʾ�οͲ����˵�
void ShowRoutesMenu();	//��ʾ�鿴��εķ�ʽ
