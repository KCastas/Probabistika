#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric> 
#include <algorithm>

class Dataset {
private:
	std::vector<double> observations; 
	bool isSample;

	// Measures of Central Tendency
	double mean;
	double median;
	std::vector<double> mode;

  // Measures of Location

  // Measures of Dispersion
  double range;
  double meanAbsoluteDeviation;
  double variance;
  double standardDeviation;
  double cv; // Coefficient of Variation

public:
	Dataset(const std::vector<double>& data, const bool is_sample) : observations(data), isSample(is_sample){}
	
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
		
    std::vector<double> sortedObs = observations;
		std::sort(sortedObs.begin(), sortedObs.end());
		
		if (n % 2 != 0) {
			median = observations[n/2];
			return median;	
		} else if (n == 0) {
			median = 0.0;
			return 0.0;
		}
		

		int lowerIndex = (int)n / 2;
		
		double lowerHalfObservation = sortedObs[lowerIndex -1];
		double higherHalfObservation = sortedObs[lowerIndex];
		
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

  // Calculations for Measures of Location


  // Calculations for Measures of Dispersion
  double calculateRange(){
    if (observations.empty()) {
      range = 0.0;
      return 0.0;
    }

    double minVal = *std::min_element(observations.begin(), observations.end());
    double maxVal = *std::max_element(observations.begin(), observations.end());

    range = maxVal - minVal; 
    return range;
  }

  double calculateMeanAbsoluteDeviation(){
    int n = observations.size(); 

    if (n == 0){
      meanAbsoluteDeviation = 0; 
      return meanAbsoluteDeviation;
    }

    calculateMean();
    double absoluteDevSum = 0;

    for (double obs : observations) {
      double deviation = obs - mean; 
      absoluteDevSum += std::abs(deviation);
    }

    meanAbsoluteDeviation = absoluteDevSum / n; 
    
    return meanAbsoluteDeviation;
  }

  double calculateVariance(){
    int n = observations.size();

    if (n == 0){
      variance = 0;
      return variance;
    }

    calculateMean();
    double squaredDevSum = 0;

    for (double obs : observations) {
      double deviation = obs - mean;
      squaredDevSum += std::pow(deviation, 2);
    }

    if (isSample){
      variance = squaredDevSum/(n - 1);
    } else{
      variance = squaredDevSum / n;
    }

    return variance;
  }

  double calculateStandardDeviation(){
    calculateVariance(); 
    
    standardDeviation = std::sqrt(variance);
    return standardDeviation;
  }

  double calculateCV(){
    calculateStandardDeviation();

    if (standardDeviation == 0){
      cv = 0;
      return cv;
    }

    cv = (1.0 * standardDeviation / mean) * 100;
    return cv;
  }
};

int main (){
	Dataset dataset({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 2.0, 3.0, 3.0,}, true);

	std::cout << "Calculated Mean: " << dataset.calculateMean() << "\n";
	std::cout << "Calculated Median: " << dataset.calculateMedian() << "\n";
	dataset.printModes();
  std::cout << "Calculated Range: " << dataset.calculateRange() << "\n";
  std::cout << "Calculated Mean Absolute Deviation: " << dataset.calculateMeanAbsoluteDeviation() << "\n";
  std::cout << "Calculated Variance: " << dataset.calculateVariance() << "\n";
  std::cout << "Calculated Standard Deviation: " << dataset.calculateStandardDeviation() << "\n";
  std::cout << "Calculated Coefficient of Variation: " << dataset.calculateCV() << "\n";

	return 0;
}
