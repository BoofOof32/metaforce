#ifndef __DNAMP1_HPP__
#define __DNAMP1_HPP__

#include "../DNACommon/DNACommon.hpp"
#include "PAK.hpp"

namespace Retro
{
namespace DNAMP1
{

extern LogVisor::LogModule Log;

/* MP1-specific, one-shot PAK traversal/extraction class */
class PAKBridge
{
    HECL::Database::Project& m_project;
    const NOD::DiscBase::IPartition::Node& m_node;
    PAK m_pak;
public:
    PAKBridge(HECL::Database::Project& project, const NOD::DiscBase::IPartition::Node& node);
    static ResExtractor LookupExtractor(const PAK::Entry& entry);
    const std::string& getName() const {return m_node.getName();}
    HECL::SystemString getLevelString() const;

    typedef PAK PAKType;
    inline const PAKType& getPAK() const {return m_pak;}
    inline const NOD::DiscBase::IPartition::Node& getNode() const {return m_node;}
};

}
}

#endif // __DNAMP1_HPP__
