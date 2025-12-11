#include <iostream>
#include <vector>
#include <numeric> 
#include <algorithm>

class Dataset {
private:
	std::vector<double> observations; 
	double mean;
	double median;
public:
	Dataset(const std::vector<double>& data) : observations(data) {}

	double calculateMean(){
		double sum = std::accumulate(observations.begin(), observations.end(), 0.0);

		int n = observations.size();

		if (n == 0) {
			mean = 0.0;
			return 0.0;
		}

		mean = sum / n;

		return mean;
	}
	double calculateMedian(){
		int n = observations.size();
		
		std::sort(observations.begin(), observations.end());
		
		if (n % 2 != 0) {
			median = observations[n/2];
			return median;	
		} else if (n == 0) {
			median = 0.0;
			return 0.0;
		}
		

		int lowerIndex = (int)n / 2;
		
		double lowerHalfObservation = observations[lowerIndex -1];
		double higherHalfObservation = observations[lowerIndex];
		
		median = (lowerHalfObservation + higherHalfObservation)/2.0;

		return median;

	}
};


int main (){
	Dataset dataset({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	std::cout << "Calculated Mean: " << dataset.calculateMean() << "\n";
	std::cout << "Calculated Median: " << dataset.calculateMedian() << "\n";

	return 0;
}
