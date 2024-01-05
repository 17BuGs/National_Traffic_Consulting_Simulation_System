#pragma once
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <string>
using namespace std;

#define MaxFileLineReadLength 100	//读文件时每行最长读取的字符数
#define MaxCityNum 672	//最大城市数量
#define MaxCityNameLength 20	//城市字符串的最长长度
#define MaxRouteNameLength 50	//班次字符串的最长长度
#define MaxRouteUnitNum 50	//从某一城市出发，直达城市的线路最大条数
#define INF 99999	//infinite

typedef bool State;
typedef short int CityNode;	//城市节点，用整形数表示
typedef int Time;	//时间用整形数表示
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
	DateTime startTime, endTime;	//起止时间
	CityNode endCity;	//终点城市
	Money cost;	//票价
	RouteUnit* nextRoute;
} RouteUnit;

typedef struct CityRoute {
	//CityNode city;
	int trainRouteNum = 0, flightRouteNum = 0;
	RouteUnit* firstTrainRoute;
	RouteUnit* firstFlightRoute;
} CityRoute;	//从某一城市出发，直达城市的线路信息

typedef struct CityGraph {
	CityRoute adjlist[MaxCityNum];
	//int numNodes, numEdges;
} CityGraph;	//邻接表

Name cityNames[MaxCityNum][MaxCityNameLength] = {};
short int cityNum = 0;
//Time minTime = INF;
//Money minMoney = INF;
//TransTimes minTranstimes = INF;
CityGraph cityGraph;

bool JudgeTimeFront(DateTime time1, DateTime time2);	//判断参数1的时间是否先于参数2
Time CalTime(DateTime stTime, DateTime edTime);	//计算两个日期相隔的分钟数
State ShowCityList();	//显示城市列表
CityNode SeekCity(char* city);	//查找某一城市，返回该城市的下标
State SaveFile();	//写入交通信息
State ReadFile();	//读取交通信息
State DestoryGraph();	//重置邻接表
State InsertCity(Name* name);	//添加城市
State DelCity(Name* name);	//删除城市
State InsertTrainRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime);	//添加火车班次
State InsertFlightRoute(Name* name, Name* start, Name* end, Money cost, DateTime stTime, DateTime edTime);	//添加航班
State DelTrainPath(Name* name);	//删除火车班次
State DelFlightPath(Name* name);	//删除航班
RouteUnit* SeekTrainRoute(CityNode st, CityNode ed);	//返回指向某一火车路线的指针
RouteUnit* SeekFlightRoute(CityNode st, CityNode ed);	//返回指向某一航班的指针
Time GetTrainRouteTimeWeight(CityNode st, CityNode ed);	//以最短时间为最佳决策时获取火车路线权重
Time GetFlightRouteTimeWeight(CityNode st, CityNode ed);	//以最短时间为最佳决策时获取飞机路线权重
Money GetTrainRouteMoneyWeight(CityNode st, CityNode ed);	//以最少开销为最佳决策时获取火车路线权重
Money GetFlightRouteMoneyWeight(CityNode st, CityNode ed);	//以最少开销为最佳决策时获取飞机路线权重
TransTimes GetTrainRouteTransTimesWeight(CityNode st, CityNode ed);	//以最少中转次数为最佳决策时获取火车路线权重
TransTimes GetFlightRouteTransTimesWeight(CityNode st, CityNode ed);	//以最少中转次数为最佳决策时获取飞机路线权重
State TrainTimeDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以火车为交通方式的最短时间决策
State TrainMoneyDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以火车为交通方式的最少开销决策
State TrainTransTimesDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以火车为交通方式的最少中转次数决策
State FlightTimeDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以飞机为交通方式的最短时间决策
State FlightMoneyDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以飞机为交通方式的最少开销决策
State FlightTransTimesDijkstra(CityNode stCity, CityNode edCity);	//Dijkstra算法求以飞机为交通方式的最少中转次数决策
State PrintPath(CityNode path[], CityNode edCity, int judge);	//输出交通路线
State ShowAllTrainRoutes();	//显示所有火车班次
State ShowStCityTrainRoutes(CityNode st);	//显示从某一城市出发的火车班次
State ShowAllFlightRoutes();	//显示所有航班
State ShowStCityFlightRoutes(CityNode st);	//显示从某一城市出发的航班
void ShowTitle();	//显示程序标题
void ShowAccountMenu();	//显示用户登入菜单
void ShowAdminMenu();	//显示管理员操作菜单
void ShowUserMenu();	//显示游客操作菜单
void ShowRoutesMenu();	//显示查看班次的方式
