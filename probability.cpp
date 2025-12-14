#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>


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

int main(){

}