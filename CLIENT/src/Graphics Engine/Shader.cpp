#include "Shader.h"

template<ShaderType T>
bool ShaderBase<T>::CompileShader(ID3DBlob** blob, std::wstring filename, std::string entry_point_name, std::string target) {
	ID3DBlob* error_blob = nullptr;
	ID3DBlob* shader_blob = nullptr;

	std::wstring directory = L"SHADERS/" + filename;

	HRESULT hr = D3DCompileFromFile(
		directory.c_str(),
		nullptr,
		nullptr,
		entry_point_name.c_str(),
		target.c_str(),
		0, 0,
		&shader_blob,
		&error_blob
	);

	if (SUCCEEDED(hr)) 
	{
		*blob = shader_blob;
		return true;
	}
	
	if (shader_blob) 
	{
		shader_blob->Release();
	}
		
	if (error_blob)
	{
		std::cerr << (const char*)error_blob->GetBufferPointer() << std::endl;
		error_blob->Release();
	}

	std::wcout << "[ERROR] Failed to Compile Shader: " << filename << std::endl;
		
	return false;
	

}


void Shader<ID3D11PixelShader>::Initialize(std::string filename, ID3D11Device* d3d_device)
{
	bool success = CompileShader(
		&this->blob,
		std::wstring(filename.begin(), filename.end()), 
		"psmain", 
		"ps_5_0"
	);

	if (!success) {
		std::cout << "[ERROR] Failed to Initialize Pixel Shader: " << filename << std::endl;
		return;
	}
	
	HRESULT hr = d3d_device->CreatePixelShader(
		this->blob->GetBufferPointer(), 
		this->blob->GetBufferSize(), 
		nullptr, 
		&this->shader
	);

	if (FAILED(hr))
		std::cout << "[ERROR] Failed to Initialize Pixel Shader: " << filename << std::endl;
	else std::cout << "[LOG] Successfully Initialized Pixel Shader: " << filename << std::endl;
}

void Shader<ID3D11VertexShader>::Initialize(std::string filename, ID3D11Device* d3d_device) 
{
	bool success = CompileShader(
		&this->blob,
		std::wstring(filename.begin(), filename.end()),
		"vsmain",
		"vs_5_0"
	);

	if (!success) {
		std::cout << "[ERROR] Failed to Initialize Vertex Shader: " << filename << std::endl;
		return;
	}

	HRESULT hr = d3d_device->CreateVertexShader(
		this->blob->GetBufferPointer(),
		this->blob->GetBufferSize(),
		nullptr,
		&this->shader
	);

	if (FAILED(hr))
		std::cout << "[ERROR] Failed to Initialize Vertex Shader: " << filename << std::endl;
	else std::cout << "[LOG] Successfully Initialized Vertex Shader: " << filename << std::endl;
}