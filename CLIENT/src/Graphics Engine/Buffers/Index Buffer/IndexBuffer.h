#pragma once
#include "../Buffer.h"
#include <iostream>
class IndexBuffer: public Buffer
{
	private:
		UINT size_list;
	public:
		void Load(void* list_incides, UINT size_list, ID3D11Device* d3d_device);
	public:
		inline UINT GetIndexListSize() {return this->size_list;}
};