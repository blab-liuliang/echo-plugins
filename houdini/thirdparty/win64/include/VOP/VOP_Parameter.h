/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * NAME:	VOP Library (C++)
 *
 */

#ifndef __VOP_Parameter_h__
#define __VOP_Parameter_h__

#include "VOP_API.h"
#include "VOP_ParameterBase.h"
#include <CH/CH_ExprLanguage.h>

class PI_EditScriptedParm;

class VOP_API VOP_Parameter : public VOP_ParameterBase
{
public:
    static OP_Node		*myConstructor(OP_Network *net,
					       const char *name,
					       OP_Operator *entry);
    static PRM_Template		*buildTemplates(VOP_Language *language);
    static PRM_Template		*getObsolete(VOP_Language *language);

    virtual void		 initializeNode();

    // Get the parm block information that will go in the dialog script
    // for our VOPNET.
    virtual void		 getParameterDeclaration(UT_String &parmdecl,
					    const VOP_Language *language,
					    const VOP_CodeGenContext &context);
    virtual void		 getParameterComment(UT_String &parm_comment,
					    const VOP_Language *language,
					    const VOP_CodeGenContext &context);
    virtual void		 getParameterBlock(UT_String &parmstr,
					    const char *shader_contexts);
    // Get the pragmas that define the UI for the parameter.
    virtual void		 getPragmas(UT_String &pragmastr,
					    const VOP_CodeGenContext &context);

    virtual bool		 getParmConstantString(const char *parmname,
					    const VOP_TypeInfo &type_info,
					       UT_String &str,
					       bool expand_string,
					       const VOP_Language *language=0);

    virtual const char		*inputLabel(unsigned idx) const;

    virtual void		 setPARMNAME(const UT_String &str);
    void			 setPARMLABEL(const UT_String &str);
    virtual void		 setPARMTYPEINDEX(int type);
    virtual void		 setPARMSCOPE(const char *scope);
    virtual void		 setPARMSTORAGE(int type);
    void			 setPARMSTRINGTYPE(const char *style);
    void			 setPARMOPFILTER(const char *filter);

    virtual void		 PARMSCOPE(UT_String &str) const;
    virtual void		 PARMACCESS(UT_String &str) const;
    virtual void		 PARMNAME(UT_String &str) const;
    virtual void		 PARMPREFIX(UT_String &str) const;
    virtual void		 PARMPOSTFIX(UT_String &str) const;
    virtual void		 PARMLABEL(UT_String &str) const;
    virtual int			 PARMTYPEINDEX() const;
    virtual void		 PARMTYPENAME(UT_String &type_name) const;
    virtual void		 PARMMENUOPTION(UT_String &menu_option) const;

    virtual bool		 isParmVisible() const;
    virtual void		 copySettingsFrom(VOP_ParmGenerator *pvop);
    virtual void		 copyDefaultValuesFrom(
				    const PI_EditScriptedParm *parm);

protected:
	     VOP_Parameter(OP_Network *parent, const char *name,
		           OP_Operator *entry);
    virtual ~VOP_Parameter();

    virtual bool	 	 updateParmsFlags();
    
    // Override cook method just so we can set our warnings properly.
    void			 PARMCOMMENT(UT_String &parmcomment) const;
    virtual bool		 USEASPARMDEFINER() const;
    virtual bool		 USEOWNEXPORTCONTEXT() const;
    virtual bool		 SHOULDHAVECORRESPONDINGCONNECTOR() const;
    virtual int			 UNIFORM() const;
    virtual int			 USEBOUND() const;
    virtual int			 EXPORTPARM() const;
    virtual void		 EXPORTSHADERCONTEXTS(
					UT_StringArray &context_names) const;
    using VOP_ParameterBase::EXPORTSHADERCONTEXTS;
    virtual void		 MENUCHOICES(UT_String &str) const;
    virtual void		 MENUSCRIPT(UT_String &str) const;
    virtual CH_ScriptLanguage	 MENUSCRIPTLANGUAGE() const;
    void			 CALLBACKSTR(UT_String &str) const;
    void			 HELPTEXTSTR(UT_String &str) const;
    void			 TAGS(UT_JSONValueMap &map) const;
    int				 INVISIBLE() const;
    int				 JOINNEXT() const;
    int				 SHOWLABEL() const;
    int				 IRANGE(int index) const;
    float			 FRANGE(int index) const;

    virtual bool		 needsInput(void);

    // True if the node defines a node parameter UI (eg, on a SHOP); 
    // otherwise, returns false (eg, if this parm node refers to a method arg).
    bool			 definesParmUI() const;

    // Build the code to be output when useBound() is true but the parameter
    // is not actually bound:
    virtual void		 getUnboundCode(UT_String &codestr,
				    const VOP_CodeGenContext &context);

    virtual void	 getParmDeclarationCode(UT_String &parm_decl,
			    const VOP_CodeGenContext &codegen_ctx,
			    const VOP_Language *language=NULL,
			    bool export_parms=false);

    // Determines based on the parm index if the PARMNAME may be changed
    // when this parm is changed.
    virtual bool		 getParmCanAffectParmName(int pidx) const;

    virtual void		 getInputTypeInfoSubclass(
					VOP_TypeInfo &type_info, int idx);
    virtual void		 getAllowedInputTypesSubclass(unsigned idx,
					VOP_VopTypeArray &voptypes);
    virtual bool		 shouldCheckTimeDependence() const;

private:
    bool			 allowMenu(int parmtype) const;

    // Store the indices of the parameters that can affect the cached parameter
    // name.
    static int			 theParmNameParmIndex;
    static int			 theParmPrefixParmIndex;
    static int			 theParmPostfixParmIndex;
    static int			 theParmTypeParmIndex;
};

#endif
