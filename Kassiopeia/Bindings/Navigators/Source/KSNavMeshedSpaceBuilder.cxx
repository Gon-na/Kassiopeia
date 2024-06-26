#include "KSNavMeshedSpaceBuilder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSNavMeshedSpaceBuilder::~KComplexElement() = default;

STATICINT sKSNavMeshedSpaceStructure = KSNavMeshedSpaceBuilder::Attribute<std::string>("name") +
                                       KSNavMeshedSpaceBuilder::Attribute<std::string>("octree_file") +
                                       KSNavMeshedSpaceBuilder::Attribute<bool>("enter_split") +
                                       KSNavMeshedSpaceBuilder::Attribute<bool>("exit_split") +
                                       KSNavMeshedSpaceBuilder::Attribute<bool>("fail_check") +
                                       KSNavMeshedSpaceBuilder::Attribute<std::string>("root_space") +
                                       KSNavMeshedSpaceBuilder::Attribute<unsigned int>("max_octree_depth") +
                                       KSNavMeshedSpaceBuilder::Attribute<double>("spatial_resolution") +
                                       KSNavMeshedSpaceBuilder::Attribute<unsigned int>("n_allowed_elements") +
                                       KSNavMeshedSpaceBuilder::Attribute<double>("absolute_tolerance") +
                                       KSNavMeshedSpaceBuilder::Attribute<double>("relative_tolerance") +
                                       KSNavMeshedSpaceBuilder::Attribute<std::string>("path");


STATICINT sToolboxKSNavMeshedSpace = KSRootBuilder::ComplexElement<KSNavMeshedSpace>("ksnav_meshed_space");

}  // namespace katrin
