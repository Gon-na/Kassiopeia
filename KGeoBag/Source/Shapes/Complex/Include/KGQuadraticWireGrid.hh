#ifndef KGQUADRATICWIREGRID_DEF
#define KGQUADRATICWIREGRID_DEF

#include <stddef.h>
#include <vector>
#include <cmath>
#include <string>

#include "KGBoundary.hh"

namespace KGeoBag
{
  class KGQuadraticWireGrid : public KGBoundary
  {
    /*
      A class describing a wire grid with a flat section profile
    */
  public:
    KGQuadraticWireGrid() {}
    KGQuadraticWireGrid(double r,
			   double pitch,
		       double diameter,
		       unsigned int nDiscPerPitch,
		       bool outerCircle) : fR(r),
						 fPitch(pitch),
					     fDiameter(diameter),
					     fNDiscPerPitch(nDiscPerPitch),
					     fOuterCircle(outerCircle){}

    virtual ~KGQuadraticWireGrid() {}

    static std::string Name() { return "quadratric_wire_grid"; }

    virtual KGQuadraticWireGrid* Clone() const;

    virtual void Initialize() const {}

    bool ContainsPoint(const double* P) const;
    double DistanceTo(const double* P,
		      double* P_in=NULL,
		      double* P_norm=NULL) const;

    double GetLength() const;
    double Area() const;
    double Volume() const;

    void SetR (double d) { fR = d; }
    void SetPitch (double d) { fPitch = d; }
    void SetDiameter(double d) { fDiameter = d; }
    void SetNDiscPerPitch(unsigned int d) { fNDiscPerPitch = d; }
    void SetOuterCircle( bool b ) { fOuterCircle = b; }

    double GetR() const { return fR;}
    double GetPitch() const { return fPitch; }
    double GetDiameter() const { return fDiameter; }
    unsigned int GetNDiscPerPitch() const { return fNDiscPerPitch; }
    bool GetOuterCircle() const { return fOuterCircle; }

  private:

    double fR;
    double fPitch;
    double fDiameter;
    unsigned int fNDiscPerPitch;
    bool fOuterCircle;
  };
}

#endif /* KGQUDRATICRWIREGRID_DEF */