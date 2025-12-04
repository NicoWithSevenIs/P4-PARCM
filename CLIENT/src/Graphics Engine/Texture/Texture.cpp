#include "Texture.h"

#include <iostream>
#include <comdef.h>
#include <filesystem>

Texture::Texture()
{
}

Texture::~Texture()
{
	m_texture->Release();
}

bool Texture::load(std::string path, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	std::wstring wide(path.begin(), path.end());

	DirectX::ScratchImage image_data;

	std::wcout << wide.c_str() << std::endl;
	std::cout << std::filesystem::exists(path) << std::endl;

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr)) {
		HRESULT res = DirectX::LoadFromWICFile(wide.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image_data);

		if (SUCCEEDED(res))
		{
			res = DirectX::CreateTexture(device, image_data.GetImages(),
				image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);


			D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
			desc.Format = image_data.GetMetadata().format;
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
			desc.Texture2D.MostDetailedMip = 0;

			device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);

			D3D11_SAMPLER_DESC sampDesc = {};
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

			res = device->CreateSamplerState(&sampDesc, &m_sampler_state);

			deviceContext->PSSetSamplers(0, 1, &m_sampler_state);
		}
		else {
			std::cout << "Texture error" << std::endl;
		}

		if (FAILED(res)) {
			_com_error err(res);
			std::wcout << L"[WIC] Failed to load: " << wide << L"\nReason: " << err.ErrorMessage() << std::endl;
		}

		return SUCCEEDED(res);

		CoUninitialize();
	}
	else {
		std::cerr << "COM initialization failed." << std::endl;
	}

	return false;
}