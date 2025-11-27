
#include <grpcpp/grpcpp.h>

#include "src/BaseRunner.h"

using namespace grpc;

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