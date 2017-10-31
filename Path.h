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

	//ПОДУМАТЬ НАД АРГУМЕНТАМИ и конструктором И УБРАТЬ ЧАСТЬ переменных из класса 
	int fortest = 0;
	bool passedPoints[height*width * 4];
	sf::Vector2<int> targetPosition = sf::Vector2<int>(372 / blockSize, 319 / blockSize);///// координаты таргета 
	//void qwe(sf::Vector2<int> point, int potentialForCurrentPoint);////рекурсивный метод для заполнения положительным приоритетом	
	void InitPMap(char map[width*height * 4]);
	void ChangedCoordForNextStep(float*x, float* y, sf::FloatRect currentCoordIn);	
	void FindPath(int startIndex, int endIndex);
	void Path::Move(char map[]);
	//int operator() ();
};