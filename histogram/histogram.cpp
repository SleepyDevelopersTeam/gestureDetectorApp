#include "histogram.h"
#include "common/utils/normalizearray.cpp"

Histogram::Histogram(unsigned int length)
{
	len = length;
	data = new float[length];
	for (unsigned i = 0; i < len; i++)
		data[i] = 0.0F;
}
Histogram::Histogram(const Histogram &source)
{
	len = source.len;
	for (unsigned int i = 0; i < len; i++)
		data[i] = source.data[i];
}

Histogram::~Histogram()
{
	delete[] data;
}

unsigned int Histogram::getLength() { return len; }
float& Histogram::at(unsigned int index)
{
	if (index < len) throw "Index out of bounds";
	return data[index];
}
float& Histogram::operator [](unsigned int index)
{
	return at(index);
}

void Histogram::normalize()
{
	normalizeArray(data, len);
}

void Histogram::cropUpper(float upperLimit)
{
	for (unsigned int i = 0; i < len; i++)
		if (data[i] > upperLimit) data[i] = upperLimit;
}
void Histogram::cropLower(float lowerLimit)
{
	for (unsigned int i = 0; i < len; i++)
		if (data[i] < lowerLimit) data[i] = lowerLimit;
}
void Histogram::crop(float lowerLimit, float upperLimit)
{
	if (lowerLimit > upperLimit) throw "Histogram::crop: invalid arguments";
	for (unsigned int i = 0; i < len; i++)
	{
		if (data[i] > upperLimit) data[i] = upperLimit;
		if (data[i] < lowerLimit) data[i] = lowerLimit;
	}
}

// iteration methods

void Histogram::forEach(float (*f)(float, unsigned int))
{
	for (unsigned int i = 0; i < len; i++)
		f(data[i], i);
}
void Histogram::forEach(float (*f)(float))
{
	for (unsigned int i = 0; i < len; i++)
		f(data[i]);
}

bool Histogram::some(bool (*f)(float))
{
	for (unsigned int i = 0; i < len; i++)
		if (f(data[i])) return true;
	return false;
}
bool Histogram::some(bool (*f)(float, unsigned int))
{
	for (unsigned int i = 0; i < len; i++)
		if (f(data[i], i)) return true;
	return false;
}
bool Histogram::every(bool (*f)(float))
{
	for (unsigned int i = 0; i < len; i++)
		if (!f(data[i])) return false;
	return true;
}
bool Histogram::every(bool (*f)(float, unsigned int))
{
	for (unsigned int i = 0; i < len; i++)
		if (!f(data[i], i)) return false;
	return true;
}

float Histogram::difference(Histogram& hist)
{
	float sum = 0;
	for (unsigned int i = 0; i < len; i++)
		sum += data[i] - hist.data[i];
	return sum;
}

Histogram Histogram::scale(unsigned int newLength)
{
	if (newLength == len)
		return Histogram(*this);

	Histogram result(newLength);
	if (newLength > len)
	{
		// TODO: enlarge the hist
	}
	else
	{
		// TODO: shrink the hist
	}
	return result;
}
