#pragma once
#include <d3d11.h>

class Buffer {
	protected: 
		ID3D11Buffer* buffer;
	public:
		inline virtual void Release(){buffer->Release(); }
};