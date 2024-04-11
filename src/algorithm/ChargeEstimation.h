#ifndef _SILKROAD_ALGORITHM_CHARGEESTIMATION_H_
#define _SILKROAD_ALGORITHM_CHARGEESTIMATION_H_

#include "AlgorithmInterface.h"
#include "../communication/OpenSearchInterface.h"

static constexpr int MAX_BATTERY_CURRENT = 100;

namespace algorithm {
using asdk::generic::AWLEStatus;

struct DevicesInfo {
  int32_t id;
  float latitude = 0;
  float longitude = 0;
  float current = 0;
  float voltage = 0;
  float lastBatteryCheckpoint = 0;
  float timestamp = 0;
};

/**
 * Fausse classe qui abstrait le comportement de la base de données.
*/
class DatabaseManager {
public:
  DatabaseManager() = default;
  ~DatabaseManager() = default;

  std::vector<DevicesInfo> getBatteryInfo(uint16_t id) {
    std::vector<DevicesInfo> batInfoBatch;
    std::vector<DevicesInfo> deviceBatteryInfos = {
        {1, 10.54, 20.97, 0.2, 50, 80,0.5},    {1, 60.24, 80.46, 0.6, 60, 80,0.6},
        {1, 100.03, 120.38, 0.7, 70, 80,0.7},  {1, 140.12, 160.45, 0.8, 80, 80,0.8},
        {1, 180.34, 200.56, 0.9, 90, 80,0.9},  {1, 220.45, 240.67, 1.0, 100, 80,1.0},
        {1, 260.56, 280.78, 1.1, 110, 80,1.1}, {1, 300.67, 320.89, 1.2, 120, 80,1.2},
        {1, 340.78, 360.90, 3.3, 130, 80,1.3}, {1, 380.89, 400.12, 1.4, 140, 80,1.4}};

    for (auto const &batInfo : deviceBatteryInfos) {
      if (batInfo.id == id) {
        batInfoBatch.push_back(batInfo);
      }
    }
    return batInfoBatch;
  }
};

/**
 * Algorithme qui estime la charge d'une batterie à l'aide du comptage de coulomb.
*/
class ChargeEstimation : public AlgorithmInterface {

public:
  explicit ChargeEstimation(std::shared_ptr<communication::OpenSearchInterface> f_searchEngine);
  ~ChargeEstimation() = default;

  void prepare(AWLEStatus &status) override;
  void execute(AWLEStatus &status) override;
  void complete(AWLEStatus &status) override;

private:
  float calculateCharge();

  std::unique_ptr<DatabaseManager> db;
  std::vector<DevicesInfo> batteryInfo;

  float lastBatteryCheckpoint = -1;
  float remainingChargePercentage = -1;
};
} // namespace algorithm

#endif // _SILKROAD_ALGORITHM_CHARGEESTIMATION_H_