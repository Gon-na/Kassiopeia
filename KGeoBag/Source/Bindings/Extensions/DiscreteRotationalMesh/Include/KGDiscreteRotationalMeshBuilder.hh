#ifndef KGDISCRETEROTATIONALMESHBUILDER_HH_
#define KGDISCRETEROTATIONALMESHBUILDER_HH_

#include "KGDiscreteRotationalMesh.hh"
#include "KGBindingsMessage.hh"

namespace KGeoBag
{

class KGDiscreteRotationalMeshAttributor : public katrin::KTagged, public KGDiscreteRotationalMeshData
{
  public:
    KGDiscreteRotationalMeshAttributor();
    ~KGDiscreteRotationalMeshAttributor() override;

  public:
    void AddSurface(KGSurface* aSurface);
    void AddSpace(KGSpace* aSpace);

  private:
    std::vector<KGSurface*> fSurfaces;
    std::vector<KGSpace*> fSpaces;

  public:
    void SetAxialAngle(double d)
    {
        fAxialAngle = d;
    }
    void SetAxialCount(int i)
    {
        fAxialCount = i;
    }

  private:
    double fAxialAngle;
    int fAxialCount;
};

}  // namespace KGeoBag

#include "KComplexElement.hh"

namespace katrin
{

typedef KComplexElement<KGeoBag::KGDiscreteRotationalMeshAttributor> KGDiscreteRotationalMeshBuilder;

template<> inline bool KGDiscreteRotationalMeshBuilder::AddAttribute(KContainer* aContainer)
{
    using namespace std;
    using namespace KGeoBag;

    if (aContainer->GetName() == "name") {
        fObject->SetName(aContainer->AsString());
        return true;
    }
    if (aContainer->GetName() == "angle") {
        aContainer->CopyTo(fObject, &KGDiscreteRotationalMeshAttributor::SetAxialAngle);
        return true;
    }
    if (aContainer->GetName() == "count") {
        aContainer->CopyTo(fObject, &KGDiscreteRotationalMeshAttributor::SetAxialCount);
        return true;
    }
    if (aContainer->GetName() == "surfaces") {
        vector<KGSurface*> tSurfaces = KGInterface::GetInstance()->RetrieveSurfaces(aContainer->AsString());
        vector<KGSurface*>::iterator tSurfaceIt;
        KGSurface* tSurface;

        if (tSurfaces.size() == 0) {
            bindmsg(eWarning) << "no surfaces found for specifier <" << aContainer->AsString() << ">" << eom;
            return true;
        }

        for (tSurfaceIt = tSurfaces.begin(); tSurfaceIt != tSurfaces.end(); tSurfaceIt++) {
            tSurface = *tSurfaceIt;
            fObject->AddSurface(tSurface);
        }
        return true;
    }
    if (aContainer->GetName() == "spaces") {
        vector<KGSpace*> tSpaces = KGInterface::GetInstance()->RetrieveSpaces(aContainer->AsString());
        vector<KGSpace*>::iterator tSpaceIt;
        KGSpace* tSpace;

        if (tSpaces.size() == 0) {
            bindmsg(eWarning) << "no spaces found for specifier <" << aContainer->AsString() << ">" << eom;
            return true;
        }

        for (tSpaceIt = tSpaces.begin(); tSpaceIt != tSpaces.end(); tSpaceIt++) {
            tSpace = *tSpaceIt;
            fObject->AddSpace(tSpace);
        }
        return true;
    }
    return false;
}

}  // namespace katrin

#endif
