// 
// 
// 

#include "RenderEngine.h"

RenderEngine::RenderEngine(Adafruit_NeoMatrix *matrix)
{
	this->matrix = matrix;
	this->objectsArray = new RenderObject*[this->arraySize];
	Serial.println("Array created.");
}

RenderEngine::~RenderEngine()
{
	if (this->objectsArray != NULL)
	{
		delete[] this->objectsArray;
		Serial.println("Array deleted.");
	}
}

void RenderEngine::AddObject(RenderObject * renderObject)
{
	if (this->objectsCount >= this->arraySize)
	{
		// max count of objects
	}

	this->objectsArray[this->objectsCount] = renderObject;
	this->objectsCount++;
}

void RenderEngine::FrameUpdate(int ms)
{
	matrix->clear();

	for(int i =0; i < this->objectsCount; i++)
	{
		this->objectsArray[i]->OnUpdate(ms);
		this->objectsArray[i]->Render(matrix);
	}

	matrix->show();
}
