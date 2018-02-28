#include "stdafx.h"
#include "VertexShader.h"

namespace Glorious
{
	VertexShader::VertexShader(std::string const& shader_path, IGameObject* game_object)
		:Component(game_object)
	{
		auto const& device_manager{ DirectManager::GetSingleton() };
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };


		//
		auto vs_file{ FileManager::ReadBinaryFile(FileManager::GetExePath() + R"(\)" + shader_path) };

		try
		{
			m_VertexShader.Attach(device_manager.CreateShader<ID3D11VertexShader>(vs_file, nullptr));
		}
		catch (std::exception const& e)
		{
			throw e;
		}

		device_context->VSSetShader(m_VertexShader.Get(), nullptr, 0);


		//
		std::vector<D3D11_INPUT_ELEMENT_DESC> input_desc
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT , 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }

		};

		try
		{
			m_InputLayout.Attach(device_manager.CreateInputLayout(input_desc, vs_file));
		}
		catch (std::exception const& e)
		{
			throw e;
		}

		device_context->IASetInputLayout(m_InputLayout.Get());
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	ID3D11VertexShader* VertexShader::GetShader() const
	{
		return m_VertexShader.Get();
	}
}
