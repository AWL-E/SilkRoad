#include "ChargeEstimation.h"
#include "../../build/src/ProtoMessages.pb.h"

namespace algorithm {

ChargeEstimation::ChargeEstimation(std::shared_ptr<communication::OpenSearchInterface> f_searchEngine): AlgorithmInterface(f_searchEngine) {}

void ChargeEstimation::prepare(AWLEStatus &status) {

  db = std::make_unique<DatabaseManager>();

  batteryInfo = db->getBatteryInfo(1);

  if (batteryInfo.empty()) {
    status.set(asdk::generic::ErrorCodes::GENERIC);
    return;
  }
  lastBatteryCheckpoint = batteryInfo.back().lastBatteryCheckpoint;
}

void ChargeEstimation::execute(AWLEStatus &status) {
   remainingChargePercentage = calculateCharge();
}
void ChargeEstimation::complete(AWLEStatus &status) {
    ProtoMessages::BatteryMessage msg;
    msg.set_batterypercentage(remainingChargePercentage);
}

float ChargeEstimation::calculateCharge() {
  auto remainingCharge = MAX_BATTERY_CURRENT * (lastBatteryCheckpoint/100);

  for (auto const &batInfo : batteryInfo) {
    if (batInfo.lastBatteryCheckpoint == lastBatteryCheckpoint)
      remainingCharge -= batInfo.current;
  }
    if(remainingCharge < 0)
    {
        remainingCharge = 0;
    }
    
    return remainingCharge/MAX_BATTERY_CURRENT * 100;
}
} // namespace algorithm