#pragma once
#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <stdexcept>

template<typename Identifier, typename Resource>
class ResourceHolder
{
public:
	void Load(Identifier id, const std::string& filename);
	template<typename Parameter>
	void Load(Identifier id, const std::string& filename, const Parameter& second_param);
	Resource& Get(Identifier id);
	const Resource& Get(Identifier id) const;


private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

#include "ResourceHolder.inl"
