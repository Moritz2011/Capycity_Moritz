

#include "Building.h"
#include "Windkraftwerk.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Windkraftwerk::Windkraftwerk() :Building("Windkraftwerk", 150, 200) {
    matMap.insert(make_pair(new Holz, 1));
    matMap.insert(make_pair(new Metall, 3));
    matMap.insert(make_pair(new Kunststoff, 2));
}