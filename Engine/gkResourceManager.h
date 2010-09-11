/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkResourceManager_h_
#define _gkResourceManager_h_

#include "gkCommon.h"


class gkResourceManager
{
public:

	typedef utHashTable<utIntHashKey, gkResource*> Resources;
	typedef Resources::Iterator ResourceIterator;



	///Resource managment events
	class ResourceListener
	{
	public:
		virtual ~ResourceListener() {}

		virtual void notifyResourceCreated(gkResource* res) {}
		virtual void notifyResourceDestroyed(gkResource* res) {}

	};

	typedef utArray<ResourceListener*> Listeners;

public:

	gkResourceManager();
	virtual ~gkResourceManager();

	gkResource* getByHandle(const gkResourceHandle& handle);
	gkResource* getByName(const gkResourceName& name);


	gkResource* create(const gkResourceName& name, const gkParameterMap *params = 0);
	gkResource* clone(gkResource *res, bool track = true, const gkParameterMap *params = 0);


	void destroy(const gkResourceHandle& handle);
	void destroy(const gkResourceName& name);
	void destroy(gkResource* ob);
	void destroyAll(void);

	bool exists(const gkResourceName& name);
	bool exists(const gkResourceHandle& handle);


	ResourceIterator getResourceIterator(void) {return m_resources.iterator();}
	Resources& getResources(void) {return m_resources;}


	void addResourceListener(ResourceListener* res);
	void removeResourceListener(ResourceListener* res);


protected:

	void notifyResourceCreated(gkResource* res);
	void notifyResourceDestroyed(gkResource* res);

	virtual gkResource* createImpl(const gkResourceName& name, const gkResourceHandle& handle, const gkParameterMap *params) = 0;

	///Default to zero if the resource doesn't support cloning
	virtual gkResource* cloneImpl(gkResource *orig, const gkResourceName &name, const gkResourceHandle &handle, const gkParameterMap *params = 0) {return 0;};

	virtual void notifyDestroyAllInstancesImpl(void) {}
	virtual void notifyDestroyAllImpl(void) {}

	virtual void notifyResourceCreatedImpl(gkResource* res) {}
	virtual void notifyResourceDestroyedImpl(gkResource* res) {}

	Resources m_resources;
	Listeners m_listsners;

private:
	gkResourceHandle m_resourceHandles;
};


#endif//_gkResourceManager_h_