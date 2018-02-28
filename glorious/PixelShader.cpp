#include "stdafx.h"
#include "PixelShader.h"

namespace Glorious
{

	PixelShader::PixelShader(std::string const& shader_path, IGameObject* game_object)
		:Component(game_object)
	{
		auto const& device_manager{ DirectManager::GetSingleton() };
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		auto ps_file{ FileManager::ReadBinaryFile(FileManager::GetExePath() + R"(\)" + shader_path) };

		try
		{
			m_PixelShader.Attach(device_manager.CreateShader<ID3D11PixelShader>(ps_file, nullptr));
		}
		catch (std::exception const& e)
		{
			throw;
		}

		device_context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	ID3D11PixelShader* PixelShader::GetShader() const
	{
		return m_PixelShader.Get();
	}
}
