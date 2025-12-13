#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric> 
#include <algorithm>

class Dataset {
private:
	std::vector<double> observations; 
	
	// Measures of Central Tendency
	double mean;
	double median;
	std::vector<double> mode;
public:
	Dataset(const std::vector<double>& data) : observations(data) {}
	
	// Calculations for Measures of Central Tendency
	double calculateMean(){
		int n = observations.size();

		if (n == 0) {
			mean = 0.0;
			return 0.0;
		}

		double sum = std::accumulate(observations.begin(), observations.end(), 0.0);

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

	std::vector<double> calculateMode(){
		int n = observations.size();
		
		if (n == 0){
			mode.clear();
			return mode;
		}

		std::unordered_map<double, int> freqMap;
		for (double obs : observations) {
			freqMap[obs]++;
		}

		int maxFreq = 0;
		for (const auto& freq: freqMap) {
			if (freq.second > maxFreq){
				maxFreq = freq.second;
			}
		}

		for (const auto& freq: freqMap) {
			if (freq.second == maxFreq){
				mode.push_back(freq.first);
			}
		}

		return mode;
	}

  void printModes(){
    calculateMode();
    int n = mode.size();

    if (n == 0){
      std::cout << "No mode\n"; 
      return;
    }

    std::cout << "Calculated modes: ";
    for (int i=0; i <= n -1; i++){
      std::cout << mode[i] << ", ";
    }

    std::cout << "\n";
  }
};


int main (){
	Dataset dataset({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2, 2, 3, 3,});

	std::cout << "Calculated Mean: " << dataset.calculateMean() << "\n";
	std::cout << "Calculated Median: " << dataset.calculateMedian() << "\n";
	dataset.printModes();

	return 0;
}
