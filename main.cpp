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
		double sum = std::accumulate(observations.begin(), observations.end(), 0,0);

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

		
		if (n % 2 != 0) {
			median = observations[n/2];
			return median;	
		} else if (n == 0) {
			median = 0.0;
			return 0.0;
		}
		
		std::sort(observations.begin(), observations.end());
		int lowerindex = (int)n / 2;
		
		lowerHalfObservation = observations[lowerIndex];
		higherHalfObservation = observations[lowerIndex + 1];
		
		median = (lowerHalfObservation + higherHalfObservation)/2.0;

		return median;

	}
};
