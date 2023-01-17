

#include "Building.h"
#include "Windkraftwerk.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Windkraftwerk::Windkraftwerk() :Building("Windkraftwerk", 150, { Holz(),Metall(),Kunststoff(),Kunststoff(),Kunststoff() }) {}