#include "PowerExchangeDetection.h"
#include <cmath>
#include <iostream>

namespace algorithm {

PowerExchangeDetection::PowerExchangeDetection(std::shared_ptr<communication::OpenSearchInterface> f_searchEngine): AlgorithmInterface(f_searchEngine) {}

void PowerExchangeDetection::prepare(AWLEStatus &status) {

  db = std::make_unique<DatabaseManager2>();

  rxDevicesInfo = db->getDeviceInfo();

  if (rxDevicesInfo.empty()) {
    status.set(asdk::generic::ErrorCodes::GENERIC);
    return;
  }
}

void PowerExchangeDetection::execute(AWLEStatus &status) {
  float closestDistance = std::numeric_limits<float>::max();
 

  for (const auto &rxDevice : rxDevicesInfo) {
    float distance = calculateDistance(txInputInfo, rxDevice);

    if (distance < closestDistance) {
      closestDistance = distance;
      closestId = rxDevice.id;
    }
  }

  if (closestId == -1) {
    status.set(asdk::generic::ErrorCodes::INVALID_ARGUMENT);
  }
}

void PowerExchangeDetection::complete(AWLEStatus &status) {

}

float PowerExchangeDetection::calculateDistance(
    const DatabaseManager2::DevicesInfo &tx,
    const DatabaseManager2::DevicesInfo &rx) {
  float txLatitude = tx.latitude;
  float txLongitude = tx.longitude;
  float rxLatitude = rx.latitude;
  float rxLongitude = rx.longitude;

  // Convert latitude and longitude from degrees to radians
  float txLatRad = txLatitude * M_PI / 180.0;
  float txLonRad = txLongitude * M_PI / 180.0;
  float rxLatRad = rxLatitude * M_PI / 180.0;
  float rxLonRad = rxLongitude * M_PI / 180.0;

  // Haversine formula
  float dlon = rxLonRad - txLonRad;
  float dlat = rxLatRad - txLatRad;
  float a = pow(sin(dlat / 2), 2) +
            cos(txLatRad) * cos(rxLatRad) * pow(sin(dlon / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  float distance = 6371 * c; // Earth radius is 6371 km

  return distance;
}



DatabaseManager2::DevicesInfo PowerExchangeDetection::getDeviceID(uint16_t id) {
  for (const auto &rxDevice : rxDevicesInfo) {
    if (rxDevice.id == id) {
      return rxDevice;
    }
  }

  return {0, 0, 0};
}
} // namespace algorithm
