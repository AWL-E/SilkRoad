#ifndef _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_
#define _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_

#include "AlgorithmInterface.h"

namespace algorithm {

using asdk::generic::AWLEStatus;

class DatabaseManager2 {
public:
  DatabaseManager2() = default;
  ~DatabaseManager2() = default;

  struct DevicesInfo {
    uint16_t id;
    float latitude;
    float longitude;
  };

  std::vector<DevicesInfo> getDeviceInfo() {

    std::vector<DevicesInfo> devices = {
        {1, 10.54, 20.97}, {2, 60.24, 80.46}, {3, 100.03, 120.38}};
    // Code to fetch data from the databases
    return devices;
  }
};

/** 
 * Algorithme qui permet d'identifier quel RX est chargé par quel TX
 */
class PowerExchangeDetection : public AlgorithmInterface {

public:
  explicit PowerExchangeDetection(std::shared_ptr<communication::OpenSearchInterface> f_searchEngine);
  ~PowerExchangeDetection() = default;

  void prepare(AWLEStatus &status) override;
  void execute(AWLEStatus &status) override;
  void complete(AWLEStatus &status) override;

private:
  float calculateDistance(const DatabaseManager2::DevicesInfo &tx,
                          const DatabaseManager2::DevicesInfo &rx);
  DatabaseManager2::DevicesInfo getDeviceID(uint16_t id);

  std::unique_ptr<DatabaseManager2> db;
  std::vector<DatabaseManager2::DevicesInfo> rxDevicesInfo;

  DatabaseManager2::DevicesInfo txInputInfo = {4, 32.22, 43.65};
  int32_t closestId = -1;
};

} // namespace algorithm

#endif // _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_