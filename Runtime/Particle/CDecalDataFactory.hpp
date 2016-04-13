#ifndef __URDE_CDECALDATAFACTORY_HPP__
#define __URDE_CDECALDATAFACTORY_HPP__

#include "RetroTypes.hpp"
#include "CFactoryMgr.hpp"
#include "IObj.hpp"
#include "CToken.hpp"
#include "IOStreams.hpp"


namespace urde
{
struct SQuadDescr;
class CDecalDescription;
class CSimplePool;

class CDecalDataFactory
{
    static bool CreateDPSM(CDecalDescription* desc,CInputStream& in,CSimplePool* resPool);
    static CDecalDescription* CreateGeneratorDescription(CInputStream& in, CSimplePool* resPool);
    static void GetQuadDecalInfo(CInputStream& in, CSimplePool* resPool, FourCC clsId, SQuadDescr& quad);
public:
    static CDecalDescription* GetGeneratorDesc(CInputStream& in,CSimplePool* resPool);
};

CFactoryFnReturn FDecalDataFactory(const SObjectTag& tag, CInputStream& in, const CVParamTransfer& vparms);
}
#endif // __URDE_CDECALDATAFACTORY_HPP__
