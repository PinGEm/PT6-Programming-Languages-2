#include <iostream>
#include <conio.h>

#define X 0
#define Y 1

int validateInput(int lowest, int highest);

int main()
{	
	// ------------------------------------- DATA TRAINING -------------------------------------
	
	
	int sampleSize = 5;
	
	double coords[][sampleSize] = 
	{
		{0,1,2,3,4}, // X COORDINATE
		{30,28.85,27.7,26.55,25.4} // Y COORDINATES
	};
	
	double sumX = 0, sumY = 0;
	
	// summing X & Y Coords
	for(int i = 0; i < sampleSize; i++)
	{
		sumX += coords[X][i];
		sumY += coords[Y][i];
	}
	
	double meanX = sumX / sampleSize;
	double meanY = sumY / sampleSize;
	
	// Calculate slope and intercept
	double numerator = 0, denominator = 0;
	for(int i = 0; i < sampleSize; i++)
	{
		numerator += (coords[X][i] - meanX) * (coords[Y][i] - meanY);
		denominator += (coords[X][i] - meanX) * (coords[X][i] - meanX);
	}
	double slope = numerator / denominator;
	double xIntercept = meanY - slope * meanX;
	
	std::cout << "Training complete!" << std::endl;
	std::cout << "Model: y = " << slope << "x + " << xIntercept << std::endl;
	
	
	// ------------------------------------- MAIN PROGRAM FLOW -------------------------------------
	
	
	std::cout << "***********************************\n";
	std::cout << "   TEMPERATURE PREDICTER PROGRAM\n";
	std::cout << "***********************************\n";

	
	// Now predict a new value
	int input;
	bool predictTime;
	bool running;
	
	do
	{
		std::cout << "Type 1 to Predict Time, Type 2 to Predict Temperature: ";
		input = validateInput(1,2);
		
		input == 1 ? predictTime = true : predictTime = false;
		input = 0;
		
		if(predictTime == false)
		{
			std::cout << "Enter the time (0-23): ";
			int newX = validateInput(0,23);
			double predictedY = slope * newX + xIntercept; // y = mx + b
			std::cout << "Temperature = " << predictedY << std::endl;
		}
		else
		{
			std::cout << "Enter the temperature in celcius: ";
			double newY;
			std::cin >> newY;
			
			double predictedX = (newY - xIntercept) / slope;
			
			predictedX > 0 && predictedX < 23 ? std::cout << "Time = " << predictedX : std::cout << "TIME IS LOWER THAN 0, OR ABOVE 23";
		}
		
		std::cout << "\nWould you like to predict another value (Type 1 if yes)?: ";
		std::cin >> input;
		
		running = (input != 1 ?  false : true);
		std::cout << "------------------\n";
	}while(running);
	
	std::cout << "ENDING PROGRAM";
	
	getch();
	return 0;
}

int validateInput(int lowest, int highest)
{
	int input;
	
	do
	{
		std::cin >> input;
		input < lowest || input > highest ? std::cout << "Please input a number from " << lowest << "-" << highest << ":" : std::cout << "";
	}while(input < lowest || input > highest);
		
	return input;
}