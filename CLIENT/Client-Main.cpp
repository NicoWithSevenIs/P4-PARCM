
#include "src/BaseRunner.h"

int main() 
{
	BaseRunner b;

	bool success = b.Initialize(1280,720);

	if (!success) 
	{
		return -1;
	}
		
	while (b.IsRunning()) 
	{
		b.Broadcast();
	}

	return 0;
}