#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
class Path //PAtch handler // graphs coming soon
{
public:
	const int maxPotential = 1000;
	const int minPotential = -500;
	const int aroundMin = -250;
	int PMap[height*width * 4];
	int priorityDifferenceFromTarget = 10;

	//�������� ��� ����������� � ������������� � ������ ����� ���������� �� ������ 
	int fortest = 0;
	bool passedPoints[height*width * 4];
	sf::Vector2<int> targetPosition = sf::Vector2<int>(372 / blockSize, 319 / blockSize);///// ���������� ������� 
	void qwe(sf::Vector2<int> point, int potentialForCurrentPoint);////����������� ����� ��� ���������� ������������� �����������	
	void InitPMap(char map[width*height * 4]);
	static void ChangedCoordForNextStep(float*x, float* y, sf::FloatRect currentCoordIn, sf::FloatRect targetCoord);
};