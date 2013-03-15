
#include <cassert>
#include <boost/checked_delete.hpp>

#include "Root.hpp"
#include "system/PluginManager.hpp"

struct exeng::Root::Private
{
    Root *root;
    system::PluginManager *pluginManager;

    Private(Root *root) : root(NULL), pluginManager(NULL)
    {
        this->root = root;
        this->pluginManager = new system::PluginManager(*root);
    }
	
    ~Private()
    {
        boost::checked_delete(this->pluginManager);
    }    
};


namespace exeng
{
	Root::Root() : impl(NULL)
	{
		this->impl = new Root::Private(this);
	}


	Root::~Root()
	{
		boost::checked_delete(this->impl);
	}


	system::PluginManager& Root::getPluginManagerRef()
	{
		assert(this->impl != NULL);

		return *this->impl->pluginManager;
	}
}
