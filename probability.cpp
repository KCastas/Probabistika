#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class ProbabilityCalculator {
  public: 
    static double eventProbability(int favorableN, int N){
      return 1.0 * favorableN / N; 
    }

    static double complement(double pA){
      return 1.0 - pA;
    }

    static double intersection(double pA, double pBgivenA){
      return 1.0 * pA * pBgivenA;
    }

    static double unionProbability(double pA, double pB, double pIntersection){
      return (double)(pA + pB - pIntersection); 
    }

    // Independent Events
    static double unionProbability(double pA, double pB){
      return (double)(pA + pB);
    }


    static double bayes(double psB, double psAgivenB, const std::vector<std::pair<double, double>>& partitions){
      double numerator = 1.0 * psB * psAgivenB;
      
      double denominator = 0; 
      for (const auto& partition : partitions){
        double pBi = partition.first; 
        double pAgivenBi = partition.second;

        denominator += 1.0 * pBi * pAgivenBi;
      }

      if (denominator == 0){
        return 0;
      }

      double pBgivenA = numerator / denominator;

      return pBgivenA;
    }
};





// Implementation For Two INDEPENDENT Events
class ChanceExperiment {
  private:
    std::pair<std::string, double> elementaryEvents[2]; // string -> event,  double -> probability

  public:
    ChanceExperiment(std::pair<std::string, double> event1, std::pair<std::string, double> event2) {
      elementaryEvents[0] = event1;
      elementaryEvents[1] = event2;
    }

    // Event Actions
    double notOccuringProbability(std::string eventName){
      std::pair<std::string, double> event = {"", 0.0};

      for (std::pair<std::string, double> pair : elementaryEvents) {
        if (pair.first == eventName){
          event = pair;
          break;
        }
      }

      if (event.first.empty()){
        return 0.0;
      }

      return 1 - event.second;
    }
    
    double bothOccuringProbability(std::string eventName1, std::string eventName2){
      std::pair<std::string, double> event1 = {"", 0.0};
      std::pair<std::string, double> event2 = {"", 0.0};
      
      for (std::pair<std::string, double> pair : elementaryEvents) {
        if (pair.first == eventName1){
          event1 = pair;
        } else if (pair.first == eventName2){
          event2 = pair;
        }

        if (!event1.first.empty() && !event2.first.empty()){
          break;
        }
      }

      if (event1.first.empty() || event2.first.empty()){
        return 0.0;
      }

      return event1.second * event2.second; // only valid for 2 independed events
    }

    double eitherOccuringProbability(std::string eventName1, std::string eventName2){
      std::pair<std::string, double> event1 = {"", 0.0};
      std::pair<std::string, double> event2 = {"", 0.0};

      for (std::pair<std::string, double> pair : elementaryEvents) {
        if (pair.first == eventName1){
          event1 = pair;
        } else if (pair.first == eventName2){
          event2 = pair;
        }

        if (!event1.first.empty() && !event2.first.empty()){
          break;
        }
      }

      return event1.second + event2.second - bothOccuringProbability(eventName1, eventName2);
    }

    double exclusiveEitherOccuringProbability(std::string eventName1, std::string eventName2){
      return eitherOccuringProbability(eventName1, eventName2) - bothOccuringProbability(eventName1, eventName2);
    }
};

void main(){
  std::cout << "Hello";
}