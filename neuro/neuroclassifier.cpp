#include "neuroclassifier.h"

NeuroClassifier::NeuroClassifier(std::string filename, unsigned int outputSize)
{
	nn = fann_create_from_file(filename.c_str());
	nout = outputSize;
}

float* NeuroClassifier::run(AbstractPoseDescriptor *pose)
{
	std::vector<float>* features = pose->getFeaturesVector();
	fann_type* input = features->data();
	fann_type* output;
	std::cout<<"FUCK"<<features->size()<<std::endl;
	output = fann_run(nn, input);
	delete features;
	return (float*) output;
}

NeuroClassifier::~NeuroClassifier()
{
	fann_destroy(nn);
}
