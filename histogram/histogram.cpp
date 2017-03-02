#include "histogram.h"
#include "common/utils/normalizearray.cpp"

int NOK(unsigned x, unsigned y)
{
	unsigned max = (x > y)? x : y;
	for (unsigned i = max; ; i++)
		if (!(i % x) && !(i % y)) return i;
}

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
	data = new float[len];
	for (unsigned int i = 0; i < len; i++)
		data[i] = source.data[i];
}
Histogram::Histogram(const Histogram &source, unsigned int anotherLength)
{
	len = anotherLength;
	data = new float[len];
	scaledFrom(source);
}

Histogram::~Histogram()
{
	delete[] data;
}

unsigned int Histogram::getLength() { return len; }
float& Histogram::at(unsigned int index)
{
	if (index >= len) throw "Index out of bounds";
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

void Histogram::forEach(void (*f)(float&, unsigned int))
{
	for (unsigned int i = 0; i < len; i++)
		f(data[i], i);
}
void Histogram::forEach(void (*f)(float&))
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
		sum += abs(data[i] - hist.data[i]);
	return sum;
}

Histogram Histogram::scale(unsigned int newLength)
{
	if (newLength == len)
		return Histogram(*this);
	return Histogram(*this, newLength);

//	Histogram result(newLength);
//	unsigned count = NOK(newLength, len);
//	unsigned N_this = count / len;
//	unsigned N_that = count / newLength;

//	for (unsigned i = 0; i < count; i++)
//		result.data[i / N_that] += data[i / N_this];

//	// for the sum of hist values to be preserved
//	for (unsigned i = 0; i < newLength; i++)
//		result.data[i] /= N_this;

//	return result;
}

void Histogram::scaledFrom(const Histogram& source)
{
	for (unsigned i = 0; i < len; i++)
		data[i] = 0.0F;

	if (len == 0 || source.len == 0) return; // no scaling allowed with zero-length hists (who whatever uses them?)(int)

	unsigned count = NOK(len, source.len);
	unsigned N_this = count / len;
	unsigned N_that = count / source.len;

	for (unsigned i = 0; i < count; i++)
		data[i / N_this] += source.data[i / N_that];

	// for the sum of hist values to be preserved
	for (unsigned i = 0; i < len; i++)
		data[i] /= N_that;
}

float Histogram::max()
{
	float max = data[0];
	for (unsigned i = 1; i < len; i++)
		if (data[i] > max)
			max = data[i];
	return max;
}
