#pragma once
#include <d3d11.h>

class Buffer {
	protected: 
		ID3D11Buffer* buffer = nullptr;
	public:
		inline virtual void Release(){buffer->Release(); }
		inline ID3D11Buffer* GetBuffer() const{ return this->buffer;}
};