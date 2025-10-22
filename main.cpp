#include <iostream>
#include <cmath>
#include <conio.h>

#define X 0
#define Y 1
#define Z 2

struct TemperatureData
{
	double temperature;
	int hour;
	int day;
	std::string month;
};

double distance(double t1, double t2, int h1, int h2, int d1, int d2)
{
	return sqrt(pow(t1 - t2, 2) + pow(h1 - h2, 2)+ pow(d1 - d2, 2));
}

int validateInput(int lowest, int highest);
int askInput();

void linearRegression(bool &running);
void multipleLinearRegression(bool &running);
void knnModel(bool &running);

int main()
{
	bool running = true;
	
	std::cout << "***********************************\n";
	std::cout << "   TEMPERATURE PREDICTER PROGRAM\n";
	std::cout << "***********************************\n";

	
	// 	Ask what MLM the user would like to use
	do
	{
		switch(askInput())
		{
			case 1: // LINEAR REGRESSION MODEL
				std::cout << "=-=-=-=-=-=-=-=-=\n";
				linearRegression(running);
				break;
			case 2: // MULTIPLE LINEAR REGRESSION MODEL
				std::cout << "=-=-=-=-=-=-=-=-=\n";
				multipleLinearRegression(running);
				break;
			case 3: // KNN MODEL
				std::cout << "=-=-=-=-=-=-=-=-=\n";
				knnModel(running);
				break;
		}	
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

int askInput()
{
	int input;
	
	do
	{
		std::cout << "What type of machine learning model would you like to use:\n1) Linear Regression Model\n2) Multiple Linear Regression Model\n3) KNN Model\nInput: ";
		std::cin >> input;
		input < 0 || input > 3 ? std::cout << input << " is not an option!\n" : std::cout << "";
	}while(input < 0 || input > 3);
		
	return input;
}

void linearRegression(bool &running)
{
	// ------------------------------------- DATA TRAINING -------------------------------------
	int input = 0;
	int sampleSize = 5;
	bool predictTime;
	
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
		numerator += (coords[X][i] - meanX) * (coords[Y][i] - meanY); // change of 
		denominator += (coords[X][i] - meanX) * (coords[X][i] - meanX);
	}
	double slope = numerator / denominator;
	double xIntercept = meanY - slope * meanX;
	// ------------------------------------- PREDICTING INPUT -------------------------------------
	std::cout << "Type 1 to Predict Time\nType 2 to Predict Temperature: ";
	input = validateInput(1,2);
	
	input == 1 ? predictTime = true : predictTime = false;
	input = 0;
	
	if(predictTime == false)
	{
		std::cout << "Enter the time (0-23): ";
		int newX = validateInput(0,23);
		double predictedY = slope * newX + xIntercept; // y = mx + b
		std::cout << "Temperature = " << predictedY;
	}
	else
	{
		std::cout << "Enter the temperature in celcius: ";
		double newY;
		std::cin >> newY;
		
		double predictedX = (newY - xIntercept) / slope;
		
		predictedX > 0 && predictedX < 23 ? std::cout << "Time = " << predictedX : std::cout << "***TIME IS LOWER THAN 0, OR ABOVE 23***";
	}
	
	
	// -------------------------- ASK USER TO PREDICT ANOTHER VALUE --------------------------
	std::cout << "\nWould you like to predict another value (Type 1 if yes)?: ";
	std::cin >> input;
	
	running = (input != 1 ?  false : true);
	std::cout << "------------------\n";
}

void multipleLinearRegression(bool &running)
{
	// code
}

void knnModel(bool &running)
{
	int input;
	// -------------------------- DATA TRAINING --------------------------
	TemperatureData dataset[] = 
	{
		{ 15.2,  6,  1,  "January" },
		{ 22.5, 14, 12, "February" },
		{ 18.9,  9, 20, "March" },
		{ 25.3, 13, 5,  "April" },
		{ 30.1, 15, 18, "May" },
		{ 35.0, 16, 22, "June" },
		{ 38.7, 14, 7,  "July" },
		{ 36.5, 17, 10, "August" },
		{ 28.4, 11, 25, "September" },
		{ 22.0, 10, 30, "October" },
		{ 16.8,  8, 19, "November" },
		{ 10.3,  7, 2,  "December" },
		{ 12.7,  5, 9,  "January" },
		{ 29.2, 12, 14, "June" },
		{ 19.4, 20, 28, "August" },
		{ 8.6,   3, 4,  "February" },
		{ 21.5, 18, 16, "April" },
		{ 33.0, 14, 21, "July" },
		{ 27.9, 13, 6,  "May" },
		{ 24.1, 17, 11, "September" },
		{ 13.0,  6, 27, "November" },
		{ 9.5,   2, 8,  "December" },
		{ 20.3, 19, 23, "October" },
		{ 17.2,  7, 15, "March" }
	};
	
	int sampleSize = sizeof(dataset) / sizeof(dataset[0]);
	
	// User input
	double temp, hour, day;
	
	std::cout << "Enter new location data:\n";
	std::cout << "Average temperature (C): ";
	std::cin >> temp;
	std::cout << "Hour (0-23): ";
	hour = validateInput(0,23);
	std::cout << "Day (1-31): ";
	day = validateInput(1,31);
	
	// Find the most similar (nearest) entry in dataset
	double minDist = 1e9; // 1 billion
	int bestMatch = -1;
	
	for (int i = 0; i < sampleSize; i++) 
	{
		double d = distance(temp, dataset[i].temperature, hour, dataset[i].hour, day, dataset[i].day);
		if (d < minDist) 
		{
			minDist = d;
			bestMatch = i;
		}
	}
	
	// Output prediction
	std::cout << "\nClosest match found in dataset:\n";
	std::cout << "Temperature: " << dataset[bestMatch].temperature << "C\n";
	std::cout << "Hour: " << dataset[bestMatch].hour << "h\n";
	std::cout << "Day: " << dataset[bestMatch].day << "d\n";
	std::cout << "Month: " << dataset[bestMatch].month << std::endl;
	std::cout << "\nPredicted Month: " << dataset[bestMatch].month << std::endl;
	
	// -------------------------- ASK USER TO PREDICT ANOTHER VALUE --------------------------
	std::cout << "\nWould you like to predict another value (Type 1 if yes)?: ";
	std::cin >> input;
	
	running = (input != 1 ?  false : true);
	std::cout << "------------------\n";
}