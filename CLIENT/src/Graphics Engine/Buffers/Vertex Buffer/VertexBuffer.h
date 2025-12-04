#pragma once

#include "../Buffer.h"
#include "../../../../../SHARED/Math.h"
#include <iostream>


class VertexBuffer : public Buffer {
	private:
		ID3D11InputLayout* layout;
		UINT size_vertex;
		UINT size_list;
	public:
		void Load(void* list_vertices, UINT size_vertex, UINT size_list, ID3DBlob* blob, ID3D11Device* d3d_device);
	public:
		inline void Release() override {
			Buffer::Release();
			layout->Release();
		}
		inline ID3D11InputLayout* GetLayout() const { return this->layout; }
		inline UINT GetVertexSize(){ return this->size_vertex; }
		inline UINT GetListSize() { return this->size_list; }
};