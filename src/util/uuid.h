#include <random>
#include <sstream>

/**
 * Code pris à l'adresse: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
*/

/**
 * Classe qui permet de générer des identifiants uniques. 
 */
namespace uuid {
    std::string generate_uuid_v4();
}