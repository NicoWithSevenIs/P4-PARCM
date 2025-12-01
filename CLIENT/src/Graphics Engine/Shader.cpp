#include "Shader.h"

template<ShaderType T>
ID3DBlob* ShaderBase<T>::CompileShader(std::wstring filename, std::string entry_point_name, std::string target) {
	ID3DBlob* error_blob = nullptr;
	ID3DBlob* shader_blob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr,
		nullptr,
		entry_point_name.c_str(),
		target.c_str(),
		0, 0,
		&shader_blob,
		&error_blob
	);

	if (!SUCCEEDED(hr))
	{
		if (shader_blob) shader_blob->Release();
		if (error_blob) error_blob->Release();
		std::wcout << "[ERROR] Failed to compile shader: " << filename << std::endl;
		return nullptr;
	}

	return shader_blob;
}


void Shader<ID3D11PixelShader>::Initialize(std::string filename, ID3D11Device* d3d_device)
{
	this->blob = CompileShader(
		std::wstring(filename.begin(), filename.end()), 
		"psmain", 
		"ps_5_0"
	);
	
	HRESULT hr = d3d_device->CreatePixelShader(
		this->blob->GetBufferPointer(), 
		this->blob->GetBufferSize(), 
		nullptr, 
		&this->shader
	);

	if (FAILED(hr))
		std::cout << "[ERROR] Failed to compile shader: " << filename << std::endl;
}

void Shader<ID3D11VertexShader>::Initialize(std::string filename, ID3D11Device* d3d_device) 
{
	this->blob = CompileShader(
		std::wstring(filename.begin(), filename.end()), 
		"vsmain", 
		"vs_5_0"
	);

	HRESULT hr = d3d_device->CreateVertexShader(
		this->blob->GetBufferPointer(),
		this->blob->GetBufferSize(),
		nullptr,
		&this->shader
	);

	if (FAILED(hr))
		std::cout << "[ERROR] Failed to compile shader: " << filename << std::endl;
}