#ifndef KSGENPOSITIONFLUXTUBEBuilder_H_
#define KSGENPOSITIONFLUXTUBEBuilder_H_

#include "KComplexElement.hh"
#include "KSFieldFinder.h"
#include "KSGenPositionFluxTube.h"
#include "KToolbox.h"
#include "KGCore.hh"

using namespace Kassiopeia;
using namespace KGeoBag;
namespace katrin
{

typedef KComplexElement<KSGenPositionFluxTube> KSGenPositionFluxTubeBuilder;

template<> inline bool KSGenPositionFluxTubeBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "surface") {
        KGSurface* tSurface = KGInterface::GetInstance()->RetrieveSurface(aContainer->AsString());
        fObject->SetOrigin(tSurface->GetOrigin());
        fObject->SetXAxis(tSurface->GetXAxis());
        fObject->SetYAxis(tSurface->GetYAxis());
        fObject->SetZAxis(tSurface->GetZAxis());
        return true;
    }
    if (aContainer->GetName() == "space") {
        KGSpace* tSpace = KGInterface::GetInstance()->RetrieveSpace(aContainer->AsString());
        fObject->SetOrigin(tSpace->GetOrigin());
        fObject->SetXAxis(tSpace->GetXAxis());
        fObject->SetYAxis(tSpace->GetYAxis());
        fObject->SetZAxis(tSpace->GetZAxis());
        return true;
    }
    if (aContainer->GetName() == "phi") {
        fObject->SetPhiValue(KToolbox::GetInstance().Get<KSGenValue>(aContainer->AsString()));
        return true;
    }
    if (aContainer->GetName() == "z") {
        fObject->SetZValue(KToolbox::GetInstance().Get<KSGenValue>(aContainer->AsString()));
        return true;
    }
    if (aContainer->GetName() == "flux") {
        aContainer->CopyTo(fObject, &KSGenPositionFluxTube::SetFlux);
        return true;
    }
    if (aContainer->GetName() == "n_integration_step") {
        aContainer->CopyTo(fObject, &KSGenPositionFluxTube::SetNIntegrationSteps);
        return true;
    }
    if (aContainer->GetName() == "only_surface") {
        aContainer->CopyTo(fObject, &KSGenPositionFluxTube::SetOnlySurface);
        return true;
    }
    if (aContainer->GetName() == "magnetic_field_name") {
        fObject->AddMagneticField(getMagneticField(aContainer->AsString()));
        return true;
    }
    return false;
}

template<> inline bool KSGenPositionFluxTubeBuilder::AddElement(KContainer* aContainer)
{
    if (aContainer->GetName().substr(0, 3) == "phi") {
        aContainer->ReleaseTo(fObject, &KSGenPositionFluxTube::SetPhiValue);
        return true;
    }
    if (aContainer->GetName().substr(0, 1) == "z") {
        aContainer->ReleaseTo(fObject, &KSGenPositionFluxTube::SetZValue);
        return true;
    }
    return false;
}

}  // namespace katrin

#endif /* KSGENPOSITIONFLUXTUBEBuilder_H_ */
