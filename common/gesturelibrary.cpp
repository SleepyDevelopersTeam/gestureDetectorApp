#include "gesturelibrary.h"

using namespace std;

GestureLibrary* GestureLibrary::instance = 0;

GestureLibrary::GestureLibrary()
{
	this->content = vector<AbstractGestureDescriptor*>();
}

GestureLibrary::~GestureLibrary()
{
//	for (int i = 0; i < this->content.size(); i++)
//	{
//		delete this->content.at(i);
//	}
	this->content.clear();
}

int GestureLibrary::addGesture(AbstractGestureDescriptor& desc)
{
	instance->content.push_back(&desc);
	return instance->content.size() - 1;
}

int GestureLibrary::matchGesture(AbstractGestureDescriptor& desc)
{
	for (size_t i = 0; i < instance->content.size(); i++)
	{
		if (desc.similarTo(*(instance->content.at(i))))
		{
			return i;
		}
	}
	return -1;
}

int GestureLibrary::addPose(AbstractPoseDescriptor &desc)
{
	// TODO
	return -1;
}
int GestureLibrary::matchPose(AbstractPoseDescriptor &pose, double accuracy)
{
	// TODO
	return -1;
}

GestureLibrary* GestureLibrary::getInstance()
{
	if (instance == 0)
		instance = new GestureLibrary();
	return instance;
}
