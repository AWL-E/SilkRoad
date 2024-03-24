#ifndef _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_
#define _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_

#include "AlgorithmInterface.h"

namespace algorithm {

using asdk::generic::AWLEStatus;

class DatabaseManager {
public:
  DatabaseManager() = default;
  ~DatabaseManager() = default;

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

class PowerExchangeDetection : public AlgorithmInterface {

public:
  PowerExchangeDetection(/*std::unique_ptr<DatabaseManager> db_f*/) =
      default; //: db(std::move(db_f)) {};
  ~PowerExchangeDetection() = default;

  void prepare(AWLEStatus &status) override;
  void execute(AWLEStatus &status) override;
  void complete(AWLEStatus &status) override;

private:
  float calculateDistance(const DatabaseManager::DevicesInfo &tx,
                          const DatabaseManager::DevicesInfo &rx);
  DatabaseManager::DevicesInfo getDeviceID(uint16_t id);

  std::unique_ptr<DatabaseManager> db;
  std::vector<DatabaseManager::DevicesInfo> rxDevicesInfo;

  DatabaseManager::DevicesInfo txInputInfo = {4, 32.22, 43.65};
  int32_t closestId = -1;
};

} // namespace algorithm

#endif // _SILKROAD_ALGORITHM_POWEREXCHANGEDETECTION_H_