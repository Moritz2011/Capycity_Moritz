

#include "Building.h"
#include "Solarpanele.h"

#include <string>
#include "Holz.h"
#include "Metall.h"
#include "Kunststoff.h"

using namespace std;


Solarpanele::Solarpanele() :Building("Solarpanele", 100, 80) {
    matMap.insert(make_pair(new Holz, 1));
    matMap.insert(make_pair(new Metall, 2));
    matMap.insert(make_pair(new Kunststoff, 5));
}