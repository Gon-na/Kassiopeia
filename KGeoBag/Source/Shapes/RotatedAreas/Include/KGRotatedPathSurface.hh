#ifndef KGROTATEDPATHSURFACE_HH_
#define KGROTATEDPATHSURFACE_HH_

#include "KGArea.hh"
#include "KGPlanarPath.hh"
#include "KGShapeMessage.hh"

#include "KThreeVector.hh"

#include <memory>

namespace KGeoBag
{

template<class XPathType> class KGRotatedPathSurface : public KGArea
{
  public:
    class Visitor
    {
      public:
        Visitor();
        virtual ~Visitor();

        virtual void VisitRotatedPathSurface(KGRotatedPathSurface* aRotatedPathSurface) = 0;
    };

  public:
    KGRotatedPathSurface() : KGArea(), fPath(new XPathType()), fSign(1.), fRotatedMeshCount(64)
    {
        CompilerCheck();
    }
    KGRotatedPathSurface(const KGRotatedPathSurface<XPathType>& aCopy) :
        KGArea(aCopy),
        fPath(aCopy.fPath),
        fSign(1.),
        fRotatedMeshCount(aCopy.fRotatedMeshCount)
    {}
    KGRotatedPathSurface(std::shared_ptr<XPathType> aPath) : KGArea(), fPath(aPath), fSign(1.), fRotatedMeshCount(64) {}
    ~KGRotatedPathSurface() override = default;

    static std::string Name()
    {
        return "rotated_" + XPathType::Name() + "_surface";
    }

  public:
    std::shared_ptr<XPathType>& Path()
    {
        return fPath;
    }
    const std::shared_ptr<XPathType>& Path() const
    {
        return fPath;
    }

    void Sign(const double& aSign)
    {
        fSign = aSign / fabs(aSign);
        return;
    }
    const double& Sign() const
    {
        return fSign;
    }

    void RotatedMeshCount(const unsigned int& aCount)
    {
        fRotatedMeshCount = aCount;
    }
    const unsigned int& RotatedMeshCount() const
    {
        return fRotatedMeshCount;
    }

  protected:
    mutable std::shared_ptr<XPathType> fPath;
    mutable double fSign;
    mutable unsigned int fRotatedMeshCount;

  public:
    void AreaInitialize() const override
    {
        return;
    }
    void AreaAccept(KGVisitor* aVisitor) override
    {
        shapemsg_debug("rotated path area named <" << GetName() << "> is receiving a visitor" << eom);
        auto* tRotatedPathSurfaceVisitor = dynamic_cast<typename KGRotatedPathSurface<XPathType>::Visitor*>(aVisitor);
        if (tRotatedPathSurfaceVisitor != nullptr) {
            shapemsg_debug("rotated path area named <" << GetName() << "> is accepting a visitor" << eom);
            tRotatedPathSurfaceVisitor->VisitRotatedPathSurface(this);
        }
        return;
    }
    bool AreaAbove(const katrin::KThreeVector& aPoint) const override
    {
        katrin::KTwoVector tZRPoint = aPoint.ProjectZR();
        bool tZRAbove = fPath->Above(tZRPoint);
        if ((tZRAbove == true) && (fSign > 0.)) {
            return true;
        }
        else {
            return false;
        }
    }
    katrin::KThreeVector AreaPoint(const katrin::KThreeVector& aPoint) const override
    {
        katrin::KTwoVector tZRPoint = aPoint.ProjectZR();
        katrin::KTwoVector tZRNearest = fPath->Point(tZRPoint);
        double tAngle = aPoint.AzimuthalAngle();
        return katrin::KThreeVector(cos(tAngle) * tZRNearest.R(), sin(tAngle) * tZRNearest.R(), tZRNearest.Z());
    }
    katrin::KThreeVector AreaNormal(const katrin::KThreeVector& aPoint) const override
    {
        katrin::KTwoVector tZRPoint = aPoint.ProjectZR();
        katrin::KTwoVector tZRNormal = fPath->Normal(tZRPoint);
        double tAngle = aPoint.AzimuthalAngle();
        return fSign * katrin::KThreeVector(cos(tAngle) * tZRNormal.R(), sin(tAngle) * tZRNormal.R(), tZRNormal.Z());
    }

  private:
    static KGPlanarPath* CompilerCheck()
    {
        XPathType* tPath = nullptr;
        return tPath;
    }
};

}  // namespace KGeoBag

#endif
