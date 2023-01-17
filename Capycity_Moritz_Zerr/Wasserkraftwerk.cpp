

#include "Building.h"
#include "Wasserkraftwerk.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Wasserkraftwerk::Wasserkraftwerk() :Building("Wasserkraftwerk", 100, 150) {
    matMap.insert(make_pair(new Holz, 1));
    matMap.insert(make_pair(new Metall, 5));
    matMap.insert(make_pair(new Kunststoff, 3));
}