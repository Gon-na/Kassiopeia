#include "KSTrajIntegratorRK65Builder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSTrajIntegratorRK65Builder::~KComplexElement() = default;

STATICINT sKSTrajIntegratorRK65Structure = KSTrajIntegratorRK65Builder::Attribute<std::string>("name");

STATICINT sToolboxKSTrajIntegratorRK65 = KSRootBuilder::ComplexElement<KSTrajIntegratorRK65>("kstraj_integrator_rk65");

}  // namespace katrin
