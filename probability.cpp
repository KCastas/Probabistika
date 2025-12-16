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

    // Simplified Example465try7
    static double bayes(double pK, double pA, double pBgivenA, double pBgivenK){
      double pKgivenB = (pK * pBgivenK) / (pK * pBgivenK + pA * pBgivenA); 

      return pKgivenB;
    }

    static double bayes(double pS2, double pEgivenS2, double pS1, double pEgivenS1, double pS3, double pEgivenS3){
      double pS2givenE = (pS2 * pEgivenS2) / (pS1 * pEgivenS1 + pS2 * pEgivenS2 + pS3 * pEgivenS3);

      return pS2givenE;
    };
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