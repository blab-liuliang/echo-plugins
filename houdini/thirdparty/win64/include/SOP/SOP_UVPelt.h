/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * NAME:	SOP library (C++)
 *
 * COMMENTS:	Pelt SOP
 */


#ifndef __SOP_UVPelt_h__
#define __SOP_UVPelt_h__

#include "SOP_API.h"
#include <GQ/GQ_Pelt.h>

#include "SOP_Node.h"

enum
{
    SOP_PELT_GROUP_INDEX = 0,
    SOP_PELT_TARGETTYPE_INDEX,
    SOP_PELT_OUTPUTTOGGLE_INDEX,
    SOP_PELT_OUTPUTGROUP_INDEX,
    SOP_PELT_SWITCHER_INDEX,
#define SOP_PELT_NUM_PELT_PARMS 4
    SOP_PELT_ITERATIONS_INDEX,
    SOP_PELT_SPRINGCONSTANT_INDEX,
    SOP_PELT_TENSION_INDEX,
    SOP_PELT_HINTPOLY_INDEX,
#define SOP_PELT_NUM_FRAME_PARMS 8
    SOP_PELT_FRAME_INDEX,
    SOP_PELT_UFROM_INDEX,
    SOP_PELT_VFROM_INDEX,
    SOP_PELT_USERANGE_INDEX,
    SOP_PELT_URANGE_INDEX,
    SOP_PELT_VRANGE_INDEX,
    SOP_PELT_ORIENTATION_INDEX,
    SOP_PELT_DENSITY_INDEX
};

class SOP_API SOP_UVPelt : public SOP_Node
{
public:
	     SOP_UVPelt(OP_Network *net, const char *name, OP_Operator *op);
    virtual ~SOP_UVPelt();

    virtual int			 isRefInput(unsigned int i) const;

    // This method is created so that it can be called by handles.  It only
    // cooks the input group of this SOP.  The geometry in this group is
    // the only geometry manipulated by this SOP.
    virtual OP_ERROR		 cookInputGroups(OP_Context &context, 
						int alone = 0);
    virtual bool		 updateParmsFlags();

    static PRM_Template		 myTemplateList[];
    static OP_Node		*myConstructor(OP_Network*, const char *,
							    OP_Operator *);

    void			 getFrame(int &numpoints, GQ_Pelt::FramePoint *&framepoints, int &metacachecount);

protected:
    virtual const char          *inputLabel(unsigned idx) const;

    // Method to cook geometry for the SOP
    virtual OP_ERROR		 cookMySop(OP_Context &context);

    void 			 pelt(OP_Context &context,
				      const GA_EdgeGroup *group,
				      const GEO_Face *frame,
				      GEO_Primitive *hint,
				      bool (*callback_func)(void *),
				      void *callback_data);

private:
    bool	OUTPUTTOGGLE()
		    { return evalInt(SOP_PELT_OUTPUTTOGGLE_INDEX, 0, 0) != 0; }
    void	OUTPUTGROUP(UT_String &str)
		    { return evalString(str, SOP_PELT_OUTPUTGROUP_INDEX, 0, 0); }
    int		TARGETTYPE()
		    { return evalInt(SOP_PELT_TARGETTYPE_INDEX, 0, 0); }
    int		ITERATIONS()
		    { return evalInt(SOP_PELT_ITERATIONS_INDEX, 0, 0); }
    float	SPRINGCONSTANT(fpreal t)
		    { return evalFloat(SOP_PELT_SPRINGCONSTANT_INDEX, 0, t); }
    int		HINTPOLY()
		    { return evalInt(SOP_PELT_HINTPOLY_INDEX, 0, 0); }
    int		UFROM()
		    { return evalInt(SOP_PELT_UFROM_INDEX, 0, 0); }
    int		VFROM()
		    { return evalInt(SOP_PELT_VFROM_INDEX, 0, 0); }
    bool	USERANGE()
		    { return evalInt(SOP_PELT_USERANGE_INDEX, 0, 0) != 0; }
    float	MINU(fpreal t)
		    { return evalFloat(SOP_PELT_URANGE_INDEX, 0, t); }
    float	MAXU(fpreal t)
		    { return evalFloat(SOP_PELT_URANGE_INDEX, 1, t); }
    float	MINV(fpreal t)
		    { return evalFloat(SOP_PELT_VRANGE_INDEX, 0, t); }
    float	MAXV(fpreal t)
		    { return evalFloat(SOP_PELT_VRANGE_INDEX, 1, t); }
    float	ORIENTATION()
		    { return evalFloat(SOP_PELT_ORIENTATION_INDEX, 0, 0); }

    // This is the group of geometry to be manipulated by this SOP and cooked
    // by the method "cookInputGroups".
    const GA_EdgeGroup		*myGroup;
    const GEO_Face		*myFrame;
    int				 myFrameMetaCacheCount;

    int				 myFramePointCount;
    GQ_Pelt::FramePoint		*myFramePoints;
};

#endif
