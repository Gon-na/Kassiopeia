#ifndef KGPLANARCIRCLE_HH_
#define KGPLANARCIRCLE_HH_

#include "KGPlanarClosedPath.hh"

namespace KGeoBag
{

class KGPlanarCircle : public KGPlanarClosedPath
{
  public:
    KGPlanarCircle();
    KGPlanarCircle(const KGPlanarCircle& aCopy);
    KGPlanarCircle(const katrin::KTwoVector& aCentroid, const double& aRadius, const unsigned int aCount = 32);
    KGPlanarCircle(const double& anX, const double& aY, const double& aRadius, const unsigned int aCount = 32);
    ~KGPlanarCircle() override;

    static std::string Name()
    {
        return "circle";
    }

    KGPlanarCircle* Clone() const override;
    void CopyFrom(const KGPlanarCircle& aCopy);

  public:
    void Centroid(const katrin::KTwoVector& aStart);
    void X(const double& aValue);
    void Y(const double& aValue);
    void Radius(const double& aValue);
    void MeshCount(const unsigned int& aCount);

    const katrin::KTwoVector& Centroid() const override;
    const double& X() const;
    const double& Y() const;
    const double& Radius() const;
    const unsigned int& MeshCount() const;

    const double& Length() const override;
    const katrin::KTwoVector& Anchor() const override;

  public:
    katrin::KTwoVector At(const double& aLength) const override;
    katrin::KTwoVector Point(const katrin::KTwoVector& aQuery) const override;
    katrin::KTwoVector Normal(const katrin::KTwoVector& aQuery) const override;
    bool Above(const katrin::KTwoVector& aQuery) const override;

  private:
    katrin::KTwoVector fCentroid;
    double fRadius;
    unsigned int fMeshCount;

    mutable double fLength;
    mutable katrin::KTwoVector fAnchor;

    void Initialize() const;
    mutable bool fInitialized;
};
}  // namespace KGeoBag

#endif
