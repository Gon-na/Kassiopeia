/*
 * KEMToolbox.hh
 *
 *  Created on: 11.05.2015
 *      Author: gosda
 */

#ifndef KEMTOOLBOX_HH_
#define KEMTOOLBOX_HH_

#include "KKeyNotFoundException.hh"
#include "KSingleton.h"
#include "KSmartPointerRelease.hh"

#include <map>
#include <string>
#include <vector>

namespace KEMField
{

class KEMToolbox : public katrin::KSingleton<KEMToolbox>
{
    friend class KSingleton<KEMToolbox>;  // allow calling the constructor

  public:
    /*
	 * KEMToolbox assumes ownership of the object.
	 */
    template<class Object> void Add(std::string name, Object* ptr);

    /*
	 * KEMToolbox keeps ownership of the object.
	 */
    template<class Object> Object* Get(std::string name);

    /*
	 * KEMToolbox keeps ownership of all objects.
	 */
    template<class Object> std::vector<std::pair<std::string, Object*>> GetAll();

    /*
	 * KEMToolbox creates own KContainer and releases the object from the given one.
	 */
    void AddContainer(katrin::KContainer& container, std::string name);

    void DeleteAll();

  protected:
    KEMToolbox() = default;
    ~KEMToolbox() override = default;

  private:
    bool checkKeyIsFree(std::string name);
    std::shared_ptr<katrin::KContainer> GetContainer(std::string name);

    typedef std::pair<std::string, std::shared_ptr<katrin::KContainer>> NameAndContainer;
    using ContainerMap = std::map<std::string, std::shared_ptr<katrin::KContainer>>;

    ContainerMap fObjects;
};

template<class Object> void KEMToolbox::Add(std::string name, Object* ptr)
{
    auto container = std::make_shared<katrin::KContainer>();
    container->Set(ptr);
    checkKeyIsFree(name);
    fObjects.insert(NameAndContainer(name, container));
}

template<class Object> Object* KEMToolbox::Get(std::string name)
{
    auto container = GetContainer(name);
    Object* object = container->AsPointer<Object>();
    if (!object)
        throw KKeyNotFoundException("KEMToolbox", name, KKeyNotFoundException::wrongType);
    return object;
}

template<class Object> std::vector<std::pair<std::string, Object*>> KEMToolbox::GetAll()
{
    std::vector<std::pair<std::string, Object*>> list;
    for (auto entry : fObjects) {
        Object* candidate = entry.second->AsPointer<Object>();
        if (candidate)
            list.push_back(std::make_pair(entry.first, candidate));
    }
    return list;
}

}  // namespace KEMField
#endif /* KEMTOOLBOX_HH_ */
