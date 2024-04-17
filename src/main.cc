
#include "./algorithm/ChargeEstimation.h"
#include "./algorithm/PowerExchangeDetection.h"
#include "./algorithm/AlgorithmManager.h"
#include "./asdk/generic/ErrorCodes.h"

#include "./communication/CommunicationInterface.h"
#include "./communication/OpenSearchClient.h"
#include "./communication/http/CURLHTTPClient.h"
#include "./communication/parsing/JSONDataBodyParser.h"

#include "./util/uuid.h"

using namespace algorithm;
using namespace asdk::generic;
using namespace communication;
using namespace communication::parsing;
using namespace std;

/**
 * Programme d'entrée.
*/
int main()
{   
// Créer les instances nécessaire à l'éxécution
    // Créer le AlgorithmDispatcher
    auto managerAlgo = make_shared<AlgorithmManager>();

    // Créer les instances de parsing
    auto jsonParser = make_shared<JSONDataBodyParser>();
    
    // Créer le client HTTP
    auto httpClient  = make_shared<CURLHTTPClient>(jsonParser);
    
    // Créer le client OpenSearch
    std::string domain = "https://search-silkroad-test-cq3gzgphhaaiivvm7zua2fhaue.aos.ca-central-1.on.aws";
    auto searchEngine = make_shared<OpenSearchClient>(httpClient, domain, uuid::generate_uuid_v4);
    // Créer les algorithmes nécessaires
    auto chargeEstimation = make_shared<ChargeEstimation>(searchEngine);
    auto powerExchange = make_shared<PowerExchangeDetection>(searchEngine);

    // Créer l'interface de communication 
    auto interfaceCommunication = make_shared<CommunicationInterface>(searchEngine, managerAlgo);


// Configuration
    std::string topicPowerExchange = "v1/verdant/+/+/+/chargingEvent";
    managerAlgo->addAlgorithm(topicPowerExchange, powerExchange);

    std::string topicChargeEstimation = "v1/verdant/+/+/+/deviceStatus";
    managerAlgo->addAlgorithm(topicPowerExchange, powerExchange);

// Lancer l'éxécution
    AWLEStatus status;
    std::string data = "";
    interfaceCommunication->handleIncomingMessage(data, status);

// TODO manage status

// Terminer l'appel lambda
    return 0;
}