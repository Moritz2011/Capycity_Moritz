

#include "Building.h"
#include "Wasserkraftwerk.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Wasserkraftwerk::Wasserkraftwerk() :Building("Wasserkraftwerk", 100, { Holz(),Holz(),Metall(),Kunststoff() }) {}