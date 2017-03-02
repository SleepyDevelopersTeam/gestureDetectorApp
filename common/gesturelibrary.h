#ifndef GESTURELIBRARY_H
#define GESTURELIBRARY_H

#include "descriptors/gesture/abstractgesturedescriptor.h"
#include "descriptors/pose/abstractposedescriptor.h"
#include <vector>

/**
 * @brief The GestureLibrary class stores all predefined gestures and allows
 * to match somehow obtained descriptors to them.
 * GestureLibrary is a singletone.
 * GestureLibrary is responsible for freeing its resources (descriptors).
 */
class GestureLibrary
{
public:
	GestureLibrary();
	~GestureLibrary();

	/**
	 * @brief getInstance implements the lazy singletone initialization.
	 * @return the only instance of GestureLibrary
	 */
	static GestureLibrary* getInstance();

	/**
	 * @brief Adds a gesture to the library
	 * @param desc - descriptor of the gesture
	 * @return index of newly recorded gesture
	 */
	static int addGesture(AbstractGestureDescriptor& desc);

	/**
	 * @brief Matches given gesture to content of the library
	 * @param desc - descriptor of the given gesture
	 * @param accuracy - the accuracy parameter when comapring descriptors
	 * @return index of first matched gesture or -1 if no matches
	 */
	static int matchGesture(AbstractGestureDescriptor& desc);

	static int addPose(AbstractPoseDescriptor& desc);

	static int matchPose(AbstractPoseDescriptor& pose, double accuracy);

private:
	std::vector<AbstractGestureDescriptor*> content;
	static GestureLibrary* instance;
};

#endif // GESTURELIBRARY_H
