#include "gesturelibrary.h"

using namespace std;

GestureLibrary* GestureLibrary::instance = 0;

GestureLibrary::GestureLibrary()
{
	this->content = vector<AbstractGestureDescriptor*>();

	poses = vector<AbstractPoseDescriptor*>();
}

GestureLibrary::~GestureLibrary()
{
//	for (int i = 0; i < this->content.size(); i++)
//	{
//		delete this->content.at(i);
//	}
	this->content.clear();
	this->poses.clear();
}

int GestureLibrary::addGesture(AbstractGestureDescriptor& desc)
{
	getInstance()->content.push_back(&desc);
	return instance->content.size() - 1;
}

int GestureLibrary::matchGesture(AbstractGestureDescriptor& desc)
{
	for (size_t i = 0; i < getInstance()->content.size(); i++)
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
	getInstance()->poses.push_back(&desc);
	return instance->poses.size() - 1;
}
int GestureLibrary::matchPose(AbstractPoseDescriptor &pose, double accuracy)
{
	for (size_t i = 0; i < getInstance()->poses.size(); i++)
	{
		if (pose.similarTo(*(instance->poses.at(i)), accuracy))
		{
			return i;
		}
	}
	return -1;
}

GestureLibrary* GestureLibrary::getInstance()
{
	if (instance == 0)
		instance = new GestureLibrary();
	return instance;
}
