#ifndef HISTOGRAM_H
#define HISTOGRAM_H

class Histogram
{
public:
	Histogram(unsigned int length);
	Histogram(const Histogram& source);
	~Histogram();
	
	unsigned int getLength();
	float& at(unsigned int index);
	
	float& operator[](unsigned int index);
	
	void normalize();
	void cropUpper(float upperLimit);
	void cropLower(float lowerLimit);
	void crop(float lowerLimit, float upperLimit);
	
	void forEach(void (*f)(float&, unsigned int));
	void forEach(void (*f)(float&));
	
	bool some(bool (*f)(float, unsigned int));
	bool some(bool (*f)(float));
	bool every(bool (*f)(float, unsigned int));
	bool every(bool (*f)(float));
	
	float difference(Histogram& hist);

	Histogram scale(unsigned int newLength);
	
private:
	unsigned int len;
	float* data;
};

template<typename T>
T* map(T (*f)(float, unsigned int), Histogram& hist)
{
	unsigned len = hist.getLength();
	T* result = new T[len];
	for (unsigned i = 0; i < len; i++)
		result[i] = f(hist.at(i), i);
}

#endif // HISTOGRAM_H
