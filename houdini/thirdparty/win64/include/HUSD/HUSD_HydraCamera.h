/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * NAME:	HUSD_HydraCamera.h (HUSD Library, C++)
 *
 * COMMENTS:	Container for GT prim repr of a hydro geometry  prim (HdRprim)
 */
#ifndef HUSD_HydraCamera_h
#define HUSD_HydraCamera_h

#include <pxr/pxr.h>

#include "HUSD_API.h"
#include "HUSD_HydraPrim.h"

#include <SYS/SYS_Types.h>
#include <UT/UT_StringHolder.h>

class HUSD_Scene;

PXR_NAMESPACE_OPEN_SCOPE
class XUSD_HydraCamera;
class TfToken;
class SdfPath;
PXR_NAMESPACE_CLOSE_SCOPE

/// Container for hydra camera (hdSprim)
class HUSD_API HUSD_HydraCamera : public HUSD_HydraPrim
{
public:
	     HUSD_HydraCamera(PXR_NS::TfToken const& typeId,
			      PXR_NS::SdfPath const& primId,
			      HUSD_Scene &scene);
    virtual ~HUSD_HydraCamera();

    PXR_NS::XUSD_HydraCamera	*hydraCamera() const { return myHydraCamera; }

    HUSD_PARM(Aperture, fpreal);
    HUSD_PARM(AspectRatio, fpreal);
    HUSD_PARM(FocusDistance, fpreal);
    HUSD_PARM(FocalLength, fpreal);
    HUSD_PARM(FStop, fpreal);
    HUSD_PARM(NearClip, fpreal);
    HUSD_PARM(FarClip, fpreal);
    HUSD_PARM(Projection, UT_StringHolder);
    
private:
    fpreal	myAperture;
    fpreal	myAspectRatio;
    fpreal	myFocusDistance;
    fpreal	myFocalLength;
    fpreal	myFStop;
    fpreal	myNearClip;
    fpreal	myFarClip;
    UT_StringHolder myProjection;
    
    PXR_NS::XUSD_HydraCamera	*myHydraCamera;
};

#endif
