#include "Path.h"

//POPUTKA USAT" PP
	//const int maxPotential = 1000;
	//const int minPotential = -500;
	//const int aroundMin = -250;
	//int PMap[height*width * 4];
	//int priorityDifferenceFromTarget = 10;

	////ѕќƒ”ћј“№ Ќјƒ ј–√”ћ≈Ќ“јћ» и конструктором » ”Ѕ–ј“№ „ј—“№ переменных из класса 
	//int fortest = 0;
	//bool passedPoints[height*width * 4];
	//sf::Vector2<int> targetPosition = sf::Vector2<int>(372 / blockSize, 319 / blockSize);///// координаты таргета 
	//void Path::qwe(sf::Vector2<int> point, int potentialForCurrentPoint)////рекурсивный метод дл€ заполнени€ положительным приоритетом
	//{
	//	fortest++;
	//	if (PMap[point.x + point.y*width] >= potentialForCurrentPoint)
	//		return;
	//	if (PMap[point.x + point.y*width] == minPotential)
	//		return;
	//	PMap[point.x + point.y*width] = potentialForCurrentPoint;//что-то нужно с этим делать по идее должно быть +=
	//															 /*passedPoints[point.x + point.y*width] = true;
	//															 passedPoints[point.x + (point.y - 1)*width] = true;
	//															 passedPoints[point.x + (point.y +1)*width] = true;
	//															 passedPoints[point.x +1+ (point.y )*width] = true;
	//															 passedPoints[point.x -1+ (point.y )*width] = true;
	//															 */
	//	if (point.x == 0 || point.x == width - 1 || point.y == 0 || point.y == height - 1)
	//		return;
	//	qwe(sf::Vector2<int>(point.x - 1, point.y), potentialForCurrentPoint - priorityDifferenceFromTarget);
	//	qwe(sf::Vector2<int>(point.x + 1, point.y), potentialForCurrentPoint - priorityDifferenceFromTarget);
	//	qwe(sf::Vector2<int>(point.x, point.y - 1), potentialForCurrentPoint - priorityDifferenceFromTarget);
	//	qwe(sf::Vector2<int>(point.x, point.y + 1), potentialForCurrentPoint - priorityDifferenceFromTarget);

	//}
	//void Path::InitPMap(char map[width*height * 4])
	//{////////assign 0 for each element from potential array 
	//	for (int j = 0; j < height; j++)
	//		for (int i = 0; i < width; i++)
	//			PMap[i + j*width] = 0;
	//	////////////

	//	////////////////////////assign negative potential
	//	for (int j = 1; j<height; j++)
	//		for (int i = 1; i < width; i++)
	//		{
	//			if (map[i + width*j] == blockChar)
	//			{
	//				PMap[i + width*j] = minPotential;
	//				if (PMap[i + width*j + 1] == 0)
	//					PMap[i + width*j + 1] = aroundMin;
	//				if (PMap[i + width*j - 1] == 0)
	//					PMap[i + width*j - 1] = aroundMin;
	//				if (PMap[i + width*(j + 1)] == 0)
	//					PMap[i + width*(j + 1)] = aroundMin;
	//				if (PMap[i + width*(j - 1)] == 0)
	//					PMap[i + width*(j - 1)] = aroundMin;
	//			}
	//		}
	//	////////////////////////assign positive potential for target and block around target
	//	//PMap[targetPosition.x+width*targetPosition.y] = maxPotential;
	//	qwe(targetPosition, maxPotential);
	//	////////////////////////
	//}   POPUTKA USAT" PP
//void Path::Move(char map[])
//{
//}
	void Path:: ChangedCoordForNextStep(float*x, float* y, 
		sf::FloatRect currentCoord)
	{	
		sf::FloatRect targetCoord = sf::FloatRect(			
			stepsStack.top()%width*blockSize, 
			stepsStack.top()/width*blockSize,1,1);
		if (currentCoord.intersects(targetCoord))
		{
			if (stepsStack.size()>1)
			stepsStack.pop();
			*x = 0;
			*y = 0;
			return;
		}

		int Dx = abs(currentCoord.left - targetCoord.left);
		int Dy = abs(currentCoord.top - targetCoord.top);
		if (Dx > Dy)
		{
			if (currentCoord.left < targetCoord.left)
				*x += 0.0005;
			else if (currentCoord.left > targetCoord.left)
				*x -= 0.0005;
			else *x = 0;
			if (currentCoord.top < targetCoord.top)
				*y += 0.0005;
			else if (currentCoord.top > targetCoord.top)
				*y -= 0.0005;
			else *y = 0;
		}
		else
		{
			if (currentCoord.top < targetCoord.top)
				*y += 0.0005;
			else if (currentCoord.top > targetCoord.top)
				*y -= 0.0005;
			else *y = 0;
			if (!(currentCoord.intersects(targetCoord)) && (currentCoord.left < targetCoord.left))
				*x += 0.0005;
			else if (currentCoord.left > targetCoord.left)
				*x -= 0.0005;
			else *x = 0;
		}		
	}
	/*int Path::operator() ()
	{
		stepsStack.top();
	}*/
	void Path::FindPath(int startIndex, int endIndex) 
	{
		stepsStack=Graph::FindPath(startIndex, endIndex);
	}	