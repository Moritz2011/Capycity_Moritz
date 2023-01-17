

#include "Building.h"
#include "Leer.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Leer::Leer() :Building("Leer", 0, 0) {
    matMap.insert(make_pair(new Holz, 0));
    matMap.insert(make_pair(new Metall, 0));
    matMap.insert(make_pair(new Kunststoff, 0));
}