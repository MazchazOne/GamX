#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Graph.h"
#include <stack>
class Path //PAtch handler // graphs coming soon //extern
{
public:
	const int maxPotential = 1000;
	const int minPotential = -500;
	const int aroundMin = -250;

	stack<int> stepsStack;
	//int PMap[height*width * 4];
	int priorityDifferenceFromTarget = 10;

	//�������� ��� ����������� � ������������� � ������ ����� ���������� �� ������ 
	int fortest = 0;
	bool passedPoints[height*width * 4];
	sf::Vector2<int> targetPosition = sf::Vector2<int>(372 / blockSize, 319 / blockSize);///// ���������� ������� 
	//void qwe(sf::Vector2<int> point, int potentialForCurrentPoint);////����������� ����� ��� ���������� ������������� �����������	
	void InitPMap(char map[width*height * 4]);
	void ChangedCoordForNextStep(float*x, float* y, sf::FloatRect* currentCoordIn,float time);	
	void FindPath(int startIndex, int endIndex);
	void Path::Move(char map[]);
	//int operator() ();
};