#pragma once

#include<d3d11.h>
#include <d3dcompiler.h>
#include<string>
#include<iostream>

template <typename S>
concept ShaderType = std::is_same_v<S, ID3D11PixelShader> || std::is_same_v<S, ID3D11VertexShader>;

template<ShaderType T>
class ShaderBase {
	protected:
		T* shader = nullptr;
		ID3DBlob* blob = nullptr;

	protected:
		bool CompileShader(ID3DBlob** blob, std::wstring filename, std::string entry_point_name, std::string target);

	public:
		virtual void Initialize(std::string filename, ID3D11Device* d3d_device) = 0;
		inline virtual void Release() 
		{ 
			this->shader->Release();
			this->blob->Release();
		}

	public:
		inline T* GetShader() const { return this->shader; }
		inline ID3DBlob* GetBlob() const {return this->blob; }
};

template<ShaderType T>
class Shader {};

template<>
class Shader<ID3D11PixelShader> final: public ShaderBase<ID3D11PixelShader> {
	public:
		void Initialize(std::string filename, ID3D11Device* d3d_device) override;

};

template<>
class Shader<ID3D11VertexShader> final : public ShaderBase<ID3D11VertexShader> {
	public:
		void Initialize(std::string filename, ID3D11Device* d3d_device) override;
};