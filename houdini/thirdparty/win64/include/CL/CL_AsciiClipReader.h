/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 * 
 * NAME:        CL_AsciiClipReader.h
 *
 * COMMENTS:
 *	This class reads from .clip files.
 */

#ifndef __CL_AsciiClipReader_h__
#define __CL_AsciiClipReader_h__

#include "CL_API.h"
#include "CL_ClipReader.h"

class UT_IStream;

class CL_API CL_AsciiClipReader : public CL_ClipReader
{
public:
    CL_AsciiClipReader() {}
    virtual ~CL_AsciiClipReader() {}

    virtual bool readClip(const char *file_name, CL_Clip &clip);

    // The file name is passed in so it can use it in error mesages.
    bool readClip(UT_IStream &is, CL_Clip &clip, const char *filename);
};

#endif
