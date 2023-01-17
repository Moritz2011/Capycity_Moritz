

#include "Building.h"
#include "Solarpanele.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Solarpanele::Solarpanele() :Building("Solarpanele", 100, { Metall(),Metall(),Metall(),Kunststoff(),Kunststoff() }) {}