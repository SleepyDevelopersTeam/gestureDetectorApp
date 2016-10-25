#include <cstdlib>

/**
 * @brief Function normalizes a double array, so it sum will be 1.0 (with as much accuracy as possible
 * @param arr - pointer of an array
 * @param len - length of the array
 */
template<typename T>
void normalizeArray(T* arr, const size_t& len)
{
	if (len == 0) return;
	T sum = arr[0];
	for (size_t i = 1; i < len; i++)
	{
		sum += arr[i];
	}
	for (size_t i = 0; i < len; i++)
	{
		arr[i] /= sum;
	}
}
